/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   I2C.h
 * Author: snir2g1
 *
 * Created on 14 mars 2019, 16:14
 */

#ifndef I2C_H
#define I2C_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <list>
#include <iterator>
#include <sstream>
#include <math.h>
#include <syslog.h>

using namespace std;

class I2C {
public:
    I2C();
    virtual ~I2C();
    void setAddrEsclave(unsigned char addr);
    void setAddrRegistre(unsigned char reg);
    int ecrire();
    char* lire();
	int ecrire(char avaleur);
protected:
    int ouvrirAcces();
    void configurerAddrEsclave(int chemin);
    void fermerAcces(int chemin);
    unsigned char address;
    unsigned char addrRegistre;
    char valeur[5];

};

#endif /* I2C_H */

