#define DataPinS 3                                  //Data Pin des 8Bit Schieberegisters
#define ShStPinS 4                                  //Store und Shift Pin des 8Bit Schieberegisters
#define MaxZeile 8                                 //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 8                                 //Anzahl Spalten der Anzeige einstellen
#define Anzeige 100                         
#define Zeit 5                                  
#define DataPinR 5                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define StorePinR 7     

int i,                                      
    n,                                        
    a,                                       
    dauer;


  bool AnzeigeRot [8][8] = {              
    {0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0},
    };
 


void setup() {


  pinMode(DataPinS, OUTPUT);
  pinMode(ShStPinS, OUTPUT);

  
}

void loop() {

    digitalWrite(DataPinS,HIGH);
    digitalWrite(ShStPinS,HIGH);
    digitalWrite(DataPinS,LOW);
    digitalWrite(ShStPinS,LOW);
    
    for(a=0; a<MaxSpalte; a++){
  
         digitalWrite(ShStPinS, HIGH);
         delay(Anzeige);
         digitalWrite(ShStPinS, LOW);
         delay(Anzeige);
         digitalWrite(StorePinR, LOW);
        }    
    
      }
    
 
