#include "display.h"


// Funcionalidade dos botões de menu
void funcionalidadeMenu(){
	//botões cima e baixo
  	if (!digitalRead(butUp))   t_butUp   = true;         // Seta a flag se o botão ButUp estiver pressionado
  	if (!digitalRead(butDown)) t_butDown = true;         // Seta a flag se o botão ButDown estiver pressionado

  	//botão direita
  	if (!digitalRead(butM))    t_butM    = true;         // Seta a flag se o botão ButM estiver pressionado

  	// ButUp solto e flag setada
  	if (digitalRead(butUp) && t_butUp) 
  	{
    	t_butUp = false;                                 
    	if (subMenu == 0) menu++;
    	if (menu > 4) menu = 1;
    	mudanca = true;
  	}

	// ButDown solto e flag setada
  	if (digitalRead(butDown) && t_butDown)
  	{
    	t_butDown = false;
    	if (subMenu == 0) menu--;
    	if (menu < 1) menu = 4;
    	mudanca = true;
  	}

  	// ButM solto e flag setada
  	if (digitalRead(butM) && t_butM)
  	{
    	t_butM = false;
    	info_botaoDirEsqMenu();
  	}
}

// Controle da interface do menu principal pela variável menu
void interfaceMenu() {
  	// Se algum botão do menu foi pressionado
	if (mudanca) {
    	// tft.setRotation(1);
    	// tft.fillScreen(BLACK);
    	tft.setCursor(0, 0);
    	tft.setTextColor(WHITE);
    	tft.setTextSize(3);
    	tft.print("Cervejino: Menu Principal");
    	tft.setCursor(0, 50);

    	// Menu de informações
    	if (menu == 1) {
      		interfaceInformacoes();
    	} 
    	else {
      		tft.setTextColor(WHITE); tft.setTextSize(2);
      		tft.print(" Informações da Receita");
    	}
    	tft.setCursor(0, 100);

    	// Menu de configuração de tempo
    	if (menu == 2) {
      		definir_Tempos();
    	} 
    	else {
      		tft.setTextColor(WHITE); tft.setTextSize(2);
      		tft.print(" Definir Tempos");
    	}
    	tft.setCursor(0, 150);

    	// Menu de configuração de temperatura
    	if (menu == 3) {
      		definir_Temperaturas();
    	} 
    	else {
      		tft.setTextColor(WHITE); tft.setTextSize(2);
      		tft.print(" Definir Temperaturas");
    	}
    	tft.setCursor(0, 200);

    	// Menu de início da mosturação
    	if (menu == 4) {
      		iniciar_Mosturacao();
    	} 
    	else {
      		tft.setTextColor(WHITE); tft.setTextSize(2);
      		tft.print(" Iniciar Mosturação");
    	}
    	tft.setCursor(0, 250);

    	// Menu de monitoramento do processo
    	if (menu == 5) {
      		monitorar_Processo();
    	} 
    	else {
      		tft.setTextColor(WHITE); tft.setTextSize(2);
      		tft.print(" Monitorar Processo");
    	}
    	mudanca = false;
  	}
}

// Seta a variável de submenu de acordo com os botões
void info_botaoDirEsqMenu() {
  	if (!digitalRead(butM))    t_butM    = true;			// Seta a flag caso o ButM estiver pressionado

  	// ButM solto e flag setada
  	if (digitalRead(butM) && t_butM)
  	{
    	t_butM = false;

    	// Controle da variável menu para submenu
    	switch (menu) 
    	{
      		case 0:
        		subMenu = 0;
        		break;
      		case 1:
        		subMenu = 1;
        		break;
      		case 2:
        		subMenu = 2;
        		break;
      		case 3:
        		subMenu = 3;
        		break;
      		case 4:
        		subMenu = 4;
        		break;
      		case 5:
        		subMenu = 5;
        		break;
        	default
        		break;
    	}
  	}
}

// Controle da interface do submenu pela variável
void valorMenuSub() {
	//Controle da variável subMenu
  	switch (subMenu)
  	{
    	case 0:
      		break;
    	case 1:
      		subMenuInfo();
      		break;
    	case 2: 
      		subMenuTempos();
      		interfaceSubMenuTempos();
      		break;
    	case 3:
      		subMenuTemperaturas();
      		interfaceSubMenuTemperaturas();
      		break;
    	case 4:
      		subMenuMosturacao();
      		break;
    	case 5:
      		subMenuMonitorar();
      		break;
      	default
      		break;
  	}
}

// Seta a variável subMenuTemperatura
void subMenuTemperaturas(){
  	if (!digitalRead(butUp))   t_butUp   = true;		// Seta a flag se o botão ButUp estiver pressionado
  	if (!digitalRead(butDown)) t_butDown = true;        // Seta a flag se o botão ButDown estiver pressionado

  	// ButUp solto e flag setada
  	if (digitalRead(butUp) && t_butUp)
  	{
    	t_butUp = false;
    	subMenuTemperatura++;
    	if (subMenuTemperatura  > 5) subMenuTemperatura  = 1;
  	}

  	// ButDown solto e flag setada
  	if (digitalRead(butDown) && t_butDown)
  	{
    	t_butDown = false;
    	subMenuTemperatura --;
    	if (subMenuTemperatura < 1)subMenuTemperatura  = 5 ;
  	}
}

// Interface do subMenu de set dos tempos para cada temperatura
void interfaceSubMenuTemperaturas() {
  	tft.fillScreen(BLACK);
  	tft.setCursor(0, 0);
  	tft.setTextColor(WHITE);
  	tft.setTextSize(3);
  	tft.print(" ------ Definir Temperaturas ------ ");
  	tft.setCursor(0, 50);
  	if (subMenuTemperatura == 1) {
    	tft.setTextColor(YELLOW); tft.setTextSize(2);
    	tft.print(" Temperatura 1 -> "); // valor 1 no menu
    	//alterar valores de tempo
    	valor_Temperatura(0);
    	tft.print(temperaturas[0]); //
    	tft.print(" Graus "); //
  	} 
  	else {
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
  	} 
  	else {
    	tft.print(" Temperatura 2 -> "); //
    	//deixar um espaço testar
    	tft.setTextColor(WHITE); tft.setTextSize(1);
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
  	} 
  	else {
    	tft.setTextColor(WHITE); tft.setTextSize(1);
    	tft.print(" Temperatura 3 -> "); //
    	//deixar um espaço testar
    	tft.print(temperaturas[2]); //
    	tft.print(" Graus "); //
  	}
  	tft.setCursor(0, 200);
  	if (subMenuTemperatura == 4) {
    	voltarMenuPrincipal();
  	} 
  	else {
    	tft.setTextColor(WHITE); tft.setTextSize(1);
    	tft.print("-> Voltar ao menu Principal");    // valor 5 no menu
  	}
  	delay(500);
}

// Menu de set do valor de tempo para cada etapa
void valor_Temperatura(int id_temperatura) {
  	if (!digitalRead(butP))    t_butP    = true;		// Seta a flag se o botão ButP estiver pressionado
  	if (!digitalRead(butM))    t_butM    = true;        // Seta a flag se o botão ButM estiver pressionado

  	// ButP solto e flag setada
  	if (!digitalRead(butP) && t_butP)
  	{
    	t_butP = false;
    	if (temperaturas[id_temperatura] > 0) temperaturas[id_temperatura]--;
    	delay(200);
  	}

  	// ButM solto e flag setada
  	if (!digitalRead(butM) && t_butM)
  	{
    	t_butM = false;
    	temperaturas[id_temperatura]++;
    	delay(200);
  	}
}

// Interface do menu das informações
void interfaceInformacoes(){
  	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print(" Informações da Receita ->");
  	info_botaoDirEsqMenu();
}

// Interface do menu de definição de tempos
void definir_Tempos(){
  	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Definir Tempos ->"); // valor 2 no menu
  	info_botaoDirEsqMenu();
}

// Interface do menu de definição de temperaturas
void definir_Temperaturas()
{
  	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Definir Temperaturas ->"); // valor 3 no menu
  	info_botaoDirEsqMenu();
}


void iniciar_Mosturacao()
{
  	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Iniciar Mosturacao ->"); // valor 4 no menu
  	info_botaoDirEsqMenu();
}


void monitorar_Processo() {
  	tft.setTextColor(YELLOW); tft.setTextSize(2);
  	tft.print("-> Monitorar Processo ->");    // valor 5 no menu
}


void subMenuTempos()
{
  	if (!digitalRead(butUp))   t_butUp   = true;		// Seta a flag se o botão ButUp estiver pressionado
  	if (!digitalRead(butDown)) t_butDown = true;        // Seta a flag se o botão ButDown estiver pressionado
  	
  	// ButUp solto e flag setada 
  	if (digitalRead(butUp) && t_butUp)
  	{
    	t_butUp = false;
    	subMenuTempo++;
    	if (subMenuTempo > 5) subMenuTempo = 1;
  	}

  	// ButDown solto e flag setada
  	if (digitalRead(butDown) && t_butDown)
  	{
    	t_butDown = false;
    	subMenuTempo--;
    	if (subMenuTempo < 1) subMenuTempo = 5 ;
  	}
}


void interfaceSubMenuTempos() {
  	tft.fillScreen(BLACK);
  	tft.setCursor(0, 0);
  	tft.setTextColor(WHITE);
  	tft.setTextSize(3);
  	tft.print(" ------ Definir Tempos ------ "); // menu prinicipal, não um vaor no menu
  	tft.setCursor(0, 50);
  	if (subMenuTempo == 1) {
    	tft.setTextColor(YELLOW); tft.setTextSize(2);
    	tft.print(" Tempo 1 -> ");
    	//alterar valores de tempo
    	valor_Tempos(0);
    	tft.print(valor_tempo[0]);
    	tft.print(" min ");
  	} 
  	else {
    	tft.setTextColor(WHITE); tft.setTextSize(1);
    	tft.print(" Tempo 1 -> ");
    	//deixar um espaço testar
    	tft.print(valor_tempo[0]);
    	tft.print(" min ");
  	}
  	tft.setCursor(0, 100);
  	if (subMenuTempo == 2) {
    	tft.setTextColor(YELLOW); tft.setTextSize(2);
    	tft.print(" Tempo 2 -> ");
    	//alterar valores de tempo
    	valor_Tempos(1);
   		tft.print(valor_tempo[1]);
    	tft.print(" min ");
  	} 
  	else {
    	tft.setTextColor(WHITE); tft.setTextSize(1);
    	tft.print(" Tempo 2 -> ");
    	//deixar um espaço testar
    	tft.print(valor_tempo[1]);
    	tft.print(" min ");
  	}
  	tft.setCursor(0, 150);
  	if (subMenuTempo == 3) {
    	tft.setTextColor(YELLOW); tft.setTextSize(2);
    	tft.print(" Tempo 3 -> ");
    	//alterar valores de tempo
    	valor_Tempos(2);
    	tft.print(valor_tempo[2]);
    	tft.print(" min ");
  	}
  	else {
    	tft.setTextColor(WHITE); tft.setTextSize(1);
    	tft.print(" Tempo 3 -> ");
    	//deixar um espaço testar
    	tft.print(valor_tempo[2]);
    	tft.print(" min ");
  	}	
  	tft.setCursor(0, 200);
  	if (subMenuTempo == 5) {
  		voltarMenuPrincipal();
  	} 
  	else {
    	tft.setTextColor(WHITE); tft.setTextSize(1);
    	tft.print("-> Voltar ao menu Principal");
  	}
  	delay(500);
}


void valor_Tempos(int id_tempo) {
  	if (!digitalRead(butP))    t_butP    = 0x01;		// Seta a flag se o botão ButP estiver pressionado
  	if (!digitalRead(butM))    t_butM    = 0x01;        // Seta a flag se o botão ButM estiver pressionado

  	// ButP solto e flag setada
  	if (!digitalRead(butP) && t_butP)
  	{
    	t_butP = 0x00;
    	if (valor_tempo[id_tempo] > 0) valor_tempo[id_tempo]--;
    	delay(200);
  	}

  	// ButM solto e flag setada
  	if (!digitalRead(butM) && t_butM)
  	{
    	t_butM = 0x00;
    	valor_tempo[id_tempo]++;
    	delay(200);
  	}
}


void voltarMenuPrincipal() {
  	tft.fillScreen(WHITE);
  	tft.setCursor(131, 207);
  	tft.setTextColor(BLACK);
  	tft.setTextSize(3);
  	tft.setTextColor(BLUE); tft.setTextSize(1);
  	tft.print(" não <- | -> sim "); //
  	if (!digitalRead(butP))    t_butP    = true;		// Seta a flag se o botão ButP estiver pressionado
  	if (!digitalRead(butM))    t_butM    = true;        // Seta a flag se o botão ButM estiver pressionado

  	// ButP solto e flag setada
  	if (digitalRead(butP) && t_butP)
  	{
    	t_butP = false;
    	tft.fillScreen(WHITE);
  	}

  	// ButM solto e flag setada
  	if (digitalRead(butM) && t_butM)
  	{
    	t_butM = false;
    	subMenu = 0;
  	}
  	delay(500);
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
  	if (!digitalRead(butP))    t_butP    = true;		// Seta a flag se o botão ButP estiver pressionado
  	if (!digitalRead(butM))    t_butM    = true;        // Seta a flag se o botão ButM estiver pressionado

  	// ButP solto e flag setada
  	if (digitalRead(butP) && t_butP)
  	{
    	t_butP = false;
    	tft.fillScreen(WHITE);
  	} 
  	else {
    	tft.setCursor(156, 326);
    	tft.setTextColor(WHITE); tft.setTextSize(2);
    	tft.print(" Parar "); //
  	}

  	// ButM solto e flag setada
  	if (digitalRead(butM) && t_butM)
  	{
    	t_butM = false;
    	voltarMenuPrincipal();
  	}
  	else {
    	tft.setCursor(232, 326);
    	tft.setTextColor(WHITE); tft.setTextSize(2);
    	tft.print(" Voltar ");
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
  	if (!digitalRead(butP))    t_butP    = true;		// Seta a flag se o botão ButP estiver pressionado
  	if (!digitalRead(butM))    t_butM    = true;        // Seta a flag se o botão ButM estiver pressionado

  	// ButP solto e flag setada
  	if (digitalRead(butP) && t_butP)
  	{
    	t_butP = false;
    	tft.fillScreen(WHITE);
  	}

  	// ButM solto e flag setada
  	if (digitalRead(butM) && t_butM)
  	{
    	t_butM = false;
    	parar = true;

  	}
}