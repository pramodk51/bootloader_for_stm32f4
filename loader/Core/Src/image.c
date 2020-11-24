/*
 * image.c
 *
 *  Created on: Sep 29, 2020
 *      Author: pramo
 */


#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "image.h"
#include "crc.h"

const image_hdr_t *imageGetHeader(image_slot_t slot)
{
	 const image_hdr_t *hdr = NULL;

	 switch (slot)
	 {
		 case IMAGE_SLOT_1:
		 	 hdr = (const image_hdr_t *)(FLASH_AREA_IMAGE_1);
			 break;
		 case IMAGE_SLOT_2:
			 hdr = (const image_hdr_t *)(FLASH_AREA_IMAGE_2);
			 break;
		 default:
			 break;
	 }

	 if (hdr && hdr->image_magic == IMAGE_MAGIC)
	 {
		 return hdr;
	 }
	 else
	 {
		 printf("!!!!!!!!!!!!!!!!!! No valid header found in slot %d !!!!!!!!!!!!!!!!!!!\r\n", slot);
		 return NULL;
	 }

}


int imageValidate(image_slot_t slot, const image_hdr_t *hdr)
{
	void *addr = NULL;

	if(slot == IMAGE_SLOT_1)
	{
		addr = (uint32_t *)(FLASH_AREA_IMAGE_1);
	}
	else
	{
		addr = (uint32_t *)(FLASH_AREA_IMAGE_2);
	}

	addr += sizeof(image_hdr_t);
	uint32_t len = hdr->image_size;
	uint32_t a = crc32(addr, len);
	uint32_t b = hdr->crc;
	if (a == b)
	{
	    return 0;
	}
	else
	{
	    printf("CRC Mismatch: %lx vs %lx\n", a, b);
	    return -1;
	}

}



void imageStart(const image_hdr_t *hdr)
{


	printf("Booting from image slot %d\r\n", (hdr->image_version%2)?1:2);
	void (*app_reset_handler)(void);


	uint32_t msp_value = 0;
	uint32_t reset_handler_address  = 0 ;

    //get the stack pointer


	//odd image version in slot1 and even image version in slot2
	if(hdr->image_version%2)
	{
		msp_value = *(volatile uint32_t *)(FLASH_AREA_IMAGE_1 + IMAGE_OFFSET);
	}
	else
	{
		msp_value = *(volatile uint32_t *)(FLASH_AREA_IMAGE_2 + IMAGE_OFFSET);
	}

	printf("msp_value %ld\r\n",msp_value);
	__set_MSP(msp_value);



	//get the reset handler address
	if(hdr->image_version%2)
	{
		reset_handler_address  = *(volatile uint32_t *)(FLASH_AREA_IMAGE_1 + IMAGE_OFFSET + 4);
	}
	else
	{
		reset_handler_address = *(volatile uint32_t *)(FLASH_AREA_IMAGE_2 + IMAGE_OFFSET + 4);
	}


	app_reset_handler = (void *)reset_handler_address;


	//disable each each peripheral to its reset state (to_test)
	//also to disable CPU and peripheral interrupts
	//HAL_DeInit();
	//HAL_CRC_MspDeInit();
	//HAL_UART_MspDeInit();
	//__HAL_RCC_SYSCFG_CLK_DISABLE();
	//__HAL_RCC_PWR_CLK_DISABLE();
	//__diable_irq();

	//jump to reset handler of the image
	app_reset_handler();

}




