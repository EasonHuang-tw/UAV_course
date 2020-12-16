#include "stm32f4xx.h"
#include "uart.h"
#include "spi.h"
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "stm32f4xx_conf.h"
#include "pwm.h"
#include "motor.h"


int main()
{
	pwm_init();           // control motor
	motor_init();	      // set pwm signal to motor
	motor_thrust_test(30);
	//esc_calibrate();
	while(1){

	}
	return 0;
}

