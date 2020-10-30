void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  serialread();
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
