#define SPEED 255

int preasure;
int tgt_preasure;
int mtspeed;

void setup() {
  
  Serial.begin(9600);
  // モーターAの制御用ピン設定
  pinMode(12, OUTPUT); // 回転方向 (HIGH/LOW)
  pinMode(9, OUTPUT); // ブレーキ (HIGH/LOW)
  pinMode(3, OUTPUT); // A PWMによるスピード制御 (0-255)
  digitalWrite(9, LOW);
  tgt_preasure = 70;
  mtspeed=255;
  
   // モーターA: 逆転
  digitalWrite(12, LOW);
}

void loop() {
  
  preasure = preasureread();
  Serial.print(preasure);
   Serial.print(";");
  
  //int vr = analogRead(A2); //A2にボリューム部の2ピンを接続。1=5V,0=GND
  
  int num = serialread();
  if(num!=-1) {
    if(num<0){
      tgt_preasure = 0;
    }else if(num>1023){
      tgt_preasure = 1023;
    }else{
      tgt_preasure = num;
    }
  }

  int diff = tgt_preasure-preasure;
 Serial.print(diff);
 Serial.print(";");
  if(diff>=10){
    mtspeed+=diff-10;
  }else if(diff<=-10){
    mtspeed+=diff+10;
  }
  
  if(mtspeed>255){
    mtspeed=255;
  }else if(mtspeed<-255){
    mtspeed=-255;
  }
  if(mtspeed>0){
    //mtspeed=255;
    digitalWrite(12, LOW);
    analogWrite(3, mtspeed);
  }else if(mtspeed<0){
    digitalWrite(12, HIGH);
    analogWrite(3, -mtspeed);
  }
   Serial.println(mtspeed);
  //analogWrite(3, mtspeed);
}

double preasureread(){
  int R1 = 920; // 10kΩ
  double fg;
  float voltage = (analogRead(A3) / 1024.0) * 5.0;
 
  // 誤差を除去
  if(voltage >= 4.9){
    voltage = 4.99;
  }

  //Serial.print(analogRead(A3));
  //Serial.print("入力電圧：");
  //Serial.print(voltage);
  //Serial.print("V 抵抗値：");
 
  // 圧力センサーの抵抗値を出力する
  if(false){
    // Serial.println("1MΩ ");
  }else{
    float val = voltage / (5.0 - voltage) * R1;
    if(val > 999){
      val = val / 1000;
     // Serial.print(val,0);
     // Serial.print("k");      
    }else{
     // Serial.print(val, 0);
    }    
   // Serial.print("Ω ");
    fg = 880.79/val + 47.96;
    //Serial.println(fg);
    return fg;
  }   
}

int serialread(){
   if(Serial.available()>0){
    long timer = millis();
    //delay(20);
    //byte data_size = Serial.available();
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
    //Serial.println(num);
    return num;
  }else{
    return -1;
  }
}
