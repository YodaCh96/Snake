#define DataPinR 7                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define MaxZeile 16                                 //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 8                                 //Anzahl Spalten der Anzeige einstellen
#define EinleseZeit 0.00002                         //Zeitveroegerung damit SR reagieren kann.

int temp;

bool TestArray [8][16] = {                          //Testarray zur Kontrolle des Nachleuten.
    {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {1,0,0,1,1,0,0,1 ,0,1,1,0,0,1,1,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,1,0,0,0,0,1,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,1,1,1,1,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0},
    };

void setup() {
  DDRD = B11111100;                               //ArduiPins als Output deklarieren (Portmanipulation)
}

void loop() {
    PORTD = B00001000;                            //DataPin auf HIGH, vorbereitung durchschalten der Reihen
    delay(EinleseZeit);
    PORTD = B00111000;                            //ShStPin und StorePin HIGH, Reihe 8 Ausgeben (ab zweitem Durchgang)
    delay(EinleseZeit);
    PORTD = B00000000;                            //Alle Ausgänge auf LOW
    for(int a=0; a<MaxSpalte-1; a++){             //Reihen 1-7 behandeln
      Einlesen(a);                                //Die 16Bits fuer eine Reihe einlesen
      PORTD = B00110000;                          //Reihe ausgeben und Linie wechseln                  
      delay(EinleseZeit);
      PORTD = B00000000;
      temp = a+1;                                 //Variabel für die 8. Reihe
    }
    Einlesen(temp);                               //Die 16Bits fuer die 8. Reihe einlesen
}

void Einlesen(int x){
  for (int n=0; n<MaxZeile; n++){                 //For schleife zum Setzten einer Reihe
    digitalWrite(ShiftPinR, LOW);                 //ShiftPinR 16Bit auf LOW
    digitalWrite(DataPinR, TestArray[x][n]);      //Array Position wird abgefragt (1 oder 0)
    digitalWrite(ShiftPinR, HIGH);                //ShiftPinR 16Bit auf HIGH
  }
}
