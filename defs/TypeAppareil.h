/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TypeAppareil.h
 * Author: snir2g2
 *
 * Created on 19 mars 2019, 16:23
 */

#ifndef TYPEAPPAREIL_H
#define TYPEAPPAREIL_H

#include <string>

using namespace std;

class TypeAppareil {
	/**
	 * Pr�cise que les donn�es qui suivent sont li�es � l'ordinateur de bord.
	 */
	public: static string ORDIBORD;
	/**
	 * Pr�cise que les donn�es qui suivent sont li�es � l'instrument.
	 */
	public: static string INSTRUMENT;
	/**
	 * Pr�cise que les donn�es qui suivent sont li�es � la batterie.
	 */
	public: static string BATTERIE;
	/**
	 * Pr�cise que les donn�es qui suivent sont li�es aux red�marrages de l'ordinateur de bord.
	 */
	public: static string REBOOT;
	/**
	 * Il s'agit de donn�es li�es au Cube globalement.
	 */
	public: static string CUBE;

};

#endif /* TYPEAPPAREIL_H */

