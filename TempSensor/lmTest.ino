
					// every increase 1 ℃, the output voltage increase 10 mv
#define lmPin A0 			// LM35-temperatur sensoren er koblet til AnalogPin 0
#include <Wire.h> 			// Inkluder Wire modul
#include <LiquidCrystal_I2C.h>		// Inkluder LiquidCrystal_I2C modul
LiquidCrystal_I2C lcd(0x27,16,2); 	// Set størelse på LCD til 0x27 for et display på 16x2 (16 karakterer, 2 rader)

float temp = 0;				// lag en float variabel kalt tem med verdi 0
long lmVal = 0;				// lag en long variabel kalt lmVal med verdi 0


void setup()
{
  Serial.begin(9600);			// Start Serial-kommunikasjon på 9600 baud (bit-rate)
  lcd.init();  				// Aktiver LCD-en
  lcd.backlight();  			// Aktiver bakgrunnslys 
  
}
void loop()
{
  lmVal = analogRead(lmPin);		// Lagre verdien fra lmPin til lmVal
  temp = (lmVal * 0.0048828125 * 100);	// 5/1024=0.0048828125;1000/10=100------   formel for å regne om voltage til celcius
  lcd.setCursor(0,0);			// plassering på LCD-en, 5 = hvor på rekken output startet
  lcd.print("Temperatur Kontr//oll");	// Display på LCD-en 0 = øverste rekke
  lcd.setCursor(0,1);			// Plassering        1 = nederste rekke
  lcd.print("Temp= ");			// 
  lcd.setCursor(5,1);			//
  lcd.print(temp);			// Display temperatur verdien
  lcd.print(" C");			//
  delay(200);				// vent i 0,2 sekunder
  //Serial.println(temp);			// Print temp-verdien i serial monitor
  Serial.print("Temperaturen er: ");
  Serial.println(temp);
  delay(3000);				// vent i 3 sekunder
}
                                      










/*** Putty må kjøres konstant for at temperatur verdien skal lagres i filen til sql database ***/



