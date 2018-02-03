#include <ARXsettings.h>
#include <SPI.h>

ARXsetting brd1;


void setup(){
  
  Serial.begin(9600);
  brd1.print_all();
  brd1.setAt1_all(0);
  brd1.setAts_all(30);

}

void loop() {
  Serial.println("hello");
  for (int i = 0; i <= 30; i += 2){
    Serial.print("i = ");
    Serial.println(i);
    brd1.setAt2_all(i);
    brd1.print_all();
    brd1.sendReg_all();
    delay(300);
  }
}








