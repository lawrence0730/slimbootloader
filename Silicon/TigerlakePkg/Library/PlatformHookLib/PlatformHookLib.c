/** @file
  The platform hook library.

  Copyright (c) 2013 - 2015, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/PciLib.h>
#include <PchAccess.h>
#include <CpuRegsAccess.h>
#include <Library/PciCf8Lib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/BootloaderCoreLib.h>
#include <IndustryStandard/Pci22.h>
#include <Library/PchPcrLib.h>
#include <Library/BootloaderCommonLib.h>

#define V_FSP_LPSS_UART_PPR_CLK_N_DIV   32767
#define V_FSP_LPSS_UART_PPR_CLK_M_DIV   602

#define R_LPSS_IO_MEM_PCP                 0x200        ///< Private Clock Parameters
#define B_LPSS_IO_MEM_PCP_CLK_UPDATE      (1<<31)      ///< Clock Divider Update
#define B_LPSS_IO_MEM_PCP_N_VAL           0x7FFF0000   ///< N value for the M over N divider
#define B_LPSS_IO_MEM_PCP_M_VAL           0x0000FFFE   ///< M value for the M over N divider
#define B_LPSS_IO_MEM_PCP_CLK_EN          1            ///< Clock Enable
#define  V_LPSS_IO_PPR_CLK_N_DIV          32767
#define  V_LPSS_IO_PPR_CLK_M_DIV          602

#define R_LPSS_IO_MEM_RESETS              0x204        ///< Software Reset
#define B_LPSS_IO_MEM_HC_RESET_REL        0x03         ///< LPSS IO Host Controller Reset Release
#define B_LPSS_IO_MEM_iDMA_RESET_REL      0x04         ///< iDMA Reset Release

#define MM_PCI_OFFSET(Bus, Device, Function) \
    ( (UINTN)(Bus << 20) +    \
      (UINTN)(Device << 15) + \
      (UINTN)(Function << 12) )

CONST UINT32
mUartMmPciOffset[] = {
  MM_PCI_OFFSET (0, PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART0),
  MM_PCI_OFFSET (0, PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART1, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART1),
  MM_PCI_OFFSET (0, PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART2, PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART2),
};

/**
  Get serial port stride register size.

  @retval  The serial port register stride size.

**/
UINT8
EFIAPI
GetSerialPortStrideSize (
  VOID
  )
{
  if (GetDebugPort () >= PCH_MAX_SERIALIO_UART_CONTROLLERS) {
    // ISA UART, 0x2F8 or 0x3F8 I/O port
    return 1;
  } else {
    // PCH UART
    return 4;
  }
}

/**
  Get serial port register base address.

  @retval  The serial port register base address.

**/
UINT64
EFIAPI
GetSerialPortBase (
  VOID
  )
{
  UINT16  Cmd16;
  UINTN   PciAddress;
  UINT8   DebugPort;
  UINT64  MmioBase;

  DebugPort = GetDebugPort ();
  if (DebugPort >=  PCH_MAX_SERIALIO_UART_CONTROLLERS) {
    if (DebugPort == 0xFE) {
      return 0x2F8;
    } else {
      return 0x3F8;
    }
  }

  PciAddress = mUartMmPciOffset[DebugPort] + (UINTN)PcdGet64(PcdPciExpressBaseAddress);
  Cmd16 = MmioRead16 (PciAddress + PCI_VENDOR_ID_OFFSET);
  if (Cmd16 == 0xFFFF) {
    //
    // Device might be hidden, assigned temp base address for it
    //
    return LPSS_UART_TEMP_BASE_ADDRESS(DebugPort);
  } else {
    if (MmioRead32 (PciAddress + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_MEMORY_SPACE) {
      MmioBase  = LShiftU64 (MmioRead32 (PciAddress + PCI_BASE_ADDRESSREG_OFFSET + 4), 32);
      MmioBase += (MmioRead32 (PciAddress + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0);
      return MmioBase;
    } else {
      return 0;
    }
  }
}

/**
  Performs platform specific initialization required for the CPU to access
  the hardware associated with a SerialPortLib instance.  This function does
  not initialize the serial port hardware itself.  Instead, it initializes
  hardware devices that are required for the CPU to access the serial port
  hardware.  This function may be called more than once.

  @retval RETURN_SUCCESS       The platform specific initialization succeeded.
  @retval RETURN_DEVICE_ERROR  The platform specific initialization could not be completed.

**/
RETURN_STATUS
EFIAPI
LegacySerialPortInitialize (
  VOID
  )
{
  UINTN   LpcBaseAddr;
  UINT16  Data16;

  LpcBaseAddr = PCI_LIB_ADDRESS (
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_LPC,
                      PCI_FUNCTION_NUMBER_PCH_LPC,
                      0);

  Data16 = PciCf8Read16 (LpcBaseAddr + R_LPC_CFG_IOD);
  Data16 |= (V_LPC_CFG_IOD_COMB_3E8 << N_LPC_CFG_IOD_COMB);
  Data16 |= (V_LPC_CFG_IOD_COMA_3F8 << N_LPC_CFG_IOD_COMA);
  MmioWrite16 (PCH_PCR_ADDRESS (PID_DMI, R_PCH_DMI_PCR_LPCIOD), Data16);
  PciCf8Write16 (LpcBaseAddr + R_LPC_CFG_IOD, Data16);

  Data16 = PciCf8Read16 (LpcBaseAddr + R_LPC_CFG_IOE);
  Data16 |= B_LPC_CFG_IOE_CBE;
  Data16 |= B_LPC_CFG_IOE_CAE;
  MmioWrite16 (PCH_PCR_ADDRESS (PID_DMI, R_PCH_DMI_PCR_LPCIOE), Data16);
  PciCf8Write16 (LpcBaseAddr + R_LPC_CFG_IOE, Data16);

  return RETURN_SUCCESS;
}


RETURN_STATUS
EFIAPI
PlatformHookSerialPortInitialize (
  VOID
  )
{
  UINTN             PciAddress;
  UINT32            BarAddress;
  UINT8             DebugPort;
  UINT32            Data32;

  DebugPort  = GetDebugPort ();

  if ( DebugPort < PCH_MAX_SERIALIO_UART_CONTROLLERS) {

    BarAddress = LPSS_UART_TEMP_BASE_ADDRESS(DebugPort);
    PciAddress = mUartMmPciOffset[DebugPort] + (UINTN)PcdGet64(PcdPciExpressBaseAddress);
    MmioWrite32 (PciAddress + R_SERIAL_IO_CFG_BAR0_LOW,  BarAddress);
    MmioWrite32 (PciAddress + R_SERIAL_IO_CFG_BAR0_HIGH, 0x0);
    MmioWrite32 (PciAddress + R_SERIAL_IO_CFG_BAR1_LOW,  BarAddress + 0x1000);
    MmioWrite32 (PciAddress + R_SERIAL_IO_CFG_BAR1_HIGH, 0x0);
    MmioWrite32 (PciAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE);
    MmioOr32    (PciAddress + R_SERIAL_IO_CFG_D0I3MAXDEVPG, BIT18 | BIT17 | BIT16);

    //
    // Bring UART out of reset
    //
    MmioWrite32 (BarAddress + R_SERIAL_IO_MEM_PPR_RESETS, B_SERIAL_IO_MEM_PPR_RESETS_IDMA | B_SERIAL_IO_MEM_PPR_RESETS_APB | B_SERIAL_IO_MEM_PPR_RESETS_FUNC);
    MmioRead32 (BarAddress + R_SERIAL_IO_MEM_PPR_RESETS);

    //
    // Set clock
    //
    Data32 = (V_FSP_LPSS_UART_PPR_CLK_N_DIV << 16) | (V_FSP_LPSS_UART_PPR_CLK_M_DIV << 1) | B_LPSS_IO_MEM_PCP_CLK_EN;
    MmioWrite32 (BarAddress + R_LPSS_IO_MEM_PCP, Data32);
    MmioWrite32 (BarAddress + R_LPSS_IO_MEM_PCP, Data32 | B_LPSS_IO_MEM_PCP_CLK_UPDATE);
    MmioRead32  (BarAddress + R_LPSS_IO_MEM_PCP);
//7583X003_1
  } else {
//7583X003_1
    LegacySerialPortInitialize ();
  }

  return RETURN_SUCCESS;
}
