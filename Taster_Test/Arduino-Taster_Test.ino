#define auf           A0 // Taster-Auf
#define rechts        A1 // Taster-Rechts
#define unten         A2 // Taster-Unten
#define links         A3 // Taster-Links
#define Start         A4 // Taster-Start-Game
#define OnOff         A5 // Taster-On-Off
#define StartLED      8 // LED-Start
#define Zeit2         5 // Zeit-Start
#define Zeit1         500 // Zeit optische Meldung
#define Anzeigedauer  200 // Wie lange eine Farbe leuchten soll
#define Zeit          10000
#define DataPinR      5 // Data Pin des 16Bit Schieberegisters
#define ShiftPinR     6 // Shift Pin des 16Bit Schieberegisters
#define StorePinR     7 // Store Pin des 16Bit Schieberegisters
#define DataPinS      3 // Data Pin des 8Bit Schieberegisters
#define ShStPinS      4 // Store und Shift Pin des 8Bit Schieberegisters
#define MaxZeile      16 // Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte     8 

int switchStatea0;
int switchStatea1;
int switchStatea2;
int switchStatea3;
int switchStatea4;
int switchStateonoff;

int i, // Für die For-Schlaufe
    n, // Für die For-Schlaufe
    a, // Für die For-Schlaufe
    dauer;

bool Array [8][16] = {     
                      {1,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
                      {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
                      {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
                      {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
                      {0,0,0,0,0,0,0,0 ,0,0,0,1,0,0,0,0}, 
                      {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
                      {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0}, 
                      {0,0,0,0,0,0,0,0 ,0,0,0,0,0,0,0,0},
                    };           

void setup(){ // Pins-Output deklarieren
  pinMode(auf, OUTPUT);
  pinMode(unten, OUTPUT);
  pinMode(links, OUTPUT);
  pinMode(rechts, OUTPUT);
  pinMode(Start, OUTPUT);
  pinMode(StartLED, OUTPUT);
  pinMode(OnOff, OUTPUT);
  pinMode(DataPinR, OUTPUT);
  pinMode(ShiftPinR, OUTPUT);
  pinMode(StorePinR, OUTPUT);
  pinMode(DataPinS, OUTPUT);
  pinMode(ShStPinS, OUTPUT);

  digitalWrite(ShStPinS, LOW); // Sicherheitshalber Pin auf Low setzten

  Serial.begin(9600); // Serial.println("");
}

void loop() {
            do{
               switchStatea4 = digitalRead(A4);
               switchStateonoff = digitalRead(A5);
            
               Serial.print ("Zustand Schalter: ");
               Serial.print(switchStateonoff); 
               Serial.print(", Zustand Reset: ");
               Serial.print(switchStatea4);
               Serial.println(".");
               delay(Zeit2);
              }while(switchStatea4 == 0 && switchStateonoff == 0  );  
                  
            if(switchStatea4 == HIGH && switchStateonoff == HIGH){
              Serial.println("Game started!");             
               for (int a = 0; a < 3; a++){ // Optische Meldung
                    for (int b = 1; b > -1; b--){ 
                    delay(Zeit1);
                    digitalWrite(StartLED, b);
                       }
                     }
                digitalWrite(switchStatea4, LOW);
              }
            }