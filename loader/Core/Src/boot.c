/*
 * boot.c
 *
 *  Created on: Sep 29, 2020
 *      Author: pramo
 */


#include <stdio.h>

#include "stm32f4xx_hal.h"

#include "image.h"
#include "boot.h"


void loadImage(void)
{
	const image_hdr_t *hdr1 = NULL;
	const image_hdr_t *hdr2 = NULL;

	int valid1 = -1;
	int valid2 = -1;

	hdr1 = imageGetHeader(IMAGE_SLOT_1);
	hdr2 = imageGetHeader(IMAGE_SLOT_2);

	//check if image_magic not matching
	if(hdr1 == NULL && hdr2 == NULL)
	{
		printf("No valid image header found....\r\n");

		HAL_Delay(50000);
		printf("Restarting the system....\r\n");
		NVIC_SystemReset();
		while(1);
	}


    //get the validity(CRC verification) of each non-null image
    if(hdr1 != NULL)
    {
    	valid1 = imageValidate(IMAGE_SLOT_1, hdr1);
    }

    if(hdr2 != NULL)
    {
    	valid2 = imageValidate(IMAGE_SLOT_2, hdr2);
    }


    //if both failed CRC verification
	if(valid1 != 0 && valid2 != 0)
	{
		printf("No valid image found....\r\n");

		HAL_Delay(50000);
		printf("Restarting the system....\r\n");
		NVIC_SystemReset();
		while(1);
	}



	//print the App version for each image
	if(valid1 == 0)
	{
		  printf("App found with version - %d \n", hdr1->image_version);
	}

	if(valid2 == 0)
	{
		  printf("App found with version - %d \n", hdr2->image_version);
	}


	//if image version at slot 1 is greater and image is valid, boot from it
    if((hdr1->image_version > hdr2->image_version) && valid1 == 0 )
    {
    	printf("\r\n\r\n\r\n!!!!!!!!!!!!!! booting image from slot 1 !!!!!!!!!!!!!!!\r\n");
    	printf("Image Version %d\r\n",hdr1->image_version);
    	imageStart(hdr1);
    }
    //image version at slot 2 is greater
    else if((hdr1->image_version < hdr2->image_version) && valid2 == 0)
    {
    	printf("\r\n\r\n\r\n!!!!!!!!!!!!!! booting image from slot 2 !!!!!!!!!!!!!!!\r\n");
    	printf("Image Version %d\r\n",hdr2->image_version);
    	imageStart(hdr2);
    }
    else //in any other case, boot from whichever is valid
    {
        if(valid1 == 0)
        {
        	printf("\r\n\r\n\r\n!!!!!!!!!!!!!! booting image from slot 1 !!!!!!!!!!!!!!!\r\n");
        	printf("Image Version %d\r\n",hdr1->image_version);
        	imageStart(hdr1);
        }
        else
        {
        	printf("\r\n\r\n\r\n!!!!!!!!!!!!!! booting image from slot 2 !!!!!!!!!!!!!!!\r\n");
        	printf("Image Version %d\r\n",hdr2->image_version);
        	imageStart(hdr2);
        }
    }

}
