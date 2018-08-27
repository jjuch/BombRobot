int enable1=11;
int enable2=10;
int in1=8;
int in2=7;
int in3=6;
int in4=5;

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enable1,OUTPUT);
  pinMode(enable2,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int pwm=255;
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enable1, pwm);
  analogWrite(enable2, pwm);
  delay(10000);
  analogWrite(enable1, 0);
  analogWrite(enable2, 0);
  delay(1000000);
}
