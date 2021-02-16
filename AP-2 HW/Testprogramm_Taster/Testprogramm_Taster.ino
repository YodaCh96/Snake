// Deklaration von Konstanten und Variablen
#define DataPinR 7
#define ShiftPinR  6
#define StorePinR  5
#define DataPinS  3
#define ShStPinS  4
#define TasterAuf  A0
#define TasterRechts  A1
#define TasterAb  A2
#define TasterLinks  A3

#define MaxZeile 16
#define MaxSpalte 8
#define d 0.2

int n;
int i;



int WertAuf = 0;      // Da wir anlagoe Eingänge haben müssen diese zuerst noch eingelesen und gespeichert werden.
int WertRechts = 0;   // Da wir anlagoe Eingänge haben müssen diese zuerst noch eingelesen und gespeichert werden.
int WertAb = 0;       // Da wir anlagoe Eingänge haben müssen diese zuerst noch eingelesen und gespeichert werden.
int WertLinks = 0;    // Da wir anlagoe Eingänge haben müssen diese zuerst noch eingelesen und gespeichert werden.
int WertNichts = 0;

// Array definieren welches dann angezeigt werden soll auf dem Dysplay
  bool AnzeigeAuf [8][16] = {           //Array für die Aufwaertstaste 
    {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,1,1,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,1,1,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,1,1,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
    {0,0,0,1,1,0,0,0 ,0,0,0,0,0,0,0,0},
    };
  bool AnzeigeRechts [8][16] = {        //Array für die rechts Taste
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0}, 
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}, 
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}, 
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    bool AnzeigeAb [8][16] = {          //Array für die nach unten Taste 
    {0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0}, 
    {0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0}, 
    {0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0}, 
    {0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0}, 
    {0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0}, 
    {0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    };
    bool AnzeigeLinks [8][16] = {     //Array für die links Taste
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0}, 
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}, 
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0}, 
    {0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    bool Nichts [8][16] = {     //Array für die links Taste
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };
    



void setup() {
  //Ausgaenge und Eingaenge beim Arduino definieren
  pinMode(DataPinR, OUTPUT);
  pinMode(ShiftPinR, OUTPUT);
  pinMode(StorePinR, OUTPUT);
  pinMode(DataPinS, OUTPUT);
  pinMode(ShStPinS, OUTPUT);
  pinMode(TasterAuf, INPUT);
  pinMode(TasterRechts, INPUT);
  pinMode(TasterAb, INPUT);
  pinMode(TasterLinks, INPUT);
  digitalWrite(ShStPinS, LOW);
  }

void loop() {
  //Auslesen der Analogen Eingängen
  if (analogRead(TasterAuf)>500){
    WertAuf = 1;
  }
  if (analogRead(TasterRechts)>500){
    WertRechts = 1;
  }
  if (analogRead(TasterAb)>500){
    WertAb = 1;
  }
  if (analogRead(TasterLinks)>500){
    WertLinks = 1;
  }
  if (WertLinks == 0 && WertAb == 0 && WertAuf == 0 && WertRechts == 0){
    WertNichts = 1;
  }

 //Zuweisung, welche Array bei welchem Tastendruck angezeigt wird.
 if (WertAuf == 1){
  digitalWrite(DataPinS, HIGH);                   //DatapinS auf High setzten damit das Bit zum durchschieben bereit gestellt wird.
    for (i=0; i<MaxSpalte; i++){                  //For schleife um die einzelnen Reihen durchzuschalten welche angezeigt werden soll 
      digitalWrite(ShStPinS, HIGH);               //StorePin und ShiftPin von LOW auf HIGH setzten da auf positive Flanke reagiert.
      delay(d);                                   //Verzoegerungszeit damit das Schieberegister reagieren kann
      digitalWrite(ShStPinS, LOW);              
      digitalWrite(DataPinS, LOW);
                       
      digitalWrite(StorePinR, LOW);               //StorePin auf LOW setzten da auf positive Flanke reagiert. (Aus sicherheit)
      for (n=0; n<MaxZeile; n++){                 // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
        digitalWrite(ShiftPinR, LOW);
        digitalWrite(DataPinR, AnzeigeAuf [i][n]);
        digitalWrite(ShiftPinR, HIGH);
        }
      digitalWrite(StorePinR, HIGH);
      delay(1);
      digitalWrite(StorePinR, LOW);      
      }
      WertAuf = 0;
 }
 if (WertNichts == 1){
  digitalWrite(DataPinS, HIGH);                   //DatapinS auf High setzten damit das Bit zum durchschieben bereit gestellt wird.
    for (i=0; i<MaxSpalte; i++){                  //For schleife um die einzelnen Reihen durchzuschalten welche angezeigt werden soll 
      digitalWrite(ShStPinS, HIGH);               //StorePin und ShiftPin von LOW auf HIGH setzten da auf positive Flanke reagiert.
      delay(d);                                   //Verzoegerungszeit damit das Schieberegister reagieren kann
      digitalWrite(ShStPinS, LOW);              
      digitalWrite(DataPinS, LOW);
                       
      digitalWrite(StorePinR, LOW);               //StorePin auf LOW setzten da auf positive Flanke reagiert. (Aus sicherheit)
      for (n=0; n<MaxZeile; n++){                 // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
        digitalWrite(ShiftPinR, LOW);
        digitalWrite(DataPinR, Nichts [i][n]);
        digitalWrite(ShiftPinR, HIGH);
        }
      digitalWrite(StorePinR, HIGH);    
      }
      WertAuf = 0;
 }
 
  
}
