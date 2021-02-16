// Deklaration von Konstanten und Variablen
#define DataPinR 7                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define ShStPinS 4                                  //Store und Shift Pin des 8Bit Schieberegisters
#define MaxZeile 16                                 //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 8                                 //Anzahl Spalten der Anzeige einstellen
#define Zeit 0.0001                                   //Verzögerungszeit für Shiftregister
#define EinleseZeit 0.00002


int temp;                                            //Für die Ausgabe der letzter LED-Reihe

// Arrays definieren welches dann angezeigt werden soll auf dem Dysplay
  bool Anzeige [8][16] = {               //Array für die rote Anzeige
    {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1}, 
    {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1}, 
    {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},
    };


void setup() { 
  DDRD = B11111100;                           //ArduiPins als Output deklarieren       
  digitalWrite(ShStPinS, LOW);                //Sicherheitshalber Pin auf Low setzten    
}

void loop() {

      PORTD = B00001000;
      delay(EinleseZeit);
      PORTD = B00111000;
      delay(EinleseZeit);
      PORTD = B00000000;
      for(int a=0; a<MaxSpalte-1; a++){
        EinlesenG(a);
        EinlesenR (a);
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
        temp = a+1;
      }
      EinlesenG(temp);
      EinlesenR (temp);
}

  

void EinlesenR(int x) {
  for (int n = 0; n < MaxZeile; n += 2) {          // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, Anzeige[x][n]);   //Auslesen vom 8 x 16 Array 
    digitalWrite(ShiftPinR, HIGH);
  }
}

void EinlesenG(int y) {
  for (int z = 1; z < MaxZeile; z += 2) {         // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, Anzeige[y][z]);   //Auslesen vom 8 x 16 Array 
    digitalWrite(ShiftPinR, HIGH);
  }
}


