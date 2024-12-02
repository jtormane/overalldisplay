// SIK LOGO

byte S1[8]={
  0b00001,
  0b00011,
  0b00011,
  0b00111,
  0b00111,
  0b01111,
  0b11111,
  0b00001
};

byte S2[8]={
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11110,
  0b11100
};

byte S3[8]={
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00111,
  0b00011,
  0b00001
};

byte S4[8]={
  0b11000,
  0b11000,
  0b10000,
  0b10000,
  0b00000,
  0b11000,
  0b10000,
  0b00000
}; 


// C++ code
//
#include <LiquidCrystal.h>

const int rs = 2,
        en = 3,
        d4 = 6,
        d5 = 7,
        d6 = 8,
      d7 = 9,
      nappi = 25  ;
int buttonState = 0,
  lastbuttonState = 0,
  buttonPressCount = 0;
float promillet = 0;

int minuutit = 0, sekunnit = 0; 
unsigned long previousMS = 0;




LiquidCrystal lcd(rs,en,d4,d5,d6,d7);


void setup()
{
  pinMode(nappi, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(2,1);
  lcd.print("Vesilinjalla");
  lcd.setCursor(0,0);
  lcd.print("Juodut juomat: 0");
}

void loop()
{
  buttonState = digitalRead(nappi);
  
  if (buttonState == LOW && lastbuttonState == HIGH){
   buttonPressCount++;
   Serial.print(buttonPressCount);
   String juomat = "Juodut juomat:"+String(buttonPressCount);
   delay(100);
   lcd.clear();
   lcd.print(juomat);
   
   promillet = buttonPressCount * 14 /(65*0.68);
   String kanni = "Promilleni:"+String(promillet); 
   lcd.setCursor(0,1);
   lcd.print(kanni);
  }
lastbuttonState = buttonState;
unsigned long currentMS = millis();
  
  if (currentMS - previousMS >= 60000){
    previousMS = currentMS;
    minuutit++;
    promillet -=0.0025;
    if(promillet<0){
      promillet = 0;
    }
   
    lcd.setCursor(0, 1);
    lcd.print("Promilleni: ");
    lcd.print(promillet, 2); // 2 desimaalia
   
  }

}
