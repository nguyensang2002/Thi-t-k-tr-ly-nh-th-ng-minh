#include <IRremote.hpp>

const int RECV = 35;
IRrecv irrecv(RECV);
//decode_results results;  // deprecated

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if(irrecv.decode()){
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
    irrecv.resume();
  }
}


CODE : 
0  :E916FF00
1  :F30CFF00
2  :E718FF00
3  :A15EFF00
4  :F708FF00
5  :E31CFF00
6  :A55AFF00
7  :BD42FF00
8  :AD52FF00
9  :B54AFF00

CH- :BA45FF00
CH  :B946FF00
CH+ :B847FF00
=<  :BB44FF00
=>  :BF40FF00
>>= :BC43FF00
-   :F807FF00
+   :EA15FF00
EQ  :F609FF00
100+:E619FF00
200+:F20DFF00