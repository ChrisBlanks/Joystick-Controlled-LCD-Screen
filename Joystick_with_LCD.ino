#include <LiquidCrystal.h> //Allows access to LCD functions

//sensor pins for joystick
const int y_dir = 0;
const int x_dir = 1;
const int push = 8;

//Storage for pin readings
int push_state = 0; 
int x_pos = 0;
int y_pos = 0;

//LCD pins
const int rs = 2; //register select pin
const int en = 3; //enable pin
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;

//LCD object initialization
LiquidCrystal my_lcd(rs,en,d4,d5,d6,d7);

//Index of cursor
int cursor_index = 0;

//string variable
char lcd_string = "A"; //Arbitrary value selected

void setup() {
  Serial.begin(9600);
  my_lcd.begin(16,2); //16 columns and 2 rows initialized
  
  pinMode(push, INPUT_PULLUP); //internal pullup resistor 
  
  pinMode(x_dir,INPUT);
  pinMode(y_dir,INPUT);
  
  my_lcd.print("Hello, User."); //16 character string maximum
  delay(3000); //3 second delay to allow user to read initial message
  
  my_lcd.clear();
  my_lcd.cursor(); //initializes cursor 
}

void loop() {
  
  push_state = digitalRead(push);
  x_pos = analogRead(x_dir);
  y_pos = analogRead(y_dir);
  
//Outputs joystick data to serial monitor
monitor_joy(); 

/*  The potentiometers in the joystick are mapped
 *from 0 to 1023 (10 bits), so the conditional 
 *values in the If statements and While statements 
 *were selected in order to match the joystick 
 *movement with the LCD commands.
 */

//move cursor to the left
 if(x_pos <= 300 && cursor_index > 0){

  cursor_index = cursor_index - 1;
  my_lcd.setCursor(cursor_index,0);
  delay(100); //Slows down movement of cursor
  }

//move cursor to the right 
 if(x_pos >= 700 && cursor_index < 16){
  
  cursor_index = 1+ cursor_index;
  my_lcd.setCursor(cursor_index,0);
  delay(100);
  }
  
//push button clears screen & resets cursor index
 if(push_state == 0){
  
  my_lcd.clear();
  cursor_index = 0;
  }
  
// increments through Ascii characters
 while(y_pos <200){
  
  lcd_string = lcd_string + 1;
  my_lcd.print(lcd_string);
  my_lcd.setCursor(cursor_index,0);
  delay(500);
  if (analogRead(y_dir) >200){
    break;
    }
  }
  
// decrements through Ascii characters
 while(y_pos > 800){
  
  lcd_string = lcd_string - 1;
  my_lcd.print(lcd_string);
  my_lcd.setCursor(cursor_index,0);
  delay(500);
    if (analogRead(y_dir) <800){
    break;
    }
  }
}

void monitor_joy(void){
  
Serial.print("Switch:  ");
Serial.print(push_state);
Serial.print("\n");

Serial.print("X-axis:  ");
Serial.print(x_pos);
Serial.print("\n");

Serial.print("Y-axis:  ");
Serial.print(y_pos);
Serial.print("\n\n");
  }
