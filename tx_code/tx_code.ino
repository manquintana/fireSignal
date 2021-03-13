#include <ezButton.h>

const int pBuzzer = 5;
ezButton buttonUp(6);
ezButton buttonDown(7);
ezButton buttonSend(8);

void setup() {
  
  Serial.begin(9600);

  // set button debounce time to 50 milliseconds, EXCEPT SEND BUTTON!
  buttonUp.setDebounceTime(50); 
  buttonUp.setCountMode(COUNT_FALLING);
  buttonDown.setDebounceTime(50); 
  buttonDown.setCountMode(COUNT_FALLING);

  pinMode(pBuzzer, OUTPUT);
}

void loop() {
  
  buttonUp.loop();
  buttonDown.loop();
  buttonSend.loop();
  unsigned int positives = buttonUp.getCount();
  unsigned int negatives = buttonDown.getCount();

  int buttonSendState = buttonSend.getState();
  Serial.println(buttonSendState);
  /*
  if (positives < negatives){
    buttonDown.resetCount();
    unsigned int count = 0;
 
    Serial.println(count);
  }else{
    unsigned int count = positives - negatives;
    Serial.println(count);
  }

  // BUZZER CONTROL
  if (buttonSend.isPressed()){
    Serial.println("Button pressed");
    
    for (int beeps = 0; beeps < 3; beeps++) {
      digitalWrite(pBuzzer, 150);
      delay(200);
      digitalWrite(pBuzzer, LOW);
      delay(800);
    }
    digitalWrite(pBuzzer, LOW);
  }
*/
  delay(100);
}
