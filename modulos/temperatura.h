#ifndef TEMPERATURA_H
#define TEMPERATURA_H

//Bibliotecas para o sensor de temperatura
#include <DallasTemperature.h>
#include <OneWire.h>


float temperatures[4] = {60.0, 60.0, 60.0, 0};


float getTempEt(uint8_t step);
void setTempEt(float temp, uint8_t step);
boolean checksTemp(float currentTemp);


#endif