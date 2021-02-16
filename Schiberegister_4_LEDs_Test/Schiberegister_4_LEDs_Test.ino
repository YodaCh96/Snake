#define st 8
#define sh 9
#define ds 10

#define Zeit1 5
#define Zeit2 1000

int x[] = {1,0,1,0};
int y[] = {0,1,0,1};

void setup() {

pinMode (st, OUTPUT);
pinMode (sh, OUTPUT);
pinMode (ds, OUTPUT);

}

void loop() {



for (int i=0; i<4; i++){

  digitalWrite(ds,LOW);
  digitalWrite(sh,LOW);

  digitalWrite(ds,x[i]);
  delay(Zeit1);
  digitalWrite(sh, HIGH);
  delay(Zeit1);
}
digitalWrite(st,HIGH);
delay(Zeit1);
digitalWrite(st,LOW);
delay(Zeit2);

for (int i=0; i<4; i++){

  digitalWrite(ds,LOW);
  digitalWrite(sh,LOW);

  digitalWrite(ds,y[i]);
  delay(Zeit1);
  digitalWrite(sh, HIGH);
  delay(Zeit1);
}
digitalWrite(st,HIGH);
delay(Zeit1);
digitalWrite(st,LOW);
delay(Zeit2);
}
