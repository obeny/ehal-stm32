/**********************************************************************************************************************
	VECTOR TABLE FOR MD/HD families
**********************************************************************************************************************/

#include "ehal/global.h"

#define VECTORS_END 0x33333333

void __weak NMI_Handler(void);
void __weak HardFault_Handler(void);
void __weak MemManage_Handler(void);
void __weak BusFault_Handler(void);
void __weak UsageFault_Handler(void);
void __weak SVC_Handler(void);
void __weak DebugMon_Handler(void);
void __weak PendSV_Handler(void);
void __weak SysTick_Handler(void);
void __weak WWDG_IRQHandler(void);
void __weak PVD_IRQHandler(void);
void __weak TAMPER_IRQHandler(void);
void __weak RTC_IRQHandler(void);
void __weak FLASH_IRQHandler(void);
void __weak RCC_IRQHandler(void);
void __weak EXTI0_IRQHandler(void);
void __weak EXTI1_IRQHandler(void);
void __weak EXTI2_IRQHandler(void);
void __weak EXTI3_IRQHandler(void);
void __weak EXTI4_IRQHandler(void);
void __weak DMA1_Channel1_IRQHandler(void);
void __weak DMA1_Channel2_IRQHandler(void);
void __weak DMA1_Channel3_IRQHandler(void);
void __weak DMA1_Channel4_IRQHandler(void);
void __weak DMA1_Channel5_IRQHandler(void);
void __weak DMA1_Channel6_IRQHandler(void);
void __weak DMA1_Channel7_IRQHandler(void);
void __weak ADC1_2_IRQHandler(void);
void __weak USB_HP_CAN1_TX_IRQHandler(void);
void __weak USB_LP_CAN1_RX0_IRQHandler(void);
void __weak CAN1_RX1_IRQHandler(void);
void __weak CAN1_SCE_IRQHandler(void);
void __weak EXTI9_5_IRQHandler(void);
void __weak TIM1_BRK_IRQHandler(void);
void __weak TIM1_UP_IRQHandler(void);
void __weak TIM1_TRG_COM_IRQHandler(void);
void __weak TIM1_CC_IRQHandler(void);
void __weak TIM2_IRQHandler(void);
void __weak TIM3_IRQHandler(void);
void __weak TIM4_IRQHandler(void);
void __weak I2C1_EV_IRQHandler(void);
void __weak I2C1_ER_IRQHandler(void);
void __weak I2C2_EV_IRQHandler(void);
void __weak I2C2_ER_IRQHandler(void);
void __weak SPI1_IRQHandler(void);
void __weak SPI2_IRQHandler(void);
void __weak USART1_IRQHandler(void);
void __weak USART2_IRQHandler(void);
void __weak USART3_IRQHandler(void);
void __weak EXTI15_10_IRQHandler(void);
void __weak RTCAlarm_IRQHandler(void);
void __weak USBWakeUp_IRQHandler(void);
void __weak TIM8_BRK_IRQHandler(void);
void __weak TIM8_UP_IRQHandler(void);
void __weak TIM8_TRG_COM_IRQHandler(void);
void __weak TIM8_CC_IRQHandler(void);
void __weak ADC3_IRQHandler(void);
void __weak FSMC_IRQHandler(void);
void __weak SDIO_IRQHandler(void);
void __weak TIM5_IRQHandler(void);
void __weak SPI3_IRQHandler(void);
void __weak UART4_IRQHandler(void);
void __weak UART5_IRQHandler(void);
void __weak TIM6_IRQHandler(void);
void __weak TIM7_IRQHandler(void);
void __weak DMA2_Channel1_IRQHandler(void);
void __weak DMA2_Channel2_IRQHandler(void);
void __weak DMA2_Channel3_IRQHandler(void);
void __weak DMA2_Channel4_5_IRQHandler(void);

/* 
 * WARNING:
 * symbol Default_Handler may be renamed by compiler
 */
__no_return __attribute__((section(".text.Default_Handler"))) void Default_Handler(void);
__no_return __attribute__((section(".text.Default_Handler"))) void Default_Handler(void) { while(1); }

extern void Reset_Handler(void) __attribute__((__interrupt__));
extern UINT32 __stack_end__;

typedef void (*const vecfunc) (void);

/*
	Exception Vectors to be placed in RAM or ROM, depending on remapping.
	Mapped to Address 0x00 after remapping.
	Absolute addressing mode must be used.
*/
__attribute__((section(".vectrom"))) void (* const _vectors[]) (void) =
{
	(vecfunc)&__stack_end__,
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0,
	0,
	0,
	0,
	SVC_Handler,
	DebugMon_Handler,
	0,
	PendSV_Handler,
	SysTick_Handler,
	WWDG_IRQHandler,
	PVD_IRQHandler,
	TAMPER_IRQHandler,
	RTC_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_IRQHandler,
	EXTI1_IRQHandler,
	EXTI2_IRQHandler,
	EXTI3_IRQHandler,
	EXTI4_IRQHandler,
	DMA1_Channel1_IRQHandler,
	DMA1_Channel2_IRQHandler,
	DMA1_Channel3_IRQHandler,
	DMA1_Channel4_IRQHandler,
	DMA1_Channel5_IRQHandler,
	DMA1_Channel6_IRQHandler,
	DMA1_Channel7_IRQHandler,
	ADC1_2_IRQHandler,
	USB_HP_CAN1_TX_IRQHandler,
	USB_LP_CAN1_RX0_IRQHandler,
	CAN1_RX1_IRQHandler,
	CAN1_SCE_IRQHandler,
	EXTI9_5_IRQHandler,
	TIM1_BRK_IRQHandler,
	TIM1_UP_IRQHandler,
	TIM1_TRG_COM_IRQHandler,
	TIM1_CC_IRQHandler,
	TIM2_IRQHandler,
	TIM3_IRQHandler,
	TIM4_IRQHandler,
	I2C1_EV_IRQHandler,
	I2C1_ER_IRQHandler,
	I2C2_EV_IRQHandler,
	I2C2_ER_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
	USART1_IRQHandler,
	USART2_IRQHandler,
	USART3_IRQHandler,
	EXTI15_10_IRQHandler,
	RTCAlarm_IRQHandler,
	USBWakeUp_IRQHandler,
	TIM8_BRK_IRQHandler,
	TIM8_UP_IRQHandler,
	TIM8_TRG_COM_IRQHandler,
	TIM8_CC_IRQHandler,
	ADC3_IRQHandler,
	FSMC_IRQHandler,
	SDIO_IRQHandler,
	TIM5_IRQHandler,
	SPI3_IRQHandler,
	UART4_IRQHandler,
	UART5_IRQHandler,
	TIM6_IRQHandler,
	TIM7_IRQHandler,
	DMA2_Channel1_IRQHandler,
	DMA2_Channel2_IRQHandler,
	DMA2_Channel3_IRQHandler,
	DMA2_Channel4_5_IRQHandler,
	0,
	(vecfunc)VECTORS_END
};

/**********************************************************************************************************************
	Provide weak aliases for each Exception handler to the Default_Handler. 
	As they are weak aliases, any function with the same name will override 
	this definition.
**********************************************************************************************************************/

#pragma weak NMI_Handler = Default_Handler
#pragma weak HardFault_Handler = Default_Handler
#pragma weak MemManage_Handler = Default_Handler
#pragma weak BusFault_Handler = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak DebugMon_Handler = Default_Handler
#pragma weak PendSV_Handler = Default_Handler
#pragma weak SysTick_Handler = Default_Handler
#pragma weak WWDG_IRQHandler = Default_Handler
#pragma weak PVD_IRQHandler = Default_Handler
#pragma weak TAMPER_IRQHandler = Default_Handler
#pragma weak RTC_IRQHandler = Default_Handler
#pragma weak FLASH_IRQHandler = Default_Handler
#pragma weak RCC_IRQHandler = Default_Handler
#pragma weak EXTI0_IRQHandler = Default_Handler
#pragma weak EXTI1_IRQHandler = Default_Handler
#pragma weak EXTI2_IRQHandler = Default_Handler
#pragma weak EXTI3_IRQHandler = Default_Handler
#pragma weak EXTI4_IRQHandler = Default_Handler
#pragma weak DMA1_Channel1_IRQHandler = Default_Handler
#pragma weak DMA1_Channel2_IRQHandler = Default_Handler
#pragma weak DMA1_Channel3_IRQHandler = Default_Handler
#pragma weak DMA1_Channel4_IRQHandler = Default_Handler
#pragma weak DMA1_Channel5_IRQHandler = Default_Handler
#pragma weak DMA1_Channel6_IRQHandler = Default_Handler
#pragma weak DMA1_Channel7_IRQHandler = Default_Handler
#pragma weak ADC1_2_IRQHandler = Default_Handler
#pragma weak USB_HP_CAN1_TX_IRQHandler = Default_Handler
#pragma weak USB_LP_CAN1_RX0_IRQHandler = Default_Handler
#pragma weak CAN1_RX1_IRQHandler = Default_Handler
#pragma weak CAN1_SCE_IRQHandler = Default_Handler
#pragma weak EXTI9_5_IRQHandler = Default_Handler
#pragma weak TIM1_BRK_IRQHandler = Default_Handler
#pragma weak TIM1_UP_IRQHandler = Default_Handler
#pragma weak TIM1_TRG_COM_IRQHandler = Default_Handler
#pragma weak TIM1_CC_IRQHandler = Default_Handler
#pragma weak TIM2_IRQHandler = Default_Handler
#pragma weak TIM3_IRQHandler = Default_Handler
#pragma weak TIM4_IRQHandler = Default_Handler
#pragma weak I2C1_EV_IRQHandler = Default_Handler
#pragma weak I2C1_ER_IRQHandler = Default_Handler
#pragma weak I2C2_EV_IRQHandler = Default_Handler
#pragma weak I2C2_ER_IRQHandler = Default_Handler
#pragma weak SPI1_IRQHandler = Default_Handler
#pragma weak SPI2_IRQHandler = Default_Handler
#pragma weak USART1_IRQHandler = Default_Handler
#pragma weak USART2_IRQHandler = Default_Handler
#pragma weak USART3_IRQHandler = Default_Handler
#pragma weak EXTI15_10_IRQHandler = Default_Handler
#pragma weak RTCAlarm_IRQHandler = Default_Handler
#pragma weak USBWakeUp_IRQHandler = Default_Handler
#pragma weak TIM8_BRK_IRQHandler = Default_Handler
#pragma weak TIM8_UP_IRQHandler = Default_Handler
#pragma weak TIM8_TRG_COM_IRQHandler = Default_Handler
#pragma weak TIM8_CC_IRQHandler = Default_Handler
#pragma weak ADC3_IRQHandler = Default_Handler
#pragma weak FSMC_IRQHandler = Default_Handler
#pragma weak SDIO_IRQHandler = Default_Handler
#pragma weak TIM5_IRQHandler = Default_Handler
#pragma weak SPI3_IRQHandler = Default_Handler
#pragma weak UART4_IRQHandler = Default_Handler
#pragma weak UART5_IRQHandler = Default_Handler
#pragma weak TIM6_IRQHandler = Default_Handler
#pragma weak TIM7_IRQHandler = Default_Handler
#pragma weak DMA2_Channel1_IRQHandler = Default_Handler
#pragma weak DMA2_Channel2_IRQHandler = Default_Handler
#pragma weak DMA2_Channel3_IRQHandler = Default_Handler
#pragma weak DMA2_Channel4_5_IRQHandler = Default_Handler
