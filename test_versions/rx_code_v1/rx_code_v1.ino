#define R1 2
#define R2 7
#define R3 A7
#define R4 5
#define R5 A0
#define R6 A6
#define R7 A1
#define R8 A4
//Columns
#define C1 6
#define C2 A2
#define C3 A3
#define C4 3
#define C5 A5
#define C6 4
#define C7 8
#define C8 9

void setup() {
   pinMode(R1, OUTPUT);
   pinMode(R2, OUTPUT);
   pinMode(R3, OUTPUT);
   pinMode(R4, OUTPUT);
   pinMode(R5, OUTPUT);
   pinMode(R6, OUTPUT);
   pinMode(R7, OUTPUT);
   pinMode(R8, OUTPUT);
   pinMode(C1, OUTPUT);
   pinMode(C2, OUTPUT);
   pinMode(C3, OUTPUT);
   pinMode(C4, OUTPUT);
   pinMode(C5, OUTPUT);
   pinMode(C6, OUTPUT);
   pinMode(C7, OUTPUT);
   pinMode(C8, OUTPUT);
// Turning all the LEDs off at the start of the sketch
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
  digitalWrite(R3,HIGH);
  digitalWrite(R4,HIGH);
  digitalWrite(R5,HIGH);
  digitalWrite(R6,HIGH);
  digitalWrite(R7,HIGH);
  digitalWrite(R8,HIGH);
  digitalWrite(C1,LOW);
  digitalWrite(C2,LOW);
  digitalWrite(C3,LOW);
  digitalWrite(C4,LOW);
  digitalWrite(C5,LOW);
  digitalWrite(C6,LOW);
  digitalWrite(C7,LOW);
  digitalWrite(C8,LOW);
}


void selectRow(int row){
  if (row==1) digitalWrite(R1,LOW); else digitalWrite(R1,HIGH);
  if (row==2) digitalWrite(R2,LOW); else digitalWrite(R2,HIGH);
  if (row==3) digitalWrite(R3,LOW); else digitalWrite(R3,HIGH);
  if (row==4) digitalWrite(R4,LOW); else digitalWrite(R4,HIGH);
  if (row==5) digitalWrite(R5,LOW); else digitalWrite(R5,HIGH);
  if (row==6) digitalWrite(R6,LOW); else digitalWrite(R6,HIGH);
  if (row==7) digitalWrite(R7,LOW); else digitalWrite(R7,HIGH);
  if (row==8) digitalWrite(R8,LOW); else digitalWrite(R8,HIGH);
}

void selectColumn(int column){
  if (column==1) digitalWrite(C1,HIGH); else digitalWrite(C1,LOW);
  if (column==2) digitalWrite(C2,HIGH); else digitalWrite(C2,LOW);
  if (column==3) digitalWrite(C3,HIGH); else digitalWrite(C3,LOW);
  if (column==4) digitalWrite(C4,HIGH); else digitalWrite(C4,LOW);
  if (column==5) digitalWrite(C5,HIGH); else digitalWrite(C5,LOW);
  if (column==6) digitalWrite(C6,HIGH); else digitalWrite(C6,LOW);
  if (column==7) digitalWrite(C7,HIGH); else digitalWrite(C7,LOW);
  if (column==8) digitalWrite(C8,HIGH); else digitalWrite(C8,LOW);
}

void turnOnAll(){
  for (int i=1;i<9;i++) {
    for (int j=1;j<9;j++){
      selectRow(i);
      selectColumn(j); 
      delay(0);
    }
  }
}

void setM(){
  
  selectRow(1);
  selectRow(2);
  selectRow(3);
  selectRow(4);
  selectColumn(1);
  
  

  
}


void loop() {
  turnOnAll();
  //delay(300);
}
