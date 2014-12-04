#include <AutoDriver.h>
#include <SoftwareSerial.h>

#define _SS_MAX_RX_BUFF 128

#define INPUT_SIZE 500
#define NUM_BOARDS 5
#define NUM_MODES 5
#define MODULE_ID 0  // CHANGE THIS FOR EACH MODULE OF 5 MOTORS

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
char charBuf[INPUT_SIZE];

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
  mySerial.begin(57600);
  delay(1000);
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

  // When a newline is recevied and we have an entire message
  if (stringComplete) {
//    Serial.println(inputString);
    // turn into charArray for processing
    inputString.toCharArray(charBuf,INPUT_SIZE);
    token = strtok(charBuf," ");  //tokenize
    
    /* Messaging Notes

      Format is with space as delimiters with
      commands ending with a newline.
      For modes:
      
      MODULE_ID M MODE_ID

      For direct stepper controls
      MODULE_ID S STEPPER_ID STEPPER_LOCATION    
    */
    
    // if we received message
    if(token)
    {
      // if the message is directed to us
//      Serial.print("Addressing module: ");
//      Serial.println(atoi(token));
      
      // Check to see if we are the module to process message
      if(true)
      {
        // strip that first signal
        token = strtok(NULL, " ");
        
        // if next token is equal to 'M' for mode
        if(token[0] == 'M'){
//          Serial.print("we have a: ");
//          Serial.println(token[0]);
          token = strtok(NULL, " ");
          
          // Take next token to process it for something
          if(token)
          {
            modeIndex = atoi(token);
//            Serial.print("Mode is: ");
//            Serial.println(modeIndex);
            token = strtok(NULL, " ");
          }
        }
        
        // All steppers stopped
        else if(token[0] == 'H'){
//          Serial.print("we have a halt: ");
//          Serial.println(token[0]);
          stepperSoftStop();
          token = strtok(NULL, " ");
        }
        
        // if not a modal change, then individually
        // addressing steppers with 'S'
        else if(token[0] == 'S'){
//          Serial.print("we have a: ");
//          Serial.println(token[0]);
          token = strtok(NULL, " ");
          
          // Parse according to which stepper
          while(token){
//            Serial.print("We are on stepper ");
//            Serial.println(token[0]);
            // which stepper
            motorIndex = atoi(token);
            token = strtok(NULL, " ");
            // where is the stepper supposed to go
            motorInfo = atoi(token);
            token = strtok(NULL, " ");
//            Serial.print("We use motor: ");
//            Serial.print(motorIndex);
//            Serial.print(". We are going to: ");
//            Serial.println(motorInfo);
            // go there (function is in stepperControl)
            if(motorInfo >= 0){
              motorToPosition(motorIndex, motorInfo);
            }
          }
          
          if(token){
//            Serial.print("extra token! is: ");
//            Serial.println(token[0]);
          }
          else{
//            Serial.print("out of tokens, yes!"); 
          }
        }
      }
    }
    
    inputString = "";
    stringComplete = false;  
  }
  
  while (mySerial.available()) {
    // get the new byte:
    char inChar = (char)mySerial.read();
//    Serial.print("got char: ");
//    Serial.println(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
//    if (inChar == '\n') {
//      stringComplete = true;
//    }
   if (inChar == 'z') {
//      Serial.println("See z!");
      stringComplete = true;
//      mySerial.flush();
//      break;
    }  
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
//void serialEvent() {
//  while (Serial.available()) {
////  while (mySerial.available()) {
//    // get the new byte:
//    char inChar = (char)Serial.read(); 
////    char inChar = (char)mySerial.read();
//    Serial.print("got char: ");
//    Serial.println(inChar);
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag
//    // so the main loop can do something about it:
//    if (inChar == '\n') {
//      stringComplete = true;
//    } 
//  }
//}

