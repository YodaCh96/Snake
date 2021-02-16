// Deklaration von Konstanten und Variablen
#define DataPinR 7                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define ShStPinS 4                                  //Store und Shift Pin des 8Bit Schieberegisters
#define MaxZeile 16                                 //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 8                                 //Anzahl Spalten der Anzeige einstellen
#define Zeit 0.0001                                   //Verzögerungszeit für Shiftregister
#define EinleseZeit 0.00002
// Pinbelegung der Buttons für die Steuerung
#define PIN_BUTTON_RIGHT A1
#define PIN_BUTTON_LEFT A3
#define PIN_BUTTON_TOP A0
#define PIN_BUTTON_BOTTOM A2  


int temp,                                            //Für die Ausgabe der letzter LED-Reihe
    Taster = 0,                                      //Erkennungsvariabel der  Taster
    Erkennung = 0;                                   //

// Arrays definieren welches dann angezeigt werden soll auf dem Dysplay
  bool AnzeigeRot [8][16] = {               //Array für die rote Anzeige
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0}, 
    {1,1,1,1,1,1,1,1 ,0,0,0,0,0,0,0,0},
    };
    
  bool AnzeigeGruen [8][16] = {               //Array für die gruene Anzeige 
    {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1}, 
    {0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1},
    };

  bool EinlesenNichts [8][16] = {0};          //Array für die leere Anzeige


void setup() {       
  digitalWrite(ShStPinS, LOW);                //Sicherheitshalber Pin auf Low setzten    
  DDRD = B11111100;                           //ArduiPins als Output deklarieren 
}

void loop() {
  Tastercheck();                             //Ueberpruefen ob ein Taster gedrueckt ist
  switch (Taster){                           
    case 1:                                 //Ausfuehrung wenn Taster nach oben gedrueckt ist.
        Serial.println("Taster nach oben");
    for(int c=0;c<10;c++){
      for(int b=0;b<100;b++){
      PORTD = B00001000;
      delay(EinleseZeit);
      PORTD = B00111000;
      delay(EinleseZeit);
      PORTD = B00000000;
      for(int a=0; a<MaxSpalte-1; a++){
        EinlesenG(a);
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
        temp = a+1;
      }
      EinlesenG(temp);
      }
      for(int b=0;b<10;b++){
      PORTD = B00001000;
      delay(EinleseZeit);
      PORTD = B00111000;
      delay(EinleseZeit);
      PORTD = B00000000;
      for(int a=0; a<MaxSpalte-1; a++){
        EinlesenN(a);
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
        temp = a+1;
      }
      EinlesenN(temp);  
      }  
  }
  break;   
    case 2:                                 //Ausfuehrung wenn Taster nach unten gedrueckt ist.
        Serial.println("Taster nach unten");
      for(int c=0;c<10;c++){
        for(int b=0;b<10;b++){
        PORTD = B00001000;
        delay(EinleseZeit);
        PORTD = B00111000;
        delay(EinleseZeit);
        PORTD = B00000000;
        for(int a=0; a<MaxSpalte-1; a++){
          EinlesenG(a);
          PORTD = B00110000;
          delay(EinleseZeit);
          PORTD = B00000000;
          temp = a+1;
        }
        EinlesenG(temp);
        }

        for(int b=0;b<100;b++){
        PORTD = B00001000;
        delay(EinleseZeit);
        PORTD = B00111000;
        delay(EinleseZeit);
        PORTD = B00000000;
        for(int a=0; a<MaxSpalte-1; a++){
          EinlesenN(a);
          PORTD = B00110000;
          delay(EinleseZeit);
          PORTD = B00000000;
          temp = a+1;
        }
        EinlesenN(temp);  
      }  
     }
break;
case 3:                                 //Ausfuehrung wenn Taster nach links gedrueckt ist.
    Serial.println("Taster nach links");
    for(int c=0;c<10;c++){
      for(int b=0;b<50;b++){
      PORTD = B00001000;
      delay(EinleseZeit);
      PORTD = B00111000;
      delay(EinleseZeit);
      PORTD = B00000000;
      for(int a=0; a<MaxSpalte-1; a++){
        EinlesenR(a);
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
        temp = a+1;
      }
      EinlesenR(temp);
      }
      for(int b=0;b<50;b++){
      PORTD = B00001000;
      delay(EinleseZeit);
      PORTD = B00111000;
      delay(EinleseZeit);
      PORTD = B00000000;
      for(int a=0; a<MaxSpalte-1; a++){
        EinlesenN(a);
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
        temp = a+1;
      }
      EinlesenN(temp);  
      }  
  }
  break;

case 4:                                   //Ausfuehrung wenn Taster nach rechts gedrueckt ist.
    Serial.println("Taster nach rechts");
    for(int c=0;c<10;c++){
      for(int b=0;b<50;b++){
      PORTD = B00001000;
      delay(EinleseZeit);
      PORTD = B00111000;
      delay(EinleseZeit);
      PORTD = B00000000;
      for(int a=0; a<MaxSpalte-1; a++){
        EinlesenG(a);
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
        temp = a+1;
      }
      EinlesenG(temp);
      }
      for(int b=0;b<50;b++){
      PORTD = B00001000;
      delay(EinleseZeit);
      PORTD = B00111000;
      delay(EinleseZeit);
      PORTD = B00000000;
      for(int a=0; a<MaxSpalte-1; a++){
        EinlesenN(a);
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
        temp = a+1;
      }
      EinlesenN(temp);  
      }  
  }
  break;
    

    default:                        //Ausfuehrung wenn keiner der Tasten gedrueckt ist.
    for(int b=0;b<10;b++){
      PORTD = B00001000;
      delay(EinleseZeit);
      PORTD = B00111000;
      delay(EinleseZeit);
      PORTD = B00000000;
      for(int a=0; a<MaxSpalte-1; a++){
        EinlesenR(a);
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
        temp = a+1;
      }
      EinlesenR(temp);
    }
  }

}



void EinlesenR(int x){                            //Funktion fuer das Array Anzeige Rot
  for (int n=0; n<MaxZeile; n++){                 // For schleife zum Setzten einer Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, AnzeigeRot[x][n]);
    digitalWrite(ShiftPinR, HIGH);
  }
}

void EinlesenG(int x){                            //Funktion fuer das Array Anzeige Gruen
  for (int n=0; n<MaxZeile; n++){                 //For schleife zum Setzten einer Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, AnzeigeGruen[x][n]);
    digitalWrite(ShiftPinR, HIGH);
  }
}

void EinlesenN(int y){                            //Funktion fuer das Array EinlesenNichts
  for (int n=0; n<MaxZeile; n++){                 //For schleife zum Setzten einer Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, EinlesenNichts[y][n]);
    digitalWrite(ShiftPinR, HIGH);
  }
}

void Tastercheck(){                              ////Funktion fuer das Ueberpruefen der Tastendruecke
  Erkennung = 0;
  Taster = 0;
  Erkennung = analogRead(PIN_BUTTON_TOP);
  if (Erkennung > 500){
    Taster = 1;
  }

  Erkennung = analogRead(PIN_BUTTON_BOTTOM);
  if (Erkennung > 500){
    Taster = 2;
  }

  Erkennung = analogRead(PIN_BUTTON_LEFT);
  if (Erkennung > 500){
    Taster = 3;
  }

  Erkennung = analogRead(PIN_BUTTON_RIGHT);
  if (Erkennung > 500){
    Taster = 4;
  }

}

