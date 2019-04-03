#include "U8glib.h"
#include "DHT.h"
 
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 3; // IN 1 == LED
//Porta ligada ao pino IN2 do modulo
int porta_rele2 = 4; // IN 2 == MOTOR ESTEIRA

U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
DHT dht(DHTPIN, DHTTYPE);
void setup() {
    Serial.begin(9600);
    dht.begin();
    pinMode(porta_rele1, OUTPUT); 
    pinMode(porta_rele2, OUTPUT);
    digitalWrite(porta_rele1, LOW);  //LIGA LED
    digitalWrite(porta_rele2, HIGH);  //DESLIGA ESTEIRA
}


void loop() {
  static unsigned long thisMicros = 0;
  static unsigned long lastMicros = 0;
  float t = dht.readTemperature();
  // picture loop
  u8g.firstPage();  
  do {
    if (isnan(t)){
      u8g.setFont(u8g_font_04b_03r);
      u8g.drawFrame(0,0, 84, 48);    // QUADRADO TELA
      u8g.drawRFrame(2, 2, 80, 15, 2);   //PRIMEIRO CIRCULO GRANDE
      u8g.drawRFrame(2, 22, 64, 10, 3);  //SEGUNDO CIRCULO GRANDE
      u8g.drawRFrame(2, 31, 30, 15, 3);  //CIRCULO PEQUENO EM BAIXO
      u8g.setPrintPos(4, 12);
      u8g.print("Falha no sensor");
      u8g.setFont(u8g_font_04b_03r);
      u8g.drawStr(4, 30, "Temperatura");
      u8g.setPrintPos(4, 43);
      u8g.print(t);
      u8g.setPrintPos(20, 43);
      u8g.print("C");
    }else{
      if(t < 35){
      digitalWrite(porta_rele1, LOW);  // DESLIGA ESTEIRA
      digitalWrite(porta_rele2, HIGH);  // LIGA LED
      u8g.setFont(u8g_font_04b_03r);
      u8g.drawFrame(0,0, 84, 48);// QUADRADO TELA
      u8g.drawRFrame(2, 2, 80, 15, 2);   //PRIMEIRO CIRCULO GRANDE
      u8g.drawRFrame(2, 22, 64, 10, 3);  //SEGUNDO CIRCULO GRANDE
      u8g.drawRFrame(2, 31, 40, 15, 3);  //CIRCULO PEQUENO EM BAIXO
      u8g.setPrintPos(4, 12);
      u8g.print("Esteira desligada!");
      u8g.setFont(u8g_font_04b_03r);
      u8g.drawStr(4, 30, "Temperatura");
      u8g.setPrintPos(4, 43);
      u8g.print(t);
      u8g.setPrintPos(30, 43);
      u8g.print("C");
  }
  else {
      digitalWrite(porta_rele1, LOW);  //lIGA LED
      digitalWrite(porta_rele2, LOW);  //LIGA ESTEIRA
      u8g.setFont(u8g_font_04b_03r);
      u8g.drawFrame(0,0, 84, 48);// QUADRADO TELA
      u8g.drawRFrame(2, 2, 80, 15, 2);   //PRIMEIRO CIRCULO GRANDE
      u8g.drawRFrame(2, 22, 64, 10, 3);  //SEGUNDO CIRCULO GRANDE
      u8g.drawRFrame(2, 31, 40, 15, 3);  //CIRCULO PEQUENO EM BAIXO
      u8g.setPrintPos(4, 12);
      u8g.print("Esteira ligada!");
      u8g.setFont(u8g_font_5x7);
      u8g.drawStr(4, 30, "Temperatura");
      u8g.setPrintPos(4, 43);
      u8g.print(t);
      u8g.setPrintPos(30, 43);
      u8g.print("C");
  }
}
  }while( u8g.nextPage() );{
  float t = dht.readTemperature();
  delay(250);
}
}
