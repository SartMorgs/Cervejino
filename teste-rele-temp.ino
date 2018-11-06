#include <OneWire.h>
#include <DallasTemperature.h>
#define rele 7
 
OneWire pino(3);
DallasTemperature barramento(&pino);
DeviceAddress sensor;
 
void setup(void)
{
  Serial.begin(9600);
  barramento.begin();
  barramento.getAddress(sensor, 0);
  pinMode( rele, OUTPUT);
}
 
void loop()
{
  float temperatura = 29.0;
  Serial.print(temperatura);
  
  barramento.requestTemperatures(); 
  float tempAtual =  barramento.getTempC(sensor);
  Serial.print(tempAtual);
  Serial.print("\n");
  delay(500);
  if(tempAtual <= temperatura){
    digitalWrite(rele,HIGH);
  }else{
    digitalWrite(rele, LOW);
}
}
