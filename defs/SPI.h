/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SPI.h
 * Author: linux
 *
 * Created on 25 mars 2020, 23:05
 */

#ifndef SPI_H
#define SPI_H
#include <fcntl.h>			//Needed for SPI port
#include <sys/ioctl.h>			//Needed for SPI port
#include <linux/spi/spidev.h>           //Needed for SPI port
#include <unistd.h>			//Needed for SPI port
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#define JPEG_BUF_SIZE 640*480

class CameraPhoto;

class SPI {

public:
    SPI();
    SPI(const SPI& orig);
    virtual ~SPI();

    int ouvrirPortSpi(int spi_device);
    int fermerPortSpi(int spi_device);
    int ecrireSpi(int spi_device,uint8_t CMD[2],int Length);
    int lireSpi(int spi_device,uint8_t CMD[1],uint8_t FLAG[1],int Length);
    void verifSpi();
    void RecuperationIMG();
    char readbuf[JPEG_BUF_SIZE];
    //uint8_t CMD[6];
private:
    int spi_cs0_fd;	//file descriptor for the SPI device			//file descriptor for the SPI device
    uint8_t spi_mode = SPI_MODE_1;
    uint8_t spi_bitsPerWord = 8;
    uint32_t spi_speed = 4000000;
    
    
};

#endif /* SPI_H */