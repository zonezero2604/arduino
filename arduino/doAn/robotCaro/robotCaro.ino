
#include <math.h>
#include <AccelStepper.h>
#include <Stepper.h>
// ĐỂ XÀI CÁC HÀM TOÁN HỌC THÌ THÊM VÀO THƯ VIỆN MATH.H
// QUY ƯỚC DỰA TRÊN SKEMATIC CỦA SHIELD CNC V3
// STEP 1, DÙNG ĐỂ XOAY
const int stepPin1 = 2; // TRỤC X QUY ƯỚC LÀ PIN 1
const int dirPin1 = 5;
// STEP 2, DÙNG CHO KHÂU 2
const int stepPin2 = 3; // TRỤC Y QUY ƯỚC LÀ PIN 2
const int dirPin2 = 6;
// KHAI BÁO BIẾN
const float pi=3.14;
double X,Y,Z,i=0,t1,t2,t11,t21;
float c1,s1,c2,s2,s21,c11,s11,x,y;
float pulse1,pulse2;
float l2=235,l3=200;
int a[5] = {0,-100,0,100}; // a là x
int b[5] = {0,215,315,415};// b là y
int k,val = 50;
void setup() 
{
//KHOI TAO SERIAL
  Serial.begin(9600);
// Sets the two pins as Outputs
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(8, OUTPUT); // CHÂN ENABLE, LOW MỚI CHẠY
  digitalWrite(8, LOW);
}
void loop() 
{ 
  int state=0,state2=0;
// CHỜ NHẬN DỮ LIỆU TỪ SERIAL
//IN GIÁ TRỊ NHẬN ĐƯỢC
  Serial.println("Nhap vao o can danh: ");
  while(Serial.available()==0);
  int val = Serial.parseInt();
  switch (val) 
  {
    case 0: {Serial.println("Thao tac that bai");break;}
    default:
  {
    Serial.print("Danh vao o: ");
    Serial.println(val);
//GIẢI MÃ KÝ TỰ 
    x=a[val/10];
    Serial.print("Toa Do X: ");
    Serial.println(x);
    y=b[val%10];
    Serial.print("Toa Do Y: ");
    Serial.println(y);
//TÍNH TOÁN GÓC
    c2=(pow(x,2)+ pow(y,2)-pow(l2,2)-pow(l3,2))/(2*l2*l3);
    s2=sqrt(abs(1 - pow(c2,2)));
    c1=(-y*(l2+l3*c2)+x*l3*s2)/(-pow(l2+l3*c2,2)-pow(l3*s2,2));
    s1=(x*(l2+l3*c2)+y*l3*s2)/(-pow(l2+l3*c2,2)-pow(l3*s2,2));
//ĐỔI RAD SANG ĐỘ
  t2=(atan2(s2,c2)*180)/3.14;
  t1=(atan2(s1,c1)*180)/3.14;
// XONG PHẦN TÍNH GÓC
//ĐỔI ĐỘ RA SỐ XUNG, ĐANG CHẠY FULL-STEP, TƯƠNG ĐƯƠNG 1 XUNG ~1,8 ĐỘ,STEP 1 VÀ STEP 2
    t1 = t1+90 ;
    t2 = t2 ;
    Serial.println("GOC 1 LA ");
    Serial.println(t1);
    Serial.println(" GOC 2 LA");
    Serial.println(t2);
// ĐỔI ĐỘ SANG XUNG
    pulse1= (t1)/1.8;
    pulse2= (t2)/1.8;

    Serial.print("PULSE 1 LA ");
    Serial.println(pulse1);
    Serial.print(" PULSE 2 LA ");
    Serial.println(pulse2);
  //QUY ƯỚC CHIỀU STEP QUAY, CHIỀU DƯƠNG LÀ THEO CHIỀU KIM ĐỒNG HỒ,HIGH LÀ CHIỀU DƯƠNG, LOW CHIỀU ÂM
//TÍNH GÓC QUY ƯỚC DƯƠNG NGƯỢC KIM ĐỒNG HỒ
//XUẤT XUNG ĐỂ QUAY ĐẾN Ô CẦN ĐÁNH
//CÁCH 1
    delay(500);
    Serial.println(" NEU PULSE >0 THI STATE =1 - LOW - ngc kdh va ngc lai");
    if(pulse1>0) {state=1;}
    if(pulse1<0) {state=0;}
    if(pulse2>0) {state2=1;}
    if(pulse2<0) {state2=0;}
    pulse1 = abs(pulse1);
    pulse2 = abs(pulse2);
// IN RA ĐỂ KIỂM TRA
    Serial.println(" STATE 1 BAN DAU");
    Serial.println(state);
    Serial.println(" STATE 2 BAN DAU");
    Serial.println(state2);
    Serial.println("------");
//XÉT ĐIỀU KIỆN LẦN 1
    if(state==1)
    {
       digitalWrite(dirPin1,LOW);
    }
    if(state==0)
    {
       digitalWrite(dirPin1,HIGH);
    }
    if(state2==1)
    {
       digitalWrite(dirPin2,LOW);
    }
    if(state2==0)
    {
       digitalWrite(dirPin2,HIGH);
    }

    delay(500);
// XUẤT XUNG CHẠY
//STEP 1,DÙNG ĐỂ XOAY
    Serial.println("Khop 1 quay ");
    for(int i = 0; i < pulse1; i++) 
  {
      digitalWrite(stepPin1,HIGH); //6000 là ok nếu ko micro
      delayMicroseconds(2000);
      digitalWrite(stepPin1,LOW);
      delayMicroseconds(2000);
  }
    delay(400);
    Serial.println("Khop 2 quay ");
    for(int i = 0; i < pulse2; i++) 
  {
    digitalWrite(stepPin2,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin2,LOW);
    delayMicroseconds(2000);
  }
    delay(400);

    Serial.println(" Done ");
    delay(1000);
//QUAY LẠI VỊ TRÍ BAN ĐẦU
    state = !state;
    state2 = !state2;
    Serial.println(" STATE 1 KHI ĐẢO");
    Serial.println(state);
    Serial.println(" STATE 2 KHI ĐẢO");
    Serial.println(state2);
      delay(400);
//XÉT ĐIỀU KIỆN LẠI
    if(state==1)
    {
      digitalWrite(dirPin1,LOW);
    }
    if(state==0)
    {
      digitalWrite(dirPin1,HIGH);
    }
    if(state2==1)
    {
      digitalWrite(dirPin2,LOW);
    }
    if(state2==0)
    {
      digitalWrite(dirPin2,HIGH);
    }

    delay(400);

// STEP 1
    Serial.println("Dao khop quay 1");
     for(int i = 0; i < pulse1; i++) 
  {
      digitalWrite(stepPin1,HIGH); //6000 là ok nếu ko micro
      delayMicroseconds(2000);
      digitalWrite(stepPin1,LOW);
      delayMicroseconds(2000);
  }
    delay(400);
//STEP2
    Serial.println("Dao khop quay 2");
    for(int i = 0; i < pulse2; i++) 
  {
    digitalWrite(stepPin2,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin2,LOW);
    delayMicroseconds(2000);
  }
    delay(400);
    Serial.println(" Done ");
}
  }
}
