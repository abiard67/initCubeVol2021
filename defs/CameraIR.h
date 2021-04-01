/*                                                        
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*                                  
 * File:   CameraIR.h
 * Author: snir2g2
 *                           
 * Created on 14 mars 2019, 17:40
 */

#ifndef CAMERAIR_H
#define CAMERAIR_H
#include "../defs/Instrument.h"
#include "../defs/I2C.h"

#define POWERCTLREG 0x00
#define RESETREG 0x01
#define THERMREG 0x0E
#define STATREG 0x04
#define FIRSTPIXREG 0x80
#define NORMALFONCT 0x00
#define SLEEPFONCT 0x10
#define STAND_BYFONCT 0x20
#define INITIALRST 0x3F

using namespace std;

/**
 * En situation de mission, cet instrument transmet une temp�rature moyenne au segment sol.
 * Dans un contexte de mesure exceptionnelle, cet instrument peut transmettre un tableau de pixels.
 */
class CameraIR : public Instrument, public I2C {
public:
    CameraIR();
    CameraIR(const CameraIR& orig);
    virtual ~CameraIR();

    /// <summary>
    /// Cette m�thode permet de lire une moyenne de temp�rature sur un certain nombres de pixels en vue d'effectuer une mission.
    /// La valeur de retour indique la pr�sence ou non d'une erreur.
    /// </summary>
    /// <param name="arayon">rayon en nombre de pixels</param>
    int lireTemperature(int rayon);
    void setDateMesure(string dateHour);
    /// <summary>
    /// Cette m�thode permet de capturer l'ensemble des pixels de la cameraIR sur demande.
    /// elle est sp�cifique � cet instrument.
    /// </summary>
    int obtenirPixels();
    void activer();
    void desactiver();
    float *getPixels();
    float getMoyenne();
    int faireMesure(char arg = -1);
    float* obtenirMesure();

private:
    float pixels[64];
    float moyenne;
    Mode mode;
    float TempInst;
    /// <summary>
    /// Cette methode permet de convertir l'octet re�u en temperature.
    /// En effet, la camera IR choisie a une resolution de 12 bits et une resolution pour
    /// les pixels de 0.25 entre 0�C et 80�C
    /// </summary>
    /// <param name="aoctetLow">La camera IR permet de stocker la temperature sur 2 octets. </param>
    /// <param name="aoctetHigh">La camera IR permet de stocker la temperature sur 2 octets. </param>
private:
    float calculerTemperature(char aoctetLow, char aoctetHigh);
    /// <summary>
    /// Cette methode permet de convertir l'octet re�u en temperature.
    /// En effet, la camera IR choisie a une resolution de 12 bits et une resolution pour
    /// le thermistore de 0.0625 entre -20�C et 80�C
    /// </summary>
    /// <param name="aoctetLow">La camera IR permet de stocker la temperature sur 2 octets. </param>
    /// <param name="aoctetHigh">La camera IR permet de stocker la temperature sur 2 octets. </param>
private:
    float calculerTempInst(char aoctetLow, char aoctetHigh);

protected:
    void obtenirMode();
    void obtenirTempInst();
};

#endif /* CAMERAIR_H */                                                          
