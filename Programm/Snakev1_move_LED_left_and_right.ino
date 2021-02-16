  /*
  Name: Snakev1.ino
  Created: 5/17/2017 10:23:11 AM
  Author: Ioannis Christodoulakis
  */
  #include <pt.h>
  #include <avr/wdt.h>
  #define DataPinR 7 //Data Pin des 16Bit Schieberegisters
  #define ShiftPinR 6 //Shift Pin des 16Bit Schieberegisters
  #define MaxZeile 16 //Anzahl Zeilen der Anzeige einstellen
  #define MaxSpalte 8 //Anzahl Spalten der Anzeige einstellen
  //#define EinleseZeit 0.0002 //Zeitverzoegerung damit das SR reagieren kann
  #define EinleseZeit 0.0002 //Zeitverzoegerung damit das SR reagieren kann
  
  static unsigned long timestampExc = 2;
  static unsigned long snakeSpeed = 50;
  
  int temp;
  int random1;
  int random2;
  int darray[10][18];
  int darraycp[10][18];
  
  //Variabeln fo?=r die Pins der Variabeln
  int buttonTop = A0;
  int buttonBot = A2;
  int buttonRight = A1;
  int buttonLeft = A3;
  int hightnumber = 0;
  int widhtnumber = 0;
  
  //Zo?=hler
  int count = 0;
  int counter = 0;
  
  //Variabeln fo?=r die Score-Ausgabe
  int gamescore = 0;
  int firstpart = 0;
  int secondpart = 0;
  
  //Variabeln welche das Signal der Buttons o?=berpro?=fen
  int buttonTpress = 0;
  int buttonBpress = 0;
  int buttonLpress = 0;
  int buttonRpress = 0;
  
  //Button welcher als letztes gedro?=ckt wurde
  int lastpressed = 4;
  
  //Konstanten fo?=r die Richtung der Schlange
  int const left = 3;
  int const right = 4;
  int const top = 1;
  int const bot = 2;
  
  //Boolean welcher o?=berpro?=ft ob das Spiel vorbei ist
  bool gameover = false;
  
  //Verschiedene Bools um Werte innerhalb des Arrays zu finden
  bool gefunden = true;
  bool foundNr1 = false;
  bool foundLast = false;
  
  static struct pt pt1, pt2, pt3;
  int i = 0;

  void setup ()
  {
    // Serial.begin(9600);
    //Anfangs Position und Lo?=nge der Schlange
    darray[5][8] = 1;
    darray[5][6] = 1;
    darraycp[5][10] = 1;
    darraycp[5][8] = 2;
    darray[7][11] = 2;
    darraycp[7][10] = 2000;
    //Pins mit einem Button werden gezeichnet als Input.
    pinMode (buttonTop, INPUT);
    pinMode (buttonLeft, INPUT);
    pinMode (buttonRight, INPUT);
    pinMode (buttonBot, INPUT);
    DDRD = B11111100;
    Serial.println (gameover);
    /*Serial.println(darray[5][8]);
    Serial.println(darray[1][8]); */
    PT_INIT (&pt1);
    PT_INIT (&pt2);
    PT_INIT (&pt3);
    Serial.println ("Setup");
  }

  static int protothread1 (struct pt *pt)
  {
    static unsigned long timestamp = 0;
    PT_BEGIN (pt);
    while (1)
    {
      timestamp = millis ();
      PT_WAIT_UNTIL (pt, millis () - timestamp > timestampExc);
      buttonpress ();
    }
    PT_END (pt);
  }

  static int protothread2 (struct pt *pt)
  {
    static unsigned long timestamp = 0;
    PT_BEGIN (pt);
    while (1)
    {
      timestamp = millis ();
      PT_WAIT_UNTIL (pt, millis () - timestamp > snakeSpeed);
      looping ();
    }
    PT_END (pt);
  }

  static int protothread3 (struct pt *pt)
  {
    static unsigned long timestamp = 0;
    PT_BEGIN (pt);
    while (1)
    {
      timestamp = millis ();
      PT_WAIT_UNTIL (pt, millis () - timestamp > timestampExc);
      giveArray ();
    }
    PT_END (pt);
  }

  void looping ()
  {
    //  Serial.println("Button Press Value");
    // goLeft();
    if (buttonLpress > 500)
    {
      Serial.println ("left");
      goLeft ();
    }
    //Falls der Button nach rechts gedro?=ckt wurde
    else if (buttonRpress > 500)
    {
      Serial.println ("right");
      goRight ();
    }
    else if (buttonBpress > 500)
    {
      Serial.println ("down");
      goDown ();
    }
    else if (buttonTpress > 500)
    {
      Serial.println ("up");
      goUp ();
    }
    /* if(stop == 500){
      exit(0);
    } */
  }

  void buttonpress ()
  {
    Serial.println ("Buttonpress");
    //Signal der Buttons wird o?=berpro?=ft
    buttonTpress = analogRead (buttonTop);
    buttonBpress = analogRead (buttonBot);
    buttonLpress = analogRead (buttonLeft);
    buttonRpress = analogRead (buttonRight);
  }

void moveSnake(int currentSnakeDirection, int previousSnakeDirection){
  
   for (int z = 1; z < 9; z++)
    {
      for (int t = 1; t < 17; t++)
      {

        

        
      } 
}

  //Bewegt sich nach rechts
  void goLeft ()
  {
    //Test move Snake MN
    for (int z = 1; z < 9; z++)
    {
      for (int t = 1; t < 17; t++)
      {
        // darray[z][t+1]=0;
        // delay(100);
        // int tt = t + 2;
        if (darray[z][2] == 1 && darray[z][4] == 1)
        {
          //Schlange am Ende angekommen
        }
        else
        {
          if (darray[z][t] == 1)
          {
            darray[z][t] = 0;
            darray[z][t - 2] = 1;
          }
        }
      }
    }
    Serial.println ("Left Array auslesen");
    for (int z = 1; z < 9; z++)
    {
      Serial.println ("");
      for (int t = 1; t < 17; t++)
      {
        Serial.print (darray[z][t]);
      }
    }
    Serial.println ("");
  }

  //Bewegt sich nach rechts
  void goRight ()
  {
    Serial.println ("Go right");
    //Test move Snake MN
    for (int z = 1; z < 9; z++)
    {
      for (int t = 17; t > 1; t--)
      {
        /* if(z==3)
        darray[z][t+1]=1;
      } */
      if (darray[z][14] == 1 && darray[z][16] == 1)
      {
      }
      else
      {
        if (darray[z][t] == 1)
        {
          darray[z][t] = 0;
          darray[z][t + 2] = 1;
        }
      }
    }
  }

  //MN
  Serial.println ("Right Array auslesen");
  for (int z = 1; z < 9; z++)
  {
    Serial.println ("");
    for (int t = 1; t < 17; t++)
    {
      Serial.print (darray[z][t]);
    }
  }
  Serial.println ("");
  }

  //Bewegt sich nach rechts
  void goUp ()
  {
    Serial.println ("Go up");
    for (int z = 1; z < 9; z++)
    {
      for (int t = 1; t < 17; t++)
      {
        if (darray[z][t] == 1)
        {
          darray[z][t] = 0;
          darray[z - 1][t] = 1;
        }
      }
    }
  }

  //Bewegt sich nach rechts
  void goDown ()
  {
    Serial.println ("Go down");
    for (int z = 9; z > 0; z--)
    {
      for (int t = 1; t < 17; t++)
      {
        if (darray[z][t] == 1)
        {
          darray[z][t] = 0;
          darray[z + 1][t] = 1;
        }
      }
    }
  }

  //Gibt das Array hero?=ber
  void giveArray ()
  {
    // Serial.println("Give Array()");
    PORTD = B00001000; // DataPin HIGH 8
    delay (EinleseZeit);
    PORTD = B00111000; // ShStPin und StorePin HIGH, Reihe 8 Ausgeben 56
    delay (EinleseZeit);
    PORTD = B00000000; // LOW 0
    for (int a = 1; a < MaxSpalte; a++)
    {
      EinlesenR (a); // Rot einlesen Reihe 1-7
      EinlesenG (a); // Gruen einlesen Reihe 1-7
      PORTD = B00110000; // Ausgeben und Linie wechseln Reihe 1-7
      delay (EinleseZeit);
      PORTD = B00000000; // Zurueck auf LOW setzten
      temp = a + 1;
    }
    EinlesenR (temp); // Rot einlesen Reihe 8
    EinlesenG (temp); // Gruen einlesen Reihe 8
  }

  void EinlesenR (int x)
  {
    for (int n = 2; n <= MaxZeile; n += 2)
    { // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
      digitalWrite (ShiftPinR, LOW);
      // Serial.println("EinlesenR(), Auslesen vom 10 x 18 Array ");
      digitalWrite (DataPinR, darray[x][n]); //Auslesen vom 10 x 18 Array
      digitalWrite (ShiftPinR, HIGH);
    }
  }

  void EinlesenG (int y)
  {
    for (int z = 1; z < MaxZeile; z += 2)
    { // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
      digitalWrite (ShiftPinR, LOW);
      // Serial.println("EinlesenG(), Auslesen vom 10 x 18 Array ");
      //  Serial.println(darray[y][z]);
      digitalWrite (DataPinR, darray[y][z]); //Auslesen vom 10 x 18 Array
      digitalWrite (ShiftPinR, HIGH);
    }
  }

  void loop ()
  {
    protothread1 (&pt1);
    protothread2 (&pt2);
    protothread3 (&pt3);
  } 
