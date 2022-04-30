/*  RW1990 Key duplicator
 *  Programm is written by Mautoz mikemautos@gmail.com
 *  Tested on Arduino Uno and Arduino Nano
 *  
 *  Pins:  
 *    Digital 10 pin is connected to 5V by 2 kOm resistor (or 2x1kOm)
 *    Gnd pin to red wire (External) on the reader
 *    Digital 10 pin to green wire (Internal) on the reader
 *    
 *  Mautoz Tech YouTube Channel: https://www.youtube.com/c/mautoztech
*/

#include <OneWire.h>
#define pin 10
OneWire  ds(pin); 
byte saved[8];
byte data[8];
int input,input2,i;

void setup() {
  Serial.begin(9600);
  Serial.println("Waiting for a key");
}

void loop() {
  delay(1000);
  
  ds.reset();
  delay(50);
  ds.write(0x33);
  
  ds.read_bytes(data, 8);

  if (data[0]!=0xFF || data[1]!=0xFF || data[2]!=0xFF || data[3]!=0xFF || data[4]!=0xFF || data[5]!=0xFF || data[6]!=0xFF || data[7] != 0xFF){
    Serial.print("Key value is ");
    for( i = 0; i < 8; i++) {
      Serial.print(data[i], HEX);
      if (i != 7) Serial.print(":");
    }
    Serial.println();
    Serial.println("Do you want to save it or rewrite it?");
    Serial.println("Commands: save, write, write [value], end");
    readCommand();
  }
}

bool readCommand(){
  while(1){
      switch(Serial.available()){
      
        case 4:
        
          if (i==0 & Serial.read()!=101) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (i==1 & Serial.read()!=110) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (i==2 & Serial.read()!=100) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (i==3 & Serial.read()!=10) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);

          Serial.println("Waiting for a key");
          return 0;
          break;
        case 5:
          if (Serial.read()!=115){
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=97) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=118) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=101) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=10) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          for (i=0; i<8;i++){
            saved[i]=data[i];
          }
          Serial.println("Key value saved: ");
          for( i = 0; i < 8; i++) {
            Serial.print(saved[i], HEX);
            if (i != 7) Serial.print(":");
          }
          Serial.println();
          Serial.println("Waiting for a new key");
          return 0;
          break;
        case 6:
          if (Serial.read()!=119){
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=114) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=105) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=116) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=101) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=10) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          writeSavedValue();
          return 0;
          break;
        case 30:
          if (Serial.read()!=119){
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=114) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=105) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=116) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=101) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          if (Serial.read()!=32) {
            while (Serial.available()) Serial.read();
            Serial.println("Incorrect input");
            break;
          }
          delay(10);
          for (i=0;i<8;i++){
            input=Serial.read();
            if (input>47 & input<58){
              input=(input-48);
            }
            else if (input>96 & input<103){
              input=(input-97)+10;
            }
            else if (input>64 & input<71){
              input=(input-65)+10;
            }
            else{
              while (Serial.available()) Serial.read();
              break;
            }
            delay(10);
            input2=Serial.read();
            if (input2>47 & input2<58){
              input=input*16+input2-48;
              saved[i]=input;
            }
            else if (input2>96 & input2<103){
              input=input*16+(input2-97)+10;
              Serial.print(input);
              saved[i]=input;
            }
            else if (input2>64 & input2<71){
              input=input*16+(input2-65)+10;
              saved[i]=input;
            }
            else{
              while (Serial.available()) Serial.read();
              break;
            }
            delay(10);
            input2=Serial.read();
            if (input2!=32 & input2!=58 & input2!=10){
              while (Serial.available()) Serial.read();
              break;
            }
            delay(10);
          }
          writeSavedValue();
          return 0;
          break;
        default:
          while (Serial.available()) Serial.read();
          break;
       } 
       delay(100);
       
    }  
  
}

void writeSavedValue(){
  ds.skip();ds.reset();ds.write(0x33);
  ds.skip();
  ds.reset();
  ds.write(0xD1);
  digitalWrite(pin, LOW); pinMode(pin, OUTPUT); delayMicroseconds(60);
  pinMode(pin, INPUT); digitalWrite(pin, HIGH); delay(10);
  Serial.println("Writing iButton ID:");
  ds.skip();
  ds.reset();
  ds.write(0xD5);
  for( i = 0; i < 8; i++) {
    writeByte(saved[i]);
    Serial.print(saved[i], HEX);
    if (i != 7) Serial.print(":");
  }
  Serial.println();
  ds.reset();
  ds.write(0xD1);
  digitalWrite(pin, LOW); pinMode(pin, OUTPUT); delayMicroseconds(10);
  pinMode(pin, INPUT); digitalWrite(pin, HIGH); delay(10); 
  Serial.println("Writing done successfully");
  delay(1000);
 
}
int writeByte(byte data){
  int data_bit;
  for(data_bit=0; data_bit<8; data_bit++){
    if (data & 1){
      digitalWrite(pin, LOW); pinMode(pin, OUTPUT);
      delayMicroseconds(60);
      pinMode(pin, INPUT); digitalWrite(pin, HIGH);
      delay(10);
    } else {
      digitalWrite(pin, LOW); pinMode(pin, OUTPUT);
      pinMode(pin, INPUT); digitalWrite(pin, HIGH);
      delay(10);
    }
    data = data >> 1;
  }
  return 0;
}
