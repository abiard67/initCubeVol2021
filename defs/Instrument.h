/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Instrument.h
 * Author: snir2g2
 *
 * Created on 14 mars 2019, 17:35
 */

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <list>
#include "../defs/Status.h"
#include "../defs/Mesure.h"

using namespace std;

class Instrument {
public:

    Instrument();
    Instrument(const Instrument& orig);
	
    virtual ~Instrument();
    Status * getStatus();
    list<Mesure*> getMesures();

	/// <summary>
	/// Cette méthode permet de vider la liste de mesures après la transmission par l'unité de communication.
	/// </summary>
	void clearMesures();

	/// <summary>
	/// Cette méthode permet de supprimer la dernière mesure de la liste de mesures après la transmission par l'unité de communication.
	/// </summary>
	void clearLastMesures();

	/// <summary>
	/// Cette méthode permet d'ajouter une mesure à la liste de mesures de l'instrument.
	/// </summary>
	void addMesure(Mesure *auneMesure);

	/// <summary>
	/// Cette méthode permet d'ajouter une date et une heure à la dernière mesure enregistrée.
	/// </summary>
	void setDateMesure(string adateHour);

	/// <summary>
	/// Cette méthode permet de récolter l'état de l'instrument (mode de fonctionnement (Normal, sommeil etc.)  et température.
	/// </summary>
    int obtenirStatus(); 

	/// <summary>
	/// Cette méthode permet d'activer l'instrument avant toute mesure ou prélèvement de données.
	/// </summary>
    virtual void activer()=0;
	/// <summary>
	/// Cette méthode permet de désactiver l'instrument quand il n'est pas utile afin d'économiser de l'énergie.
	/// </summary>
    virtual void desactiver()=0;
    
private:
    string type;
    
protected:
	/// <summary>
	/// Cette méthode envoie une requête à l'instrument pour connaître son mode de fonctionnement. (Normal, sommeil etc.)
	/// </summary>
    virtual void obtenirMode()=0;   
	/// <summary>
	/// Cette méthode envoie une requête à l'instrument pour récupérer sa température interne.
	/// Remarque : Si l'instrument est dans l'état SLEEP, il se peut que la température soit nulle.
	/// </summary>   
    virtual void obtenirTempInst()=0;     

    Status* status;
    list<Mesure*> listedemesures;
};

#endif /* INSTRUMENT_H */


