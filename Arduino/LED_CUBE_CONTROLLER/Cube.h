#ifndef Cube_h
#define Cube_h

#include "Arduino.h"

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

 /*
  * NOTES
  * 
  * LATCH and ADLATCH control the output state. The chip has an Output Enable (OE) pin that is active low, and needs to be toggled in order for data to be displayed. This needs to be fixed before the driver will work.
  * The output registers also all have a common clock, this is what switches the data over from the internal registers to the output registers. Again, I am not sure which pin this is.
  */

class Cube{
  public:
    Cube();
    void resetCube();//Resets all outputs of the cube to 0, all registers to 0, and presets the pins.
    void writePorts();
    void clk();//Clocks our shift registers by one pulse.
    void setLayer(byte layer);
    void writeLayer();
    void pushToOutput();//Pushes contents of internal registers to output registers.
    void writeCube();//Writes the current cube data to all layers of the cube.
    byte setBit(byte b, byte bitLocation, byte state);

    byte **CUBE_DATA;//Pointer CUBE_DATA holds the state of every LED
    
  private:
    
    //These hold the state of portB and PortC
    byte PORTB_state = B0000000;//Initialize all to low
    byte PORTC_state = 0;//Initialized to ON
    byte currentLayer = 0;//Initialized to first layer
};

#endif Cube_h
