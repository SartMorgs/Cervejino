#ifndef INTERFACE_H
#define INTERFACE_H

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
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// Valores das cores com 16-bit:
#define BLACK   	0x0000
#define BLUE    	0x001F
#define RED     	0xF800
#define GREEN   	0x07E0
#define CYAN    	0x07FF
#define MAGENTA 	0xF81F
#define YELLOW  	0xFFE0
#define WHITE   	0xFFFF


uint8_t tempSubMenu, timeSubMenu, menu, subMenu;                        //Variáveis para selecionar o menu
boolean t_butUp, t_butDown, t_butP, t_butM;                             //Flags para armazenar o estado dos botões
boolean  salvar = false, mudanca = false, parar = false;
typedef enum {NADA = 0, SOMA, SUB} check_t;

// Seta o display
void setDisplay(uint8_t x, uint8_t y, int color, uint8_t size, string text);
// Verifica se os botões foram pressionados
boolean checkButtonUp();
boolean checkButtonDown();
boolean checkButtonP();
boolean checkButtonM();
// Seta valores dos menus e submenus
void setMenu(uint8_t value);
void setSubMenu(uint8_t value);
void setTimeSubMenu(uint8_t value);
void setTempSubMenu(uint8_t value);
// Retorna valores dos menus e submenus
uint8_t getMenu();
uint8_t getSubMenu();
uint8_t getTimeSubMenu();
uint8_t getTempSubMenu();
// Interface de cada tela do menu
void interfaceInfo();
void interfaceSetTime();
void interfaceSetTemp();
void interfaceStartMost();
void checkProcess();
// Verifica soma ou subtração de valores
check_t checkValue();
// Volta ao menu principal
void backMainMenu();
// Mostra menus
void showTempSubMenu(uint8_t tempsubmenu);
void showTimeSubMenu(uint8_t timesubmenu);
void showMoniSubMenu();
void checkButtonStopBack();
void showSubMenu(uint8_t submenu);
void showMenu(uint8_t menu);



#endif