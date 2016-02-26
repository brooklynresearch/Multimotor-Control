#include <SPI.h>
#include <Ethernet.h>

#include <ArdOSC.h>
#include <SoftwareSerial.h>

#define _SS_MAX_TX_BUFF 256 


byte myMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte myIp[]  = { 192, 168, 0, 178 };
int  serverPort  = 10000;

SoftwareSerial motorSerial01(4, 5); // RX, TX
SoftwareSerial motorSerial02(2, 3); // RX, TX

int ledPin =  9;

int t=0;

OSCServer server;

int serialMessageDelay = 150;
String motorControls01 = "0 S";
String motorControls02 = "0 S";

void setup(){ 

  Serial.begin(115200);

  Serial.println("Hello World");

  Ethernet.begin(myMac ,myIp); 
  server.begin(serverPort);

  //set callback function
  server.addCallback("/ledTest",&func0);
  
  server.addCallback("/mode/0",&func1);
  server.addCallback("/mode/1",&func2);
  server.addCallback("/mode/2",&func3);
  server.addCallback("/mode/3",&func4);
  
  server.addCallback("/mode/10",&func11);
  server.addCallback("/mode/11",&func12);
  server.addCallback("/mode/12",&func13);
  server.addCallback("/mode/13",&func14);
  
  server.addCallback("/motorTest",&motorTest01);
  server.addCallback("/motorTestHome", &motorTest02);

//  motorSerial01.begin(57600);
//  motorSerial02.begin(57600);
  
  pinMode(ledPin, OUTPUT);  
  
  Serial.println("Totally Initialized");

}

void loop(){
  if(server.aviableCheck()>0){
  //    Serial.println("alive! "); 
  } 
    analogWrite(ledPin, t);
  //  motorSerial.write("0 S 0 0 1 0 2 0 3 0 4 0");
  /*
  motorSerial.println("0 S 0 400 1 400 2 400 3 400 4 400");  
  delay(100);
  motorSerial.println("1 S 0 400 1 400 2 400 3 400 4 400");
  motorSerial.println("2 S 0 400 1 400 2 400 3 400 4 400");
  motorSerial.println("3 S 0 400 1 400 2 400 3 400 4 400");
//
//  motorSerial.println();
//  
  delay(2000);

  motorSerial.println("0 S 0 10 1 10 2 10 3 10 4 10");  
  delay(100);
  motorSerial.println("1 S 0 10 1 10 2 10 3 10 4 10");
  motorSerial.println("2 S 0 10 1 10 2 10 3 10 4 10");
  motorSerial.println("3 S 0 10 1 10 2 10 3 10 4 10");

  Serial.println("Just sent");
  while(1);
  */
}

void func0(OSCMessage *_mes){
  Serial.println("LED CONTROLLED");
  t = _mes->getArgInt32(0);
}

void func1(OSCMessage *_mes){
  Serial.println("We Got Something on 0");
  
  motorControls01 = ("0 S 0 ");
  
  int motor00 = 400;
  int motor01 = 400;
  int motor02 = 400;
  int motor03 = 400;
  int motor04 = 400;
  
  motorControls01 += motor00;
  motorControls01 += " 1 ";
  motorControls01 += motor01;
  motorControls01 += " 2 ";
  motorControls01 += motor02;
  motorControls01 += " 3 ";
  motorControls01 += motor03;
  motorControls01 += " 4 ";
  motorControls01 += motor04;
  
  Serial.println(motorControls01);
//  motorSerial01.println(motorControls01);
  
  //get 1st argument(int32)
//  t = _mes->getArgInt32(0);
//  motorSerial.println("0 S 0 400 1 400 2 400 3 400 4 400");  
//  delay(serialMessageDelay);
//  motorSerial.println("1 S 0 400 1 400 2 400 3 400 4 400");
//  delay(serialMessageDelay);
//  motorSerial.println("2 S 0 400 1 400 2 400 3 400 4 400");
//  delay(serialMessageDelay);
//  motorSerial.println("3 S 0 400 1 400 2 400 3 400 4 400");
 

}

void func2(OSCMessage *_mes){
  Serial.println("We got something on 1");
//  motorSerial01.write("1 S 5 400 6 400 7 400 8 400 9 400");
//  motorSerial01.println();

}

void func3(OSCMessage *_mes){
  Serial.println("We got something on 2");
//  motorSerial02.write("2 S 10 400 11 400 12 400 13 400 14 400");
//  motorSerial02.println();

}

void func4(OSCMessage *_mes){
  Serial.println("We got something on 3");
//  motorSerial02.write("3 S 15 400 16 400 17 400 18 400 19 400");
//  motorSerial02.println();
}

void func11(OSCMessage *_mes){
  Serial.println("We Got Something on 0");
  
  motorControls01 = ("0 S 0 ");
  
  int motor00 = 0;
  int motor01 = 0;
  int motor02 = 0;
  int motor03 = 0;
  int motor04 = 0;
  
  motorControls01 += motor00;
  motorControls01 += " 1 ";
  motorControls01 += motor01;
  motorControls01 += " 2 ";
  motorControls01 += motor02;
  motorControls01 += " 3 ";
  motorControls01 += motor03;
  motorControls01 += " 4 ";
  motorControls01 += motor04;
  
  Serial.println(motorControls01);
//  motorSerial01.println(motorControls01);
  
 

}

void func12(OSCMessage *_mes){
  Serial.println("We got something on 1");
//  motorSerial01.write("1 S 5 10 6 10 7 10 8 10 9 10");
//  motorSerial01.println();

}

void func13(OSCMessage *_mes){
  Serial.println("We got something on 2");
//  motorSerial02.write("2 S 10 10 11 10 12 10 13 10 14 10");
//  motorSerial02.println();

}

void func14(OSCMessage *_mes){
  Serial.println("We got something on 3");
//  motorSerial02.write("3 S 15 10 16 10 17 10 18 10 19 10");
//  motorSerial02.println();
}

void motorTest01(OSCMessage *_mes){
  Serial.println("The mainframe is contacting us");
  motorControls01 = "0 S";
  motorControls02 = "0 S";
//  int motor00 = _mes->getArgInt32(0);
//  int motor01 = _mes->getArgInt32(1);
//  int motor02 = _mes->getArgInt32(2);
//  int motor03 = _mes->getArgInt32(3);
//  int motor04 = _mes->getArgInt32(4);
//  int motor05 = _mes->getArgInt32(5);
//  int motor06 = _mes->getArgInt32(6);
//  int motor07 = _mes->getArgInt32(7);
//  int motor08 = _mes->getArgInt32(8);
//  int motor09 = _mes->getArgInt32(9);
//  int motor10 = _mes->getArgInt32(10);
//  int motor11 = _mes->getArgInt32(11);
//  int motor12 = _mes->getArgInt32(12);
//  int motor13 = _mes->getArgInt32(13);
//  int motor14 = _mes->getArgInt32(14);
//  int motor15 = _mes->getArgInt32(15);
//  int motor16 = _mes->getArgInt32(16);
//  int motor17 = _mes->getArgInt32(17);
//  int motor18 = _mes->getArgInt32(18);
//  int motor19 = _mes->getArgInt32(19);
  
  int motor00 = 200;
  int motor01 = 200;
  int motor02 = 200;
  int motor03 = 200;
  int motor04 = 200;
  int motor05 = 200;
  int motor06 = 200;
  int motor07 = 200;
  int motor08 = 200;
  int motor09 = 200;
  int motor10 = 200;
  int motor11 = 200;
  int motor12 = 200;
  int motor13 = 200;
  int motor14 = 200;
  int motor15 = 200;
  int motor16 = 200;
  int motor17 = 200;
  int motor18 = 200;
  int motor19 = 200;
  
  motorControls01 += " 0 ";
  motorControls01 += motor00;
  motorControls01 += " 1 ";
  motorControls01 += motor01;
  motorControls01 += " 2 ";
  motorControls01 += motor02;
  motorControls01 += " 3 ";
  motorControls01 += motor03;
  motorControls01 += " 4 ";
  motorControls01 += motor04; 
  motorControls01 += " 5 ";
  motorControls01 += motor05;
  motorControls01 += " 6 ";
  motorControls01 += motor06;
  motorControls01 += " 7 ";
  motorControls01 += motor07;
  motorControls01 += " 8 ";
  motorControls01 += motor08;
  motorControls01 += " 9 ";
  motorControls01 += motor09;
  motorControls01 += " z";

  motorControls02 += " 10 ";
  motorControls02 += motor10;
  motorControls02 += " 11 ";
  motorControls02 += motor11;
  motorControls02 += " 12 ";
  motorControls02 += motor12;
  motorControls02 += " 13 ";
  motorControls02 += motor13;
  motorControls02 += " 14 ";
  motorControls02 += motor14;
  motorControls02 += " 15 ";
  motorControls02 += motor15;
  motorControls02 += " 16 ";
  motorControls02 += motor16;
  motorControls02 += " 17 ";
  motorControls02 += motor17;
  motorControls02 += " 18 ";
  motorControls02 += motor18;
  motorControls02 += " 19 ";
  motorControls02 += motor19;
  motorControls02 += " z";

  
  
  motorSerial01.begin(57600);
  Serial.println(motorControls01);
  motorSerial01.println(motorControls01);
  motorSerial01.end();
  
  motorSerial02.begin(57600);
  Serial.println(motorControls02);
  motorSerial02.println(motorControls02);
  motorSerial02.end();
  
  
}

void motorTest02(OSCMessage *_mes){
  Serial.println("The mainframe is contacting us");
  motorControls01 = "0 S";
  motorControls02 = "0 S";
//  int motor00 = _mes->getArgInt32(0);
//  int motor01 = _mes->getArgInt32(1);
//  int motor02 = _mes->getArgInt32(2);
//  int motor03 = _mes->getArgInt32(3);
//  int motor04 = _mes->getArgInt32(4);
//  int motor05 = _mes->getArgInt32(5);
//  int motor06 = _mes->getArgInt32(6);
//  int motor07 = _mes->getArgInt32(7);
//  int motor08 = _mes->getArgInt32(8);
//  int motor09 = _mes->getArgInt32(9);
  int motor10 = _mes->getArgInt32(0);
  int motor11 = _mes->getArgInt32(1);
  int motor12 = _mes->getArgInt32(2);
  int motor13 = _mes->getArgInt32(3);
  int motor14 = _mes->getArgInt32(4);
  int motor15 = _mes->getArgInt32(5);
  int motor16 = _mes->getArgInt32(6);
  int motor17 = _mes->getArgInt32(7);
  int motor18 = _mes->getArgInt32(8);
  int motor19 = _mes->getArgInt32(9);
  
//  int motor00 = 0;
//  int motor01 = 0;
//  int motor02 = 0;
//  int motor03 = 0;
//  int motor04 = 0;
//  int motor05 = 0;
//  int motor06 = 0;
//  int motor07 = 0;
//  int motor08 = 0;
//  int motor09 = 0;
//  int motor10 = 0;
//  int motor11 = 0;
//  int motor12 = 0;
//  int motor13 = 0;
//  int motor14 = 0;
//  int motor15 = 0;
//  int motor16 = 0;
//  int motor17 = 0;
//  int motor18 = 0;
//  int motor19 = 0;
// 
// 
//  motorControls01 += " 0 ";
//  motorControls01 += motor00;
//  motorControls01 += " 1 ";
//  motorControls01 += motor01;
//  motorControls01 += " 2 ";
//  motorControls01 += motor02;
//  motorControls01 += " 3 ";
//  motorControls01 += motor03;
//  motorControls01 += " 4 ";
//  motorControls01 += motor04; 
//  motorControls01 += " 5 ";
//  motorControls01 += motor05;
//  motorControls01 += " 6 ";
//  motorControls01 += motor06;
//  motorControls01 += " 7 ";
//  motorControls01 += motor07;
//  motorControls01 += " 8 ";
//  motorControls01 += motor08;
//  motorControls01 += " 9 ";
//  motorControls01 += motor09;
//  motorControls01 += " z";

  motorControls02 += " 10 ";
  motorControls02 += motor10;
  motorControls02 += " 11 ";
  motorControls02 += motor11;
  motorControls02 += " 12 ";
  motorControls02 += motor12;
  motorControls02 += " 13 ";
  motorControls02 += motor13;
  motorControls02 += " 14 ";
  motorControls02 += motor14;
  motorControls02 += " 15 ";
  motorControls02 += motor15;
  motorControls02 += " 16 ";
  motorControls02 += motor16;
  motorControls02 += " 17 ";
  motorControls02 += motor17;
  motorControls02 += " 18 ";
  motorControls02 += motor18;
  motorControls02 += " 19 ";
  motorControls02 += motor19;
  motorControls02 += " z";

  motorSerial01.begin(57600);
  Serial.println(motorControls01);
  motorSerial01.println(motorControls01);
  motorSerial01.end();
  
  motorSerial02.begin(57600);
  Serial.println(motorControls02);
  motorSerial02.println(motorControls02);
  motorSerial02.end();
  
}


