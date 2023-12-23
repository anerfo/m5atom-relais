#include "M5Atom.h"

#define OFF 1
#define ON 0

bool _state = OFF;
bool _target = OFF;
uint8_t DisBuff[2 + 5 * 5 * 3];
uint8_t _displayBrightness = 50;

void clearBuffer() {
    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    for (int i = 0; i < 25; i++) {
        DisBuff[2 + i * 3 + 0] = 0;
        DisBuff[2 + i * 3 + 1] = 0;
        DisBuff[2 + i * 3 + 2] = 0;
    }
}

void displayClosed() {
    DisBuff[2 + 22 * 3 + 0] = _displayBrightness;
    DisBuff[2 + 17 * 3 + 0] = _displayBrightness;
    DisBuff[2 + 12 * 3 + 0] = _displayBrightness;
    DisBuff[2 +  8 * 3 + 0] = _displayBrightness;
    DisBuff[2 +  4 * 3 + 0] = _displayBrightness;
}

void displayOpen() {
    DisBuff[2 + 22 * 3 + 0] = _displayBrightness;
    DisBuff[2 + 17 * 3 + 0] = _displayBrightness;
    DisBuff[2 + 12 * 3 + 0] = _displayBrightness;
    DisBuff[2 +  6 * 3 + 0] = _displayBrightness;
    DisBuff[2 +  0 * 3 + 0] = _displayBrightness;
    DisBuff[2 +  8 * 3 + 1] = _displayBrightness;
    DisBuff[2 +  4 * 3 + 1] = _displayBrightness;
}

void UpdateDisplay()
{
  clearBuffer();
  _state == ON ? displayOpen() : displayClosed();
  M5.dis.displaybuff(DisBuff);
}

void writeRelaisState()
{
  Serial.println((String("relais:") + (_state == ON ? "on" : "off")).c_str());
}

void setup() {
  M5.begin(true, false, true);
  pinMode(33, OUTPUT);
  UpdateDisplay();
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readString();
        if(command.indexOf("relais:off") >= 0)
        {
          _target = OFF;
        }
        else if(command.indexOf("relais:on") >= 0)
        {
          _target = ON;
        }
        else if(command.indexOf("relais:get") >= 0)
        {
          writeRelaisState();
        }
        else if(command.indexOf("display:") >= 0)
        {
          command.replace("display:", "");
          _displayBrightness = command.toInt();
          UpdateDisplay();
        }
    }
    if (M5.Btn.wasPressed()) {
      if(_state == ON) _target = OFF;
      else _target = ON;
    }
    if(_state != _target)
    {
      digitalWrite(33, _target);
      _state = _target;
      writeRelaisState();
      UpdateDisplay();
    }
    delay(50);
    M5.update();
}
