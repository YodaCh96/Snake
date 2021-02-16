#define DataPinR 7                          //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                         //Shift Pin des 16Bit Schieberegisters
#define MaxZeile 16                         //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 8                         //Anzahl Spalten der Anzeige einstellen
#define EinleseZeit 0.00002                 //Zeitverzoegerung damit das SR reagieren kann
int temp;


  int darray [10][18] = {               //Array für die Aufwaertstaste 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };



void setup() {
  DDRD = B11111100;                         //ArduiPins als Output deklarieren
}

void loop() {
    PORTD = B00001000;                      // DataPin HIGH
    delay(EinleseZeit);
    PORTD = B00111000;                      // ShStPin und StorePin HIGH, Reihe 8 Ausgeben
    delay(EinleseZeit);
    PORTD = B00000000;                      // LOW

    
    for(int a=1; a<MaxSpalte; a++){         //Schleife um einzelne Reihen durchzuschalten
      EinlesenR(a);                         // Rot einlesen Reihe 1-7
      EinlesenG(a);                         // Gruen einlesen Reihe 1-7
      PORTD = B00110000;                    // Ausgeben und Linie wechseln Reihe 1-7
      delay(EinleseZeit);
      PORTD = B00000000;                    // Zurueck auf LOW setzten
      temp = a+1;
    }
    EinlesenR(temp);                        // Rot einlesen Reihe 8
    EinlesenG(temp);                        // Gruen einlesen Reihe 8
    
}



void EinlesenR(int x){
  for (int n=1; n<MaxZeile; n+=2){          // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, darray[x][n]);   //Auslesen vom 10 x 18 Array 
    digitalWrite(ShiftPinR, HIGH);
  }
}

void EinlesenG(int y){
  for (int z=2; z<=MaxZeile; z+=2){         // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, darray[y][z]);   //Auslesen vom 10 x 18 Array 
    digitalWrite(ShiftPinR, HIGH);
  }
}

