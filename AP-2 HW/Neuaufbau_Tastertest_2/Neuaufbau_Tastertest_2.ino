//Konstanten definition
#define DataPinR 7                        //Data Pin des 16Bit Schieberegisters
#define ShiftPinR  6                      //Shift Pin des 16Bit Schieberegisters
#define StorePinR  5                      //Store Pin des 16Bit Schieberegisters
#define DataPinS  3                       //Data Pin des 8Bit Schieberegisters
#define ShStPinS  4                       //Store und Shift Pin des 8Bit Schieberegisters
#define TasterAuf A0                      //Eingang für Taste Auf
#define TasterAb  A2                      //Eingang für Taste Ab
#define TasterLinks A3                    //Eingang für Taste Links
#define TasterRechts A1                   //Eingang für Taste Rechts
#define d 0.1                             //Konstante für die Zeitverzögerung
#define MaxSpalte 8                       //Einstellen der Anzahl Spalten
#define MaxZeile 16                       //Einstellen der Anzahl Zeilen


// Variablen definition
int i;                                    //Initialisierung Variable für for-Schlaufe
int n;                                    //Initialisierung Variable für for-Schlaufe

bool AnzeigeAuf [8][16] = {               //Array für die Aufwaertstaste 
    {0,0,0,1,1,0,0,0 ,1,1,1,0,0,1,1,1}, 
    {0,0,1,1,1,1,0,0 ,1,1,0,0,0,0,1,1}, 
    {0,1,1,1,1,1,1,0 ,1,0,0,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0 ,1,1,1,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0 ,1,1,1,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0 ,1,1,1,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0 ,1,1,1,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0 ,1,1,1,0,0,1,1,1},
    };
    
bool AnzeigeAb [8][16] = {              //Array für die nach unten Taste 
    {0,0,0,1,1,0,0,0, 1,1,1,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0, 1,1,1,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0, 1,1,1,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0, 1,1,1,0,0,1,1,1}, 
    {0,0,0,1,1,0,0,0, 1,1,1,0,0,1,1,1}, 
    {0,1,1,1,1,1,1,0, 1,0,0,0,0,0,0,1}, 
    {0,0,1,1,1,1,0,0, 1,1,0,0,0,0,1,1}, 
    {0,0,0,1,1,0,0,0, 1,1,1,0,0,1,1,1},
    };

bool AnzeigeLinks [8][16] = {            //Array für die nach links Taste    
    {0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1}, 
    {0,0,1,0,0,0,0,0, 1,1,0,1,1,1,1,1}, 
    {0,1,1,0,0,0,0,0, 1,0,0,1,1,1,1,1}, 
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0}, 
    {0,1,1,0,0,0,0,0, 1,0,0,1,1,1,1,1}, 
    {0,0,1,0,0,0,0,0, 1,1,0,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1},
    };

bool AnzeigeRechts [8][16] = {          //Array für die nach rechts Taste    
    {0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,1,0,0, 1,1,1,1,1,0,1,1}, 
    {0,0,0,0,0,1,1,0, 1,1,1,1,1,0,0,1}, 
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,1,1,0, 1,1,1,1,1,0,0,1}, 
    {0,0,0,0,0,1,0,0, 1,1,1,1,1,0,1,1}, 
    {0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1},
    };
    
bool Nichts [8][16] = {                 //Array wenn keine Taste gedrueckt wird                    
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
  // Die Pins des Arduiono definieren
  pinMode(DataPinR, OUTPUT);
  pinMode(ShiftPinR, OUTPUT);
  pinMode(StorePinR, OUTPUT);
  pinMode(DataPinS, OUTPUT);
  pinMode(ShStPinS, OUTPUT);
  pinMode(TasterAuf, INPUT);
  pinMode(TasterAb, INPUT);
  // Aus sicherheit alle Ausgänge auf LOW setzten
  digitalWrite(DataPinS, LOW);
  digitalWrite(ShStPinS, LOW);
  digitalWrite(StorePinR, LOW);
  digitalWrite(ShiftPinR, LOW);
  digitalWrite(DataPinR, LOW);

}

void loop() {
  if(analogRead(TasterAuf) > 500){                              // If Anweisung wenn Taster nach oben gedrueckt wird.
    for(i=0; i<MaxSpalte; i++){                                  // For Schlaufe um die einzelnen Reihen anzusteuern.
     if (i == 0){                                                // Setzt das einzelne Bit welches bestimmt welche Reihe leuchtet                                            
      digitalWrite(DataPinS, HIGH); 
      }
    digitalWrite(ShStPinS, HIGH);                               // Das einzelne Bit wird im Schieberegister (SR) weitergeschoben.
    delay(d);
    digitalWrite(ShStPinS, LOW);
    digitalWrite(DataPinS, LOW);
     
       for (n=0; n<MaxZeile; n++){                               // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
        digitalWrite(ShiftPinR, LOW);                           //Das Array wird ausgelesen und die Informationen ans SR uebergeben
        digitalWrite(DataPinR, AnzeigeAuf [i][n]);
        digitalWrite(ShiftPinR, HIGH);
        }
       digitalWrite(StorePinR, HIGH);
       delay(d);
       digitalWrite(StorePinR, LOW);
  }
  }if(analogRead(TasterAb) > 200){                             // If Anweisung wenn Taster nach unten gedrueckt wird.
   for(i=0; i<MaxSpalte; i++){                                  // Gleicher Aufbau wie bei Taster nach oben gedrzueckt.
     if (i == 0){                                            
      digitalWrite(DataPinS, HIGH); 
      }
    digitalWrite(ShStPinS, HIGH);
    delay(d);
    digitalWrite(ShStPinS, LOW);
    digitalWrite(DataPinS, LOW);
     
       for (n=0; n<MaxZeile; n++){
        digitalWrite(ShiftPinR, LOW);
        delay(d);
        digitalWrite(DataPinR, AnzeigeAb [i][n]);
        delay(d);
        digitalWrite(ShiftPinR, HIGH);
        delay(d);
        }
       digitalWrite(StorePinR, HIGH);
       delay(d);
       digitalWrite(StorePinR, LOW);
  }
  }if(analogRead(TasterLinks) > 500){                          // If Anweisung wenn Taster nach links gedrueckt wird.
   for(i=0; i<MaxSpalte; i++){                                  // Gleicher Aufbau wie bei Taster nach oben gedrzueckt.
     if (i == 0){
      digitalWrite(DataPinS, HIGH); 
      }
    digitalWrite(ShStPinS, HIGH);
    delay(d);
    digitalWrite(ShStPinS, LOW);
    digitalWrite(DataPinS, LOW);
     
       for (n=0; n<MaxZeile; n++){
        digitalWrite(ShiftPinR, LOW);
        delay(d);
        digitalWrite(DataPinR, AnzeigeLinks [i][n]);
        delay(d);
        digitalWrite(ShiftPinR, HIGH);
        delay(d);
        }
       digitalWrite(StorePinR, HIGH);
       delay(d);
       digitalWrite(StorePinR, LOW);
  }
  }if(analogRead(TasterRechts) > 500){                          // If Anweisung wenn Taster nach rechts gedrueckt wird.
   for(i=0; i<MaxSpalte; i++){                                  // Gleicher Aufbau wie bei Taster nach oben gedrzueckt.
     if (i == 0){
      digitalWrite(DataPinS, HIGH); 
      }
    digitalWrite(ShStPinS, HIGH);
    delay(d);
    digitalWrite(ShStPinS, LOW);
    digitalWrite(DataPinS, LOW);
     
       for (n=0; n<MaxZeile; n++){
        digitalWrite(ShiftPinR, LOW);
        delay(d);
        digitalWrite(DataPinR, AnzeigeRechts [i][n]);
        delay(d);
        digitalWrite(ShiftPinR, HIGH);
        delay(d);
        }
       digitalWrite(StorePinR, HIGH);
       delay(d);
       digitalWrite(StorePinR, LOW);
  }
  }else{
    for(i=0; i<MaxSpalte; i++){                                  // Anweisung wenn kein Taster gedrueckt wird                                                             
     if (i == 0){                                                 // Gleicher Aufbau wie bei Taster nach oben gedrzueckt.                                            
      digitalWrite(DataPinS, HIGH); 
      }
    digitalWrite(ShStPinS, HIGH);
    delay(d);
    digitalWrite(ShStPinS, LOW);
    digitalWrite(DataPinS, LOW);
     
       for (n=0; n<MaxZeile; n++){
        digitalWrite(ShiftPinR, LOW);
        delay(d);
        digitalWrite(DataPinR, Nichts [i][n]);
        delay(d);
        digitalWrite(ShiftPinR, HIGH);
        delay(d);
        }
       digitalWrite(StorePinR, HIGH);
       delay(d);
       digitalWrite(StorePinR, LOW);
  }  
  }
  
}

