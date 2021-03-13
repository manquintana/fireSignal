#define R1 A2
#define R2 A3
#define R3 A4
#define R4 A5

//Columns
#define C1 4
#define C2 5
#define C3 6
#define C4 7


void setup() {
   pinMode(R1, OUTPUT);
   pinMode(R2, OUTPUT);
   pinMode(R3, OUTPUT);
   pinMode(R4, OUTPUT);
   
   pinMode(C1, OUTPUT);
   pinMode(C2, OUTPUT);
   pinMode(C3, OUTPUT);
   pinMode(C4, OUTPUT);
  
// Turning all the LEDs off at the start of the sketch
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
  digitalWrite(R3,HIGH);
  digitalWrite(R4,HIGH);
  
  digitalWrite(C1,LOW);
  digitalWrite(C2,LOW);
  digitalWrite(C3,LOW);
  digitalWrite(C4,LOW);
  
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
  for (int i=1;i<5;i++) {
    for (int j=1;j<5;j++){
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
