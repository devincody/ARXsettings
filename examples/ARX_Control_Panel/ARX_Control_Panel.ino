

/*
 * ARX_Control_Panel.ino -- part of the ARX_Control_Panel project.
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
#include <ARXsettings.h>
#include "ARX_Control_PanelSettings.h"

/* our project specific types and functions are here */
#include "ARX_Control_Panel.h"




/* 
 * In addition to any custom globals you declared,
 * here you have access to:
 * 
 * *** MySUI -- the SerialUI instance.
 * Use it as you would the Serial device, e.g.
 * 	MySUI.println(F("Helloooo..."));
 * 	
 * 	
 * *** MyInputs -- a container for 
 * values submitted by users. Contents:
 *  
 *    MyInputs.Filter (long int)
 *    MyInputs.AT1 (long int)
 *    MyInputs.AT2 (long int)
 *    MyInputs.ATS (long int)
 *    MyInputs.FEE (bool)
 *    MyInputs.ChannelNumber (long int)
 *    MyInputs.TogglePeriod (long int)
 *  
 *  
 *  
 * 
 */


/* **** standard setup() function **** */
void setup() {
  
	if (!SetupSerialUI()) {
		DIE_HORRIBLY(F("Problem during setup"));
	}
	
	

}


void loop() {

  /* We checkForUser() periodically, to see
  ** if anyone is attempting to send us some
  ** data through SerialUI.
  **
  ** This code checks at every pass of the main
  ** loop, meaning a user can interact with the 
  ** system at any time.  Should you want to
  ** check for user access only once (say have a
  ** N second wait on startup, and then forgo
  ** allowing SerialUI access), then increase the
  ** delay parameter and use checkForUserOnce(), e.g.
  **
  **    mySUI.checkForUserOnce(15000);
  **
  ** to allow 15 seconds to connect on startup only.
  **
  ** Called without parameters, or with 0, checkForUser 
  ** won't delay the program, as it won't block at all.
  ** Using a parameter > 0:
  **	checkForUser(MAX_MS);
  ** will wait for up to MAX_MS milliseconds for a user,
  ** so is equivalent to having a delay(MAX_MS) in the loop,
  ** when no user is present.
  */
  if (MySUI.checkForUser()) {
    
    /* Now we keep handling the serial user's
    ** requests until they exit or timeout.
    */
    while (MySUI.userPresent()) {
      // actually respond to requests, using
      MySUI.handleRequests();

	  // you could add a quick task here, to perform
	  // after *every* request, but it's better to use
	  // the setUserPresenceHeartbeat-related methods
    }
  } /* end if we had a user on the serial line */
  
  // add code here to run when no ones around
  

}


