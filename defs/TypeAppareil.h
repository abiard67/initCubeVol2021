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
	protected: static string ORDIBORD;
	/**
	 * Pr�cise que les donn�es qui suivent sont li�es � l'instrument.
	 */
	protected: static string INSTRUMENT;
	/**
	 * Pr�cise que les donn�es qui suivent sont li�es � la batterie.
	 */
	protected: static string BATTERIE;
	/**
	 * Pr�cise que les donn�es qui suivent sont li�es aux red�marrages de l'ordinateur de bord.
	 */
	protected: static string REBOOT;
	/**
	 * Il s'agit de donn�es li�es au Cube globalement.
	 */
	protected: static string CUBE;

};

#endif /* TYPEAPPAREIL_H */

