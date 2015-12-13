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

struct Leitura { //struct (estrutura de dados) e usado pra dar mais performance, ja q os dados n serao enviados um a um
	short acelX, acelY, acelZ, gyroX, gyroY, gyroZ, stateTap; //aqui sera do tipo short pq o int do pc usa 4 bytes, mas o que vem do arduino eh de 2 bytes;
	//o tipo short usa tbm 2 bytes e, por isso, vai ser compativel....
	//int giroX, giroY, giroZ;
};

//instanciando globalmente Eixos e Comunicacao para uso depois
Leitura leitura;
Comunicacao com = NULL;



int iniciar(char* porta) {
	com = Comunicacao(porta);
	return com.iniciar();
}
int ler() {
	char ci, cf;

	//realizar a leitura do caractere i que representa o inicio
	int resultado = com.ler((char*) &ci, sizeof(ci)); //manda ler e capta o resultado
	if (resultado == EXIT_SUCCESS && (ci == 'I')) { //se o resultado for sucesso e ele tiver encontrado o i
		resultado = com.ler((char*) &leitura, sizeof(leitura)); //vai ler o conteudo de dados depois do i na estrutura
		if (resultado == EXIT_SUCCESS) {  //se leu os dados ok
			resultado = com.ler((char*) &cf, sizeof(cf)); //o resultado sera a leitura do f
			if (resultado == EXIT_SUCCESS && (cf == 'F')) { //se leu tudo certinho, vai marcar o resultado como sucesso
				resultado = EXIT_SUCCESS;
		}
	  }
	}

	return resultado;
}

int getAcelX(){
	return leitura.acelX;
}
int getAcelY(){
	return leitura.acelY;
}
int getAcelZ(){
	return leitura.acelZ;
}

int getGiroX(){
	return leitura.gyroX;
}
int getGiroY(){
	return leitura.gyroY;
}
int getGiroZ(){
	return leitura.gyroZ;
}

int getTap(){
	return leitura.stateTap;
}
int finalizar(){
	return com.finalizar();
}
