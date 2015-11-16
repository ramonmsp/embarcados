/*
 * comunicacao.h
 *
 *Prove uma classe cujos metodos possibilitam
 *Prove a comunicacao com um dispositivo controlador
 *Prove que reliza a leitura de sensores de 10 eixos
 *
 *  Created on: 08/10/2015
 *      Author: Ramon e Randler
 */

#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

#include <stdlib.h>

//diretivas de compilacao
#if _WIN32 || _WIN64
#include <windows.h>
#endif
#ifdef __linux__
#include <unistd.h>
#define Sleep(x) usleep(x * 1000);
#endif

class Comunicacao{
private:
	char* porta;

//definindo o tipo de variavel para salvar a porta a partir do SO
#ifdef __linux__
	int hPorta;
#endif
#if _WIN32 || _WIN64
	HANDLE hPorta;
#endif

public:
	//passar a porta em q o arduino est� alocado.. "COM3, COM4"
	Comunicacao(char* porta);

	//iniciar a comunicacao com a porta serial
	int iniciar();

	//realiza a leitura de um buffer a partir da porta serial
	int ler(char* buffer, long unsigned int bytesParaLer);

	//finaliza o uso da porta serial
	int finalizar();

	//verifica alteração no acel
	int verificaAcel(short x, short y, short z);
	//verifica alteração no gyro
	int verificaGiro(short x, short y, short z);
};

#endif /* COMUNICACAO_H_ */
