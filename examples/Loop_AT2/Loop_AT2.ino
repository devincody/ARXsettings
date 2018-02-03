/********************************************************           
* Loop_AT2: Example program for the ARXsettings library *   
*                                                       *   
* Author:  Devin Cody                                   *   
*                                                       *   
* Date:  February 2, 2018                               *   
********************************************************/  

//Mandatory Includes
#include <ARXsettings.h>
#include <SPI.h>

ARXsetting brd1;             // Initialize an ARX board


//Setup function executes once
void setup(){
  Serial.begin(9600);        //Must be included for ARXsetting::print_all() to work
  brd1.init();               //Initialize SPI and send IO intialization commands
  brd1.setAt1_all(0);        //Set the value of At1 for all channels
  brd1.setAts_all(30);       //Set the value of At2 for all channels
  brd1.print_all();          //Prints hex values for all registers
}

//Loop function executes continuously
void loop() {
  for (int i = 0; i <= 30; i += 2){
    Serial.print("i = ");
    Serial.println(i);
    brd1.setAt2_all(i);      //Set the value of At2 for all channels
    brd1.print_all();        //Prints a summary of the current ARX register settings
    brd1.sendReg_all();      //Send the control bits to the ARX board via SPI
    delay(300);
  }
}








