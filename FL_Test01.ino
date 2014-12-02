#include <AutoDriver.h>
#include <SoftwareSerial.h>

// Test sketch for the L6470 AutoDriver library. This program instantiates three
//  AutoDriver boards and uses them to play Jonathon Coulton's "Want You Gone" from
//  the Portal 2 soundtrack. In a more general sense, it adds support for playing
//  music with stepper motors. Not all notes can be played, of course- at too high
//  a steps/sec rate, the motors will slip and dogs and cats will live together.


#define INPUT_SIZE 30
#define NUM_BOARDS 5
#define NUM_MODES 5
#define MODULE_ID 0

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
    if(token)
    {
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
        
//        if(token)
//        {
//          Serial.println(atoi(token));
//          token = strtok(NULL, " ");
//        }
//        if(token)
//        {
//          Serial.println(atoi(token));
//          token = strtok(NULL, " ");
//        }
//        if(token)
//        {
//          Serial.println(atoi(token));
//          token = strtok(NULL, " ");
//        }
//        if(token)
//        {
//          Serial.println(atoi(token));
//          token = strtok(NULL, " ");
//        }
//        if(token)
//        {
//          Serial.println(atoi(token));
//          token = strtok(NULL, " ");
//        }
        
        if(token){
          Serial.print("extra token! is: ");
          Serial.println(token[0]);
        }
        else{
          Serial.print("out of tokens, yes!"); 
        }
        
      }
    }
    
    inputString = "";
    stringComplete = false;  
  }
  
//  // if it's a change in mode
//  if(inByte == 'M'){
//    modeIndex = Serial.parseInt();
//    modeInfo = Serial.parseInt();
//    Serial.print("Mode Index: ");
//    Serial.print(modeIndex);
//    Serial.print(", Mode Info: ");
//    Serial.println(modeInfo);
//    modeChange = true;
//  }
//  
//  // if it's direct servo control
//  else if(Serial.find("S")){
//    motorIndex = Serial.parseInt();
//    motorInfo = Serial.parseInt();
//    Serial.print("Motor Index: ");
//    Serial.print(motorIndex);
//    Serial.print(", Motor Info: ");
//    Serial.println(motorInfo);
//    stepperCommand = true;
//  }
//  
//  // For resetting home on servo
//  else if(Serial.find("R")){
//    int resetIndex = Serial.parseInt();
//    int resetInfo = Serial.parseInt();
//    Serial.print("Reset Index: ");
//    Serial.print(resetIndex);
//    Serial.print(", Reset Info: ");
//    Serial.println(resetInfo);
//    resetCommand = true;
//  }
  
  // if we have incoming mode change
//  if(modeChange){
//    
//    
//    switch(modeIndex){
//      
//      case 0:
//        Serial.println("Mode 0");
//        break;
//    
//      case 1:
//        Serial.println("Mode 1");
//        break;
//        
//      case 2:
//        Serial.println("Mode 2");
//        break;
//        
//      case 3:
//        Serial.println("Mode 3");
//        break;
//    
//      case 4:
//        Serial.println("Mode 4");
//        break;
//    
//      default:
//        break;
//      
//    }
//    // modeChange is over
//    modeChange = false; 
//  }
//  
//  // if we have incoming stepper command
//  else if (stepperCommand){
//    stepLocation = motorInfo;
//    switch(motorIndex){
//      
//      case 0:
//        Serial.print("Stepper 0: ");
//        Serial.println(motorInfo);
//        
//        // movement
//        if(boardA.getParam(ABS_POS) < stepLocation){
//          boardA.move(FWD, stepLocation - boardA.getParam(ABS_POS));
//        }
//        else if (boardA.getParam(ABS_POS) > stepLocation){
//          boardA.move(REV, boardA.getParam(ABS_POS) - stepLocation);
//        }
//        
//        Serial.print("Step location wanted: ");
//        Serial.print(stepLocation);
//        Serial.print(", Step location at: ");
//        Serial.println(boardA.getParam(ABS_POS));
//        
//        break;
//    
//      case 1:
//        Serial.print("Stepper 1: ");
//        Serial.println(motorInfo);
//        if(boardB.getParam(ABS_POS) < stepLocation){
//          boardB.move(FWD, stepLocation - boardB.getParam(ABS_POS));
//        }
//        else if (boardB.getParam(ABS_POS) > stepLocation){
//          boardB.move(REV, boardB.getParam(ABS_POS) - stepLocation);
//        }
//        
//        Serial.print("Step location wanted: ");
//        Serial.print(stepLocation);
//        Serial.print(", Step location at: ");
//        Serial.println(boardB.getParam(ABS_POS));
//        
//        break;
//        
//      case 2:
//        Serial.print("Stepper 2: ");
//        Serial.println(motorInfo);
//        if(boardC.getParam(ABS_POS) < stepLocation){
//          boardC.move(FWD, stepLocation - boardC.getParam(ABS_POS));
//        }
//        else if (boardC.getParam(ABS_POS) > stepLocation){
//          boardC.move(REV, boardC.getParam(ABS_POS) - stepLocation);
//        }
//        
//        Serial.print("Step location wanted: ");
//        Serial.print(stepLocation);
//        Serial.print(", Step location at: ");
//        Serial.println(boardC.getParam(ABS_POS));
//        break;
//        
//      case 3:
//        Serial.print("Stepper 3: ");
//        Serial.println(motorInfo);
//        if(boardD.getParam(ABS_POS) < stepLocation){
//          boardD.move(FWD, stepLocation - boardD.getParam(ABS_POS));
//        }
//        else if (boardD.getParam(ABS_POS) > stepLocation){
//          boardD.move(REV, boardD.getParam(ABS_POS) - stepLocation);
//        }
//        
//        Serial.print("Step location wanted: ");
//        Serial.print(stepLocation);
//        Serial.print(", Step location at: ");
//        Serial.println(boardD.getParam(ABS_POS));
//        break;
//    
//      case 4:
//        Serial.print("Stepper 4: ");
//        Serial.println(motorInfo);
//        if(boardE.getParam(ABS_POS) < stepLocation){
//          boardE.move(FWD, stepLocation - boardE.getParam(ABS_POS));
//        }
//        else if (boardE.getParam(ABS_POS) > stepLocation){
//          boardE.move(REV, boardE.getParam(ABS_POS) - stepLocation);
//        }
//        
//        Serial.print("Step location wanted: ");
//        Serial.print(stepLocation);
//        Serial.print(", Step location at: ");
//        Serial.println(boardE.getParam(ABS_POS));
//        break;
//    
//      default:
//        Serial.println("Default stepper");
//        break;
//      
//    }
//    
//    // stepperCommand is over
//    stepperCommand = false; 
//  }
  
//  if (Serial.available() !=0)
//  {
//    
//    byte inByte = Serial.read();
//    Serial.println(inByte);
//    switch(inByte){
//      case 'h':
//        boardA.goHome();
//        boardB.goHome();
//        boardC.goHome();
//        boardD.goHome();
//        boardE.goHome();
//        while (boardA.busyCheck());
//        break;
//      case 'd':
//        dance();
//        break;
//      case '1':
//        boardA.move(FWD, 50);
//        while (boardA.busyCheck());
//        break;
//      case '2':
//        boardB.move(FWD, 50);
//        while (boardA.busyCheck());
//        break;
//      case '3':
//        boardC.move(FWD, 50);
//        while (boardA.busyCheck());
//        break;
//      case '4':
//        boardD.move(FWD, 50);
//        while (boardA.busyCheck());
//        break;
//      case '5':
//        boardE.move(FWD, 50);
//        while (boardA.busyCheck());
//        break;
//      case '!':
//        boardA.move(REV, 50);
//        while (boardA.busyCheck());
//        break;
//      case '@':
//        boardB.move(REV, 50);
//        while (boardA.busyCheck());
//        break;
//      case '#':
//        boardC.move(REV, 50);
//        while (boardA.busyCheck());
//        break;
//      case '$':
//        boardD.move(REV, 50);
//        while (boardA.busyCheck());
//        break; 
//      case '%':
//        boardE.move(REV, 50);
//        while (boardA.busyCheck());
//        break;
//      case '6':
//        moveAllReverse();
//        break;
//      case '7':
//        moveAllForward();
//        break;
//      case '8':
//        moveAllReverseLong();
//        break;
//      case '9':
//        moveAllForwardLong();
//        break;
//      case 'r':
//        resetAllPos();
//        break;
//        
//      // quick steps/throttle test
//      case 'z':
//        boardE.move(FWD, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(FWD, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(FWD, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(FWD, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(FWD, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(REV, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(REV, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(REV, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(REV, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        boardE.move(REV, 10);
//        while (boardA.busyCheck());
//        delay(100);
//        break;
//       
//      case 'x':
//        boardE.run(FWD, 1000);
//        delay(3000);
//        boardE.softStop();
//        boardE.run(FWD, 1000);
//        delay(3000);
//        boardE.softStop();
//         boardE.run(REV, 1000);
//        delay(3000);
//        boardE.softStop();
//         boardE.run(REV, 1000);
//        delay(3000);
//        boardE.softStop();
//        break;
//        
//      case 'y':
//        
//        boardC.move(FWD, stepsTest);
//        
//        boardD.move(FWD, stepsTest);
//       
//        boardE.move(FWD, stepsTest);
////        delay(100);
//
//        while(boardE.busyCheck());
//        
//        boardC.move(REV, stepsTest);
//        
//        boardD.move(REV, stepsTest);
//
//        boardE.move(REV, stepsTest);
//
//        while(boardE.busyCheck());
//        
//        boardC.move(FWD, stepsTest);
////        delay(100);
//        boardD.move(FWD, stepsTest);
//
////        delay(100);
//        boardE.move(FWD, stepsTest);
//
//        while(boardE.busyCheck());
////        delay(100);
//        boardC.move(REV, stepsTest);
//        boardD.move(REV, stepsTest);
//        boardE.move(REV, stepsTest);
//        
//        while(boardE.busyCheck());
//        break;
//      
//      case 'n':
//        boardE.move(FWD, stepsTest);
//        boardE.move(REV, stepsTest);
//        break;
//      
//      case 'q':
//        Serial.print("Start q, at pos: ");
//        Serial.println(boardE.getParam(ABS_POS));
//        
//        for (int i=0; i < 2; i++){
//          Serial.println("Forward");
////          boardA.run(FWD, 400);
////          boardB.run(FWD, 400);
////          boardC.run(FWD, 400);
//          boardC.run(FWD, 400);
////          boardE.run(FWD, 400);
//          while(boardC.getParam(ABS_POS) < 600){
//            Serial.print("Positions: ");
//            Serial.print(boardA.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardB.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardC.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardD.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.println(boardE.getParam(ABS_POS));
//          }
//          Serial.println("Reverse");
////          boardA.run(REV, 400);
////          boardB.run(REV, 400);
////          boardC.run(REV, 400);
//          boardC.run(REV, 400);
////          boardE.run(REV, 400);
//          while(boardC.getParam(ABS_POS) > 200 && !(boardC.getParam(ABS_POS) > 4194204)){
//            Serial.print("Positions: ");
//            Serial.print(boardA.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardB.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardC.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardD.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.println(boardE.getParam(ABS_POS));
//          }
//        }
//        
//        boardA.softStop();
//        boardB.softStop();
//        boardC.softStop();
//        for (int i=0; i < 2; i++){
//          Serial.println("Forward");
////          boardA.run(FWD, 400);
////          boardB.run(FWD, 400);
////          boardC.run(FWD, 400);
//          boardD.run(FWD, 400);
////          boardE.run(FWD, 400);
//          while(boardD.getParam(ABS_POS) < 600){
//            Serial.print("Positions: ");
//            Serial.print(boardA.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardB.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardC.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardD.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.println(boardE.getParam(ABS_POS));
//          }
//          Serial.println("Reverse");
////          boardA.run(REV, 400);
////          boardB.run(REV, 400);
////          boardC.run(REV, 400);
//          boardD.run(REV, 400);
////          boardE.run(REV, 400);
//          while(boardD.getParam(ABS_POS) > 200 && !(boardD.getParam(ABS_POS) > 4194204)){
//            Serial.print("Positions: ");
//            Serial.print(boardA.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardB.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardC.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardD.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.println(boardE.getParam(ABS_POS));
//          }
//        }
//        boardD.softStop();
//        for (int i=0; i < 2; i++){
//          Serial.println("Forward");
////          boardA.run(FWD, 400);
////          boardB.run(FWD, 400);
////          boardC.run(FWD, 400);
//          boardE.run(FWD, 400);
////          boardE.run(FWD, 400);
//          while(boardE.getParam(ABS_POS) < 600){
//            Serial.print("Positions: ");
//            Serial.print(boardA.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardB.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardC.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardD.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.println(boardE.getParam(ABS_POS));
//          }
//          Serial.println("Reverse");
////          boardA.run(REV, 400);
////          boardB.run(REV, 400);
////          boardC.run(REV, 400);
//          boardE.run(REV, 400);
////          boardE.run(REV, 400);
//          while(boardE.getParam(ABS_POS) > 200 && !(boardE.getParam(ABS_POS) > 4194204)){
//            Serial.print("Positions: ");
//            Serial.print(boardA.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardB.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardC.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.print(boardD.getParam(ABS_POS));
//            Serial.print(" ");
//            Serial.println(boardE.getParam(ABS_POS));
//          }
//        }
//        boardE.softStop();
//        Serial.print("Done with q, at pos: ");
//        Serial.println(boardE.getParam(ABS_POS));
//        break;
//      
//      default:
//        stepperPositioningTest();
//    }
//    
//    Serial.print("E position is: ");
//    // This yields the current absolute position
//    Serial.println(boardE.getParam(ABS_POS));
//    
//  }  
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

