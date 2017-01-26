# arduino-servo
Use an arduino and a potentiometer to control a motor and make a DIY heavy-duty R/C servo!

I used an existing R/C servo with its electronics removed for its potentiometer and housing. This was mechanically connected to the steering mechanism on a heavy duty brushed motor for positional feedback. (I used a windscreen wiper motor)

The centre of the pot connects to the A0 pin, and the two outer pins connect to REF (the analog voltage reference pin on the arduino) and GND respectively.

I used a regular R/C receiver for input (PWM).

The motor controller is a regular R/C brushed ESC set to 'immediate' mode - so there is no delay for changing direction / reversing. This is important as ESCs stuck in race mode won't allow the motor to change direction suddenly.

To use this code, configure your pin assignments to suit your setup, adjust the parameters to suit the input you receive from your potentiometer and r/c receiver (look at the serial output), set some values for your ESC (keep the max and min conservative to begin with), and make any other adjustments as per the comments in the code.

Adjust the value "PGain" in increments of 1 if it's either too sloppy or oscillates back and forth.

It's a good idea to make sure your servo has strong mechanical travel limits so it won't tear your servo linkage off if it just spins for whatever reason, or the linkage with the pot fails.

Image of my servo:

http://i.imgur.com/MjcOb6b.jpg
