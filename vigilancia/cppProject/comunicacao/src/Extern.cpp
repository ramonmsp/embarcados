/*
 * Extern.cpp
 *
 *	Externalização das funcoes das rotinas de acesso ao acelerometro
 *  Created on: 15/10/2015
 *      Author: Ramon Maciel
 */

#include "Extern.h"
#include "Comunicacao.h"

struct Eixos {
  short acelX, acelY, acelZ;
};
Eixos eixos;
Comunicacao com = NULL;

int iniciar(char* porta){
	com = Comunicacao(porta);
	return com.iniciar();
}
int ler(){
	char ci, cf;
		Eixos eixos;
		//enquanto estiver executando

			//realiza a leitura do caracter I (Inicio)
		int resultado = com.ler((char*)&ci, sizeof(ci));
		if ((resultado == EXIT_SUCCESS) && (ci=='I')) {
			//se a leitura de 'I' ocorrer bem
			//ler os eixos
			resultado = com.ler((char*)&eixos,sizeof(eixos));
			if (resultado == EXIT_SUCCESS) {
				resultado = com.ler((char*)&cf, sizeof(cf));
				//se a leitura de 'I' ocorrer bem
							//ler os eixos
				if ((resultado == EXIT_SUCCESS) && (cf == 'F')) {
					//se tudo for atendido, exibe os eixos do acelerometro
					resultado = EXIT_SUCCESS;
				}
			}
		}
		return resultado;

}
int getAcelX(){
	return eixos.acelX;
}
int getAcelY(){
	return eixos.acelY;
}
int getAcelZ(){
	return eixos.acelZ;
}
int finalizar(){
	return com.finalizar();
}

