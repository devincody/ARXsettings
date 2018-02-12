

/*
 * setup.cpp -- part of the ARX_Control_Panel project.
 * Setup of SerialUI and menu system
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
#include "ARX_Control_PanelSettings.h"

/* our project specific types and functions are here */
#include "ARX_Control_Panel.h"



/* MySUI
 * Our SerialUI Instance, through which we can send/receive
 * data from users. Actually instantiated here, for global use.
 */
SUI::SerialUI MySUI(11);


/*
 * The container for MyInputs, which
 * holds all the variables for the various inputs.
 * Actually instantiated here, for global use.
 */
MyInputsContainerSt MyInputs;







bool SetupSerialUI() {

	MySUI.setGreeting(F(serial_ui_greeting_str));
	// SerialUI acts just like (is actually a facade for)
	// Serial.  Use _it_, rather than Serial, throughout the
	// program.
	// basic setup of SerialUI:
	MySUI.begin(serial_baud_rate); // serial line open/setup
	MySUI.setTimeout(serial_readtimeout_ms);   // timeout for reads (in ms), same as for Serial.
	MySUI.setMaxIdleMs(serial_maxidle_ms);    // timeout for user (in ms)
	// how we are marking the "end-of-line" (\n, by default):
	MySUI.setReadTerminator(serial_input_terminator);
	// project UID -- will be used to remember state in Druid...
	MySUI.setUID(SUI_STR("1f8713a7bb094eb08afe4a38536f8817bPPUA7QTnA"));

	
	
	
	
	// a few error messages we hopefully won't need
	
	SUI_FLASHSTRING CouldntCreateMenuErr = F("Could not create menu?");
	SUI_FLASHSTRING CouldntAddItemErr = F("Could not add item?");
	
	// get top level menu, to start adding items
	SUI::Menu * topMenu = MySUI.topLevelMenu();
	if (! topMenu ) {
		// well, that can't be good...
		MySUI.returnError(F("Very badness in sEriALui!1"));
		return false;
	}
	
	
	
	/* *** Main Menu *** */
  if( ! topMenu->addCommand(
    SUI_STR("Init SPI"),
    MainMenu::doINITSPI,
    SUI_STR("Initializes SPI"))) {
    MySUI.returnError(CouldntAddItemErr);
    return false;
  }
	
	if( ! topMenu->addRequest(
		&(MyInputs.Filter),
		SUI_STR("Filter"),
		NULL,
		SUI_STR("Split"),
		SUI_STR("Through"),
		SUI_STR("Blocked"),
		SUI_STR("Reduced"),
		MainMenu::FilterChanged)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! topMenu->addRequest(
		&(MyInputs.AT1),
		SUI_STR("AT1"),
		NULL,
		0,
		30,
		MainMenu::AT1Changed)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! topMenu->addRequest(
		&(MyInputs.AT2),
		SUI_STR("AT2"),
		NULL,
		0,
		30,
		MainMenu::AT2Changed)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! topMenu->addRequest(
		&(MyInputs.ATS),
		SUI_STR("ATS"),
		NULL,
		0,
		30,
		MainMenu::ATSChanged)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! topMenu->addRequest(
		&(MyInputs.FEE),
		SUI_STR("FEE"),
		NULL,
		MainMenu::FEEChanged)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! topMenu->addRequest(
		&(MyInputs.ChannelNumber),
		SUI_STR("Channel Number"),
		SUI_STR("Which channel do you want to update?"),
		MainMenu::ChannelNumberChanged)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! topMenu->addCommand(
		SUI_STR("Update Channel"),
		MainMenu::doUpdateChannel,
		SUI_STR("Updates Single Channel and Transmits"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! topMenu->addCommand(
		SUI_STR("Update All Channels"),
		MainMenu::doUpdateAllChannels,
		SUI_STR("Saves info for all channels"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! topMenu->addCommand(
		SUI_STR("Send to All Channels"),
		MainMenu::doSendToAllChannels,
		SUI_STR("Updates all Channels with configuration"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	SUI::Menu * submen1 = topMenu->subMenu(
		SUI_STR("Advanced"),
		SUI_STR("Additional Options"));
	if (! submen1 ) { 
		DIE_HORRIBLY(CouldntCreateMenuErr);
	}
	


	/* *** Main Menu -> Advanced *** */

	
	if( ! submen1->addCommand(
		SUI_STR("Set All to Default"),
		MainMenu::Advanced::doSetAllToDefault,
		SUI_STR("Split ATS=30 AT1=14 AT2=14"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addRequest(
		&(MyInputs.TogglePeriod),
		SUI_STR("Toggle Period"),
		SUI_STR("Milliseconds"),
		0,
		5000,
		MainMenu::Advanced::TogglePeriodChanged)) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addCommand(
		SUI_STR("Toggle AT1"),
		MainMenu::Advanced::doToggleAT1,
		SUI_STR("Toggles AT1 between 0 and 30"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addCommand(
		SUI_STR("Toggle AT2"),
		MainMenu::Advanced::doToggleAT2,
		SUI_STR("Toggles AT2 between 0 and 30"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addCommand(
		SUI_STR("Toggle ATS"),
		MainMenu::Advanced::doToggleATS,
		SUI_STR("Toggles ATS between 0 and 30"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addCommand(
		SUI_STR("Toggle Filter"),
		MainMenu::Advanced::doToggleFilter,
		SUI_STR("Toggles between the 4 filters"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}
	
	if( ! submen1->addCommand(
		SUI_STR("Toggle FEE"),
		MainMenu::Advanced::doToggleFEE,
		SUI_STR("Toggles FEEs on/off"))) {
		MySUI.returnError(CouldntAddItemErr);
		return false;
	}

	
	
	
	return true;
	
}


