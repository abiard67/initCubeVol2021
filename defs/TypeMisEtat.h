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
	public: static string TEMPCELSIUS;
	/**
	 * La grandeur mesurée ou à mesurer est une température.
	 */
	public: static string TEMPERATURE;
	/**
	 * Demande ou transmission des pixels d'une image
	 */
	public: static string PIXEL;
	/**
	 * Périodicité avec laquelle une activité doit être effectuée
	 */
	public: static string PERIOD;
	/**
	 * Durée d'une activité
	 */
	public: static string DURATION;
	/**
	 * Date de début de mission ou date à bord ou date de dernier redémarrage
	 */
	public: static string DATETIME;
	/**
	 * Stockage libre en Mio
	 */
	public: static string STOCKMO;
	/**
	 * Stockage occupé en pourcentage
	 */
	public: static string STOPOURCENT;
	/**
	 * Quantité RAM libre en Mio
	 */
	public: static string RAMMO;
	/**
	 * Quantité RAM occupé en pourcentage
	 */
	public: static string RAMPOURCENT;


	/**
	 * Appareil allumé
	 */
	public: static string ON;
	/**
	 * Appareil éteint
	 */
	public: static string OFF;
	/**
	 * Signalisation d'une erreur de fonctionnement
	 */
	public: static string ERROR;
	/**
	 * Mode veille de l'appareil
	 */
	public: static string SLEEP;
	/**
	 * L'appareil est prêt à être réveillé par une requête
	 */
	public: static string STANDBY;
	/**
	 * L'appareil est en fonctionnement normal et consomme de l'énergie
	 */
	public: static string NORMAL;
	/**
	 * Permet d'indiquer le niveau de charge de la batterie en %.
	 */
	public: static string CHARGE;
	/**
	 * Permet d'indiquer la tension de la batterie en V.
	 */
	public: static string VOLTAGE;
	/**
	 * Permet d'indiquer le courant de la batterie en mA.
	 */
	public: static string AMPERAGE;
	/**
	 * Permet d'indiquer que la batterie est en charge
	 */
	public: static string LOAD;
	/**
	 * Permet d'indiquer le nombre de redémarrage depuis le dernier contact
	 */
	public: static string REBOOT_NUMBER;
	/**
	 * Permet d'indiquer une trame contenant une image
	 */
	public: static string IMG;
};

#endif
