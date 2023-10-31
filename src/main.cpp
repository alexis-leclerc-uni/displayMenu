#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define outputA 6
#define outputB 7
 
int aState;
int aLastState;
int totalColumns = 16;
int totalRows = 2;
int counter = 1000001;
 
LiquidCrystal_I2C lcd(0x27, totalColumns, totalRows);

char menuItems[4][10] = {"Corona", "Biere", "Labatt", "Chepo"};
 
void menu(int counter);
void initMenu(char items[4][10]);


void setup(){
  lcd.init();
  lcd.backlight(); // use to turn on and turn off LCD back light
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (8, INPUT_PULLUP);
   
  Serial.begin (9600);
  aLastState = digitalRead(outputA);  

  initMenu(menuItems);

/*
  lcd.setCursor(1,0);
  lcd.print("Corona");
  lcd.setCursor(1,1);
  lcd.print("Biere");
  lcd.setCursor(10,0);
  lcd.print("Labatt");
  lcd.setCursor(10,1);
  lcd.print("Chepo");
*/
  menu(counter/2);
}
 
void loop() {
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){    
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) {
       counter ++;
     } else {
       counter --;
     }
   }
   menu(counter/2);
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }

void menu(int counter){
  lcd.setCursor(0, counter%2);
  lcd.print(">");
  lcd.setCursor(0, (counter)%2-1);
  lcd.print(" ");
}

void initMenu(char items[4][10]){
  //Serial.println(sizeof(items));
  for(unsigned int i = 0; i <= sizeof(items) + 1; i++){
    Serial.println(items[i]);
    Serial.print("i : ");
    Serial.println(i);
    Serial.println((i%4)>2 ? 10 : 1);
    Serial.println(i%2);
    lcd.setCursor((i%4) >= 2 ? 10 : 1, (i % 2));
    lcd.print(items[i]);
  }
}