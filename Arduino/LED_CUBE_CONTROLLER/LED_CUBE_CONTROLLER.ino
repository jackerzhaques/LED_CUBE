#include "Cube.h"

Cube *cube;

void setup() {
  // put your setup code here, to run once:
  cube = new Cube();
  for(int layer = 0; layer < 8; layer++){
    for(int row = 0; row < 8; row++){
      cube->CUBE_DATA[layer][row] = 0xFF;
    }
  }
  /*
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);*/
}

void loop() {
  for(int i = 0; i < 100000; i+= 250){
    for(int layer = 0; layer < 8; layer++){
      cube->setLayer(layer);
      cube->writeLayer();
      cube->pushToOutput();
      delayMicroseconds(10000 - i);
    }
  }
  /*
  
  // put your main code here, to run repeatedly:
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(A2, LOW);
  delay(100);
  digitalWrite(A1, LOW);
  delay(100);
  digitalWrite(A0, LOW);
  delay(100);
  digitalWrite(6,HIGH);
  delay(100);

  digitalWrite(2, HIGH);
  for(int i = 0; i < 64; i++){
    digitalWrite(3, LOW);
    delay(1);
    digitalWrite(3, HIGH);
    delay(1);
    //digitalWrite(5, LOW);
    //delay(100);
  }

  digitalWrite(5, 1);
  delay(100);
  digitalWrite(5, 0);
  delay(100);
  digitalWrite(5, 1);
  delay(100);
  
  delay(3000);*/
}

//Layer select is a decoder: 74238

//Output 2 goes to pin 14, data
//Output 3 goes to pin 11, Shift Register Clock Input
//Output 4 goes to pin 10, Master Reset
//Output 5 goes to pin 12, Storage Register Clock Input/Output Enable Active Low
//Output 6 goes to decoder pin 6. layer enable
//ANALOG 0 goes to decore pin 3, A2
//ANALOG 1 goes to decoder pin 2, A1
//ANALOG 2 goes to decoder pin 1, A0


