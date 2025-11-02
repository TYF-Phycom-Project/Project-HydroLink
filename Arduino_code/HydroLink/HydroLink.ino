#include <LiquidCrystal_I2C.h>

//LCD variables
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte light_c[8] = { 
    B00000,
    B01110, 
    B11111, 
    B11111, 
    B01110, 
    B00100, 
    B01110,  
    B00000 };

byte water_c[8] = {
    B00000,
    B00100,
    B00100, 
    B01110, 
    B11111, 
    B01110, 
    B00100,   
    B00000 };

int light_status = 0;
int water_status = 0;

//Light variables
const int light = 3;
const int light2 = 4;
const int light_button = 2;

int led_state = LOW;
int last_button_state = HIGH;
int button_state = HIGH;

unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 50;


//Water variables
const int waterSensor = A0;
const int waterPump_Relay = 5;

int water_level = 0;
int min_level = 300;

void setup() {
  Serial.begin(9600);

  pinMode(waterSensor, INPUT);
  pinMode(light_button, INPUT_PULLUP);

  pinMode(light, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(waterPump_Relay, OUTPUT);

  lcd.init();           
  lcd.backlight();
  lcd.clear();
}

void loop() {

  //-------------------------LIGHT CONTROL----------------------------------
  int button_read = digitalRead(light_button); //Read the button : 0 or 1
    
  if (button_read != last_button_state) { //check is the button_read changed
    last_debounce_time = millis(); //set last time the button got push to current time im millisecond (millis() = return millisecond since arduino started)
  }

  if ((millis() - last_debounce_time) > debounce_delay) { //check if since last time the button push is more than the delay
    if (button_read != button_state) { //check if the current button read is not equal to and lastest button read 
      button_state = button_read; //set lastest button read to current button read
      
      if (button_state == LOW) { //check if the lastest button read is LOW (its pushed)
        led_state = !led_state; //change light state to opposite of light state (LOW to HIGH / HIGH to LOW)
        digitalWrite(light, led_state); 
        digitalWrite(light2, led_state);

        if (led_state == LOW){
          light_status = 0;
        }else{
          light_status = 1;
        }
      }
    }
  }

  last_button_state = button_read; //set last_button_state to current button read
  //----------------------------------------------------------------------------

  //-------------------------WATER CONTROL--------------------------------------
  int water_level = analogRead(waterSensor);//Read water sensor value
  Serial.println((water_level/100) * 100);

  if((water_level/100) * 100 < min_level){//check if current water level below the minimum level
    digitalWrite(waterPump_Relay, LOW);//Turn on the water pump
    water_status = 1;
  }
  else{//if current water level above the minimum level
    digitalWrite(waterPump_Relay, HIGH);//Turn off the water pump
    water_status = 0;
  }
  //------------------------------------------------------------------------------

  //-------------------------LCD CONTROL------------------------------------------
  LCD_command(light_status, water_status);
  //------------------------------------------------------------------------------
}

void LCD_command(int light_status, int water_status){
  if(water_status == 0){
    lcd.createChar(1, water_c); 
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.print("WATER: FILLED");

  }
  else{
    lcd.createChar(1, water_c); 
    lcd.setCursor(0, 0);
    lcd.write(byte(1));
    lcd.setCursor(2, 0);
    lcd.print("WATER: REFILL...");
  }

  if(light_status == 0){
    lcd.createChar(2, light_c); 
    lcd.setCursor(0, 1);
    lcd.write(byte(2));
    lcd.setCursor(2, 1);
    lcd.print("LIGHT: OFF.");
  }
  else{
    lcd.createChar(2, light_c); 
    lcd.setCursor(0, 1);
    lcd.write(byte(2));
    lcd.setCursor(2, 1);
    lcd.print("LIGHT: ON. ");
  }
}



