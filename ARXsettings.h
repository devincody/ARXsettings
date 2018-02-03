#ifndef __ARXsett__
#define __ARXsett__


#include "Arduino.h"
//#include "SPI.h"
#include <math.h>

#define _MK(x,y) ((x & (1 << y))>0)
#define NCHAN 8




class ARXsetting{
	private:
		byte reg1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //corresponds to 4C
		byte reg2[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //corresponds to 54
		byte reg3[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //corresponds to 5C

		int registers[3] = {0x4C, 0x54, 0x5C};
		
		//looking for [16,8,4,2]
		int at1[4] = {0,3,2,1};
		int at2[4] = {0,2,3,1};
		int ats[4] = {0,3,2,1};

		bool SPI_INIT = false;

		int NCS = 10;

	public:

		typedef enum{
			SPLIT,
			REDUCED,
			THRU,
			BLOCKED
		} filter_t;

		ARXsetting();

		void setCS(int ncs);

		//ARX Register Setters
		void setReg1(int channel, byte setting);
		void setReg2(int channel, byte setting);
		void setReg3(int channel, byte setting);

		//ARX Register Getters
		byte getReg1(int channel);
		byte getReg2(int channel);
		byte getReg3(int channel);

		//ARX Attenuator Settings
		void setAt1(int channel, int setting);
		void setAt2(int channel, int setting);
		void setAts(int channel, int setting);
		void setAt1_all(int setting);
		void setAt2_all(int setting);
		void setAts_all(int setting);

		//ARX FEE Settings
		void setFEE(int channel, bool setting);
		void setFEE_A(int channel, bool setting);
		void setFEE_B(int channel, bool setting);
		void setFEE_all(bool setting);

		//ARX Filter Settings
		void setFilter(int channel, filter_t setting);
		void setFilter_all(filter_t setting);

		//SPI ARX Methods
		void sendReg1();
		void sendReg2();
		void sendReg3();
		void sendReg_all();

		//SPI Base Methods
		void writeRegister(byte thisRegister, byte thisValue);
		void write8(byte reg, byte val);
		void write8_diff(byte reg, byte val[]);
		void init();
		void init_ARX_reg();

		//Printing Methods
		void printreg(int reg); //one indexed
		void print_all();


};


#endif




