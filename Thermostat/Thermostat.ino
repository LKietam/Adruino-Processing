#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define TEMP_ADDR 72
LiquidCrystal_I2C lcd(0x27,16,2);
const int Led=11;
byte degree[8]={B00110, B01001, B01001, B00110, B00000, B00000, B00000, B00000};
byte LED_On[8]={B00100,B10101,B01110,B11111,B01110,B10101,B00100,B00000};
byte LED_Off[8]={B00100, B00100,B00100,B11111,B00100,B00100,B00100,B00000};
boolean one_time=false;
int set_temp=23;
const int DOWN_BUTTON=8;
const int UP_BUTTON=9;
boolean lastDownTempButton= LOW;
boolean currentDownTempButton= LOW;
boolean lastUpTempButton= LOW;
boolean currentUpTempButton= LOW;
void setup() {
  // put your setup code here, to run once:
  pinMode(Led,OUTPUT);
  lcd.begin();
  Wire.begin();
  lcd.createChar(0,degree);
  lcd.createChar(2,LED_On);
  lcd.createChar(1,LED_Off);
  lcd.setCursor(0,0);
  lcd.print("Current:");
  lcd.setCursor(10,0);
  lcd.write((byte)0);
  lcd.setCursor(11,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Set: ");
  lcd.setCursor(10,1);
  lcd.write((byte)0);
  lcd.setCursor(11,1);
  lcd.print("C");
  lcd.setCursor(15,1);
  lcd.write(1);
}

boolean debounce(boolean last, int pin){
  boolean current=digitalRead(pin);
  if(last!=current){
    delay(5);
    current= digitalRead(pin);
  }
  return current;
}
void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(TEMP_ADDR);
  Wire.write(0);
  Wire.endTransmission(TEMP_ADDR);
  Wire.requestFrom(TEMP_ADDR,1);

  while(Wire.available()==0);
  int c=Wire.read();
  lcd.setCursor(8,0);
  lcd.print(c);

  currentDownTempButton= debounce(lastDownTempButton, DOWN_BUTTON);
  currentUpTempButton= debounce(lastUpTempButton, UP_BUTTON);

  if(lastDownTempButton== LOW && currentDownTempButton == HIGH){
    set_temp--; 
  }else if(lastUpTempButton== LOW && currentUpTempButton == HIGH){
    set_temp++;
  }
  lcd.setCursor(8,1);
  lcd.print(set_temp);
  lastDownTempButton= currentDownTempButton;
  lastUpTempButton= currentUpTempButton;
  if(c>=set_temp){
    digitalWrite(Led,LOW);
    lcd.setCursor(15,1);
    lcd.write(2);
  }
  else{
    one_time=false;
    digitalWrite(Led,HIGH);
    lcd.setCursor(15,1);
    lcd.write(1);
  }
}
