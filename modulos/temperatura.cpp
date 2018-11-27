#include "temperatura.h"

// Função para pegar a temperatura de uma etapa especificada
float getTempEt(uint8_t step){
	return temperatures[step];
}

// Função para setar uma temperatura especificada de uma etapa especificada
void setTempEt(float temp, uint8_t step){
	temperatures[step] = temp;
}

// Função para verificar se a temperatura atual é igual a temperatura esperada
boolean checksTemp(float currentTemp, uint8_t step){
	if(currentTemp == temperatures[step]) 
		return true;
	else 
		return false;
}