  #include <LiquidCrystal_I2C.h>
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

 void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
 }

 void loop() {

  LCD_command(light_status, water_status);
 
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
    lcd.print("WATER: FILLED");
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



