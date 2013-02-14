/*
 * miml.h
 * auto-generated file
 */

#ifndef MIML_H_
#define MIML_H_

#include "logging.h"
#include "libusb-basic.h"
#include "mouse.h"
#include "mouse2.h"
#include "gps.h"
#include "theo-imu.h"
#include "virtdevsrv.h"
#include "fc.h"
#include "profile.h"

void FCFERR_Poll(void);
void FCF_Init (libusbSource * usb_source);
void FCF_Log (uint32_t fourcc, const unsigned char *buffer, int act_len);
void FCF_ProfSendMsg(const char *message);
#endif /* MIML_H_ */
