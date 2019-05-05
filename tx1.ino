#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>


RF24 radio(9,10);

volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long loopTime;

void flow () // Interrupt function
{
  flow_frequency++;
  yield();
}

unsigned char ADDRESS0[5] = {0xb1, 0x43, 0x88, 0x99, 0x45};

void setup() {
  Serial.begin(9600);
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH);
  attachInterrupt(0, flow, RISING);
  sei();
  currentTime = millis();
  loopTime = currentTime;
  
  radio.begin();
  radio.setRetries(15,15);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(ADDRESS0);
  radio.openReadingPipe(0,ADDRESS0);
  radio.stopListening();
}

void loop() {
  currentTime = millis();
   if(currentTime >= (loopTime + 1000))
   {
      loopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
   }
      radio.write(&l_hour,sizeof(l_hour));     //send data over nrf
  Serial.println(l_hour);
  delay(100);
  
}

