![Alt text](https://www.advantech.tw/css/css-img/advantech-logo-notagl.svg "Advantech sbl")

Slim Bootloader support 
=======================

Status
------

  |Apollolake|Platform ID|Bring up|GPIO|HSIO|EC(IO)|GOP(VBT)|Payload|
  |----|----|----|----|----|----|----|----|
  |SOM-2569|0x10|Yes|NotReady|NotReady|NotReady|Yes|UEFI|
  |SOM-3569|0x11|Yes|NotReady|NotReady|NotReady|Yes|UEFI|
  |SOM-6869|0x12|Yes|NotReady|NotReady|NotReady|Yes|UEFI|
  |SOM-7569|0x13|Yes|NotReady|NotReady|NotReady|Yes|UEFI|


  |Coffeelake|Platform ID|Bring up|GPIO|HSIO|EC(IO)|GOP(VBT)|Payload|
  |----|----|----|----|----|----|----|----|
  |SOM-6882|0x01|Yes|Yes|NotReady|NotReady|Yes|UEFI|

  |Cometlake|Platform ID|Bring up|GPIO|HSIO|EC(IO)|GOP(VBT)|Payload|
  |----|----|----|----|----|----|----|----|
  |NotReady|NotReady|NotReady|NotReady|NotReady|NotReady|NotReady|NotReady|

  |Tigerlake|Platform ID|Bring up|GPIO|HSIO|EC(IO)|GOP(VBT)|PYLD|EPLD|
  |----|----|----|----|----|----|----|----|----|
  |SOM-7583|0x10|Yes|Yes|Yes|Yes|Yes|OSLR|UEFI|

  |Elkhartlake|Platform ID|BringUp|GPIO|HSIO|EC(IO)|GOP(VBT)|Payload|
  |----|----|----|----|----|----|----|----|
  |SOM-2532|0x10|Yes|NotReady|NotReady|NotReady|Yes|UEFI|

History
-------

> ## 7583000S000X003    
>
>> 7583X003_1    Add EC support.
>> 7583X003_2    Add ftpm support.
>> 7583X003_3    Update System_OK GPIO state E7 at PreSiliconInit stage.
>> 7583X003_4    Add Realtek ALC892 Audio Codec Verb table.

  7583X002    Update Platform ID to 0x10 and enable SOC UART2 debug port.
  
  2532X001    Add SOM-2532 support with external fsp binary.
  
  6882X001_1  Update GPIO setting and removed CRB EC support.


Build Environment
-----------------

>Python 3.6

    set PYTHON_HOME=C:\Python36

>NASM 2.11

    set NASM_PREFIX=C:\Nasm\

>IASL 20160422

    set IASL_PREFIX=C:\ASL\

>OpenSSL

    set OPENSSL_PATH=C:\Openssl

>Slim BootLoader Key

    set SBL_KEY_DIR=%CD%\..\sblKeys\

>EDK2 Payload Image 

    set WORKSPACE=%CD%

    set PACKAGES_PATH=%CD%

    set EDK_TOOLS_PATH=%CD%\BaseTools

    set BASE_TOOLS_PATH=%CD%\BaseTools

Download Slim Bootloader
------------------------

git clone https://github.com/Advgcipc/slimbootloader.git


Create Slim Bootloader Key
--------------------------

python BootloaderCorePkg\Tools\GenerateKeys.py -k ..\sblKeys


Build Slim Bootloader
---------------------

python BuildLoader.py build $(PlatformName)

python BuildLoader.py clean -d

Build SBL Release mode:
python BuildLoader.py build $(PlatformName) -r -p "OsLoader.efi:LLDR:Lz4;UEFIPAYLOADRel.fd:UEFI:Lzma"

Build SBL Debug mode:
python BuildLoader.py build $(PlatformName) -p "OsLoader.efi:LLDR:Lz4;UEFIPAYLOADDbg.fd:UEFI:Lzma"


Stitch Slim Bootloader
----------------------

python Platform/ApollolakeBoardPkg/Script/StitchLoader.py -i <BIOS_IMAGE_NAME> -s Outputs/apl/Stitch_Components.zip -o <SBL_IFWI_IMAGE_NAME>

Example:

python Platform/ApollolakeBoardPkg/Script/StitchLoader.py -i 35690000I60X402.bin -s Outputs/apl/Stitch_Components.zip -o 35690000S60X402.bin


Build UEFIPayload
-----------------


git clone --recurse-submodules https://github.com/tianocore/edk2.git edk2

git submodule update ¡Vrecursive

edksetup.bat

build -a X64 -b DEBUG -t VS2017 -D BOOTLOADER=SBL -p UefiPayloadPkg\UefiPayloadPkg.dsc 


Build Slim Bootloader with UEFIPayload
--------------------------------------

copy $(BUILD_DIR)\UEFIPAYLOAD.fd into $(SOURCE)\PayloadPkg\PayloadBins\UEFIPAYLOADRel.fd

Example:

copy edk2\Build\UefiPayloadPkgX64\DEBUG_VS2015x86\FV\UEFIPAYLOAD.fd sbl\PayloadPkg\PayloadBins\UEFIPAYLOAD.fd

Update .dlt file
----------------
Insert the following line to file sbl\Platform\ApollolakeBoardPkg\CfgData\CfgData_Int_LeafHill.dlt:

GEN_CFG_DATA.PayloadId                   | 'UEFI'

  Repeat *** Build Slim Bootloader *** and *** Stitch Slim Bootloader ***



Slim Bootloader
================

**Welcome to the Slim Bootloader project!**

Slim Bootloader is an open-source boot firmware solution, built from the
ground up to be secure, lightweight, and highly optimized while leveraging
robust tools and libraries from the [EDK II](https://www.tianocore.org/edk2/)
framework.

What is a Bootloader?
---------------------
Just like a typical [BIOS](https://en.wikipedia.org/wiki/BIOS), Slim Bootloader
is the piece of software responsible for initializing the core hardware
components of the system when it is powered on, followed by the loading and
launching of the desired operating system.

Slim Bootloader offers the flexibility for OEMs, device manufacturers, and hobbyists
to isolate, configure, and optimize for the the specific requirements of the system
thereby achieving unparalleled boot performance and minimizing firmware footprint.

Supported Platforms
-------------------
Please visit [Supported Hardware](https://slimbootloader.github.io/supported-hardware/index.html) page for a list of platforms supported by Slim Bootloader.

Getting Started
---------------
Documentation for compiling, using, and extending Slim Bootloader can be found
[here](https://slimbootloader.github.io/).

Mailing List
--------------
You can subscribe to our mailing list for questions or share your learnings:
https://lists.01.org/postorius/lists/sbl-devel.lists.01.org/

Archives: Â https://lists.01.org/hyperkitty/list/sbl-devel@lists.01.org/

License
-------
Slim Bootloader is released under the terms of the BSD-2-Clause Plus Patent License.
Please see the `LICENSE` file for the full terms of the license.
