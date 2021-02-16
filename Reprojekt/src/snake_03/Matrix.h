//Class Matrix
class Matrix{

  // Länge und Breite des Spielfelds
#define MATRIX_HORIZONTAL_LENGTH 16 
#define MATRIX_VERTICAL_LENGTH 8 
#define DataPinR 7                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define ShStPinS 4                                  //Store und Shift Pin des 8Bit Schieberegisters
#define MaxZeile 8                                  //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 16                                //Anzahl Spalten der Anzeige einstellen
#define EinleseZeit 0.00004
#define LED_GREEN 2
#define LED_RED 1


int temp;                                            //Für die Ausgabe der letzter LED-Reihe
int darray   [MATRIX_VERTICAL_LENGTH][MATRIX_HORIZONTAL_LENGTH];
int ledColor;

private:
void giveArray();
void EinlesenR(int x);
void EinlesenG(int y);
void Leeren();

public:
  void clear();
  void drawPixel(int x, int y,bool isSomething, int ledColor);
  void writeDisplay();
  void print(int input);
  void setCursor(int x, int y);
  void setTextColor(int color);
  void arraytoSerial();

};




void Matrix::clear(){

    
    
    memset(darray, 0, sizeof darray);
    
}

void Matrix::drawPixel(int y, int x, bool drawMe,int ledColor){

    //Wenn drawMe true ist LED anschalten
    if(drawMe == true){  

// darray[y][x*2] = 1; 
    
      if(ledColor == LED_RED){
          darray[y][x*2] = 1;     
      }
      
      else {
           
        
       
        darray[y][(x * 2) + 1] = 1;
        


        /*
        //(ledColor == LED_GREEN)
        if(x > 0){
          darray[y][(x * 2) - 1]   = 1;  
        }
     */
      }  

        
    }else{
        darray[y][x*2] = 0;

        
         
        
      
        darray[y][(x * 2) + 1] = 0;
       
      
    }
}


 void Matrix::setTextColor(int color){
  ledColor = color;
  }


void Matrix::print(int input){
  
  
}

void Matrix::setCursor(int x, int y){
  
  
}

 void Matrix::writeDisplay(){
    
    giveArray();  

   //arraytoSerial();


}

//Gibt das Array her�ber
void Matrix::giveArray() {
  DDRD = B11111100;                           //ArduiPins als Output deklarieren
  
      for(int a=0; a<MaxZeile; a++){
        EinlesenG(a);
        EinlesenR (a);
     /*   if(a == MaxZeile-1){
         PORTD = B00001000;                  //DataPin 8Bit auf High setzten  
        }//if */   
        PORTD = B00110000;
        delay(EinleseZeit);
        PORTD = B00000000;
      }//for
      Leeren();
}


void Matrix::EinlesenR(int x) {
  for (int n = 1; n < MaxSpalte; n += 2) {   //For schleife zum Setzten einer Reihe mir roter Farbe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, darray[x][n]);    //Auslesen vom 8 x 16 Array 
    digitalWrite(ShiftPinR, HIGH);
  }
}

void Matrix::EinlesenG(int y) {
  for (int z = 0; z < MaxSpalte; z += 2) {  //For schleife zum Setzten einer Reihe mit gruener Farbe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, darray[y][z]);   //Auslesen vom 8 x 16 Array 
    digitalWrite(ShiftPinR, HIGH);
  }
}

void Matrix::Leeren() {
  digitalWrite(DataPinR, LOW);   //Auslesen vom 8 x 16 Array
  for(int n=0; n<16; n++){
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(ShiftPinR, HIGH);
  }//for
  PORTD = B00001000;                  //DataPin 8Bit auf High setzten 
  delay(EinleseZeit);
  PORTD = B00110000;
  delay(EinleseZeit);
  PORTD = B00000000;
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
