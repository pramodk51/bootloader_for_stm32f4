/*
 * crc.h
 *
 *  Created on: Sep 29, 2020
 *      Author: pramo
 */

#ifndef INC_CRC_H_
#define INC_CRC_H_

#include <stdint.h>
#include <stddef.h>

uint32_t crc32(const void *buf, uint32_t size);

#endif /* INC_CRC_H_ */
