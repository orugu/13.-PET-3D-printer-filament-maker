#include <stdio.h>
#include <string.h>
#include "ui_function.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED define
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1);

#define RXD 16
#define TXD 17
#define ENA 18

char selectmenu = 0;
int speed =400;
void display_status(void)
{
  //display maker start
  display.setCursor(0,0);
  display.println("Test");
  display.display();
  display.setCursor(0,8);
  display.println("LOWTEST");
  display.display();
  display.setCursor(32,40);
  display.print("speed: %d",speed);
  display.setCursor();
  
  
  //display maker end
  display.display();//endpoint
}

void setup() {
  //display_init(display);
  pinMode(18,OUTPUT);
  // Initialize serial
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  pinMode(TXD,OUTPUT);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  delay(10);


  delay(100);
}

void loop() {
  while(1)
  {
    selectmenu = Serial.read();
    if(selectmenu =='1')
    {
    digitalWrite(ENA,HIGH);
    }
    else if(selectmenu=='2')
    {
    digitalWrite(ENA,LOW);
    }
    // Serial 2 available
    else if(selectmenu=='3')
    {
      speed+= 50;
      display.clearDisplay();
    }
    else if(selectmenu=='4')
    {
      speed -=50;
      display.clearDisplay();
    }
    else if(selectmenu=='5')
    {
      speed +=10;
      display.clearDisplay();
    }
    else if(selectmenu=='6')
    {
      speed -=10;
      display.clearDisplay();
    }
    selectmenu = 0;
    Serial.println(speed);
    digitalWrite(TXD,HIGH);
    delayMicroseconds(speed);
    digitalWrite(TXD,LOW);
    delayMicroseconds(speed);
    display_status();
    

    
    
  }
}