#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <TM1637Display.h>

/* TM1637 Display */
TM1637Display display(4,3);
const uint8_t OFF[] = {0, 0, 0, 0};

/* Buttons + Buzzer */
int count = 0;
const int pBuzzer = 2;
const int pButtonUp = 8;
const int pButtonDown = 7;
const int pButtonSend = 5;

/*NRF24*/
#define CE_PIN 9
#define CSN_PIN 10
byte direccion[5] ={'m','a','n','u','1'}; //canal de tx-rx
RF24 radio(CE_PIN, CSN_PIN);
int datos[1];//vector con los datos a enviar

void setup() {
  radio.begin();
  radio.openWritingPipe(direccion);
  
  Serial.begin(9600);

  //TM1637
  display.setBrightness(10);
  display.setSegments(OFF);
  display.showNumberDecEx(0, 0, true, 2, 2);
  display.showNumberDecEx(0, 0x40, true, 2, 0);
  
  //Buttons
  pinMode(pButtonUp, INPUT);
  digitalWrite(pButtonUp, HIGH); // connect internal pull-up
  pinMode(pButtonDown, INPUT);
  digitalWrite(pButtonDown, HIGH);
  pinMode(pButtonSend, INPUT);
  digitalWrite(pButtonSend, HIGH);

}


void calculateTime() {
  int seconds = count;
  int minutes = 0;
  while (seconds > 59) {
    minutes++;
    seconds = seconds - 60;
  }
  //Serial.println("minutos:");
  //Serial.println(minutes);
  //Serial.println("segundos:");
  //Serial.println(seconds);

  display.showNumberDecEx(seconds, 0, true, 2, 2);
  display.showNumberDecEx(minutes, 0x40, true, 2, 0);
}

void startCountDown(){
  while(count > 0){
    count--;
    calculateTime();
    if (count == 0){
      digitalWrite(pBuzzer, 150);
      delay(800);
      digitalWrite(pBuzzer, LOW);
    }
    delay(1000);
  }
}

boolean buttonPressed(int pin)
{
  int button_pressed = !digitalRead(pin); // pin low -> pressed
  return button_pressed;
}


void loop() {

  if (buttonPressed(pButtonUp)) {
    if (count < 3541) {
      count = count + 1;
    }
    calculateTime();
  }

  if (buttonPressed(pButtonDown)) {
    if (count > 0) {
      count = count - 1;
    } else {
      count = 0;
    }
    calculateTime();
  }

  //Serial.println(count);

  // BUZZER CONTROL
  if (buttonPressed(pButtonSend)) {
    if (count != 0){              //Si hay tiempo seteado
      digitalWrite(pBuzzer, 150);
      delay(800);
      digitalWrite(pBuzzer, LOW);
      delay(3000);
      for (int beeps = 0; beeps < 3; beeps++) {
        digitalWrite(pBuzzer, 150);
        delay(200);
        digitalWrite(pBuzzer, LOW);
        delay(800);
      }
      digitalWrite(pBuzzer, LOW);
      
      
      //Envia numero de segundos para apagar la luz!
      datos[0]=count;
      bool ok = radio.write(datos, sizeof(datos));
      while (!ok){
        Serial.println("No se ha podido enviar. Reenviando...");
        ok = radio.write(datos, sizeof(datos));
        delay(200);
      }
      Serial.print("Datos enviados: ");
      Serial.println(datos[0]);
      startCountDown();
      
      
      
    }
    else{                         // Codigo de error si no hay tiempo seteado
      digitalWrite(pBuzzer, 150);
      delay(50);
      digitalWrite(pBuzzer, LOW);
      delay(50);
      digitalWrite(pBuzzer, 150);
      delay(50);
      digitalWrite(pBuzzer, LOW);
      delay(50);
    }
    
  }
  else{
    //Envia codigo 0 para prender la luz!
    datos[0]=0;
    bool ok = radio.write(datos, sizeof(datos));
    while (!ok){
      Serial.println("No se ha podido enviar. Reenviando...");
      ok = radio.write(datos, sizeof(datos));
      delay(200);
    }
    Serial.print("Datos enviados: ");
    Serial.println(datos[0]);
  }

  // sleep a moment before next iteration
  delay(120);

}
