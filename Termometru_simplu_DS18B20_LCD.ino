
//=========================================================//
//=                   Codul  Arduino                                                                      =//
//=                       pentru                                                                                =//
//=              Termometru simplu cu DS18B20                                             =//
//=                 si afisare pe LCD 16x2 
//=                         V-2       
//=     citire instantanee temperatura DS18B20 fara delay                 
//=          https://hobby-geomar.blogspot.com/                                          =//
//=======================================================//

//--- Biblioteci necesare -------
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>


// inițializează biblioteca prin asocierea pinilor de la LCD
// cu pinii Arduino la care sunt conectati
LiquidCrystal lcd(7,   // pin RS LCD -> digital 8 Arduino
                  6,   // pin EN LCD -> digital 7 Arduino
                  5,   // pin D4 LCD -> digital 6 Arduino
                  4,   // pin D5 LCD -> digital 5 Arduino
                  3,   // pin D6 LCD -> digital 4 Arduino
                  2);  // pin D7 LCD -> digital 3 Arduino


#define ONE_WIRE_BUS A3  //----- Senzorul DS 18B20 este conectat pe pin A3 Arduino
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float tempC;  //---- Variabilă care memoreaza temperatura


void setup() {

  sensors.begin();  // --- Initializare LCD

  lcd.begin(16, 2);  // --- Tip LCD, 16x2

  // -----------------------------------------------------------------
  // Cod opțional pentru mesajul introductiv
  // Puneți-vă propriul mesaj între ghilimele, ex: "* Hobby-GeoMar *"
  // intre ghilimele maxim 16 caractere cat are linia de la LCD
  // -----------------------------------------------------------------

  lcd.setCursor(1, 0);            //---- Setare afisare mesaj 1, prima linie, pozitia 1
  lcd.print("* Hobby-GeoMar *");  //---- Mesaj 1 pentru afisare pe LCD
  lcd.setCursor(1, 1);            //---- Setare afisare mesaj 2, a doua linie, pozitia 1
  lcd.print("  blogspot.com  ");  //---- Mesaj 2 pentru afisare pe LCD
  delay(2000);                    //---- intarziere 2 secunde, timp cat este afisat mesajul
  lcd.clear();                    //---- Stergere LCD
  //---------------------------------------
}

void loop() {
  //-- citire temperatura aproape instantaneu si memorare in tempC fara blocari/delay
  unsigned long start = millis();  //Înainte de a bloca requestForConversion
  sensors.requestTemperatures();   //Solicitați temperatura de la senzor.
  unsigned long stop = millis();         //După blocarea requestForConversion
  tempC = (sensors.getTempCByIndex(0));  //Citiți temperatura de la primul (singurul) senzor de pe bus.
  start = millis();
  sensors.setWaitForConversion(false);  
  sensors.requestTemperatures();
  sensors.setWaitForConversion(true);
  stop = millis();

   int resolution = 10;
  delay(750/ (1 << (12-resolution)));

  lcd.setCursor(4, 0);  //---- Setare afisare temperatura pe prima linie a LCD-ului de la pozitia 0
  lcd.print("Temp = ");  //---- Afisare text "TEMP:" pe LCD
  lcd.print(tempC, 2);  //---- Afisare temperatura senzor pe LCD (tempC, 0) este fara zecimala, (tempC, 1) cu o zecimala)
  lcd.print("\337C");   //---- Afisare simbol grad Celsius pe LCD
}
//============== Terminare program ============================