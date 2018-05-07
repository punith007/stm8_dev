//#include "stm8s.h"
#include <stdint.h>

#define TIM2_PSCR	(*(volatile uint8_t *)0x530E)
#define TIM2_EGR	(*(volatile uint8_t *)0x5306)
#define TIM2_EGR_UG	(*(volatile uint8_t *)0x5307)
#define TIM2_CR1	(*(volatile uint8_t *)0x5300)
#define TIM2_CR1_CEN	(*(volatile uint8_t *)0x5301)
#define TIM2_CNTRH	(*(volatile uint8_t *)0x530C)
#define TIM2_CNTRL	(*(volatile uint8_t *)0x530D)

#define PB_ODR	(*(volatile uint8_t *)0x5005)
#define PB_DDR	(*(volatile uint8_t *)0x5007)
#define PB_CR1	(*(volatile uint8_t *)0x5008)

int main() {
  // Default clock is HSI/8 = 2MHz

  //PB_DDR |= (1 << PB5); // PB5 is now output
  //PB_CR1 |= (1 << PB5); // PB5 is now pushpull
  PB_DDR = 0x20;
  PB_CR1 = 0x20;

  TIM2_PSCR = 0b00000111; //  Prescaler = 128
  // Generate an update event so prescaler value will be taken into account.
  TIM2_EGR |= (1 << TIM2_EGR_UG);
  TIM2_CR1 |= (1 << TIM2_CR1_CEN); // Enable TIM2

  while (1) {
    if ( ( ((uint16_t)TIM2_CNTRH << 8) + (uint16_t)TIM2_CNTRL ) >= 15625 ) {
      // Reset counter back to 0
      TIM2_CNTRH = 0;
      TIM2_CNTRL = 0;

      // Toggle LED.
      //PB_ODR ^= (1 << PB5);
      PB_ODR ^= 0x20;
    }
  }
}
