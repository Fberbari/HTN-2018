#include <Wire.h>
////Arduino Nano, /dev/ttyUSB0

int shape1[3][2] = {{0,3},{1,3},{0,-1}};
const int shape2[3][2] = {{0,1},{0,3},{0,-1}};
const int shape3[3][2] = {{0,1},{0,2},{0,3}};
const int shape4[3][2] = {{0,4},{1,3},{0,-1}};
int robots [3] = {1,2,3}; // holds the addresses of all the slaves not connectedto the master
bool slave_arrived;// flag to indicate wether or not a slave is in position


void setup() {
  // Start the I2C Bus as Master
  //set all pins HIGH
  Wire.begin();
  Serial.begin(9600); 
}

void loop() {
  queen((int**)(shape1));

}

void queen(int** shape) {
 while(1){   
    for (int i = 0; i < 3; i++) {
      if(shape[i][1] == -1) {
        return;
      }
      if(shape[i][0] == 0) {
        digitalWrite(shape[0][i], HIGH);
      }
      else {
        transmit(shape[i][1]);
      }
    }
  }
}
      

void transmit(int led) {
  while(1){

    Serial.print("looking for my slave! \n");
    
    for (int i = 0; i < 3; i ++){
      
      // that robot already arrived
      if (robots[i] == -1){
        continue;
      }
      
      Wire.beginTransmission(robots[i]); // transmit to device #9  
      Wire.write(led);// sends x 
      
      if (Wire.endTransmission()== 0){

        Serial.print("There ya are! \n");
        robots[i] = -1;
        return; 
      }
    } 
  }
}
