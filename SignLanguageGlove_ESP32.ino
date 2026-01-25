#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(80);
Adafruit_MPU6050 mpu;

const int PIN_THUMB = 36;
const int PIN_INDEX = 39;
const int PIN_MIDDLE = 34;
const int PIN_RING = 35;
const int PIN_PINKY = 32;

int minThumb = 3260; 
int maxThumb = 3480;
int minIndex = 3520; 
int maxIndex = 3780;
int minMiddle = 3120;
int maxMiddle = 3160;
int minRing = 3360; 
int maxRing = 3700;
int minPinky = 3000; 
int maxPinky = 3040;

float angleThumb, angleIndex, angleMiddle, angleRing, anglePinky;
char resultBuffer[50];
int resultIndex = 0;

void setup() {
  Serial.begin(115200);

  pinMode(PIN_THUMB, INPUT);
  pinMode(PIN_INDEX, INPUT);
  pinMode(PIN_MIDDLE, INPUT);
  pinMode(PIN_RING, INPUT);
  pinMode(PIN_PINKY, INPUT);

  if (!mpu.begin()) {
    while (1) delay(10);
  }
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  int rawThumb = analogRead(PIN_THUMB);
  int rawIndex = analogRead(PIN_INDEX);
  int rawMiddle = analogRead(PIN_MIDDLE);
  int rawRing = analogRead(PIN_RING);
  int rawPinky = analogRead(PIN_PINKY);

  rawThumb = constrain(rawThumb, minThumb, maxThumb);
  rawIndex = constrain(rawIndex, minIndex, maxIndex);
  rawMiddle = constrain(rawMiddle, minMiddle, maxMiddle);
  rawRing = constrain(rawRing, minRing, maxRing);
  rawPinky = constrain(rawPinky, minPinky, maxPinky);

  angleThumb = map(rawThumb, minThumb, maxThumb, 0, 90);
  angleIndex = map(rawIndex, minIndex, maxIndex, 0, 90);
  angleMiddle = map(rawMiddle, minMiddle, maxMiddle, 0, 90);
  angleRing = map(rawRing, minRing, maxRing, 0, 90);
  anglePinky = map(rawPinky, minPinky, maxPinky, 0, 90);

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  char detectedChar = 0;

  if (angleThumb > 45 && angleIndex < 45 && angleMiddle < 45 && angleRing < 45 && anglePinky < 45) {
    detectedChar = 'A';
  }
  else if (angleThumb < 45 && angleIndex > 45 && angleMiddle < 45 && angleRing < 45 && anglePinky < 45) {
    detectedChar = 'B';
  }
  else if (angleThumb < 45 && angleIndex < 45 && angleMiddle > 45 && angleRing < 45 && anglePinky < 45) {
    detectedChar = 'C';
  }
  else if (angleThumb < 45 && angleIndex < 45 && angleMiddle < 45 && angleRing > 45 && anglePinky < 40) {
    detectedChar = 'D';
  }
  else if (angleThumb > 45 && angleIndex < 45 && angleMiddle < 45 && angleRing < 45 && anglePinky > 45) {
    detectedChar = 'E';
  }
  else if (angleThumb > 45 && angleIndex > 45 && angleMiddle < 45 && angleRing < 45 && anglePinky < 45) {
    detectedChar = 'F';
  }
  else if (angleThumb > 45 && angleIndex < 45 && angleMiddle > 45 && angleRing < 45 && anglePinky < 45) {
    detectedChar = 'G';
  }
  else if (angleThumb > 45 && angleIndex < 45 && angleMiddle < 45 && angleRing > 45 && anglePinky < 45) {
    detectedChar = 'H';
  }
  else if (angleThumb < 45 && angleIndex < 45 && angleMiddle < 45 && angleRing > 45 && anglePinky > 45) {
    detectedChar = 'I';
  }
  else if (angleThumb < 45 && angleIndex < 45 && angleMiddle > 45 && angleRing > 45 && anglePinky > 45) {
    detectedChar = 'J';
  }
  else if (angleThumb < 45 && angleIndex > 45 && angleMiddle > 45 && angleRing > 45 && anglePinky > 45) {
    detectedChar = 'K';
  }
  else if (angleThumb > 45 && angleIndex > 45 && angleMiddle > 45 && angleRing < 45 && anglePinky < 45) {
    detectedChar = 'L';
  }
  else if (angleThumb > 45 && angleIndex > 45 && angleMiddle > 15 && angleRing > 45 && anglePinky < 45) {
    detectedChar = 'M';
  }
  else if (angleThumb < 45 && angleIndex > 45 && angleMiddle > 45 && angleRing < 45 && anglePinky < 45) {
    detectedChar = 'N';
  }
  else if (angleThumb > 45 && angleIndex < 45 && angleMiddle > 45 && angleRing > 45 && anglePinky < 45) {
    detectedChar = 'O';
  }
  else if (angleThumb > 45 && angleIndex > 45 && angleMiddle < 45 && angleRing < 45 && anglePinky > 45) {
    detectedChar = 'P';
  }
  else if (angleThumb > 45 && angleIndex < 45 && angleMiddle < 45 && angleRing > 45 && anglePinky > 45) {
    detectedChar = 'Q';
  }
  else if (angleThumb > 45 && angleIndex > 45 && angleMiddle < 45 && angleRing > 45 && anglePinky < 45) {
    detectedChar = 'R';
  }
  else if (angleThumb < 45 && angleIndex > 45 && angleMiddle < 45 && angleRing > 45 && anglePinky < 45) {
    detectedChar = 'S';
  }
  else if (angleThumb > 45 && angleIndex < 45 && angleMiddle > 45 && angleRing < 45 && anglePinky > 45) {
    detectedChar = 'T';
  }
  else if (angleThumb < 45 && angleIndex > 45 && angleMiddle < 45 && angleRing > 45 && anglePinky > 45) {
    detectedChar = 'U';
  }
  else if (angleThumb > 45 && angleIndex > 45 && angleMiddle < 45 && angleRing > 45 && anglePinky > 45) {
    detectedChar = 'V';
  }
  else if (angleThumb > 45 && angleIndex > 45 && angleMiddle > 45 && angleRing < 45 && anglePinky > 45) {
    detectedChar = 'W';
  }
  else if (angleThumb < 45 && angleIndex < 45 && angleMiddle > 45 && angleRing > 45 && anglePinky < 45) {
    detectedChar = 'X';
  }
  else if (angleThumb < 45 && angleIndex > 45 && angleMiddle > 45 && angleRing > 45 && anglePinky < 45) {
    detectedChar = 'Y';
  }
  else if (angleThumb > 45 && angleIndex < 45 && angleMiddle > 45 && angleRing > 45 && anglePinky > 45) {
    detectedChar = 'Z';
  }
  else if (angleThumb > 45 && angleIndex > 45 && angleMiddle > 45 && angleRing > 45 && anglePinky > 45) {
    if (resultIndex > 0) {
      if (client.connected()) {
        client.println(resultBuffer);
      }
      memset(resultBuffer, 0, sizeof(resultBuffer));
      resultIndex = 0;
    }
  }

  if (detectedChar != 0) {
    resultBuffer[resultIndex] = detectedChar;
    resultIndex++;
    if (resultIndex >= 49) resultIndex = 0;
    delay(500); 
  }
  
  delay(100);
}
