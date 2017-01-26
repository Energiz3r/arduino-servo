# arduino-servo
Use an arduino and a potentiometer to control a motor and make a DIY heavy-duty R/C servo!

I used an existing R/C servo with its electronics removed for its potentiometer and housing. This was mechanically connected to the steering mechanism on a heavy duty brushed motor for positional feedback. (I used a windscreen wiper motor)

The centre of the pot connects to the A0 pin, and the two outer pins connect to REF (the analog voltage reference pin on the arduino) and GND respectively.

I used a regular R/C receiver for input (PWM).

The motor controller is a regular R/C brushed ESC set to 'immediate' mode - so there is no delay for changing direction / reversing. This is important as ESCs stuck in race mode won't allow the motor to change direction suddenly.

Image of my servo:

http://i.imgur.com/MjcOb6b.jpg
