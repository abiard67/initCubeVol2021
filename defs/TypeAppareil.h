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
	 * Précise que les données qui suivent sont liées à l'ordinateur de bord.
	 */
	protected: static string ORDIBORD;
	/**
	 * Précise que les données qui suivent sont liées à l'instrument.
	 */
	protected: static string INSTRUMENT;
	/**
	 * Précise que les données qui suivent sont liées à la batterie.
	 */
	protected: static string BATTERIE;
	/**
	 * Précise que les données qui suivent sont liées aux redémarrages de l'ordinateur de bord.
	 */
	protected: static string REBOOT;
	/**
	 * Il s'agit de données liées au Cube globalement.
	 */
	protected: static string CUBE;

};

#endif /* TYPEAPPAREIL_H */

