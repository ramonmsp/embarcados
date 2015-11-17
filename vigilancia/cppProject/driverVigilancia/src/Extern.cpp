/*
 * Extern.cpp
 *
 *Externalizacao das rotinas de acesso ao acelerometro
 *
 *
 *  Created on: 15/10/2015
 *      Author: Ramon e Randler
 */

#include <Comunicacao.h>
#include "Extern.h"
#include <cstdlib>

struct Eixos { //struct (estrutura de dados) e usado pra dar mais performance, ja q os dados n serao enviados um a um
	short acelX, acelY, acelZ, gyroX, gyroY, gyroZ, stateTap; //aqui sera do tipo short pq o int do pc usa 4 bytes, mas o que vem do arduino eh de 2 bytes;
	//o tipo short usa tbm 2 bytes e, por isso, vai ser compativel....
	//int giroX, giroY, giroZ;
};

//instanciando globalmente Eixos e Comunicacao para uso depois
Eixos eixos;
Comunicacao com = NULL;


bool flag = true;

int iniciar(char* porta) {
	com = Comunicacao(porta);
	return com.iniciar();
}
int ler() {
	char ci, cf;

	//realizar a leitura do caractere i que representa o inicio
	int resultado = com.ler((char*) &ci, sizeof(ci)); //manda ler e capta o resultado
	if (resultado == EXIT_SUCCESS && (ci == 'I')) { //se o resultado for sucesso e ele tiver encontrado o i
		resultado = com.ler((char*) &eixos, sizeof(eixos)); //vai ler o conteudo de dados depois do i na estrutura
		if (resultado == EXIT_SUCCESS) {  //se leu os dados ok
			resultado = com.ler((char*) &cf, sizeof(cf)); //o resultado sera a leitura do f
			if (resultado == EXIT_SUCCESS && (cf == 'F')) { //se leu tudo certinho, vai marcar o resultado como sucesso
				if(flag){//captura os primeiros valores para se ter valores minimos e máximos
					com.setPrimeiroAcel(eixos.acelX, eixos.acelY, eixos.acelZ);
					com.setPrimeiroGiro(eixos.gyroX, eixos.gyroY, eixos.gyroZ);
					flag=false;
					resultado = EXIT_SUCCESS;
				}
				resultado = EXIT_SUCCESS;
				if((com.verificaAcel(eixos.acelX, eixos.acelY,  eixos.acelZ) == 1)  ||
					(com.verificaGiro(eixos.gyroX, eixos.gyroY, eixos.gyroZ) == 1) ||
					(com.getTap(eixos.stateTap))){
							resultado = 505;
				}
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

int getGiroX(){
	return eixos.gyroX;
}
int getGiroY(){
	return eixos.gyroY;
}
int getGiroZ(){
	return eixos.gyroZ;
}

int getTap(){
	return eixos.stateTap;
}
int finalizar(){
	return com.finalizar();
}
