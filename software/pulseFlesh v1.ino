#define DEBUGLOG_DEFAULT_LOG_LEVEL_OFF 

#include <WiFi.h>
#include <ArduinoOSCWiFi.h> 

#define DEBUG_MODE 1 
#define BLUE_LED_PIN 2   

// hardware pins configuration
const int ECG_OUTPUT_PIN = 36; // vp pin for ecg analog input
const int LO_PLUS_PIN = 21;    // d21 pin for ecg electrode disconnection check lo plus
const int LO_MINUS_PIN = 15;   // d15 pin for ecg electrode disconnection check lo minus
const int CV_OUT_PIN = 25;     // d25 pin for dac analog voltage output
const int PIEZO_INPUT_PIN = 32; // d32 pin for piezo mechanical sensor input

// calibration boundaries for clipping signal noise
const int BIOMIN = 800;   
const int BIOMAX = 3400;  

float currentCV = 0.0;
int prevRaw = 0;
float smoothPiezo = 0.0;

void setup() {
  #if DEBUG_MODE
    Serial.begin(115200);
    Serial.println("PULSEFLESH V1: BIO-INTERFACE INITIALIZED");
  #endif
  
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(BLUE_LED_PIN, LOW); 

  // configuration of input pins for sensors and connection check
  pinMode(LO_PLUS_PIN, INPUT);
  pinMode(LO_MINUS_PIN, INPUT);
  pinMode(PIEZO_INPUT_PIN, INPUT); 

  // setting native 12 bit resolution for esp32 adc
  analogReadResolution(12);
  dacWrite(CV_OUT_PIN, 0);

  // hardware delay to prevent first frame reading artifact
  delay(100);
  prevRaw = analogRead(ECG_OUTPUT_PIN);
}

void loop() {
  // reading data streams from hardware sensors
  int rawEcg = analogRead(ECG_OUTPUT_PIN);
  int rawPiezo = analogRead(PIEZO_INPUT_PIN); 
  int targetCV = 0;

  // low pass filter to smooth out high frequency piezo jitter
  smoothPiezo = (rawPiezo * 0.1) + (smoothPiezo * 0.9);

  // check if any of ecg leads are disconnected from body
  bool electrodesOff = (digitalRead(LO_PLUS_PIN) == 1) || (digitalRead(LO_MINUS_PIN) == 1);

  if (electrodesOff) {
    digitalWrite(BLUE_LED_PIN, HIGH); 
    // smooth volume drop to prevent clicks on synth side when electrodes disconnect
    currentCV *= 0.85; 
    if (currentCV < 1.0) currentCV = 0;
  } else {
    digitalWrite(BLUE_LED_PIN, LOW);  

    // software filter to drop sudden hardware spikes from poor skin contact
    if (abs(rawEcg - prevRaw) > 1000) {
      rawEcg = prevRaw;
    }

    // extraction of micro muscle noise component by computing delta
    int chaos = abs(rawEcg - prevRaw);
    prevRaw = rawEcg; 

    // quadratic scaling curve for expressive synth response
    int constrainedEcg = constrain(rawEcg, BIOMIN, BIOMAX);
    float norm = (float)(constrainedEcg - BIOMIN) / (BIOMAX - BIOMIN);
    norm = norm * norm; 
    targetCV = norm * 255; 

    // blending structural heart rate with chaotic muscle data
    targetCV += chaos / 8;
    targetCV = constrain(targetCV, 0, 255);

    // adaptive smoothing based on how fast the input values change
    int delta = abs(targetCV - currentCV);
    float dynamicSmooth = (delta > 40) ? 0.9 : 0.2;

    currentCV = (targetCV * dynamicSmooth) + (currentCV * (1.0 - dynamicSmooth));
  }

  // sending processed organic cv value to hardware dac output channel
  dacWrite(CV_OUT_PIN, (int)currentCV);

  #if DEBUG_MODE
    // parallel serial print lines formatted for arduino serial plotter tool
    Serial.print("Raw_Bio:");        Serial.print(rawEcg);
    Serial.print(",");
    Serial.print("Smooth_Piezo:");   Serial.print(smoothPiezo); 
    Serial.print(",");
    Serial.print("CV_Out_Scaled:");  Serial.println(currentCV * 16); 
  #endif

  // fast delay setting main main processing loop speed to around 450 hz
  delay(2); 
}