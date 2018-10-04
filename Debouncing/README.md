# Software Debouncing
In this code, a button press will change the state of the LED. The code has been configured so that it elminates debouncing of the button. Debouncing occurs when the button is released from being pressed, and it oscilates for a brief moment of time. When this happens, a single button press can be interpreted as two button presses which could cause issue for any code. If debouncing were to occur in this example, pressing the button once would not change the state of the LED. 

## MSP430G2ET
Pins:

LED - Port 1.0 set to GPIO, output, inital state of 0
Button - Port 1.3 set to GPIO, input, pull up resistor, interrupt enabled
TimerA - AClock in UP Mode, interrupt enabled

## MSP432P401R
Pins:

LED - Port 1.0 set to GPIO, output, inital state of 0
Button - Port 1.1 set to GPIO, input, pull up resistor, interrupt enabled
TimerA - AClock in UP Mode, interrupt enabled

## How the Code was Implemented
The interrupt occurs on the negative edge of the button. Since the button is configured with a pull up resistor, the falling edge occurs when then button is pressed by the user. when the falling edge interrupt is triggered, a timer begins counting. Measuring the signal of the button on the oscilloscope, the time between bounces is about 400 ns. Therefore, the timer needs to count to a value of at least 400 ns. Since the clock choosen (ACLK) has a period higher than that (31 microseconds), one cycle should do. However, CCR0 was set to 10 just to be safe. Once the timer is done timing, The timerDone variable is set to 1 and the button can be triggered again. 
