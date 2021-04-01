/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CameraPhoto.cpp
 * Author: Yanis
 * 
 * Created on 11 mars 2020, 14:24
 */

#include "../defs/CameraPhoto.h"

CameraPhoto::CameraPhoto() {
    this -> address=0x30;
}

CameraPhoto::CameraPhoto(const CameraPhoto& orig) {
}

CameraPhoto::~CameraPhoto() {
}

void CameraPhoto::activer() {
    setAddrRegistre(DEVICECONTROL);
    ecrire(BANK2);
    setAddrRegistre(COM7);
    ecrire(SRST);
    //setAddrRegistre(0x09);
    //ecrire(0);
}

void CameraPhoto::desactiver() {
    setAddrRegistre(DEVICECONTROL);
    ecrire(BANK2);
    setAddrRegistre(0x09);
    ecrire(1);
}

void CameraPhoto::configResolution() {

    envoiTableau(OV2640_JPEG_INIT);
    envoiTableau(OV2640_YUV422);
    envoiTableau(OV2640_JPEG);
    setAddrRegistre(DEVICECONTROL);
    ecrire(BANK2);
    setAddrRegistre(DEVICECONTROL);
    ecrire(0x15);
    envoiTableau(OV2640_320x240_JPEG);
    cout<<"Résolution OK"<<endl;
}

int CameraPhoto::envoiTableau(const struct sensor_reg reglist[]) {
	cout<<"envoi tableau"<<endl;
  int err = 0;
  unsigned int reg_addr = 0;
  unsigned int reg_val = 0;                     
  const struct sensor_reg *next = reglist;
  while ((reg_addr != 0xff) | (reg_val != 0xff))
  {
    reg_addr =next->reg;
    reg_val = next->val;
    setAddrRegistre(reg_addr);
    err = ecrire(reg_val);
    usleep(20000);
    next++;
  }
  return err;
}

void CameraPhoto::lancer_capture() 
{
	uint8_t CMD[2];
	CMD[0]=ARDUCHIP_FIFO | 0x80;
   CMD[1]=FIFO_CLEAR_MASK; 
   ecrireSpi(0,CMD,2);

   CMD[0]=ARDUCHIP_FIFO | 0x80;
   CMD[1]=FIFO_START_MASK; 
   ecrireSpi(0,CMD,2);
   cout<<"commande capture OK"<<endl;
   usleep(10000);
   verifSpi();
   cout<<"capture ok"<<endl;
}

int CameraPhoto::GestionJPEG() {
      ofstream file;
      file.open("Test.jpeg",ios::out);
	  if(!file)
    {
      cout<<"Erreur fichier.."<<endl;
      return 0;
    }
    cout<<"\nFichier OK !."<<endl;

    file.write(readbuf,sizeof(readbuf));
    perror("");
    file.close();  
    cout<<"\nFichier sauvé et fermé !."<<endl;
		 return 0;
    }
    
