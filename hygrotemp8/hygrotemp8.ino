#include <DSP0401B.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

#define SDI_PIN 2   // data out
#define CLK_PIN 3   // clock
#define LE_PIN  4   // latch
#define OE_PIN  5   // output enable

DSP0401B mydisp;
Adafruit_BME280 bme; // I2C

void setup() {
  // 2 display chained
  mydisp.begin(2, SDI_PIN, CLK_PIN, LE_PIN, OE_PIN);
  // set brightness
  mydisp.brightness(35);

  if (!bme.begin(0x76)){
    /*
    mydisp.sendtext("*ERREUR*");
    while (1) {
      mydisp.brightness(35);
      delay(500);
      mydisp.brightness(0);
      delay(500);
    }
    */
    while(1) {
      mydisp.slidetext("BME180 ERROR",170);
    }
  }
}

void loop() {
  char texte[9]; // = "42#C 56%";
  int temp = (int)bme.readTemperature();
  int hygro= (int)bme.readHumidity();

// simple 8790 & 297
/*
  texte[0]=(temp/10)+48;
  texte[1]=temp-((temp/10)*10)+48;
  texte[5]=(hygro/10)+48;
  texte[6]=hygro-((hygro/10)*10)+48;
*/

// ternaire 8790 & 297
/*
  texte[0]= (temp<10) ? ' ' : (temp/10)+48;
  texte[1]=temp-((temp/10)*10)+48;
  texte[5]= (hygro<10) ? ' ' : (hygro/10)+48;
  texte[6]=hygro-((hygro/10)*10)+48;
*/

// snprintf 10200 & 309
//  snprintf(texte, 9, "%2d#C%3d%%", temp, hygro);
//  snprintf(texte, 9, "%3d#%3d%%", temp, hygro);

 snprintf(texte, 9, "%2d%s%3d%%",temp, (temp<-9) ? "#" : "#C", hygro);

  mydisp.sendtext(texte);
  delay(1000);
}
