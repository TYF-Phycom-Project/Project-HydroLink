  #include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x27, 16, 2);

 //custom character
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

  const int light = 3;
  const int light2 = 4;

  int light_state = LOW;

  const int light_button = 2;
  int button_state = 0;

 void setup() {
  Serial.begin(9600);

  pinMode(light_button, INPUT);

  pinMode(light, OUTPUT);
  pinMode(light2, OUTPUT);

  lcd.init();
  lcd.backlight();
 }

 void loop() {

  button_state = digitalRead(light_button);

  waterLevel_input();
  light_command(button_state);

  LCD_command(light_status, water_status);
 
 }

 void waterLevel_input(){

  int level = 0;

  int level_input = analogRead(A0);

  //water level is above the set level
  if(level_input >= level){
    light_status = 1;
    water_status = 1;
  }
  //water level is below the set level
  else{
    //...some function for refill
    light_status = 0;
    water_status = 0;
  }

 }

 void refillWater(){
  //...
 }

 void light_command(int button){
   if(button == HIGH){
      if(led_state == HIGH){
        led_state = LOW;
        light_status = 1;
      }
      else{
        led_state = HIGH;
        light_status = 0;
      }
   }

   digitalWrite(light, led_state);
   digitalWrite(light2, led_state);
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
    lcd.print("LIGHT: OFF");
  }
  else{
    lcd.createChar(2, light_c); 
    lcd.setCursor(0, 1);
    lcd.write(byte(2));
    lcd.setCursor(2, 1);
    lcd.print("LIGHT: ON");
  }
 }



