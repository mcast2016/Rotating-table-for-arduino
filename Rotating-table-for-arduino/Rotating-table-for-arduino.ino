/*
    ArduinoUno
    ステッピングモーター
    https://www.amazon.co.jp/gp/product/B07VG7LDWC/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&th=1
        2相
        回転角1.8°
        DC8.0V（仕様では4.1V）
    モータドライバ:A4988(Allegro)
    https://www.amazon.co.jp/gp/product/B084XB43QZ/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1
    https://iot.keicode.com/arduino/arduino-stepper-motor-a4988.php
    フォトカプラ
    
*/
long _beforetime = 0;
const int DIR  = 7;
const int STEP = 9;
#define ENC_INPUT_PIN 8
int motor_pls;
int i;
float i_angle;
float angle;
int x10_i_angle;
void setup() {
    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);
    digitalWrite(DIR, LOW);
    digitalWrite(STEP, LOW);
    digitalWrite(DIR, HIGH);
    i = 0;
    i_angle = 0;
    angle = 0;
    motor_pls = 2000;
    Serial.begin(9600);
    pinMode(ENC_INPUT_PIN,INPUT);
    _beforetime = millis();
}

void loop() {
  //20ステップ動く
  while(i <20){
    Serial.print("sensorMODE=");
    Serial.print(digitalRead(ENC_INPUT_PIN));
    Serial.print(", i=");
    Serial.println(i);
    moving(motor_pls);
    if(digitalRead(ENC_INPUT_PIN)==HIGH){
      i = i+1;
      while(digitalRead(ENC_INPUT_PIN)==HIGH){
      moving(motor_pls);  
      }
    }
  }
  //20ステップで停止
  if(i > 20){
    motor_pls = 0;
    while (i < 2000){
      Serial.println("STOP!!");
      }
  }
//各種計算//
  //回転角を計算する
    x10_i_angle = 1.8*i*10;
    int x10_angle = x10_i_angle%360;
    angle = x10_angle/10;
  //回転速度を計算する
    //long speed = 1.8/diff_time/1000; //°/sec
//    long rpm = speed*200; //rpm
  //目標速度との差分
//    long diff_rpm = 60 -rpm;
  //log
    //Serial.print("angle:");
    //Serial.print(angle);
    //Serial.print(", ");
    //Serial.print("rpm");
    //Serial.println(rpm);
}
int moving(int motor_pls){
  Serial.println("moving");
  digitalWrite(STEP, HIGH);
  delayMicroseconds(motor_pls);
  digitalWrite(STEP, LOW);
  delayMicroseconds(motor_pls);
}
