/*
 * net_param_init.c
 *
 *  Created on: 18 июн. 2020 г.
 *      Author: Daniil
 */
#include "net_param_init.h"
#include "lwip.h"

extern uint8_t MACAddr[6];
extern uint8_t IP_ADDRESS[4];
extern uint8_t NETMASK_ADDRESS[4];
extern uint8_t GATEWAY_ADDRESS[4];

//variables for displaying installed network settings

void Net_Param_init() {
	if ((*(__IO uint32_t*) MAC_SET_FLASH_1) != 0xFFFFFFFF) {
		MACAddr[0] = *(__IO uint32_t*) MAC_SET_FLASH_1;
		MACAddr[1] = *(__IO uint32_t*) MAC_SET_FLASH_2;
		MACAddr[2] = *(__IO uint32_t*) MAC_SET_FLASH_3;
		MACAddr[3] = *(__IO uint32_t*) MAC_SET_FLASH_4;
		MACAddr[4] = *(__IO uint32_t*) MAC_SET_FLASH_5;
		MACAddr[5] = *(__IO uint32_t*) MAC_SET_FLASH_6;
	} else {
		MACAddr[0] = 0x0;
		MACAddr[1] = 0x13;
		MACAddr[2] = 0x37;
		MACAddr[3] = 0x01;
		MACAddr[4] = 0x23;
		MACAddr[5] = 0x55;
		Set_MAC_ADDR(MACAddr[0], MACAddr[1], MACAddr[2], MACAddr[3], MACAddr[4],
				MACAddr[5]);
	}

	if ((*(__IO uint32_t*) ip_SET_FLASH_1) != 0xFFFFFFFF) {
		IP_ADDRESS[0] = *(__IO uint32_t*) ip_SET_FLASH_1;
		IP_ADDRESS[1] = *(__IO uint32_t*) ip_SET_FLASH_2;
		IP_ADDRESS[2] = *(__IO uint32_t*) ip_SET_FLASH_3;
		IP_ADDRESS[3] = *(__IO uint32_t*) ip_SET_FLASH_4;

	} else {
		IP_ADDRESS[0] = 192;
		IP_ADDRESS[1] = 168;
		IP_ADDRESS[2] = 0;
		IP_ADDRESS[3] = 10;
		Set_IP_ADDR(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
	}

	if ((*(__IO uint32_t*) mask_SET_FLASH_1) != 0xFFFFFFFF) {
		NETMASK_ADDRESS[0] = *(__IO uint32_t*) mask_SET_FLASH_1;
		NETMASK_ADDRESS[1] = *(__IO uint32_t*) mask_SET_FLASH_2;
		NETMASK_ADDRESS[2] = *(__IO uint32_t*) mask_SET_FLASH_3;
		NETMASK_ADDRESS[3] = *(__IO uint32_t*) mask_SET_FLASH_4;

	} else {
		NETMASK_ADDRESS[0] = 255;
		NETMASK_ADDRESS[1] = 255;
		NETMASK_ADDRESS[2] = 255;
		NETMASK_ADDRESS[3] = 0;
		Set_MASK_ADDR(NETMASK_ADDRESS[0], NETMASK_ADDRESS[1],
				NETMASK_ADDRESS[2], NETMASK_ADDRESS[3]);
	}

	if ((*(__IO uint32_t*) gtw_SET_FLASH_1) != 0xFFFFFFFF) {
		GATEWAY_ADDRESS[0] = *(__IO uint32_t*) gtw_SET_FLASH_1;
		GATEWAY_ADDRESS[1] = *(__IO uint32_t*) gtw_SET_FLASH_2;
		GATEWAY_ADDRESS[2] = *(__IO uint32_t*) gtw_SET_FLASH_3;
		GATEWAY_ADDRESS[3] = *(__IO uint32_t*) gtw_SET_FLASH_4;

	} else {
		GATEWAY_ADDRESS[0] = 192;
		GATEWAY_ADDRESS[1] = 168;
		GATEWAY_ADDRESS[2] = 0;
		GATEWAY_ADDRESS[3] = 1;
		Set_GTW_ADDR(GATEWAY_ADDRESS[0], GATEWAY_ADDRESS[1], GATEWAY_ADDRESS[2],
				GATEWAY_ADDRESS[3]);
	}

}
