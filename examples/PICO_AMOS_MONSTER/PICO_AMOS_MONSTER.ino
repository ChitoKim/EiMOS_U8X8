#include <mahjongAsst_U8X8.h>
int address_pin[] = 
{
  21, 20, 19, 18
};
int analog_pin[] = 
{
  A2, A2, A2, A2,
  A2, A2, A2, A2,
  A2, A2, A2, A2,
  A2, A2, A2, A2
};
int button_mode[] =
{
  2, 3, 4, 5
};
int button_honba = 22;
float RES_AMOS_MONSTER[] =
{
  20.0f, 100.0f, 1000.0f ,1000.0f
};
float R_REF[] =
{
  10.0f, 10.0f, 10.0f, 10.0f
};
mahjongAsst_U8X8 Asst(analog_pin, RES_AMOS_MONSTER, R_REF);

// Hardware I2C 

// U8X8_SSD1306_128X64_NONAME_HW_I2C oled0(U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_HW_I2C oled1(U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_2ND_HW_I2C oled2(U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_2ND_HW_I2C oled3(U8X8_PIN_NONE);

// Software I2C

const int SCL0 = 6;
const int SDA0 = 7;
const int SCL1 = 8;
const int SDA1 = 9;
const int SCL2 = 10;
const int SDA2 = 11;
const int SCL3 = 12;
const int SDA3 = 13;
U8X8_SSD1306_128X64_NONAME_SW_I2C oled0(SCL0, SDA0, U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_SW_I2C oled1(SCL1, SDA1, U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_SW_I2C oled2(SCL2, SDA2, U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_SW_I2C oled3(SCL3, SDA3, U8X8_PIN_NONE);

U8X8 oled[4] = {oled0, oled1, oled2, oled3};
int i2c_address[4] = {0x3C *2, 0x3D * 2, 0x3C *2, 0x3D * 2};
void
setup()
{
  Asst.begin();
  Asst.setNSlot(4);          //set number of slots; 5k 1k 100 (NSLOT = 3), or 5k 1k 100 100 (NSLOT = 4)
  Asst.setADCResolution(12); //set ADC Resolution; e.g. if arduino uno, set it to 10

  Asst.setMesType(RES);     //choose measure type; resistance(RES) or CAP(capacitance)
  Asst.setPullType(PULLDOWN); //choose whether to pull up or down the reference resistors
                              //one of these: PULLUP, PULLDOWN, INPUT_PULLUP
  Asst.setMUX4067(address_pin);
  // Asst.setModeButton(button_mode);   //uncommment if you use mode buttons
  // Asst.setHonbaButton(button_honba); //uncomment if you use honba buttons
  Asst.setDisplay(oled);
  // Asst.setI2CAddress(i2c_address);
  Asst.initDisplay();
}
void
loop()
{
  Asst.loop(500);
  Asst.scoreDisplayLoop(750);
}
