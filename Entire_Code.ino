#include <SoftwareSerial.h>
const int SW1 = 17; // SW Joystick
const int X1 = 0; // VRx Joystick
const int Y1 = 1; // VRy Joystick
int SW=0; //Switch State
int X=0; //X axis pos
int Y=0; //Y axis pos

const int UFRT = 33;//ultrasonic sensors
const int UFRE = 35;//deep brown - trig    light brown - echo     orange +     white --
const int UFLT = 37;// deep blue-trig       light blue-echo       deep green-pos    light green-neg
const int UFLE = 39;//
const int URT = 41;//deep brown - trig    light brown - echo     orange +     white --
const int URE = 43;
const int ULT = 45;// deep blue-trig       light blue-echo       deep green-pos    light green-neg
const int ULE = 47;
const int UBT = 49;// deep blue-trig       light blue-echo       deep green-pos    light green-neg
const int UBE = 51;
int F1=0;
int F2=0;
int R=0;
int L=0;
int B=0;
int a=0;

const int D1 = 22;//communication ports
const int D2 = 24;//send ports
const int D3 = 26;
const int D4 = 28;
const int D5 = 30;
const int D6 = 32;//receive ports
const int D7 = 34;
const int D8 = 36;
int S1=0;
int S2=0;
int S3=0;
int S4=0;
int S5=0;
int S6=0;
int S7=0;
int S8=0;
int ip=0;
int op=0;
int code=0;

const int T1=13;//Tilt Sensors
const int T2=14;
int tilt1=0;
int tilt2=0;

const int IR1=15;//IR Sensors
const int IR2=16;
int IRF=0;
int IRB=0;

int crash=0;
int rough=0;

int SND1=0;
int SND2=0;
int SND3=0;
SoftwareSerial SIM900A(10,11); // TX | RX
void setup() 
{
  pinMode(SW, INPUT_PULLUP);
  pinMode(UFLT, OUTPUT);
  pinMode(UFRT, OUTPUT);
  pinMode(ULT, OUTPUT);
  pinMode(URT, OUTPUT);
  pinMode(UBT, OUTPUT);
  pinMode(UFLE, INPUT);
  pinMode(UFRE, INPUT);
  pinMode(ULE, INPUT);
  pinMode(URE, INPUT);
  pinMode(UBE, INPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(T1, INPUT);
  pinMode(T2, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(SND1, OUTPUT);
  pinMode(SND2, OUTPUT);
  pinMode(SND3, OUTPUT);
  Serial.begin(9600);
  while(!Serial);
  // start communication with the SIM900A in 9600
  SIM900A.begin(9600); 
  Serial.println("SIM900A Start.");
  delay(1000);
  Serial.println("Setup is complete. Wheelchair has booted.");
}

void loop() 
{
  ir();
  ultrasonic();
  tilted();
  printStatus();
  checkStatus();
  debug();
  printStatus();
}

void emergency()
{
    digitalWrite(D1,HIGH);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,HIGH);
    digitalWrite(D4,HIGH);
    digitalWrite(D5,HIGH);
  sendMessage();
  call();
}

void ir()
{
  
}

void ultrasonic()
{
    digitalWrite(UFLT, LOW);
    delayMicroseconds(2);
    digitalWrite(UFLT, HIGH);
    delayMicroseconds(10);
    digitalWrite(UFLT, LOW);
    F1 = pulseIn(UFLE, HIGH);

    digitalWrite(UFRT, LOW);
    delayMicroseconds(2);
    digitalWrite(UFRT, HIGH);
    delayMicroseconds(10);
    digitalWrite(UFRT, LOW);
    F2 = pulseIn(UFRE, HIGH);

    digitalWrite(ULT, LOW);
    delayMicroseconds(2);
    digitalWrite(ULT, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULT, LOW);
    L = pulseIn(ULE, HIGH);

    digitalWrite(URT, LOW);
    delayMicroseconds(2);
    digitalWrite(URT, HIGH);
    delayMicroseconds(10);
    digitalWrite(URT, LOW);
    R = pulseIn(URE, HIGH);

    digitalWrite(UBT, LOW);
    delayMicroseconds(2);
    digitalWrite(UBT, HIGH);
    delayMicroseconds(10);
    digitalWrite(UBT, LOW);
    B = pulseIn(UBE, HIGH);
    if(F1<4000 && F1>0)
    {
      a=1;
    }
    else if(F2<4000 && F2>0)
    {
      a=2;
    }
    else if(L<4000)
    {
      a=3;
    }
    else if(R<4000)
    {
      a=4;
    }
    else if(B<4000)
    {
      a=5;
    }
    else
    {
      a=6;
    }
    if(F1<4000 || F2<4000 || L<4000 || R<4000 || B<4000)
    {
      digitalWrite(SND1,HIGH);
      digitalWrite(SND2,LOW);
      digitalWrite(SND3,LOW);
    }
    else if(F1<4000 || F2<4000 || L<4000 || R<4000 || B<4000)
    {
      digitalWrite(SND1,LOW);
      digitalWrite(SND2,HIGH);
      digitalWrite(SND3,LOW);
    }
    else if(F1<4000 || F2<4000 || L<4000 || R<4000 || B<4000)
    {
      digitalWrite(SND1,LOW);
      digitalWrite(SND2,LOW);
      digitalWrite(SND3,HIGH);
    }
    else
    {
      digitalWrite(SND1,LOW);
      digitalWrite(SND2,LOW);
      digitalWrite(SND3,LOW);
    }
}

void tilted()
{
  if(digitalRead(T1)==LOW)
   tilt1=1;
  else
   tilt1=0;
  if(digitalRead(T2)==LOW)
   tilt2=1;
  else
   tilt2=0;
}

void sendMessage()
{
    String Message="Wheelchair has met with an accident. Location:"; 
    Serial.println ("System is in Emergency Mode");
    SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(1000);
    SIM900A.println("AT+CMGS=\"+917044332775\"\r"); //Mobile phone number to send message
    delay(1000);
    SIM900A.println(Message);// Messsage content
    delay(100);
    Serial.println ("Message Sent.");
    SIM900A.println((char)26);// ASCII code of CTRL+Z
    delay(1000);
    Serial.println ("System will try to return to Normal Mode");
}

void call()
{
  SIM900A.println("ATD+917044332775;");
  int x=0;
  Serial.println("Waiting for call disconnection.");
  while(x=0)
  {
    if(digitalRead(SW)==HIGH)
      x=1;
  }
  Serial.println("Call disconnected.");
  SIM900A.println("ATH");
}

 void printStatus()
 {
    /*Serial.print("J_Switch :");
    Serial.print(SW);
    Serial.print("\t");
    Serial.print("X:");
    Serial.print(X);
    Serial.print("\t");
    Serial.print("Y:");
    Serial.print(Y);
    Serial.print("\t");
    Serial.print("M:");
    Serial.print(mov);
    Serial.print("\t");
    Serial.print("T:");
    Serial.print(tilt);
    Serial.println();*/
    //Serial.println(ip);
    Serial.print("F1 ");
    Serial.print(F1);
    Serial.print("    F2 ");
    Serial.print(F2);
    Serial.print("    R ");
    Serial.print(R);
    Serial.print("    L ");
    Serial.print(L);
    Serial.print("    B ");
    Serial.print(B);
    Serial.println();
    //delay(1000);
    
 }
 void checkStatus()
 {
    if(crash==1)//emergency
    {
      code=11111;
      digitalWrite(D1,HIGH);
      digitalWrite(D2,HIGH);
      digitalWrite(D3,HIGH);
      digitalWrite(D4,HIGH);
      digitalWrite(D5,HIGH);
    }
    else if(IRF==1)//edge forward
    {
      code=10011;
      digitalWrite(D1,HIGH);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,HIGH);
    digitalWrite(D5,HIGH);
    }
    else if(IRB==1)//edge backward
    {
      code=10111;
      digitalWrite(D1,HIGH);
    digitalWrite(D2,LOW);
    digitalWrite(D3,HIGH);
    digitalWrite(D4,HIGH);
    digitalWrite(D5,HIGH);
    }
    else if(a==1 || a==2)//forward obstacle
    {
      code=00001;
      digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,HIGH);
    }
    else if(a==5)//backward obstacle
    {
      code=00011;
      digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,HIGH);
    digitalWrite(D5,HIGH);
    }
    else if(a==3)//obstacle left
    {
      code=00111;
      digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);
    digitalWrite(D3,HIGH);
    digitalWrite(D4,HIGH);
    digitalWrite(D5,HIGH);
    }
    else if(a==4)//obstacle right
    {
      code=01111;
      digitalWrite(D1,LOW);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,HIGH);
    digitalWrite(D4,HIGH);
    digitalWrite(D5,HIGH);
    }
    else if(tilt1==1)//Forward Slope
    {
      code=10000;
      digitalWrite(D1,HIGH);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,LOW);
    }
    /*else if(tilt2==1)//Backward Slope
    {
      code=10001;
      digitalWrite(D1,HIGH);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,HIGH);
    }
    else if(rough==1)//rough surface
    {
      code=11000;
      digitalWrite(D1,HIGH);
    digitalWrite(D2,HIGH);
    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,LOW);
    }*/
    else//stable system
    {
      code=00000;
      digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,LOW);
    }
    
  }
 void debug()
 {  
    
    /*digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,LOW);*/
    if(digitalRead(D6)==LOW)
    {
      S6=0;
    }
    else if(digitalRead(D6)==HIGH)
    {
      S6=1;
    }
    if(digitalRead(D7)==LOW)
    {
      S7=0;
    }
    else if(digitalRead(D7)==HIGH)
    {
      S7=1;
    }
    if(digitalRead(D8)==LOW)
    {
      S8=0;
    }
    else if(digitalRead(D8)==HIGH)
    {
      S8=1;
    }
    ip=(S6*100)+(S7*10)+S8;
    if(ip==111)
    {
      emergency();
    }
 }
 
 
