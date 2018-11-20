#include "temporizador.h"

uint8_t getTime(uint8_t step){
	return timeValue[step];
}


void setTime(uint8_t vtime, uint8_t step){
	timeValue[step] = vtime;
}

void setTotalTime(){
	total = timeValue[0] + timeValue[1] + timeValue[2] + timeValue[3];


  	if(total > 60){
      	hour = total / 60;
      	min = total % 60;
      	sec = 0;
      	hourLeft = hour;
      	minLeft = min;
      	secLeft = sec;
  	}
  	else{
      	hour = 0;
      	min = total;
      	sec = 0;
      	hourLeft = hour;
      	minLeft = min;
      	secLeft = sec;
  	}
}

uint8_t* getTimeLeft(){
	uint8_t t[3] = {hourLeft, minLeft, secLeft};
	return t;
}

void updateTimeLeft(uint8_t h, uint8_t m, uint8_t s){
	if(!(rtc.getTime().hour == h && rtc.getTime().minute == m && rtc.getTime().second == s)){
		if(secLeft == 0){
      		secLeft = 59;
      		if(minLeft == 0){
        		minLeft = 59;
      		}
      		else{
        		minLeft = minLeft - 1;
      		}
      		if(hourLeft == 0){
        		hourLeft = 59;
      		}
      		else{
        		hourLeft = hourLeft - 1;
      		}
    	}
    	else{
      		secLeft = secLeft - 1;
    	}
	}
}


void configRTC(){
	//Aciona o relógio
  	rtc.halt(false);
  	rtc.setTime(0, 0, 0); 						// set tempo como sendo zero 
}
