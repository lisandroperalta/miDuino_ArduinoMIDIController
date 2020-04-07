// Lisandro Peralta
// 07 - Abril - 2020

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int analog0 = 0; //Our initial pot values. We need one for the first value and a second to test if there has been a change made. This needs to be done for all 3 pots.
int lastAnalog0 = 0;

int potVal1 = 0;
int potVal2 = 0;
int potVal3 = 0;
int potVal4 = 0;
int potVal5 = 0;
int potVal6 = 0;


int lastPotVal1 = 0;
int lastPotVal2 = 0;
int lastPotVal3 = 0;
int lastPotVal4 = 0;
int lastPotVal5 = 0;
int lastPotVal6 = 0;

bool estadoPrevBtn2 = 0;
bool estadoPrevBtn3 = 0;
bool estadoPrevBtn4 = 0;
bool estadoPrevBtn5 = 0;

int mapOriginMin = 3;
int mapOriginMax = 1020;
float damperRatio=0.1;

void setup()
{
  MIDI.begin(1);
  // initialize the pushbutton pin as an input:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  Serial.begin(115200);
}

void loop()
{
  potenciometros();
  botones();
}
void potenciometros()
{

  int diff = 22; // difference amount

  // READ POTENTIOMETERS //

  potVal1 = analogRead(0);
  potVal2 = analogRead(1);
  potVal3 = analogRead(2);
  potVal4 = analogRead(3);
  potVal5 = analogRead(4);
  potVal6 = analogRead(5);
  // CALCULATE DIFFERENCE BETWEEN NEW VALUE AND LAST RECORDED VALUE //

  int potVal1diff = potVal1 - lastPotVal1;
  int potVal2diff = potVal2 - lastPotVal2;
  int potVal3diff = potVal3 - lastPotVal3;
  int potVal4diff = potVal4 - lastPotVal4;
  int potVal5diff = potVal5 - lastPotVal5;
  int potVal6diff = potVal6 - lastPotVal6;

  // SEND MIDI MESSAGE //

  if (abs(potVal1diff) > diff) // execute only if new and old values differ enough
  {
    potVal1 += damperRatio * (lastPotVal1 - potVal1);
    MIDI.sendControlChange(1, map(potVal1, mapOriginMin, mapOriginMax, 0, 127), 1);
    // map sensor range to MIDI range
    lastPotVal1 = potVal1; // reset old value with new reading
  }

  if (abs(potVal2diff) > diff)
  {
    potVal2 += damperRatio * (lastPotVal2 - potVal2);
    MIDI.sendControlChange(2, map(potVal2, mapOriginMin, mapOriginMax, 0, 127), 1);
    lastPotVal2 = potVal2;
  }

  if (abs(potVal3diff) > diff)
  {
    potVal3 += damperRatio * (lastPotVal3 - potVal3);
    MIDI.sendControlChange(3, map(potVal3, mapOriginMin, mapOriginMax, 0, 127), 1);
    lastPotVal3 = potVal3;
  }
  if (abs(potVal4diff) > diff)
  {
    potVal4 += damperRatio * (lastPotVal4 - potVal4);
    MIDI.sendControlChange(4, map(potVal4, mapOriginMin, mapOriginMax, 0, 127), 1);
    lastPotVal4 = potVal4;
  }
  if (abs(potVal5diff) > diff)
  {
    potVal5 += damperRatio * (lastPotVal5 - potVal5);
    MIDI.sendControlChange(5, map(potVal5, mapOriginMin, mapOriginMax, 0, 127), 1);
    lastPotVal5 = potVal5;
  }
  if (abs(potVal6diff) > diff)
  {
    potVal6 += damperRatio * (lastPotVal6 - potVal6);
    MIDI.sendControlChange(6, map(potVal6, mapOriginMin, mapOriginMax, 0, 127), 1);
    lastPotVal6 = potVal6;
  }

  delay(50); // small delay further stabilizes sensor readings
}

void botones()
{

  ///// BOTONES
  //2
  if (digitalRead(2) == HIGH && estadoPrevBtn2 == false)
  {
    MIDI.sendNoteOn(2, 127, 1); // Send a Note (pitch 1, velo 127 on channel 1);
    estadoPrevBtn2 = true;
  }
  if (digitalRead(2) == LOW && estadoPrevBtn2 == true)
  {
    MIDI.sendNoteOff(2, 127, 1); // Send a Note (pitch 1, velo 127 on channel 1)
    estadoPrevBtn2 = false;
  }
  //3
  if (digitalRead(3) == HIGH && estadoPrevBtn3 == false)
  {
    MIDI.sendNoteOn(3, 127, 1); // Send a Note (pitch 1, velo 127 on channel 1);
    estadoPrevBtn3 = true;
  }
  if (digitalRead(3) == LOW && estadoPrevBtn3 == true)
  {
    MIDI.sendNoteOff(3, 127, 1); // Send a Note (pitch 1, velo 127 on channel 1)
    estadoPrevBtn3 = false;
  }
  //4
  if (digitalRead(4) == HIGH && estadoPrevBtn4 == false)
  {
    MIDI.sendNoteOn(4, 127, 1); // Send a Note (pitch 1, velo 127 on channel 1);
    estadoPrevBtn4 = true;
  }
  if (digitalRead(4) == LOW && estadoPrevBtn4 == true)
  {
    MIDI.sendNoteOff(4, 127, 1); // Send a Note (pitch 1, velo 127 on channel 1)
    estadoPrevBtn4 = false;
  }
  //5
  if (digitalRead(5) == HIGH && estadoPrevBtn5 == false)
  {
    MIDI.sendNoteOn(5, 127, 1); // Send a Note (pitch 1, velo 127 on channel 1);
    estadoPrevBtn5 = true;
  }
  if (digitalRead(5) == LOW && estadoPrevBtn5 == true)
  {
    MIDI.sendNoteOff(5, 127, 1); // Send a Note (pitch 1, velo 127 on channel 1)
    estadoPrevBtn5 = false;
  }
  // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END // LOOP END
}

/* VIEJOS POTENCIOMETROS
  //////////////0
  analog0 = analogRead(0) / 8;                                                // Divide by 8 to get range of 0-127 for midi
  if (analog0 - lastAnalog0 >= tolerancia || lastAnalog0 - analog0 >= tolerancia) // If the value does not = the last value the following command is made. This is because the pot has been turned. Otherwise the pot remains the same and no midi message is output.
  {
    // sendControlChange   (       inControlNumber,      inControlValue,       inChannel   )
    MIDI.sendControlChange(1, analog0, 1);
    lastAnalog0 = analog0;
            delay(200);
  }

  /////////////1
  analog1 = analogRead(1) / 8; // Divide by 8 to get range of 0-127 for midi
  if (analog1 - lastAnalog1 >= tolerancia || lastAnalog1 - analog1 >= tolerancia) // If the value does not = the last value the following command is made. This is because the pot has been turned. Otherwise the pot remains the same and no midi message is output.
  {
    // sendControlChange   (       inControlNumber,      inControlValue,       inChannel   )
    MIDI.sendControlChange(2, analog1, 1);
    lastAnalog1 = analog1;
            delay(200);
  }

  ////////////////2
  analog2 = analogRead(2) / 8; // Divide by 8 to get range of 0-127 for midi
  if (analog2 - lastAnalog2 >= tolerancia || lastAnalog2 - analog2 >= tolerancia) // If the value does not = the last value the following command is made. This is because the pot has been turned. Otherwise the pot remains the same and no midi message is output.
  {
    // sendControlChange   (       inControlNumber,      inControlValue,       inChannel   )
    MIDI.sendControlChange(3, analog2, 1);
    lastAnalog2 = analog2;
            delay(200);
  }

  ////////////////3
  analog3 = analogRead(3) / 8; // Divide by 8 to get range of 0-127 for midi
  if (analog3 - lastAnalog3 >= tolerancia || lastAnalog3 - analog3 >= tolerancia) // If the value does not = the last value the following command is made. This is because the pot has been turned. Otherwise the pot remains the same and no midi message is output.
  {
    // sendControlChange   (       inControlNumber,      inControlValue,       inChannel   )
    MIDI.sendControlChange(4, analog3, 1);
    lastAnalog3 = analog3;
            delay(200);
  }

  ////////////////4
  analog4 = analogRead(4) / 8; // Divide by 8 to get range of 0-127 for midi
  if (analog4 - lastAnalog4 >= tolerancia || lastAnalog4 - analog4 >= tolerancia) // If the value does not = the last value the following command is made. This is because the pot has been turned. Otherwise the pot remains the same and no midi message is output.
  {
    // sendControlChange   (       inControlNumber,      inControlValue,       inChannel   )
    MIDI.sendControlChange(5, analog4, 1);
    lastAnalog4 = analog4;
            delay(200);
  }

  ////////////////5
  analog5 = analogRead(5) / 8; // Divide by 8 to get range of 0-127 for midi
  if (analog5 - lastAnalog5 >= tolerancia || lastAnalog5 - analog5 >= tolerancia) // If the value does not = the last value the following command is made. This is because the pot has been turned. Otherwise the pot remains the same and no midi message is output.
  {
    // sendControlChange   (       inControlNumber,      inControlValue,       inChannel   )
    MIDI.sendControlChange(6, analog5, 1);
    lastAnalog5 = analog5;
            delay(200);
  }
*/
