/**
 * CONSTANTS
 */
// LIGHTS
unsigned int LIGHTS_START = 0;
unsigned int LIGHTS_END = 11;
unsigned int BUTTON_ONE = 13;
unsigned int BUTTON_TWO = 12;
// TIMES
unsigned int TEST_MODE = 1000;
unsigned int MENU_MODE = 500;
unsigned int EASY_MODE = 75;
unsigned int MEDIUM_MODE = 50;
unsigned int HARD_MODE = 25;
unsigned int INSANE_MODE = 15;

// VARIABLES
unsigned long lightSpeed = MENU_MODE;
boolean buttonOnePressed = false;
boolean buttonTwoPressed = false;
unsigned long previousMillis = 0;        // will store last time LED was updated
int previousLight = -1;
int currentLight = LIGHTS_START;
boolean forwards = true;
int score1 = 0;
int score2 = 0;
boolean playing = false;

void setup() {
  // put your setup code here, to run once:
  Serial.println("setup: start");
  for (int i = LIGHTS_START; i < LIGHTS_END; i++) {
    Serial.print("setup: pinMode(");
    Serial.print(i);
    Serial.print(", OUTPUT)\n");
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON_ONE, INPUT);
  Serial.println("setup: end");
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
  if (!playing) {
    menuLoop();
  } else {
    gameLoop();
  }
}

void menuLoop() {
  int buttonState = digitalRead(BUTTON_ONE);
  if (buttonState == HIGH) {
    playing = true;
    lightSpeed = MENU_MODE;
  }
  loopLights(!playing);
}

void gameLoop() {
  if (buttonState == HIGH) {
    buttonOnePressed = !buttonOnePressed;
  }
  loopLights(!buttonOnePressed);
}

void loopLights(bool toLoop) {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (toLoop && currentMillis - previousMillis >= lightSpeed) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    if (previousLight != -1) {
      digitalWrite(previousLight, LOW);
    }
    digitalWrite(currentLight, HIGH);
    previousLight = currentLight;
    if (currentLight == LIGHTS_START) {
      forwards = true; 
    } else if (currentLight == LIGHTS_END - 1) {
      forwards = false;
    }
    if (forwards) {
      currentLight += 1;
    } else {
      currentLight -= 1;
    }
  }
}

