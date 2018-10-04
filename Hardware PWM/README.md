# Hardware PWM
The purpose of this code is to generate a PWM singal using the harwarein the microcoontrollers. Instead of using two TACCR registers, an outmode will be selected and used to generate a PWM signal. This is more efficient than using two TACCR registers because the outmode is programmed into the microcontroller to perform a certain function. Whereas in software the programmer has to code in the functionality.

## MSP430G2ET
Pins: </br>
LED - Port 1.6 set to GPIO, output, inital state of 0 </br>
Button - Port 1.3 set to GPIO, input, pull up resistor, interrupt enabled </br>
TimerA - AClock in UP Mode, outmode set to toggle/reset

## MSP430FR2311
Pins: </br>
LED - Port 1.0 set to GPIO, output, inital state of 0 </br>
Button - Port 1.1 set to GPIO, input, pull up resistor, interrupt enabled </br>
TimerA - AClock in UP Mode, outmode set to toggle/reset

## How to Implement the Code
The code for hardware PWM is similar to the code for software PWM. Except in generating a hardware PWM signal, the outmode will set an interrupt for TACCR0 and TACCR1. When the interrupt for TACCR1 is hit, the signal will toggle and when the interrupt for TACCR0 is hit, the signal will reset. This is more efficient than generating the signal through software.
