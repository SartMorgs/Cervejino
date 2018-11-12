//Biblioteca Do Clock externo
#include <DS1307.h>
DS1307 rtc(A5, A6); // Define as portas de funcionamento do Clock

//Bibliotecas para o sensor de temperatura
#include <DallasTemperature.h>
#include <OneWire.h>

//Bibliotecas para o funcionamento do LCD
#include <SPI.h>
#include "Adafruit_GFX.h"
#include <FreeDefaultFonts.h>
#include <MCUFRIEND_kbv.h>
#include <TFT_HX8357GLUE.h>
#include <UTFTGLUE.h>
MCUFRIEND_kbv tft;

// --- Mapeamento de Hardware ---
//Definir as portas de entrada dos botôes
#define butUp    22                                    //Botão para selecionar tela acima no digital 12
#define butDown  23                                     //Botão para selecionar tela abaixo no digital 11
#define butP     24                                   //Botão de ajuste mais no digital 10
#define butM     25                                     //Botão de ajuste menos no digital 9

//Definir pinos do LCD
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

//Define a porta do relé
#define rele 26
// Valores das cores com 16-bit:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// --- Protótipo das Funções Auxiliares ---
void temperatura(int temp);
//void valor_Tempos(int id_tempo);
void controle(int i);

void funcionalidadeMenu();                                      //Função para modificar o menu atual
void interfaceMenu();                                      //Função para mostrar o menu atual
void valorMenuSub();
void info_botaoDirEsqMenu();
void subMenuTemperaturas();
void interfaceSubMenuTemperaturas();
void valor_Temperatura(int id_temperatura);
void subMenuTempos();
void interfaceSubMenuTempos();
void voltarMenuPrincipal();
void valor_Tempos(int id_tempo);
void monitorar_Processo();
void iniciar_Mosturacao();
void definir_Temperaturas();
void definir_Tempos();
void interfaceInformacoes();
void subMenuInfo();
void subMenuMosturacao();
void subMenuMonitorar();
void monitoraBotaoPararVoltar();
void setTotalTime();
void showTimeLeft();



// --- Variáveis Globais ---
DS1307 rtc(A4, A5);                                                                          // Configura as portas do RTC
int  subMenuTemperatura = 0, subMenuTempo = 0, menu = 0, subMenu = 0;                        //Variáveis para selecionar o menu
boolean t_butUp, t_butDown, t_butP, t_butM;                                                  //Flags para armazenar o estado dos botões
uint8_t hora, minuto, segundo;
//uint8_t hora_restante, minuto_restante, segundo_restante;
uint8_t total;
int valor_tempo[4] = {30, 30, 30, 0};                                                       // valores de tempos em minutos
float temperaturas[4] = {60.0, 60.0, 60.0, 0};
char dados_lidos[100];                                              // valores de temperatura atribuidos pelo usuário
boolean  salvar = false, mudanca = false, parar = false, settemp, totaltime;                                    //Flags para salvar estado ou condição de parada no monitoramento

void setup() {
  //Define inicialização do LCD
  Serial.begin(9600);
  uint32_t when = millis();
  //    while (!Serial) ;   //hangs a Leonardo until you connect a Serial
  if (!Serial) delay(5000);           //allow some time for Leonardo
  Serial.println("Serial took " + String((millis() - when)) + "ms to start");
  //    tft.reset();                 //hardware reset
  uint16_t ID = tft.readID(); //
  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9481; // write-only shield
  //    ID = 0x9329;                             // force ID
  tft.begin(ID);

  // Define a porta do rele como saída
  pinMode(rele, OUTPUT);
  // Define a entrada dos botôes como  com pull-ups internos
  pinMode(butUp, INPUT_PULLUP);
  pinMode(butDown , INPUT_PULLUP);
  pinMode(butP  , INPUT_PULLUP);
  pinMode(butM  , INPUT_PULLUP);
  
  t_butUp   = false;                                      //limpa flag do botão Up
  t_butDown = false;                                      //limpa flag do botão Down
  t_butP    = false;                                      //limpa flag do botão P
  t_butM    = false;                                      //limpa flag do botão M

 //Aciona o relógio
  rtc.halt(false);
  rtc.setTime(0, 0, 0); // set tempo como sendo zero 
  //Configura a Tela LCD 
  tft.setRotation(1);         //mudar a tela para horizontal
  tft.fillScreen(BLACK);     // cor de fundo branca
}

void loop() {
  //dispMenu();
  //subMenuTemperatura();
  //dispSubMenuTemperatura();
  //interfaceMenu();
  //interfaceSubMenuTemperaturas();
 subMenuMonitorar();
  /*
  // condição incial de entrada para ter acesso ás funcionalidades principais  menu inicia com 0
  if (menu >= 0 && menu <= 4 && subMenu == 0) { 
    funcionalidadeMenu();
    interfaceMenu();
  } else if (subMenu > 0 && subMenu < 6) {//Condição de entrada para ter acesso aos subMenus do programa
    valorMenuSub();
  }
  /*
   * //Sugestão de mudança depois
   else if (subMenu > 0 && subMenu < 4) {
    valorMenuSub();
  }else if(subMenu >= 4 && subMenu < 6){
  }
  */
}

void funcionalidadeMenu() {
  //botões cima e baixo
  if (!digitalRead(butUp))   t_butUp   = true;         //Botão Up - '' pressionado? Seta flag
  if (!digitalRead(butDown)) t_butDown = true;         //Botão Down 'v' pressionado? Seta flag
  //botão direita
  if (!digitalRead(butM))    t_butM    = true;         //Botão M - '->' pressionado? Seta flag

  if (digitalRead(butUp) && t_butUp)                   //Botão Up solto e flag setada?
  { //Sim...
    t_butUp = false;                                   //Limpa flag
    if (subMenu == 0)menu++;                        //Incrementa menu
    if (menu > 4) menu = 1;                     //Se menu maior que 4, volta a ser 1
    mudanca = true;
  }
  if (digitalRead(butDown) && t_butDown)               //Botão Down solto e flag setada?
  { //Sim...
    t_butDown = false;                                 //Limpa flag
    if (subMenu == 0)menu--;                                           //Decrementa menu
    if (menu < 1) menu = 4;                     //Se menu menor que 1, volta a ser 4
    mudanca = true;
  }
  if (digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  {
    t_butM = false;
    info_botaoDirEsqMenu();
  }
}
void interfaceMenu() {                              // interfaceMenu
  /* imagem na tela no inicio
   *        tft.setRotation(1);
   *        wid = tft.width();
            ht = tft.height();
            extern const uint8_t penguin[];
            tft.setAddrWindow(wid - 40 - 40, 20 + 0, wid - 1 - 40, 20 + 39);
            tft.pushColors(penguin, 1600, 1);
            delay();
  */
  if (mudanca) {  // se algum botão for prescionado executa novamente a ação, caso contrário continua a mesma coisa.
    // tft.setRotation(1);
    // tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("Cervejino: Menu Principal"); // menu prinicipal, não um vaor no menu
    tft.setCursor(0, 50);
    if (menu == 1) {
      interfaceInformacoes();
    } else {
      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.print(" Informações da Receita"); // valor 1 no menu
    }
    tft.setCursor(0, 100);
    if (menu == 2) {
      definir_Tempos();
    } else {
      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.print(" Definir Tempos"); // valor 2 no menu
    }
    tft.setCursor(0, 150);
    if (menu == 3) {
      definir_Temperaturas();
    } else {
      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.print(" Definir Temperaturas"); // valor 3 no menu
    }
    tft.setCursor(0, 200);
    if (menu == 4) {
      iniciar_Mosturacao();
    } else {
      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.print(" Iniciar Mosturação");  // valor 4 no menu
    }
    tft.setCursor(0, 250);
    if (menu == 5) {
      monitorar_Processo();
    } else {
      tft.setTextColor(WHITE); tft.setTextSize(2);
      tft.print(" Monitorar Processo");    // valor 5 no menu
    }
    mudanca = false;
    //delay(1000);
  }
}
void info_botaoDirEsqMenu() {
  if (!digitalRead(butM))    t_butM    = true;         //Botão Direita pressionado? Seta flag

  if (digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  {
    t_butM = false;                                    //Limpa flag
    //lcd.clear();
    switch (menu)                                       //Controle da variável menu para submenu
    {
      case 0:
        subMenu = 0;
        break;
      case 1:
        subMenu = 1; // info receitas, pode ser uma imagem 
        break;
      case 2:
        subMenu = 2; // definir tempos
        break;
      case 3:
        subMenu = 3; // definir temperaturas
        break;
      case 4:
        subMenu = 4; // iniciar Mosturação, salva as info e monitora o processo
        break;
      case 5:
        subMenu = 5; // Monitorar processo
        break;

    }
    // subMenu = 0;
  }
}
void valorMenuSub() {
  switch (subMenu)                                       //Controle da variável subMenu
  {
    case 0:
      break;
    case 1:     //informacoes da receita
      subMenuInfo();
      break;
    case 2:  //definir tempos
      subMenuTempos();
      interfaceSubMenuTempos();
      break;
    case 3: //definir temperaturas
      subMenuTemperaturas();
      interfaceSubMenuTemperaturas();
      break;
    case 4:  // iniciar mosturacao
      subMenuMosturacao();
      break;
    case 5: //monitorar processo
      subMenuMonitorar();
      break;
  }
}
/*Verifica informações a respeito das temperaturas*/
void subMenuTemperaturas() // Tela submenu = 2 com os tempos
{
  if (!digitalRead(butUp))   t_butUp   = true;         //Botão Up pressionado? Seta flag
  if (!digitalRead(butDown)) t_butDown = true;         //Botão Down pressionado? Seta flag

  if (digitalRead(butUp) && t_butUp)                   //Botão Up solto e flag setada?
  { //Sim...
    t_butUp = false;                                   //Limpa flag
    subMenuTemperatura++;                                           //Incrementa menu
    if (subMenuTemperatura  > 5) subMenuTemperatura  = 1;                     //Se menu maior que 4, volta a ser 1
  }

  if (digitalRead(butDown) && t_butDown)               //Botão Down solto e flag setada?
  {
    t_butDown = false;                                 //Limpa flag
    subMenuTemperatura --;                                           //Decrementa menu
    if (subMenuTemperatura < 1)subMenuTemperatura  = 5 ;                     //Se menu menor que 1, volta a ser 4
  }
}
void interfaceSubMenuTemperaturas() {
  //limpar tela
  //tft.setRotation(0);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print(" ------ Definir Temperaturas ------ "); // menu prinicipal, não um vaor no menu
  tft.setCursor(0, 50);
  if (subMenuTemperatura == 1) {
    tft.setTextColor(YELLOW); tft.setTextSize(2);
    tft.print(" Temperatura 1 -> "); // valor 1 no menu
    //alterar valores de tempo
    valor_Temperatura(0);
    tft.print(temperaturas[0]); //
    tft.print(" Graus "); //
  } else {
    tft.setTextColor(WHITE); tft.setTextSize(1);
    tft.print(" Temperatura 1 -> "); //
    //deixar um espaço testar
    tft.print(temperaturas[0]); //
    tft.print(" Graus "); //
  }
  tft.setCursor(0, 100);
  if (subMenuTemperatura == 2) {
    tft.setTextColor(YELLOW); tft.setTextSize(2);
    tft.print(" Temperatura 2 -> "); // valor 1 no menu
    //alterar valores de tempo
    valor_Temperatura(1);
    tft.print(temperaturas[1]); //
    tft.print(" Graus "); //
  } else {
    tft.setTextColor(WHITE); tft.setTextSize(1);
    tft.print(" Temperatura 2 -> "); //
    //deixar um espaço testar
    tft.print(temperaturas[1]); //
    tft.print(" Graus "); //
  }
  tft.setCursor(0, 150);
  if (subMenuTemperatura == 3) {
    tft.setTextColor(YELLOW); tft.setTextSize(2);
    tft.print(" Temperatura 3 -> "); // valor 1 no menu
    //alterar valores de tempo
    valor_Temperatura(2);
    tft.print(temperaturas[2]); //
    tft.print(" Graus "); //
  } else {
    tft.setTextColor(WHITE); tft.setTextSize(1);
    tft.print(" Temperatura 3 -> "); //
    //deixar um espaço testar
    tft.print(temperaturas[2]); //
    tft.print(" Graus "); //
  }
  tft.setCursor(0, 200);
  if (subMenuTemperatura == 4) {
    voltarMenuPrincipal();
  } else {
    tft.setTextColor(WHITE); tft.setTextSize(1);
    tft.print("-> Voltar ao menu Principal");    // valor 5 no menu
  }
  delay(500);
}
void valor_Temperatura(int id_temperatura) {
  if (!digitalRead(butP))    t_butP    = true;         //Botão P pressionado? Seta flag
  if (!digitalRead(butM))    t_butM    = true;         //Botão M pressionado? Seta flag

  if (!digitalRead(butP) && t_butP)                     //Botão P solto e flag setada?
  {
    t_butP = false;                                    //Limpa flag
    if (temperaturas[id_temperatura] > 0)valor_tempo[id_temperatura]--;
    delay(200);
  }
  if (!digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  {
    t_butM = false;                                    //Limpa flag
    temperaturas[id_temperatura]++;
    delay(200);
  }
}
/*Interfaces do Menu Principal*/
void interfaceInformacoes()     // Menu=1   -> submenu 1
{
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.print(" Informações da Receita ->");
  info_botaoDirEsqMenu();
}

void definir_Tempos() // Menu = 2 -> submenu 2
{
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.print("-> Definir Tempos ->"); // valor 2 no menu
  info_botaoDirEsqMenu();
}

void definir_Temperaturas() // Menu = 3 -> submenu 3
{
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.print("-> Definir Temperaturas ->"); // valor 3 no menu
  info_botaoDirEsqMenu();
}

void iniciar_Mosturacao() // Menu = 4 -> submenu 4
{
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.print("-> Iniciar Mosturacao ->"); // valor 4 no menu
  info_botaoDirEsqMenu();
}

void monitorar_Processo() { // menu= 5 -> submenu 5
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.print("-> Monitorar Processo ->");    // valor 5 no menu
}
/*Fim das interfaces do Menu Principal*/

void subMenuTempos() // Tela submenu = 2 com os tempos
{
  if (!digitalRead(butUp))   t_butUp   = true;         //Botão Up pressionado? Seta flag
  if (!digitalRead(butDown)) t_butDown = true;         //Botão Down pressionado? Seta flag
  if (digitalRead(butUp) && t_butUp)                   //Botão Up solto e flag setada?
  { //Sim...
    t_butUp = false;                                   //Limpa flag
    subMenuTempo++;                                           //Incrementa menu
    if (subMenuTempo > 5) subMenuTempo = 1;                     //Se menu maior que 4, volta a ser 1
  }
  if (digitalRead(butDown) && t_butDown)                  //Botão Down solto e flag setada?
  {
    t_butDown = false;                                        //Limpa flag
    subMenuTempo--;                                           //Decrementa menu
    if (subMenuTempo < 1)subMenuTempo = 5 ;
  }
}
void interfaceSubMenuTempos() {
  //limpar tela
  //tft.setRotation(0);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print(" ------ Definir Tempos ------ "); // menu prinicipal, não um vaor no menu
  tft.setCursor(0, 50);
  if (subMenuTempo == 1) {
    tft.setTextColor(YELLOW); tft.setTextSize(2);
    tft.print(" Tempo 1 -> "); // valor 1 no menu
    //alterar valores de tempo
    valor_Tempos(0);
    tft.print(valor_tempo[0]); //
    tft.print(" min "); //
  } else {
    tft.setTextColor(WHITE); tft.setTextSize(1);
    tft.print(" Tempo 1 -> "); //
    //deixar um espaço testar
    tft.print(valor_tempo[0]); //
    tft.print(" min "); //
  }
  tft.setCursor(0, 100);
  if (subMenuTempo == 2) {
    tft.setTextColor(YELLOW); tft.setTextSize(2);
    tft.print(" Tempo 2 -> "); // valor 1 no menu
    //alterar valores de tempo
    valor_Tempos(1);
    tft.print(valor_tempo[1]); //
    tft.print(" min "); //
  } else {
    tft.setTextColor(WHITE); tft.setTextSize(1);
    tft.print(" Tempo 2 -> "); //
    //deixar um espaço testar
    tft.print(valor_tempo[1]); //
    tft.print(" min "); //
  }
  tft.setCursor(0, 150);
  if (subMenuTempo == 3) {
    tft.setTextColor(YELLOW); tft.setTextSize(2);
    tft.print(" Tempo 3 -> "); // valor 1 no menu
    //alterar valores de tempo
    valor_Tempos(2);
    tft.print(valor_tempo[2]); //
    tft.print(" min "); //
  } else {
    tft.setTextColor(WHITE); tft.setTextSize(1);
    tft.print(" Tempo 3 -> "); //
    //deixar um espaço testar
    tft.print(valor_tempo[2]); //
    tft.print(" min "); //
  }
  tft.setCursor(0, 200);
  if (subMenuTempo == 5) {
    voltarMenuPrincipal();
  } else {
    tft.setTextColor(WHITE); tft.setTextSize(1);
    tft.print("-> Voltar ao menu Principal");    // valor 5 no menu
  }
  delay(500);
}
void valor_Tempos(int id_tempo) {
  if (!digitalRead(butP))    t_butP    = 0x01;         //Botão P pressionado? Seta flag
  if (!digitalRead(butM))    t_butM    = 0x01;         //Botão M pressionado? Seta flag

  if (!digitalRead(butP) && t_butP)                     //Botão P solto e flag setada?
  {
    t_butP = 0x00;                                    //Limpa flag
    if (valor_tempo[id_tempo] > 0)valor_tempo[id_tempo]--;
    delay(200);
  }
  if (!digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  {
    t_butM = 0x00;                                    //Limpa flag
    valor_tempo[id_tempo]++;
    delay(200);
  }
}

void voltarMenuPrincipal() {
  // tft.setRotation(0);
  tft.fillScreen(WHITE);
  tft.setCursor(131, 207);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(BLUE); tft.setTextSize(1);
  tft.print(" não <- | -> sim "); //
  if (!digitalRead(butP))    t_butP    = true;         //Botão P pressionado? Seta flag
  if (!digitalRead(butM))    t_butM    = true;         //Botão M pressionado? Seta flag

  if (digitalRead(butP) && t_butP)                     //Botão P solto e flag setada?
  { //Não...
    t_butP = false;                                    //Limpa flag
    tft.fillScreen(WHITE); //limpar tela
  }
  if (digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  { //Sim
    t_butM = false;                                    //Limpa flag
    //lcd.clear();
    subMenu = 0;
  }
  delay(500);
}
void subMenuInfo() {

}
void subMenuMosturacao() {
/*
  //conferir se todas as informações estão salvas antes de iniciar a brasagem;
 
  //if(){
    while(1){ //temperatura e tempo 1 no vetor[0]
      subMenuMonitorar();
      if(tempoAtual >= tempos[0])break;//est1 = false; //saida do while
      if(parar)break;
      controle(0);
    }
    while(1){ //temperatura e tempo 1 no vetor[1]
       subMenuMonitorar();
       if(tempoAtual >= esperado)break;//est1 = false; // saida do while
       if(parar)break;
       controle(1);
    }
    while(1){ //temperatura e tempo 1 no vetor[2]
       subMenuMonitorar();
       if(tempoAtual >= esperado)break;//est1 = false; // saida do while
       if(parar)break;
       controle(2);
    }
    */
  }
  
 void controle(int i){
  /*temperaturaAtual = lerSensorTemp();
  if(temperaturaAtual <= temperatura(i)){
    digitalWrite(rele,HIGH)
  }else{
    digitalWrite(rele,LOW)
  }*/
}

void subMenuMonitorar() { // tela de monitoramento
  tft.setCursor(5, 10);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print(" Monitoramento");
  tft.setCursor(34, 96); tft.setTextColor(WHITE);
  tft.setTextSize(2);
  //tft.print(barramento.getTempC(sensorTemperatura))
  tft.setCursor(91, 96);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(" °C"); //
  tft.setCursor(156, 50); tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(" Temp1 "); //
  tft.setCursor(156, 158); tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(" Temp2 "); //
  tft.setCursor(156, 207); tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(" Temp3 "); //
  tft.setCursor(232, 50);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(" Tempo1 "); //
  tft.setCursor(232, 188);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(" Tempo2 "); //
  tft.setCursor(232, 207);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(" Tempo3 "); //
  tft.setCursor(15, 207);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(" Tempo Restante "); //
  tft.setCursor(15, 246);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(" hora "); //
  tft.print(":"); //
  tft.setCursor(73, 246);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(" min "); //tft.print(" .getTime().min ")
  tft.print(":"); //
  tft.setCursor(91, 246);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print(" Seg "); //
  tft.print(":"); //
  monitoraBotaoPararVoltar();
  tft.setCursor(15, 465);
  tft.setTextColor(WHITE); tft.setTextSize(1);
  tft.print(" Projeto Cervejino "); //


}
void monitoraBotaoPararVoltar() {

  tft.print(" não <- | -> sim "); //
  if (!digitalRead(butP))    t_butP    = true;         //Botão P pressionado? Seta flag
  if (!digitalRead(butM))    t_butM    = true;         //Botão M pressionado? Seta flag

  if (digitalRead(butP) && t_butP)                     //Botão P solto e flag setada? // condição para parar
  { //Não...
    t_butP = false;                                    //Limpa flag
    tft.fillScreen(WHITE); //limpar tela
  } else {
    tft.setCursor(156, 326);
    tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.print(" Parar "); //
  }
  if (digitalRead(butM) && t_butM)                     //Botão P solto e flag setada? // voltar
  { //Sim
    t_butM = false;                                    //Limpa flag
    voltarMenuPrincipal();
  } else {
    tft.setCursor(232, 326);
    tft.setTextColor(WHITE); tft.setTextSize(2);
    tft.print(" Voltar "); //
  }

}
void pararProcesso() {
  tft.fillScreen(WHITE);
  tft.setCursor(91, 96);
  tft.setTextColor(WHITE); tft.setTextSize(3);
  tft.print(" Deseja para o Processo "); //
  tft.setCursor(91, 207);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(BLUE); tft.setTextSize(3);
  tft.print(" não <- | -> sim "); //
  if (!digitalRead(butP))    t_butP    = true;         //Botão P pressionado? Seta flag
  if (!digitalRead(butM))    t_butM    = true;         //Botão M pressionado? Seta flag

  if (digitalRead(butP) && t_butP)                     //Botão P solto e flag setada?
  { //Não...
    t_butP = false;                                    //Limpa flag
    tft.fillScreen(WHITE); //limpar tela e volta ao normal
  }
  if (digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  { //Sim
    t_butM = false;                                    //Limpa flag
    //flag para finalizar o processo ou setar todos os tempos igual a 0
    parar = true;
    // retorna para
    //subMenu = 0;
  }
}

void setTotalTime(){
  total = valor_tempo[0] + valor_tempo[1] + valor_tempo[2] + valor_tempo[3];

  if(total > 60){
    if(settemp == false){
      hora = total / 60;
      minuto = total % 60;
      hora_restante = hora;
      minuto_restante = minuto;
      segundo_restante = segundo;
      settemp = true;
    }
  }
  else{
    if(settemp == false){
      hora = 0;
      minuto = total;
      segundo = 0;
      hora_restante = hora;
      minuto_restante = minuto;
      segundo_restante = segundo;
      settemp = true;
    }
  }


  // Mostrar tempo no display
  tft.setCursor(0, 0);
  tft.setTextColor("WHITE");
  tft.setTextSize(5);
  tft,print("Tempo total da receita: ")
  tft.print("0" + hora + ":" + minuto + "00");

}


void showTimeLeft(){


  if(rtc.getTime().hour == hora && rtc.getTime().minute == minuto && rtc.getTime().second == segundo){

  }
  else{
    tft.setCursor(1, 0);
    tft.setTextColor("WHITE");
    tft.setTextSize(3);
    tft.print("Tempo decorrente: ");
    tft.print(rtc.getTime().hour + ":" + rtc.getTime().minute + ":" + rtc.getTime().second);

    tft.setCursor(2, 0);
    tft.setTextColor("WHITE");
    tft.setTextSize(3);
    tft.print("Tempo restante: ");
    if(segundo_restante == 0){
      segundo_restante = 59;
      if(minuto_restante == 0){
        minuto_restante = 59;
      }
      else{
        minuto_restante = minuto_restante - 1;
      }
      if(hora_restante == 0){
        hora_restante = 59;
      }
      else{
        hora_restante = hora_restante - 1;
      }
    }
    else{
      segundo_restante = segundo_restante - 1;
    }
    tft.print(hora_restante + ":" + minuto_restante + ":" + segundo_restante);
  }

  tft.print("0" + hora + ":" + minuto + "00");
}

/*
}
void controle(int i){
  temperaturaAtual = lerSensorTemp();
  if(temperaturaAtual <= temperatura(i)){
    digitalWrite(rele,HIGH)
  }else{
    digitalWrite(rele,LOW)
  }
}
*/