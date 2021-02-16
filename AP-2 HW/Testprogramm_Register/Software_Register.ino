// Deklaration von Konstanten und Variablen
#define DataPinR 7                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define StorePinR 5                                 //Store Pin des 16Bit Schieberegisters
#define DataPinS 3                                  //Data Pin des 8Bit Schieberegisters
#define ShStPinS 4                                  //Store und Shift Pin des 8Bit Schieberegisters
#define MaxZeile 16                                 //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 8                                 //Anzahl Spalten der Anzeige einstellen
#define Anzeigedauer 400                            //Verzoegrungszeit einstellen, wie lange eine Farbe leuchten soll
#define Zeit 0.1                                    //Verzögerungszeit für Shiftregister


char i;                                             //Für die For-Schlaufe
char n;                                             //Für die For-Schlaufe
int a;                                              //Für die For-Schlaufe

// Array definieren welches dann angezeigt werden soll auf dem Dysplay
  bool AnzeigeRot [16] = { 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};
  bool AnzeigeGruen [16] = { 0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1 };


void setup() {
//ArduiPins als Output deklarieren
  pinMode(DataPinR, OUTPUT);
  pinMode(ShiftPinR, OUTPUT);
  pinMode(StorePinR, OUTPUT);
  pinMode(DataPinS, OUTPUT);
  pinMode(ShStPinS, OUTPUT);
//Sicherheitshalber Pin auf Low setzten
  digitalWrite(ShStPinS, LOW);
  
}

void loop() {
  // Die Roten LEDs zum leuchten bringen:
  for(a=0; a<Anzeigedauer; a++){                  //Schlaufe um Anzeigedauer der Farbe zu bestimmen
    digitalWrite(DataPinS, HIGH);                 //DatapinS auf High setzten damit das Bit zum durchschieben bereit gestellt wird.
    for (i=0; i<MaxSpalte; i++){                  //For schleife um die einzelnen Reihen durchzuschalten welche angezeigt werden soll
      digitalWrite(ShStPinS, HIGH);               //StorePin und ShiftPin eine poitive Flanke erzeugen um das DataPinS Bit einzulesen
      delay(Zeit);                                //Verzoerungszeit damit Schiftregister Zeit zum reagieren haben
      digitalWrite(ShStPinS, LOW);                
      digitalWrite(DataPinS, LOW);                
      digitalWrite(StorePinR, LOW);               //StorePin auf LOW setzten damit dieser wieder einsatzfaehig ist
      for (n=0; n<MaxZeile; n++){                 // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
        digitalWrite(ShiftPinR, LOW);
        digitalWrite(DataPinR, AnzeigeRot[n]);
        digitalWrite(ShiftPinR, HIGH);
        }
      digitalWrite(StorePinR, HIGH);
      delay(Zeit);
      }
    }
      // Die gruenen LEDs zum leuchten bringen:
  for(a=0; a<Anzeigedauer; a++){                  //Schlaufe um Anzeigedauer der Farbe zu bestimmen 
    digitalWrite(DataPinS, HIGH);                 //DatapinS auf High setzten damit das Bit zum durchschieben bereit gestellt wird.
    for (i=0; i<MaxSpalte; i++){                  //For schleife um die einzelnen Reihen durchzuschalten welche angezeigt werden soll
      digitalWrite(ShStPinS, HIGH);               //StorePin und ShiftPin eine poitive Flanke erzeugen um das DataPinS Bit einzulesen
      delay(Zeit);                                //Verzoerungszeit damit Schiftregister Zeit zum reagieren haben
      digitalWrite(ShStPinS, LOW);                //Store Pin und ShitPin für die naechste potive Flanke wieder auf
      digitalWrite(DataPinS, LOW);                //DataPinS wieder auf LOW setzten da dieser nun vom ShStPinS eingelsen wurde   
      digitalWrite(StorePinR, LOW);               //StorePinR auf LOW setzten um diese wieder Einsatzfaehig zu machen
    for (n=0; n<MaxZeile; n++){                   //For schleife zum Setzten einer Reihe sowie das Ausgeben einer Reihe
      digitalWrite(ShiftPinR, LOW);               //ShiftPinR auf LOW setzten da auf positive Flanke reagiert.
      digitalWrite(DataPinR, AnzeigeGruen[n]);    //DataPin vom Schieberegister anhand Arrays auf Low oder High setzen
      digitalWrite(ShiftPinR, HIGH);              //Wert von DataPinR einlesen
      }
    digitalWrite(StorePinR, HIGH);
    delay(Zeit);
    digitalWrite(StorePinR, LOW);
    }
  }
}