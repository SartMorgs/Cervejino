#include "interface.h"

void setDisplay(uint8_t x, uint8_t y, int color, uint8_t size, string text){
	tft.setCursor(x, y);
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.print(text);
}

boolean checkButtonUp(){
	if (!digitalRead(butUp)) t_butUp = true;
	if (digitalRead(butUp) && t_butUp){
		t_butUp = false;
		return true;
	}
	else return false;
}

boolean checkButtonDown(){
	if (!digitalRead(butDown)) t_butDown = true;
	if (digitalRead(butDown) && t_butDown){
		t_butDown = false;
		return true;
	}
	else return false;
}

boolean checkButtonP(){
	if (!digitalRead(butP)) t_butP = true;
	if (digitalRead(butP) && t_butP){
		t_butP = false;
		return true;
	}
	else return false;
}

boolean checkButtonM(){
	if (!digitalRead(butM)) t_butM = true;
	if (digitalRead(butM) && t_butM){
		t_butM = false;
		return true;
	}
	else return false;
}

void setMenu(uint8_t value){
	menu = value;
}

void setSubMenu(uint8_t value){
	subMenu = value;
}

void setTimeSubMenu(uint8_t value){
	timeSubMenu = value;
}

void setTempSubMenu(uint8_t value){
	tempSubMenu = value;
}

uint8_t getMenu(){
	return menu;
}

uint8_t getSubMenu(){
	return subMenu;
}

uint8_t getTimeSubMenu(){
	return timeSubMenu;
}

uint8_t getTempSubMenu(){
	return tempSubMenu;
}

void interfaceInfo(){
	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Informações da Receita ->");
  	if(checkButtonM()) subMenu = menu;
}

void interfaceSetTime(){
	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Definir Tempos ->");
  	if(checkButtonM()) subMenu = menu;
}

void interfaceSetTemp(){
	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Definir Temperaturas ->");
  	if(checkButtonM()) subMenu = menu;
}

void interfaceStartMost(){
	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Iniciar Mosturacao ->");
  	if(checkButtonM()) subMenu = menu;
}

void checkProcess(){
	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Monitorar Processo ->");
  	if(checkButtonM()) subMenu = menu;
}

check_t checkValue(){
	if(checkButtonP()) return SUB;
	else if(checkButtonM()) return SOMA;
	else return NADA;
}

void backMainMenu(){
	tft.fillScreen(WHITE);
	setDisplay(131, 207, BLACK, 3, " não <- | -> sim ");
	if(checkButtonP()) tft.fillScreen(WHITE);
	else if(checkButtonM()) subMenu = 0;
	delay(500);
}

void showTempSubMenu(){
	tft.fillScreen(BLACK);
	setDisplay(0, 0, WHITE, 3, " ------ Definir Temperaturas ------ ");
	switch(tempSubMenu){
		case 1:
			setDisplay(0, 50, YELLOW, 2, " Temperatura 1 -> ");
			checkValue();
			break;
		case 2:
			setDisplay(0, 100, YELLOW, 2, " Temperatura 2 -> ");
			checkValue();
			break;
		case 3:
			setDisplay(0, 150, YELLOW, 2, " Temperatura 3 -> ");
			checkValue();
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			voltarMenuPrincipal();
			break;
		default:
			tft.setTextColor(WHITE);
			tft.setTextSize(1);
			tft.setCursor(0, 50);
			tft.print(" Temperatura 1 -> ");
			tft.setCursor(0, 100);
			tft.print(" Temperatura 2 -> ");
			tft.setCursor(0, 150);
			tft.print(" Temperatura 3 -> ");
			tft.setCursor(0, 200);
			tft.print(" Temperatura 4 -> ");
			tft.setCursor(0, 250);
			tft.print(" Temperatura 5 -> ");
			break;
	}
}

void showTimeSubMenu(){
	setDisplay(0, 0, WHITE, 3, " ------ Definir Tempos ------ ");
	switch(timeSubMenu){
		case 1:
			setDisplay(0, 50, YELLOW, 2, " Tempo 1 -> ");
			checkValue();
			break;
		case 2:
			setDisplay(0, 100, YELLOW, 2, " Tempo 2 -> ");
			checkValue();
			break;
		case 3:
			setDisplay(0, 150, YELLOW, 2, " Tempo 3 -> ");
			checkValue();
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			voltarMenuPrincipal();
			break;
		default:
			tft.setTextColor(WHITE);
			tft.setTextSize(1);
			tft.setCursor(0, 50);
			tft.print(" Tempo 1 -> ");
			tft.setCursor(0, 100);
			tft.print(" Tempo 2 -> ");
			tft.setCursor(0, 150);
			tft.print(" Tempo 3 -> ");
			tft.setCursor(0, 200);
			tft.print(" Tempo 4 -> ");
			tft.setCursor(0, 250);
			tft.print(" Tempo 5 -> ");
			break;
	}
}

void showMoniSubMenu(){
	setDisplay(5, 10, WHITE, 3, " Monitoramento ");
	setDisplay(34, 95, WHITE, 2, "");
	setDisplay(91, 96, WHITE, 2, " ºC ");
	setDisplay(156, 50, WHITE, 2, " Temp 1 ");
	setDisplay(156, 158, WHITE, 2, " Temp 2 ");
	setDisplay(232, 50, WHITE, 2, " Temp 3 ");
	setDisplay(232, 188, WHITE, 2, " Tempo1 ");
	setDisplay(15, 207, WHITE, 2, " Tempo2 ");
	setDisplay(15, 246, WHITE, 2, " Tempo3 ");
	monitoraBotaoPararVoltar();
	setDisplay(15, 465, WHITE, 1, " Projeto Cervejino ");
}

void checkButtonStopBack(){
	tft.print(" não <- | -> sim ");
	if(checkButtonP()) tft.fillScreen(WHITE);
	else if(checkButtonM()) backMainMenu();
	else{
		setDisplay(156, 326, WHITE, 2, " Parar ");
		setDisplay(232, 326, WHITE, 2, " Voltar ");
	}
}

void showSubMenu(uint8_t submenu){
	switch(submenu){
		case 0:
      		break;
    	case 1:
      		
      		break;
    	case 2: 
      		showTimeSubMenu();
      		break;
    	case 3:
      		showTempSubMenu();
      		break;
    	case 4:
      		showMostSubMenu();
      		break;
    	case 5:
      		showMoniSubMenu();
      		break;
      	default:
      		break;
    }
}

void showMenu(uint8_t menu){
	string text = "Cervejino: menu principal";
	switch(menu){
		case 0:
			break;
		case 1:
			interfaceInfo();
			break;
		case 2:
			interfaceSetTime();
			break;
		case 3:
			interfaceSetTemp();
			break;
		case 4:
			interfaceStartMost()
			break;
		case 5:
			checkProcess();
			break;
		default:
			tft.setCursor(0, 0);
			tft.setTextSize(2);
			tft.print(" Informações da Receita");
			tft.setCursor(0, 100);
			tft.print(" Definir Tempos");
			tft.setCursor(0, 150);
			tft.print(" Definir Temperaturas");
			tft.setCursor(0, 200);
			tft.print(" Iniciar Mosturação");
			tft.setCursor(0, 250);
			tft.print(" Monitorar Processo");
			break;
	}
}