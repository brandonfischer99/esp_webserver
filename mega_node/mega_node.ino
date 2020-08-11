#include <Wire.h>

#define A_PIN 49
#define B_PIN 47
#define C_PIN 48
#define D_PIN 50
#define E_PIN 52
#define F_PIN 51
#define G_PIN 53
#define H_PIN 46

//Receives serial message from esp8266 board
char incomingByte = 0;

void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Serial.begin(9600);           /* start serial for debug */

  pinMode(E_PIN, OUTPUT);//bottom left segment
  pinMode(D_PIN, OUTPUT);//bottom segment
  pinMode(C_PIN, OUTPUT);//bottom right segment
  pinMode(H_PIN, OUTPUT);//dot in corner
  pinMode(G_PIN, OUTPUT);//middle line
  pinMode(F_PIN, OUTPUT);//top left
  pinMode(A_PIN, OUTPUT);//top center
  pinMode(B_PIN, OUTPUT);//top right

  clearDisplay();
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (Wire.available() > 0) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c, DEC);           /* print the character */
    switch(c)
    {
      case 0:
        //light up a zero
        clearDisplay();
        digitalWrite(A_PIN, HIGH);
        digitalWrite(B_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        digitalWrite(D_PIN, HIGH);
        digitalWrite(E_PIN, HIGH);
        digitalWrite(F_PIN, HIGH);
        break;
      case 1:
        //light up a one
        clearDisplay();
        digitalWrite(B_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        break;
      case 2:
        //light up a 2
        clearDisplay();
        digitalWrite(A_PIN, HIGH);
        digitalWrite(B_PIN, HIGH);
        digitalWrite(G_PIN, HIGH);
        digitalWrite(E_PIN, HIGH);
        digitalWrite(D_PIN, HIGH);
        break;
      case 3:
        //light up a 3
        clearDisplay();
        digitalWrite(A_PIN, HIGH);
        digitalWrite(B_PIN, HIGH);
        digitalWrite(G_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        digitalWrite(D_PIN, HIGH);
        break;
      case 4:
        //light up a 4
        clearDisplay();
        digitalWrite(F_PIN, HIGH);
        digitalWrite(G_PIN, HIGH);
        digitalWrite(B_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        break;
      case 5:
        //light up a 5
        clearDisplay();
        digitalWrite(A_PIN, HIGH);
        digitalWrite(F_PIN, HIGH);
        digitalWrite(G_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        digitalWrite(D_PIN, HIGH);
        break;
      case 6:
        //light up a 6
        clearDisplay();
        digitalWrite(A_PIN, HIGH);
        digitalWrite(F_PIN, HIGH);
        digitalWrite(G_PIN, HIGH);
        digitalWrite(E_PIN, HIGH);
        digitalWrite(D_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        break;
      case 7:
        //light up a 7
        clearDisplay();
        digitalWrite(A_PIN, HIGH);
        digitalWrite(B_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        break;
      case 8:
        //light up an 8
        clearDisplay();
        digitalWrite(A_PIN, HIGH);
        digitalWrite(B_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        digitalWrite(D_PIN, HIGH);
        digitalWrite(E_PIN, HIGH);
        digitalWrite(F_PIN, HIGH);
        digitalWrite(G_PIN, HIGH);
        break;
      case 9:
        //light up a 9
        clearDisplay();
        digitalWrite(A_PIN, HIGH);
        digitalWrite(B_PIN, HIGH);
        digitalWrite(C_PIN, HIGH);
        digitalWrite(F_PIN, HIGH);
        digitalWrite(G_PIN, HIGH);
        break;
      default:
        clearDisplay();
        break;  
    }
  }
 Serial.println();             /* to newline */
 
}

void clearDisplay()
{ 
  int i = 46;
  for(;i < 54; i++)
  {
    digitalWrite(i, LOW);
  }
}
