//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/***																	//
		Arduino Kode for;													//
																	//
			LCD-LicuidCrystal modul, med potentiometer for kontrast styring.						//
			DTH11 Temp/Humid sensor												//
			Grønn/Led av/på Lys/vifte oversikt(under utvikling)								//
																	//
																	//
***/																	//
																	//
																	//
																	//
																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	//
// Inkluder de nødvendige bibliotek kodene												//
#include <LiquidCrystal.h>			// LCD-display bibliotek								//
#include <dht.h>				// Temp/Fuktiget-sensor bibliotek							//
																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	//
// Initialiser biblioteket med interface pins (hvilken pins interfacen bruker)								//
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);		// Definer hvilken pins som er koblet til hvilke 					// 							// komponenter										//
dht DHT;					// Usikker på hva denne kommandoen gjør							//
																	//
																	//
#define DHT11_PIN 8			// DHT11(Temp/Hum-Sensor) er koblet til digital pin 8						//
#define greenledPin 6			// Grønn led er koblet til digital pin 6							//
#define redledPin 7			// Rød led er koblet til digital pin 7								//
																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////																	//
																	//
// Intialsier variabler som skal brukes senere i programmet										//
int lysbryterState = 0;			// Lys bryter State er 0 (av)									//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	//
																//	//
void setup() {					// void setup() Instillinger programmet får ved oppstart 			//	//
  lcd.begin(16, 2);				// Velg hvor mange rader og rekker LCD displayet skal ha (16 rader, 2 rekker)	//	//
  Serial.begin(9600);				// Begynn serial kommunikasjon med 9600 bauds					//	//
  pinMode(greenledPin, OUTPUT);			// Set grønn led pin som output pin						//	//
  pinMode(redledPin, OUTPUT);			// Set rød led pin som output pin						//	//
  digitalWrite(greenledPin, HIGH);		// Slå på grønn led								//	//
  digitalWrite(redledPin, HIGH);		// Slå på rød led								//	//
  delay(1000);					// Vent i 1 sekund								//	//
}																//	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	//
																	//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	//
void loop() {						// void loop() program koden som skal kjøres kontinuerlig på repeat 	   //	//
  Serial.print("temp");					// Print temp i serial monitor(på 9600 buds)				   //	//
  Serial.println(DHT.temperature);			// Print temperatur verdien fra DHT sensoren i serial monitor		   //	//
  																   //	//	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	//
  																   //	//
  int chk = DHT.read11(DHT11_PIN);			// chk = return verdien av DHT.read() funksjonen på Temp/Hum-sensor pinen  //	//
  switch (chk)								// bruk switch med chk som argument			   //	//
    {																   //	//
      case DHTLIB_OK:							// Verdi av DHTLIB_OK					   //	//  
	  	Serial.print("OK, temp/hum sensor virker normalt\t"); 	// Print til seribal monitor				   //	//
	  	break;							// bryt ut av kodn og gå videre				   //	//
      case DHTLIB_ERROR_CHECKSUM: 					// Verdi av DHTLIB_ERROR_CHECKSUM			   //	//
		Serial.print("Checksum error,\t"); 			// -||-							   //	//
		break;							// -||-							   //	//
      case DHTLIB_ERROR_TIMEOUT: 					// Verdi av DHTLIB_ERROR_TIMEOUT			   //	//
		Serial.print("Time out error,\t"); 			// 							   //	//
		break;							//							   //	//
      default: 								// Default verdi					   //	//
		Serial.print("Unknown error,\t"); 			//							   //	//
		break;							//							   //	//
}																   //	//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	//
																   //	//
  lcd.print("Sensor Oversikt");							// Print på LCD-display (default posisjon)	   //	//
																   //	//  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	//
																   //	//
  // Rull 13 posisjoner(lengden av stringen som skal vises) til venstre for å flytte den ut av skjermen til venstre		   //	//
  {{for (int positionCounter = 0; positionCounter < 13; positionCounter++) {							   //	//
    lcd.scrollDisplayLeft();							// Rull en posisjon mot venstre			   //	//
    delay(50);									// Vent litt 50 millisekunder			   //	//	
  }																   //	//
																   //	//
  // Rull 29 posisjoner (lengden av string + lengden av displayet, for å flytte mot høyre og ut avskjermen			   //	//
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {							   //	//
    lcd.scrollDisplayRight(); 							// Rull en posisjon mot høyre			   //	//
    delay(50);									// Vent litt 50 millisekunder			   //	//
  }																   //	//
																   //	//
    // Rull 16 posisjoner (display lengde + string lengde) for å rulle tilbake til midten av skjermen				   //	//
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {							   //	//
    lcd.scrollDisplayLeft(); 							// Rull en posisjon mot venstre			   //	//
    delay(50);									// Vent litt 50 millisekunder			   //	//
  }																   //	//
  delay(500);									// Vent litt etter loopen 500 millisekunder	   //	//
}																   //	//
																   //	//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   //
																   //	//
  lcd.clear();					// klargjør LCD display for nytt output (fjern eksisterende symboler)		   //	//
  lcd.print("Temp:");				// Print Temp: på LCD skjermen (standard posisjon etter clear)			   //	//
  lcd.print(DHT.temperature,1);			// Print verdien fra DHT.temperature,1 (temperatur verdien)			   //	//
  lcd.print(" C");				// Print C									   //	//
  lcd.setCursor(0,1);				// Sett LCD peker poisjon (hvor det første symbolet skal vises)			   //	//
  lcd.print("RH:");				// Print RH:									   //	//
  lcd.print(DHT.humidity,1);			// Print verdien fra DHT.humidity,1 (fuktighets verdien)			   //	//
  lcd.print(" %");				// Print %									   //	//
  delay(3000);					// Vent i 3 sekunder								   //	//
  lcd.clear();					// Fjern eksiterende symboler som er vist på LCD skjermen			   //	//
  																   //	//
  if (digitalRead(greenledPin) == HIGH)		// Hvis grønn LED lyser								   //	//
    lcd.print("Light is on!");			// Print Light is on								   //	//
  else						// Hvis grønn LED ikke lyser							   //	//
    lcd.print("Light is off!");			// Print Light is off								   //	//
  																   //	//
  lcd.setCursor(0,1);  				// Sett LCD peker posisjon, rad 1 rekke 2					   //	//
  if (digitalRead(redledPin) == LOW)		// Hvis rød LED er av								   //	//
    lcd.print("Fan is off");			// Print Fan is off!								   //	//
  else if (digitalRead(redledPin) == HIGH)	// Eller hvis rød  LED er på							   //	//
    lcd.print("Fan is on");  			// Print Fan is on								   //	//
  else						//										   //	//
    lcd.print("error");				// Print error									   //	//
  																   //	//
  delay(2000);					// Vent i 2 sekunder								   //	//
  lcd.clear();					// Fjern eksisterende symboler på LCD-displayet					   //	//
}																   //	//
																   //	//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	//
																	//
}																	//
																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






