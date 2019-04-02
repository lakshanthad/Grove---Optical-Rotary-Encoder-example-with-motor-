 /*
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#include <Encoder.h>
#include <SparkFunMiniMoto.h>  // Include the MiniMoto library

// Create two MiniMoto instances, with different address settings.
MiniMoto motor0(0xC4); // A1 = 1, A0 = clear
MiniMoto motor1(0xC0); // A1 = 1, A0 = 1 (default)

#define FAULTn  16     // Pin used for fault detection.
#define PIN_ROT A0

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);
//   avoid using pins with LEDs attached
long position4Speed = 0;
unsigned long time, time_cur;


void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  time = time_cur = millis();
  pinMode(FAULTn, INPUT);
  pinMode(PIN_ROT, INPUT);
  motor0.drive(10);
}

long oldPosition  = -999;
float speed = 0;
int angle = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
//    Serial.println(newPosition - oldPosition);

    time_cur = millis();
    speed = (newPosition - oldPosition)/4/((time_cur - time)/1000.0f/60);
    time = time_cur;
    Serial.print("The speed is ");
    Serial.print(speed);
    Serial.println(" rpm");
  
    oldPosition = newPosition;
  }
   int a = analogRead(PIN_ROT);
  if (a != angle) {
    motor0.drive(map(a, 0, 1023, 10, 68));
  }
  
  delay(2000);
}
