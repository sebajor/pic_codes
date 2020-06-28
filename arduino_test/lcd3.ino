#include <SoftwareSerial.h>

void LCD_write(unsigned char dat){
  if(dat & (1<<4)) digitalWrite(8, HIGH); else digitalWrite(8, LOW);
  if(dat & (1<<5)) digitalWrite(9, HIGH); else digitalWrite(9, LOW);
  if(dat & (1<<6)) digitalWrite(10, HIGH); else digitalWrite(10, LOW);
  if(dat & (1<<7)) digitalWrite(11, HIGH); else digitalWrite(11, LOW);
  digitalWrite(12, HIGH); //EN=1
  delay(6);
  digitalWrite(12, LOW); //EN=0
  delay(1);//

  dat = (dat<<4);
  if(dat & (1<<4)) digitalWrite(8, HIGH); else digitalWrite(8, LOW);
  if(dat & (1<<5)) digitalWrite(9, HIGH); else digitalWrite(9, LOW);
  if(dat & (1<<6)) digitalWrite(10, HIGH); else digitalWrite(10, LOW);
  if(dat & (1<<7)) digitalWrite(11, HIGH); else digitalWrite(11, LOW);
  digitalWrite(12, HIGH); //EN=1
  delay(6);
  digitalWrite(12, LOW); //EN=0
  delay(1);//
}

void LCD_cmd(unsigned char dat){
  digitalWrite(13,LOW); //RS = 0
  LCD_write(dat);
}

void LCD_data(unsigned char dat){
  digitalWrite(13, HIGH); //RS=1
  LCD_write(dat);
}

void LCD_printf(unsigned char *data){
    while(*data){
        LCD_data(*data);
        data++;
    }
}


void setup() {
  char test[4] = {'h','o','l','a'} ;
  pinMode(8, OUTPUT); //D4
  pinMode(9, OUTPUT); //D5
  pinMode(10,OUTPUT); //D6
  pinMode(11,OUTPUT); //D7
  pinMode(12,OUTPUT); //EN 
  pinMode(13,OUTPUT); //RS
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  delay(100);
  LCD_cmd(0x28);
  LCD_cmd(0x0C);  //No cursor, no blink
  LCD_data('r');//('s');  //No se que wea... parece que el problema es que al inicializar hay que dejar mas rato los valores?
  LCD_cmd(0x06);  //automatic increment
  LCD_data('d');
  LCD_cmd(0x80);
  delay(100);
  LCD_cmd(0x02);
  LCD_cmd(0x02);
  for(int i=0; i<4;i++){
    LCD_data(test[i]);
  }
  
}

void loop() {
  char in;
  if(Serial.available()){
    in = Serial.read();

    
    if(in=='p'){
      int t=1;
      int t2 = 1;
      //copying the LCD crystal lib... try 3 times for each command
      
      LCD_cmd(0x28);  //4bit 2 line 5x7
      LCD_cmd(0x0C);  //No cursor, no blink      
      LCD_cmd(0x06);  //automatic increment
      LCD_cmd(0x80);  //address with 0 offset 80h (ni idea q paso aca
      LCD_cmd(0x02);
      delay(t);
      LCD_data('h');
      Serial.println("finish");
    }
    if(in=='l'){
      LCD_cmd(0x28);
      LCD_cmd(0x0C);  //No cursor, no blink
      LCD_data('s');  //No se que wea... parece que el problema es que al inicializar hay que dejar mas rato los valores?
      LCD_cmd(0x06);  //automatic increment
      LCD_data('d');
      LCD_cmd(0x80);
      //Serial.println("Ayuda!!");
    }
    if(in=='a'){
      LCD_cmd(0x28);
      Serial.println("4bit x 2line");
    }
    if(in=='s'){
      LCD_cmd(0x0C);
      Serial.println("asdqwe");
    }
    if(in=='d'){
      LCD_cmd(0x06);
      Serial.println("qwe12");
    }
    if(in=='f'){
      LCD_cmd(0x80);
      Serial.println("zxcasd");
    }
    if(in=='*'){
      LCD_cmd(0x02);  //1st line
    }
    if(in=='l'){
      LCD_cmd(0xC0);  //2nd line
    }
    //if(in=='m'){
    // LCD_cmd(0x94); //3rd line si hay
    //}
    if(in=='c'){
      LCD_cmd(0x01);  //clear all
    }
    if(in=='m'){
      LCD_printf("Hello World!");
    }
    else{
        LCD_data(in);
    }
  }
}
