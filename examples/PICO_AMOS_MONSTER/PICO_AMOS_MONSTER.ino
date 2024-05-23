#include <mahjongAsst_U8X8.h>
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
mahjongAsst_U8X8 Asst(adc, RES_AMOS_MONSTER, R_REF);

/* Hardware I2C*/
U8X8_SSD1306_128X64_NONAME_HW_I2C oled0(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_HW_I2C oled1(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_2ND_HW_I2C oled2(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_2ND_HW_I2C oled3(U8X8_PIN_NONE);

U8X8 oled[] = {oled0, oled1, oled2, oled3};


int i2c_address[4] = {0x3C *2, 0x3D * 2, 0x3C *2, 0x3D * 2};
float weight[] = {0.3f, 0.3f, 0.3f, 0.3f};


void
setup()
{
  Asst.setNSlot(4);          //set number of slots; 5k 1k 100 (NSLOT = 3), or 5k 1k 100 100 (NSLOT = 4)

  Asst.setMesType(RES);     //choose measure type; resistance(RES) or CAP(capacitance)
  Asst.setPullType(PULLUP); //choose whether to pull up or down the reference resistors
                              //one of these: PULLUP, PULLDOWN, INPUT_PULLUP
                              
  // Asst.setOffset(200);    // uncomment to enable busting sticks
  Asst.setWeight(weight);
  // Asst.setModeButton(button_mode); // uncomment to enable mode buttons
  // Asst.setHonbaButton(button_honba); // uncomment to enable a honba button

  Wire.begin();
  Wire1.begin();
  
  Asst.setDisplay(oled);
  Asst.setI2CAddress(i2c_address);
  Asst.initDisplay();

  Asst.initExtADC();
  Asst.setExtADC(1, 16, 3.3f);
  Asst.begin();
}
void
loop()
{
  Asst.loop(500);
  Asst.scoreDisplayLoop(500);
}