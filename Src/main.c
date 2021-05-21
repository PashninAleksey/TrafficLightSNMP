/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lwip/apps/httpd.h"
#include "stdint.h"
#include "string.h"
#include "my_mibs.h"
#include "ssi.h"
#include "cgi.h"
#include "math.h"
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "flash_if.h"
#include "flash_write.h"
#include "net_param_init.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
osMailQId TemperatureHandle;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef struct struct_sock_t {

	struct netconn *conn;
} struct_sock;
struct_sock sock01;
uint16_t tcp_port = 502;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* initialization SSI and CGI */
extern uint16_t SSI_Handler(int iIndex, char *pcInsert, int iInsertLen);
extern char const** TAGS;

extern const tCGI CLR_All_CGI;
extern const tCGI CLR1_CGI;
extern const tCGI CLR2_CGI;
extern const tCGI IP_CGI;
extern const tCGI MAC_CGI;
extern const tCGI MSK_CGI;
extern const tCGI GTW_CGI;

extern tCGI CGI_TAB[7];

extern uint8_t Red1_str[3];
extern uint8_t Red2_str[3];
extern uint8_t Green1_str[3];
extern uint8_t Green2_str[3];
extern uint8_t Blue1_str[3];
extern uint8_t Blue2_str[3];
extern uint8_t White1_str[3];
extern uint8_t White2_str[3];

extern const struct snmp_mib mib2;
static const struct snmp_mib *my_snmp_mibs[] = { &mib2, &pashnin_mib };

u8_t * syscontact_str = (u8_t*) "Si Tech";
u16_t syscontact_len = sizeof("Si Tech");
u8_t * syslocation_str = (u8_t*) "SNMP traffic light";
u16_t syslocation_len = sizeof("SNMP traffic light");
u8_t * sysname_str = (u8_t*) "Traffic light";
u16_t sysname_len = sizeof("Traffic light");
u16_t bufsize = 256;
const u8_t * sysdescr = (u8_t*) "SNMP traffic light made in Si Tech ";
const u16_t sysdescr_len = sizeof("SNMP traffic light made in Si Tech ");
//temperature for SSI and SNMP
float T_avg = 0;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim4;

osThreadId HTTPserverHandle;
osThreadId temperatureHandle;
osThreadId modBusHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM4_Init(void);
static void MX_IWDG_Init(void);
void HTTPinit(void const * argument);
void temp_measur(void const * argument);
void modBusInit(void const * argument);

/* USER CODE BEGIN PFP */
void generate_zero(uint8_t *buf, uint8_t size, uint8_t len) {

	for (int j = 0; j < len; j++) {
		buf[size - 1 - j] = buf[len - 1 - j];
	}
	for (int i = 0; i < size - len; i++) {
		buf[i] = '0';
	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	__enable_irq();
	/* traffic light start data initialization */
	ColorRGBW[0] = 0;
	ColorRGBW[1] = 0;
	ColorRGBW[2] = 0;
	ColorRGBW[3] = 0;
	ColorRGBW[4] = 0;
	ColorRGBW[5] = 0;
	ColorRGBW[6] = 0;
	ColorRGBW[7] = 0;

	for (int i = 0; i < 3; i++) {
		Red1_str[i] = '0';
		Red2_str[i] = '0';
		Green1_str[i] = '0';
		Green2_str[i] = '0';
		Blue1_str[i] = '0';
		Blue2_str[i] = '0';
		White1_str[i] = '0';
		White2_str[i] = '0';
	}

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	osMailQDef(Temperature, 1, data);
	TemperatureHandle = osMailCreate(osMailQ(Temperature), NULL);
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	//Initialize net parameters
	Net_Param_init();
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_LWIP_Init();
	MX_ADC1_Init();
	MX_TIM1_Init();
	MX_TIM4_Init();
	MX_IWDG_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of HTTPserver */
	osThreadDef(HTTPserver, HTTPinit, osPriorityNormal, 0, 2560);
	HTTPserverHandle = osThreadCreate(osThread(HTTPserver), NULL);

	/* definition and creation of temperature */
	osThreadDef(temperature, temp_measur, osPriorityNormal, 0, 1280);
	temperatureHandle = osThreadCreate(osThread(temperature), NULL);

	/* definition and creation of modBus */
	osThreadDef(modBus, modBusInit, osPriorityNormal, 0, 1280);
	modBusHandle = osThreadCreate(osThread(modBus), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI
			| RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void) {

	/* USER CODE BEGIN ADC1_Init 0 */

	/* USER CODE END ADC1_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		Error_Handler();
	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC1_Init 2 */

	/* USER CODE END ADC1_Init 2 */

}

/**
 * @brief IWDG Initialization Function
 * @param None
 * @retval None
 */
static void MX_IWDG_Init(void) {

	/* USER CODE BEGIN IWDG_Init 0 */

	/* USER CODE END IWDG_Init 0 */

	/* USER CODE BEGIN IWDG_Init 1 */

	/* USER CODE END IWDG_Init 1 */
	hiwdg.Instance = IWDG;
	hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
	hiwdg.Init.Reload = 4095;
	if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN IWDG_Init 2 */

	/* USER CODE END IWDG_Init 2 */

}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void) {

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = { 0 };

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 200;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 255;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4)
			!= HAL_OK) {
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */
	HAL_TIM_MspPostInit(&htim1);

}

/**
 * @brief TIM4 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM4_Init(void) {

	/* USER CODE BEGIN TIM4_Init 0 */

	/* USER CODE END TIM4_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 200;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 255;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim4) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM4_Init 2 */

	/* USER CODE END TIM4_Init 2 */
	HAL_TIM_MspPostInit(&htim4);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE()
	;
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	__HAL_RCC_GPIOE_CLK_ENABLE()
	;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;
	__HAL_RCC_GPIOD_CLK_ENABLE()
	;

}

/* USER CODE BEGIN 4 */
static void tcp_thread(void *arg) {

	err_t err, recv_err;
	struct netconn *conn;
	struct netbuf *inbuf;
	struct netconn *newconn;
	struct_sock *arg_sock;
	arg_sock = (struct_sock*) arg;
	conn = arg_sock->conn;
	u16_t buflen, buflen_answer;
	uint8_t* buf;
	uint8_t data[100] = { '\0' };

	for (;;) {

		err = netconn_accept(conn, &newconn);
		if (err == ERR_OK) {
			for (;;) {

				recv_err = netconn_recv(newconn, &inbuf);
				if (recv_err == ERR_OK) {
					netbuf_data(inbuf, (void**) &buf, &buflen);
					if ((buf[0] == 0x0D) || (buf[0] == 0x0A)) {
						netbuf_delete(inbuf);
						continue;
					}

					memset(data, '\0', sizeof(data));
					memcpy(data, buf, buflen);

					//read analog output
					if (data[7] == 0x3) {

						data[8] = data[11] * 2;
						data[5] = data[8] + 3;
						buflen_answer = data[5] + 6;

						if (data[9] == 0 && data[11] == 4) {
							for (int i = 0; i <= 8; i = i + 2) {
								data[9 + i] = 0;
								data[10 + i] = ColorRGBW[i / 2];
							}
						} else if (data[9] == 4 && data[11] == 4) {
							for (int i = 0; i <= 8; i = i + 2) {
								data[9 + i] = 0;
								data[10 + i] = ColorRGBW[4 + i / 2];
							}

						} else if (data[9] == 0 && data[11] == 8) {
							for (int i = 0; i <= 16; i = i + 2) {
								data[9 + i] = 0;
								data[10 + i] = ColorRGBW[i / 2];
							}
						} else {
							//if incorrect parameter
							buflen_answer = 9;
							data[5] = 3;
							data[7] = data[7] | 128;
							data[8] = 3;
						}
					}

					//recording multiple analog outputs
					else if (data[7] == 0x10) {

						buflen_answer = 12;
						data[5] = data[11] * 2 + 2;

						//1 traffic light
						if (data[9] == 0 && data[11] == 4 && data[12] == 8) {

							memset(Red1_str, '\0', sizeof(Red1_str));
							memset(Green1_str, '\0', sizeof(Green1_str));
							memset(Blue1_str, '\0', sizeof(Blue1_str));
							memset(White1_str, '\0', sizeof(White1_str));

							TIM1->CCR4 = data[14];
							TIM1->CCR3 = data[16];
							TIM1->CCR1 = data[18];
							TIM1->CCR2 = data[20];

							ColorRGBW[0] = data[14];
							ColorRGBW[1] = data[16];
							ColorRGBW[2] = data[18];
							ColorRGBW[3] = data[20];

							itoa(data[14], Red1_str, 10);
							itoa(data[16], Green1_str, 10);
							itoa(data[18], Blue1_str, 10);
							itoa(data[20], White1_str, 10);

							generate_zero(Red1_str, sizeof(Red1_str),
									strlen(Red1_str));
							generate_zero(Green1_str, sizeof(Green1_str),
									strlen(Green1_str));
							generate_zero(Blue1_str, sizeof(Blue1_str),
									strlen(Blue1_str));
							generate_zero(White1_str, sizeof(White1_str),
									strlen(White1_str));

						} else if (data[9] == 4 && data[11] == 4
								&& data[12] == 8) {

							//2 traffic light
							memset(Red2_str, '\0', sizeof(Red2_str));
							memset(Green2_str, '\0', sizeof(Green2_str));
							memset(Blue2_str, '\0', sizeof(Blue2_str));
							memset(White2_str, '\0', sizeof(White2_str));

							TIM4->CCR1 = data[14];
							TIM4->CCR2 = data[16];
							TIM4->CCR3 = data[18];
							TIM4->CCR4 = data[20];

							ColorRGBW[4] = data[14];
							ColorRGBW[5] = data[16];
							ColorRGBW[6] = data[18];
							ColorRGBW[7] = data[20];

							itoa(data[14], Red2_str, 10);
							itoa(data[16], Green2_str, 10);
							itoa(data[18], Blue2_str, 10);
							itoa(data[20], White2_str, 10);

							generate_zero(Red2_str, sizeof(Red2_str),
									strlen(Red2_str));
							generate_zero(Green2_str, sizeof(Green2_str),
									strlen(Green2_str));
							generate_zero(Blue2_str, sizeof(Blue2_str),
									strlen(Blue2_str));
							generate_zero(White2_str, sizeof(White2_str),
									strlen(White2_str));

						} else if (data[9] == 0 && data[11] == 8
								&& data[12] == 16) {
							//all color

							memset(Red1_str, '\0', sizeof(Red1_str));
							memset(Green1_str, '\0', sizeof(Green1_str));
							memset(Blue1_str, '\0', sizeof(Blue1_str));
							memset(White1_str, '\0', sizeof(White1_str));

							memset(Red2_str, '\0', sizeof(Red2_str));
							memset(Green2_str, '\0', sizeof(Green2_str));
							memset(Blue2_str, '\0', sizeof(Blue2_str));
							memset(White2_str, '\0', sizeof(White2_str));

							TIM1->CCR4 = data[14];
							TIM1->CCR3 = data[16];
							TIM1->CCR1 = data[18];
							TIM1->CCR2 = data[20];

							TIM4->CCR1 = data[22];
							TIM4->CCR2 = data[24];
							TIM4->CCR3 = data[26];
							TIM4->CCR4 = data[28];

							ColorRGBW[0] = data[14];
							ColorRGBW[1] = data[16];
							ColorRGBW[2] = data[18];
							ColorRGBW[3] = data[20];

							ColorRGBW[4] = data[22];
							ColorRGBW[5] = data[24];
							ColorRGBW[6] = data[26];
							ColorRGBW[7] = data[28];

							itoa(data[14], Red1_str, 10);
							itoa(data[16], Green1_str, 10);
							itoa(data[18], Blue1_str, 10);
							itoa(data[20], White1_str, 10);

							itoa(data[22], Red2_str, 10);
							itoa(data[24], Green2_str, 10);
							itoa(data[26], Blue2_str, 10);
							itoa(data[28], White2_str, 10);

							generate_zero(Red1_str, sizeof(Red1_str),
									strlen(Red1_str));
							generate_zero(Green1_str, sizeof(Green1_str),
									strlen(Green1_str));
							generate_zero(Blue1_str, sizeof(Blue1_str),
									strlen(Blue1_str));
							generate_zero(White1_str, sizeof(White1_str),
									strlen(White1_str));

							generate_zero(Red2_str, sizeof(Red2_str),
									strlen(Red2_str));
							generate_zero(Green2_str, sizeof(Green2_str),
									strlen(Green2_str));
							generate_zero(Blue2_str, sizeof(Blue2_str),
									strlen(Blue2_str));
							generate_zero(White2_str, sizeof(White2_str),
									strlen(White2_str));

						} else {
							//if incorrect parameter
							buflen_answer = 9;
							data[5] = 3;
							data[7] = data[7] | 128;
							data[8] = 3;
						}

					} else {
						//if incorrect parameter
						buflen_answer = 9;
						data[5] = 3;
						data[7] = data[7] | 128;
						data[8] = 1;
					}
					netconn_write(newconn, data, buflen_answer, NETCONN_COPY);

					netbuf_delete(inbuf);

				} else {
					netbuf_delete(inbuf);
					netconn_close(newconn);
					netconn_delete(newconn);
					break;
				}

			}

		} else {
			osDelay(1);
		}
	}
}

//calculate temperature
float computeTemp(float u) {
	float resistance;

	float Untc = u / 4096 * 3.3;
	resistance = Untc * 5100.0 / (3.3 - Untc);
	float result = 1 / (1.0 / 298.15 + 1.0 / 4390.0 * log(resistance / 19500))
			- 273.15;
	return result;
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_HTTPinit */
/**
 * @brief  Function implementing the HTTPserver thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_HTTPinit */
void HTTPinit(void const * argument) {
	/* USER CODE BEGIN 5 */

	/* initialization SSI and CGI */
	httpd_init();
	http_set_ssi_handler(SSI_Handler, (char const **) TAGS, 13);
	CGI_TAB[0] = CLR1_CGI;
	CGI_TAB[1] = CLR2_CGI;
	CGI_TAB[2] = IP_CGI;
	CGI_TAB[3] = MAC_CGI;
	CGI_TAB[4] = CLR_All_CGI;
	CGI_TAB[5] = MSK_CGI;
	CGI_TAB[6] = GTW_CGI;
	http_set_cgi_handlers(CGI_TAB, 7);

	/* start PWM */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

//set parameters for SNMP
	snmp_mib2_set_syscontact(syscontact_str, &syscontact_len, bufsize);
	snmp_mib2_set_syslocation(syslocation_str, &syslocation_len, bufsize);
//set to 0 when disabled, >0 when enabled
	snmp_set_auth_traps_enabled(0);
	snmp_mib2_set_sysdescr(sysdescr, &sysdescr_len);
	snmp_mib2_set_sysname(sysname_str, &sysname_len, bufsize);

	snmp_set_mibs(my_snmp_mibs, LWIP_ARRAYSIZE(my_snmp_mibs));
	snmp_init(); //Just after udp_init

//temperature measurement results
	osEvent event2;
	volatile data *d1;
	/* Infinite loop */
	for (;;) {
		event2 = osMailGet(TemperatureHandle, 100);
		if (event2.status == osEventMail) {
			d1 = event2.value.p;
			T_avg = d1->T;
		}

		HAL_IWDG_Refresh(&hiwdg);
		osDelay(1);
	}
	/* USER CODE END 5 */
}

/* USER CODE BEGIN Header_temp_measur */
/**
 * @brief Function implementing the temperature thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_temp_measur */
void temp_measur(void const * argument) {
	/* USER CODE BEGIN temp_measur */
	volatile data d;
	volatile data *d_p;
	d_p = &d;
	float T_board;
	/* Infinite loop */
	for (;;) {
		d_p = osMailAlloc(TemperatureHandle, osWaitForever);
		T_board = 0.0;
		for (int i = 0; i < 10; i++) {
			HAL_ADC_Start(&hadc1);
			HAL_ADC_PollForConversion(&hadc1, 100);
			T_board = T_board + HAL_ADC_GetValue(&hadc1);
			HAL_ADC_Stop(&hadc1);
		}
		T_board = T_board / 10.;
		T_board = computeTemp(T_board);
		d.T = T_board;
		osMailPut(TemperatureHandle, &d);
		HAL_IWDG_Refresh(&hiwdg);
		osDelay(1);

	}
	/* USER CODE END temp_measur */
}

/* USER CODE BEGIN Header_modBusInit */
/**
 * @brief Function implementing the modBus thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_modBusInit */
void modBusInit(void const * argument) {
	/* USER CODE BEGIN modBusInit */
	struct netconn *conn;
	err_t err;

	conn = netconn_new(NETCONN_TCP);
	if (conn != NULL) {
		sock01.conn = conn;
		err = netconn_bind(conn, NULL, tcp_port);
		if (err == ERR_OK) {
			netconn_listen(conn);
			sys_thread_new("tcp_thread", tcp_thread, (void*) &sock01,
			DEFAULT_THREAD_STACKSIZE, osPriorityNormal);

		} else {
			netconn_delete(conn);
		}
	}
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END modBusInit */
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM2 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM2) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	NVIC_SystemReset();
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	NVIC_SystemReset();
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
