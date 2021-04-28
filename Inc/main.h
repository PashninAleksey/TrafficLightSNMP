/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern const struct snmp_mib pashnin_mib;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
typedef struct {
	float T;
} data;
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define USER_FLASH_FIRST_PAGE_ADDRESS 0x08020000 /* Only as example see comment */
#define USER_FLASH_LAST_PAGE_ADDRESS  0x080E0000
#define USER_FLASH_END_ADDRESS        0x080FFFFF

#define  ip_SET_FLASH_1 		 0x08080000
#define  ip_SET_FLASH_2 		 0x08080004
#define  ip_SET_FLASH_3 		 0x08080008
#define  ip_SET_FLASH_4 		 0x0808000C

#define  mask_SET_FLASH_1 		 0x08080030
#define  mask_SET_FLASH_2 		 0x08080034
#define  mask_SET_FLASH_3 		 0x08080038
#define  mask_SET_FLASH_4 		 0x0808003C

#define  gtw_SET_FLASH_1 		 0x08080040
#define  gtw_SET_FLASH_2 		 0x08080044
#define  gtw_SET_FLASH_3 		 0x08080048
#define  gtw_SET_FLASH_4 		 0x0808004C

#define  MAC_SET_FLASH_1 		 0x08080010
#define  MAC_SET_FLASH_2 		 0x08080014
#define  MAC_SET_FLASH_3 		 0x08080018
#define  MAC_SET_FLASH_4 		 0x0808001C
#define  MAC_SET_FLASH_5 		 0x08080020
#define  MAC_SET_FLASH_6 		 0x08080024

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
