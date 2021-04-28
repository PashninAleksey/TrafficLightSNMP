/*
 * flash_write.h
 *
 *  Created on: 29 ��� 2020 �.
 *      Author: Daniil
 */

#ifndef FLASH_WRITE_H_
#define FLASH_WRITE_H_
#include "main.h"

void Set_MAC_ADDR(uint8_t mac1_int, uint8_t mac2_int, uint8_t mac3_int,
		uint8_t mac4_int, uint8_t mac5_int, uint8_t mac6_int);
void Set_IP_ADDR(uint8_t ip1_int, uint8_t ip2_int, uint8_t ip3_int,
		uint8_t ip4_int);
void Set_MASK_ADDR(uint8_t mask1_int, uint8_t mask2_int, uint8_t mask3_int,
		uint8_t mask4_int);
void Set_GTW_ADDR(uint8_t gtw1_int, uint8_t gtw2_int, uint8_t gtw3_int,
		uint8_t gtw4_int);
#endif /* FLASH_WRITE_H_ */
