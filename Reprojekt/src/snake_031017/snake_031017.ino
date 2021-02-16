//#include <gfxfont.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_LEDBackpack.h>
#include "pt.h"
#include "Matrix.h"



// Pinbelegung der Buttons fC<r die Steuerung
#define PIN_BUTTON_RIGHT A1
#define PIN_BUTTON_LEFT A3
#define PIN_BUTTON_TOP A0
#define PIN_BUTTON_BOTTOM A2

// LC$nge und Breite des Spielfelds
#define MATRIX_HORIZONTAL_LENGTH 8
#define MATRIX_VERTICAL_LENGTH 8

#define DIRECTION_TOP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_BOTTOM 2
#define DIRECTION_LEFT 3

#define LED_ON 1
#define LED_OFF 0

#define LED_GREEN 2
#define LED_RED 1

// PrC<ft ob der Wert eine Schlange reprC$sentiert (im Spielfeld)
#define SNAKE(a) (a > 0)

int field[MATRIX_HORIZONTAL_LENGTH][MATRIX_VERTICAL_LENGTH] = { 0 };

int snakeHeadX;
int snakeHeadY;

static struct pt pt1, pt2, pt3;



int direction = DIRECTION_TOP;
int snakeLength = 3;
unsigned long prevTime = 0;

unsigned long delayTime = 400;
unsigned long buttonCheckTime = 50;
static unsigned long timestampExc = 2;

int fruitX, fruitY;
unsigned long fruitPrevTime = 0;
unsigned long fruitBlinkTime = 200;
int fruitLed = LED_ON;

boolean gameOverShown = false;
boolean gameOver = false;


//Adafruit_8x8matrix matrix = Adafruit_8x8matrix();  
//Anstatt Adafruit wurde hier eine Hardware-Eigenentwicklung verwendet
//Aus diesem Grunde wurde das File Matrix.h überschrieben
Matrix matrix = Matrix ();



// Setup - wird einmal am Start des Programms aufgerufen
void setup ()
{
  Serial.begin (9600);

  // LED Matrix initialisieren
  randomSeed (analogRead (4));

  // Spiel initialisieren, Anfangsposition der Schlange zufC$llig setzen
  snakeHeadX = random (0, MATRIX_HORIZONTAL_LENGTH);
  snakeHeadY = random (0, MATRIX_VERTICAL_LENGTH);
  field[snakeHeadX][snakeHeadY] = snakeLength;

  // Erste Frucht platzieren
  makeFruit ();

  PT_INIT (&pt1);
  PT_INIT (&pt2);
  PT_INIT (&pt3);

}


static int protothread1 (struct pt *pt)
{
  static unsigned long timestamp = 0;
  PT_BEGIN (pt);
  while (1)
    {
      timestamp = millis ();
      PT_WAIT_UNTIL (pt, millis () - timestamp > timestampExc);
      matrix.writeDisplay ();
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
      PT_WAIT_UNTIL (pt, millis () - timestamp > delayTime);
      loop2 ();
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
      PT_WAIT_UNTIL (pt, millis () - timestamp > buttonCheckTime);
      checkButtons ();
    }
  PT_END (pt);
}



// PrC<ft ob der Button, der an buttonPin anliegt gedrC<ckt ( > 500) wurde
boolean buttonClicked (int buttonPin)
{
  return analogRead (buttonPin) > 500;
}

// Wird stC$ndig aufgerufen, so lange das Programm lC$uft
void loop2 ()
{

  // ggf. Richtung der Schlange C$ndern
  //checkButtons();


  // Game Loop verzC6gern, damit das Game nicht sofort vorrC<ber ist...
  unsigned long currentTime = millis ();
  if (currentTime - prevTime >= delayTime)
    {
      //Ermittelt wie sich die Schlange bewegt
      nextstep ();

      prevTime = currentTime;
    }

  // Spielfeld auf Matrix zeichnen
  draw ();
}

// PrC<ft die Richtungstasten und setzt die Bewegungsrichtung der Schlange
// + Validierung um zu prC<fen dass Schlange nicht "in sich" hereinlC$uft
void checkButtons ()
{
  int currentDirection = direction;
  if (buttonClicked (PIN_BUTTON_LEFT) && currentDirection != DIRECTION_RIGHT)
    {
      direction = DIRECTION_LEFT;
    }
  else if (buttonClicked (PIN_BUTTON_RIGHT)
	   && currentDirection != DIRECTION_LEFT)
    {
      direction = DIRECTION_RIGHT;
    }
  else if (buttonClicked (PIN_BUTTON_TOP)
	   && currentDirection != DIRECTION_BOTTOM)
    {
      direction = DIRECTION_TOP;
    }
  else if (buttonClicked (PIN_BUTTON_BOTTOM)
	   && currentDirection != DIRECTION_TOP)
    {
      direction = DIRECTION_BOTTOM;
    }
}

// Zeichnet das Spielfeld (Schlange + Frucht) auf der LED Matrix
void draw ()
{

  matrix.clear ();


  // Wenn das Spiel noch lC$uft...
  if (!gameOver)
    {
      for (int x = 0; x < MATRIX_HORIZONTAL_LENGTH; x++)
	{
	  for (int y = 0; y < MATRIX_VERTICAL_LENGTH; y++)
	    {
	      matrix.drawPixel (x, y, SNAKE (field[x][y]), LED_RED);
	    }
	}

      drawFruit ();     
    }


  // Wenn Game Over...Alles rot
  else
    {
      matrix.clear ();


      for (int x = 0; x < MATRIX_HORIZONTAL_LENGTH; x++)
	{
	  for (int y = 0; y < MATRIX_VERTICAL_LENGTH; y++)
	    {

	      //matrix.setTextColor(LED_RED);
	      matrix.drawPixel (x, y, true, LED_RED);
	    }
	}

    }
}




// Zeichnet die Frucht auf die Matrix und implementiert das Blinken des Pixels
void drawFruit ()
{
  if (inPlayField (fruitX, fruitY))
    {
      //matrix.setTextColor(LED_GREEN);
      matrix.drawPixel (fruitX, fruitY, true, LED_GREEN);

    }
}

// Gibt zurC<ck ob die angegebenen Koordinaten im Spielfeld liegen
boolean inPlayField (int x, int y)
{
  return (x >= 0) && (x < MATRIX_HORIZONTAL_LENGTH) && (y >= 0)
    && (y < MATRIX_VERTICAL_LENGTH);
}

// Schlange verschieben, ggf. verlC$ngern und feststellen ob Spiel vorbei ist
void nextstep ()
{
  int newX = snakeHeadX;
  int newY = snakeHeadY;

  // Basierend auf derzeitiger Richtung die Schlange verschieben
  switch (direction)
    {
    case DIRECTION_TOP:
      //newY--;
      newX--;
      break;
    case DIRECTION_RIGHT:
      //newX++;
      newY++;
      break;
    case DIRECTION_BOTTOM:
      //newY++;
      newX++;
      break;
    case DIRECTION_LEFT:
      //newX--;
      newY--;
      break;
    }

  // Wenn neue Position C<ber die Grenzen der Matrix hinausragt, neue Position auf die andere Seite setzen
  if (newY >= MATRIX_VERTICAL_LENGTH)
    newY = 0;
  else if (newY < 0)
    newY = MATRIX_VERTICAL_LENGTH - 1;

  if (newX >= MATRIX_HORIZONTAL_LENGTH)
    newX = 0;
  else if (newX < 0)
    newX = MATRIX_HORIZONTAL_LENGTH - 1;

  // Wenn der Kopf ein Teil der Schlange berC<hrt, war's das...
  if (isPartOfSnake (newX, newY))
    {
      gameOver = true;
      delay (3000);
      return;
    }


  // Wenn eine Frucht eingesammelt wird, Schlange erweitern und neue Frucht erstellen
  if ((newX == fruitX) && (newY == fruitY))
    {


      Serial.println ("Hit here");
      snakeLength++;
      makeFruit ();
    }

  // Spielfeld anpassen sodass Schlange verschoben wird
  for (int x = 0; x < MATRIX_HORIZONTAL_LENGTH; x++)
    {
      for (int y = 0; y < MATRIX_VERTICAL_LENGTH; y++)
	{
	  int value = field[x][y];
	  if (SNAKE (value))
	    field[x][y] = value - 1;
	}
    }

  snakeHeadX = newX;
  snakeHeadY = newY;
  field[newX][newY] = snakeLength;
}

// Erstellt eine Frucht auf einer zufC$lligen Position innerhalb des Spielfelds
void makeFruit ()
{
  int x, y = 0;

  // ZufC$llige Position so generieren, dass sie nicht auf der Schlange liegt
  do
    {
      x = random (0, MATRIX_HORIZONTAL_LENGTH);
      y = random (0, MATRIX_VERTICAL_LENGTH);
    }
  while (isPartOfSnake (x, y));

  fruitX = x;
  fruitY = y;
}

// PrC<ft ob die C<bergebenen Koordinaten (der Punkt) ein Teil der Schlange ist
boolean isPartOfSnake (int x, int y)
{
  return SNAKE (field[x][y]);
}

void loop ()
{
  protothread1 (&pt1);
  protothread2 (&pt2);
  protothread3 (&pt3);
}

//Für Debug-Zwecke
void fieldArray2SerialMonitor (int amount)
{
  //Field 8 * 8 ausgeben
  for (int z = 0; z < 8; z++)
    {
      Serial.println ("");
      for (int t = 0; t < 8; t++)
	{
	  Serial.print (field[z][t]);
	}
    }

  Serial.println ("");
}


