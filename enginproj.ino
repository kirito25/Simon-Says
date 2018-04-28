
int button[] = {2, 3, 4, 5, 6}; //The five button input pins
int ledpin[] = {8, 9, 10, 11, 12};  // LED pins
int turn = 0;  // turn counter
int buttonstate = 0;  // button state checker
int randomArray[100]; //Intentionally long to store up to 100 inputs (if person get this far they need a life)
int inputArray[100]; 
const int failPin = 13;
int list[] = {294,311,262,494};
int buttonNote[] = {127,262,390,502,666};
int duration[] = {300,300,300,300,300};
char* color[]={"Blue", "Yellow", "Green", "Red", "Dark Blue"};

void setup()
{
  Serial.begin(9600);

  for(int x=0; x<5; x++)  
  {
    pinMode(ledpin[x], OUTPUT);
  }
 
  for(int x=0; x<5; x++)
  {
    pinMode(button[x], INPUT); 
    digitalWrite(button[x], HIGH);    
  }
  pinMode(failPin, OUTPUT);
  randomSeed(analogRead(0)); 
  Serial.println(int(sizeof(list))/2);
 }

void loop()
{  
  for (int y=0; y<=99; y++)
  {
    //function for generating the array to be matched by the player
    //flashes LEDS when correct also user testing they work
    for(int z = 0; z < 5; z++){
      digitalWrite(ledpin[z], HIGH);
      beepBoop(z);;
      noTone(7);
    }
   
    digitalWrite(ledpin[0], LOW);
    delay(100);
    digitalWrite(ledpin[1], LOW);
    delay(100);
    digitalWrite(ledpin[2], LOW);
    delay(100);
    digitalWrite(ledpin[3], LOW);
    delay(100);
    digitalWrite(ledpin[4], LOW);
    delay(100);
 
    for (int y=turn; y <= turn; y++)
    { //control by turn variable
      Serial.println(""); //Some serial output to follow along
      Serial.print("Turn: ");
      Serial.print(y);
      Serial.println("");
      randomArray[y] = random(1, 6); //Assigning a random number (1-5) to the randomArray[y], y being the turn count
      for (int x=0; x <= turn; x++)
      {
        for(int y=0; y<5; y++)
        {
          if (randomArray[x] == 1 && ledpin[y] == 8) {
            digitalWrite(ledpin[y], HIGH);
            beepBoop(y);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }

          if (randomArray[x] == 2 && ledpin[y] == 9) {
            digitalWrite(ledpin[y], HIGH);
            beepBoop(y);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
 
          if (randomArray[x] == 3 && ledpin[y] == 10) {
            digitalWrite(ledpin[y], HIGH);
            beepBoop(y);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
          if (randomArray[x] == 4 && ledpin[y] == 11) {
            digitalWrite(ledpin[y], HIGH);
            beepBoop(y);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
	        if (randomArray[x] == 5 && ledpin[y] == 12) {  
            digitalWrite(ledpin[y], HIGH);
            beepBoop(y);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
        }
      }
    }
    input();
  }
}
void input() {  //user input and checking input against the generated array
  
  for (int x=0; x <= turn;) { //Statement controlled by turn count
    for(int y=0; y<5; y++) {
      buttonstate = digitalRead(button[y]);
      if (buttonstate == LOW && button[y] == 2) { //Checking for button push
        digitalWrite(ledpin[0], HIGH);
        beepBoop(y);
        delay(200);
        digitalWrite(ledpin[0], LOW);
        inputArray[x] = 1;
        delay(250);
        Serial.print(" ");
        Serial.print("Blue");
        if (inputArray[x] != randomArray[x]) { //onspot mistake checking
          fail();                              
        }                                      
        x++;
      }
      if (buttonstate == LOW && button[y] == 3) {
        digitalWrite(ledpin[1], HIGH);
        beepBoop(y);
        delay(200);
        digitalWrite(ledpin[1], LOW);
        inputArray[x] = 2;
        delay(250);
        Serial.print(" ");
        Serial.print("Yellow");
        if (inputArray[x] != randomArray[x]) {
          fail();
        }
        x++;
      }
      if (buttonstate == LOW && button[y] == 4) {
        digitalWrite(ledpin[2], HIGH);
        beepBoop(y);
        delay(200);
        digitalWrite(ledpin[2], LOW);
        inputArray[x] = 3;
        delay(250);
        Serial.print(" ");
        Serial.print("Green");
        if (inputArray[x] != randomArray[x]) {
          fail();
        }
        x++;
      }
      if (buttonstate == LOW && button[y] == 5) {
        digitalWrite(ledpin[3], HIGH);
        beepBoop(y);
        delay(200);
        digitalWrite(ledpin[3], LOW);
        inputArray[x] = 4;
        delay(250);
        Serial.print(" ");
        Serial.print("Red");
        if (inputArray[x] != randomArray[x])
        {
          fail();
        }
        x++;
      }
      if (buttonstate == LOW && button[y] == 6) {
         digitalWrite(ledpin[4], HIGH);
         beepBoop(y);
         delay(200);
         digitalWrite(ledpin[4], LOW);
         inputArray[x] = 5;
         delay(250);
         Serial.print(" ");
         Serial.print("Dark Blue");
         if (inputArray[x] != randomArray[x]) {
           fail();
         }
         x++;
       }
    }
  }
  delay(500);
  turn++; //Increments the turn count, also the last action before starting the output function over again
}

void fail() { //Function used if the player fails to match the sequence
  digitalWrite(failPin, HIGH);
  for(int x = 0; x < 1; x++){
    for(int i = 0; i < int(sizeof(list))/2; i++){
      // turn off tone function for pin 8:
      noTone(7);
      // play a note on pin 8 for 500 ms:
      tone(7, list[i], 0);
      delay(600);
    }
  }
  delay(100);
  digitalWrite(failPin, LOW);
  noTone(7);
  turn = -1; //Resets turn value so the game starts over without need for a reset button
}
void beepBoop(int y){ //Make sound according to LED
  tone(7, buttonNote[y], duration[y]);
  delay(200);
  noTone(7);
}
