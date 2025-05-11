// ----------LIBRARY----------
#include <LiquidCrystal.h> 

// ----------DEFINITIONS----------
const int buttonPin1 = 3, buttonPin2 = 4, green = 6, buzzer = 5, red = 2; //button1 = IN button2 = OUT
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
int digit1, digit2, digit3, digit4, digit5, digit6, digit7;
bool correct = false; //IF THE KEY IS IN SEQUENCE
bool pressed1 = false;
bool pressed2 = false;
int playerscore = 0;
int highscore = 0;
int displayTime = 2000;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ----------SETUP----------
void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

// ----------LOOP----------
void loop() {
  mainMenu();
  numberGame();
}

// ----------GAME----------
void numberGame() {
  playerscore = 0;
  
  displayTime = 2000;

  while (true) {    //keeps the code running until broken or the player gets a wrong answer
    
    //resets values when starting a new round
    correct = false;
    pressed1 = false;
    pressed2 = false;

    generateSequence();

    displaySequence();

    increaseDifficulty();

    checkTheKey();

    checkPlayerInput();

    if ((correct && pressed1) || (!correct && pressed2)) {  
      playerRight(); //if the player presses the correct button
    } else {
      playerWrong(); //if the player presses the wrong button
      break; 
    }
  }
}

// ----------FUNCTIONS----------

void mainMenu() { //starting screen + display highscore
  lcd.clear();
  lcd.print("Press to Start");
  lcd.setCursor(0, 1);
  lcd.print("Record:");
  lcd.print(highscore);
  while (digitalRead(buttonPin1) == HIGH && digitalRead(buttonPin2) == HIGH) {} //waits on this screen until input is received
  delay(200);
}

void generateSequence() { // generates random 7 digit sequence
  digit1 = random(0, 10);
  digit2 = random(0, 10);
  digit3 = random(0, 10);
  digit4 = random(0, 10);
  digit5 = random(0, 10);
  digit6 = random(0, 10);
  digit7 = random(0, 10);
}

void displaySequence() { //displays generated sequence
  lcd.clear();
  lcd.print("Remember:");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(digit1);
  lcd.print(digit2);
  lcd.print(digit3);
  lcd.print(digit4);
  lcd.print(digit5);
  lcd.print(digit6);
  lcd.print(digit7);
}

void increaseDifficulty() {  
  delay(displayTime); 
  Serial.println(displayTime); //doesnt have to be here, its just to see how fast the display time gets throughout the game
}

void checkTheKey() { 
  int key = random(0, 10); //generates random KEY
  lcd.clear();
  lcd.print("Digit: ");
  lcd.setCursor(0, 1);
  lcd.print(key); //displays KEY

  //verifies if KEY is contained in the sequence (correct = true or false depending..)
  correct = (key == digit1 || key == digit2 || key == digit3 ||key == digit4 || key == digit5 || key == digit6 || key == digit7);
}

void checkPlayerInput() {
  while (true) { //waits indefinitely until a button is pressed
    if (digitalRead(buttonPin1) == LOW) { // the button is a pull up
      pressed1 = true; 
      break; //breaks while
    } else if (digitalRead(buttonPin2) == LOW) {
      pressed2 = true;
      break; //breaks while
    }
  }
}

void playerRight() { //if player is right
  playerscore++; //adds to score (+1)
  
  if (displayTime > 400) { //decreases display time by 100ms for each right answer to increase difficulty throughout the game, caps at 400ms
    displayTime -= 100;
  }

  lcd.clear();
  digitalWrite(green, HIGH); //LED lights green
  lcd.print("Correct!"); 
  delay(2000);
  digitalWrite(green, LOW);
}

void playerWrong() { //if player is wrong
  lcd.clear();
  digitalWrite(red, HIGH); //LED lights red
  errorNoise(); //buzzer noise function
  lcd.print("Wrong!");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(playerscore); //displays your score
  delay(1500);
  digitalWrite(red, LOW);

  if (playerscore > highscore) { //checks if the current playerscore beat the previous highscore, and replaces it if necessary
    highscore = playerscore;
  }
}

void errorNoise(){ 
  tone(buzzer, 50, 150); //activates buzzer, with frequency of 50 and duration of 150ms
  delay(200);
  tone(buzzer, 50, 150);
}
