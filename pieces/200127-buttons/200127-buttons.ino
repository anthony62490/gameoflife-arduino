/* Simple demo of the 4x4 button matrix. The resistor values aren't quite what is listed on the chip, but they seem 
fairly consistent. Wiring:
VCC - 5V
GND - GND
OUT - A0

Outputs per Button:
01 - 1023
02 - 930-931
03 - 853-854
04 - 787-788
05 - 676-677
06 - 633-634
07 - 597-598
08 - 564-565
09 - 504-505
10 - 480-481
11 - 459-460
12 - 439-440
13 - 402-403
14 - 323-324
15 - 270-271
16 - 232-233
*/

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensor = analogRead(A0);
  Serial.println(sensor);
  delay(100);
}
