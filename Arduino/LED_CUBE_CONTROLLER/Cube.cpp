#include "Cube.h"

/*
 * We define...
 * PORTB
 * PIN 8, DATA
 * PIN 9, CLOCK
 * PIN 10, Reset Active Low
 * PIN 11, Storage Register Clock Input/Output Enable Active Low
 * PIN 12, Layer Enable Active High
 * 
 * PORTC
 * ANALOG0, AD1 
 * ANALOG1, AD2
 * ANALOG2, AD3
 */

Cube::Cube(){
  //Initialize PORTB
  DDRB = 0xFF;//Set the pin state of Port B to output, pins 8-13
  PORTB = PORTB_state;//Set pins all to 0
  //Initialize PORTC
  DDRC = 0xFF;//Set the pin states of Analog pins 0-5 to outputs
  PORTC = PORTC_state;//Set pins all to 0 excedpt RX and TX

  //Initialize CUBE_DATA
  CUBE_DATA = new byte*[8];//Initialize CUBE_DATA to point to 8 addresses
  for(byte z = 0; z < 8; z++){//Loop through each address
    CUBE_DATA[z] = new byte[8];//Initialize that address to an address of 8 bytes, now the pointer is an 8x8 array
    for(int c = 0; c < 8; c++){//Loop through each new byte
      CUBE_DATA[z][c] = 0x00;//Initialize that byte to 0
    }
  }

  //Initialize the cube to all LEDs off
  resetCube();
}

void Cube::resetCube(){
  //First set the clear pin to 0, clears all shift registers
  bitClear(PORTB_state, 2);//PORTB_state = setBit(PORTB_state, 3, 0);//Set bit 3 (RESET) to 0, leave all other bits
  PORTB = PORTB_state;//Now write the port state to the output registers
  //Now reset the clear pin to HIGH
  bitSet(PORTB_state, 2);//PORTB_state = setBit(PORTB_state, 3, 1);//Set bit 3 (RESET) to 1, leave all other bits.
  PORTB = PORTB_state;//Write the state to the output registers.

  //Now to ensure the LEDs show nothing, we will write both the outpet enable (bit 4) and layer enable (bit 5) to HIGH and LOW
  bitSet(PORTB_state, 3);//PORTB_state = setBit(PORTB_state, 4, 1);//Set the state of LATCH to low
  bitClear(PORTB_state, 5);//PORTB_state = setBit(PORTB_state, 5, 0);
  PORTB = PORTB_state;//Write the outputs
}

byte Cube::setBit(byte b, byte bitLocation, byte state){
  //Thank you to Leandros from stack exchange for this expression.
  b ^= (-state ^ b) & (1 << bitLocation);
  return b;
}

void Cube::clk(){
  //Clock pin is 9, so bit is 1
  //Clock is falling edge trigger
  //So first we make sure the clock is high
  bitSet(PORTB_state, 1);//PORTB_state = setBit(PORTB_state, 1, 1);
  PORTB = PORTB_state;//Write our state to the port
  //Now trigger the clock (set to 0)
  bitClear(PORTB_state, 1);//PORTB_state = setBit(PORTB_state, 1, 0);
  PORTB = PORTB_state;//Write our state to the port.
  //Now preset the pin to HIGH again
  bitSet(PORTB_state, 1);//PORTB_state = setBit(PORTB_state, 1, 1);
  PORTB = PORTB_state;//Write our state to the port.
}

void Cube::writePorts(){
  PORTB = PORTB_state;
  PORTC = PORTC_state;
}

void Cube::setLayer(byte layer){
  currentLayer = layer;//Set the internal layer to the new layer
  PORTC_state = layer;//Set the PORTC state byte to this value, it will auto-convert to binary
  PORTC = PORTC_state;//Write PORTC_state to PORTC.
}

void Cube::writeLayer(){
  //Loop through all 8 bytes
  for(byte col = 0; col < 8; col++){
    //Each bit in the byte has to be loaded into the shift registers in order
    byte columnData = CUBE_DATA[currentLayer][col];
    for(byte row = 0; row < 8; row++){
      //Set the data bit
      byte dataBit = ((columnData >> row) & 0x01);//Shift the byte by how many bits we need, this will put that bit in the 0 spot. Then AND it with 0b00000001, so it sets our first bit in the byte to the bit we want.
      PORTB_state = setBit(PORTB_state, 0, dataBit);//Set this bit in our state variable
      PORTB = PORTB_state;//Write our data pin high
      //Now clock our shift registers
      clk();
    }
  }
}

void Cube::pushToOutput(){
  //Shift the outputs from the storage register to the output register
  //Output register clock is bit 4
  //Decoder enable pin is bit 5
  bitClear(PORTB_state,3);//PORTB_state = setBit(PORTB_state, 4, 1);
  PORTB = PORTB_state;
  bitSet(PORTB_state,3);//PORTB_state = setBit(PORTB_state, 4, 0);
  bitSet(PORTB_state,4);//PORTB_state = setBit(PORTB_state, 5, 1);
  PORTB = PORTB_state;
}

void Cube::writeCube(){
  //Loop through each layer, write to the layer, and push to the output.
  for(int layer = 0; layer < 8; layer++){
    setLayer(layer);
    writeLayer();
    pushToOutput();
  }
}

