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
	short umidade;
	short temperatura;
	short luminosidade;
} info;

Comunicacao com = NULL;

int iniciar(char* porta) {
	com = Comunicacao(porta);
	return com.iniciar();
}
int ler() {
	int resultado = EXIT_FAILURE;
	char ci = 0, cf = 0;
	resultado = com.ler((char*) &ci, sizeof(ci)); //manda ler e capta o resultado
	if (resultado == EXIT_SUCCESS && (ci == 'I')) { //se o resultado for sucesso e ele tiver encontrado o i
		resultado = com.ler((char*) &info, sizeof(info)); //vai ler o conteudo de dados depois do i na estrutura
		if (resultado == EXIT_SUCCESS) {  //se leu os dados ok
			resultado = com.ler((char*) &cf, sizeof(cf)); //o resultado sera a leitura do f
			if (resultado == EXIT_SUCCESS && (cf == 'F')) { //se leu tudo certinho, vai imprimir
				resultado = EXIT_SUCCESS;
			}

		}
	}
	return resultado;
}
int getId() {
	return info.id;
}
int getUmidade() {
	return info.umidade;
}
int getTemperatura() {
	return info.temperatura;
}
int getLuminosidade() {
	return info.luminosidade;
}
int finalizar() {
	return com.finalizar();
}

