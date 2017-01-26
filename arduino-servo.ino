/*

Steering servo controller
for DangerFlite R/C Toolbox

*/

#define showSerial false //set to true to turn on serial output

//motor parameters
#define motPin 3 //the output pin that goes to the motor controller (servo)
#define motMax 115 //the max servo output (degrees) the motor controller will accept
#define motMid 90 //the middle (stopped) position
#define motMin 75 //min
//if motor turns the wrong way, invert the polarity. no need to do that in code

//steer RC input parameters
#define rxPin 2 //the pin the receiver is connected to
#define rxMax 1950 //PWM max
#define rxMin 1000 //PWM min (who needs PPM/S.BUS support?! nobody, that's who)
#define rxTrim -150 //trim the centre position by this amount (positive or negative integer)
#define rxInvert true //invert steering direction

//max allowed (physical) position for this servo (use Serial output to get this value from "Input")
//if the PID controller tries to move the servo past this value the motor output is set to motMid
#define posMax 63000
#define posMin 37900

//potentiometer parameters
#define potPin A0 //the pot input pin
#define potMax 965 //highest analog value the pot generates
#define potMin 80 //lowest analog value the pot generates
//no need to invert pot direction - invert steering and/or invert polarity on your motor

//tuning
#define PGain 3 //Proportional gain for the control loop

//libs
#include <Servo.h> //include servo lib
Servo motor; //set up object

//setup
void setup() {

  pinMode(rxPin, INPUT); //set input mode for RX pin
  motor.attach(motPin); //attach object to pin
  if (showSerial) {
    Serial.begin(115200); //pour a bowl of Serial
  }
  
}

//keep the loop time consistent by setting the duration (microseconds)
int loopTime = 2500; //this can't be less than the maximum PWM width the RX will produce. 2500 is a safe value

//the main loop
void loop() {
  
  //sample the PWM width of the RX input. Shortening the sample time to near the maxmimum value seems to break it
  //it only waits long enough to sample the pulse width, not the full 25000 microseconds. leave as-is
  //if the PWM width is higher than expected, the effect it'll have on the loop duration is irrelevant as your input is invalid
  int long input = pulseIn(rxPin, HIGH, 25000);

  //adjust input by the trim amount
  input = input + rxTrim;

  //clamp input to an acceptable range in case of invalid PWM width
  input = constrain(input, rxMin, rxMax);

  //invert input direction
  if (rxInvert) {  
    input = rxMin + (rxMax - rxMin) - (input - rxMin);
  }

  //keep the loop time consistent by adding a delay so it's always (x) microseconds
  delayMicroseconds(loopTime - input); //the compute time of the loops adds to this but that doesn't matter as it doesn't vary

  //map the input values to the same range as the pot so they can be compared
  input = map(input, rxMin, rxMax, potMin, potMax);

  //multiply the value by 100 so we don't have to use floats to compute accurately (faster)
  input = input * 100;
  
  //read position value from pot
  int long pos = analogRead(potPin);

  //constrain value to valid range
  pos = constrain(pos, potMin, potMax);

  //multiply by 100
  pos = pos * 100;

  //do Proportional control here
  int long output = (input - pos) * PGain;

  //divide output by 100 and map to a value the motor controller can use
  output = map((output / 100), potMin, potMax, motMin, motMax);

  //make sure the value doesn't step outside valid range
  output = constrain(output, motMin, motMax);

  //limit max and min positions by setting the motor output to centre position if it does
  //not really an elegant solution as it bypasses the P loop, but it works great on my setup
  if (pos < posMin && output < motMid) {

    output = motMid;
    
  }
  else if (pos > posMax && output > motMid) {

    output = motMid;
    
  }

  //set the output to the motor
  motor.write(output);

  //show some diagnostic values on the Serial interface
  if (showSerial) {
    
    Serial.print("Input: ");
    Serial.print(input);
    Serial.print(" Position: ");
    Serial.print(pos);
    Serial.print(" Output: ");
    Serial.println(output);

  }

}



