#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

#define levelsensor A0

RF24 radio(7,8); 

unsigned int level;

unsigned char ADDRESS1[5] = {0xb2, 0x43, 0x88, 0x99, 0x45};

void setup() {
  Serial.begin(9600);
  pinMode(levelsensor,INPUT);
  radio.begin();
  radio.setRetries(15,15);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(ADDRESS1);
  radio.openReadingPipe(0,ADDRESS1);
  radio.stopListening();
}

void loop() {
  level = analogRead(levelsensor);
  radio.write(&level,sizeof(level));
  Serial.print("Level - ");
  Serial.println(level);
  delay(100);

  }


