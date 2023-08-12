#include  "HardwareSerial.h"
#ifndef   SevenSegment_h
#define   SevenSegment_h
#include  <Adafruit_NeoPixel.h>

class SevenSegment {

//===================================================================================
  private:
//===================================================================================

    // Structure Of Segment LED Pixel Types
    struct _segboundary {
      uint8_t start;
      uint8_t stop;
    };

    // Digits
    struct _digit {
      _segboundary segment[7];
    };

    // Variables
    uint8_t   _pin;           // Pin Number On the Microcontroller
    uint8_t   _numpixels;     // Number Of Led's On the Strip
    uint8_t   _numdisplays;   // The Number Of Digit Units Created From LED Strip
    uint8_t   _segsize;       // Segment Size

    // Colors For The Usage
    uint32_t  _baseColor;     // Base Color
    uint32_t  _opponentColor; // Opponent Color
    uint32_t  _refereeColor;  // Referee Color

    // Adafruit_NeoPixel object
    Adafruit_NeoPixel _neopixel;

//-----------------------------------------------------------------------------------
//  Prepare Boundaries
//-----------------------------------------------------------------------------------

    void _boundaries() {

      // To Store The Position Of The Assignment
      unsigned int start_position = 0;
      unsigned int stop_position = start_position + _segsize;

      // Loop Through Digits
      for (int i = 0; i < _numdisplays; i++) {
        // Main Assign Loop Segment 1
        for (uint8_t j = 0; j < 7; j++) {
          // Display Segments
          digits[i].segment[j].start = start_position;
          digits[i].segment[j].stop = stop_position;
          start_position = start_position + _segsize;
          stop_position = start_position + _segsize;
        }
      }

    }

//===================================================================================
  public:
//===================================================================================
//  Array of _digit objects
//-----------------------------------------------------------------------------------
    
    _digit*   digits;

//-----------------------------------------------------------------------------------
//  Constructor : SevenSegment
//-----------------------------------------------------------------------------------
    
    SevenSegment(uint8_t pin, uint8_t displays, uint8_t pixelcount) : _neopixel(pixelcount, pin, NEO_GRB + NEO_KHZ800) {
      
      // Assign Pins & Do Calculations
      _pin          = pin;
      _numdisplays  = displays;
      _numpixels    = pixelcount;
      _segsize      = _numpixels / (_numdisplays * 7);

      // Allocate memory for the digits array
      digits = new _digit[_numdisplays];

      // Additional initialization code for the Adafruit_NeoPixel object
      _neopixel.begin();
      _neopixel.show();

    }

//-----------------------------------------------------------------------------------
//  Constructor : Clearing Segment
//-----------------------------------------------------------------------------------

    ~SevenSegment() {
      // Release the memory for the digits array
      delete[] digits;
    }

//-----------------------------------------------------------------------------------
//  Begin
//-----------------------------------------------------------------------------------
    
    void begin() {

      // Set Bounderies
      _boundaries();

      // Start Pixels
      _neopixel.begin();

      // Clearing Pixels
      _neopixel.clear();

      // Display
      _neopixel.show();

    }

//-----------------------------------------------------------------------------------
//  Color
//-----------------------------------------------------------------------------------
    
    void color(uint8_t r, uint8_t g, uint8_t b) {
      _baseColor = _neopixel.Color(r, g, b);
    }

//-----------------------------------------------------------------------------------
//  Set Pixel Color
//-----------------------------------------------------------------------------------
    
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
      _neopixel.setPixelColor(n, r, g, b);
    }

//-----------------------------------------------------------------------------------
//  Clear The Buffer From The Strip
//-----------------------------------------------------------------------------------
    
    void clear() {
      _neopixel.clear();
    }

//-----------------------------------------------------------------------------------
//  Show Buffer On LED Strip
//-----------------------------------------------------------------------------------
    
    void show() {
      _neopixel.show();
    }

//-----------------------------------------------------------------------------------
//  Generate Shape Byte For Each Segment On A Signle Display
//-----------------------------------------------------------------------------------
    
    uint8_t shape(bool a, bool b, bool c, bool d, bool e, bool f, bool g) {

      // Buffer Data
      uint8_t enable = 0;

      // Setting Up
      if(a == true) { bitSet(enable, 1); } else { bitClear(enable, 1); }
      if(b == true) { bitSet(enable, 2); } else { bitClear(enable, 2); }
      if(c == true) { bitSet(enable, 3); } else { bitClear(enable, 3); }
      if(d == true) { bitSet(enable, 4); } else { bitClear(enable, 4); }
      if(e == true) { bitSet(enable, 5); } else { bitClear(enable, 5); }
      if(f == true) { bitSet(enable, 0); } else { bitClear(enable, 0); }
      if(g == true) { bitSet(enable, 6); } else { bitClear(enable, 6); }

      // Return The Value
      return enable;

    }

//-----------------------------------------------------------------------------------
//  Convert A Number To Shape
//-----------------------------------------------------------------------------------
    
    uint8_t numberToShape(uint8_t number) {

      // Buffer Data
      uint8_t enable = 0;

      // Make Desition
      switch(number) {
        case 0:
          return shape(true, true, true, true, true, true, false);
        case 1:
          return shape(false, true, true, false, false, false, false);
        case 2:
          return shape(true, true, false, true, true, false, true);
        case 3:
          return shape(true, true, true, true, false, false, true);
        case 4:
          return shape(false, true, true, false, false, true, true);
        case 5:
          return shape(true, false, true, true, false, true, true);
        case 6:
          return shape(true, false, true, true, true, true, true);
        case 7:
          return shape(true, true, true, false, false, false, false);
        case 8:
          return shape(true, true, true, true, true, true, true);
        case 9:
          return shape(true, true, true, true, false, true, true);
      }

      // Return
      return 0;

    }

//-----------------------------------------------------------------------------------
//  Write On Segment
//-----------------------------------------------------------------------------------
    
    void writeOneSegment(_digit& digit, uint8_t segment, uint8_t brightness, uint8_t r, uint8_t g, uint8_t b) {

      // The Light Intensity
      _neopixel.setBrightness(brightness);

      // Loop Within The segment Pixels
      for(int j = digit.segment[segment].start; j < digit.segment[segment].stop; j++) {
        _neopixel.setPixelColor(j, _neopixel.Color(r, g, b));
      }

    }

//-----------------------------------------------------------------------------------
//  Write Shape To Neo Pixel
//-----------------------------------------------------------------------------------
    
    void writeSingleDisplayShape(_digit& digit, uint8_t shape, uint8_t brightness, uint8_t r, uint8_t g, uint8_t b) {

      // The Light Intensity
      _neopixel.setBrightness(brightness);

      // Loop Through All Segments
      for (int i = 0; i < 7; i++) {

        // Loop Within The segment Pixels
        for (int j = digit.segment[i].start; j < digit.segment[i].stop; j++) {

          // Put Colors
          if (bitRead(shape, i) == 1) {
            _neopixel.setPixelColor(j, _neopixel.Color(r, g, b));
          }
          else {
            _neopixel.setPixelColor(j, _neopixel.Color(0, 0, 0));
          }
        }
      }

      _neopixel.show();
    }

//-----------------------------------------------------------------------------------
//  Write Number To Display
//-----------------------------------------------------------------------------------
    
    void writeNumber(unsigned int number, uint8_t brightness, uint8_t r, uint8_t g, uint8_t b) {

      // Loop to display the numbers
      for(int i=_numdisplays-1; i>=0; i--) {

        // Write To Seven Segment
        writeSingleDisplayShape(digits[i], numberToShape(number%10), brightness, r, g, b);

        // Number
        number /= 10;

      }

    }

//-----------------------------------------------------------------------------------
//  Fade In
//-----------------------------------------------------------------------------------

    void fadein(uint8_t min, uint8_t max) {

      for(int i=min; i<max; i++) {
        _neopixel.setBrightness(i);
        _neopixel.show();
        delay(1);
      }

    }

//-----------------------------------------------------------------------------------
//  Fade Out
//-----------------------------------------------------------------------------------

    void fadeout(uint8_t max, uint8_t min) {

      for(int i=max; i>min; i--) {
        _neopixel.setBrightness(i);
        _neopixel.show();
        delay(1);
      }

    }

//-----------------------------------------------------------------------------------

};

#endif