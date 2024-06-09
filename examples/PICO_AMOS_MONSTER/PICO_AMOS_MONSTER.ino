#include <EiMOS_U8X8.h>
int button_mode[] =
{
  6, 7, 8, 9
};
int button_honba = 10;
float RES_AMOS_MONSTER[] =
{
  //in kiloohms
  20.0f, 100.0f, 1000.0f ,1000.0f
};
float R_REF[] =
{
  //in kiloohms
  10.0f, 10.0f, 10.0f, 10.0f
  // 2.2f, 10.0f, 100.0f, 100.0f
};

ADS1115 ADC0(0x48, &Wire);
ADS1115 ADC1(0x49, &Wire);
ADS1115 ADC2(0x4A, &Wire);
ADS1115 ADC3(0x4B, &Wire);

ADS1X15 *adc[] = {&ADC0, &ADC1, &ADC2, &ADC3};
EiMOS_U8X8 EM(adc, RES_AMOS_MONSTER, R_REF);

/* Hardware I2C*/
U8X8_SSD1306_128X64_NONAME_HW_I2C oled0(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_HW_I2C oled1(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_2ND_HW_I2C oled2(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_2ND_HW_I2C oled3(U8X8_PIN_NONE);

/* Software I2C */
// enum SWI2CPIN
// {
//   SW_SDA0 = 12,
//   SW_SCL0 = 13,
//   SW_SDA1 = 14,
//   SW_SCL1 = 15,
//   SW_SDA2 = 16,
//   SW_SCL2 = 17,
//   SW_SDA3 = 18,
//   SW_SCL3 = 19
// };
// U8X8_SSD1306_128X64_NONAME_SW_I2C oled0(SW_SCL0, SW_SDA0, U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_SW_I2C oled1(SW_SCL1, SW_SDA1, U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_SW_I2C oled2(SW_SCL2, SW_SDA2, U8X8_PIN_NONE);
// U8X8_SSD1306_128X64_NONAME_SW_I2C oled3(SW_SCL3, SW_SDA3, U8X8_PIN_NONE);

U8X8 oled[] = {oled0, oled1, oled2, oled3};


int i2c_address[4] = {0x3C *2, 0x3D * 2, 0x3C *2, 0x3D * 2};
float weight[] = {0.3f, 0.3f, 0.3f, 0.3f};
enum I2CPIN {
  _SDA0 = 4,
  _SCL0 = 5,
  _SDA1 = 2,
  _SCL1 = 3
};


void
setup()
{
  EM.setNSlot(4);          //set number of slots; 5k 1k 100 (NSLOT = 3), or 5k 1k 100 100 (NSLOT = 4)

  EM.setMesType(RES);     //choose measure type; resistance(RES) or CAP(capacitance)
  EM.setPullType(PULLUP); //choose whether to pull up or down the reference resistors
                              //one of these: PULLUP, PULLDOWN, INPUT_PULLUP
                              
  // EM.setOffset(200);    // uncomment to enable busting sticks
  EM.setWeight(weight);
  // EM.setModeButton(button_mode); // uncomment to enable mode buttons
  // EM.setHonbaButton(button_honba); // uncomment to enable a honba button

  Wire.setSDA(_SDA0);
  Wire.setSCL(_SCL0);
  Wire.begin();

  Wire1.setSDA(_SDA1);
  Wire1.setSCL(_SCL1); // set I2C pins
  Wire1.begin(); //tweak pins_arduino.h for second I2C
  
  EM.setDisplay(oled);
  EM.setI2CAddress(i2c_address);
  EM.initDisplay();

  EM.initExtADC();
  EM.setExtADC(/*setGain*/ 1, /*ADC Resolution*/16, /*VCC*/3.3f);
  EM.begin();
}
void
loop()
{
  EM.loop(500);
  EM.scoreDisplayLoop(500);
}