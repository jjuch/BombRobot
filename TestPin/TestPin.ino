int Throttle=13;
int Steer=12;
int enable1=11;
int enable2=10;
int in1=8;
int in2=7;
int in3=6;
int in4=5;
unsigned long valThrot;
double valSteer;

void setup() {
  Serial.begin(115200);
  pinMode(Throttle,INPUT);
  pinMode(Steer, INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enable1,OUTPUT);
  pinMode(enable2,OUTPUT);
  
  Serial.println("Intitiation Finished");
}

void loop() {
  valThrot = pulseIn(Throttle,HIGH);
  valSteer=pulseIn(Steer, HIGH);
  Serial.println("read");
  Serial.print("Throttle:");
  Serial.print(valThrot);
  Serial.print("  Steering:");
  Serial.println(valSteer);

  int pwm=0;
  int pwm1 = 0;
  int pwm2= 0;
  //int swd = pulseIn(switchD, HIGH, 25000);
  //int rc4 = pulseIn(rc_channel4, HIGH, 25000);
  
 double mapSteer =(( valSteer-960)/1000);
 //double mapSteer= map(valSteer,1000,2000,0.0,1.0);
  
  Serial.println(mapSteer);
  
  
  Serial.print("switch: ");
  
  if(valThrot==0){
      Serial.println(" no signal");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enable1, 0);
      analogWrite(enable2, 0);
  }
  else if(valThrot > 1530){ //right stick
      pwm = map(valThrot, 1530, 2000, 0, 255); //map our speed to 0-255 range
      pwm1 = round(pwm*mapSteer/max(mapSteer,(1-mapSteer)));
      pwm2 = round(pwm*(1.0-mapSteer)/max(mapSteer,(1-mapSteer)));
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enable1, pwm1);
      analogWrite(enable2, pwm2);
      Serial.print(" right stick speed: ");
      Serial.println(pwm1);
      Serial.print(" left stick speed: ");
      Serial.println(pwm2);
  }
  else if(valThrot < 1460){
      pwm = map(valThrot, 1460, 1000, 0, 255); //map our speed to 0-255 range
      pwm1 = round(pwm*mapSteer/max(mapSteer,(1-mapSteer)));
      pwm2 = round(pwm*(1.0-mapSteer)/max(mapSteer,(1-mapSteer)));
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enable1, pwm1);
      analogWrite(enable2, pwm2);
      Serial.print(" left stick speed: ");
      Serial.println(pwm2);
  }else{
      Serial.println(" stick centered");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enable1, 0);
      analogWrite(enable2, 0);
  }
  
  delay(10);

}
