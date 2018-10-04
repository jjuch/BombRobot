int Throttle=13;
int Steer=12;
int enableVL=11;
int enableVR=10;
int enableAL=5;
int enableAR=6;
int inL1=8;
int inL2=7;
int inR1=4;
int inR2=3;
unsigned long valThrot;
double valSteer;
double speedRatio=135.0/163.0;

void setup() {
  Serial.begin(9600);
  pinMode(Throttle,INPUT);
  pinMode(Steer, INPUT);
  pinMode(inL1,OUTPUT);
  pinMode(inL2, OUTPUT);
  pinMode(inR1,OUTPUT);
  pinMode(inR2, OUTPUT);
  pinMode(enableVL,OUTPUT);
  pinMode(enableVR,OUTPUT);
  pinMode(enableAL,OUTPUT);
  pinMode(enableAR,OUTPUT);
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
  Serial.print("Speedratio: ");
  Serial.println(speedRatio);

  int pwm = 0;
  int pwmL = 0;
  int pwmR = 0;
  int pwmVL = 0;
  int pwmVR = 0;
  int pwmAL = 0;
  int pwmAR = 0;
  
 double mapSteer =(( valSteer-960)/1000);
 //double mapSteer= map(valSteer,1000,2000,0.0,1.0);
  
  Serial.println(mapSteer);
  
  
  Serial.print("switch: ");
  
  if(valThrot==0){
      Serial.println(" no signal");
      digitalWrite(inL1, LOW);
      digitalWrite(inL2, LOW);
      digitalWrite(inR1, LOW);
      digitalWrite(inR2, LOW);
      analogWrite(enableVL, 0);
      analogWrite(enableVR, 0);
      analogWrite(enableAL, 0);
      analogWrite(enableAR, 0);
  }
  else if(valThrot > 1530){ //right stick
      pwm = map(valThrot, 1530, 2000, 0, 255); //map our speed to 0-255 range
      pwmL=pwm*mapSteer/max(mapSteer,(1-mapSteer));
      pwmR=pwm*(1.0-mapSteer)/max(mapSteer,(1-mapSteer));
      pwmVL = round(pwmL);
      pwmVR = round(pwmR);
      pwmAL = round(pwm*speedRatio);
      pwmAR = round(pwm*speedRatio);
      digitalWrite(inL1, LOW);
      digitalWrite(inL2, HIGH);
      digitalWrite(inR1, LOW);
      digitalWrite(inR2, HIGH);
      analogWrite(enableVL, pwmVL);
      analogWrite(enableAL, pwmAL);
      analogWrite(enableVR, pwmVR);
      analogWrite(enableAR, pwmAR);
      
      Serial.print(" right stick speed: ");
      Serial.print(pwmVL);
      Serial.print(" and ");
      Serial. println(pwmAL);
      Serial.print(" left stick speed: ");
      Serial.print(pwmVR);
      Serial.print(" and ");
      Serial.println(pwmAR);
  }
  else if(valThrot < 1460){
      pwm = map(valThrot, 1470, 1000, 0, 255); //map our speed to 0-255 range
      pwmL=pwm*mapSteer/max(mapSteer,(1-mapSteer));
      pwmR=pwm*(1.0-mapSteer)/max(mapSteer,(1-mapSteer));
      pwmVL = round(pwmL);
      pwmVR = round(pwmR);
      pwmAL = round(pwm*speedRatio);
      pwmAR = round(pwm*speedRatio);
      digitalWrite(inL1, HIGH);
      digitalWrite(inL2, LOW);
      digitalWrite(inR1, HIGH);
      digitalWrite(inR2, LOW);
      analogWrite(enableVL, pwmVL);
      analogWrite(enableAL, pwmAL);
      analogWrite(enableVR, pwmVR);
      analogWrite(enableAR, pwmAR);
      
      Serial.print(" right stick speed: ");
      Serial.print(pwmVL);
      Serial.print(" and ");
      Serial. println(pwmAL);
      Serial.print(" left stick speed: ");
      Serial.print(pwmVR);
      Serial.print(" and ");
      Serial.println(pwmAR);
  }else{
      Serial.println(" stick centered");
      digitalWrite(inL1, LOW);
      digitalWrite(inL2, LOW);
      digitalWrite(inR1, LOW);
      digitalWrite(inR2, LOW);
      analogWrite(enableVL, 0);
      analogWrite(enableAL, 0);
      analogWrite(enableVR, 0);
      analogWrite(enableAR, 0);
  }
  
  delay(10);

}
