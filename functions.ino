//============================================================
//  Minus Number
//============================================================

  void minus(uint8_t points) {

    // Build Shape For Point
    uint8_t number  = sevenSegment.numberToShape(points);

    // To Write - Sign shape
    uint8_t sign    = sevenSegment.shape(false, false, false, false, false, false, true);

    // Minus Sign Written
    sevenSegment.writeSingleDisplayShape(sevenSegment.digits[0], sign, 100, 255, 255, 0);

    // Showing
    sevenSegment.writeSingleDisplayShape(sevenSegment.digits[1], number, 100, 255, 255, 0);

  }

//============================================================
//  Waiting Number
//============================================================

  void waiting() {

    // writeNumber(0, 1, 255, 255, 255);
    sevenSegment.writeSingleDisplayShape(sevenSegment.digits[0], sevenSegment.shape(false, false, false, false, false, false, true), 1, 255, 255, 0);
    sevenSegment.writeSingleDisplayShape(sevenSegment.digits[1], sevenSegment.shape(false, false, false, false, false, false, true), 1, 255, 255, 0);

    // Cross Fade
    for(int times=0; times<3; times++) {
      sevenSegment.fadein(1, 255);
      sevenSegment.fadeout(255, 1);
    }

    // Clear The Display
    sevenSegment.writeSingleDisplayShape(sevenSegment.digits[0], sevenSegment.shape(false, false, false, false, false, false, false), 100, 255, 255, 0);
    sevenSegment.writeSingleDisplayShape(sevenSegment.digits[1], sevenSegment.shape(false, false, false, false, false, false, false), 100, 255, 255, 0);

    // Show
    sevenSegment.show();

  }

//============================================================
//  Add Point
//============================================================

  void addPoint(uint8_t points) {

    // Update The Score
    score = points;

    // Clear Data On Pixel Strips
    sevenSegment.clear();
    
    // Send Data To Neo Pixel
    sevenSegment.writeNumber(score, 100, 255, 0, 0);

    // Command Neo Pixel To Show
    sevenSegment.show();

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
    sevenSegment.show();

    // Wait For The Number
    delay(800);

    // Clear Data On Pixel Strips
    sevenSegment.clear();
    
    // Send Data To Neo Pixel
    sevenSegment.writeNumber(score, 100, 255, 0, 0);

    // Command Neo Pixel To Show
    sevenSegment.show();

  }

//============================================================
//  End Of Functions
//============================================================