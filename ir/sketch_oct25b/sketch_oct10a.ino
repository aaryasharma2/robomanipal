#include <SoftwareSerial.h>
int rx = 6;
int tx = 9;
int x = 0;
SoftwareSerial mySerial(rx,tx);
char c[1];// RX=6 TX=9 

void setup()  
{
  // Open serial communications:
  Serial.begin(9600);

  // Set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

}

void loop() 

{
  Serial.println("Enter character");
  char c ='a';
  mySerial.write(c);
  
  while (mySerial.available()>0) {
    mySerial.println(mySerial.read());
  }
}
