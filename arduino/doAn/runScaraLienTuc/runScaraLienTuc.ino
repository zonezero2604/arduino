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
const float pi = 3.14;
double X, Y, Z, i = 0, t1, t2, t11, t21;
float c1, s1, c2, s2, s21, c11, s11, x, y;
float pulse1, pulse2;
float l2 = 235, l3 = 200;

int a[5] = {10, 60, 10, 10}; // a là x
int b[5] = {185, 110, 185, 170}; // b là y
double gocStep1[10] = {0, 0, 0, 0};
double gocStep2[10] = {0, 0, 0, 0};

//int a[5] = {40, 40, 10, 10}; // a là x
//int b[5] = {170, 185, 185, 170}; // b là y
int k, val = 50;
double bu;

const double d = 80;
const double l1f = 100;
const double l2f = 100;
const double l1r = 100;
const double l2r = 100;

int X1 = 40;
int Y1 = 170;

double angle_1;
double angle_2;


boolean isGoal = false;

void setup() {
  //KHOI TAO SERIAL
  Serial.begin(9600);
  // Sets the two pins as Outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(8, OUTPUT); // CHÂN ENABLE, LOW MỚI CHẠY
  digitalWrite(8, LOW);
}

void loop() {


  if (!isGoal)
  {

    /**************************************************************Goc cua toa do dau tien*****************************************************************/
    Serial.print("Toa do diem dau tien la x: ");
    Serial.println(a[0]);
    Serial.print("Toa do diem dau tien la y: ");
    Serial.println(b[0]);

    //Tính q1- Góc của động cơ 1
    double q1;
    q1 = atan2(b[0], a[0]) + acos((-1 * pow(l2f, 2) + pow(l1f, 2) + pow(a[0], 2) + pow(b[0], 2)) / (2 * l1f * sqrt(pow(a[0], 2) + pow(b[0], 2)))); // radian
    angle_1 = q1 * (360 / (2 * PI));
    gocStep1[0]=angle_1;
    Serial.print("Góc của động cơ 1: ");
    Serial.println(gocStep1[0]);

    //Tính q2 - Góc của động cơ 2
    double dif_dx = (d - a[0]);
    double q2;
    q2 = PI - atan2(b[0], dif_dx) - acos((-1 * pow(l2r, 2) + pow(l1r, 2) + pow(dif_dx, 2) + pow(b[0], 2)) / (2 * l1r * sqrt(pow(dif_dx, 2) + pow(b[0], 2))));
    angle_2 = q2 * (360 / (2 * PI));
    gocStep2[0]=angle_2;
    Serial.print("Góc của động cơ 2: ");
    Serial.println(gocStep2[0]);
    /******************************************************************************************************************************************************/
    chay(gocStep1[0], gocStep2[0]) ;


    /************************************************************** Goc cua toa do N *****************************************************************/
    Serial.print("Toa do N la x: ");
    Serial.println(a[1]);
    Serial.print("Toa do N la y: ");
    Serial.println(b[1]);

    //Tính q1- Góc của động cơ 1
    double gocRand1, gocDoN_1;
    gocRand1 = atan2(b[1], a[1]) + acos((-1 * pow(l2f, 2) + pow(l1f, 2) + pow(a[1], 2) + pow(b[1], 2)) / (2 * l1f * sqrt(pow(a[1], 2) + pow(b[1], 2)))); // radian
    gocDoN_1 = gocRand1 * (360 / (2 * PI));
    gocStep1[1]=gocDoN_1;
    Serial.print("Góc của động cơ 1: ");
    Serial.println(gocStep1[1]);

    //Tính q2 - Góc của động cơ 2
    dif_dx = (d - a[1]);
    double gocRand2, gocDoN_2;
    gocRand1 = PI - atan2(b[1], dif_dx) - acos((-1 * pow(l2r, 2) + pow(l1r, 2) + pow(dif_dx, 2) + pow(b[1], 2)) / (2 * l1r * sqrt(pow(dif_dx, 2) + pow(b[1], 2))));
    gocDoN_2 = gocRand1 * (360 / (2 * PI));
    gocStep2[1]=gocDoN_2;
    Serial.print("Góc của động cơ 2: ");
    Serial.println(gocStep2[1]);
    /******************************************************************************************************************************************************/
    /************************************************************** Toa do ANPHA 3 *****************************************************************/
    double gocAnpha3_1, gocAnpha3_2, gocDoN_1_1, gocDoN_1_2;
    gocDoN_1_1 = gocStep1[0];
    gocDoN_1_2 = gocStep2[0];
    gocAnpha3_1 = gocDoN_1 - gocDoN_1_1;
    gocAnpha3_2 = gocDoN_2 - gocDoN_1_2;

    Serial.print("Góc anpha của động cơ 1: ");
    Serial.println(gocAnpha3_1);

    //Tính q2 - Góc của động cơ 2
    Serial.print("Gócanpha của động cơ 2: ");
    Serial.println(gocAnpha3_2);
    /******************************************************************************************************************************************************/
        chay(gocAnpha3_1, gocAnpha3_2) ;

    isGoal = true;
  }

  else if (isGoal)
  {
    //Another some code
  }

}



void chieuQuay(float pulse1, float pulse2) {
  //QUY ƯỚC CHIỀU STEP QUAY, CHIỀU DƯƠNG LÀ THEO NGƯỢC CHIỀU KIM ĐỒNG HỒ,HIGH LÀ CHIỀU DƯƠNG state = 1, LOW CHIỀU ÂM state = 0
  //TÍNH GÓC QUY ƯỚC DƯƠNG NGƯỢC KIM ĐỒNG HỒ
  //CÁCH 1
  int state, state2;
  delay(500);

  if (pulse1 > 0) {
    state = 1;
  }
  if (pulse1 < 0) {
    state = 0;
  }
  if (pulse2 > 0) {
    state2 = 1;
  }
  if (pulse2 < 0) {
    state2 = 0;
  }
  pulse1 = abs(pulse1);
  pulse2 = abs(pulse2);
  // IN RA ĐỂ KIỂM TRA
  Serial.println(" STATE 1 Dong co 1");
  Serial.println(state);
  Serial.println(" STATE 2 Dong co 2");
  Serial.println(state2);
  Serial.println("------");
  //XÉT ĐIỀU KIỆN LẦN 1
  if (state == 1)
  {
    digitalWrite(dirPin1, HIGH);
    Serial.println("Dong co 1 quay nguoc KDH");
  }
  if (state == 0)
  {
    digitalWrite(dirPin1, LOW);
    Serial.println("Dong co 1 quay cung KDH");
  }
  if (state2 == 1)
  {
    digitalWrite(dirPin2, HIGH);
    Serial.println("Dong co 2 quay nguoc KDH");
  }
  if (state2 == 0)
  {
    digitalWrite(dirPin2, LOW);
    Serial.println("Dong co 1 quay cung KDH");
  }

  delay(500);

}



void xuatXung(float pulse1, float pulse2) {
  // XUẤT XUNG CHẠY
  pulse1 = abs(pulse1);
  pulse2 = abs(pulse2);
  if (pulse1 > pulse2)
  {

    bu = pulse1 - pulse2;
    for (int i = 0; i < pulse2; i++)
    {
      digitalWrite(stepPin1, HIGH); //6000 là ok nếu ko micro
      delayMicroseconds(2000);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(2000);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(2000);
    }
    for (int i = 0; i < bu; i++)
    {
      digitalWrite(stepPin1, HIGH); //6000 là ok nếu ko micro
      delayMicroseconds(2000);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(2000);
    }

  }
  else
  {
    bu = pulse2 - pulse1;
    for (int i = 0; i < pulse1; i++)
    {
      digitalWrite(stepPin1, HIGH); //6000 là ok nếu ko micro
      delayMicroseconds(2000);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(2000);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(2000);
    }
    for (int i = 0; i < bu; i++)
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(2000);
    }
  }

}



void chay(double goc_1, double goc_2)
{
  /*****************************ĐỔI ĐỘ RA SỐ XUNG, ĐANG CHẠY FULL-STEP, TƯƠNG ĐƯƠNG 1 XUNG ~1,8 ĐỘ,STEP 1 VÀ STEP 2*************************************/
  pulse1 = (goc_1) / 1.8;
  pulse2 = (goc_2) / 1.8;

  Serial.print("PULSE 1 LA ");
  Serial.println(pulse1);
  Serial.print(" PULSE 2 LA ");
  Serial.println(pulse2);

      /*******************************************QUY ƯỚC CHIỀU STEP QUAY**************************************************************************/
    chieuQuay(pulse1, pulse2);
    /******************************************************************************************************************************************************/

    /*******************************************XUẤT XUNG ĐỂ QUAY ĐẾN Ô CẦN ĐÁNH**************************************************************************/
    xuatXung(pulse1, pulse2);
    /******************************************************************************************************************************************************/

  
}
