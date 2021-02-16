#define DataPinS  3                                
#define ShStPinS  4                               
#define DataPinR  5                               
#define ShiftPinR 6                                
#define StorePinR 7  
   
#define MaxZeile  8                               
#define MaxSpalte 8
   
#define Anzeige 1 

#define auf      A0          
#define rechts   A1         
#define unten    A2         
#define links    A3         

  bool Pfeilauf [8][8] = {              
    {0,0,0,1,1,0,0,0}, 
    {0,0,1,1,1,1,0,0}, 
    {0,1,1,1,1,1,1,0}, 
    {1,1,1,1,1,1,1,1}, 
    {0,0,1,1,1,1,0,0}, 
    {0,0,1,1,1,1,0,0}, 
    {0,0,1,1,1,1,0,0}, 
    {0,0,1,1,1,1,0,0},
    };
    
  bool Pfeilunten [8][8] = {              
    {0,0,1,1,1,1,0,0}, 
    {0,0,1,1,1,1,0,0}, 
    {0,0,1,1,1,1,0,0}, 
    {0,0,1,1,1,1,0,0}, 
    {1,1,1,1,1,1,1,1}, 
    {0,1,1,1,1,1,1,0}, 
    {0,0,1,1,1,1,0,0}, 
    {0,0,0,1,1,0,0,0},
    }; 
    
  bool Pfeillinks [8][8] = {              
    {0,0,0,1,0,0,0,0}, 
    {0,0,1,1,0,0,0,0}, 
    {0,1,1,1,1,1,1,1}, 
    {1,1,1,1,1,1,1,1}, 
    {1,1,1,1,1,1,1,1}, 
    {0,1,1,1,1,1,1,1}, 
    {0,0,1,1,0,0,0,0}, 
    {0,0,0,1,0,0,0,0},
    };
    
bool Pfeilrechts [8][8] = {              
    {0,0,0,0,1,0,0,0}, 
    {0,0,0,0,1,1,0,0}, 
    {1,1,1,1,1,1,1,0}, 
    {1,1,1,1,1,1,1,1}, 
    {1,1,1,1,1,1,1,1}, 
    {1,1,1,1,1,1,1,0}, 
    {0,0,0,0,1,1,0,0}, 
    {0,0,0,0,1,0,0,0},
    };

bool nichts [8][8] = {              
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

  pinMode(DataPinR, OUTPUT);
  pinMode(ShiftPinR, OUTPUT);
  pinMode(StorePinR, OUTPUT);
  pinMode(DataPinS, OUTPUT);
  pinMode(ShStPinS, OUTPUT);
  pinMode(auf,OUTPUT);
  pinMode(unten,OUTPUT);
  pinMode(links,OUTPUT);
  pinMode(rechts,OUTPUT);
  
  Serial.begin(9600);
  
}

void loop() {

  int switchStatea0 = digitalRead(A0);
  int switchStatea1 = digitalRead(A1);
  int switchStatea2 = digitalRead(A2);
  int switchStatea3 = digitalRead(A3);

//***********************************************************************//

if ((switchStatea0 || switchStatea1 || switchStatea2 || switchStatea3) == LOW){
                Serial.println("Kein Signal!");
                 digitalWrite(DataPinS,HIGH);
    digitalWrite(ShStPinS,HIGH);
    digitalWrite(DataPinS,LOW);
    digitalWrite(ShStPinS,LOW);
    
      for(int a=0; a<MaxSpalte; a++){
          for (int n=0; n<MaxZeile; n++){                 
               digitalWrite(ShiftPinR, LOW);
               digitalWrite(DataPinR, nichts[a][n]);
               digitalWrite(ShiftPinR, HIGH);
              }
         digitalWrite(StorePinR, HIGH);
         digitalWrite(StorePinR, LOW);
         digitalWrite(ShStPinS, HIGH);
         delay(Anzeige);
         digitalWrite(ShStPinS, LOW);
         delay(Anzeige);
        } 
               }
           if(switchStatea0 == HIGH){
              Serial.println("Auf!");
               digitalWrite(DataPinS,HIGH);
    digitalWrite(ShStPinS,HIGH);
    digitalWrite(DataPinS,LOW);
    digitalWrite(ShStPinS,LOW);
    
      for(int a=0; a<MaxSpalte; a++){
          for (int n=0; n<MaxZeile; n++){                 
               digitalWrite(ShiftPinR, LOW);
               digitalWrite(DataPinR, Pfeilauf[a][n]);
               digitalWrite(ShiftPinR, HIGH);
              }
         digitalWrite(StorePinR, HIGH);
         digitalWrite(StorePinR, LOW);
         digitalWrite(ShStPinS, HIGH);
         delay(Anzeige);
         digitalWrite(ShStPinS, LOW);
         delay(Anzeige);
        } 
              }
           if(switchStatea1 == HIGH){
              Serial.println("Rechts!");
               digitalWrite(DataPinS,HIGH);
    digitalWrite(ShStPinS,HIGH);
    digitalWrite(DataPinS,LOW);
    digitalWrite(ShStPinS,LOW);
    
      for(int a=0; a<MaxSpalte; a++){
          for (int n=0; n<MaxZeile; n++){                 
               digitalWrite(ShiftPinR, LOW);
               digitalWrite(DataPinR, Pfeilrechts[a][n]);
               digitalWrite(ShiftPinR, HIGH);
              }
         digitalWrite(StorePinR, HIGH);
         digitalWrite(StorePinR, LOW);
         digitalWrite(ShStPinS, HIGH);
         delay(Anzeige);
         digitalWrite(ShStPinS, LOW);
         delay(Anzeige);
        } 
              }
           if(switchStatea2 == HIGH){
              Serial.println("Unten!");
               digitalWrite(DataPinS,HIGH);
    digitalWrite(ShStPinS,HIGH);
    digitalWrite(DataPinS,LOW);
    digitalWrite(ShStPinS,LOW);
    
      for(int a=0; a<MaxSpalte; a++){
          for (int n=0; n<MaxZeile; n++){                 
               digitalWrite(ShiftPinR, LOW);
               digitalWrite(DataPinR, Pfeilunten[a][n]);
               digitalWrite(ShiftPinR, HIGH);
              }
         digitalWrite(StorePinR, HIGH);
         digitalWrite(StorePinR, LOW);
         digitalWrite(ShStPinS, HIGH);
         delay(Anzeige);
         digitalWrite(ShStPinS, LOW);
         delay(Anzeige);
        } 
              }
           if(switchStatea3 == HIGH){
              Serial.println("Links!!");
               digitalWrite(DataPinS,HIGH);
    digitalWrite(ShStPinS,HIGH);
    digitalWrite(DataPinS,LOW);
    digitalWrite(ShStPinS,LOW);
    
      for(int a=0; a<MaxSpalte; a++){
          for (int n=0; n<MaxZeile; n++){                 
               digitalWrite(ShiftPinR, LOW);
               digitalWrite(DataPinR, Pfeillinks[a][n]);
               digitalWrite(ShiftPinR, HIGH);
              }
         digitalWrite(StorePinR, HIGH);
         digitalWrite(StorePinR, LOW);
         digitalWrite(ShStPinS, HIGH);
         delay(Anzeige);
         digitalWrite(ShStPinS, LOW);
         delay(Anzeige);
        } 
             }
//***********************************************************************//   
      }
      
    
 
