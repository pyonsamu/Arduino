#define SPEED 255
int TR = 2;

int pos;

void setup() {
  pinMode(TR,OUTPUT);
  
  Serial.begin(9600);
  // モーターAの制御用ピン設定
  pinMode(12, OUTPUT); // 回転方向 (HIGH/LOW)
  pinMode(9, OUTPUT); // ブレーキ (HIGH/LOW)
  pinMode(3, OUTPUT); // A PWMによるスピード制御 (0-255)
  pos=1023;
}

void loop() {


  Serial.println(analogRead(A3));

  
  
  int vr = analogRead(A2); //A2にボリューム部の2ピンを接続。1=5V,0=GND
  
  int num = dataread();
  if(num!=-1) {
    if(num<0){
      pos = 0;
    }else if(num>1023){
      pos = 1023;
    }else{
      pos = num;
    }
  }


  
 

 // モーターA: 正転
  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);
  while(pos-vr>=10){
    vr = analogRead(A2);
    analogWrite(3, SPEED);
    Serial.println(analogRead(A3));
  }
  digitalWrite(9, HIGH);

   // モーターA: 逆転
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  while(vr-pos>=10){
    vr = analogRead(A2);
    analogWrite(3, SPEED);
    Serial.println(analogRead(A3));
  }
  digitalWrite(9, HIGH);

}

int dataread(){
  byte data_size = Serial.available();
   if(data_size>0){
    delay(20);
    data_size = Serial.available();
    byte buf[data_size];
    for(byte i=0;i<data_size;i++){
      buf[i] = Serial.read()-'0';
    }
    long num = 0;
    long dub = 1;
    for(byte i=0;i<data_size;i++){
      num += buf[(data_size-i)-1]*dub;
      dub *= 10;
    }
    //Serial.println(num);
    return num;
  }else{
    return -1;
  }
}
