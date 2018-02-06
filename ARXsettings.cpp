/********************************************************           
* ARXsettings.c: Implements the ARXsetting Class	    *   
*                                                       *   
* Author:  Devin Cody                                   *   
*                                                       *   
* Date:  February 2, 2018                               *   
********************************************************/  

#include <ARXsettings.h>


void printHex(int num, int precision);
void assert(bool TF);


ARXsetting::ARXsetting(){}

void ARXsetting::setCS(int ncs){
	NCS = ncs;
}

void ARXsetting::setReg1(int channel, byte setting){
	reg1[channel] = setting;
}

void ARXsetting::setReg2(int channel, byte setting){
	reg2[channel] = setting;
}

void ARXsetting::setReg3(int channel, byte setting){
	reg3[channel] = setting;
}

byte ARXsetting::getReg1(int channel){
	return reg1[channel];
}
byte ARXsetting::getReg2(int channel){
	return reg2[channel];
}
byte ARXsetting::getReg3(int channel){
	return reg3[channel];
}


void ARXsetting::setAt1(int channel, int setting){
	/*
	A bit of a convoluted pice of code, stemming from the fact
	that the parallel ditigal control lines on the RF attenuators
	do not map linearly with the ports of the IO exanders. Thus
	we must conduct a remapping of the binary bits in setting.
	The mapping is done first by determining if a bit in setting
	is a 0 or a 1, then pushing it into the new position with
	(7-at1[i])

	The control bits for AT1 are stored in the first 4 bits of
	the second register. The mask is used to ensure only those
	bits are ever toggled.

	The macro _MK(X,Y) determines whether X's binary 
	representation has a 1 at position Y. The for loop iterates 
	over the SQRT()-1 of the 4 possible control settings for
	the ARX board (i.e. (1<<4-i) = 16, 8, 4, 2 for i = [0:3]). 

	The private variable at1 determines where the result of the
	macro will be stored in the register's storage. Here, 7 is 
	used instead of 3 because we want to write in the first byte.
	*/

	assert(channel < 9 && channel > 0);
	assert(setting < 31 && setting > 0);

	byte ans = getReg2(_CH(channel));
	byte mask = 0xF0;
	ans &= ~mask; // clear out bits

	for (int i = 0; i < 4; i ++)
		ans |= ( _MK(setting, 4-i) << (7-at1[i]) ) & mask;

	//Serial.print("setting = ");
	//Serial.println(_CH(channel));
	//printHex(ans, 2);
	setReg2(_CH(channel), ans);
}
void ARXsetting::setAt2(int channel, int setting){
	/*
	See documentation for setAt1

	Bits in locations: 0x0000 1111 of register 2
	*/
	assert(channel < 9 && channel > 0);
	assert(setting < 31 && setting > 0);

	byte ans = getReg2(_CH(channel));
	byte mask = 0x0F;
	ans &= ~mask; // clear out bits
	for (int i = 0; i < 4; i ++)
		ans |= ( _MK(setting, 4-i) << (3-at2[i]) ) & mask;
	setReg2(_CH(channel), ans);
}

void ARXsetting::setAts(int channel, int setting){
	/*
	See documentation for setAt1

	Bits in locations: 0x0000 1111 of register 3
	*/
	assert(channel < 9 && channel > 0);
	assert(setting < 31 && setting > 0);

	byte ans = getReg3(_CH(channel));
	byte mask = 0x0F;
	ans &= ~mask; // clear out bits
	for (int i = 0; i < 4; i ++)
		ans |= ( _MK(setting, 4-i) << (3-ats[i]) ) & mask;
	setReg3(_CH(channel), ans);
}

void ARXsetting::setAt1_all(int setting){
	/*
	Set AT1 for all channels
	*/
	assert(setting < 31 && setting > 0);

	for (int i = 1; i <= NCHAN; i++){
		setAt1(i, setting);
	}
}

void ARXsetting::setAt2_all(int setting){
	/*
	Set AT2 for all channels
	*/
	assert(setting < 31 && setting > 0);

	for (int i = 1; i <= NCHAN; i++){
		setAt2(i, setting);
	}
}

void ARXsetting::setAts_all(int setting){
	/*
	Set ATS for all channels
	*/
	assert(setting < 31 && setting > 0);

	for (int i = 1; i <= NCHAN; i++){
		setAts(i, setting);
	}
}

void ARXsetting::setFEE(int channel, bool setting){
	/*
	Set FEE for channel A and channel B
	*/

	setFEE_A(channel, setting);
	setFEE_B(channel, setting);
}

void ARXsetting::setFEE_A(int channel, bool setting){
	/*
	Set FEEA for one channel
	*/
	assert(channel < 9 && channel > 0);

	byte pattern = 0x10;
	byte reg = getReg1(_CH(channel));
	if (setting){
		setReg1(_CH(channel), reg | pattern);
	} else {
		setReg1(_CH(channel), reg & ~pattern);
	}
}

void ARXsetting::setFEE_B(int channel, bool setting){
	/*
	Set FEEB for one channel
	*/
	assert(channel < 9 && channel > 0);

	byte pattern = 0x20;
	byte reg = getReg1(_CH(channel));
	if (setting){
		setReg1(_CH(channel), reg | pattern);
	} else {
		setReg1(_CH(channel), reg & ~pattern);
	}
}

void ARXsetting::setFEE_all(bool setting){
	for (int i = 1; i <= NCHAN; i++){
		setFEE(i, setting);
	}
}


void ARXsetting::setFilter(int channel, filter_t setting){
	// 0x80 == reduced
	// 0x40 == thru
	// 0xC0 == blocked
	// 0x00 == split
	assert(channel < 9 && channel > 0);

	byte mask = 0xC0;
	byte reg = getReg1(_CH(channel));
	reg &= ~mask; // clear out bits

	switch(setting){
		case (SPLIT):
			setReg1(_CH(channel), reg | (0x00 & mask));
			break;
		case (REDUCED):
			setReg1(_CH(channel), reg | (0x80 & mask));
			break;
		case (THRU):
			setReg1(_CH(channel), reg | (0x40 & mask));
			break;
		case (BLOCKED):
			setReg1(_CH(channel), reg | (0xC0 & mask));
			break;
	}
}

void ARXsetting::setFilter_all(filter_t setting){
	/*
	Set Filters for all channels
	*/
	for (int i =1; i <= NCHAN; i++){
		setFilter(i, setting);
	}
}


void ARXsetting::printreg(int reg){
	/*
	Print Registers for all channels
	*/

	for (int i =0; i < 8; i++){
		switch(reg){
		case 1:
			printHex(reg1[i],2);
			break;
		case 2:
			printHex(reg2[i],2);
			break;
		case 3:
			printHex(reg3[i],2);
			break;
		}

		if (i == 7){
			Serial.println();
			break;
		}
		Serial.print(", ");
	}
}

void ARXsetting::print_all(){
	Serial.print("Register 1:");
	printreg(1);
	Serial.print("Register 2:");
	printreg(2);
	Serial.print("Register 3:");
	printreg(3);
}


void ARXsetting::sendReg1(){
	if(!SPI_INIT){
		init();
	}

	write8_diff(registers[0],reg1);
}
void ARXsetting::sendReg2(){
	if(!SPI_INIT){
		init();
	}

	write8_diff(registers[1],reg2);
}
void ARXsetting::sendReg3(){
	if(!SPI_INIT){
		init();
	}

	write8_diff(registers[2],reg3);
}

void ARXsetting::sendReg_all(){
	sendReg1();
	sendReg2();
	sendReg3();
}


void ARXsetting::write8(byte reg, byte val){
  digitalWrite(NCS, LOW);
 
  for (int i = 0; i < NCHAN; i++){
    writeRegister(reg, val);
  }
  digitalWrite(NCS, HIGH);
}

void ARXsetting::write8_diff(byte reg, byte val[]){
  digitalWrite(NCS, LOW);
  for (int i = 0; i < NCHAN; i++){
    writeRegister(reg, val[i]);
  }
  digitalWrite(NCS, HIGH);
}

void ARXsetting::init(){
	SPI.beginTransaction(SPISettings(BAUD, MSBFIRST,SPI_MODE0));
	SPI.begin();
	Serial.println("SPI Initialized");
	SPI_INIT = true;
	init_ARX_reg();
}

void ARXsetting::init_ARX_reg(){
	pinMode(NCS, OUTPUT);
	write8(0x04, 0x01);
	delay(100);
	write8(0x09, 0x55);
	delay(100);
	write8(0x0A, 0x55);
	delay(100);
	write8(0x0B, 0x55);
	delay(100);
	write8(0x0C, 0x55);
	delay(100);
	write8(0x0D, 0x55);
	delay(100);
	write8(0x0E, 0x55);
	delay(100);
	write8(0x0F, 0x55);
	delay(100);
	Serial.println("Registers Initialized");
}


void ARXsetting::writeRegister(byte thisRegister, byte thisValue) {
  SPI.transfer(thisRegister); //Send register location
  SPI.transfer(thisValue);  //Send value to record into register
}


void printHex(int num, int precision) {
	//Gives control over precision, unlike Serial.println(num, HEX)
	char tmp[16];
	char format[128];

	sprintf(format, "0x%%.%dX", precision);

	sprintf(tmp, format, num);
	Serial.print(tmp);
}

void assert(bool TF){
	if(!TF){
		Serial.println("Invalid Parameter");
		Serial.println("Program will not execute as intended");
		Serial.println("Aborting");
		Serial.flush();
		exit(1);
	}
}


