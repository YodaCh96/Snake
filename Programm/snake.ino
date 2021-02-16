/*
 Name:    Snake.ino
 Created: 5/17/2017 10:23:11 AM
 Author:  Ioannis Christodoulakis
*/



int random1;
int random2;

int darray[10][18];
int darraycp[10][18];


int buttonTop = 8;
int buttonBot = 9;
int buttonRight = 10;
int buttonLeft = 11;
int hightnumber = 0;
int widhtnumber = 0;
int count = 0;
int counter = 0;

int gamescore = 0;
int firstpart = 0;
int secondpart = 0;

int buttonTpress = 0;
int buttonBpress = 0;
int buttonLpress = 0;
int buttonRpress = 0;
int lastpressed = 4;

int const left = 3;
int const right = 4;
int const top = 1;
int const bot = 2;

bool gameover = false;
bool gefunden = true;
bool foundNr1 = false;
bool foundLast = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(buttonTop, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(buttonBot, INPUT);

  darray[5][8] = 1;
  darray[5][10] = 1;
  darraycp[5][8] = 1;
  darraycp[5][10] = 2;

  randomZahl();

}

void loop() {
   digitalWrite(2,1);
  if (gameover == false) {
    for (int i = 1; i < 9; i++) {
      for (int a = 1; a < 17; a++) {
        if (darray[i][a] == 2 && darraycp[i][a] == 2000 && a % 2 != 0) {
          gefunden = true;
        }
        else {
          gefunden = false;
          randomZahl();
        }

      }
    }
  }
  buttonTpress = digitalRead(buttonTop);
  buttonBpress = digitalRead(buttonBot);
  buttonLpress = digitalRead(buttonLeft);
  buttonRpress = digitalRead(buttonRight);
  if (gameover == false) {
    if (buttonTpress == 1 && lastpressed != top)
    {
      goTop();
      buttonTpress = 0;

    }
    else if (buttonBpress == 1 && lastpressed != bot)
    {
      goBot();
      buttonBpress = 0;
    }
    else if (buttonLpress == 1 && lastpressed != left)
    {
      goLeft();
      buttonLpress = 0;

    }
    else if (buttonRpress == 1 && lastpressed != right)
    {
      goRight();
      buttonRpress = 0;
    }
    else {

    }

    if (gameOver == false) {
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

}

void goTop() {
  if (lastpressed != bot) {
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
          else if (darraycp[i - 1][a] == 1) {
            gameOver();
            return;
          }
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
                    for (int p = 1; p < 17; p++){
                    if (darraycp[z][p] > 0 && darraycp[z][p] < 2000) {
                        darray[z][p] = 1;
                      }
                      else if (darraycp[z][p] = 2000) {
                        darray[z][p] = 2;
                        delay(500);
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
                          delay(500);
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
                          delay(500);
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
                          delay(500);
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

void randomZahl() {
  random1 = random(1, 9);
  random2 = random(1, 17);
  PickUp(random1, random2);

}
void PickUp(int random_zahl_1, int random_zahl_2) {
  if (darray[random_zahl_1][random_zahl_2] == 1) {
    randomZahl();
  }
  else {
    darray[random_zahl_1][random_zahl_2] = 2;
    darraycp[random_zahl_1][random_zahl_2] = 2000;
    gefunden = true;
  }
}

void giveArray() {

}

void score() {
  if (gamescore == 0) {

  }
  firstpart = gamescore / 10;
  secondpart = gamescore % 10;
  for (int i = 1; i < 9; i++) {
    for (int a = 1; a < 17; a++) {
      darray[i][a] = 0;
      darraycp[i][a] = 0;
    }
  }
  scoreausgabe(firstpart, secondpart);

  
}
void gameOver() {
  gameover = true;
  score();

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

  
}
