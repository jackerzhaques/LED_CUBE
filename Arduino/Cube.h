#ifndef Cube_h
#define Cube_h

#include "Arduino.h"

/*
 * We define...
 * PORTB
 * PIN 8, DATA
 * PIN 9, CLOCK
 * PIN 10, RESET
 * PIN 11, LATCH
 * PIN 12, ADLATCH
 * 
 * PORTC
 * ANALOG0, AD1 
 * ANALOG1, AD2
 * ANALOG2, AD3
 */

class Cube{
  public:
    Cube();
    void resetCube();//Resets all outputs of the cube to 0, all registers to 0, and presets the pins.
    void writePorts();
    void clk();//Clocks our shift registers by one pulse.
    void setLayer(byte layer);
    void writeLayer();
    byte setBit(byte b, byte bitLocation, byte state);

  private:
    //Pointer CUBE_DATA holds the state of every LED
    byte **CUBE_DATA;
    //These hold the state of portB and PortC
    byte PORTB_state = B00000110;//Data low, Clock high, Reset high, latch low, Adlatch low
    byte PORTC_state = 0;//Initialized to ON
    byte currentLayer = 0;//Initialized to first layer
};

#endif Cube_h
