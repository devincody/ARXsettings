## Welcome.
Version 2.1

### Purpose
This project was developed specifically to assist in controlling a single 16-channel ARX board using Arduino.

The library abstracts away many complicated bit manipulations and allows the user to focus on operating the ARX board.

### Give me the code!

Download the repository as a .zip file by clicking the "Clone or Download" button.

If you don't have it already, download the Arduino IDE [here](https://www.arduino.cc/en/Main/Software)

Open the Arduino IDE. Go to Sketch>Include Library>Add .ZIP Library. Browse to your download location and select your file.

Follow the instructions on [this website](https://www.baldengineer.com/installing-arduino-library-from-github.html) if you still have quesitons.
### Overview

Broadly speaking, the methods are split into three categories. The first category is for configuring a single ARX channel. The second is for configuring all ARX channels simultaneously and the last category is the initialization and execution methods.

#### Setting a signal channel
The following methods will change the setting for a single channel.
```c++
void setAt1(int channel, int setting);          // channel: [1-8], setting: [0-30]
void setAt2(int channel, int setting);
void setAts(int channel, int setting);
void setFEE(int channel, bool setting);         // channel: [1-8], setting: true/false
void setFEE_A(int channel, bool setting);
void setFEE_B(int channel, bool setting);
void setFilter(int channel, filter_t setting);  // channel: [1-8], setting: SPLIT, BLOCKED, THRU, REDUCED
                                                // settings must be prefixed by ARXsetting:: (e.g. ARXsetting::SPLIT)
```

#### Setting all channels
The following methods will change the setting for all channels
```c++
void setAt1_all(int setting);
void setAt2_all(int setting);
void setAts_all(int setting);
void setFEE_all(bool setting);
void setFilter_all(filter_t setting);
```

#### Initializing and sending
The following commands control the *flow* of information
```c++
void init();
void setCS(int ncs);        //set the chip select pin
void sendReg_all();         //sends data via spi
void printreg(int reg);     //one indexed
void print_all();
```
    
### Examples

Once the library is downloaded, you can find the examples in the Arduino IDE at:

Open>libraries>ARXsettings

### FAQ\*

\* These questions have never actually been asked

#### What is an Arduino?
[Arduino](https://www.arduino.cc/) is a family of microcontrollers which has been designed to facilitate the development of embedded solutions.

#### Why doesn't the IDE see my Arduino?
There are many potential reasons for this and many reasons are discussed in depth elsewhere. For the Arduinos in the Weinreb lab, the reason *might* be that your computer doesn't yet have the driver required to use the CH34X serial-USB chip on these boards. Follow the download instructions on [this website](https://kig.re/2014/12/31/how-to-use-arduino-nano-mini-pro-with-CH340G-on-mac-osx-yosemite.html).

#### Where is the GUI?
The GUI has not yet been included with this github package. Future revisions will include the GUI.


### More Questions?
Talk to Devin
