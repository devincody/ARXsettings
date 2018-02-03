/********************************************************           
* Default_Config: Sets an ARX board to its default      *
*                 configuration                         *   
*                                                       *   
* Author:  Devin Cody                                   *   
*                                                       *   
* Date:  February 2, 2018                               *   
********************************************************/  

#include <ARXsettings.h>
#include <SPI.h>

ARXsetting brd1; //


void setup(){
  Serial.begin(9600);
  brd1.setAt1_all(14);
  brd1.setAt2_all(14);
  brd1.setAts_all(30);
  brd1.setFilter_all(30);
  brd1.print_all(ARXsetting::SPLIT);
  brd1.sendReg_all();
}

void loop(){}
