// Deklaration von Konstanten und Variablen
int DataPinR = 1;
int ShiftPinR = 2;
int StorePinR = 3;
int DataPinS = 4;
int ShStPinS = 5;
int TasterAuf = A0;
int TasterRechts = A1;
int TasterAb = A2;
int TasterLinks = A3;

int i;            //Für die For-Schlaufe
int n;            //Für die For-Schlaufe
int a;            //Für die For-Schlaufe
int MaxZeile = 16;
int MaxSpalte = 8;
int Anzeigedauer = 100;

int WertAuf;      // Da wir anlagoe Eingänge haben müssen diese zuerst noch eingelesen und gespeichert werden.
int WertRechts;   // Da wir anlagoe Eingänge haben müssen diese zuerst noch eingelesen und gespeichert werden.
int WertAb;       // Da wir anlagoe Eingänge haben müssen diese zuerst noch eingelesen und gespeichert werden.
int WertLinks;    // Da wir anlagoe Eingänge haben müssen diese zuerst noch eingelesen und gespeichert werden.

// Array definieren welches dann angezeigt werden soll auf dem Dysplay
  bool AnzeigeRot [16] = { 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 };
  bool AnzeigeGruen [16] = { 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 };



void setup() {
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
  // Die Roten LEDs zum leuchten bringen:
  for(a=0; a<Anzeigedauer; a++){                  //Schlaufe um Anzeigedauer der Farbe zu bestimmen
    digitalWrite(DataPinS, HIGH);                 //DatapinS auf High setzten damit das Bit zum durchschieben bereit gestellt wird.
    for (i=0; i<MaxSpalte; i++){                  //For schleife um die einzelnen Reihen durchzuschalten welche angezegt werden soll
      digitalWrite(ShStPinS, HIGH);               //StorePin und ShiftPin auf LOW setzten da auf positive Flanke reagiert.
      delay(2);
      digitalWrite(ShStPinS, LOW);
      digitalWrite(DataPinS, LOW);               //DataPinS wieder auf LOW setzten da dieser nun vom ShStPinS eingelsen wurde. 
    
      digitalWrite(StorePinR, LOW);                 //StorePin auf LOW setzten da auf positive Flanke reagiert.
    for (n=0; n<MaxZeile; n++){                   // For schleife zum Setzten einer Reihe und das Ausgeben einer Reihe
      digitalWrite(ShiftPinR, LOW);
      digitalWrite(DataPinR, AnzeigeRot[i]);
      digitalWrite(ShiftPinR, HIGH);
      }
    digitalWrite(StorePinR, HIGH);
    delay(2);
    digitalWrite(StorePinR, LOW);
    }
  }

  // Die gruenen LEDs zum leuchten bringen:
  for(a=0; a<Anzeigedauer; a++){                  //Schlaufe um Anzeigedauer der Farbe zu bestimmen 
    digitalWrite(DataPinS, HIGH);                 //DatapinS auf High setzten damit das Bit zum durchschieben bereit gestellt wird.
    for (i=0; i<MaxSpalte; i++){                  //For schleife um die einzelnen Reihen durchzuschalten welche angezegt werden soll
      digitalWrite(ShStPinS, HIGH);               //StorePin und ShiftPin auf LOW setzten da auf positive Flanke reagiert.
      delay(2);
      digitalWrite(ShStPinS, LOW);
      digitalWrite(DataPinS, LOW);               //DataPinS wieder auf LOW setzten da dieser nun vom ShStPinS eingelsen wurde. 
    
      digitalWrite(StorePinR, LOW);                 //StorePin auf LOW setzten da auf positive Flanke reagiert.
    for (n=0; n<MaxZeile; n++){                   // For schleife zum Setzten einer Reihe und das Ausgeben einer Reihe
      digitalWrite(ShiftPinR, LOW);
      digitalWrite(DataPinR, AnzeigeGruen[i]);
      digitalWrite(ShiftPinR, HIGH);
      }
    digitalWrite(StorePinR, HIGH);
    delay(2);
    digitalWrite(StorePinR, LOW);
    }
  }
  
  
  
  
}
