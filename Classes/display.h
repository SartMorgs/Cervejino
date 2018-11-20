#ifndef DISPLAY_H
#define DISPLAY_H

//Bibliotecas para o funcionamento do LCD
#include <SPI.h>
#include "Adafruit_GFX.h"
#include <FreeDefaultFonts.h>
#include <MCUFRIEND_kbv.h>
#include <TFT_HX8357GLUE.h>
#include <UTFTGLUE.h>
MCUFRIEND_kbv tft;

//Definir as portas de entrada dos botôes
#define butUp    22                                    	//Botão para selecionar tela acima no digital 12
#define butDown  23                                     //Botão para selecionar tela abaixo no digital 11
#define butP     24                                   	//Botão de ajuste mais no digital 10
#define butM     25                                     //Botão de ajuste menos no digital 9

//Definir pinos do LCD
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Valores das cores com 16-bit:
#define BLACK   	0x0000
#define BLUE    	0x001F
#define RED     	0xF800
#define GREEN   	0x07E0
#define CYAN    	0x07FF
#define MAGENTA 	0xF81F
#define YELLOW  	0xFFE0
#define WHITE   	0xFFFF


int  subMenuTemperatura = 0, subMenuTempo = 0, menu = 0, subMenu = 0;                        //Variáveis para selecionar o menu
boolean t_butUp, t_butDown, t_butP, t_butM;                                                  //Flags para armazenar o estado dos botões
boolean  salvar = false, mudanca = false, parar = false;

void funcionalidadeMenu();
void interfaceMenu();
void info_botaoDirEsqMenu();
void valorMenuSub();
void subMenuTemperaturas();
void interfaceSubMenuTemperaturas();
void valor_Temperatura(int id_temperatura);
void interfaceInformacoes();
void definir_Tempos();
void definir_Temperaturas()void definir_Temperaturas();
void iniciar_Mosturacao();
void monitorar_Processo();
void subMenuTempos();
void interfaceSubMenuTempos();
void valor_Tempos(int id_tempo);
void voltarMenuPrincipal();
void subMenuMonitorar();
void monitoraBotaoPararVoltar();
void pararProcesso();



#endif