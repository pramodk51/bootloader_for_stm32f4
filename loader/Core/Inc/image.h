/*
 * image.h
 *
 *  Created on: Sep 29, 2020
 *      Author: pramo
 */

#ifndef INC_IMAGE_H_
#define INC_IMAGE_H_



#define IMAGE_MAGIC 0xABCD

#define FLASH_AREA_IMAGE_1   0x08020000        //sector 5 start
#define FLASH_AREA_IMAGE_2   0x080a0000        //sector 9 start

#define IMAGE_OFFSET        0x400             //because vector table offset should be a multiple of 0x200


typedef struct __attribute__((packed)){
    uint16_t image_magic;
    uint16_t image_version;
    uint32_t image_size;
    uint32_t crc;

} image_hdr_t;


typedef enum {
	IMAGE_SLOT_1 = 1,
	IMAGE_SLOT_2 = 2

} image_slot_t;


const image_hdr_t *imageGetHeader(image_slot_t slot);

int imageValidate(image_slot_t slot, const image_hdr_t *hdr);

void imageStart(const image_hdr_t *hdr);


#endif /* INC_IMAGE_H_ */
