#include <msp430.h> 


/**
 * Debouncing_G2
 * Author: Jordan Alberico
 * Created: 9/29/18
 * Last Edited: 10/2/18
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
    _BIS_SR(GIE); // enable global interrupt

    while(1)
    {

    }

}

void LEDSetup()
{
    P1SEL &= ~BIT0; //sets port 1.0 to GPIO
    P1DIR |= BIT0; //sets port 1.0 to output
    P1OUT &= ~BIT0; //Turns off LED
}

void ButtonSetup()
{
    P1SEL &= ~BIT3; //sets port 1.3 to GPIO
    P1DIR &= ~BIT3; //sets port 1.3 to input
    P1REN |= BIT3; //Pull up resistor on port 1.3
    P1IE |= BIT3; //enable interrupt on port 1.3
    P1IES |= BIT3; //sets interrupt on port 1.3 to falling edge
    P1IFG &= ~BIT3; //clear interrupt flag

}

void TimerASetup()
{
    timerDone = 1;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port1(void)
{
    if (timerDone == 1)
    {
        P1OUT ^= BIT0; //Toggles LED
        TA0CTL = TASSEL_1 + MC_1 + TAIE; //AClock in UP Mode, Interrupt enabled
        TACCR0 = 10;
        timerDone = 0;
    }
    P1IFG &= ~BIT3; //Clear interrupt flag
}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
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

