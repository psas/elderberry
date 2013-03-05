/*
 * auto generated fcf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fcfutils.h"

/**		User Modules	*/

#include "module_mouse_clark.h"
#include "module_mouse_clark2.h"
#include "module_mouse_jm.h"
#include "module_mouse_jm2.h"
#include "module_testLoggerScreen.h"
#include "module_profile.h"
//#include "module_temp.h"
#include "module_testIMU.h"
#include "module_testLoggerDisk.h"
#include "module_gps.h"
#include "module_theo-imu.h"



/***************	CODE GENERATED SPACE	**************/

void fcf_init() {
	// System inits
	init_fcf();			//< Special FCF init that sets up fd structures

	// User module inits
<<<<<<< Updated upstream
	//init_diskLogger();	// This should be listed first.
	//init_temp();
	//init_mouse_clark();
	//init_mouse_jm();
	//init_mouse_jm2();
=======
	//init_diskLogger();
	//init_mouse3();
	init_mouse();
>>>>>>> Stashed changes
	//init_theo_imu();
	//init_test();
	//init_gps();
	//init_theo_imu();
	init_profiling();
}


void fcf_callback_gyr(char *buff, int length) {
	screenLogger_getMessage("gyr", buff, length);
	//diskLogger_getMessage("gyr", buff, length);
}


void fcf_callback_acc(char *buff, int length) {
	screenLogger_getMessage("acc", buff, length);
	//diskLogger_getMessage("acc", buff, length);
}

void fcf_callback_temp(char *buff, int length){
	screenLogger_getTemp("temp", buff, length);
}

<<<<<<< Updated upstream
void fcf_callback_mouse_clark(unsigned char *buff, int length){
	screenLogger_getMouseMessage("mouse_clark", buff, length);
=======
void fcf_callback_mouse(unsigned char *buff, int length){
	static int count = 0;
	if (++count == 10000) fcf_stop_main_loop();
	screenLogger_getMouseMessage("mouse", buff, length);
>>>>>>> Stashed changes
}

void fcf_callback_mouse_clark2(unsigned char *buff, int length){
	screenLogger_getMouseMessage("mouse_clark2", buff, length);
}

void fcf_callback_profile(unsigned char *buff, int length){
	profile_getMessage(buff, length);
}

void fcf_callback_gps(unsigned char ret, unsigned char * buff, int length){
}

void fcf_callback_theo_imu(const char * src, unsigned char * buff, int length){
}


/***************	END CODE GENERATED SPACE	**************/
