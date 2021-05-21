#include "flash_write.h"

//addresses for network parameters, temperatures, and ports
uint32_t IP_FLASH_ADDRESS[4] =
		{ 0x08080000, 0x08080004, 0x08080008, 0x0808000C };
uint32_t MASK_FLASH_ADDRESS[4] = { 0x08080030, 0x08080034, 0x08080038,
		0x0808003C };
uint32_t GTW_FLASH_ADDRESS[4] =
		{ 0x08080040, 0x08080044, 0x08080048, 0x0808004C };
uint32_t MAC_FLASH_ADDRESS[6] = { 0x08080010, 0x08080014, 0x08080018,
		0x0808001C, 0x08080020, 0x08080024 };

//arrays for temporary storage of data during recording
uint32_t tmp_ip[4];
uint32_t tmp_gtw[4];
uint32_t tmp_msk[4];
uint32_t tmp_mac[6];

HAL_StatusTypeDef flash_ok = HAL_ERROR;

void read_flash_data() {



	for (int i = 0; i < 4; i++) {
		tmp_ip[i] = *(__IO uint32_t*) IP_FLASH_ADDRESS[i];
	}
	for (int i = 0; i < 4; i++) {
		tmp_gtw[i] = *(__IO uint32_t*) GTW_FLASH_ADDRESS[i];
	}

	for (int i = 0; i < 4; i++) {
		tmp_msk[i] = *(__IO uint32_t*) MASK_FLASH_ADDRESS[i];
	}

	for (int i = 0; i < 6; i++) {
		tmp_mac[i] = *(__IO uint32_t*) MAC_FLASH_ADDRESS[i];
	}
}

//write to memory subnet mask
void Set_MASK_ADDR(uint8_t *mask) {
	read_flash_data();
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Unlock();
	}

	FLASH_Erase_Sector(FLASH_SECTOR_8, VOLTAGE_RANGE_3);

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Lock();
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Unlock();
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, IP_FLASH_ADDRESS[i],
					tmp_ip[i]);
		}
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, GTW_FLASH_ADDRESS[i],
					tmp_gtw[i]);
		}
	}

	for (int i = 0; i < 6; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_FLASH_ADDRESS[i],
					tmp_mac[i]);
		}
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD,
					MASK_FLASH_ADDRESS[i], mask[i]);
		}
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Lock();
	}

}
//write to memory gateway
void Set_GTW_ADDR(uint8_t *gtw) {
	read_flash_data();
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Unlock();
	}

	FLASH_Erase_Sector(FLASH_SECTOR_8, VOLTAGE_RANGE_3);

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Lock();
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Unlock();
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, IP_FLASH_ADDRESS[i],
					tmp_ip[i]);
		}
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD,
					MASK_FLASH_ADDRESS[i], tmp_msk[i]);
		}
	}

	for (int i = 0; i < 6; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_FLASH_ADDRESS[i],
					tmp_mac[i]);
		}
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, GTW_FLASH_ADDRESS[i],
					gtw[i]);
		}
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Lock();
	}

}
//write to memory ip
void Set_IP_ADDR(uint8_t *ip) {
	read_flash_data();
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Unlock();
	}

	FLASH_Erase_Sector(FLASH_SECTOR_8, VOLTAGE_RANGE_3);

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Lock();
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Unlock();
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, GTW_FLASH_ADDRESS[i],
					tmp_gtw[i]);
		}
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD,
					MASK_FLASH_ADDRESS[i], tmp_msk[i]);
		}
	}

	for (int i = 0; i < 6; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_FLASH_ADDRESS[i],
					tmp_mac[i]);
		}
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			int b = ip[i];
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, IP_FLASH_ADDRESS[i],
					ip[i]);
		}
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Lock();
	}

}
//write to memory MAC address
void Set_MAC_ADDR(uint8_t *mac) {

	read_flash_data();
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Unlock();
	}

	FLASH_Erase_Sector(FLASH_SECTOR_8, VOLTAGE_RANGE_3);

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Lock();
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Unlock();
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, GTW_FLASH_ADDRESS[i],
					tmp_gtw[i]);
		}
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD,
					MASK_FLASH_ADDRESS[i], tmp_msk[i]);
		}
	}

	for (int i = 0; i < 4; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, IP_FLASH_ADDRESS[i],
					tmp_ip[i]);
		}
	}

	for (int i = 0; i < 6; i++) {
		flash_ok = HAL_ERROR;
		while (flash_ok != HAL_OK) {
			flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_FLASH_ADDRESS[i],
					mac[i]);
		}
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Lock();
	}

}

