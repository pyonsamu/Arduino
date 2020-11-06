#define SPEED 240
//int TR = 2;

int pos;

bool flag=false;
bool flag_sol=false;
long timer=0;

void setup() {
  
  Serial.begin(9600);
  // モーターAの制御用ピン設定
  pinMode(12, OUTPUT); // 回転方向 (HIGH/LOW)
  pinMode(9, OUTPUT); // ブレーキ (HIGH/LOW)
  pinMode(3, OUTPUT); // A PWMによるスピード制御 (0-255)
  pos=1023;

  //pinMode(TR,OUTPUT);
}

void loop() {
  
  
  int vr = analogRead(A2); //A2にボリューム部の2ピンを接続。1=5V,0=GND
  
  int num = serialread();
  if(num!=-1) {
    if(num<0){
      pos = 0;
    }else if(num>1023){
      pos = 1023;
    }else{
      pos = num;
    }
  }

  
 
  int diff = pos-vr;

  
  if(diff>=10){
    // モーターA: 正転
    digitalWrite(12, HIGH);
    digitalWrite(9, LOW);
    if(flag){
      //digitalWrite(TR,LOW);
     // Serial.println("move");
      flag=false;
    }
    if(flag_sol){
      //digitalWrite(TR,LOW);
      //Serial.println("0");
      flag_sol=false;
    }
    
    analogWrite(3, SPEED);
  }else if(diff<=-10){
     // モーターA: 逆転
    digitalWrite(12, LOW);
    digitalWrite(9, LOW);
    if(flag){
      //digitalWrite(TR,LOW);
      //Serial.println("move");
      flag=false;
    }
    if(flag_sol){
      //digitalWrite(TR,LOW);
      //Serial.println("0");
      flag_sol=false;
    }
    analogWrite(3, SPEED);
  }else{
    digitalWrite(9, HIGH);
    if(!flag){
      //digitalWrite(TR,HIGH);
      //Serial.println("stop");
      flag=true;
      timer=millis();
    }
    if(!flag_sol && millis()-timer>100){
      Serial.println("1");
      //digitalWrite(TR,HIGH);
      timer=millis();
      flag_sol=true;
    }
  }
}

int serialread(){
   if(Serial.available()>0){
    long timer = millis();
    byte buf[10];
    byte data;
    int count=0;
    while(millis() - timer < 20){
      if(Serial.available()>0){
        data = Serial.read()-'0';
        if(data!=11){
          buf[count] = data;
          count++;
        }else{
          break;
        }
      }
    }
    long num = 0;
    long dub = 1;
    for(byte i=0;i<count;i++){
      
      num += buf[(count-i)-1]*dub;
      dub *= 10;
      
    }
    Serial.println(num);
    return num;
  }else{
    return -1;
  }
}
