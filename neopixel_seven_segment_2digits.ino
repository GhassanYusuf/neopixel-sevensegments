//============================================================
// Neo Pixel Strip Libraris
//============================================================
  
  // Library
  #include <Adafruit_NeoPixel.h>

  // AVR  
  #ifdef __AVR__
    #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
  #endif

  // Main Settings Of The Strip
  #define PIN         15  // Pin Number On the Microcontroller
  #define NUMPIXELS   98  // Number Of Led's On the Strip
  #define NUMDIGITS   2   // The Number Of Digit Units Created From LED Strip

  // Calculating The Size Of Each Segment On A Signle Digit Unit
  #define SEGSIZE     NUMPIXELS/(NUMDIGITS * 7)

  // Creating The Pixel Strip
  Adafruit_NeoPixel   pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//------------------------------------------------------------
// Seven Segments Settings
//------------------------------------------------------------

  // Structure Of Segment LED Pixel Types
  struct SegmentPixelSize {
    uint8_t start;
    uint8_t stop;
  };

  // Digits 
  struct Digit {
    SegmentPixelSize segments[7];
  };

  // The Segmants
  Digit digit[NUMDIGITS];

//============================================================
// Setup
//============================================================

  void setup() {

    // Start Serial
    Serial.begin(9600);

    // Make Sure It Works
    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
      clock_prescale_set(clock_div_1);
    #endif

    // Start Neo Pixel
    setupSSDisplay(digit);

    // Start Pixels
    pixels.begin();

    // Clearing Pixels
    pixels.clear();

    // Display
    pixels.show();

  }

//============================================================
// Loop
//============================================================

  void loop() {

    // Serial Command
    if(Serial.available()) {
      String x = Serial.readStringUntil('\n');
      while(Serial.available()) Serial.read();
      x.trim();
      pixels.clear();
      write(shapeNumber(x.toInt()), 80, 255, 0, 0);
    }

  }

//============================================================
// Enable The Segments
//============================================================