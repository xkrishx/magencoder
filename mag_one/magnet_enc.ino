#include <AS5145.h>
#include <PID_v2.h>

AS5145 myAS5145(9);
#define PIN_INPUT 9
#define PIN_OUTPUT 11
long value;
long avgval;
double  Input, Output;
double Setpoint;
double Kp= 14, Ki= 7, Kd= 22;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, P_ON_M,DIRECT);
float inputangle;

void setup() {
  Serial.begin(19200);
  pinMode(9,INPUT);
    Setpoint= 150;
//  TCCR1B= TCCR1B & 0b11111000 | 1;
  myPID.SetMode(1);
  myPID.SetSampleTime(1);
 //myPID.SetOutputLimits(-125,125);
}

void loop() {
  // put your main code here, to run repeatedly:
//  value= myAS5145.encoder_degrees();
// Serial.print("enter angle setpoint ");
//  while(Serial.available()==0) {
//  }



 if (Serial.available()) {
  analogWrite(11, 127);
  inputangle= Serial.parseFloat();
  Setpoint= inputangle;
 // delay(1000);
 }

  value= myAS5145.pwm_degrees();
  Input= map(value, 0, 4095, 0, 255);
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);
  Serial.println(Input);
  // Serial.print(",");
  // Serial.println(value);
  // Serial.println(Setpoint);
  // Serial.print("\r");
//  delay(20);

}
