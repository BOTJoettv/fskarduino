#define CYCLES_TO_NS(cycles)  ((cycles)*(1E9/F_CPU))
#include <limits.h>

const int pulsePin = A0;

uint32_t pulseCur;
int pulsetime;
float frequency = 0;
int StartTime = millis();
int nextData;
int receive_data[54];
int dindex = 0;
int loopcycles;
int lastCycle ;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ARM_DEMCR |= ARM_DEMCR_TRCENA;
  ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
  attachInterrupt(digitalPinToInterrupt(23), myInterrupt, RISING);
  ARM_DWT_CYCCNT = 0;
  lastCycle = 0;
}

void loop() {
  loopcycles = ARM_DWT_CYCCNT;
  if(millis() - StartTime == 100){//only useful for testing
    StartTime = millis();
    Serial.print(frequency);
    Serial.println(" Hz");
  }
  if(frequency >= 425000000 && dindex < 54){
    receive_data[dindex] = 1;
    dindex = dindex + 1;
  }
  else if(frequency >= 400000000 && dindex < 54){
    receive_data[dindex] = 0;
    dindex = dindex + 1;
  }
  delayNanoseconds(CYCLES_TO_NS(200-(loopcycles-ARM_DWT_CYCCNT))); //constant delay (idk how many nanoseconds, probably 250)
}

void myInterrupt(){
  if(ARM_DWT_CYCCNT < (INT_MAX - 100)){
    pulsetime = CYCLES_TO_NS(ARM_DWT_CYCCNT - lastCycle);  
    frequency=1000000000/pulsetime;
  }
  else{
    ARM_DWT_CYCCNT = 0;
  }
  lastCycle = ARM_DWT_CYCCNT;
}