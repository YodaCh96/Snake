//Class Matrix
class Matrix{

  // Länge und Breite des Spielfelds
#define MATRIX_HORIZONTAL_LENGTH 16 
#define MATRIX_VERTICAL_LENGTH 8 
#define DataPinR 7                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define ShStPinS 4                                  //Store und Shift Pin des 8Bit Schieberegisters
#define MaxZeile 16                                 //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 8                                 //Anzahl Spalten der Anzeige einstellen
#define Zeit 0.0001                                   //Verzögerungszeit für Shiftregister
#define EinleseZeit 0.00002


int temp;                                            //Für die Ausgabe der letzter LED-Reihe
int darray   [MATRIX_VERTICAL_LENGTH][MATRIX_HORIZONTAL_LENGTH];

private:
void giveArray();
void EinlesenR(int x);
void EinlesenG(int y);

public:
  void clear();
  void drawPixel(int x, int y,bool isSomething);
  void writeDisplay();
  void print(int input);
  void setCursor(int x, int y);
  void setTextColor(int color);
  void arraytoSerial();

};




void Matrix::clear(){

    
    
    memset(darray, 0, sizeof darray);
    
}

void Matrix::drawPixel(int y, int x, bool drawMe){

    //Wenn drawMe true ist LED anschalten
    if(drawMe == true){  
          darray[y][x*2] = 1;      
    }else{
        darray[y][x*2] = 0;
    }
}


 void Matrix::setTextColor(int color){
  
  }


void Matrix::print(int input){
  
  
}

void Matrix::setCursor(int x, int y){
  
  
}

 void Matrix::writeDisplay(){
    
    giveArray();  

   // arraytoSerial();


}

//Gibt das Array her�ber
void Matrix::giveArray() {
  DDRD = B11111100;                           //ArduiPins als Output deklarieren  


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
void Matrix::EinlesenR(int x) {
  for (int n = 1; n < MaxZeile; n += 2) {          // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, darray[x][n]);   //Auslesen vom 8 x 16 Array 
    digitalWrite(ShiftPinR, HIGH);
  }
}

void Matrix::EinlesenG(int y) {
  for (int z = 0; z < MaxZeile; z += 2) {         // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, darray[y][z]);   //Auslesen vom 8 x 16 Array 
    digitalWrite(ShiftPinR, HIGH);
  }
}



void Matrix::arraytoSerial() {
  //Serial.println("Array auslesen");
  for (int z = 0; z < 8; z++)
  {
    Serial.println("");
    for (int t = 0; t < 16; t++)
    {
      Serial.print(darray[z][t]);
    }
  }
  Serial.println("");
}






//End Class Matrix
