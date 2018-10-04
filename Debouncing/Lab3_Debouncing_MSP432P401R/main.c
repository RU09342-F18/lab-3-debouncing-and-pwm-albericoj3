#include "msp.h"


/**
 * Debouncing_MSP432P401R
 * Author: Jordan Alberico
 * Created: 10/3/18
 * Last Edited: 10/3/18
 */

extern void LEDSetup();
extern void ButtonSetup();
extern void TimerASetup();

int timerDone;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    LEDSetup(); // Sets up LEDs
    ButtonSetup(); // Sets up Buttons
    TimerASetup(); // Sets up timer
    __enable_irq();  // enable global interrupt
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31); //Needed for MSP432 Interrupts

    while(1)
    {

    }

}

void LEDSetup()
{
    P1SEL0 &= ~BIT0; //sets port 1.0 to GPIO
    P1DIR |= BIT0; //sets port 1.0 to output
    P1OUT &= ~BIT0; //Turns off LED
}

void ButtonSetup()
{
    P1SEL1 &= ~BIT1; //sets port 1.1 to GPIO
    P1DIR &= ~BIT1; //sets port 1.1 to input
    P1REN |= BIT1; //Pull up resistor on port 1.1
    P1IE |= BIT1; //enable interrupt on port 1.1
    P1IES |= BIT1; //sets interrupt on port 1.1 to falling edge
    P1IFG &= ~BIT1; //clear interrupt flag
}

void TimerASetup()
{
    timerDone = 1;
}

void Port_1(void)
{
    if (timerDone == 1)
    {
        P1OUT ^= BIT0; //Toggles LED
        TA0CTL = TASSEL_1 + MC_1 + TAIE; //AClock in UP Mode, Interrupt enabled
        TA0CCR0 = 10;
        timerDone = 0;
    }
    P1IFG &= ~BIT1; //Clear interrupt flag
}


void TA0_0_IRQHandler(void)
{
   switch(TA0IV)       //TimerA interrupt vector values
   {
    case 2:
       break;
    case 4:
        break;
    case 10:                       //Counter reaches CCR0
        timerDone = 1;            //Timer has delayed for desired length of time so set to true
        TA0CTL = TACLR;            //Clear counter
        TA0CTL = TASSEL_1 + MC_0;  //Stop Counting
        break;
   }


}
