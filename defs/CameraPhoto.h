/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CameraPhoto.h
 * Author: Yanis
 *
 * Created on 11 mars 2020, 14:24
 */

#ifndef CAMERAPHOTO_H
#define CAMERAPHOTO_H

#include "I2C.h"
#include "Instrument.h"
#include "ov2640_regs.h"
#include "SPI.h"
#include <fstream>

#define ARDUCHIP_TEST1                  0x00
#define ARDUCHIP_TRIG      		0x41
#define ARDUCHIP_FRAMES                 0x01
#define ARDUCHIP_MODE                   0x02
#define MCU2LCD_MODE                    0x00
#define CAM2LCD_MODE                    0x01
#define LCD2MCU_MODE                    0x02
#define LOW_POWER_MODE                  0x40 //0 = Normal mode,1 = Low power mode
#define ARDUCHIP_TIM                    0x03
#define HREF_LEVEL_MASK    		0x01 
#define VSYNC_LEVEL_MASK   		0x02  
#define LCD_BKEN_MASK      		0x04
#define ARDUCHIP_FIFO      		0x04
#define FIFO_CLEAR_MASK    		0x01
#define FIFO_START_MASK    		0x02
#define FIFO_RDPTR_RST_MASK             0x10
#define FIFO_WRPTR_RST_MASK             0x20
#define ARDUCHIP_GPIO			0x06 
#define GPIO_RESET_MASK			0x01  						
#define GPIO_PWDN_MASK			0x02 
#define GPIO_PWREN_MASK			0x04
#define BURST_FIFO_READ			0x3C
#define SINGLE_FIFO_READ		0x3D 
#define FIFO_SIZE1			0x42
#define FIFO_SIZE2			0x43
#define FIFO_SIZE3			0x44
#define DEVICECONTROL                   0xff
#define BANK1                           0x00
#define BANK2                           0x01
#define COM7							0x12
#define SRST							0x80
#define CMD_BUF_SIZE 512


using namespace std;

class CameraPhoto : public Instrument , public I2C, public SPI {
public:
    CameraPhoto();
    CameraPhoto(const CameraPhoto& orig);
    virtual ~CameraPhoto();
    void activer();
    void desactiver();
    void configResolution();
    int envoiTableau(const struct sensor_reg reglist[]);
    void lancer_capture();
    int GestionJPEG();
private:
    
};

#endif /* CAMERAPHOTO_H */

