/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sauvegarde.cpp
 * Author: Romain
 * 
 * Created on 23 juin 2020, 17:42
 */

#include <climits>
#include <sstream>
#include "../defs/Sauvegarde.h"

Sauvegarde::Sauvegarde() {
}

Sauvegarde::Sauvegarde(const Sauvegarde& orig) {
}

Sauvegarde::~Sauvegarde() {
}

bool Sauvegarde::enregistrerMesures(list<Mesure *> lesMesures) { // initialement prévu : bool Sauvegarde::enregistrerMesure(Mesure mesure);
	this->lesMesures = lesMesures;
    //pugi::xml_document doc;
    //char commandeCreer[256];
    //char xmlFile[] = "initcube.xml";
    //sprintf(commandeCreer, "touch %s", xmlFile);
    //if (doc.load_file(xmlFile)) {
    //    lireID();
    //    pugi::xpath_node nodeVal = doc.select_node("//initcube/etat/bord/temperature");
    //    nodeVal.node().attribute("seuilAlerteHaut").set_value(90);
    //    doc.save_file(xmlFile);
        return true;
    //} else {
    //    return false;
    //}
}

bool Sauvegarde::ajouterAMission() { // initialement prévu : bool Sauvegarde::ajouterAMission(Mesure mesure);
    return 0;
}

unsigned char Sauvegarde::lireID() {
    //pugi::xml_document doc;
    //char xmlFile[] = "initcube.xml";
    unsigned char cubeId;
    //if (doc.load_file(xmlFile)) {
    //    pugi::xpath_node nodeId = doc.select_node("//initcube/description/id");
    //    string intermediateId = nodeId.node().child_value();
    //    istringstream iss(intermediateId);
    //    int nb;
    //    iss >> nb;
    //    cubeId = (unsigned char) nb;
    //} else {
        cubeId = 0;
    //}
    return cubeId;
}