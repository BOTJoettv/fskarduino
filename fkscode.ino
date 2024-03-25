int image_data[] = {0,1,1,1,1,0,0,0,1,0,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,1,0};

void setup() {
  pinMode(12, OUTPUT);
}

void loop() {
  for (int i = 0; i < 54; i += 1){
    if (image_data[i] == 0)  {
      digitalWrite(12, LOW);
      //time passed should be about 47 cycles
    }
    else{
      digitalWrite(12, HIGH);
      //time passed should be about 57 cycles
    }
  }
  delay(5000);
}
