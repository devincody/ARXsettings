
#ifndef _ARX_Control_Panel_ARX_Control_Panel_h
#define _ARX_Control_Panel_ARX_Control_Panel_h


/*
 * ARX_Control_Panel.h -- part of the ARX_Control_Panel project.
 * Declarations for everything that was generated...
 * Mysterion the Anonymous
 *  
 * 
 * Copyright (C) 2017 Mysterion the Anonymous
 * 
 * Generated by DruidBuilder [https://devicedruid.com/], 
 * as part of project "1f8713a7bb094eb08afe4a38536f8817bPPUA7QTnA",
 * aka ARX_Control_Panel.
 * 
 * Druid4Arduino, Device Druid, Druid Builder, the builder 
 * code brewery and its wizards, SerialUI and supporting 
 * libraries, as well as the generated parts of this program 
 * are 
 *            Copyright (C) 2013-2017 Pat Deegan 
 * [http://psychogenic.com/ | http://flyingcarsandstuff.com/]
 * and distributed under the terms of their respective licenses.
 * See http://devicedruid.com for details.
 * 
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE 
 * PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, 
 * YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR
 * CORRECTION.
 * 
 * Keep in mind that there is no warranty and you are solely 
 * responsible for the use of all these cool tools.
 * 
 * Play safe, have fun.
 * 
 */



/* we need the SerialUI lib */
#include <SerialUI.h>


/* MySUI
 * Our SerialUI Instance, through which we can send/receive
 * data from users.
 */ 
extern SUI::SerialUI MySUI;






/*
 * The container for MyInputs, which
 * holds all the variables for the various inputs.
 */
typedef struct MyInputsContainerStruct {
	
	long int Filter;
	long int AT1;
	long int AT2;
	long int ATS;
	bool FEE;
	long int ChannelNumber;
	long int TogglePeriod;
	// constructor to set sane startup vals
	MyInputsContainerStruct() : 
		Filter(1),
		AT1(0),
		AT2(0),
		ATS(0),
		FEE(false),
		ChannelNumber(0),
		TogglePeriod(0)
	{}
} MyInputsContainerSt;

extern MyInputsContainerSt MyInputs;





/* ********* callbacks and validation functions ********* */



/* *** Main Menu *** */
namespace MainMenu {

void doINITSPI();

void FilterChanged();

void AT1Changed();

void AT2Changed();

void ATSChanged();

void FEEChanged();

void ChannelNumberChanged();

void doUpdateChannel();

void doUpdateAllChannels();

void doSendToAllChannels();



/* *** Main Menu -> Advanced *** */
namespace Advanced {

void doSetAllToDefault();

void TogglePeriodChanged();

void doToggleAT1();

void doToggleAT2();

void doToggleATS();

void doToggleFilter();

void doToggleFEE();

} /* namespace Advanced */

} /* namespace MainMenu */



/* ***** SetupSerialUI: where we'll be setting up menus and such **** */
bool SetupSerialUI();


#define DIE_HORRIBLY(msg)	for(;;){ MySUI.println(msg); delay(1000); }


#endif
