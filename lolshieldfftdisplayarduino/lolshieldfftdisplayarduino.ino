#include <Charliplexing.h>
#include <Figure.h>
#include <Font.h>
#include <Myfont.h>

#include <SoftwareSerial.h>
SoftwareSerial portOne(2, 3);
int count;

void setup(){
  LedSign::Init(DOUBLE_BUFFER);
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // Start each software serial port
  portOne.begin(9600);
}

void loop(){
  LedSign::Set(5, 5, 1);
  portOne.listen();
  while (portOne.available() > 0) {
    char inByte = portOne.read();
    int amp = inByte - '0';
    Serial.write(inByte);
    for(int i = 0; i < 9; i++){
      LedSign::Set(count, i , 0);
    }
    for(int i = 0; i < 5; i++){
      LedSign::Set(count, i , 1);
    }
    //count++;
  }
}






