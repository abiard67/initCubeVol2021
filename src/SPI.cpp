/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SPI.cpp
 * Author: linux
 * 
 * Created on 25 mars 2020, 23:05
 */

#include "../defs/SPI.h"
#include "../defs/CameraPhoto.h"

SPI::SPI() {
   //spi_cs0_fd = open("/dev/spidev0.0", O_RDWR);
}

SPI::SPI(const SPI& orig) {
}

SPI::~SPI() {
}

int SPI::ouvrirPortSpi(int spi_device)
{
    int status_value = -1;
    int *spi_cs_fd;
    spi_device = 0;
    spi_mode = SPI_MODE_1;
    spi_bitsPerWord = 8;
    spi_speed = 8000000;		
    spi_cs_fd = &spi_cs0_fd;
    //*spi_cs_fd = open("/dev/spidev0.0", O_RDWR);
	spi_cs0_fd = open("/dev/spidev0.0", O_RDWR);;
		std::cout<<"open spi_cs_fd = " << *spi_cs_fd <<endl;
     if (spi_cs0_fd < 0)
    {
        perror("Error - Could not open SPI device");
        exit(1);
    }
    return spi_cs0_fd;
}

int SPI::fermerPortSpi(int spi_device) 
{
    spi_device = 0;
    int status_value = -1;
    int *spi_cs_fd;
    spi_cs_fd = &spi_cs0_fd;
    status_value = close(*spi_cs_fd);
    if(status_value < 0)
    {
    	perror("Error - Could not close SPI device");
    	exit(1);
    }
    return(status_value);
}

int SPI::ecrireSpi(int spi_device, uint8_t CMD[2],int Length) 
{
    spi_device = 0;
    struct spi_ioc_transfer spi;
    int i = 0;
    int retVal = -1;
    int spi_cs_fd;
    spi_cs_fd = spi_cs0_fd;
	std::cout<<" ecrire spi_cs_fd = " << spi_cs_fd <<endl;
	memset(&spi, 0, sizeof(spi));
    spi.tx_buf = (unsigned long)CMD;		
	spi.rx_buf = (unsigned) NULL;
    spi.len = Length;
    spi.delay_usecs = 0;
    spi.speed_hz = spi_speed;
    spi.bits_per_word = spi_bitsPerWord;
    spi.cs_change = 0;		
	std::cout<<" apr�s config spi_cs_fd = " << spi_cs_fd<<" Length" << Length <<endl;
    retVal = ioctl(spi_cs_fd, SPI_IOC_MESSAGE(1), &spi);
    if(retVal < 0)
    {
	perror("Error - Problem transmitting spi data..ioctl W");
	exit(1);
    }
    return retVal;
}

int SPI::lireSpi(int spi_device,uint8_t CMD[1],uint8_t FLAG[1],int Length)
{
    spi_device = 0;
    struct spi_ioc_transfer spi[2];
    int i = 0;
    int retVal = -1;
    int spi_cs_fd;
    spi_cs_fd = spi_cs0_fd;	
	memset(&spi, 0, sizeof(spi));
	spi[0].tx_buf = (unsigned long) CMD;	
    spi[0].rx_buf = (unsigned )NULL;		
    spi[0].len = 1;
    spi[0].delay_usecs = 0;
    spi[0].speed_hz = spi_speed;
    spi[0].bits_per_word = spi_bitsPerWord;
    spi[0].cs_change = 0;	

	spi[1].tx_buf = (unsigned) NULL;	
    spi[1].rx_buf = (unsigned long )FLAG;		
    spi[1].len = Length;
    spi[1].delay_usecs = 0;
    spi[1].speed_hz = spi_speed;
    spi[1].bits_per_word = spi_bitsPerWord;
    spi[1].cs_change = 0;
    retVal = ioctl(spi_cs_fd, SPI_IOC_MESSAGE(2), &spi);
    if(retVal < 0)
    {
		perror("Error - Problem transmitting spi data.. r1 ioctl ");
		exit(1);
    }
    return retVal;
}

void SPI::verifSpi()
{
   uint8_t CMD[1];
   uint8_t FLAG[1];
       FLAG[0]=0;
    CMD[0]=ARDUCHIP_TRIG;
   do {

    //ecrireSpi(0,CMD,1);
    lireSpi(0,CMD, FLAG,1);
	usleep(10000);
    }
    while ((FLAG[0]  & 0x8) != 0x8);
}

void SPI::RecuperationIMG() { //Doit aller dans CameraPhoto
	uint8_t CMD[1];
	uint8_t FLAG[1];
	uint8_t image[JPEG_BUF_SIZE];

	unsigned int len1, len2, len3, count = 0;

	CMD[0]=FIFO_SIZE1;
	lireSpi(0,CMD, FLAG,1);
	len1 = FLAG[0];

	CMD[0]=FIFO_SIZE2;
	lireSpi(0,CMD, FLAG,1);
	len2 = FLAG[0];

	CMD[0]=FIFO_SIZE3;
	lireSpi(0,CMD, FLAG,1);
	len3 = FLAG[0];

	count = ((len3 << 16) | (len2 << 8) | len1) & 0x07fffff;
	cout<<"count ok"<< count <<endl;
	//CMD[0]=BURST_FIFO_READ;
	CMD[0]=SINGLE_FIFO_READ;

	for (int i=0; i<count; i++)
	{
		lireSpi(0,CMD, FLAG,1);
		image[i] = FLAG[0];
		readbuf[i]=image[i];
	}
	cout<<endl;

	close(spi_cs0_fd);
}
