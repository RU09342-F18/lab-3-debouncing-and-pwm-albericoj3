#include <msp430.h> 



/**
 * Software_PWM_F5529LP
 * Author: Jordan Alberico
 * Created: 10/3/18
 * Last Edited: 10/4/18
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
    PM5CTL0 &= ~LOCKLPM5;
    __enable_interrupt();
    __bis_SR_register(GIE);

    while (1)
    {

    }
}

void LEDSetup()
{
    P4SEL &= ~BIT7; // Sets port 1.0 to GPIO
    P4DIR |= BIT7; // Sets port 4.7 to output
   // P1SEL &= ~BIT6; // Sets port 1.6 to GPIO
  //  P1DIR |= BIT6; // Sets port 1.6 to output
    P4OUT &= ~BIT7; // LED port 1.0 starts off
  //  P1OUT &= ~BIT6; // LED port 1.6 starts off

}

void ButtonSetup()
{
    P1SEL &= ~BIT1; // Sets port 1.1 to GPIO
    P1DIR &= ~BIT1; // Sets port 1.1 to input
    P1IE |= BIT1; // Interrupt Enabled on port 1.1
    P1IES |= BIT1; // Sets interrupt as falling edge
    P1IFG &= ~BIT1; // Clears Interrupt flag on port 1.1
    P1REN |= BIT1; // Enables pull up resistor on port 1.1
}

void TimerASetup()
{
    TA0CTL = TASSEL_1 + MC_1 + TAIE; //ACLK, up mode
    TA0CCR0 = 60;
    TA0CCR1 = 30;
    TA0CCTL0 |= CCIE; // Enable Interrupt
    TA0CCTL1 |= CCIE; // Enable Interrupt
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
    switch (TA0IV)
    {
        case 2:
            P4OUT ^= BIT7;
            break;

        case 4:
            break;

        case 10:
            if (TA0CCR1 <= 0)
            {
                P4OUT |= BIT7;
            }
            else
            {
                P4OUT &= ~BIT7;
            }
            break;
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (TA0CCR1 > 0)
    {
        TA0CCR1 -= 3;
    }
    else
    {
        TA0CCR1 = 30;
    }
    P1IFG &= ~BIT1; // Clears Interrupt flag on port 1.1
}

