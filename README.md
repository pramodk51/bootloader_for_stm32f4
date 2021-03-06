# bootloader_for_stm32f4

A bootloader for stm32f4. It selects the valid and latest(version) application image and boots from it after basic verification. It rollbacks and boots from previous image if the latest image is invalid. Can be used to create an OTA update solution.
This Project is based on STM32F429ZI Nucleo board.


/loader contains bootloader project

/app1   contains a simple application project 

/app2


# Flash memory map.

![GitHub Logo](/images/memory_map.png)


Bootloader runs from Flash starting at 0x8000000. (Default starting point for stm32) 

Application images are placed at 2 different slots. Specified in Linker script of each app images.
FLASH_AREA_IMAGE_1   0x08020000
FLASH_AREA_IMAGE_2   0x080A0000

For simplicity, image version increases in integral order, e.g. 1, 2 .. for every new image.
Odd version images are placed in slot 1. Even version images are placed in slot 2. 


# Image header content.
Linker script is modified to store the image header at the start of bin file. Actual Application data starts from  after a certain offset. A header section in linker file whose size is 1K.

![GitHub Logo](/images/header_format.png)

                                                                                                                                                                                                                                                                                                                       
Linker file contains additional HEADER section to store headers for images.

![GitHub Logo](/images/image_linker.png)

# Header MAGIC 
A pre-known value (here 0xABCD) to add extra validation to image.

# Vector-Table relocation.
Vector table for image 1 starts from 0x08020400 and for image 2 form 0x080A0400. Vector table location is the start of FLASH section for STM32.

Minimal Nos. of Vector elements in startup file is (90 external + 16 system ). This comes as 106*4 bytes. This why, in system_stm32xx.c, it is mentioned to use multiple of 0x200 as offset. (0x200 is the power of two next to 107x4 bytes). 

![GitHub Logo](/images/image_table_relocation.png)

# CRC generation
Use crc.py file to append crc and image size in final bin file.

$ python crc.py app1.bin 



To add:
Image signing instead of CRC.

Storing boot counter and image boot status to avoid verification and app selection every time.




Reference:
https://interrupt.memfault.com/blog/device-firmware-update-cookbook
https://microcontrollerslab.com/what-is-interrupt-vector-table/
