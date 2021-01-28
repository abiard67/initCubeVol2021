#include <string>
using namespace std;

#ifndef __TypeMisEtat_h__
#define __TypeMisEtat_h__

class TypeMisEtat;

/**
 * Types liés aux informations des comptes rendus de mission et d'état du système.
 */
class TypeMisEtat
{
	/**
	 * Les températures seront données en °C.
	 */
	protected: static string TEMPCELSIUS;
	/**
	 * La grandeur mesurée ou à mesurer est une température.
	 */
	protected: static string TEMPERATURE;
	/**
	 * Demande ou transmission des pixels d'une image
	 */
	protected: static string PIXEL;
	/**
	 * Périodicité avec laquelle une activité doit être effectuée
	 */
	protected: static string PERIOD;
	/**
	 * Durée d'une activité
	 */
	protected: static string DURATION;
	/**
	 * Date de début de mission ou date à bord ou date de dernier redémarrage
	 */
	protected: static string DATETIME;
	/**
	 * Stockage libre en Mio
	 */
	protected: static string STOCKMO;
	/**
	 * Stockage occupé en pourcentage
	 */
	protected: static string STOPOURCENT;
	/**
	 * Quantité RAM libre en Mio
	 */
	protected: static string RAMMO;
	/**
	 * Quantité RAM occupé en pourcentage
	 */
	protected: static string RAMPOURCENT;


	/**
	 * Appareil allumé
	 */
	protected: static string ON;
	/**
	 * Appareil éteint
	 */
	protected: static string OFF;
	/**
	 * Signalisation d'une erreur de fonctionnement
	 */
	protected: static string ERROR;
	/**
	 * Mode veille de l'appareil
	 */
	protected: static string SLEEP;
	/**
	 * L'appareil est prêt à être réveillé par une requête
	 */
	protected: static string STANDBY;
	/**
	 * L'appareil est en fonctionnement normal et consomme de l'énergie
	 */
	protected: static string NORMAL;
	/**
	 * Permet d'indiquer le niveau de charge de la batterie en %.
	 */
	protected: static string CHARGE;
	/**
	 * Permet d'indiquer la tension de la batterie en V.
	 */
	protected: static string VOLTAGE;
	/**
	 * Permet d'indiquer le courant de la batterie en mA.
	 */
	protected: static string AMPERAGE;
	/**
	 * Permet d'indiquer que la batterie est en charge
	 */
	protected: static string LOAD;
	/**
	 * Permet d'indiquer le nombre de redémarrage depuis le dernier contact
	 */
	protected: static string REBOOT_NUMBER;
};

#endif
