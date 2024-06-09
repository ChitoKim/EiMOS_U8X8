/*
  Special Thanks to Mahjong

  EiMOS_U8X8 - EiMOS_U8X8.cpp
  EiMOS Library combined with U8G2 displays
  Formerly known as mahjongAsst_U8X8

 *  Copyright (c) 2023, Chito Kim
 *  All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 

  ***** U8G2 Reference *****
  ============ BSD License for U8g2lib Code ============

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "EiMOS_U8X8.h"
const uint8_t u8x8_font_mahjong[68] U8X8_FONT_SECTION("u8x8_font_mahjong") = 
  " !\2\2\376\374\370\360\340\300\200\0\0\0\0\0\0\0\0\0\0\1\3\7\14\34\77\177\376\0\0\0"
  "\0\0\0\0\0\0\330\330\0\330\330\0\0\0\0\0\0\0\0\0\0\0\66\66\0\66\66\0\0\0\0\0"
  "\0\0\0";
/*
  Fontname: u8x8_font_mahjong
  Copyright: Created with Fony 1.4.7
  Glyphs: 2/2
  BBX Build Mode: 3
*/
const uint8_t* _font = u8x8_font_px437wyse700b_2x2_r;

const char U8X8_CHAR_CHECK = '\x40';
const char U8X8_CHAR_RIICHI = '\x20';
const char U8X8_CHAR_HONBA = '\x21';

EiMOS_U8X8::EiMOS_U8X8(MUX *mux, ENV *env, PIN *pin, VAL *val, U8X8 *u8x8[])
: EiMOS(mux, env, pin, val)
{
  setDisplay(u8x8);
}
EiMOS_U8X8::EiMOS_U8X8(int charge[], int analog[], float v_unit[], float ref[])
: EiMOS(charge, analog, v_unit, ref)
{
}
EiMOS_U8X8::EiMOS_U8X8(int analog[], float v_unit[], float ref[]) 
: EiMOS(analog, v_unit, ref)
{ 
}
EiMOS_U8X8::EiMOS_U8X8(int charge[], int analog, float v_unit[], float ref[])
: EiMOS(charge, analog, v_unit, ref)
{ 
}
EiMOS_U8X8::EiMOS_U8X8(int analog, float v_unit[], float ref[])
: EiMOS(analog, v_unit, ref)
{  
}
EiMOS_U8X8::EiMOS_U8X8(int charge[], ADS1X15 *ext_adc[], float v_unit[], float ref[])
:EiMOS(charge, ext_adc, v_unit, ref)
{
}
EiMOS_U8X8::EiMOS_U8X8(ADS1X15 *ext_adc[], float v_unit[], float ref[])
:EiMOS(ext_adc, v_unit, ref)
{
}

void
EiMOS_U8X8::setDisplay(U8X8 *u8x8[])
{   
  int i;
  for(i = 0; i < 4; i++)
  {
    u8x8_p[i] = u8x8[i];
  }
}
void
EiMOS_U8X8::setDisplay(U8X8 u8x8[])
{
  int i;
  for(i = 0; i < 4; i++)
  {
    u8x8_p[i] = &u8x8[i];
  }
}
void
EiMOS_U8X8::initDisplay()
{
  int i;
  U8X8 *dis = nullptr;
  for(i = 0; i < 4; i++) 
  {
    dis = (this->u8x8_p)[i];
    // dis->setI2CAddress((i % 2) ? 0x3D * 2 : 0x3C * 2);
    dis->begin();
    dis->setPowerSave(0);
    dis->setFont(_font);
    dis->setCursor(0,0);
    dis->print("EiMOS");
    dis->setCursor(0, 2);
    dis->print("w/ OLED");
    dis->setCursor(0, 4);
    dis->print("created");
    dis->setCursor(0, 6);
    dis->print("by Chito");
  } delay(1000);
  for(i = 0; i < 4; i++)
  {
    dis = (this->u8x8_p)[i];
    dis->clearDisplay();
  }
  lastDisplayTime = millis();
  delay(1000);
}
void
EiMOS_U8X8::setI2CAddress(int n, int addr)
{
  u8x8_p[n]->setI2CAddress(addr);
}
void
EiMOS_U8X8::setI2CAddress(int a[])
{
  int i;
  for(i = 0; i < 4; i++)
  {
    u8x8_p[i]->setI2CAddress(a[i]);
  }
}
void
EiMOS_U8X8::scoreDisplay(int player)
{
  //display scores onto the LCD display
  //mode: NORMAL(actual score) or DIFF(difference to my score)
  //err[]: check if sticks are in wrong places
  int *score = this->getScore();
  int *error = this->getError();
  int mode  =  (this->getMode())[player];
  int honba  = this->getHonba();
  U8X8* dis = (this->u8x8_p)[player];

  int score_self = score[player];
  int p_self   = player;
  int p_right  = this->right(player); 
  int p_facing = this->facing(player);
  int p_left   = this->left(player);
  int total = 0;  
  int digit[4]; // numbers actually displayed; usually score itself
  char buffer[20];
  for(int i = 0; i < 4; i++) 
  {
    total += score[i];  
    if(mode == NORMAL)
      digit[i] = score[i];
    else if(mode == DIFF)
      digit[i] = score[i] - score_self;
    else if(mode == PM)
      digit[i] = score[i] - SUM / 4;
  }
  dis->setFont(_font);
  
  sprintf(buffer, " %4d   ", digit[p_facing]);
  if(error[p_facing]) 
  {
    buffer[1]= ' '; buffer[2] = 'E'; buffer[3] = 'R'; buffer[4] = 'R';
  }
  dis->setCursor(0, 0);
  dis->print(buffer);

  sprintf(buffer, "%-4d%4d", digit[p_left], digit[p_right]);
  if(error[p_left]) 
  {
    buffer[0] = 'E'; buffer[1] = 'R'; buffer[2] = 'R'; buffer[3] = ' ';
  } 
  if(error[p_right]) 
  {
    buffer[4] = ' '; buffer[5] = 'E'; buffer[6] = 'R'; buffer[7] = 'R'; 
  }
  dis->setCursor(0, 2);
  dis->print(buffer);

  sprintf(buffer, " %4d   ", digit[p_self]);
  if(error[p_self]) 
  {
    buffer[1]= ' '; buffer[2] = 'E'; buffer[3] = 'R'; buffer[4] = 'R';
  }
  if(mode == DIFF)
  {
  buffer[1] = ' '; buffer[2] = 'D'; buffer[3] = 'I'; buffer[4] = 'F';
  }
  else if(mode == PM)
  {
    buffer[6] = '+'; buffer[7] = '-';
  }
  dis->setCursor(0, 4);
  dis->print(buffer);


  switch(total) 
  {
    case 1000:
      dis->setCursor(0, 6);
      dis->setFont(u8x8_font_open_iconic_check_2x2); //check sign
      dis->print(U8X8_CHAR_CHECK);
      dis->setFont(_font);
      dis->print("  ");
      break;
    case 910: case 920: case 930: case 940: case 950:
    case 960: case 970: case 980: case 990:
      dis->setCursor(0, 6);
      dis->setFont(u8x8_font_mahjong);
      dis->print(U8X8_CHAR_RIICHI); //riichi
      sprintf(buffer, "%-2d", (1000 - total) / 10);
      dis->setFont(_font);
      dis->print(buffer);
      break;
    default:
      dis->setCursor(0, 6);
      if(total > 1000)
      {
        dis->print("!! ");
      }
      else
      {
        dis->print("!  ");
      }
      break;
  }

  if(honba)
  {
    dis->setCursor(6,6);
    dis->setFont(u8x8_font_mahjong);
    dis->print(U8X8_CHAR_HONBA); // honba
    sprintf(buffer, "%-2d", honba);
    dis->setFont(_font);
    dis->print(buffer);
  }
  else
  {
    dis->setCursor(6,6);
    dis->setFont(_font);
    dis->print("   ");
  }
  dis->setCursor(12, 6);
  dis->print("  ");
}  
void
EiMOS_U8X8::scoreDisplayLoop(int period)
{
  //display the four scores on four displays, if mode is PM, delay some time(default 0)
  int i;
  unsigned long currentTime = millis(); 
  if(currentTime > lastDisplayTime + period)
  {
    for(i = 0; i < 4; i++)
    {
      this->scoreDisplay(i);
    }
    lastDisplayTime = currentTime;
  }
}

//below three functions return one of the other players
int
EiMOS_U8X8::right(int player)
{
  return (player == 3) ? 0 : player + 1;
}

int
EiMOS_U8X8::facing(int player)
{
  return (player >= 2) ? player - 2 : player + 2;
}

int
EiMOS_U8X8::left(int player)
{
  return (player == 0) ? 3 : player - 1;
}