#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H


//Biblioteca Do Clock externo
#include <DS1307.h>

DS1307 rtc(A5, A6); 										// Define as portas de funcionamento do Clock

float temperaturas[5] = {60.0, 60.0, 60,0, 0.0, 0.0};		// Vetor de temperaturas
uint8_t timeValue[5] = {30, 30, 30, 0, 0};						// Vetor dos tempos
uint8_t totalTime, hour, min, sec, hourLeft, minLeft, secLeft;	// Variáveis para manipulação de tempo


uint8_t getTime(uint8_t step);
void setTime(uint8_t vtime, uint8_t step);
void setTotalTime();
uint8_t* getTimeLeft();
void updateTimeLeft(uint8_t h, uint8_t m, uint8_t s);
void configRTC();

#endif