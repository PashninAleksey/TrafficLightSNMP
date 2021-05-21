#include "net_param_init.h"
#include "lwip.h"

extern uint8_t MACAddr[6];
extern uint8_t IP_ADDRESS[4];
extern uint8_t NETMASK_ADDRESS[4];
extern uint8_t GATEWAY_ADDRESS[4];

extern uint32_t MAC_FLASH_ADDRESS[6];
extern uint32_t IP_FLASH_ADDRESS[4];
extern uint32_t GTW_FLASH_ADDRESS[4];
extern uint32_t MASK_FLASH_ADDRESS[4];
//variables for displaying installed network settings

void Net_Param_init() {
	if ((*(__IO uint32_t*) MAC_FLASH_ADDRESS[0]) != 0xFFFFFFFF) {
		for (int i = 0; i < 6; i++) {
			MACAddr[i] = *(__IO uint32_t*) MAC_FLASH_ADDRESS[i];
		}
	} else {
		MACAddr[0] = 0x0;
		MACAddr[1] = 0x13;
		MACAddr[2] = 0x37;
		MACAddr[3] = 0x01;
		MACAddr[4] = 0x23;
		MACAddr[5] = 0x55;
		Set_MAC_ADDR(MACAddr);
	}

	if ((*(__IO uint32_t*) IP_FLASH_ADDRESS[0]) != 0xFFFFFFFF) {
		for (int i = 0; i < 4; i++) {
			IP_ADDRESS[i] = *(__IO uint32_t*) IP_FLASH_ADDRESS[i];
		}

	} else {
		IP_ADDRESS[0] = 192;
		IP_ADDRESS[1] = 168;
		IP_ADDRESS[2] = 0;
		IP_ADDRESS[3] = 10;
		Set_IP_ADDR(IP_ADDRESS);
	}

	if ((*(__IO uint32_t*) MASK_FLASH_ADDRESS[0]) != 0xFFFFFFFF) {
		for (int i = 0; i < 4; i++) {
			NETMASK_ADDRESS[i] = *(__IO uint32_t*) MASK_FLASH_ADDRESS[i];
		}

	} else {
		NETMASK_ADDRESS[0] = 255;
		NETMASK_ADDRESS[1] = 255;
		NETMASK_ADDRESS[2] = 255;
		NETMASK_ADDRESS[3] = 0;
		Set_MASK_ADDR(NETMASK_ADDRESS);
	}

	if ((*(__IO uint32_t*) GTW_FLASH_ADDRESS[0]) != 0xFFFFFFFF) {
		for (int i = 0; i < 4; i++) {
			GATEWAY_ADDRESS[i] = *(__IO uint32_t*) GTW_FLASH_ADDRESS[i];
		}

	} else {
		GATEWAY_ADDRESS[0] = 192;
		GATEWAY_ADDRESS[1] = 168;
		GATEWAY_ADDRESS[2] = 0;
		GATEWAY_ADDRESS[3] = 1;
		Set_GTW_ADDR(GATEWAY_ADDRESS);
	}

}
