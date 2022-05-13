#include "stm32f4xx_hal.h"
#include "delay.h"
static uint8_t fac_us = 0;
static uint16_t fac_ms = 0;

void delay_init(void)
{
  fac_us = 100; // 100*1/100M
  fac_ms = (uint16_t)fac_us * 1000;
}
// 定时时间计算：（1+TIM_Prescaler ）/72M）*（1+TIM_Period ）
// TIM_Period = 9999; // 自动重装载寄存器周期的值
//我觉得应该是指多周期需要重装载的意思
void delay_us(uint32_t nus)
{
  uint32_t temp;
  SysTick->LOAD = nus * fac_us;             //
  SysTick->VAL = 0x00;                      //
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // start
  do
  {
    temp = SysTick->CTRL; //
  } while ((temp & 0x01) && !(temp & (1 << 16)));
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL = 0X00;
}

void delay_ms(uint16_t nms)
{
  uint32_t temp;
  SysTick->LOAD = nms * fac_ms;             //
  SysTick->VAL = 0x00;                      //
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // start
  do
  {
    temp = SysTick->CTRL; //
  } while ((temp & 0x01) && !(temp & (1 << 16)));
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL = 0X00;
}

void delayus(uint32_t us)
{
  __IO uint32_t currentTicks = SysTick->VAL;
  /* Number of ticks per millisecond */
  const uint32_t tickPerMs = SysTick->LOAD + 1;
  /* Number of ticks to count */
  const uint32_t nbTicks = ((us - ((us > 0) ? 1 : 0)) * tickPerMs) / 1000;
  /* Number of elapsed ticks */
  uint32_t elapsedTicks = 0;
  __IO uint32_t oldTicks = currentTicks;
  do
  {
    currentTicks = SysTick->VAL;
    elapsedTicks += (oldTicks < currentTicks) ? tickPerMs + oldTicks - currentTicks : oldTicks - currentTicks;
    oldTicks = currentTicks;
  } while (nbTicks > elapsedTicks);
}
