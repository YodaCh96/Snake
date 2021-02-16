// Deklaration von Konstanten und Variablen
#define DataPinR 7                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define ShStPinS 4                                  //Store und Shift Pin des 8Bit Schieberegisters
#define MaxZeile 8                                  //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 16                                //Anzahl Spalten der Anzeige einstellen
#define EinleseZeit 0.00002


int temp;                                            //Für die Ausgabe der letzter LED-Reihe

// Arrays definieren welches dann angezeigt werden soll auf dem Dysplay
  bool Anzeige [8][16] = {               //Array für die Anzeige
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}, 
    {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1}, 
    {1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0}, 
    {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0}, 
    {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    };


void setup() { 
  DDRD = B11111100;                           //ArduiPins als Output deklarieren       
  digitalWrite(ShStPinS, LOW);                //Sicherheitshalber Pin auf Low setzten
}

void loop() {
      for(int a=0; a<MaxZeile; a++){
        EinlesenG(a);
        EinlesenR (a);
        if(a == MaxZeile-1){
         PORTD = B00001000;                  //DataPin 8Bit auf High setzten  
        }//if    
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
      }//for
}//loop

  

void EinlesenR(int x) {
  for (int n = 0; n < MaxSpalten; n += 2) {   //For schleife zum Setzten einer Reihe mir roter Farbe
    digitalWrite(ShiftPinR, LOW);
    delay(EinleseZeit);                       //Sicherheit das keine falschen Bits eingelesen werden
    digitalWrite(DataPinR, Anzeige[x][n]);    //Auslesen vom 8 x 16 Array 
    digitalWrite(ShiftPinR, HIGH);
    delay(EinleseZeit);                      //Sicherheit das keine falschen Bits eingelesen werden
  }
}

void EinlesenG(int y) {
  for (int z = 1; z < MaxSpalten; z += 2) {  //For schleife zum Setzten einer Reihe mit gruener Farbe
    digitalWrite(ShiftPinR, LOW);
    delay(EinleseZeit);                      //Sicherheit das keine falschen Bits eingelesen werden
    digitalWrite(DataPinR, Anzeige[y][z]);   //Auslesen vom 8 x 16 Array 
    digitalWrite(ShiftPinR, HIGH);
    delay(EinleseZeit);                     //Sicherheit das keine falschen Bits eingelesen werden
  }
}


