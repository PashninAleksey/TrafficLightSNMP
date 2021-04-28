/*
 * flash_write.c
 *
 *  Created on: 29 ��� 2020 �.
 *      Author: Daniil
 */
#include "flash_write.h"

HAL_StatusTypeDef flash_ok = HAL_ERROR;

uint32_t tmp_Port, tmp_T, tmp_ip1, tmp_ip2, tmp_ip3, tmp_ip4, tmp_mac1,
		tmp_mac2, tmp_mac3, tmp_mac4, tmp_mac5, tmp_mac6, tmp_mask1, tmp_mask2,
		tmp_mask3, tmp_mask4, tmp_gtw1, tmp_gtw2, tmp_gtw3, tmp_gtw4;

void read_flash_data() {

	tmp_ip1 = (*(__IO uint32_t*) ip_SET_FLASH_1);
	tmp_ip2 = (*(__IO uint32_t*) ip_SET_FLASH_2);
	tmp_ip3 = (*(__IO uint32_t*) ip_SET_FLASH_3);
	tmp_ip4 = (*(__IO uint32_t*) ip_SET_FLASH_4);

	tmp_mac1 = (*(__IO uint32_t*) MAC_SET_FLASH_1);
	tmp_mac2 = (*(__IO uint32_t*) MAC_SET_FLASH_2);
	tmp_mac3 = (*(__IO uint32_t*) MAC_SET_FLASH_3);
	tmp_mac4 = (*(__IO uint32_t*) MAC_SET_FLASH_4);
	tmp_mac5 = (*(__IO uint32_t*) MAC_SET_FLASH_5);
	tmp_mac6 = (*(__IO uint32_t*) MAC_SET_FLASH_6);

	tmp_mask1 = (*(__IO uint32_t*) mask_SET_FLASH_1);
	tmp_mask2 = (*(__IO uint32_t*) mask_SET_FLASH_2);
	tmp_mask3 = (*(__IO uint32_t*) mask_SET_FLASH_3);
	tmp_mask4 = (*(__IO uint32_t*) mask_SET_FLASH_4);

	tmp_gtw1 = (*(__IO uint32_t*) gtw_SET_FLASH_1);
	tmp_gtw2 = (*(__IO uint32_t*) gtw_SET_FLASH_2);
	tmp_gtw3 = (*(__IO uint32_t*) gtw_SET_FLASH_3);
	tmp_gtw4 = (*(__IO uint32_t*) gtw_SET_FLASH_4);

}

void Set_MASK_ADDR(uint8_t mask1_int, uint8_t mask2_int, uint8_t mask3_int,
		uint8_t mask4_int) {
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

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_1, tmp_ip1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_2, tmp_ip2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_3, tmp_ip3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_4, tmp_ip4);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_1,
				mask1_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_2,
				mask2_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_3,
				mask3_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_4,
				mask4_int);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_1,
				tmp_gtw1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_2,
				tmp_gtw2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_3,
				tmp_gtw3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_4,
				tmp_gtw4);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_1,
				tmp_mac1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_2,
				tmp_mac2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_3,
				tmp_mac3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_4,
				tmp_mac4);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_5,
				tmp_mac5);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_6,
				tmp_mac6);
	}
}
void Set_GTW_ADDR(uint8_t gtw1_int, uint8_t gtw2_int, uint8_t gtw3_int,
		uint8_t gtw4_int) {
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

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_1, tmp_ip1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_2, tmp_ip2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_3, tmp_ip3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_4, tmp_ip4);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_1,
				tmp_mask1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_2,
				tmp_mask2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_3,
				tmp_mask3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_4,
				tmp_mask4);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_1,
				gtw1_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_2,
				gtw2_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_3,
				gtw3_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_4,
				gtw4_int);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_1,
				tmp_mac1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_2,
				tmp_mac2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_3,
				tmp_mac3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_4,
				tmp_mac4);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_5,
				tmp_mac5);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_6,
				tmp_mac6);
	}

}
void Set_IP_ADDR(uint8_t ip1_int, uint8_t ip2_int, uint8_t ip3_int,
		uint8_t ip4_int) {
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
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_1, ip1_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_2, ip2_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_3, ip3_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_4, ip4_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_1,
				tmp_mac1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_2,
				tmp_mac2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_3,
				tmp_mac3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_4,
				tmp_mac4);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_5,
				tmp_mac5);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_6,
				tmp_mac6);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_1,
				tmp_mask1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_2,
				tmp_mask2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_3,
				tmp_mask3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_4,
				tmp_mask4);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_1,
				tmp_gtw1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_2,
				tmp_gtw2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_3,
				tmp_gtw3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_4,
				tmp_gtw4);
	}

}
void Set_MAC_ADDR(uint8_t mac1_int, uint8_t mac2_int, uint8_t mac3_int,
		uint8_t mac4_int, uint8_t mac5_int, uint8_t mac6_int) {

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

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_1, tmp_ip1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_2, tmp_ip2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_3, tmp_ip3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, ip_SET_FLASH_4, tmp_ip4);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_1,
				tmp_mask1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_2,
				tmp_mask2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_3,
				tmp_mask3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, mask_SET_FLASH_4,
				tmp_mask4);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_1,
				tmp_gtw1);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_2,
				tmp_gtw2);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_3,
				tmp_gtw3);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, gtw_SET_FLASH_4,
				tmp_gtw4);
	}

	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_1,
				mac1_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_2,
				mac2_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_3,
				mac3_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_4,
				mac4_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_5,
				mac5_int);
	}
	flash_ok = HAL_ERROR;
	while (flash_ok != HAL_OK) {
		flash_ok = HAL_FLASH_Program(TYPEPROGRAM_WORD, MAC_SET_FLASH_6,
				mac6_int);
	}
}
