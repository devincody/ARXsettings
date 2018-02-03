/********************************************************           
* Toggle_single: Toggles a single channel between all   *
*                settings available                     *   
*                                                       *   
* Author:  Devin Cody                                   *   
*                                                       *   
* Date:  February 2, 2018                               *   
********************************************************/  

#include <ARXsettings.h>
#include <SPI.h>

#define WAIT 500                               //Wait 500ms between toggles
#define CHANNEL 5                              //Make changes on Channel 5

ARXsetting brd1;                               // Initialize an ARX board

//Setup function executes once
void setup(){
  Serial.begin(9600);                          //Must be included for ARXsetting::print_all() to work
  brd1.init();                                 //Initialize SPI and send IO intialization commands
  brd1.setAt1_all(14);                         //Set the value of At1 for all channels
  brd1.setAt2_all(14);                         //Set the value of At1 for all channels
  brd1.setAts_all(30);                         //Set the value of At1 for all channels
  brd1.setFilter_all(ARXsetting::SPLIT);       //Set the Filter to SPLIT for all channels
  brd1.setFEE_all(false);                      //Set the FEE setting to OFF
  brd1.sendReg_all();                          //Send the control bits to the ARX board via SPI
  brd1.print_all();                            //Prints a summary of the current ARX register settings
}

//Loop function executes continuously
void loop(){
  brd1.setAt1(CHANNEL, 14);                         //Set the value of At1 for only CHANNEL
  brd1.setAt2(CHANNEL, 14);                         //Set the value of At1 for only CHANNEL
  brd1.setAts(CHANNEL, 30);                         //Set the value of At1 for only CHANNEL
  brd1.setFilter(CHANNEL, ARXsetting::SPLIT);       //Set the Filter to SPLIT for only CHANNEL
  brd1.setFEE(CHANNEL, false);                      //Set the FEE setting to OFF for only CHANNEL
  brd1.sendReg_all();                               //Send the control bits to the ARX board via SPI
  brd1.print_all();                                 //Prints a summary of the current ARX register settings
  delay(WAIT);
  brd1.setAt1(CHANNEL, 30);                         //Set the value of At1 for only CHANNEL
  brd1.setAt2(CHANNEL, 30);                         //Set the value of At1 for only CHANNEL
  brd1.setAts(CHANNEL, 0);                          //Set the value of At1 for only CHANNEL
  brd1.setFilter(CHANNEL, ARXsetting::REDUCED);     //Set the Filter to SPLIT for only CHANNEL
  brd1.setFEE(CHANNEL, true);                       //Set the FEE setting to OFF for only CHANNEL
  brd1.sendReg_all();                               //Send the control bits to the ARX board via SPI
  brd1.print_all();                                 //Prints a summary of the current ARX register settings
  delay(WAIT);


}
