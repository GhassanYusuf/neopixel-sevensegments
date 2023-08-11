//============================================================
//  Setup Digit
//============================================================

  void initialize() {
    
    // Start Neo Pixel
    setupSSDisplay(digit);

    // Start Pixels
    pixels.begin();

    // Clearing Pixels
    pixels.clear();

    // Display
    pixels.show();

    // Waiting
    waiting();

  }

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
    for(int i=NUMDIGITS-1; i>=0; i--) {

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
        }

        // If Not
        else {
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

//============================================================
//  Rainbow Seven Segment
//============================================================

  // Rainbow effect for a seven-segment display. Pass delay time (in ms) between frames.
  // void rainbowSevenSegment(Digit &digit, uint8_t number) {

  //   // Loop to display the numbers
  //   // for(int i=0; i<NUMDIGITS; i++) {
  //   //   writeShape(_digit[i], digitToShape(number % 10), brightness, r, g, b);
  //   //   number /= 10;
  //   // }
  //   pixels.clear();

  //   for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {

  //     // Display
  //     for(int j = digit.segments[segment].start; j < digit.segments[segment].stop; j++) {
        
  //       // Set the color of each segment
  //       uint32_t color = pixels.gamma32(pixels.ColorHSV(firstPixelHue + (j * 65536 / 7)));

  //       // Set the color of each segment
  //       pixels.setPixelColor(j, color);

  //     }

  //     // Show
  //     pixels.show();

  //     // Waiting
  //     delay(7);

  //   }

  // }

//============================================================
//  Minus Number
//============================================================

  void minus(uint8_t points) {

    // Build Shape For Point
    uint8_t number  = digitToShape(points);

    // To Write - Sign shape
    uint8_t sign    = shape(false, false, false, false, false, false, true);

    // Minus Sign Written
    writeShape(digit[0], sign, 100, referee.r, referee.g, referee.b);

    // Showing
    writeShape(digit[1], number, 100, referee.r, referee.g, referee.b);

  }

//============================================================
//  Waiting Number
//============================================================

  void waiting() {

    // writeNumber(0, 1, 255, 255, 255);
    writeShape(digit[0], shape(false, false, false, false, false, false, true), 1, 255, 255, 255);
    writeShape(digit[1], shape(false, false, false, false, false, false, true), 1, 255, 255, 255);

    // Cross Fade
    for(int times=0; times<3; times++) {
      crossfade(1);
    }

    // Clear The Display
    writeShape(digit[0], shape(false, false, false, false, false, false, false), 100, 255, 255, 255);
    writeShape(digit[1], shape(false, false, false, false, false, false, false), 100, 255, 255, 255);

    // Show
    show();

  }

//============================================================
//  End Of Functions
//============================================================

  void crossfade(int cfdelay) {

    // Fade In
    fadein(cfdelay);
    // Fade Out
    fadeout(cfdelay);

  }

//============================================================
//  End Of Functions
//============================================================

  void fadein(int fdelay) {

    for(int i=1; i<255; i++) {
      pixels.setBrightness(i);
      show();
      delay(fdelay);
    }

  }

//============================================================
//  End Of Functions
//============================================================

  void fadeout(int fdelay) {

    for(int i=255; i>=1; i--) {
      pixels.setBrightness(i);
      show();
      delay(fdelay);
    }

  }

//============================================================
//  Add Point
//============================================================

  void addPoint(uint8_t points) {

    // Update The Score
    score = points;

    // Clear Data On Pixel Strips
    pixels.clear();
    
    // Send Data To Neo Pixel
    writeNumber(score, 100, participant.r, participant.g, participant.b);

    // Command Neo Pixel To Show
    show();

  }

//============================================================
//  Sub Point
//============================================================

  void subPoint(uint8_t points) {

    // Display The Minus Magnitude Sign
    minus(score - points);

    // Update The Score
    score = points;

    // Show Display
    show();

    // Wait For The Number
    delay(800);

    // Clear Data On Pixel Strips
    pixels.clear();
    
    // Send Data To Neo Pixel
    writeNumber(score, 100, participant.r, participant.g, participant.b);

    // Command Neo Pixel To Show
    show();

  }

//============================================================
//  End Of Functions
//============================================================
