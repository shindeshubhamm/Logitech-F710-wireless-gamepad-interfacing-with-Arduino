#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

#include <usbhid.h>

struct GamePadEventData
{
  uint8_t X, Y, Z1, Z2, Rz;
};


class JoystickEvents
{
  public:
    uint8_t lx = 128;
    uint8_t ly = 128;
    uint8_t rx = 128;
    uint8_t ry = 128;
    uint8_t ht = 9;
    uint8_t bu = 0;



    virtual void OnGamePadChanged(const GamePadEventData *evt);
    virtual void OnHatSwitch(uint8_t hat);
    virtual void OnButtonUp(uint8_t but_id);
    virtual void OnButtonDn(uint8_t but_id);
};

#define RPT_GEMEPAD_LEN		5

class JoystickReportParser : public HIDReportParser
{
    JoystickEvents *joyEvents;

    uint8_t oldPad[RPT_GEMEPAD_LEN];
    uint8_t oldHat;
    uint16_t oldButtons;


  public:
    JoystickReportParser(JoystickEvents *evt);
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
    uint8_t yellow = 0;
    uint8_t lb = 0;
    uint8_t lt = 0;
    uint8_t rb = 0;
    uint8_t rt = 0;
    uint8_t st = 0;
    uint8_t bk = 0;
    uint8_t jl = 0;
    uint8_t jr = 0;

    virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __HIDJOYSTICKRPTPARSER_H__
