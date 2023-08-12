//============================================================
//  Neo Pixel Strip Libraris
//============================================================
  
  // Library Include
  #include "SevenSegment.h"

//------------------------------------------------------------
//  Seven Segments Settings
//------------------------------------------------------------
  
  // Pin configuration
  #define LED_PIN       D5
  #define NUM_PIXELS    7*7*2
  #define NUM_DISPLAYS  2

  // Create An Instance Of The SevenSegment Library
  SevenSegment sevenSegment(LED_PIN, NUM_DISPLAYS, NUM_PIXELS);

  // Score
  uint8_t score;

//============================================================
//  Setup
//============================================================

  void setup() {

    // Start Serial
    Serial.begin(9600);

    // Serial New Line
    Serial.println(); Serial.println();

    // Initialize
    sevenSegment.begin();

    // Waiting
    waiting();

  }

//============================================================
//  Loop
//============================================================

  void loop() {

    // Serial Command
    if(Serial.available()) {
      
      // String Data
      String x = Serial.readStringUntil('\n');
      
      // Clear Remaining Data
      while(Serial.available()) Serial.read();
      
      // Clear Data From
      x.trim();
      
      // Make Decision
      if(score > x.toInt()) {
        subPoint(x.toInt());
      } else {
        addPoint(x.toInt());
      }

    }

  }

//============================================================
//  Enable The Segments
//============================================================
