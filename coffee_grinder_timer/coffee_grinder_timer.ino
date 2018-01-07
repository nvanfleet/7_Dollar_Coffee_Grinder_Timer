//title           :coffee_grinder_timer.ino
//description     :This is a small timer program for a coffee grinder
//description     :realized with a Digispark MCU
//author          :Theo Gasteiger
//year            :2017
//notes           :please feel free to adapt it to your needs

// Copyright (c) 2017 Theo Gasteiger

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//==============================================================================

//------------------------------------------------------------------------------
// Input Pins
//
const byte GRINDER = 0;           // Digital Output 0
const byte BUTTON = 1;            // Digital Input 1
const byte POTENTIOMETER_PIN = 2; // Analog Input pin 2

const byte POTENTIOMETER = 1;     // Analog Input 0

//------------------------------------------------------------------------------
// Variables
//
const int min_grind_time = 4000;
const int grind_time_multiplier = 8;

unsigned long time_to_stop = -1;
int pot_value = 0;

//------------------------------------------------------------------------------
// Setup
//
void setup()
{
  pinMode(GRINDER, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);
}

//------------------------------------------------------------------------------
// Loop
//
void loop() {
  unsigned long current_time = millis();
  int grinder_running = digitalRead(GRINDER) == HIGH ? true : false;
  pot_value = 1023 - analogRead(POTENTIOMETER);
  
  // Check if we have a time to stop
  if (grinder_running && current_time >= time_to_stop) {
    stop_grinder();
    return;
  }

  // Start the grinder and set a time to stop
  if (digitalRead(BUTTON) && grinder_running == false) {
    time_to_stop = current_time + min_grind_time + pot_value * grind_time_multiplier;
    digitalWrite(GRINDER, HIGH);
    delay(1000);
    return;
  }

  // Shut off the running grinder off early
  if (digitalRead(BUTTON) && grinder_running) {
    stop_grinder();
    delay(1000);
    return;
  }
}

void stop_grinder() {
    time_to_stop = -1;
    digitalWrite(GRINDER, LOW);
}

