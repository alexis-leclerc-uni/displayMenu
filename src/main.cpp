#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define outputA 6
#define outputB 7
#define inputSW 8
 
int aState;
int globalState = 0;
int aLastState;
int totalColumns = 16;
int totalRows = 2;
int counter = 1000001;
int positionY;
int positionX;
 
LiquidCrystal_I2C lcd(0x27, totalColumns, totalRows);

const char* menuItems[] = {"Corona", "50", "Labatt", "Bleu Dry",  NULL };
 
void menu(int counter);
void initMenu(const char* items[]);


void setup(){
  lcd.init();
  lcd.backlight(); // use to turn on and turn off LCD back light
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (inputSW, INPUT_PULLUP);
   
  Serial.begin (9600);
  aLastState = digitalRead(outputA);  

  initMenu(menuItems);

  menu(counter/2);
}
 
void loop() {
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   switch (globalState)
   {
   case 0:
   if (aState != aLastState){    
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) {
       counter ++;
     } else {
       counter --;
     }
    menu(counter/2);
   }
    if(!digitalRead(inputSW)){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Vous avez pris:");
      lcd.setCursor(0, 1);
      lcd.print(menuItems[((counter/2) % 4)]);
      globalState = 1;
    }
    break;
  case 1:
   if (aState != aLastState){    
    lcd.clear();
    initMenu(menuItems);
    globalState = 0;
   }
  
   
   default:
    break;
   }
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }

void menu(int counter){
  lcd.setCursor(positionX, positionY);
  lcd.print(" ");
  positionX = (counter%4) >= 2 ? 9 : 0;
  positionY = (counter % 2);
  lcd.setCursor(positionX, positionY);
  lcd.print(">");
}

void initMenu(const char* items[]){
  int nbItems;
  while(items[nbItems] != nullptr){
    nbItems++;
  }
  //Serial.println(sizeof(items));
  for(unsigned int i = 0; i <= (nbItems); i++){
    lcd.setCursor((i%4) >= 2 ? 10 : 1, (i % 2));
    lcd.print(items[i]);
  }
}