#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
SoftwareSerial BTSerial(0,1); 


Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);


char var;
int dir = 0;
int angle = -1;
String tmp = "";
float magneto = 0;
float result;
void setup() {

 Serial.begin(9600);
 BTSerial.begin(9600);
 // BTSerial.print("AT\r\n"); //Check Status
 delay(500);
 delay(500);

 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);

if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
 
 }
void loop() {
    //var = Serial.read(); // receive angle and calculate mag
   

  while (BTSerial.available() > 0){
    delay(100);
    var = BTSerial.read();
    dir = (int)var -'0';
    tmp+=dir;
    angle = tmp.toInt();
//    Serial.print(angle);
  }
//    Serial.print("out");

  if(angle != -1){
      //Serial.print("in");

      while(magneto == 0){
        sensors_event_t event; 
        mag.getEvent(&event);


         //Calibration 
        
        //Mag Minimums: -88.36  -52.09  0.00
        //Mag Maximums: 48.82  40.73  175.92
        
        
        
        
        //CorrectedValue = map(RawValue, RawLow, RawHigh, ReferenceLow, ReferenceHigh)
          float correctY;
          float correctX;
          correctY = map(event.magnetic.y, -52.55, 42.55, -60, 60); 
          correctX = map(event.magnetic.x, -88.73,48.73, -60, 60);

          float Pi = 3.1415926535;
          
          // Calculate the angle of the vector y,x
          //float heading = (atan2(correctY,correctX) * 180) / Pi;
          //magneto = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
          magneto = (atan2(correctY,correctX) * 180) / Pi;
          
          // Normalize to 0-360
          if (magneto < 0)
          {
            magneto = 360  + magneto;
          }
//          Serial.print("Compass Heading: ");
//          Serial.println(magneto);
//          
//        Serial.print("finish");
      }
      
      result = angle - (magneto + 50);
      
      if(result < 0){
        result = result + 360;
      }
      
      //Serial.println(angle);
        // angle changes to result
        Serial.print(" Mag value: ");
        Serial.print(magneto+50);
        Serial.print(" result value: ");
        Serial.print(result);
        Serial.println();

        if((result>337.5 && result <=359) || (result <= 22.5 && result >=0)){
          digitalWrite(2,HIGH);
          Serial.print("pin 2 is on");
          delay(2000);
          digitalWrite(2,LOW);
        }
        if(result>22.5 && result <= 67.5){
          digitalWrite(9,HIGH);
          Serial.print("pin 9 is on");
          delay(2000);
          digitalWrite(9,LOW);
        }
        if(result>67.5 && result <= 112.5){
          digitalWrite(8,HIGH);
          Serial.print("pin 8 is on");
          delay(2000);
          digitalWrite(8,LOW);
        }
        if(result>112.5 && result <= 157.5){
          digitalWrite(7,HIGH);
          Serial.print("pin 7 is on");
          delay(2000);
          digitalWrite(7,LOW);
        }
        if(result>157.5 && result <= 202.5){
          digitalWrite(6,HIGH);
          Serial.print("pin 6 is on");
          delay(2000);
          digitalWrite(6,LOW);
        }
        if(result>202.5 && result <= 247.5){
          digitalWrite(5,HIGH);
          Serial.print("pin 5 is on");
          delay(2000);
          digitalWrite(5,LOW);
        }
        if(result>247.5 && result <= 292.5){
          digitalWrite(4,HIGH);
          Serial.print("pin 4 is on");
          delay(2000);
          digitalWrite(4,LOW);
        }
        if(result>292.5 && result <= 337.5 ){
          digitalWrite(3,HIGH);
          Serial.print("pin 3 is on");
          delay(2000);
          digitalWrite(3,LOW);
        }
        tmp = "";
        angle = -1;
        magneto = 0;
      }
}


