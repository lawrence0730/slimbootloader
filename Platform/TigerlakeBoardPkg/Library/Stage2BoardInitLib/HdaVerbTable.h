/** @file

  Copyright (c) 2021, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef __HDA_VERB_TABLE_H__
#define __HDA_VERB_TABLE_H__

#include <Library/BaseLib.h>

///
/// Use this macro to create HDAUDIO_VERB_TABLE and populate size automatically
///
#define HDAUDIO_VERB_TABLE_INIT(Vid,Did,Rid,Sdi,...) \
{ \
  { Vid, Did, Rid, Sdi, (sizeof((UINT32[]){__VA_ARGS__})/sizeof(UINT32)) }, \
  { __VA_ARGS__ } \
}

/**
  Azalia verb table header
  Every verb table should contain this defined header and followed by azalia verb commands.
**/
typedef struct {
  UINT16  VendorId;             ///< Codec Vendor ID
  UINT16  DeviceId;             ///< Codec Device ID
  UINT8   RevisionId;           ///< Revision ID of the codec. 0xFF matches any revision.
  UINT8   SdiNum;               ///< SDI number, 0xFF matches any SDI.
  UINT16  DataDwords;           ///< Number of data DWORDs following the header.
} PCH_HDA_VERB_TABLE_HEADER;

#ifdef _MSC_VER
//
// Disable "zero-sized array in struct/union" extension warning.
// Used for neater verb table definitions.
//
#pragma warning (push)
#pragma warning (disable: 4200)
#endif
typedef struct  {
  PCH_HDA_VERB_TABLE_HEADER  Header;
  UINT32 Data[];
} HDAUDIO_VERB_TABLE;
#ifdef _MSC_VER
#pragma warning (pop)
#endif

//7583X003_4
const HDAUDIO_VERB_TABLE OemHdaVerbTblSomDb5830 = HDAUDIO_VERB_TABLE_INIT (
// ;===================================================================================================
// ;
// ;                               Realtek Semiconductor Corp.
// ;
// ;===================================================================================================
// 
// ;Realtek High Definition Audio Configuration - Version : 5.0.3.1
// ;Realtek HD Audio Codec : ALC892
// ;PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_00000000
// ;HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0892&SUBSYS_00000000
// ;The number of verb command block : 17
// 
// ;    NID 0x11 : 0x40000000
// ;    NID 0x12 : 0x411111F0
// ;    NID 0x14 : 0x01014010
// ;    NID 0x15 : 0x411111F0
// ;    NID 0x16 : 0x411111F0
// ;    NID 0x17 : 0x411111F0
// ;    NID 0x18 : 0x01A19040
// ;    NID 0x19 : 0x411111F0
// ;    NID 0x1A : 0x01813030
// ;    NID 0x1B : 0x411111F0
// ;    NID 0x1C : 0x411111F0
// ;    NID 0x1D : 0x40220601
// ;    NID 0x1E : 0x01451120
// ;    NID 0x1F : 0x411111F0
// 
// 
  //
  //  VerbTable: TGL Display Audio Codec
  //  Revision ID = 0xFF
  //  Codec Vendor: 0x10EC0888
  //
  0x10EC, 0x0888,
  0xFF, 0xFF,
// ;===== HDA Codec Subsystem ID Verb-table =====
// ;HDA Codec Subsystem ID  : 0x00000000
// dd 00172000h
// dd 00172100h
// dd 00172200h
// dd 00172300h
   0x00172000,
   0x00172100,
   0x00172200,
   0x00172300,
// 
// 
// ;===== Pin Widget Verb-table =====
// ;Widget node 0x01 :
// dd 0017FF00h
// dd 0017FF00h
// dd 0017FF00h
// dd 0017FF00h
   0x0017FF00,
   0x0017FF00,
   0x0017FF00,
   0x0017FF00,
// ;Pin widget 0x11 - S/PDIF-OUT2
// dd 01171C00h
// dd 01171D00h
// dd 01171E00h
// dd 01171F40h
   0x01171C00,
   0x01171D00,
   0x01171E00,
   0x01171F40,
// ;Pin widget 0x12 - DMIC
// dd 01271CF0h
// dd 01271D11h
// dd 01271E11h
// dd 01271F41h
   0x01271CF0,
   0x01271D11,
   0x01271E11,
   0x01271F41,
// ;Pin widget 0x14 - FRONT (Port-D)
// dd 01471C10h
// dd 01471D40h
// dd 01471E01h
// dd 01471F01h
   0x01471C10,
   0x01471D40,
   0x01471E01,
   0x01471F01,
// ;Pin widget 0x15 - SURR (Port-A)
// dd 01571CF0h
// dd 01571D11h
// dd 01571E11h
// dd 01571F41h
   0x01571CF0,
   0x01571D11,
   0x01571E11,
   0x01571F41,
// ;Pin widget 0x16 - CEN/LFE (Port-G)
// dd 01671CF0h
// dd 01671D11h
// dd 01671E11h
// dd 01671F41h
   0x01671CF0,
   0x01671D11,
   0x01671E11,
   0x01671F41,
// ;Pin widget 0x17 - SIDESURR (Port-H)
// dd 01771CF0h
// dd 01771D11h
// dd 01771E11h
// dd 01771F41h
   0x01771CF0,
   0x01771D11,
   0x01771E11,
   0x01771F41,
// ;Pin widget 0x18 - MIC1 (Port-B)
// dd 01871C40h
// dd 01871D90h
// dd 01871EA1h
// dd 01871F01h
   0x01871C40,
   0x01871D90,
   0x01871EA1,
   0x01871F01,
// ;Pin widget 0x19 - MIC2 (Port-F)
// dd 01971CF0h
// dd 01971D11h
// dd 01971E11h
// dd 01971F41h
   0x01971CF0,
   0x01971D11,
   0x01971E11,
   0x01971F41,
// ;Pin widget 0x1A - LINE1 (Port-C)
// dd 01A71C30h
// dd 01A71D30h
// dd 01A71E81h
// dd 01A71F01h
   0x01A71C30,
   0x01A71D30,
   0x01A71E81,
   0x01A71F01,
// ;Pin widget 0x1B - LINE2 (Port-E)
// dd 01B71CF0h
// dd 01B71D11h
// dd 01B71E11h
// dd 01B71F41h
   0x01B71CF0,
   0x01B71D11,
   0x01B71E11,
   0x01B71F41,
// ;Pin widget 0x1C - CD-IN
// dd 01C71CF0h
// dd 01C71D11h
// dd 01C71E11h
// dd 01C71F41h
   0x01C71CF0,
   0x01C71D11,
   0x01C71E11,
   0x01C71F41,
// ;Pin widget 0x1D - BEEP-IN
// dd 01D71C01h
// dd 01D71D06h
// dd 01D71E22h
// dd 01D71F40h
   0x01D71C01,
   0x01D71D06,
   0x01D71E22,
   0x01D71F40,
// ;Pin widget 0x1E - S/PDIF-OUT
// dd 01E71C20h
// dd 01E71D11h
// dd 01E71E45h
// dd 01E71F01h
   0x01E71C20,
   0x01E71D11,
   0x01E71E45,
   0x01E71F01,
// ;Pin widget 0x1F - S/PDIF-IN
// dd 01F71CF0h
// dd 01F71D11h
// dd 01F71E11h
// dd 01F71F41h
   0x01F71CF0,
   0x01F71D11,
   0x01F71E11,
   0x01F71F41,
// ;Widget node 0x20 :
// dd 02050007h
// dd 020409C8h
// dd 02050007h
// dd 020409C8h
   0x02050007,
   0x020409C8,
   0x02050007,
   0x020409C8,
);
//7583X003_4

CONST HDAUDIO_VERB_TABLE HdaVerbTableDisplayAudio = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: TGL Display Audio Codec
  //  Revision ID = 0xFF
  //  Codec Vendor: 0x80862812
  //
  0x8086, 0x2812,
  0xFF, 0xFF,
  //
  // Display Audio Verb Table
  //
  // Enable the third converter and 4 pin widgets (for GEN10+, the Vendor Node ID is 02h)
  0x00278111,
  // Pin Widget 5 - PORT B - Configuration Default: 0x18560010
  0x00571C10,
  0x00571D00,
  0x00571E56,
  0x00571F18,
  // Pin Widget 6 - PORT C - Configuration Default: 0x18560020
  0x00671C20,
  0x00671D00,
  0x00671E56,
  0x00671F18,
  // Pin Widget 7 - PORT D - Configuration Default: 0x18560030
  0x00771C30,
  0x00771D00,
  0x00771E56,
  0x00771F18,
  // Pin Widget 8 - PORT E - Configuration Default: 0x18560040
  // For GEN10+ forth port was added and Node ID 8 has this Pin Widget for the forth port
  0x00871C40,
  0x00871D00,
  0x00871E56,
  0x00871F18,
  // Disable the third converter and 4 Pins (NID 02h)
  0x00278100
);

//
// TGL RVP Audio Codec
//
CONST HDAUDIO_VERB_TABLE TglHdaVerbTableAlc711 = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC711)
  //  Revision ID = 0xff
  //  Codec Verb Table
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0700
  //
  0x10EC, 0x0711,
  0xFF, 0xFF,
 //===================================================================================================
//
//                               Realtek Semiconductor Corp.
//
//===================================================================================================
//
//Realtek High Definition Audio Configuration - Version : 5.0.3.1
//Realtek HD Audio Codec : ALC711
//PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_72708086
//HDA Codec PnP ID : INTELAUDIO\FUNC_01&VEN_10EC&DEV_0711&SUBSYS_10EC11C2
//The number of verb command block : 17

//    NID 0x12 : 0x40000000
//    NID 0x13 : 0x411111F0
//    NID 0x14 : 0x411111F0
//    NID 0x15 : 0x411111F0
//    NID 0x16 : 0x411111F0
//    NID 0x17 : 0x411111F0
//    NID 0x18 : 0x411111F0
//    NID 0x19 : 0x04A11010
//    NID 0x1A : 0x411111F0
//    NID 0x1B : 0x411111F0
//    NID 0x1D : 0x40400001
//    NID 0x1E : 0x411111F0
//    NID 0x1F : 0x411111F0
//    NID 0x21 : 0x04211020
//    NID 0x29 : 0x411111F0


//===== HDA Codec Subsystem ID Verb-table =====
//HDA Codec Subsystem ID  : 0x10EC11C2
  0x001720C2,
  0x00172111,
  0x001722EC,
  0x00172310,

  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C00,
  0x01271D00,
  0x01271E00,
  0x01271F40,
  //Pin widget 0x13 - DMIC
  0x01371CF0,
  0x01371D11,
  0x01371E11,
  0x01371F41,
  //Pin widget 0x14 - FRONT (Port-D)
  0x01471CF0,
  0x01471D11,
  0x01471E11,
  0x01471F41,
  //Pin widget 0x15 - I2S-OUT
  0x01571CF0,
  0x01571D11,
  0x01571E11,
  0x01571F41,
  //Pin widget 0x16 - LINE3 (Port-B)
  0x01671CF0,
  0x01671D11,
  0x01671E11,
  0x01671F41,
  //Pin widget 0x17 - I2S-OUT
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  //Pin widget 0x18 - I2S-IN
  0x01871CF0,
  0x01871D11,
  0x01871E11,
  0x01871F41,
  //Pin widget 0x19 - MIC2 (Port-F)
  0x01971C10,
  0x01971D10,
  0x01971EA1,
  0x01971F04,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71CF0,
  0x01A71D11,
  0x01A71E11,
  0x01A71F41,
  //Pin widget 0x1B - LINE2 (Port-E)
  0x01B71CF0,
  0x01B71D11,
  0x01B71E11,
  0x01B71F41,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C01,
  0x01D71D00,
  0x01D71E40,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x1F - S/PDIF-IN
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41,
  //Pin widget 0x21 - HP-OUT (Port-I)
  0x02171C20,
  0x02171D10,
  0x02171E21,
  0x02171F04,
  //Pin widget 0x29 - I2S-IN
  0x02971CF0,
  0x02971D11,
  0x02971E11,
  0x02971F41,
  //Widget node 0x20 - 1 :
  0x05B50010,
  0x05B4581D,
  0x0205006F,
  0x0204058B,

  //Widget node 0x20 - 2 :
  0x02050045,
  0x02045289,
  0x0205004A,
  0x0204201B,
);

//
// Realtek ALC701 Audio Codec
//
CONST HDAUDIO_VERB_TABLE TglHdaVerbTableAlc274 = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC274) CNL external kit
  //  Revision ID = 0xff
  //  Codec Verb Table for CNL PCH boards
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0274
  //
  0x10EC, 0x0274,
  0xFF, 0xFF,
  //===================================================================================================
  //
  //                               Realtek Semiconductor Corp.
  //
  //===================================================================================================

  //Realtek High Definition Audio Configuration - Version : 5.0.3.0
  //Realtek HD Audio Codec : ALC274
  //PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_72708086
  //HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0274&SUBSYS_10EC10F6
  //The number of verb command block : 16

  //    NID 0x12 : 0x40000000
  //    NID 0x13 : 0x411111F0
  //    NID 0x14 : 0x411111F0
  //    NID 0x15 : 0x411111F0
  //    NID 0x16 : 0x411111F0
  //    NID 0x17 : 0x411111F0
  //    NID 0x18 : 0x411111F0
  //    NID 0x19 : 0x04A11020
  //    NID 0x1A : 0x411111F0
  //    NID 0x1B : 0x411111F0
  //    NID 0x1D : 0x40451B05
  //    NID 0x1E : 0x411111F0
  //    NID 0x1F : 0x411111F0
  //    NID 0x21 : 0x04211010


  //===== HDA Codec Subsystem ID Verb-table =====
  //,DA Codec Subsystem ID  : 0x10EC10F6
  0x001720F6,
  0x00172110,
  0x001722EC,
  0x00172310,

  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C00,
  0x01271D00,
  0x01271E00,
  0x01271F40,
  //Pin widget 0x13 - DMIC
  0x01371CF0,
  0x01371D11,
  0x01371E11,
  0x01371F41,
  //Pin widget 0x14 - NPC
  0x01471CF0,
  0x01471D11,
  0x01471E11,
  0x01471F41,
  //Pin widget 0x15 - I2S_OUT2
  0x01571CF0,
  0x01571D11,
  0x01571E11,
  0x01571F41,
  //Pin widget 0x16 - LINE3 (Port-B)
  0x01671CF0,
  0x01671D11,
  0x01671E11,
  0x01671F41,
  //Pin widget 0x17 - I2S_OUT1
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  //Pin widget 0x18 - I2S_IN
  0x01871CF0,
  0x01871D11,
  0x01871E11,
  0x01871F41,
  //Pin widget 0x19 - MIC2 (Port-F)
  0x01971C20,
  0x01971D10,
  0x01971EA1,
  0x01971F04,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71CF0,
  0x01A71D11,
  0x01A71E11,
  0x01A71F41,
  //Pin widget 0x1B - LINE2 (Port-E)
  0x01B71CF0,
  0x01B71D11,
  0x01B71E11,
  0x01B71F41,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C05,
  0x01D71D1B,
  0x01D71E45,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x1F - S/PDIF-IN
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41,
  //Pin widget 0x21 - HP-OUT (Port-I)
  0x02171C10,
  0x02171D10,
  0x02171E21,
  0x02171F04,
  //Widget node 0x20 :
  0x02050045,
  0x02045289,
  0x0205006F,
  0x02042C0B,
  //Widget node 0x20 - 1 :
  0x02050035,
  0x02048968,
  0x05B50001,
  0x05B48540,
  //Widget node 0x20 - 2 :
  0x05850000,
  0x05843888,
  0x05850000,
  0x05843888,
  //Widget node 0x20 - 3 :
  0x0205004A,
  0x0204201B,
  0x0205004A,
  0x0204201B
);// HdaVerbTableAlc274

//
// Realtek ALC274 Audio Codec
//
CONST HDAUDIO_VERB_TABLE TglHdaVerbTableAlc701 = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC701) CNL external kit
  //  Revision ID = 0xff
  //  Codec Verb Table for CNL PCH boards
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0701
  //
  0x10EC, 0x0701,
  0xFF, 0xFF,
  //===================================================================================================
  //
  //                               Realtek Semiconductor Corp.
  //
  //===================================================================================================

  //Realtek High Definition Audio Configuration - Version : 5.0.3.0
  //Realtek HD Audio Codec : ALC701
  //PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_72708086
  //HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0701&SUBSYS_10EC10F4
  //The number of verb command block : 17

  //    NID 0x12 : 0x40000000
  //    NID 0x13 : 0x411111F0
  //    NID 0x14 : 0x411111F0
  //    NID 0x15 : 0x411111F0
  //    NID 0x16 : 0x411111F0
  //    NID 0x17 : 0x411111F0
  //    NID 0x18 : 0x411111F0
  //    NID 0x19 : 0x04A11020
  //    NID 0x1A : 0x411111F0
  //    NID 0x1B : 0x411111F0
  //    NID 0x1D : 0x40451B05
  //    NID 0x1E : 0x411111F0
  //    NID 0x1F : 0x411111F0
  //    NID 0x21 : 0x04211010
  //    NID 0x29 : 0x411111F0


  //===== HDA Codec Subsystem ID Verb-table =====
  //HDA Codec Subsystem ID  : 0x10EC10F4
  0x001720F4,
  0x00172110,
  0x001722EC,
  0x00172310,

  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C00,
  0x01271D00,
  0x01271E00,
  0x01271F40,
  //Pin widget 0x13 - DMIC
  0x01371CF0,
  0x01371D11,
  0x01371E11,
  0x01371F41,
  //Pin widget 0x14 - FRONT (Port-D)
  0x01471CF0,
  0x01471D11,
  0x01471E11,
  0x01471F41,
  //Pin widget 0x15 - I2S-OUT
  0x01571CF0,
  0x01571D11,
  0x01571E11,
  0x01571F41,
  //Pin widget 0x16 - LINE3 (Port-B)
  0x01671CF0,
  0x01671D11,
  0x01671E11,
  0x01671F41,
  //Pin widget 0x17 - I2S-OUT
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  //Pin widget 0x18 - I2S-IN
  0x01871CF0,
  0x01871D11,
  0x01871E11,
  0x01871F41,
  //Pin widget 0x19 - MIC2 (Port-F)
  0x01971C20,
  0x01971D10,
  0x01971EA1,
  0x01971F04,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71CF0,
  0x01A71D11,
  0x01A71E11,
  0x01A71F41,
  //Pin widget 0x1B - LINE2 (Port-E)
  0x01B71CF0,
  0x01B71D11,
  0x01B71E11,
  0x01B71F41,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C05,
  0x01D71D1B,
  0x01D71E45,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x1F - S/PDIF-IN
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41,
  //Pin widget 0x21 - HP-OUT (Port-I)
  0x02171C10,
  0x02171D10,
  0x02171E21,
  0x02171F04,
  //Pin widget 0x29 - I2S-IN
  0x02971CF0,
  0x02971D11,
  0x02971E11,
  0x02971F41,
  //Widget node 0x20 :
  0x02050045,
  0x02045289,
  0x0205006F,
  0x02042C0B,

  //Widget node 0x20 - 1 :
  0x05850000,
  0x05843888,
  0x0205004A,
  0x0204201B,
);// HdaVerbTableAlc701
#endif /* __HDA_VERB_TABLE_H__ */
