int TR = 2;

int flag=0;
bool flag_sol=false;

void setup() {  //setup関数

  Serial.begin(9600);
  pinMode(TR,OUTPUT);

}

void loop() {


  flag=serialread();

  if(flag==1 || flag==0){
     
  }else{
    return;
  }

  if(flag==1 && !flag_sol){
    digitalWrite(TR,HIGH);
    flag_sol=true;
  }else if(flag==0 && flag_sol){
    digitalWrite(TR,LOW);
    flag_sol=false;
  }
  

  delay(100);



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
    //Serial.println(num);
    return num;
  }else{
    return -1;
  }
}
