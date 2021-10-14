//#include <avr/wdt.h>
#define STEP 50000
#define ONOFFINTERVALL 10000000//10000000


//Ein/Ausgänge zuweisen
  const byte A_H5 = 19;
  const byte A_H8  = 18;
  const byte A_H7  = 16;
  const byte A_H10  = 17;
  const byte A_H9  = 15;
  const byte A_H11  = 14;
  const byte A_H6  = 13;
  const byte A_Umfahrung  = 9;
  const byte A_LED1  = 10;
  const byte A_LED2  = 11;
  const byte A_LED3  = 12;
  
  const byte E_S22_4_6 = 2;
  const byte E_S21_3_5 = 0;
  const byte E_S20_3_5 = 8;
  const byte E_S23_4_6 = 3;
  const byte E_TASTER9_10 = 4;
  const byte E_Signal = 5;
  const byte E_VonHbf = 6;
  const byte E_VonAltenberg = 7;
  const byte E_Tx_frei = 1;

  
//Globale Variablen
  //const unsigned int interval = 1000;
  unsigned long previousMillis = 0;
  unsigned long currentMillis = 0;   //Hole vom Timer die aktuellen 
  bool lightsOnOff = true;
   
  volatile int calc = 0;
  volatile unsigned long milisDebug = 0;
  int dim = 0;
  unsigned long lastMilis = 0;

  
//################SETUP######################################################
void setup() {

  cli();
  TCNT0 = 0;
  TCCR0A = 0;
  TCCR0B = 0;
  OCR0A = 240;
  TCCR0A |= (1 << WGM01);
  TCCR0B |= (1 << CS00);
  TIMSK0 |= (1 << OCIE0A);
  sei();
  
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);   //zum Debuggen einkommentiren
  while (!Serial) 
  {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Initialisiert");

  
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(E_TASTER9_10, INPUT);
//  pinMode(E_Tx_frei, INPUT);
  
  pinMode(A_H5, OUTPUT);
  pinMode(A_H7, OUTPUT);
  pinMode(A_H8, OUTPUT);
  pinMode(A_H9, OUTPUT);
  pinMode(A_H10, OUTPUT);
  pinMode(A_H11, OUTPUT);
  pinMode(A_H6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);  

}
//################SETUP###ENDE###############################################

ISR(TIMER0_COMPA_vect)
{
  calc++;
  milisDebug++;
  currentMillis++;
  if(currentMillis >= ONOFFINTERVALL)
  {
    Serial.print("currentmillis ");
    
    currentMillis = 0;
    if(lightsOnOff)
      lightsOnOff = false;
    else
      lightsOnOff = true;
    Serial.println(lightsOnOff);
  }
  if(calc >= 1000)
  {
    calc = 0;
  }


}

//################Schleife##################################################
void loop() 
{  
  
  //milisDebug++;
  

  if(milisDebug >= 1600)
  {

      dim++;
      if(dim > 500)
        dim = 0;
      //Serial.print("dim=");
      //Serial.println(dim);
    milisDebug = 0;
  }

  if(lightsOnOff && calc >= 250)
  {
          if(calc >= dim)
          {
              digitalWrite(A_H8, LOW);    
          }
          else
          {
              digitalWrite(A_H8, HIGH);
          }


        digitalWrite(A_H5, HIGH); //5
        digitalWrite(A_H7, HIGH); //8
        digitalWrite(A_H9, HIGH); //8
        digitalWrite(A_H10, HIGH); //5
        digitalWrite(A_H11, HIGH); //8
        digitalWrite(A_H6, HIGH); //8
        if(currentMillis > STEP)
        {
          digitalWrite(8, HIGH); //5 
          digitalWrite(12, HIGH); //8
        }
        if(currentMillis > (STEP*2))
        {
          if(calc >= dim*2)
          {
              digitalWrite(7, LOW);
              digitalWrite(9, LOW);    
          }
          else
          {
              digitalWrite(7, HIGH);
              digitalWrite(9, HIGH);
          }
          //digitalWrite(7, HIGH); //8
          //digitalWrite(9, HIGH); //8
        }
        if(currentMillis > (STEP*3))
        {
          digitalWrite(10, HIGH); //5
        }                
        if(currentMillis > (STEP*4))
        {
           digitalWrite(11, HIGH); //8
        }         
        
    }
    else
    {
        digitalWrite(A_H5, LOW); //5
        digitalWrite(A_H7, LOW); //8
        digitalWrite(A_H9, LOW); //8
        digitalWrite(A_H10, LOW); //5
        digitalWrite(A_H11, LOW); //8
        digitalWrite(A_H6, LOW); //8
//        digitalWrite(7, LOW); //8
        digitalWrite(8, LOW); //5        
 //       digitalWrite(9, LOW); //8
        digitalWrite(10, LOW); //5
        digitalWrite(11, LOW); //8
        digitalWrite(12, LOW); //8      
     }
  
    
    if(calc >= dim)
    {
        digitalWrite(13, LOW);    
    }
    else
    {
        digitalWrite(13, HIGH);
    }
  
  
}


//################Schleife###ENDE###############################################
