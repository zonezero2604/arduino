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
int a[5] = {0, -100, 0, 100}; // a là x
int b[5] = {0, 215, 315, 415}; // b là y
int k, val = 50;

const double d = 80;
const double l1f = 100;
const double l2f = 100;
const double l1r = 100;
const double l2r = 100;

int X1 = 40;
int Y1 = 170;

double angle_1;
double angle_2;

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
  // CHỜ NHẬN DỮ LIỆU TỪ SERIAL
  //IN GIÁ TRỊ NHẬN ĐƯỢC
  Serial.println("Nhap X,Y : "); // 40 space 170
  while (Serial.available() == 0);
  int x = Serial.parseInt();
  int y = Serial.parseInt();

  Serial.print("Toa do X la: ");
  Serial.println(x);
  Serial.print("Toa do Y la: ");
  Serial.println(y);

  switch (x)
  {
    case 0: {
        Serial.println("Thao tac that bai");
        break;
      }
    default:
      {


        //Tính q1- Góc của động cơ 1 từ tọa độ
        double q1;
        q1 = atan2(y, x) + acos((-1 * pow(l2f, 2) + pow(l1f, 2) + pow(x, 2) + pow(y, 2)) / (2 * l1f * sqrt(pow(x, 2) + pow(y, 2)))); // radian
        angle_1 = q1 * (360 / (2 * PI));
        Serial.print("Góc của động cơ 1: ");
        Serial.println(angle_1);

        //Tính q2 - Góc của động cơ 2
        double dif_dx = (d - x);
        double q2;
        q2 = PI - atan2(y, dif_dx) - acos((-1 * pow(l2r, 2) + pow(l1r, 2) + pow(dif_dx, 2) + pow(y, 2)) / (2 * l1r * sqrt(pow(dif_dx, 2) + pow(y, 2))));
        angle_2 = q2 * (360 / (2 * PI));
        Serial.print("Góc của động cơ 2: ");
        Serial.println(angle_2);

        //ĐỔI ĐỘ RA SỐ XUNG, ĐANG CHẠY FULL-STEP, TƯƠNG ĐƯƠNG 1 XUNG ~1,8 ĐỘ,STEP 1 VÀ STEP 2
        pulse1 = (angle_1) / 1.8;
        pulse2 = (angle_2) / 1.8;

        Serial.print("PULSE 1 LA ");
        Serial.println(pulse1);
        Serial.print(" PULSE 2 LA ");
        Serial.println(pulse2);


        int state, state2;
        //QUY ƯỚC CHIỀU STEP QUAY, CHIỀU DƯƠNG LÀ THEO NGƯỢC CHIỀU KIM ĐỒNG HỒ,HIGH LÀ CHIỀU DƯƠNG, LOW CHIỀU ÂM
        //TÍNH GÓC QUY ƯỚC DƯƠNG NGƯỢC KIM ĐỒNG HỒ
        //XUẤT XUNG ĐỂ QUAY ĐẾN Ô CẦN ĐÁNH
        //CÁCH 1
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
        Serial.println(" STATE 1 BAN DAU");
        Serial.println(state);
        Serial.println(" STATE 2 BAN DAU");
        Serial.println(state2);
        Serial.println("------");
        //XÉT ĐIỀU KIỆN LẦN 1
        if (state == 1)
        {
          digitalWrite(dirPin1, HIGH);
        }
        if (state == 0)
        {
          digitalWrite(dirPin1, LOW);
        }
        if (state2 == 1)
        {
          digitalWrite(dirPin2, HIGH);
        }
        if (state2 == 0)
        {
          digitalWrite(dirPin2, LOW);
        }

        delay(500);
        // XUẤT XUNG CHẠY
        //STEP 1,DÙNG ĐỂ XOAY
        Serial.println("Khop 1 quay ");
        for (int i = 0; i < pulse1; i++)
        {
          digitalWrite(stepPin1, HIGH); //6000 là ok nếu ko micro
          delayMicroseconds(2000);
          digitalWrite(stepPin1, LOW);
          delayMicroseconds(2000);
        }
        delay(400);
        Serial.println("Khop 2 quay ");
        for (int i = 0; i < pulse2; i++)
        {
          digitalWrite(stepPin2, HIGH);
          delayMicroseconds(2000);
          digitalWrite(stepPin2, LOW);
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
        if (state == 1)
        {
          digitalWrite(dirPin1, HIGH);
        }
        if (state == 0)
        {
          digitalWrite(dirPin1, LOW);
        }
        if (state2 == 1)
        {
          digitalWrite(dirPin2, HIGH);
        }
        if (state2 == 0)
        {
          digitalWrite(dirPin2, LOW);
        }

        delay(400);

        // STEP 1
        Serial.println("Dao khop quay 1");
        for (int i = 0; i < pulse1; i++)
        {
          digitalWrite(stepPin1, HIGH); //6000 là ok nếu ko micro
          delayMicroseconds(2000);
          digitalWrite(stepPin1, LOW);
          delayMicroseconds(2000);
        }
        delay(400);
        //STEP2
        Serial.println("Dao khop quay 2");
        for (int i = 0; i < pulse2; i++)
        {
          digitalWrite(stepPin2, HIGH);
          delayMicroseconds(2000);
          digitalWrite(stepPin2, LOW);
          delayMicroseconds(2000);
        }
        delay(400);
        Serial.println(" Done ");
      }
  }
}
