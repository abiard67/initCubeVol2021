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
	public: static string ORDIBORD;
	/**
	 * Précise que les données qui suivent sont liées à l'instrument.
	 */
	public: static string INSTRUMENT;
	/**
	 * Précise que les données qui suivent sont liées à la batterie.
	 */
	public: static string BATTERIE;
	/**
	 * Précise que les données qui suivent sont liées aux redémarrages de l'ordinateur de bord.
	 */
	public: static string REBOOT;
	/**
	 * Il s'agit de données liées au Cube globalement.
	 */
	public: static string CUBE;

};

#endif /* TYPEAPPAREIL_H */

