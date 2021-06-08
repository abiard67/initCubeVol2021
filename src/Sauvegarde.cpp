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

bool Sauvegarde::creerSauvegarde(SegmentVol* segmentVol){
	 pugi::xml_document doc;
 
 auto declarationNode = doc.append_child(pugi::node_declaration);
    declarationNode.append_attribute("version")    = "1.0";
    declarationNode.append_attribute("encoding")   = "ISO-8859-1";
    declarationNode.append_attribute("standalone") = "yes";
    pugi::xml_node Segment = doc.append_child("SegmentVol");
    pugi::xml_node Instrument = Segment.append_child("Instrument");
    pugi::xml_node Mission = Segment.append_child("Mission");
	pugi::xml_attribute periodicity = Mission.append_attribute("periodicity");
	periodicity.set_value(segmentVol->getMission()->getPeriodicity());
	pugi::xml_attribute duration = Mission.append_attribute("duration");
	duration.set_value(segmentVol->getMission()->getDuration());
    pugi::xml_node Ordinateur_de_bord = Segment.append_child("Ordinateur_de_bord");
    pugi::xml_node Batterie = Segment.append_child("Batterie");
   
 
 doc.save_file("Save2.xml");
 return true;
}

bool Sauvegarde::chargerContexte(SegmentVol* segmentVol){

	return true;
}
bool Sauvegarde::supprimerSaugegarde(){

	return true;
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