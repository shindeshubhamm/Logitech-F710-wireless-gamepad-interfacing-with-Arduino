#include "hidjoystickrptparser.h"

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
  joyEvents(evt),
  oldHat(0xDE),
  oldButtons(0)
{
  for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
    oldPad[i] = 0xD;

}

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
  bool match = true;

  // Checking if there are changes in report since the method was last called
  for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
    if (buf[i] != oldPad[i])
    { 
      match = false;
      break;
    }

  // Calling Game Pad event handler
  // if (!match ) {
  joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

  for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++) oldPad[i] = buf[i];
  //}

  uint8_t hat = (buf[5] & 0xF);

  // Calling Hat Switch event handler
  //if (hat != oldHat ) {

  //}

  joyEvents->OnHatSwitch(hat);
  oldHat = hat;

  uint16_t buttons = (0x0000 | buf[6]);
  buttons <<= 4;
  buttons |= (buf[5] >> 4);
  uint16_t changes = (buttons ^ oldButtons);

  // Calling Button Event Handler for every button changed
  //if (changes) {
  for (uint8_t i = 0; i < 0x0C; i++)
  {
    uint16_t mask = (0x0001 << i);

    if (((mask & changes) > 0) )
    {
      if ((buttons & mask) > 0)
      {
        //          joyEvents->OnButtonDn(i + 1);
        if (i + 1 == 1)  blue = 1;
        if (i + 1 == 2)  green = 1;
        if (i + 1 == 3)  red = 1;
        if (i + 1 == 4)  yellow = 1;
        if (i + 1 == 5)  lb = 1;
        if (i + 1 == 6)  rb = 1;
        if (i + 1 == 7)  lt = 1;
        if (i + 1 == 8)  rt = 1;
        if (i + 1 == 9)  bk = 1;
        if (i + 1 == 10)  st = 1;
        if (i + 1 == 11)  jl = 1;
        if (i + 1 == 12)  jr = 1;
      }
      else
      {
        //        joyEvents->OnButtonUp(i + 1);
        if (i + 1 == 1)  blue = 0;
        if (i + 1 == 2)  green = 0;
        if (i + 1 == 3)  red = 0;
        if (i + 1 == 4)  yellow = 0;
        if (i + 1 == 5)  lb = 0;
        if (i + 1 == 6)  rb = 0;
        if (i + 1 == 7)  lt = 0;
        if (i + 1 == 8)  rt = 0;
        if (i + 1 == 9)  bk = 0;
        if (i + 1 == 10)  st = 0;
        if (i + 1 == 11)  jl = 0;
        if (i + 1 == 12)  jr = 0;
      }
    }
  }
  oldButtons = buttons;

  //}
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{
  //  Serial.print("X1: ");
  //  Serial.print(evt->X, DEC);
  //  //PrintHex<uint8_t > (evt->X,0x80);
  //  Serial.print("\tY1:  ");
  //  Serial.print(evt->Y, DEC);
  //  //PrintHex<uint8_t > (evt->Y,0x80);
  //  Serial.print("\tX2: ");
  //  Serial.print(evt->Z1, DEC);
  //  //PrintHex<uint8_t > (evt->Z1,0x80);
  //  Serial.print("\tY2: ");
  //  Serial.print(evt->Z2, DEC);
  //
  //  //PrintHex<uint8_t > (evt->Z2,0x80);
  //  Serial.print("\tRz: ");
  //  Serial.print(evt->Rz, DEC);
  //  // PrintHex<uint8_t > (evt->Rz,0x80);
  //  Serial.println(" ");

  lx = evt->Y;
  ly = evt->Z1;
  rx = evt->Z2;
  ry = evt->Rz;
}

void JoystickEvents::OnHatSwitch(uint8_t hat)
{
  //Serial.print("Hat Switch: ");

  if (hat != 8) {
    ht = hat;
  }
  else {
    ht = 9;
  }
  //PrintHex<uint8_t > (hat, 0x80);
  //Serial.println("");
}

void JoystickEvents::OnButtonUp(uint8_t but_id) {
  bu = 0;
  //  Serial.print("Up: ");
  //  Serial.println(0, DEC);
}

void JoystickEvents::OnButtonDn(uint8_t but_id) {
  bu = but_id;
  //  Serial.print("Dn: ");
  //  Serial.println(but_id, DEC);
}
