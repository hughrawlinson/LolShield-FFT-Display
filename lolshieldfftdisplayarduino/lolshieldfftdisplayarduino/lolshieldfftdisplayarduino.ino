#include <SoftwareSerial.h>
#include <Charliplexing.h>
#include <Figure.h>
#include <Font.h>
#include <Myfont.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  LedSign::Init();
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {

    String col = getValue(inputString, ' ', 1);
    String am = getValue(inputString, ' ', 0);
    
    int column = stringToInt(col);
    int amp = stringToInt(am);
    
    Serial.println(column);
    Serial.println(amp);
    
    amp = 9 - amp;
    
    for(int i = 0; i < 9; i++) {
      //turn off lights
      LedSign::Set(column, i, 0);
      if(i>amp){
        LedSign::Set(column, i, 1);
      }
    }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

int stringToInt(String s)
{
    char arr[12];
    s.toCharArray(arr, sizeof(arr));
    return atoi(arr);
}
