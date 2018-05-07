#include <stdint.h>
#define TIM4_ISR 23

#define CLK_CKDIVR	(*(volatile uint8_t *)0x50c6)
#define CLK_PCKENR1	(*(volatile uint8_t *)0x50c7)

#define TIM4_CR1	(*(volatile uint8_t *)0x5340)
#define TIM4_PSCR	(*(volatile uint8_t *)0x5347)
#define TIM4_ARR	(*(volatile uint8_t *)0x5348)
#define TIM4_IER	(*(volatile uint8_t *)0x5343)
#define TIM4_SR 	(*(volatile uint8_t *)0x5344)

#define PB_ODR	(*(volatile uint8_t *)0x5005)
#define PB_DDR	(*(volatile uint8_t *)0x5007)
#define PB_CR1	(*(volatile uint8_t *)0x5008)

//uint_8 count=0;

int main() {
    /* Enable interrupts */
    __asm__("rim");
    /* Set PD3 as output */
    PB_DDR |= 0x20;
    PB_CR1 |= 0x20;

    /*
    // Prescaler = 128 
    TIM4_PSCR = 0b00000111;
    TIM4_ARR = 0xFF;
    TIM4_IER |= 0x01; // Enable Update Interrupt
    TIM4_CR1 |= 0x01; // Enable TIM4
    */

    TIM4_PSCR = 0b00000111;
    // Period =
    TIM4_ARR = 0xFF;
    //TIM4_ARRL = 0xFF;
    TIM4_IER |= 0x01; // Enable Update Interrupt
    TIM4_CR1 |= 0x01; // Enable TIM2

    while (1) {
        /* Loop forever */
    }
}

void timer_isr(void) __interrupt(TIM4_ISR) {
    PB_ODR ^= 0x20;
    TIM4_SR &= 0xFE;
    //TIM2_SR1 &= 0xfe; 
}
