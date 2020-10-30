int TR = 2;

 

void setup() {  //setup関数

  pinMode(TR,OUTPUT);

}

void loop() {

  digitalWrite(TR,HIGH);

  delay(1000);

  digitalWrite(TR,LOW);

  delay(1000);

}
