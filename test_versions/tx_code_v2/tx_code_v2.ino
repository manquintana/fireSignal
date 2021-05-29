#include <ezButton.h>
#include <TM1637Display.h>


/* TM1637 Display */
TM1637Display display(2, 3);
const uint8_t OFF[] = {0, 0, 0, 0};

/* Buttons + Buzzer */
const int pBuzzer = 5;
ezButton buttonUp(6);
ezButton buttonDown(7);
ezButton buttonSend(8);
int count = 0;

void setup() {
  
  Serial.begin(9600);


  //TM1637
  display.setBrightness(4);
  display.setSegments(OFF);
  display.showNumberDec(count, true, 4, 0); 

  // set button debounce time to 50 milliseconds, EXCEPT SEND BUTTON!
  buttonUp.setDebounceTime(50); 
  buttonUp.setCountMode(COUNT_FALLING);
  buttonDown.setDebounceTime(50); 
  buttonDown.setCountMode(COUNT_FALLING);

  pinMode(pBuzzer, OUTPUT);
}


void calculateTime(){
  display.showNumberDec(count, true, 4, 0);   
}


void showValuesOnDisplay() {
  for(int i=count; i>0; i--) {
    display.showNumberDec(i, true, 4, 0);
    delay(1000);
  }
}



void loop() {
  
  buttonUp.loop();
  buttonDown.loop();
  buttonSend.loop();
  unsigned int positives = buttonUp.getCount();
  unsigned int negatives = buttonDown.getCount();

   // MODIFICAR ESTO CON : https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection
  
  if (buttonUp.getState() == 0){ //Si esta presionado sumar segundos
   if (count < 3541){
    delay(200);
    count = count + 1;
   }
  }
  if (buttonUp.isReleased()){
    count = count - 1;
  }
  calculateTime();
  

  if (buttonDown.getState() == 0){ //Si esta presionado restar segundos
   if (count > 0){
    count = count - 1; 
   }else{
    count = 0;
   }
   delay(200);
  }
  if (buttonDown.isReleased()){
    if (count != 0){
      count = count + 1;  
    }
  }
  Serial.println(count);    
  

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
    showValuesOnDisplay();
  }

  delay(50);
}
