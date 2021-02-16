#define DataPinS 3                              
#define ShStPinS 4                             
#define MaxZeile 8                                
#define MaxSpalte 8                                 
#define Anzeige 100                         
#define Zeit 5                                  
#define DataPinR 5                                  
#define ShiftPinR 6                                 
#define StorePinR 7     

int i,                                      
    n,                                        
    a,                                       
    dauer;

  bool AnzeigeRot [8][8] = {              
    				        {1,0,0,0,0,0,0,0}, 
    				        {0,1,0,0,0,0,0,0}, 
   				        {0,0,1,0,0,0,0,0}, 
    				        {0,0,0,1,0,0,0,0}, 
    				        {0,0,0,0,1,0,0,0}, 
    				        {0,0,0,0,0,1,0,0}, 
    				        {0,0,0,0,0,0,1,0}, 
    				        {0,0,0,0,0,0,0,1},
    			           };
 
void setup() {

  pinMode(DataPinR, OUTPUT);
  pinMode(ShiftPinR, OUTPUT);
  pinMode(StorePinR, OUTPUT);
  pinMode(DataPinS, OUTPUT);
  pinMode(ShStPinS, OUTPUT);
  
}

void loop() {

    digitalWrite(DataPinS,HIGH);
    digitalWrite(ShStPinS,HIGH);
    digitalWrite(DataPinS,LOW);
    digitalWrite(ShStPinS,LOW);

    for(a=0; a<MaxSpalte; a++){
       for (n=0; n<MaxZeile; n++){                 
            digitalWrite(ShiftPinR, LOW);
            digitalWrite(DataPinR, AnzeigeRot[a][n]);
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
      
    
  
 