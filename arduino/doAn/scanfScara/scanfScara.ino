#include <math.h>

float pulse1,pulse2;

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
  // put your setup code here, to run once:
  //KHOI TAO SERIAL
  Serial.begin(9600);
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

  //Tính q1- Góc của động cơ 1
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


int state,state2;
    //QUY ƯỚC CHIỀU STEP QUAY, CHIỀU DƯƠNG LÀ THEO CHIỀU KIM ĐỒNG HỒ,HIGH LÀ CHIỀU DƯƠNG, LOW CHIỀU ÂM
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

}
