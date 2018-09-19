#include <Wire.h>

// IR sensors
const int irled1 = A0;
const int irled2 = A1;
const int irled3 = A2;
const int irled4 = A3;

const int motor1a = 6;
const int motor1b = 7;
const int motor2a = 8;
const int motor2b = 9;
const int spd = 50;

// variable that defines wether slave should make its own decisions or obey the master
bool under_self_control = true;


void setup() {
  
  Wire.begin(1);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
 
  

  pinMode(irled1, INPUT);
  pinMode(irled2, INPUT);
  pinMode(irled3, INPUT);
  pinMode(irled4, INPUT);

  // 4 motors?!
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
  

  pinMode(irled1, INPUT);
  pinMode(irled2, INPUT);
  pinMode(irled3, INPUT);
  pinMode(irled4, INPUT);

  Serial.begin(9600);
}

void loop() {

  unsigned long startedWaiting = millis();
  int max1 = 0, max2 = 0, max3 = 0, max4 = 0;
  int finalmax = 0;


  //go straight for 10 secs
  forward();

  
  // gather the max value along that line
  while(millis() - startedWaiting <= 10000) { //run for 10 seconds
    max1 = max(analogRead(irled1), max1);
    max2 = max(analogRead(irled2), max2);
    max3 = max(analogRead(irled3), max3);
    max4 = max(analogRead(irled4), max4);

  }
  
  finalmax = max(max(max1, max2),max(max3,max4));
  
  // the robot is instructed to head to the point recorded as the maximum
  if(max1 == finalmax) {
    go_to_max(irled1, finalmax);
    
  } else if (max2 == finalmax) {
    go_to_max(irled1, finalmax);
    
  } else if (max3 == finalmax) {
    go_to_max(irled1, finalmax);
    
  } else {
    go_to_max(irled1, finalmax);
  }

  // orient the slave to face the source of irl
  turn();

  // head towards it
  forward();

  // master takes command of slave as soon as I2C contacts touch
  under_self_control = false;
  while (! under_self_control);





Serial.print(analogRead(irled1));
Serial.print("\n");
/*
Serial.print(analogRead(irled2));
Serial.print("\n");
Serial.print(analogRead(irled3));
Serial.print("\n");
Serial.print(analogRead(irled4));
Serial.print("\n");
*/
}

void forward() {
  analogWrite(motor1a, spd);
  analogWrite(motor1b, 0);
  analogWrite(motor2a, spd);
  analogWrite(motor2b, 0);
}

void backward() {
  analogWrite(motor1a, spd);
  analogWrite(motor1b, 0);
  analogWrite(motor2a, spd);
  analogWrite(motor2b, 0);
}

//stops the robot in its tracks
void stop_motors(){
  analogWrite(motor1a, 0);
  analogWrite(motor1b, 0);
}

// backs up until the point of maximum strength is found
void go_to_max(int irled, int max_point){

    while (analogRead(irled) < (0.9 * max_point) ){
      backward();     
    }
    
    // as soon as that while loop is broken, kill the motors.
    stop_motors();
}




// Turns to face the maximum strength
void turn() {
  unsigned long start_time = millis();
  int turnmax = 0;
  analogWrite(motor1a, spd);
  analogWrite(motor1b, 0);

  
  while((millis() - start_time) <= 10000){

     // this should just be in regards to the sensor facing the front
     turnmax = max(turnmax, analogRead(irled1));
  }

  // just wait until the old max is reached again
  while (analogRead(irled1) < (0.9 * turnmax));

  stop_motors();
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

  stop_motors();    

  
  while (1 < Wire.available()); // loop through all but the last
    
    int pin_to_fire = Wire.read(); // receive the instruction to turn on light x
   
   // code for "no lights to be turned on
   if (pin_to_fire != -1){

    // the corresponding led is turned on
    digitalWrite(pin_to_fire, HIGH);

      
   }

}
