//============================================================
//  Setup Digit
//============================================================

  void setupSSDisplay(Digit *number) {
    
    // Display Size Of The Seven Segment
    Serial.println(" -> Segment Size : " + String(SEGSIZE));

    // To Store The Position Of The Assignment
    unsigned int  start_position  = 0;
    unsigned int  stop_position   = start_position + SEGSIZE;

    // Loop Through Digits
    for(int i=0; i<NUMDIGITS; i++) {
      // Main Assign Loop Segment 1
      for(uint8_t j=0; j<SEGSIZE; j++) {
        // Display Segments
        Serial.println(" -> [" + String(i+1) + "] Start Position " + String(start_position) + ", End Position " + String(stop_position));
        digit[i].segments[j].start = start_position;
        digit[i].segments[j].stop  = stop_position;
        start_position = start_position + SEGSIZE;
        stop_position = start_position + SEGSIZE;
      }
    }

  }

//============================================================
//  Write The Number To The Segment
//============================================================

  void writeNumber(unsigned int number, uint8_t brightness, uint8_t r, uint8_t g, uint8_t b) {

    // Loop to display the numbers
    for(int i=0; i<NUMDIGITS; i++) {
      writeShape(digit[i], digitToShape(number % 10), brightness, r, g, b);
      number /= 10;
    }

  }

//============================================================
//  Enable The Segments
//============================================================

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

//============================================================
//  DigitToShape
//============================================================

  uint8_t digitToShape(uint8_t number) {

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

//============================================================
//  Write Shape To Display
//============================================================

  void writeShape(Digit &digit, uint8_t shape, uint8_t brightness, uint8_t r, uint8_t g, uint8_t b) {

    // The Light Intensity
    pixels.setBrightness(brightness);

    // Loop Through All Segments
    for(int i=0; i<7; i++) {
      // Loop Within The segment Pixels
      for(int j = digit.segments[i].start; j < digit.segments[i].stop; j++) {
        // Put Colors
        if(bitRead(shape, i) == 1) {
          pixels.setPixelColor(j, pixels.Color(r, g, b));
        } else {
          pixels.setPixelColor(j, pixels.Color(0, 0, 0));
        }
      }
    }

  }

//============================================================
//  Write Single Segment
//============================================================

  void writeOneSegment(Digit &digit, uint8_t segment, uint8_t brightness, uint8_t r, uint8_t g, uint8_t b) {

    // The Light Intensity
    pixels.setBrightness(brightness);

    // Loop Within The segment Pixels
    for(int j = digit.segments[segment].start; j < digit.segments[segment].stop; j++) {
      pixels.setPixelColor(j, pixels.Color(r, g, b));
    }

  }

//============================================================
//  Clearing The Display
//============================================================

  void clear() {

    // Clear Pixels
    pixels.clear();

  }

//============================================================
//  Show The Display
//============================================================

  void show() {

    // Show Pixels
    pixels.show();

  }