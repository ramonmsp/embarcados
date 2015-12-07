/*
 * Extern.cpp
 *
 *  Created on: 03/12/2015
 *      Author: root
 */

#include <Comunicacao.h>
#include "Extern.h"
#include <cstdlib>

struct InfoRF {
	short id;
	short batimentos;
	short temperatura;
	bool movimento;
}infoRF;

Comunicacao com = NULL;

int iniciar(char* porta){
	com = Comunicacao(porta);
	return com.iniciar();
}
int ler(){
	int resultado = EXIT_FAILURE;
	char ci = 0, cf = 0;
	if (com.ler(&ci, sizeof(ci))){
		if (com.ler((char*) &infoRF, sizeof(InfoRF)) == 0){
			if((com.ler(&cf, sizeof(char)) == 0) && (cf == 'F')){
				resultado = EXIT_SUCCESS;
			}

		}
	}
	return resultado;
}
int getId(){
	return infoRF.id;
}
int getBatimentos(){
	return infoRF.batimentos;
}
int getTemperatura(){
	return infoRF.temperatura;
}
int getMovimento(){
	return infoRF.movimento;
}
int finalizar(){
	return com.finalizar();
}


