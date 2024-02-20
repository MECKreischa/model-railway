int input = 2;
int randOnOff;
int randNr;
int randdelay;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);                   
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  randomSeed(millis());
  if (digitalRead(input) == HIGH)
  {
    randOnOff = random(1, 5);
    if (randOnOff == 3)
    {
      randNr = random(3, 8);
      digitalWrite(randNr, HIGH);
    }
    if (randOnOff == 2)
    {
      randNr = random(3, 8);
      digitalWrite(randNr, LOW);
    }
  }
  else
  {
      randNr = random(3, 8);
      digitalWrite(randNr, LOW);
  } 
  randdelay = random(1000, 10000); 
  delay(randdelay);
}
