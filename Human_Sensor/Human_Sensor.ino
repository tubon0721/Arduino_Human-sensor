#include <LiquidCrystal.h>

int human=0;
int state=0;
int a_value=0;
int b_value=0;
const int a_sen=13;
const int b_sen=12;
const int button_reset=3;
const int buzzer =2;
int time;
int time_h=0;
int time_m=0;
float time_s=0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
    pinMode(a_sen, INPUT);
    pinMode(b_sen, INPUT);
    lcd.begin(16, 2);    
    Serial.begin( 9600 );
}

void loop()
{
  lcd.setCursor(0,0);
  if(digitalRead(a_sen)==1&&digitalRead(b_sen)==1&&state==1){
    a_value=0;
    b_value=0;
    delay( 200 );
    time_s+=0.2;
  }
  else{
    a_value=digitalRead(a_sen);
    b_value=digitalRead(b_sen);
    delay( 200 );
    time_s+=0.2;
  }
  
  Serial.print("Av：");Serial.print(a_value);
  Serial.print("  Bv：");Serial.print(b_value);
  Serial.print("  As：");Serial.print(digitalRead(a_sen));
  Serial.print("  Bs：");Serial.print(digitalRead(b_sen));
  Serial.print("  ");
  Serial.print("    ");
  Serial.print("state：");
  Serial.print(state);
  Serial.print("  人数：");
  Serial.print(human);
  Serial.print("  ");
  times();
  
  
  if((a_value>b_value)&&state==0){
    human++;
    state++;
    delay( 200 );
    time_s+=0.2;
  }
  else if((a_value<b_value)&&state==0){
    human--;
    state++;
    delay( 200 );
    time_s+=0.2;
  }
  if(digitalRead(a_sen)==0&&digitalRead(b_sen)==0)
    state=0;
    
  if(digitalRead(button_reset)==LOW){
    human=0;
    state=0;
    Serial.print("リセット\n");
    lcd.print("  reset");
    delay(2000);
    time_s+=2;
  }
//*****************************
  lcd.setCursor(0,1);
  lcd.print("human:");
  lcd.print(human);
  lcd.print(" ");
  if(time_m>=1&&human!=0){
    lcd.print("danger");
    tone(2,440);
  }
  else{
    lcd.print("safe");
    noTone(2);
  }
  
  delay(100);
  lcd.clear();
  time_s+=0.1;
}

void times()
{
  if(time_s>=60.0){
    time_m+=1;
    time_s -= 60;
  }
  if(time_m==60){
    time_h+=1;
    time_m=0;
  }
  if(time_h==24)
    time_h=0;
    
  if(time_h<10){
    Serial.print("0");
    lcd.print("0");
  }
  Serial.print(time_h);
  lcd.print(time_h);
  
  Serial.print(":");
  lcd.print(":");
  
  if(time_m<10){
    Serial.print("0");
    lcd.print("0");
  }
  Serial.print(time_m);
  lcd.print(time_m);
  
  Serial.print(":");
  lcd.print(":");
  
  if(time_s<10){
    Serial.print("0");
    lcd.print("0");
  }
  Serial.println(time_s,1);
  lcd.print(time_s,0);
}
