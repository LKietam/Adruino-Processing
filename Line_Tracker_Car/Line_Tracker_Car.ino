  int stopc=0;
  int IN1=11;
  int IN2=9;
  int IN3=8;
  int IN4=7;
  int ENA=6;
  int ENB=5;
  int ABS =140;
  void mForward(){
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void mBack(){
  analogWrite(ENA,ABS);
  analogWrite(ENB,ABS);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void mLeft(){
  analogWrite(ENA,200);
  analogWrite(ENB,200);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void mRight(){
  analogWrite(ENA,200);
  analogWrite(ENB,200);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void mStop(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int num1,num2,num3;
  num1=digitalRead(2);
  num2=digitalRead(4);
  num3=digitalRead(10);
  if((num1==1)&&num2&&num3){
    stopc++;
  }
 if(stopc==0){
  if((num1==0)&&num2&&num3){
    mLeft();
    delay(2);
    while(1){
      num2=digitalRead(4);
      if(num2==1){
        mLeft();
        delay(2);
      }else
      break;
    }
   }else if(num2&&num1&&(num3==0)){
    mRight();
    delay(2);
    while(1){
      num2=digitalRead(4);
      if(num2==1){
        mRight();
        delay(2);
      }else
      break;
    }
   }
   else{
    mForward();
    delay(2);
   }
 }
}
