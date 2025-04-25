#include <avr/wdt.h>
#include <SPI.h>

#define PORT_DEBUG 0 // print ADC level

//Ein/Ausgänge zuweisen
  const byte A_frei = 2;
  const byte A_D3  = 3;
  const byte A_D4  = 4;
  const byte A_D5  = 5;
  const byte A_D6  = 6;
  const byte A_D7  = 7;
  const byte E_A4  = A4;
  const byte E_A5  = A5;
  const byte E_A6  = A6;
  const byte E_A7  = A7;
  
  const byte E_fragezeichen = 8;

//##############Klassendefinition##############################
class Input
{
  private:
  byte port;
  bool lastInputState = false;
  bool risingEdge = false;
  bool isAdc = false;
  unsigned long lastTimerValue = 0;
  int pollingtimeMS = 500;
  
  public:
  Input()
  {
    //Serial.print("Eingang initialisiert Port:");
  };
  void SetPin(byte ledPort)
  {
    port = ledPort;
    if(port > 13) {    //Analog input
      isAdc = true;
    } else {
      pinMode(ledPort, INPUT);
    }

    Serial.print("Eingang initialisiert Port:");
    Serial.println(ledPort, DEC);

  }
  //Methoden
  byte isTrue(unsigned long timerValue)     //Rückgabewert Eingang 0=False, 1=pos Flanke, 2=True
  {
    if(isAdc) {
      int adc = analogRead(port);
      if(PORT_DEBUG && port == E_A5) {
        Serial.print(port, DEC);
        Serial.print(":");
        Serial.println(adc, DEC);
      }
      if(adc > 600) {
        lastInputState = false;
        risingEdge = false;
      	return 0;
      }
    } else if(digitalRead(port)) {
        lastInputState = false;
        risingEdge = false;
        return 0;
    }
    if(!lastInputState)   //Taster erstmalig betätigt
    {
        lastInputState = true;
        lastTimerValue = timerValue;
        risingEdge = true;
        //Serial.println("Taster");
        return 0;
    }
    if(timerValue > (lastTimerValue+pollingtimeMS)) //Entprellzeit abwarten
    {
      if(risingEdge)
      {
        //Serial.println(1, DEC);
        risingEdge = false;
        return 1;
      }
      return 2;
      //Serial.println(1, DEC);
    }
  }
};
//##############Klassendefinition###ENDE##############################



  
//Globale Variablen
  const unsigned int interval = 1000;
  unsigned long previousMillis = 0;
  Input Taster1;
  Input Taster2;
  Input Taster3;
  Input Taster4;
  
//################SETUP######################################################
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);   //zum Debuggen einkommentiren
  while (!Serial) 
  {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Initialisiert");

  
  pinMode(LED_BUILTIN, OUTPUT);

 
  pinMode(A_frei, OUTPUT);
  pinMode(A_D3, OUTPUT);
  pinMode(A_D4, OUTPUT);
  pinMode(A_D5, OUTPUT);
  pinMode(A_D6, OUTPUT);
  pinMode(A_D7, OUTPUT);
  
  //Input Bsp.:
  Taster1.SetPin(E_A4);
  Taster2.SetPin(E_A5);
  Taster3.SetPin(E_A6);
  Taster4.SetPin(E_A7);

  SPI.begin();
  SPI.transfer(5);
  
  wdt_enable(WDTO_2S);  //Watchdog enable mit 2sekunden
}
//################SETUP###ENDE###############################################


//################Schleife##################################################
void loop() 
{
  wdt_reset();
  //Serial.println("wdt_reset");
  
  unsigned long currentMillis = millis();   //Hole vom Timer die aktuellen 
  /*
  digitalWrite(A_D3, true);
  digitalWrite(A_D4, true);
  digitalWrite(A_D5, true);
  digitalWrite(A_D6, true);
  digitalWrite(A_D7, true);
  digitalWrite(LED_BUILTIN, true);
  delay(1000);
  digitalWrite(A_D3, false);
  digitalWrite(A_D4, false);
  digitalWrite(A_D5, false);
  digitalWrite(A_D6, false);
  digitalWrite(A_D7, false);
  digitalWrite(LED_BUILTIN, false);
  delay(1000);
  */

  if(Taster1.isTrue(currentMillis) == 1)   //Flanke Taster Signal
  {
      Serial.println("Taster1");
      digitalWrite(A_D3, !digitalRead(A_D3)); //Toggle Ausgang
      SPI.transfer(1);
  }
  if(Taster2.isTrue(currentMillis) == 1)   //Flanke Taster Signal
  {
      Serial.println("Taster2");
      digitalWrite(A_D4, !digitalRead(A_D4)); //Toggle Ausgang
      SPI.transfer(5);
  }
  if(Taster3.isTrue(currentMillis) == 1)   //Flanke Taster Signal
  {
      Serial.println("Taster3");
      digitalWrite(A_D5, !digitalRead(A_D5)); //Toggle Ausgang
      SPI.transfer(5);
  }
  if(Taster4.isTrue(currentMillis) == 1)   //Flanke Taster Signal
  {
      Serial.println("Taster4");
      digitalWrite(A_D6, !digitalRead(A_D6)); //Toggle Ausgang
      SPI.transfer(1);
  }
  /*
  if(analogRead(E_A7) > 100)
  {
      //digitalWrite(A_D3, !digitalRead(A_D3)); //Toggle Ausgang
      digitalWrite(A_D3, true);
  } else {
      digitalWrite(A_D3, false);
      Serial.println("TasterSignal");
  }*/

//  if((Taster_VonAltenberg.isTrue(currentMillis) == 2) && (Taster_VonHbf.isTrue(currentMillis) == 2))
//  {
//      Serial.println("Umfahrung");
//      digitalWrite(A_Umfahrung, true); 
//      Serial.println("Umfahrung: LED1 und LED2 und 3");
//      digitalWrite(A_LED1, true);
//      digitalWrite(A_LED2, true); 
//      digitalWrite(A_LED3, true); 
//  }

   
//  if(!digitalRead(A_Regler1) && !digitalRead(A_Regler2))
//  {
//    if(digitalRead(A_LED1) || digitalRead(A_LED2) || digitalRead(A_LED3))
//    {
//      Serial.println("LED's aus");
//      digitalWrite(A_LED1, false);
//      digitalWrite(A_LED2, false); 
//      digitalWrite(A_LED3, false); 
//    }    
//  }
}


//################Schleife###ENDE###############################################
