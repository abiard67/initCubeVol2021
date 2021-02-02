/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Protocole.h
 * Author: snir2g2
 *
 * Created on 18 mars 2019, 08:36
 */

#ifndef PROTOCOLE_H
#define PROTOCOLE_H

#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>
#include <list>
#include <vector>

#include "../defs/Message.h"
#include "../defs/TypeMisEtat.h"
#include "../defs/TypeAppareil.h"
#include "../defs/TypeCommande.h"
#include "../defs/TypeAck.h"

class Protocole : public TypeCommande, public TypeMisEtat, public TypeAppareil, public TypeAck {
	public:
		Protocole();
		Protocole(const Protocole& orig);
		virtual ~Protocole();
	/**
	 * accesseur au tableau de 100 octets à transmettre ou reçus
	 */
		char *getTableau();
		int getNbrePaquets();
		int getNumPaquet();
		list<vector<char>> getReceived();
	/**
	 * modificateur au tableau de 100 octets à transmettre ou reçus
	 * complété par des 0 si nécessaire
	 * 
	 */
		void setTableau(char laDataRecu[100]);
		void setNbrePaquets(int n);
		void setNumPaquet(int n);
		/// <param name="arecu">Méthode permettant d'ajouter un paquet de données à la liste des données reçues.</param>
   		void addReceived(char recu [100]);
		void detramerMessage();

	/// <summary>
	/// méthode d'extraction du code message dans le tableau d'octets reçus
	/// première méthode appelée lors de la réception d'une salve.
	/// retourne le code message si OK
	/// retourne le code erreur ERR_CHECKSUM si problème de checksum
	/// retourne le code erreur ERR_FORMAT si la trame de commence pas par ~
	/// Le type Message est soit :
	/// -TypeCommande::MISSION
	/// -TypeCommande::MEASURE
	/// -TypeCommande::STATUS
	/// </summary>
		string extraireTypeMessage(int &pos);

	/// <summary>
	/// Méthode d'extraction du nombre de paquets et du numéro de paquet.
	/// Complète les attributs correspondants de Protocole.
	/// </summary>
	/// <param name="apos">Position du dernier caractère du code message.</param>
		void extraireNombrePaquets(int &pos);

	/// <summary>
	/// Méthode qui calcule le nombre de paquets dans une salve reçue.
	/// </summary>
		int calculerNbrePaquetsSalve();

	/// <summary>
	/// Méthode d'extraction du type de données dans le tableau d'octets reçus
	/// à exécuter après extraireTypeMessage et test de la valeur de retour
	/// Le type de données dépend du type de message :
	/// Si TypeMessage = TypeCommande::MISSION, le type de données est, pour cet incrément TypeMisEtat::TEMPCELSIUS.
	/// Si TypeMessage = TypeCommande::MEASURE, le type de données peut être, pour cet incrément :
	/// - TypeMisEtat::TEMPCELSIUS,
	/// - TypeMisEtat::PIXEL.
	/// </summary>
	/// <param name="pos">position du type de données de Mission</param>
		string extraireTypeDataMission(int &pos);

	 /// Méthode d'extraction des données d'une mission dans le tableau d'octets reçus
	 /// à utiliser après  extraireTypeDataMission
	 /// <param name="datas"> liste des données de la mission</param>
	 /// <param name="dateHours"> liste des dates/heures de prélèvement</param>
	 /// <param name="dateHours"> position des données de Mission</param>
		int extraireDataMission(list<float> &datas , list<string> &dateHours,int &pos, string typeMission);

	 /// Méthode permettant de supprimer le paquet traité dans la liste des paquets
	 /// recus
	 /// Elle DOIT être utilisée après traitement du paquet.
		void supprimerPaquet();


    protected:
	/**
	 * déclaration des constantes d'erreur
	 */
		static string ERR_CHECKSUM;
		static string ERR_FORMAT;
	/**
	 * déclaration de constantes protocole
	*/
		static int pause;

	/**
	 * nombre de paquets constituant l'information
	 */
		int nbrePaquets;
	/**
	 * numéro du paquet véhiculant l'information
	 */
		int numPaquet;
	/**
	 * tableau de 100 octets à transmettre (complété par des 0)
	 */
		char tableau[100]; 
		list<vector<char>> received;

		void calculerChecksum(char & PF, char & pf);
		bool verifierChecksum();
		void tramerMission(Message* message, int nbrePaquets, int numPaquet);
		void tramerStatus(Message* message, int nbrePaquets, int numPaquet);
		void tramerMesure(Message* message, int nbrePaquets, int numPaquet);
		unsigned char calculerNombrePaquets(Message * message);
		void extraireCommande();
		void extraireParametres();
		/// Cette méthode permet d'ajouter les données de l'ordinateur de bord à la trame.
		/// </summary>
		/// <param name="aposition">Position où doivent être insérées les informations.</param>
		void ajouterDataOrdiBord(Message* amessage, unsigned int &aposition);

		/// <summary>
		/// Cette méthode permet d'ajouter les données de la batterie à la trame.
		/// </summary>
		/// <param name="aposition">Position où doivent être insérées les informations.</param>
		void ajouterDataBattery(Message* amessage, unsigned int &aposition);

		/// <summary>
		/// Cette méthode permet d'ajouter les données d'état de l'instrument à la trame.
		/// </summary>
		/// <param name="aposition">Position où doivent être insérées les informations.</param>
		void ajouterStatusInst(Message* amessage, unsigned int &aposition);

		/// <summary>
		/// Cette méthode permet d'ajouter les données de température du cube et de reboot (nombre et date du dernier) à la trame.
		/// </summary>
		/// <param name="amessage">Contenant des informations.</param>
		/// <param name="aposition">Position où doivent être insérées les informations.</param>
		void ajouterStatusCube(Message* amessage, unsigned int &aposition);

};

#endif /* PROTOCOLE_H */


