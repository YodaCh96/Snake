/*
Name:    SnakeV2.ino
Created:  5/17/2017 10:23:11 AM
Author: Ioannis Christodoulakis

*/

#include "pt.h"
#include <avr/wdt.h>

#define DataPinR 7                                  //Data Pin des 16Bit Schieberegisters
#define ShiftPinR 6                                 //Shift Pin des 16Bit Schieberegisters
#define MaxZeile 16                                 //Anzahl Zeilen der Anzeige einstellen
#define MaxSpalte 8                                 //Anzahl Spalten der Anzeige einstellen
#define EinleseZeit 0.00002                         //Zeitveroegerung damit SR reagieren kann.
#define buttonTop A0
#define buttonBot A2
#define buttonRight A1
#define buttonLeft A3

int temp;

int random1;
int random2;

int darray[10][18];
int darraycp[10][18];

//Variabeln für die Pins der Variabeln

int hightnumber = 0;
int widhtnumber = 0;

//Zähler
int count = 0;
int counter = 0;

//Variabeln für die Score-Ausgabe
int gamescore = 0;
int firstpart = 0;
int secondpart = 0;

//Variabeln welche das Signal der Buttons überprüfen
int buttonTpress = 0;
int buttonBpress = 0;
int buttonLpress = 0;
int buttonRpress = 0;

//Button welcher als letztes gedrückt wurde
int lastpressed = 4;

//Konstanten für die Richtung der Schlange
int const left = 3;
int const right = 4;
int const top = 1;
int const bot = 2;

//Boolean welcher überprüft ob das Spiel vorbei ist
bool gameover = false;

//Verschiedene Bools um Werte innerhalb des Arrays zu finden
bool gefunden = true;
bool foundNr1 = false;
bool foundLast = false;
static struct pt pt1;
static struct pt pt2;

void setup() {


  //Anfangs Position und Länge der Schlange
  darray[5][10] = 1;
  darray[5][8] = 1;
  darraycp[5][10] = 1;
  darraycp[5][8] = 2;
  darray[7][10] = 2;
  darraycp[7][10] = 2000;

  //Pins mit einem Button werden gezeichnet als Input.
  pinMode(buttonTop, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(buttonBot, INPUT);
  DDRD = B11111100;

  giveArray();

  PT_INIT(&pt1);
  PT_INIT(&pt2);

}
static int protothread1(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    //PT_WAIT_UNTIL(pt, function_returns_true());
    buttonpress();
  }
  PT_END(pt);
}
static int protothread2(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    //PT_WAIT_UNTIL(pt, function_returns_true());
    looping();
  }
  PT_END(pt);
}
void looping() {
  if (gameover == false) {
    //Falls der Button nach oben gedrückt wurde
    if (buttonTpress > 500 && lastpressed != top)
    {
      goTop();
      buttonTpress = 0;

    }
    //Falls der Button nach unten gedrückt wurde
    else if (buttonBpress > 500 && lastpressed != bot)
    {
      goBot();
      buttonBpress = 0;
    }
    //Falls der Button nach links gedrückt wurde
    else if (buttonLpress > 500 && lastpressed != left)
    {
      goLeft();
      buttonLpress = 0;

    }
    //Falls der Button nach rechts gedrückt wurde
    else if (buttonRpress > 500 && lastpressed != right)
    {
      goRight();
      buttonRpress = 0;
    }
    else {

    }

    if (gameOver == false) {
      //Die Schlange geht alle 0,5 Sekunden ein LED weiter falls die Richtung nicht geändert wird
      switch (lastpressed) {
      case top:
        goTop();
        break;
      case bot:
        goBot();
        break;
      case left:
        goLeft();
        break;
      case right:
        goRight();
        break;
      default:
        break;

      }
    }
  }
  //Überprüft ob sich ein Teil der Schlange am Rand befindet
  for (int i = 0; i < 18; i++) {
    if (darray[0][i] == 1) {
      gameOver();
    }
  }
  for (int i = 0; i < 10; i++) {
    if (darray[i][0] == 1) {
      gameOver();
    }
  }
  for (int i = 0; i < 10; i++) {
    if (darray[i][17] == 1) {
      gameOver();
    }
  }
  for (int i = 0; i < 18; i++) {
    if (darray[9][i] == 1) {
      gameOver();
    }
  }
  if (gameover == false) {
    for (int i = 1; i < 9; i++) {
      for (int a = 1; a < 17; a++) {
        //Überprüft ob ein Pickup(2) schon im Array vorhanden ist
        if (darray[i][a] == 2 && darraycp[i][a] == 2000 && a % 2 != 0) {
          gefunden = true;
        }
        else {
          gefunden = false;
          //Zwei Random Zahlen für das Array werden gemacht, an welcher Stelle dann ein Pickup erscheint
          randomZahl();
        }

      }
    }
  }
  if (gameover == false) {
    giveArray();
  }
}
void buttonpress() {

  //Signal der Buttons wird überprüft
  buttonTpress = analogRead(buttonTop);
  buttonBpress = analogRead(buttonBot);
  buttonLpress = analogRead(buttonLeft);
  buttonRpress = analogRead(buttonRight);
}
void loop() {
  protothread1(&pt1);
  protothread1(&pt2);
  
}
//Bewegt sich nach oben
void goTop() {
  if (lastpressed != bot) {
    for (int i = 1; i < 9; i++) {
      for (int a = 2; a < 9; a = a + 2) {
        //Zählt die Länge der Schlange
        if (darraycp[i][a] != 2000 && darraycp[i][a] != 0) {

          count++;
          counter++;
        }
      }
    }
    for (int i = 1; i < 9; i++) {
      for (int a = 2; a < 9; a = a + 2) {
        //Sucht nach dem letzten Stück der Schlange
        if (darraycp[i][a] == count) {
          darraycp[i][a] = 3000;
          foundLast = true;


        }
        //Sucht nach dem ersten Stück der Schlange
        else if (darraycp[i][a] == 1) {
          //Überprüft ob ein PickUp vor der Schlange liegt
          if (darraycp[i - 1][a - 1] == 2000) {
            darraycp[i - 1][a] = 500;
            darraycp[i - 1][a - 1] == 0;
            foundNr1 = true;
            gamescore++;

            for (int q = 1; q < 9; i++) {
              for (int r = 2; r < 9; r = r + 2) {
                if (darraycp[q][r] == 3000) {
                  darraycp[q][r] = count + 1;
                }
              }
            }
          }
          //Überprüft ob ein Teil der Schlange vor einem liegt
          else if (darraycp[i - 1][a] == 1) {
            gameOver();
            return;
          }
          //Falls nichts vor einem liegt
          else {
            darraycp[i - 1][a] = 500;
            foundNr1 = true;
            for (int q = 1; q < 9; q++) {
              for (int r = 2; r < 9; r = r + 2) {
                if (darraycp[q][r] == 3000) {

                  darraycp[q][r] = 0;
                }
              }
            }
          }
        }

      }
    }
    if (foundNr1 && foundLast) {
      //bewegt die Schlange um eins in die angegebene Richtung
      for (int b = 1; b < counter - 1; b++) {
        for (int p = 1; p < 9; p++) {

          for (int k = 2; k < 9; k = k + 2) {

            if (darraycp[p][k] == count--) {
              darraycp[p][k] = count;
              count--;
              if (darraycp[p - 1][k] = 500) {
                darraycp[p - 1][k] = 1;
                count = 0;
                counter = 0;
                foundNr1 = false;
                foundLast = false;
                for (int z = 1; z < 9; z++) {
                  for (int p = 1; p < 17; p++) {
                    //Kopiert das cp Array in das richtige Array
                    if (darraycp[z][p] > 0 && darraycp[z][p] < 2000) {
                      darray[z][p] = 1;
                    }
                    else if (darraycp[z][p] = 2000) {
                      darray[z][p] = 2;
                    }
                  }
                }
              }
            }

          }
        }

      }
    }

  }

  lastpressed = 1;
}


//bewegt sich nach unten
void goBot() {

  if (lastpressed != top) {
    for (int i = 1; i < 9; i++) {
      for (int a = 2; a < 9; a = a + 2) {
        if (darraycp[i][a] != 2000 && darraycp[i][a] != 0) {
          count++;
          counter++;
        }
      }
    }
    for (int i = 1; i < 9; i++) {
      for (int a = 2; a < 9; a = a + 2) {
        if (darraycp[i][a] == count) {
          darraycp[i][a] = 3000;
          foundLast = true;

        }
        else if (darraycp[i][a] == 1) {

          if (darraycp[i + 1][a - 1] == 2000) {
            darraycp[i + 1][a] = 500;
            darraycp[i + 1][a - 1] == 0;
            foundNr1 = true;
            gamescore++;

            for (int q = 1; q < 9; i++) {
              for (int r = 2; r < 9; r = r + 2) {
                if (darraycp[q][r] == 3000) {
                  darraycp[q][r] = count + 1;
                }
              }
            }
          }
          else if (darraycp[i + 1][a] == 1) {
            gameOver();
            return;
          }
          else {
            darraycp[i + 1][a] = 500;
            foundNr1 = true;
            for (int q = 1; q < 9; q++) {
              for (int r = 2; r < 9; r = r + 2) {
                if (darraycp[q][r] == 3000) {

                  darraycp[q][r] = 0;
                }
              }
            }
          }
        }

      }
      if (foundNr1 && foundLast) {
        for (int b = 1; b < counter - 1; b++) {
          for (int p = 1; i < 9; i++) {

            for (int k = 1; k < 9; k = k + 2) {

              if (darraycp[i][k] == count--) {
                darraycp[i][k] = count;
                count--;
                if (darraycp[i + 1][k] = 500) {
                  darraycp[i + 1][k] = 1;
                  count = 0;
                  counter = 0;
                  foundNr1 = false;
                  foundLast = false;

                  for (int z = 1; z < 9; z++) {
                    for (int p = 1; p < 17; p++)
                    {
                      if (darraycp[z][p] > 0 && darraycp[z][p] < 2000) {
                        darray[z][p] = 1;
                      }
                      else if (darraycp[z][p] = 2000) {
                        darray[z][p] = 2;
                      }
                    }
                  }
                }
              }

            }
          }

        }
      }

    }
  }
  lastpressed = 2;
}

//Bewegt sich nach links
void goLeft() {

  if (lastpressed != right) {
    for (int i = 1; i < 9; i++) {
      for (int a = 1; a < 9; a++) {
        if (darraycp[i][a] != 2000 && darraycp[i][a] != 0) {
          count++;
          counter++;
        }
      }
    }
    for (int i = 1; i < 9; i++) {
      for (int a = 2; a < 9; a = a + 2) {
        if (darraycp[i][a] == count) {
          darraycp[i][a] = 3000;
          foundLast = true;

        }
        else if (darraycp[i][a] == 1) {

          if (darraycp[i][a - 1] == 2000) {
            darraycp[i][a - 2] = 500;
            darraycp[i][a - 1] == 0;
            foundNr1 = true;
            gamescore++;

            for (int q = 1; q < 9; i++) {
              for (int r = 2; r < 9; r = r + 2) {
                if (darraycp[q][r] == 3000) {
                  darraycp[q][r] = count + 1;
                }
              }
            }
          }
          else if (darraycp[i][a - 2] == 1) {
            gameOver();
            return;
          }
          else {
            darraycp[i][a - 1] = 500;
            foundNr1 = true;
            for (int q = 1; q < 9; q++) {
              for (int r = 2; r < 9; r = r + 2) {
                if (darraycp[q][r] == 3000) {

                  darraycp[q][r] = 0;
                }
              }
            }
          }
        }

      }
    }
    if (foundNr1 && foundLast) {
      for (int b = 1; b < counter - 1; b++) {
        for (int p = 1; p < 9; p++) {

          for (int k = 2; k < 9; k = k + 2) {

            if (darraycp[p][k] == count--) {
              darraycp[p][k] = count;
              count--;
              if (darraycp[p][k - 1] = 500) {
                darraycp[p][k - 1] = 1;
                count = 0;
                counter = 0;
                foundNr1 = false;
                foundLast = false;

                for (int z = 1; z < 9; z++) {
                  for (int p = 1; p < 17; p++)
                  {
                    if (darraycp[z][p] > 0 && darraycp[z][p] < 2000) {
                      darray[z][p] = 1;
                    }
                    else if (darraycp[z][p] = 2000) {
                      darray[z][p] = 2;
                    }
                  }
                }
              }
            }

          }
        }

      }
    }

    lastpressed = 3;
  }
}
//Bewegt sich nach rechts
void goRight() {

  if (lastpressed != left) {
    for (int i = 1; i < 9; i++) {
      for (int a = 1; a < 9; a++) {
        if (darraycp[i][a] != 2000 && darraycp[i][a] != 0) {
          count++;
          counter++;
        }
      }
    }
    for (int i = 1; i < 9; i++) {
      for (int a = 2; a < 9; a = a + 2) {
        if (darraycp[i][a] == count) {
          darraycp[i][a] = 3000;
          foundLast = true;

        }
        else if (darraycp[i][a] == 1) {

          if (darraycp[i][a + 1] == 2000) {
            darraycp[i][a + 2] = 500;
            darraycp[i][a + 1] == 0;
            foundNr1 = true;
            gamescore++;

            for (int q = 1; q < 9; i++) {
              for (int r = 2; r < 9; r = r + 2) {
                if (darraycp[q][r] == 3000) {
                  darraycp[q][r] = count + 1;
                }
              }
            }
          }
          else if (darraycp[i][a + 2] == 1) {
            gameOver();
            return;
          }
          else {
            darraycp[i][a + 1] = 500;
            foundNr1 = true;
            for (int q = 1; q < 9; q++) {
              for (int r = 2; r < 9; r = r + 2) {
                if (darraycp[q][r] == 3000) {

                  darraycp[q][r] = 0;
                }
              }
            }
          }
        }

      }
    }
    if (foundNr1 && foundLast) {
      for (int b = 1; b < counter - 1; b++) {
        for (int p = 1; p < 9; p++) {

          for (int k = 1; k < 9; k = k + 2) {

            if (darraycp[p][k] == count--) {
              darraycp[p][k] = count;
              count--;
              if (darraycp[p][k + 1] = 500) {
                darraycp[p][k + 1] = 1;
                count = 0;
                counter = 0;
                foundNr1 = false;
                foundLast = false;

                for (int z = 1; z < 9; z++) {
                  for (int t = 1; t < 17; t++)
                  {
                    if (darraycp[z][t] > 0 && darraycp[z][t] < 2000) {
                      darray[z][t] = 1;
                    }
                    if (darraycp[z][t] == 2000) {
                      darray[z][t] = 2;
                    }
                  }
                }
              }
            }

          }
        }

      }
    }

  }

  lastpressed = 4;


}

//erstellt zwei RandomZahlen
void randomZahl() {
  random1 = random(1, 9);
  random2 = random(1, 17);
  PickUp(random1, random2);

}
//Setzt das PickUp
void PickUp(int random_zahl_1, int random_zahl_2) {
  //Falls an dieser Stelle sich ein Teil der Schlange befindet
  if (darray[random_zahl_1][random_zahl_2] == 1) {
    randomZahl();
  }
  else {
    darray[random_zahl_1][random_zahl_2] = 2;
    darraycp[random_zahl_1][random_zahl_2] = 2000;
    gefunden = true;
  }
}


/*
void score() {
  if (gamescore == 0) {

  }
  //Spaltet den Score auf
  firstpart = gamescore / 10;
  secondpart = gamescore % 10;
  for (int i = 1; i < 9; i++) {
    for (int a = 1; a < 17; a++) {
      //Setzt beide Array's Komplett auf Null
      darray[i][a] = 0;
      darraycp[i][a] = 0;
    }
  }
  scoreausgabe(firstpart, secondpart);


}

//Resetet den Arduino
void softwareReset(uint8_t prescaller) {
  // start watchdog with the provided prescaller

  wdt_enable(prescaller);
  // wait for the prescaller time to expire

  // without sending the reset signal by using

  // the wdt_reset() method

  while (1) {}
}

//Wird ausgeführt falls das Spiel vorbei ist
void gameOver() {
  gameover = true;
  score();
  giveArray();
  do {
    //Falls ein Knopf gedrückt wird
    if (buttonTpress > 500) {
      softwareReset(WDTO_60MS);
    }
    else if (buttonBpress > 500) {
      softwareReset(WDTO_60MS);
    }
    else if (buttonLpress > 500) {
      softwareReset(WDTO_60MS);
    }
    else if (buttonRpress > 500) {
      softwareReset(WDTO_60MS);
    }
  } while (true);

}




void scoreausgabe(int first, int second) {
  switch (first) {
  case 0:
    //10er-Stelle: gibt eine 0 aus
    darray[2][4] = 1;
    darray[2][6] = 1;
    darray[3][2] = 1;
    darray[3][8] = 1;
    darray[4][8] = 1;
    darray[4][2] = 1;
    darray[5][2] = 1;
    darray[5][8] = 1;
    darray[6][2] = 1;
    darray[6][8] = 1;
    darray[7][4] = 1;
    darray[7][6] = 1;
    break;
  case 1:
    //10er-Stelle: gibt eine 1 aus
    darray[2][6] = 1;
    darray[3][4] = 1;
    darray[3][6] = 1;
    darray[4][6] = 1;
    darray[5][6] = 1;
    darray[6][6] = 1;
    darray[7][6] = 1;
    break;
  case 2:
    //10er-Stelle: gibt eine 2 aus
    darray[2][4] = 1;
    darray[2][6] = 1;
    darray[3][8] = 1;
    darray[3][2] = 1;
    darray[4][8] = 1;
    darray[5][6] = 1;
    darray[6][4] = 1;
    darray[7][2] = 1;
    darray[7][4] = 1;
    darray[7][6] = 1;
    darray[7][8] = 1;
    break;

  case 3:
    //10er-Stelle: gibt eine 3 aus
    darray[2][2] = 1;
    darray[2][4] = 1;
    darray[2][6] = 1;
    darray[3][6] = 1;
    darray[4][6] = 1;
    darray[4][4] = 1;
    darray[4][2] = 1;
    darray[5][6] = 1;
    darray[6][6] = 1;
    darray[7][6] = 1;
    darray[7][4] = 1;
    darray[7][2] = 1;
    break;
  case 4:
    //10er-Stelle: gibt eine 4 aus
    darray[2][6] = 1;
    darray[3][4] = 1;
    darray[3][6] = 1;
    darray[4][2] = 1;
    darray[4][6] = 1;
    darray[5][2] = 1;
    darray[5][4] = 1;
    darray[5][6] = 1;
    darray[6][6] = 1;
    darray[7][6] = 1;
    break;
  case 5:
    //10er-Stelle: gibt eine 5 aus
    darray[2][2] = 1;
    darray[2][4] = 1;
    darray[2][6] = 1;
    darray[2][8] = 1;
    darray[3][2] = 1;
    darray[4][4] = 1;
    darray[5][6] = 1;
    darray[6][8] = 1;
    darray[7][2] = 1;
    darray[7][4] = 1;
    darray[7][6] = 1;
    break;
  case 6:
    //10er-Stelle: gibt eine 6 aus
    darray[2][2] = 1;
    darray[2][4] = 1;
    darray[2][6] = 1;
    darray[3][2] = 1;
    darray[4][2] = 1;
    darray[5][2] = 1;
    darray[5][4] = 1;
    darray[5][6] = 1;
    darray[6][2] = 1;
    darray[6][6] = 1;
    darray[7][2] = 1;
    darray[7][4] = 1;
    darray[7][6] = 1;
    break;
  case 7:
    //10er-Stelle: gibt eine 7 aus
    darray[2][4] = 1;
    darray[2][2] = 1;
    darray[2][6] = 1;
    darray[2][8] = 1;
    darray[3][8] = 1;
    darray[4][6] = 1;
    darray[5][6] = 1;
    darray[6][4] = 1;
    darray[7][4] = 1;
    break;
  case 8:
    //10er-Stelle: gibt eine 8 aus
    darray[2][4] = 1;
    darray[2][6] = 1;
    darray[3][2] = 1;
    darray[3][8] = 1;
    darray[4][4] = 1;
    darray[4][6] = 1;
    darray[5][2] = 1;
    darray[5][8] = 1;
    darray[6][2] = 1;
    darray[6][8] = 1;
    darray[7][4] = 1;
    darray[7][6] = 1;
    break;
  case 9:
    //10er-Stelle: gibt eine 9 aus
    darray[2][4] = 1;
    darray[2][6] = 1;
    darray[3][2] = 1;
    darray[3][8] = 1;
    darray[4][4] = 1;
    darray[4][6] = 1;
    darray[4][8] = 1;
    darray[5][8] = 1;
    darray[6][8] = 1;
    darray[6][2] = 1;
    darray[7][4] = 1;
    darray[7][6] = 1;
    break;
  }
  switch (second) {
  case 0:
    //1er-Stelle: gibt eine 0 aus
    darray[2][12] = 1;
    darray[2][14] = 1;
    darray[3][10] = 1;
    darray[3][16] = 1;
    darray[4][16] = 1;
    darray[4][10] = 1;
    darray[5][10] = 1;
    darray[5][16] = 1;
    darray[6][10] = 1;
    darray[6][16] = 1;
    darray[7][12] = 1;
    darray[7][14] = 1;
    break;
  case 1:
    //1er-Stelle: gibt eine 1 aus
    darray[2][14] = 1;
    darray[3][12] = 1;
    darray[3][14] = 1;
    darray[4][14] = 1;
    darray[5][14] = 1;
    darray[6][14] = 1;
    darray[7][14] = 1;
    break;
  case 2:
    //1er-Stelle: gibt eine 2 aus
    darray[2][12] = 1;
    darray[2][14] = 1;
    darray[3][16] = 1;
    darray[3][10] = 1;
    darray[4][16] = 1;
    darray[5][14] = 1;
    darray[6][12] = 1;
    darray[7][10] = 1;
    darray[7][12] = 1;
    darray[7][14] = 1;
    darray[7][16] = 1;
    break;

  case 3:
    //1er-Stelle: gibt eine 3 aus
    darray[2][10] = 1;
    darray[2][12] = 1;
    darray[2][14] = 1;
    darray[3][14] = 1;
    darray[4][14] = 1;
    darray[4][12] = 1;
    darray[4][10] = 1;
    darray[5][14] = 1;
    darray[6][14] = 1;
    darray[7][14] = 1;
    darray[7][12] = 1;
    darray[7][10] = 1;
    break;
  case 4:
    //1er-Stelle: gibt eine 4 aus
    darray[2][14] = 1;
    darray[3][12] = 1;
    darray[3][14] = 1;
    darray[4][10] = 1;
    darray[4][14] = 1;
    darray[5][10] = 1;
    darray[5][12] = 1;
    darray[5][14] = 1;
    darray[6][14] = 1;
    darray[7][14] = 1;
    break;
  case 5:
    //1er-Stelle: gibt eine 5 aus
    darray[2][10] = 1;
    darray[2][12] = 1;
    darray[2][14] = 1;
    darray[2][16] = 1;
    darray[3][10] = 1;
    darray[4][12] = 1;
    darray[5][14] = 1;
    darray[6][16] = 1;
    darray[7][10] = 1;
    darray[7][12] = 1;
    darray[7][14] = 1;
    break;
  case 6:
    //1er-Stelle: gibt eine 6 aus
    darray[2][10] = 1;
    darray[2][12] = 1;
    darray[2][14] = 1;
    darray[3][10] = 1;
    darray[4][10] = 1;
    darray[5][10] = 1;
    darray[5][12] = 1;
    darray[5][14] = 1;
    darray[6][10] = 1;
    darray[6][14] = 1;
    darray[7][10] = 1;
    darray[7][12] = 1;
    darray[7][14] = 1;
    break;
  case 7:
    //1er-Stelle: gibt eine 7 aus
    darray[2][12] = 1;
    darray[2][10] = 1;
    darray[2][14] = 1;
    darray[2][16] = 1;
    darray[3][16] = 1;
    darray[4][14] = 1;
    darray[5][14] = 1;
    darray[6][12] = 1;
    darray[7][12] = 1;
    break;
  case 8:
    //1er-Stelle: gibt eine 8 aus
    darray[2][12] = 1;
    darray[2][14] = 1;
    darray[3][10] = 1;
    darray[3][16] = 1;
    darray[4][12] = 1;
    darray[4][14] = 1;
    darray[5][10] = 1;
    darray[5][16] = 1;
    darray[6][10] = 1;
    darray[6][16] = 1;
    darray[7][12] = 1;
    darray[7][16] = 1;
    break;
  case 9:
    //1er-Stelle: gibt eine 9 aus
    darray[2][12] = 1;
    darray[2][14] = 1;
    darray[3][10] = 1;
    darray[3][16] = 1;
    darray[4][12] = 1;
    darray[4][14] = 1;
    darray[4][16] = 1;
    darray[5][16] = 1;
    darray[6][16] = 1;
    darray[6][10] = 1;
    darray[7][12] = 1;
    darray[7][14] = 1;
    break;
  }

*/

}
//Gibt das Array herüber
void giveArray() {
  PORTD = B00001000;        // DataPin HIGH
  delay(EinleseZeit);
  PORTD = B00111000;        // ShStPin und StorePin HIGH, Reihe 8 Ausgeben
  delay(EinleseZeit);
  PORTD = B00000000;        // LOW
  for(int a=1; a<MaxSpalte; a++){
    EinlesenR(a);           // Rot einlesen Reihe 1-7
    EinlesenG(a);           // Gruen einlesen Reihe 1-7
    PORTD = B00110000;      // Ausgeben und Linie wechseln Reihe 1-7
    delay(EinleseZeit);
    PORTD = B00000000;     // Zurueck auf LOW setzten
    temp = a+1;
  }
  EinlesenR(temp);          // Rot einlesen Reihe 8
  EinlesenG(temp);          // Gruen einlesen Reihe 8
}

void EinlesenR(int x){
  for (int n=1; n<MaxZeile; n+=2){                 // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, darray[x][n]);
    digitalWrite(ShiftPinR, HIGH);
  }
}

void EinlesenG(int y){
  for (int z=2; z<=MaxZeile; z+=2){                 // For schleife zum Setzten einer Reihe und das Ausgeben dieser Reihe
    digitalWrite(ShiftPinR, LOW);
    digitalWrite(DataPinR, darray[y][z]);
    digitalWrite(ShiftPinR, HIGH);
  }
}

