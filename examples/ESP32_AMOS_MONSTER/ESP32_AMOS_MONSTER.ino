#include <mahjongAsst_U8X8.h>
int address_pin[] = 
{
  16, 17, 5, 18
};
int analog_pin[] = 
{
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32
};
int button_mode[] =
{
  36, 39, 34, 35
};
int button_honba = 32;
float RES_AMOS_MONSTER[] =
{
  //in kiloohms
  20.0f, 100.0f, 1000.0f ,1000.0f
};
float R_REF[] =
{
  //in kiloohms
  2.0f, 22.0f, 22.0f, 22.0f 
};
mahjongAsst_U8X8 Asst(analog_pin, RES_AMOS_MONSTER, R_REF);

/* Hardware I2C*/
U8X8_SSD1306_128X64_NONAME_HW_I2C oled0(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_HW_I2C oled1(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_2ND_HW_I2C oled2(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_2ND_HW_I2C oled3(U8X8_PIN_NONE);

/* Software I2C*/
// U8X8_SSD1306_128X64_NONAME_SW_I2C oled0(SCL0, SDA0, U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_SW_I2C oled1(SCL1, SDA1, U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_SW_I2C oled2(SCL2, SDA2, U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_SW_I2C oled3(SCL3, SDA3, U8X8_PIN_NONE);

U8X8 oled[4] = {oled0, oled1, oled2, oled3};
int i2c_address[4] = {0x3C *2, 0x3D * 2, 0x3C *2, 0x3D * 2};
float weight[] = {0.3f, 0.6f, 0.3f, 0.3f};
void
setup()
{
  Asst.begin();
  Asst.setNSlot(4);          //set number of slots; 5k 1k 100 (NSLOT = 3), or 5k 1k 100 100 (NSLOT = 4)
  Asst.setADCResolution(12); //set ADC Resolution; e.g. if arduino uno, set it to 10

  Asst.setMesType(RES);     //choose measure type; resistance(RES) or CAP(capacitance)
  Asst.setPullType(PULLDOWN); //choose whether to pull up or down the reference resistors
                              //one of these: PULLUP, PULLDOWN, INPUT_PULLUP
  // Asst.setMUX4051(address_pin, enable_pin); //set two 74hc4051 ics to multiplex 16 analog inputs
                                            //3 address pins shared, and 
  // Asst.setOffset(200);
  Asst.setWeight(weight);
  Asst.setMUX4067(address_pin);
  Asst.setModeButton(button_mode);
  Asst.setHonbaButton(button_honba);
  Asst.setDisplay(oled);
  Asst.setI2CAddress(i2c_address);
  Asst.initDisplay();
}
void
loop()
{
  Asst.loop(500);
  Asst.scoreDisplayLoop(750);
}
