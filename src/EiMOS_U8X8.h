/*
  Special Thanks to Mahjong

  EiMOS_U8X8 - EiMOS_U8X8.h
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

#ifndef _MAHJONGASST_U8X8_H
#define _MAHJONGASST_U8X8_H
#include <EiMOS.h>
#include <U8x8lib.h>

class EiMOS_U8X8 : public EiMOS
{
private:
  unsigned long lastDisplayTime = 0L; 
  U8X8 *u8x8_p[4] = {nullptr, nullptr, nullptr, nullptr};
public:
  EiMOS_U8X8(MUX *mux, ENV *env, PIN *pin, VAL *val, U8X8 *u8x8[]);
  EiMOS_U8X8(int charge[], int analog[], float v_unit[], float ref[]);
  EiMOS_U8X8(int analog[], float v_unit[], float ref[]); 
  EiMOS_U8X8(int charge[], int analog, float v_unit[], float ref[]);
  EiMOS_U8X8(int analog, float v_unit[], float ref[]);
  EiMOS_U8X8(int charge[], ADS1X15 *ext_adc[], float v_unit[], float ref[]);
  EiMOS_U8X8(ADS1X15 *ext_adc[], float v_unit[], float ref[]);
  U8X8** getU8X8();
  void setNullU8X8();
  void setDisplay(U8X8* u8x8[]);
  void setDisplay(U8X8 u8x8[]);
  void initDisplay();
  void setI2CAddress(int a, int b);
  void setI2CAddress(int a[]);
  void scoreDisplay(int player);
  void scoreDisplayLoop(int period);
  int  right(int player);
  int  facing(int player);
  int  left(int player);
};
#endif