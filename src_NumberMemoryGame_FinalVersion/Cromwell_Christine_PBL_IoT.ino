// ----------LIBRARY----------
#include <LiquidCrystal.h> // Controls LCD display; allows to print messages, moving cursors, clear the screen and others.

// ----------DEFINITIONS----------
// Pin assignments for buttons, LEDs, buzzer, and LCD
const int buttonPin1 = 3, buttonPin2 = 4, green = 6, buzzer = 5, red = 2; //button1 = IN button2 = OUT
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12; //LCD pins


// Variables for the 7 digit sequence
int digit1, digit2, digit3, digit4, digit5, digit6, digit7;

//Game state tracking
bool correct = false;    // If the KEY is inside the number sequence
bool pressed1 = false;  // If button 1 was pressed
bool pressed2 = false; // If button 2 was pressed
int playerscore = 0;  // Current score
int highscore = 0;   // Highest score recorded so far
int displayTime = 2000;  // Time to show the number sequence in ms

//LCD setup with the defined pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ----------SETUP----------
void setup() {
  //Set pin modes
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);

  //Initialize LCD Module
  lcd.begin(16, 2); // 16 columns, 2 rows
  Serial.begin(9600); // Starting serial communication for debugging
  randomSeed(analogRead(0)); // Seed random number generator using analog input
}

// ----------LOOP----------
void loop() {
  mainMenu(); //Shows the welcome menu and wait for the player to press a button to start
  numberGame(); //Start the number memory game 
}

// ----------GAME----------

// Main game LOGIC
void numberGame() {
  playerscore = 0;
  
  displayTime = 2000; // Reset display time for each new game

  while (true) {    // keeps the code running until broken or the player gets a wrong answer
    
    //resets values when starting a new round
    correct = false;
    pressed1 = false;
    pressed2 = false;

    generateSequence();      // Generate 7 random digits 

    displaySequence();      // Show the sequence to the player

    increaseDifficulty();  // Shorten display time as score increases

    checkTheKey();        // Show a digit and ask if it is in the sequence

    checkPlayerInput();  // Wait for the player's button input

    //Knowing or determining if the player's answer was correct

    if ((correct && pressed1) || (!correct && pressed2)) {  
      playerRight();   // if the player presses the correct button, anwered correctly
    } else {
      playerWrong(); // if the player presses the wrong button, answered incorrectly
      break;        // End the game loop
    }
  }
}

// ----------FUNCTIONS----------

void mainMenu() { //starting screen + display highscore + waits for input to begin
  lcd.clear();
  lcd.print("Press to Start");
  lcd.setCursor(0, 1);
  lcd.print("Record:");
  lcd.print(highscore);
  while (digitalRead(buttonPin1) == HIGH && digitalRead(buttonPin2) == HIGH) {} //waits on this screen until input is received
  delay(200); //This line gives the circuit 200 ms to settle before continuing, ensuring only one button press is registered.

}

void generateSequence() { // generates random 7 digit sequence
  digit1 = random(0, 10); //generates integers from: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 + min (inclusive) to max (exclusive)
  digit2 = random(0, 10);
  digit3 = random(0, 10);
  digit4 = random(0, 10);
  digit5 = random(0, 10);
  digit6 = random(0, 10);
  digit7 = random(0, 10);
}

void displaySequence() { //displays generated sequence on the LCD
  lcd.clear();
  lcd.print("Remember:"); // writes the text "Remember:" on the first line of the LCD.
  delay(1000);
  lcd.setCursor(0, 1); //sets the cursor position on the LCD screen +  ensures that anything printed next (like the 7-digit number) appears neatly on the second line of the display, under the "Remember:" label.
  lcd.print(digit1);
  lcd.print(digit2);
  lcd.print(digit3);
  lcd.print(digit4);
  lcd.print(digit5);
  lcd.print(digit6);
  lcd.print(digit7);
}

void increaseDifficulty() {  //reducing display time per round
  delay(displayTime); //Time for player to memorize sequence
  Serial.println(displayTime); //doesnt have to be here, its just to see how fast the display time gets throughout the game + Serial.println(displayTime); // Prints the current display time to the Serial Monitor for debugging. Helps to track how the game's difficulty changes after each correct answer

}

void checkTheKey() { //Chooses a random digit (key) and checks if it's in the sequence
  int key = random(0, 10); //generates random KEY/ digit between 0-9
  lcd.clear();
  lcd.print("Digit: ");
  lcd.setCursor(0, 1);
  lcd.print(key); //displays KEY

  //verifies if KEY is contained in the sequence (correct = true or false depending..)
  correct = (key == digit1 || key == digit2 || key == digit3 ||key == digit4 || key == digit5 || key == digit6 || key == digit7);
}

void checkPlayerInput() { 
  while (true) { //waits indefinitely until a button is pressed
    if (digitalRead(buttonPin1) == LOW) { // the button is a pull up + // "IN" button
      pressed1 = true; 
      break; //breaks while
    } else if (digitalRead(buttonPin2) == LOW) { // "OUT" button
      pressed2 = true;
      break; //breaks while
    }
  }
}

void playerRight() { //if player is right
  playerscore++; //adds to score (+1)
  
  if (displayTime > 400) { //decreases display time by 100ms for each right answer to increase difficulty throughout the game, caps at 400ms + Speeds up the game by reducing display time, minimum 400ms
    displayTime -= 100;
  }

 // Component Feedback: green LED and message
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
  delay(1500); // Pauses for 1500ms to allow the player to read the "Wrong!" message and their score before the screen changes
  digitalWrite(red, LOW);

  if (playerscore > highscore) { //checks if the current playerscore beat the previous highscore, and replaces it if necessary
    highscore = playerscore;
  }
}

void errorNoise(){ 
  tone(buzzer, 50, 150); //activates buzzer twice for wrong answer, with frequency of 50 and duration of 150ms
  delay(200);
  tone(buzzer, 50, 150);
}
