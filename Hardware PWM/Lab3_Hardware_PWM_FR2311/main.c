#include <msp430.h> 



/**
 * Hardware_PWM_FR2311
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
    P1SEL0 |= BIT0; // Sets port 1.0 to Timer
    P1DIR |= BIT0; // Sets port 1.0 to output
    P1OUT &= ~BIT0; // LED port 1.0 sTBrts off

}

void ButtonSetup()
{
    P1SEL0 &= ~BIT1; // Sets port 1.1 to GPIO
    P1DIR &= ~BIT1; // Sets port 1.1 to input
    P1IE |= BIT1; // Interrupt Enabled on port 1.1
    P1IES |= BIT1; // Sets interrupt as falling edge
    P1IFG &= ~BIT1; // Clears Interrupt flag on port 1.1
    P1REN |= BIT1; // Enables pull up resistor on port 1.1
}

void TimerASetup()
{
    TB0CTL = TBSSEL_1 + MC_1 + TBIE; //ACLK, up mode, toggle/reset
    TBCCTL1 = OUTMOD_2; //timer in toggle/reset mode
    TBCCR0 = 60;
    TBCCR1 = 30;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (TBCCR1 > 0)
    {
        TBCCR1 -= 3;
    }
    else
    {
        TBCCR1 = 30;
    }
    P1IFG &= ~BIT1; // Clears Interrupt flag on port 1.1
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
{
    switch (TB0IV)
    {
        case 2:
            P1OUT ^= BIT0;
            break;

        case 4:
            break;

        case 10:
            if (TBCCR1 <= 0)
            {
                P1OUT |= BIT0;
            }
            else
            {
                P1OUT &= ~BIT0;
            }
            break;
    }
}
