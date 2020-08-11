//Receives serial message from esp8266 board
char incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  //when I receive data, read it and store it in incomingByte
  if(Serial.available() > 0)
  {
    incomingByte = Serial.read();

    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  
}
