#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

//software SPI
Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);

unsigned long punchStart = 0;//variable for non-blocking punch timeframe check
const long punchInterval = 200; //timeframe of a punch in ms
int punchAccel = 15;//the beginning of a punch in m/s^2
int punchDecel = -20;//the end of a punch in m/s^2
int flameTime = 500;//how long the flame lasts, in ms

void setup(void) {
  //Test to see if accelerometer is communicating
  Serial.begin(9600);
  Serial.println("LIS3DH test!");  
  if (! lis.begin(0x19)) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_16_G);   //+-16G range for good punch detection
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

  pinMode(7, OUTPUT); //Zapalniczka - styki
  pinMode(8, OUTPUT); //Zapalniczka - guzik
  pinMode(9, OUTPUT); //Zawór
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void loop() {
  lis.read();
  sensors_event_t event; 
  lis.getEvent(&event);
  
 //look for punch starting
  if (event.acceleration.x > punchAccel){
     Serial.println(event.acceleration.x);
     punchStart = millis();
  }
  
  unsigned long currentMillis = millis();

  //look for punch ending
  if ((event.acceleration.x)*(-1) < punchDecel && currentMillis - punchStart < punchInterval){
      Serial.println(event.acceleration.x);
      Serial.println("Punch");
      Fire(flameTime);
    }
}

void Fire(int flameTime){
  digitalWrite(8, HIGH);
  delay(100); //to be sure lighter will be ignited before a cloud of a gas
  digitalWrite(9, HIGH);
  delay(flameTime);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  delay(flameTime);
  digitalWrite(7, HIGH); // to keep lighter on but not ignited
}
