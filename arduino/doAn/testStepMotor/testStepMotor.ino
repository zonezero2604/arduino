// Run a A4988 Stepstick from an Arduino Uno
int x = 200;
int en = 8;
int dirX = 5;
int stepX = 2;
int n=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(en, OUTPUT);
  pinMode(stepX, OUTPUT);
  pinMode(dirX, OUTPUT);
  digitalWrite(en, LOW);
}

void loop() {
  Serial.print("Quay bao nhieu vong?: ");
  while (Serial.available() == 0) {
  }
  n = Serial.parseInt();
  Serial.println();
  x = n * 200;
  digitalWrite(dirX, HIGH );
  for (int i = 1; i <= x; i = i + 1) {
    digitalWrite(stepX, HIGH);
    delay(10);
    digitalWrite(stepX, LOW);
    delay(10);
  }
  delay(2000);


}
