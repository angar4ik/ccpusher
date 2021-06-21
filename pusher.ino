#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object
  myservo.write(90);
}

// Example 4 - Receive a number as text and convert it to an int
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;
int dataNumber = 0;             // new for this version

void loop() {
    recvWithEndMarker();
    showNewNumber();
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    if (Serial.available() > 0) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewNumber() {
    if (newData == true) {
      if(String(receivedChars).indexOf("INFO") != -1) {
        Serial.println("CC Dipper v1.1");
        newData = false;
      }
      else {
        dataNumber = 0;             // new for this version
        dataNumber = atoi(receivedChars);   // new for this version
        if (dataNumber <= 180 && !(dataNumber < 1)) { setAngle(dataNumber); Serial.println(dataNumber); }
        else { Serial.println("NaN or OoR"); }
        newData = false;
      }
   }
}

void setAngle(int angle){
    myservo.write(angle);
}
