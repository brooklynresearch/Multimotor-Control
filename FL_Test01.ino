#include <AutoDriver.h>
#include <SoftwareSerial.h>

#define INPUT_SIZE 30
#define NUM_BOARDS 5
#define NUM_MODES 5
#define MODULE_ID 0 // CHANGE THIS FOR EACH MODULE OF 5 MOTORS

// Create our AutoDriver instances. The parameters are pin numbers in
//  Arduino-speke for CS, reset, and busy.
AutoDriver boardA(10, 6, 4);
AutoDriver boardB(9, 6, 4);
AutoDriver boardC(8, 6, 4);
AutoDriver boardD(7, 6, 4);
AutoDriver boardE(5, 6, 4);
SoftwareSerial mySerial(3,2); // rx, tx

int current_mode[NUM_MODES] = {0,1,2,3,4};
char input[INPUT_SIZE + 1];
char* token;
char charBuf[50];

String inputString = "";
boolean stringComplete = false;
long stepperTime = 0;
int stepperThreshold = 4000;  
int stepsTest = 600;

// comms variable
int modeIndex = 0;
int modeInfo = 0;

int motorIndex = 0;
int motorInfo = 0;
int stepLocation = 0;  // where to move in steps wise

int resetIndex = 0;
int resetInfo = 0;

boolean modeChange = false;
boolean stepperCommand = false;
boolean resetCommand = false;

void setup()
{
  
  Serial.begin(115200);
  Serial.println("Hello world");
  mySerial.begin(115200);
  dSPINConfig();
  stepperTime = millis();
//  boardA.softStop();
  boardA.resetPos();
  boardB.resetPos();
  boardC.resetPos();
  boardD.resetPos();
  boardE.resetPos();
  char* command = strtok(input, "&");
  
}

void loop()
{
//  byte inByte;
//  
//  if(Serial.available() != 0){
//     inByte = Serial.read();
//     Serial.print("My Byte: ");
//     Serial.println(inByte);
//  }
//  
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString.toCharArray(charBuf,50);
    token = strtok(charBuf," ");
    
    // if we received message
    if(token)
    {
      // if the message is directed to us
      Serial.print("Addressing module: ");
      Serial.println(atoi(token));
      
      if(atoi(token) == MODULE_ID)
      {
        token = strtok(NULL, " ");
        
        if(token[0] == 'M'){
          Serial.print("we have a: ");
          Serial.println(token[0]);
          token = strtok(NULL, " ");
          if(token)
          {
            modeIndex = atoi(token);
            Serial.print("Mode is: ");
            Serial.println(modeIndex);
            token = strtok(NULL, " ");
          }
        }
        
        else if(token[0] == 'S'){
          Serial.print("we have a: ");
          Serial.println(token[0]);
          token = strtok(NULL, " ");
          
          // Parse according to stepper
          while(token){
            Serial.print("We are on stepper ");
            Serial.println(token[0]);
            
            motorIndex = atoi(token);
            token = strtok(NULL, " ");
            motorInfo = atoi(token);
            token = strtok(NULL, " ");
            Serial.print("We use motor: ");
            Serial.print(motorIndex);
            Serial.print(". We are going to: ");
            Serial.println(motorInfo);
            
            motorToPosition(motorIndex, motorInfo);
          }
          
          if(token){
            Serial.print("extra token! is: ");
            Serial.println(token[0]);
          }
          else{
            Serial.print("out of tokens, yes!"); 
          }
        }
      }
    }
    
    inputString = "";
    stringComplete = false;  
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

