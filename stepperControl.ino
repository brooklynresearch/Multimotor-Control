void stepperControl(){
  
  boardA.run(FWD, 400);
  Serial.println("Running");
  Serial.println(boardA.busyCheck());
  boardB.run(FWD, 2000);
  boardC.run(FWD, 10);

  while (boardA.busyCheck());
  Serial.println(boardA.busyCheck());

  
//  boardA.softStop();
//  boardB.softStop();
////  boardC.softStop();
//  while (boardA.busyCheck());
//  
//  boardA.run(REV, 4000);
//  boardB.run(REV, 2000);
////  boardC.run(REV, 100);
//  while (boardA.busyCheck());
//  
//  boardA.softStop();
//  boardB.softStop();
////  boardC.softStop();
//  while (boardA.busyCheck());
}

void dance(){
  boardA.move(REV, 500);
  boardB.move(REV, 500);
  boardC.move(REV, 500);
  boardD.move(REV, 500);
  boardE.move(REV, 500);
  
  while(boardA.busyCheck());
  delay(1000);
  
  boardB.move(FWD, 250);
  boardC.move(FWD, 500);
  boardD.move(FWD, 250);
  
  while(boardA.busyCheck());
  delay(1000);
  
  boardB.move(REV, 250);
  boardC.move(REV, 500);
  boardD.move(REV, 250);
  
  while(boardA.busyCheck());
  delay(1000);
  
  boardA.move(FWD, 500);
  boardB.move(FWD, 400);
  boardC.move(FWD, 300);
  boardD.move(FWD, 200);
  boardE.move(FWD, 100);
  
  while(boardA.busyCheck());
  delay(1000);
  
  boardA.move(REV, 250);
  boardB.move(REV, 150);
  boardC.move(REV, 50);
  boardD.move(FWD, 50);
  boardE.move(FWD, 150);
  
  while(boardA.busyCheck());
  delay(1000);
  
  boardA.move(FWD, 250);
  boardB.move(FWD, 250);
  boardC.move(FWD, 250);
  boardD.move(FWD, 250);
  boardE.move(FWD, 250);
  
  while(boardA.busyCheck());

}

void moveAllForward(){
  boardA.move(FWD, 100);
  boardB.move(FWD, 100);
  boardC.move(FWD, 100);
  boardD.move(FWD, 100);
  boardE.move(FWD, 100);
  while(boardA.busyCheck());
}

void moveAllForwardLong(){
  boardA.move(FWD, 400);
  boardB.move(FWD, 400);
  boardC.move(FWD, 400);
  boardD.move(FWD, 400);
  boardE.move(FWD, 400);
  while(boardA.busyCheck());
}

void moveAllReverseLong(){
  boardA.move(REV, 400);
  boardB.move(REV, 400);
  boardC.move(REV, 400);
  boardD.move(REV, 400);
  boardE.move(REV, 400);
  while(boardA.busyCheck());
}

void resetAllPos(){
    boardA.resetPos();
    boardB.resetPos();
    boardC.resetPos();
    boardD.resetPos();
    boardE.resetPos();
}

void moveAllReverse(){
  boardA.move(REV, 100);
  boardB.move(REV, 100);
  boardC.move(REV, 100);
  boardD.move(REV, 100);
  boardE.move(REV, 100);
  while(boardA.busyCheck());
}
void stepperPositioningTest(){
  boardA.move(FWD, 200);
//  boardA.goUntil(COPY_ABSPOS, FWD, 100);
//  boardA.softStop();
  Serial.print("Busy?: ");
  Serial.println(boardA.busyCheck());
  Serial.print("Status: ");
  Serial.println(boardA.getStatus());
//  while (boardA.busyCheck());
//  Serial.print("Busy?: ");
//  Serial.println(boardA.busyCheck());
  
}

void boardBTest(){
  boardB.move(REV, 700);
  
  while(boardA.busyCheck());

  boardB.move(FWD, 700);
  
  while(boardA.busyCheck());
  
}

void stepperSoftStop(){
  boardA.softStop();
}

// Really long function selecting which motor to go to what step
void motorToPosition(int currentMotor, int targetStep){
  // Giant switch statement because we don't have arrays for some goddamn reason
  Serial.print("Current Motor is: ");
  Serial.println(currentMotor);
  Serial.print("TargetStep is: ");
  Serial.print(targetStep);
  
  switch(currentMotor){
    case 0:
      Serial.print("Stepper 0: ");
      Serial.println(currentMotor);
      
      // logic for how much to reverse or forward depending
      // on current position and desired position
      if(boardA.getParam(ABS_POS) < targetStep){
        boardA.move(FWD, targetStep - boardA.getParam(ABS_POS));
      }
      else if (boardA.getParam(ABS_POS) > targetStep){
        boardA.move(REV, boardA.getParam(ABS_POS) - targetStep);
      }
      
      Serial.print("Step location wanted: ");
      Serial.print(targetStep);
      Serial.print(", Step location at: ");
      Serial.println(boardA.getParam(ABS_POS));
      
      break;
  
    case 1:
      Serial.print("Stepper 1: ");
      Serial.println(currentMotor);
      if(boardB.getParam(ABS_POS) < targetStep){
        boardB.move(FWD, targetStep - boardB.getParam(ABS_POS));
      }
      else if (boardB.getParam(ABS_POS) > targetStep){
        boardB.move(REV, boardB.getParam(ABS_POS) - targetStep);
      }
      
      Serial.print("Step location wanted: ");
      Serial.print(stepLocation);
      Serial.print(", Step location at: ");
      Serial.println(boardB.getParam(ABS_POS));
      
      break;
      
    case 2:
      Serial.print("Stepper 2: ");
      Serial.println(currentMotor);
      if(boardC.getParam(ABS_POS) < targetStep){
        boardC.move(FWD, targetStep - boardC.getParam(ABS_POS));
      }
      else if (boardC.getParam(ABS_POS) > targetStep){
        boardC.move(REV, boardC.getParam(ABS_POS) - targetStep);
      }
      
      Serial.print("Step location wanted: ");
      Serial.print(targetStep);
      Serial.print(", Step location at: ");
      Serial.println(boardC.getParam(ABS_POS));
      break;
      
    case 3:
      Serial.print("Stepper 3: ");
      Serial.println(currentMotor);
      if(boardD.getParam(ABS_POS) < targetStep){
        boardD.move(FWD, targetStep - boardD.getParam(ABS_POS));
      }
      else if (boardD.getParam(ABS_POS) > targetStep){
        boardD.move(REV, boardD.getParam(ABS_POS) - targetStep);
      }
      
      Serial.print("Step location wanted: ");
      Serial.print(targetStep);
      Serial.print(", Step location at: ");
      Serial.println(boardD.getParam(ABS_POS));
      break;
  
    case 4:
      Serial.print("Stepper 4: ");
      Serial.println(currentMotor);
      if(boardE.getParam(ABS_POS) < targetStep){
        boardE.move(FWD, targetStep - boardE.getParam(ABS_POS));
      }
      else if (boardE.getParam(ABS_POS) > targetStep){
        boardE.move(REV, boardE.getParam(ABS_POS) - targetStep);
      }
      
      Serial.print("Step location wanted: ");
      Serial.print(targetStep);
      Serial.print(", Step location at: ");
      Serial.println(boardE.getParam(ABS_POS));
      break;
  
    default:
      Serial.println("Default stepper");
      break;
    
  }
}
