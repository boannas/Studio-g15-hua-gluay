/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"
#include "ModBusRTU.h"
#include "Basesystem.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */
// --porpor-- //

ModbusHandleTypedef hmodbus;
u16u8_t registerFrame[200];
int mode = 0;
int stop = 0;
int motor = 0;
uint8_t ps2rx[10];
uint8_t f[10];
int on = 0;
int v[3];
int h[3];
int counth = 0;
int countv = 0;
int fuck = 0;
int ps2vpos;
int ps2v;
int ps2hpos;
int ps2h;
uint8_t x = 1;			// Fine tune with PSX
int y;
int num[]= {48,49,50,51,52,53,54,55,56,57};
int pwm1 = 0;
int r[] = {0,0,0,0,0,0};
int l[] = {0,0,0,0,0,0};
uint8_t data_packet[4] = {0x45, 0,0, 0x0A};
uint16_t velo[34000];
int start;
int i = 0;
int j = 1;
float pwm = 41.67;

//~~QEI Read From AMT103V & PID~~//
uint32_t QEIReadRaw;
int32_t diff;
arm_pid_instance_f32 PID = {0};
volatile uint16_t setposition = 0;
float Vfeedback = 0;

typedef struct
	{
		// for record New / Old value to calculate dx / dt
		uint32_t Position[2];
		uint64_t TimeStamp[2];
		float QEIPostion_1turn;
		int QEIAngularVelocity;
	}
	QEI_StructureTypeDef;
	QEI_StructureTypeDef QEIdata = {0};
	uint64_t _micros = 0;
	enum
	{
	NEW,OLD
	};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM5_Init(void);
static void MX_UART4_Init(void);
static void MX_TIM16_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
uint64_t micros();
void QEIEncoderPosVel_Update();
void PS2X_Reader();
void Automatic_Control();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_UART4_Init();
  MX_TIM16_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim5);
  hmodbus.huart = &huart2;
  hmodbus.htim = &htim16;
  hmodbus.slaveAddress = 0x15;
  hmodbus.RegisterSize =200;
  Modbus_init(&hmodbus, registerFrame);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  Modbus_Protocal_Worker();
//	  HAL_Delay(200);
	  Routine();
	  Vacuum();
	  GripperMovement();

//  	  QEIReadRaw = __HAL_TIM_GET_COUNTER(&htim2); // Encoder QEI
//  	  static uint64_t timestamps =0;
//  	  int64_t currentTime = micros();
//
//  	  if(currentTime > timestamps)
//  	  {
//  		  timestamps = currentTime + 100000;//us
//  		  QEIEncoderPosVel_Update();
//  	  }


//	  if (start == 1){
//		static uint32_t timestamp =0;
//		if(timestamp < HAL_GetTick())
//		{
//		  timestamp = HAL_GetTick()+0.5;
//
//		  velo[i] = QEIdata.QEIAngularVelocity;
//
//		  data_packet[1] = (uint8_t)(QEIdata.QEIAngularVelocity & 0x00FF); // Mask with 0x00FF to get LSB
//		  data_packet[2]  = (uint8_t)(QEIdata.QEIAngularVelocity >> 8)& 0x00FF; // Shift right 8 bits to get MSB
//
//		  // Transmit data over UART
//		  for (int i = 0; i < sizeof(data_packet); i++)
//		  {
//			HAL_UART_Transmit(&hlpuart1, &data_packet[i], 1, 5);
//		  }
//
//
//		  /// j = 1
//		  if (i == (j*2000)){
//			  j++;
//		  }
//
//		  if ((j%2) == 0){
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (j/2)*3*pwm);
////			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
//		  }
//
//		  if ((j%2) == 1){
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
//		  }
//		  if (j == 18){
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
//		  }
//		  i++;
//
//		}
//	}

<<<<<<< HEAD
=======
	  if (start == 1){
		static uint32_t timestamp =0;
		if(timestamp < HAL_GetTick())
		{
		  timestamp = HAL_GetTick()+0.5;

		  velo[i] = QEIdata.QEIAngularVelocity;

		  data_packet[1] = (uint8_t)(QEIdata.QEIAngularVelocity & 0x00FF); // Mask with 0x00FF to get LSB
		  data_packet[2]  = (uint8_t)(QEIdata.QEIAngularVelocity >> 8)& 0x00FF; // Shift right 8 bits to get MSB

		  // Transmit data over UART
		  for (int i = 0; i < sizeof(data_packet); i++)
		  {
			HAL_UART_Transmit(&hlpuart1, &data_packet[i], 1, 5);
		  }


		  /// j = 1
		  if (i == (j*2000)){
			  j++;
		  }

		  if ((j%2) == 0){
			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (j/2)*3*pwm);
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
		  }

		  if ((j%2) == 1){
			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		  }
		  if (j == 18){
			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		  }
		  i++;

		}

	  }
//  	  QEIReadRaw = __HAL_TIM_GET_COUNTER(&htim2); // Encoder QEI
//  	  static uint64_t timestamps =0;
//  	  int64_t currentTime = micros();
//
//  	  if(currentTime > timestamps)
//  	  {
//  		  timestamps = currentTime + 100000;//us
//  		  QEIEncoderPosVel_Update();
//  	  }
//
//
>>>>>>> 9b4fa2369da5fcc0c216ebcc5ae4d72abeaa21a2
//	  if (start == 1){
//		static uint32_t timestamp =0;
//		if(timestamp < HAL_GetTick())
//		{
//		  timestamp = HAL_GetTick()+0.5;
//
//		  velo[i] = QEIdata.QEIAngularVelocity;
//
//		  data_packet[1] = (uint8_t)(QEIdata.QEIAngularVelocity & 0x00FF); // Mask with 0x00FF to get LSB
//		  data_packet[2]  = (uint8_t)(QEIdata.QEIAngularVelocity >> 8)& 0x00FF; // Shift right 8 bits to get MSB
//
//		  // Transmit data over UART
//		  for (int i = 0; i < sizeof(data_packet); i++)
//		  {
//			HAL_UART_Transmit(&hlpuart1, &data_packet[i], 1, 5);
//		  }
//
//
//		  /// j = 1
//		  if (i == (j*2000)){
//			  j++;
//		  }
//
//		  if ((j%2) == 0){
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (j/2)*3*pwm);
////			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
//		  }
//
//		  if ((j%2) == 1){
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
//		  }
//		  if (j == 18){
//			  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
//		  }
//		  i++;
//
//		}
//
//	  }
<<<<<<< HEAD

=======
>>>>>>> 9b4fa2369da5fcc0c216ebcc5ae4d72abeaa21a2


//	  	  if(mode == 1)
//	  	  {
//	  		PS2X_Reader();
//	  	  }
//	  	  else if(mode == 2)
//	  	  {
//	  		Automatic_Control();
//	  	  }
	  HAL_UART_Receive(&huart4,ps2rx, 10 ,10);

	  if(ps2rx[0] == 74){
		  stop = 1;
	  }

	  if (stop == 1 && ps2rx[0] == 75){
		  stop = 0;
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);		//Stop
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
		  pwm1 = 0;
	  }

	  else if(stop == 0){
		  PS2X_Reader();
	  }


  }



  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 169;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1699;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 19999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 169;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 4294967295;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 169;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 1145;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim16, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9700;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_8_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 19200;
  huart2.Init.WordLength = UART_WORDLENGTH_9B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_EVEN;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Photo_Base_Pin Photo_Top_Pin */
  GPIO_InitStruct.Pin = Photo_Base_Pin|Photo_Top_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Reed_Pull_Pin */
  GPIO_InitStruct.Pin = Reed_Pull_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Reed_Pull_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Eme_logic_Pin */
  GPIO_InitStruct.Pin = Eme_logic_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Eme_logic_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Reed_Push_Pin */
  GPIO_InitStruct.Pin = Reed_Push_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Reed_Push_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
//MicroSecondTimer Implement
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
//		if(htim == &htim5)
//			{
//			_micros += UINT32_MAX;
//			}
		if(htim == &htim4)
		{
			 Heartbeat();
		}
	}

//uint64_t micros()
//	{
//		return __HAL_TIM_GET_COUNTER(&htim5)+_micros;
//	}

void QEIEncoderPosVel_Update()
	{
		//collect data
		QEIdata.TimeStamp[NEW] = micros();
		QEIdata.Position[NEW] = __HAL_TIM_GET_COUNTER(&htim2);
		//Postion 1 turn calculation
		QEIdata.QEIPostion_1turn = QEIdata.Position[NEW] % 8192;
		//calculate dx
		int32_t diffPosition = QEIdata.Position[NEW] - QEIdata.Position[OLD];
		//Handle Warp around
		if(diffPosition > 32256)
			diffPosition -=64512;
		if(diffPosition < -32256)
			diffPosition +=64512;
		//calculate dt
		float diffTime = (QEIdata.TimeStamp[NEW]-QEIdata.TimeStamp[OLD]) * 0.000001;
		//calculate anglar velocity
		QEIdata.QEIAngularVelocity = ((diffPosition/8192.0)*60) / diffTime;
		//store value for next loop
		QEIdata.Position[OLD] = QEIdata.Position[NEW];
		QEIdata.TimeStamp[OLD]=QEIdata.TimeStamp[NEW];
}

void PS2X_Reader()
{
	///----- Stage 1: Jogging and Floor selection -----///
	ps2v = 0;
	ps2h = 0;
	on = 0;
	if (ps2rx[0] == 69) 		//Press L4 to switch to use Joy stick
	{
		mode = 1;
		ps2vpos = 132;
	}
	if (ps2rx[0] == 70)		//Press L5 to switch to use Button
	{
		mode = 2;
	}
	//--- Mode Joy stick ---//
	if (mode == 1)
	{
		//Read Ps2 Joy stick in VERTICAL
		if(ps2rx[0] == 81){
			if (ps2rx[2] == 83){
				y = 1;
			}
			else if (ps2rx[3] == 83){
				y = 2;
			}
			else if (ps2rx[4] == 83){
				y = 3;
			}
			for(int k=1 ; k<5 ; k++){
				for (int l=0; l<10 ; l++){
					if (ps2rx[k] == num[l]){
						v[k-1] = l;
					}
				}
			}
			if (y == 1){
				ps2vpos = v[0];
			}
			else if (y == 2){
				ps2vpos = (v[0]*10)+v[1];
			}
			else if (y == 3){
				ps2vpos = (v[0]*100)+(v[1]*10)+v[2];
			}

//			  //Read Ps2 Joy stick in HORIZON
//			  if (ps2rx[0] == 83 && ps2rx[2] == 13)
//			  {
//				  for (int i = 0; i < 10 ; i++)
//				  {
//					  if (ps2rx[1]==num[i])
//					  {
//						  h[0] = i;
//					  }
//				  }
//				  ps2hpos = h[0];
//			  }
//			  else if (ps2rx[0] == 83 && ps2rx[3] == 13)
//			  {
//				  for (int i = 0; i < 10 ; i++)
//				  {
//					  if (ps2rx[1]==num[i])
//					  {
//						  h[0] = i;
//					  }
//					  if (ps2rx[2]==num[i])
//					  {
//						  h[1] = i;
//					  }
//				  }
//				  ps2hpos = (h[0]*10)+h[1];
//			  }
//			  else if (ps2rx[0] == 83 && ps2rx[4] == 13)
//			  {
//				  for (int i = 0; i < 10 ; i++)
//				  {
//					  if (ps2rx[1]==num[i])
//					  {
//						  h[0] = i;
//					  }
//					  if (ps2rx[2]==num[i])
//					  {
//						  h[1] = i;
//					  }
//					  if (ps2rx[3]==num[i])
//					  {
//						  h[2] = i;
//					  }
//				  }
//				  ps2hpos = (h[0]*100)+(h[1]*10)+h[2];
//			  }
		}

		//Convert from 0 - 255 to -128 - 128
		ps2v = ps2vpos - 132;
		ps2h = ps2hpos - 132;

		//Generate PWM
		pwm1 = (ps2v / 128.0)*300;
		if (pwm1 > 300)
		{
			pwm1 = 300;
		}
		if (pwm1 < -300)
		{
			pwm1 = -300;
		}
		if (pwm1 < 0)
		{
			pwm1 = pwm1 * -1;
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);		//PWM out Backward
		}
		else if (pwm1 > 0)
		{
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);		//PWM out forward
		}
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm1);
	}

	//--- Mode Button ---//
	else if (mode == 2)
	{
		//////////////////////BUG BUG BUG BUG BUG BUG BUG BUG//////////////////////////////
//		if (l[6] == 1 && mode == 2){
//			f[fuck] = 1+fuck;
//			fuck++;
//		}
//		/// this upper code for checking in Live Expression about Floor Seclection
//		//---- Reset Floor in Array f[] ----//
//		if (r[0] == 1 && mode == 2){
//			f[fuck-1] = 0;
//			fuck--;
//		}
		//////////////////////BUG BUG BUG BUG BUG BUG BUG BUG//////////////////////////////
		ps2v = 0;
		ps2h = 0;
		//Keys Map
		static uint32_t timestamp =0;
		if(timestamp < HAL_GetTick())
		{
			timestamp = HAL_GetTick()+100;
			ps2rx[0] = 0;
		}
		for (int i =0;i<6;i++)
		{
			if (ps2rx[0] == 0)
			{
				//Left
				l[0] = 0; //w
				l[1] = 0;	//a
				l[2] = 0;	//s
				l[3] = 0;	//d
				l[4] = 0;	//l1
				l[5] = 0;	//l2
				l[6] = 0;
				l[7] = 0;
				//Right
				r[0] = 0;	//w
				r[1] = 0;	//a
				r[2] = 0;	//s
				r[3] = 0;	//d
				r[4] = 0;	//r1
				r[5] = 0;	//r2

				on = 0;
			}

			if (ps2rx[0] - 65 == i)
			{
				l[i] = 1;
			}

			else if (ps2rx[0] - 73 == i)
			{
				r[i] = 1;
			}
		}

		//Generate PWM
		if (l[2] == 1)
		{
			pwm1 = pwm1 - x;	// + PWM with x
			if (pwm1 < 0)
			{
				pwm1 = 0;		// to make pwm1 >= 0
			}
		}
		else if (l[3] == 1)
		{
			pwm1 = pwm1 + x;	// - PWM with x
		}
		else if (l[0] == 1)		//Press down button(l1) to PWM out forward
		{
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm1);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			motor = 1;		//motor is working forward for checking in Live Expression
		}
		else if (l[1] == 1)		//Press down button(l1) to PWM out backward
		{
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwm1);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
			motor = 2;		//motor is working backward for checking in Live Expression
		}
		else if (r[1] == 1)		//Press X(r1) to stop
		{
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);		//Stop
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			motor =0;			//motor is not working for checking in Live Expression
		}
	}

	//---- Floor Seclection ----//
	if(base.ShelveMode == 1)
	{
		if (ps2rx[0] == 71)
		{
			base.Shelve[fuck] = 1+fuck;
			fuck= fuck +1;
		}
		else if (ps2rx[0] == 73)
		{
			base.Shelve[fuck-1] = 0;
			fuck = fuck -1;
		}

		if (ps2rx[0] == 72 && registerFrame[0x10].U16 == 0b0001)
		{
			base.ShelveMode = 0;
			registerFrame[0x10].U16 = 0b0000;
		}
	}

}

void Automatic_Control()
{

		  static uint32_t timestamp =0;
	 	  diff = setposition - QEIReadRaw;
		  if(timestamp < HAL_GetTick())
			  {
			  timestamp = HAL_GetTick()+1;
			  Vfeedback = arm_pid_f32(&PID, setposition - QEIReadRaw);
			  }
		  if(diff > 0)
			  {
				  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, Vfeedback);
				  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			  }
		  else if(diff < 0)
			  {
				  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, Vfeedback);
				  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
			  }
}

// Photo Limit Condition
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_4)
    {
        // Handle the interrupt for PA4
        // Example: Toggle an LED, send a message, etc.
    	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
    	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);	//PWM out backward
    }
    else if (GPIO_Pin == GPIO_PIN_6)
    {
        // Handle the interrupt for PA6
        // Example: Toggle a different LED, trigger another event, etc.
    	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
    	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);	//PWM out backward
		mode = 0;
    }
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
