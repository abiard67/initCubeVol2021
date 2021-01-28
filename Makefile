CC=g++
FLAGS=-Wall
DEFS = ./defs
LIB = ./lib
SRC = ./src
BIN = ./bin

all: $(LIB)/TypeAppareil.o $(LIB)/TypeAck.o $(LIB)/TypeCommande.o $(LIB)/TypeMisEtat.o $(LIB)/Reboot.o $(LIB)/Status.o $(LIB)/Protocole.o $(LIB)/Message.o $(LIB)/Mesure.o $(LIB)/serialib.o $(LIB)/Batterie.o $(LIB)/CameraIR.o $(LIB)/EmetteurRecepteur.o $(LIB)/Etat.o $(LIB)/Horloge.o $(LIB)/I2C.o $(LIB)/Instrument.o $(LIB)/Mission.o $(LIB)/Ordinateur.o $(LIB)/Stockage.o $(LIB)/SegmentSol.o $(LIB)/SegmentVol.o $(LIB)/Temperature.o 
	@echo "Compilation programme principal"
	$(CC) $(FLAGS) $(SRC)/main.cpp $(LIB)/TypeAppareil.o $(LIB)/TypeAck.o $(LIB)/TypeCommande.o $(LIB)/TypeMisEtat.o $(LIB)/Reboot.o $(LIB)/Status.o $(LIB)/Protocole.o $(LIB)/Message.o $(LIB)/Mesure.o $(LIB)/serialib.o $(LIB)/Batterie.o $(LIB)/CameraIR.o $(LIB)/EmetteurRecepteur.o $(LIB)/Etat.o $(LIB)/Horloge.o $(LIB)/I2C.o $(LIB)/Instrument.o $(LIB)/Mission.o $(LIB)/Ordinateur.o $(LIB)/Stockage.o $(LIB)/SegmentSol.o $(LIB)/SegmentVol.o $(LIB)/Temperature.o -std=c++14 -lpthread  -o $(BIN)/main
	@echo "Compilation terminer"

$(LIB)/Reboot.o : $(SRC)/Reboot.cpp $(DEFS)/Reboot.h 
	@echo "Compilation classe Reboot"
	$(CC) -c $(SRC)/Reboot.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/TypeCommande.o : $(SRC)/TypeCommande.cpp $(DEFS)/TypeCommande.h 
	@echo "Compilation classe TypeCommande"
	$(CC) -c $(SRC)/TypeCommande.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/TypeAck.o : $(SRC)/TypeAck.cpp $(DEFS)/TypeAck.h 
	@echo "Compilation classe TypeAck"
	$(CC) -c $(SRC)/TypeAck.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/TypeMisEtat.o : $(SRC)/TypeMisEtat.cpp $(DEFS)/TypeMisEtat.h 
	@echo "Compilation classe TypeMisEtat"
	$(CC) -c $(SRC)/TypeMisEtat.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/TypeAppareil.o : $(SRC)/TypeAppareil.cpp $(DEFS)/TypeAppareil.h 
	@echo "Compilation classe TypeAppareil"
	$(CC) -c $(SRC)/TypeAppareil.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Protocole.o : $(SRC)/Protocole.cpp $(DEFS)/Protocole.h 
	@echo "Compilation classe Protocole"
	$(CC) -c $(SRC)/Protocole.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Message.o : $(SRC)/Message.cpp $(DEFS)/Message.h 
	@echo "Compilation classe Message"
	$(CC) -c $(SRC)/Message.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/serialib.o : $(SRC)/serialib.cpp $(DEFS)/serialib.h 
	@echo "Compilation classe serialib"
	$(CC) -c $(SRC)/serialib.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Mesure.o : $(SRC)/Mesure.cpp $(DEFS)/Mesure.h 
	@echo "Compilation classe Mesure"
	$(CC) -c $(SRC)/Mesure.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Status.o : $(SRC)/Status.cpp $(DEFS)/Status.h 
	@echo "Compilation classe Status"
	$(CC) -c $(SRC)/Status.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Batterie.o : $(SRC)/Batterie.cpp $(DEFS)/Batterie.h 
	@echo "Compilation classe Batterie"
	$(CC) -c $(SRC)/Batterie.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/CameraIR.o : $(SRC)/CameraIR.cpp $(DEFS)/CameraIR.h 
	@echo "Compilation classe CameraIR"
	$(CC) -c $(SRC)/CameraIR.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/EmetteurRecepteur.o : $(SRC)/EmetteurRecepteur.cpp $(DEFS)/EmetteurRecepteur.h 
	@echo "Compilation classe EmetteurRecepteur"
	$(CC) -c $(SRC)/EmetteurRecepteur.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Etat.o : $(SRC)/Etat.cpp $(DEFS)/Etat.h 
	@echo "Compilation classe Etat"
	$(CC) -c $(SRC)/Etat.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Horloge.o : $(SRC)/Horloge.cpp $(DEFS)/Horloge.h 
	@echo "Compilation classe Horloge"
	$(CC) -c $(SRC)/Horloge.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/I2C.o : $(SRC)/I2C.cpp $(DEFS)/I2C.h 
	@echo "Compilation classe I2C"
	$(CC) -c $(SRC)/I2C.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Instrument.o : $(SRC)/Instrument.cpp $(DEFS)/Instrument.h 
	@echo "Compilation classe Instrument"
	$(CC) -c $(SRC)/Instrument.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Mission.o : $(SRC)/Mission.cpp $(DEFS)/Mission.h 
	@echo "Compilation classe Mission"
	$(CC) -c $(SRC)/Mission.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Ordinateur.o : $(SRC)/Ordinateur.cpp $(DEFS)/Ordinateur.h 
	@echo "Compilation classe Ordinateur"
	$(CC) -c $(SRC)/Ordinateur.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/Stockage.o : $(SRC)/Stockage.cpp $(DEFS)/Stockage.h 
	@echo "Compilation classe Stockage"
	$(CC) -c $(SRC)/Stockage.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/SegmentSol.o : $(SRC)/SegmentSol.cpp $(DEFS)/SegmentSol.h 
	@echo "Compilation classe SegmentSol"
	$(CC) -c $(SRC)/SegmentSol.cpp -std=c++14 -lpthread  -o $@ $(FLAGS) 

$(LIB)/SegmentVol.o : $(SRC)/SegmentVol.cpp $(DEFS)/SegmentVol.h 
	@echo "Compilation classe SegmentVol"
	$(CC) -c $(SRC)/SegmentVol.cpp -std=c++14 -lpthread  -o $@ $(FLAGS)

$(LIB)/Temperature.o : $(SRC)/Temperature.cpp $(DEFS)/Temperature.h 
	@echo "Compilation classe Temperature"
	$(CC) -c $(SRC)/Temperature.cpp -std=c++14 -lpthread  -o $@ $(FLAGS)


