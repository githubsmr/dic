#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

RF24 radio(9,10);

byte pip;
byte newdata;
int rx;
int rx1;
int rx2;

unsigned char ADDRESS2[1]= {0xb2};  
unsigned char ADDRESS3[1]= {0xb3};  
unsigned char ADDRESS4[1]= {0xb4};  
unsigned char ADDRESS5[1]= {0xb5}; 

unsigned char ADDRESS1[5]  = 
{
   0xb1,0x43,0x88,0x99,0x45
}; 

unsigned char ADDRESS0[5]  = 
{
  0xb0,0x43,0x88,0x99,0x45
};

void setup() {
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(ADDRESS0);
  radio.openReadingPipe(0,ADDRESS0);
  radio.openReadingPipe(1,ADDRESS1);
  radio.openReadingPipe(2,ADDRESS2);
  radio.openReadingPipe(3,ADDRESS3);
  radio.openReadingPipe(4,ADDRESS4);
  radio.openReadingPipe(5,ADDRESS5);

  radio.startListening();
  delay(1000);
}

void loop() {
  if ( radio.available(&pip) )
  {
   
    radio.read(&rx,sizeof(rx));
    newdata = 1;
    Serial.println(pip );
  }
  if(newdata == 1)
  {
    newdata = 0;
    if(pip==1)
    {
      rx1 = rx;
      Serial.print("Rx1 = ");
      Serial.println(rx1);
    }
    if(pip==2)
    {
      rx2 = rx;
      Serial.print("Rx2 = ");
      Serial.println(rx2);
    
  }

  if(rx1 > 80)
  {
    if(rx2 < 400)
    {
      digitalWrite(4,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(5,LOW);
      Serial.println("Water Pump turned ON");
    }
    else{
      digitalWrite(4,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(5,LOW);
    }
  }
  else
  {
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    Serial.println("Water Pump turned Off");
  }
  delay(100);
}
}
