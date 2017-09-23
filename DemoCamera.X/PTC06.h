/* 
 * File:   PTC06.h
 * Author: TrongKhanh
 *
 * Created on September 1, 2015, 9:16 PM
 */

#ifndef PTC06_H
#define	PTC06_H
#include "console.h"
/*************BYTE dau tien mac dinh cua host or cmr******/
#define CMD_HOST 0x56
#define CMD_CMR  0x76

/*************size anh*******/
#define SIZE_QQVGA 0x22 //160x120
#define SIZE_QVGA  0x11 //320x240
#define SIZE_VGA   0x00 //640x480

/************baud rate*************/
#define X_9600      0xAE
#define Y_9600      0xC8
#define X_19200     0x56
#define Y_19200     0xE4
#define X_38400     0x2A
#define Y_38400     0xF2
#define X_57600     0x1C
#define Y_57600     0x4C
#define X_115200    0x0D
#define Y_115200    0xA6

void sendByte(BYTE byte);
void sendComand(BYTE rxbuffer[], WORD len);
BYTE getCommand(BYTE rxbuffer[], WORD len);
BYTE sendReset(void);
BYTE sendStartPhoto(void);
BYTE sendGetLength(void);
void setPhotoLen(BYTE len1, BYTE len2);
DWORD sendGetPhoto(BYTE rxbuffer[]);
DWORD takePhoto(BYTE rxbuffer[]);
#endif	/* PTC06_H */
