#include <EiMOS_RLC.h>
#include <EiMOS_U8X8.h>
#define SCL0 22
#define SDA0 23
#define SCL1 24
#define SDA1 25
#define SCL2 26
#define SDA2 27
#define SCL3 28
#define SDA3 29
int charge_pin[] = {
  // please note: avoid using RX, TX pin as charge pins
  7, 6, 5,
  4, 3, 2,
  14, 15, 16,
  17, 18, 19};
int analog_pin[] = {
  A0, A1, A2,
  A4, A5, A6,
  A8, A9, A10,
  A12, A13, A14};
int button_mode[] = {
  A3, A7, A11, A15};
int button_honba = 19;
float CAP_CENTURY_GOLD[] = {
  5.0f, 10.0f, 1.0f, 1.0f};
float CAP_CENTURY_SILVER[] = {
  225.0f, 10.0f, 1.0f, 1.0f};
float R_REF[] = {
  // internal pullup resistor is 34.8k
  //34.8f, 34.8f, 34.8f, 34.8f
  100.0f, 100.0f, 100.0f, 100.0f
};
float CENTURY_GOLD_R_PAR[] = {
  1000.0f, PIN_NONE, PIN_NONE, PIN_NONE};
U8X8_SSD1306_128X64_NONAME_SW_I2C oled0(SCL0, SDA0, U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_SW_I2C oled1(SCL1, SDA1, U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_SW_I2C oled2(SCL2, SDA2, U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_SW_I2C oled3(SCL3, SDA3, U8X8_PIN_NONE);
U8X8 *oled[4] = {&oled0, &oled1, &oled2, &oled3};

EiMOS_RLC RLC(charge_pin, analog_pin, CAP_CENTURY_GOLD, R_REF); // CENTURY TENPAL, GOLD sticks
// EiMOS_RLC RLC(charge_pin, analog_pin, CAP_CENTURY_SILVER, R_REF); //CENTURY TENPAL, SILVER sticks

EiMOS_U8X8 OLED(oled);

void
setup()
{
  RLC.setNSlot(3);
  RLC.setPullType(INPUT_PULLUP);
  RLC.setADCResolution(10);
  // RLC.setOffset(200);
  RLC.setMesType(CAP);
  RLC.setParRes(CENTURY_GOLD_R_PAR);
  OLED.initDisplay();
  RLC.setModeButton(button_mode);
  RLC.setHonbaButton(button_honba);
  RLC.begin();
}
void
loop()
{
  RLC.measure();
  OLED.show(RLC.getResults());
}
