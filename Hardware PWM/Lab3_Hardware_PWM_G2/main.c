#include <msp430.h> 



/**
 * Hardware_PWM_G2
 * Author: Jordan Alberico
 * Created: 10/3/18
 * Last Edited: 10/3/18
 */

extern void LEDSetup();
extern void ButtonSetup();
extern void TimerASetup();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    LEDSetup(); // Initialize LED
    ButtonSetup(); // Initialize Buttons
    TimerASetup(); // Initialize TimerA
    __bis_SR_register(GIE);

    while (1)
    {

    }
}

void LEDSetup()
{
    P1SEL |= BIT6; // Sets port 1.6 to Timer
    P1DIR |= BIT6; // Sets port 1.6 to output
    P1OUT &= ~BIT6; // LED port 1.6 starts off

}

void ButtonSetup()
{
    P1SEL &= ~BIT3; // Sets port 1.3 to GPIO
    P1DIR &= ~BIT3; // Sets port 1.3 to input
    P1IE |= BIT3; // Interrupt Enabled on port 1.3
    P1IES |= BIT3; // Sets interrupt as falling edge
    P1IFG &= ~BIT3; // Clears Interrupt flag on port 1.3
    P1REN |= BIT3; // Enables pull up resistor on port 1.3
}

void TimerASetup()
{
    TA0CTL = TASSEL_1 + MC_1; //ACLK, up mode, toggle/reset
    TA0CCTL1 = OUTMOD_2; //timer in toggle/reset mode
    CCR0 = 60;
    CCR1 = 30;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (TACCR1 > 0)
    {
        CCR1 -= 3;
    }
    else
    {
        CCR1 = 30;
    }
    P1IFG &= ~BIT3; // Clears Interrupt flag on port 1.3
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A (void)
{
    switch (TA0IV)
    {
        case 2:
            P1OUT ^= BIT6;
            break;

        case 4:
            break;

        case 10:
            if (TACCR1 <= 0)
            {
                P1OUT |= BIT6;
            }
            else
            {
                P1OUT &= ~BIT6;
            }
            break;
    }
}
