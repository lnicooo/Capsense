#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart/uart.h"

volatile uint16_t chargeCycle;

void initPinInterrput(){
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << PC1);
}

ISR(PCINT1_vect){
  chargeCycle++;
  DDRC |= (1 << PC1);
  _delay_us(2); //capacitor charge time
  DDRC &= ~(1 << PC1);
  PCIFR |= (1 << PCIF1);

}


int main(){



  DDRB |= (1 << PB5);

  MCUCR |= (1 << PUD); //disable pulups

  PORTC |= (1 << PC1);

	uart_init();
	stdout = &uart_output;
	stdin  = &uart_input;

  initPinInterrput();

  printf("Ready\n");

  while(1){
    chargeCycle=0;
    DDRC |= (1 << PC1);

    sei();
    _delay_ms(50);
    cli();
    if(chargeCycle < 3600){
      PORTB |= (1 << PB5);
    }
    else{
      PORTB &= ~(1 << PB5);
    }
    printf("%d\n",chargeCycle);

  }


}
