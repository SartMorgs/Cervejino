#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>
#include "Adafruit_GFX.h"
#include <FreeDefaultFonts.h>
#include <MCUFRIEND_kbv.h>
#include <TFT_HX8357GLUE.h>
#include <UTFTGLUE.h>
MCUFRIEND_kbv tft;

//#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// --- Mapeamento de Hardware ---
#define butUp    22                                    //Botão para selecionar tela acima no digital 12
#define butDown  23                                     //Botão para selecionar tela abaixo no digital 11
#define butP     24                                   //Botão de ajuste mais no digital 10
#define butM     25                                     //Botão de ajuste menos no digital 9
//#define Lamp1    A0                                     //Saída para lâmpada 1 no A0 (será usado como digital)
//#define Lamp2    A1                                     //Saída para lâmpada 2 no A1 (será usado como digital)

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
void iniciarBrasagem();

void changeMenu();                                      //Função para modificar o menu atual
void dispMenu();                                      //Função para mostrar o menu atual
void valorMenuSub();
void info_botaoDirEsqMenu();
void subMenuTemperaturas();
void dispSubMenuTemperatura();
void valor_Temperatura(int id_temperatura);
void subMenuTempos();
void dispSubMenuTempos();
void voltarMenuPrincipal();
void valor_Tempos(int id_tempo);
void monitorar_Processo();
void iniciar_Mosturacao();
void definir_Temperaturas();
void definir_Tempos();
void informacoes();
void subMenuInfo();
void subMenuMosturacao();
void subMenuMonitorar();



// --- Variáveis Globais ---
int  subMenuTemperatura = 0, subMenuTempo = 0, menu = 0, subMenu = 0;                                 //Variável para selecionar o menu
//char set1 = 0x00, set2 = 0x00;                          //Controle das lâmpadas
boolean t_butUp, t_butDown, t_butP, t_butM;             //Flags para armazenar o estado dos botões
int valor_tempo[4] = {30, 30, 30, 0}; // valores de tempos em minutos
float temperaturas[4] = {60.0, 60.0, 60.0, 0}; // valores de temperatura atribuidos pelo usuário
boolean  mudanca = true;

void setup() {
  // put your setup code here, to run once:
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
  //lcd.begin(16, 2);                                     //Inicializa LCD 16 x 2

  for (char i = 22; i < 26; i++) pinMode(i, INPUT_PULLUP); //Entrada para os botões (digitais 9 a 12) com pull-ups internos

  // pinMode(Lamp1, OUTPUT);                                //Configura saída para lâmpada 1
  //pinMode(Lamp2, OUTPUT);                                //Configura saída para lâmpara 2

  t_butUp   = 0x00;                                      //limpa flag do botão Up
  t_butDown = 0x00;                                      //limpa flag do botão Down
  t_butP    = 0x00;                                      //limpa flag do botão P
  t_butM    = 0x00;                                      //limpa flag do botão M

  tft.setRotation(1);
  tft.fillScreen(BLACK);
}

void loop() {
  //dispMenu();
  //subMenuTemperatura();
  //dispSubMenuTemperatura();
  if (menu >= 0 && menu <= 4 && subMenu == 0) {
    changeMenu();
    dispMenu();
  } else if (subMenu != 0 ) {
    valorMenuSub();
  }
}

void changeMenu() {
  //botões cima e baixo
  if (!digitalRead(butUp))   t_butUp   = 0x01;         //Botão Up pressionado? Seta flag
  if (!digitalRead(butDown)) t_butDown = 0x01;         //Botão Down pressionado? Seta flag
  //botão direita
  if (!digitalRead(butM))    t_butM    = 0x01;         //Botão M pressionado? Seta flag

  if (digitalRead(butUp) && t_butUp)                   //Botão Up solto e flag setada?
  { //Sim...
    t_butUp = 0x00;                                   //Limpa flag
    if (subMenu == 0)menu++;                        //Incrementa menu
    if (menu > 4) menu = 1;                     //Se menu maior que 4, volta a ser 1
    mudanca = true;
  } 
  if (digitalRead(butDown) && t_butDown)               //Botão Down solto e flag setada?
  { //Sim...
    t_butDown = 0x00;                                 //Limpa flag
    if (subMenu == 0)menu--;                                           //Decrementa menu
    if (menu < 1) menu = 4;                     //Se menu menor que 1, volta a ser 4
    mudanca = true;
  }
  if (digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  {
    t_butM = 0x00;
    info_botaoDirEsqMenu();
  }
}
void dispMenu() {
  /* imagem na tela no inicio 
   *        tft.setRotation(1);
   *        wid = tft.width();
            ht = tft.height();

            extern const uint8_t penguin[];
            tft.setAddrWindow(wid - 40 - 40, 20 + 0, wid - 1 - 40, 20 + 39);
            tft.pushColors(penguin, 1600, 1);
            delay();
  
  
  */
  if (mudanca) {
    // tft.setRotation(1);
    // tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("Cervejino: Menu Principal"); // menu prinicipal, não um vaor no menu
    tft.setCursor(0, 50);
    if (menu == 1) {
      informacoes();
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
    delay(1000);
  }
}
void info_botaoDirEsqMenu() {
  if (!digitalRead(butM))    t_butM    = 0x01;         //Botão Direita pressionado? Seta flag
  if (digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  {
    t_butM = 0x00;                                    //Limpa flag
    //lcd.clear();
    switch (menu)                                       //Controle da variável menu para submenu
    {
      case 0:
        subMenu = 0; // info receitas
        break;                                     //break
      case 1:                                       //Caso 2
        subMenu = 1; // definir tempos
        break;                                     //break
      case 2:                                       //Caso 3
        subMenu = 2; // definir temperaturas
        break;
      case 3:                                       //Caso 4
        subMenu = 3; // iniciar Mosturação
        break;
      case 4:
        subMenu = 4; // Monitorar processo
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
      dispSubMenuTempos();
      break;
    case 3: //definir temperaturas
      subMenuTemperaturas();
      dispSubMenuTemperaturas();
      break;
    case 4:  // iniciar mosturacao
      subMenuMosturacao();
      break;
    case 5: //monitorar processo
      subMenuMonitorar();
      break;
  }
}
void subMenuTemperaturas() // Tela submenu = 2 com os tempos
{

  if (!digitalRead(butUp))   t_butUp   = 0x01;         //Botão Up pressionado? Seta flag
  if (!digitalRead(butDown)) t_butDown = 0x01;         //Botão Down pressionado? Seta flag

  if (digitalRead(butUp) && t_butUp)                   //Botão Up solto e flag setada?
  { //Sim...
    t_butUp = 0x00;                                   //Limpa flag
    subMenuTemperatura++;                                           //Incrementa menu
    if (subMenuTemperatura  > 5) subMenuTemperatura  = 1;                     //Se menu maior que 4, volta a ser 1
  }

  if (digitalRead(butDown) && t_butDown)               //Botão Down solto e flag setada?
  { 
    t_butDown = 0x00;                                 //Limpa flag
    subMenuTemperatura --;                                           //Decrementa menu
    if (subMenuTemperatura < 1)subMenuTemperatura  = 5 ;                     //Se menu menor que 1, volta a ser 4
  }
}
void dispSubMenuTemperaturas() {
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
  if (!digitalRead(butP))    t_butP    = 0x01;         //Botão P pressionado? Seta flag
  if (!digitalRead(butM))    t_butM    = 0x01;         //Botão M pressionado? Seta flag

  if (!digitalRead(butP) && t_butP)                     //Botão P solto e flag setada?
  { 
    t_butP = 0x00;                                    //Limpa flag
    if (temperaturas[id_temperatura] > 0)valor_tempo[id_temperatura]--;
    delay(200);
  }
  if (!digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  {
    t_butM = 0x00;                                    //Limpa flag
    temperaturas[id_temperatura]++;
    delay(200);
  }
}
void informacoes()     // Menu=1   -> submenu 1
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
void subMenuTempos() // Tela submenu = 2 com os tempos
{

  if (!digitalRead(butUp))   t_butUp   = 0x01;         //Botão Up pressionado? Seta flag
  if (!digitalRead(butDown)) t_butDown = 0x01;         //Botão Down pressionado? Seta flag

  if (digitalRead(butUp) && t_butUp)                   //Botão Up solto e flag setada?
  { //Sim...
    t_butUp = 0x00;                                   //Limpa flag
    subMenuTempo++;                                           //Incrementa menu
    if (subMenuTempo > 5) subMenuTempo = 1;                     //Se menu maior que 4, volta a ser 1
  }

  if (digitalRead(butDown) && t_butDown)               //Botão Down solto e flag setada?
  { 
    t_butDown = 0x00;                                 //Limpa flag
    subMenuTempo--;                                           //Decrementa menu
    if (subMenuTempo < 1)subMenuTempo = 5 ;                     //Se menu menor que 1, volta a ser 4
  }
}
void dispSubMenuTempos(){
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
  tft.setCursor(0, 250);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(BLUE); tft.setTextSize(1);
  tft.print(" não <- | -> sim "); //
  if (!digitalRead(butP))    t_butP    = 0x01;         //Botão P pressionado? Seta flag
  if (!digitalRead(butM))    t_butM    = 0x01;         //Botão M pressionado? Seta flag

  if (digitalRead(butP) && t_butP)                     //Botão P solto e flag setada?
  { //Não...
    t_butP = 0x00;                                    //Limpa flag
    tft.fillScreen(WHITE); //limpar tela
  }
  if (digitalRead(butM) && t_butM)                     //Botão P solto e flag setada?
  { //Sim
    t_butM = 0x00;                                    //Limpa flag
    //lcd.clear();
    subMenu = 0;
  }
  delay(500);
}

void iniciarBrasagem() {
  boolean est1=true,est2=true,est3=true;

  //conferir se todas as informações estão salvas antes de iniciar a brasagem;
  while(incio){
    while(!est1){ //temperatura e tempo 1 no vetor[0]

      if(tempoAtual == esperado)est1 = false; //saida do while
    }
    while(!est2){ //temperatura e tempo 1 no vetor[1]
       if(tempoAtual == esperado)est1 = false; // saida do while
    }
    while(!est3){ //temperatura e tempo 1 no vetor[2]
       if(tempoAtual == esperado)est1 = false; // saida do while
    }
  }

}

void subMenuInfo() {

}
void subMenuMosturacao() {

}
void subMenuMonitorar() {

  

}

