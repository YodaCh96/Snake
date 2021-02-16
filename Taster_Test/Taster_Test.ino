#define auf A0
#define unten A2
#define rechts A1
#define links A3

//int switchStatea0 = 0;
//int switchStatea1 = 0;
//int switchStatea2 = 0;
//int switchStatea3 = 0;

void setup(){
  pinMode (auf, OUTPUT);
  pinMode (unten, OUTPUT);
  pinMode (links, OUTPUT);
  pinMode (rechts, OUTPUT);
  Serial.begin(9600);
  
}

void loop(){
  
  int switchStatea0 = digitalRead(A0);
  int switchStatea1 = digitalRead(A1);
  int switchStatea2 = digitalRead(A2);
  int switchStatea3 = digitalRead(A3);
  
 if (switchStatea0 == HIGH){
  Serial.println("Auf!!!");
}
if (switchStatea1 == HIGH){
  Serial.println("Rechts!!!");
}
if (switchStatea2 == HIGH){
  Serial.println("Unten!!!");
} 
if (switchStatea3 == HIGH){
  Serial.println("Links!!!");
} 
if ((switchStatea0 || switchStatea1 || switchStatea2 || switchStatea3) == LOW){
  Serial.println("Kein Signal!!!");
}
}
