# Software PWM
The objective of this code is to generate a changing PWM signal using software. This PWM signal will be used to increase the brightness by 10% each time a button is pressed. Once the LED is at 100% brightness, the next button press will cause the LED to return to its original brightness. 

## MSP430G2ET
Pins: </br>
LED - Port 1.0 set to GPIO, output, inital state of 0 </br>
Button - Port 1.3 set to GPIO, input, pull up resistor, interrupt enabled </br>
TimerA - AClock in UP Mode, interrupt enabled

## MSP430F5529LP
Pins: </br>
LED - Port 4.7 set to GPIO, output, inital state of 0 </br>
Button - Port 1.1 set to GPIO, input, pull up resistor, interrupt enabled </br>
TimerA - AClock in UP Mode, interrupt enabled

## How the Code was Implemented
This code uses a timer to control the pulse width of the PWM signals. Both TACCR0 and TACCR1 trigger interrupts. When the timer is timing, as it hits TACCR1 it turns on the light and TACCR0 will turn off the light. This way, the value of TACCR1 can be reduced by a factor of 10% each time the button is pressed. This will cause the duty cycle of the PWM signal to increase therefore increasing the brightness of the LED. Once the value of TACCR1 hits 0, the value resets to its original value.
