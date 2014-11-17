#ifndef ROLLCONTROL_H_
#define ROLLCONTROL_H_

#include "adis.h"

typedef struct {
	int number;
} RollServoMessage;

void MIML_INIT rollcontrol_init(int argc, char * argv[]);
void MIML_RECEIVER rc_receive_raw(unsigned char *, unsigned int, unsigned char *);
void MIML_RECEIVER rc_receive_imu(ADISMessage *);
void MIML_SENDER rc_send_servo(RollServoMessage *);
#endif
