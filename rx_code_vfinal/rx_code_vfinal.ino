#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



//Rows
#define R1 A2
#define R2 A3
#define R3 A4
#define R4 A5
//Columns
#define C1 4
#define C2 5
#define C3 6
#define C4 7

// RF24
#define CE_PIN 9
#define CSN_PIN 10
byte direccion[5] ={'m','a','n','u','1'};  //canal de tx-rx
RF24 radio(CE_PIN, CSN_PIN);
int datos[1];//vector con los datos recibido


void setup() {
  Serial.begin(9600);
  
  radio.begin(); //Inicializacion rf24l01
  radio.openReadingPipe(1, direccion);
  radio.startListening();
   
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
   
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  
// Turning all the LEDs off at the start of the sketch
  turnOnAll();
  
}

void selectRow(int row){
  if (row==1) digitalWrite(R1,LOW); else digitalWrite(R1,HIGH);
  if (row==2) digitalWrite(R2,LOW); else digitalWrite(R2,HIGH);
  if (row==3) digitalWrite(R3,LOW); else digitalWrite(R3,HIGH);
  if (row==4) digitalWrite(R4,LOW); else digitalWrite(R4,HIGH);
}

void selectColumn(int column){
  if (column==1) digitalWrite(C1,HIGH); else digitalWrite(C1,LOW);
  if (column==2) digitalWrite(C2,HIGH); else digitalWrite(C2,LOW);
  if (column==3) digitalWrite(C3,HIGH); else digitalWrite(C3,LOW);
  if (column==4) digitalWrite(C4,HIGH); else digitalWrite(C4,LOW);
}

void turnOnAll(){
  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);
  digitalWrite(R3,LOW);
  digitalWrite(R4,LOW);
  
  digitalWrite(C1,HIGH);
  digitalWrite(C2,HIGH);
  digitalWrite(C3,HIGH);
  digitalWrite(C4,HIGH);
}

void turnOffAll(int tiempo){
  Serial.print("START initial time:");
  Serial.println(tiempo);
  while (tiempo > 0){
    digitalWrite(R1,HIGH);
    digitalWrite(R2,HIGH);
    digitalWrite(R3,HIGH);
    digitalWrite(R4,HIGH);
    digitalWrite(C1,LOW);
    digitalWrite(C2,LOW);
    digitalWrite(C3,LOW);
    digitalWrite(C4,LOW);
    
    Serial.println(tiempo);
    tiempo= tiempo - 1;
    delay(1000);
  }
  turnOnAll();
}



void loop() {
  if (radio.available()){
    radio.read(datos,sizeof(datos));
    switch (datos[0]){
      case 0:
        Serial.println(datos[0]);
        turnOnAll();
        break;
      default:
        Serial.print("disparar: ");
        Serial.println(datos[0]);
        turnOffAll(datos[0]);
        break;
    }
  } 
  
  delay(100);
}
