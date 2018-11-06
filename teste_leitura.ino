#include <DS1307.h>
#include <SPI.h>
#include <SD.h>

DS1307 rtc(A4, A5);

uint8_t hora, minuto, segundo;
uint8_t valores[5] = {0, 0, 0, 0, 0};
uint8_t etapas = 3, total, verif, settemp;
char dados_lidos[100];

void setup() {
  verif = 0;
  settemp = 0;

  // Iniciando o módulo SD
  SD.begin(4);
  
  //Aciona o relógio
  rtc.halt(false);
  rtc.setTime(0, 0, 0);

  //Definições do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);

  Serial.begin(9600);
}

void loop() {

  File dados = SD.open("definicoes.txt", FILE_WRITE);

  if(dados){
    int i = 0;
    while(dados.available()){
      if(i == 0){
        etapas = dados.read();
      }
      else{
        valores[i - 1] = dados.read();
      }
      i++;
    }
  }
  else{
    Serial.println("Nao foi possivel abrir o arquivo");
  }
  dados.close();

  
  
  if(etapas > 0 && etapas < 6 && verif == 0){
    // Seta os valores das etapas no vetor
    /*
    switch(etapas){
      case 3:
         break;
      case 4:
         break;
      default:
         break;
    }
    */
    verif = 1;
  }
  total = valores[0] + valores[1] + valores [2] + valores[3] + valores[4];


  if(total > 60){
    if(settemp == 0){
      hora = total / 60;
      minuto = total % 60;
      segundo = 0;
      rtc.setTime(hora, segundo, minuto);
      settemp = 1;
    }
  }
  else{
    if(settemp == 0){
      hora = 0;
      minuto = total;
      segundo = 0;
      rtc.setTime(hora, minuto, segundo);
      settemp = 1;
    }
  }

}
