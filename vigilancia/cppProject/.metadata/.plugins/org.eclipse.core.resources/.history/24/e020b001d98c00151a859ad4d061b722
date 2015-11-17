/*
 * Comunicacao.cpp
 *
 *  Created on: 08/10/2015
 *      Author: Ramon e Randler
 */

#include "Comunicacao.h"
#ifdef __linux__
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#endif


short primMaiorAcelX, primMaiorAcelY, primMaiorAcelZ, primMaiorGiroX, primMaiorGiroY, primMaiorGiroZ;
short primMenorAcelX, primMenorAcelY, primMenorAcelZ, primMenorGiroX, primMenorGiroY, primMenorGiroZ;

Comunicacao::Comunicacao(char* porta){
	hPorta = 0;
	this->porta = porta;
}

int Comunicacao::iniciar(){
	int resultado = EXIT_SUCCESS;
#if _WIN32 ||_WIN64
	//abrindo a porta para leitura e escrita, open_existing so abre se ja existir
	hPorta = CreateFile(porta, GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL);
	//para o caso de nao conseguir realizar o CreateFile, dar retornno de erro do sistema
	if (hPorta == INVALID_HANDLE_VALUE){
		resultado = GetLastError();
	} else {
		//configuracao da porta
		DCB dcb;//estrutura de dados q esta na api de acesso a portas seriais do windows
		//zerar bytes da dcb
		memset(&dcb, 0, sizeof(dcb));
		//informa o tamanho do dcb
		dcb.DCBlength = sizeof(dcb);
		dcb.BaudRate = CBR_9600;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		dcb.ByteSize = 8;

		if (!SetCommState(hPorta, &dcb)){
			resultado = GetLastError();
		}
	}
#endif
#ifdef __linux__
	//abrindo as paradas tal qual no windows
	hPorta = open(porta, O_RDWR | O_NOCTTY | O_NDELAY);
	if (hPorta == -1){
		resultado = errno;//pega o ultimo erro erro
	} else {
		fcntl(hPorta, F_SETFL, 0);
	}

#endif

	Sleep(2000);

	return resultado;
}

int Comunicacao::ler(char* buffer, long unsigned int bytesParaLer){
	int resultado = EXIT_FAILURE;

	long unsigned int bytesLidos = 0;
#if _WIN32 || _WIN64
	//leia a porta e jogue os dados para dentro do buffer
	//jogue para bytesLidos a quantidade de bytes que realmente foram lidos
	ReadFile(hPorta, buffer, bytesParaLer, &bytesLidos, NULL);
#endif
#ifdef __linux__
	bytesLidos = read(hPorta, (void*)buffer, bytesParaLer);
#endif

	if(bytesLidos == bytesParaLer){
		resultado = EXIT_SUCCESS;
	}

	return resultado;
}

int Comunicacao::finalizar(){
#if _WIN32 || _WIN64
	CloseHandle(hPorta);
#endif
#ifdef __linux__
	close(hPorta);
#endif

	return EXIT_SUCCESS;
}

short Comunicacao::verificaAcel(short x, short y, short z){
	int saida =0;
	if((x < primMenorAcelX || x > primMaiorAcelX) &&
			(y < primMenorAcelY || y > primMaiorAcelY) &&
			(z < primMenorAcelZ || z > primMaiorAcelZ)){
		saida = 1;
	}
	return saida;
}


short Comunicacao::verificaGiro(short x, short y, short z){
	short saida =0;
	if((x < primMenorGiroX || x > primMaiorGiroX) &&
			(y < primMenorGiroY || y > primMaiorGiroY) &&
			(z < primMenorGiroZ || z > primMaiorGiroZ)){
		saida = 1;
	}
	return saida;

};
void Comunicacao::setPrimeiroAcel(short X, short Y, short Z){
	primMaiorAcelX = X+30;
	primMaiorAcelY = Y+30;
	primMaiorAcelZ = Z+30;

	primMenorAcelX = X-30;
	primMenorAcelY = Y-30;
	primMenorAcelZ = Z-30;
};

void Comunicacao::setPrimeiroGiro(short X, short Y, short Z){
	primMaiorGiroX = X+50;
	primMaiorGiroY = Y+50;
	primMaiorGiroZ = Z+50;

	primMenorGiroX = X-50;
	primMenorGiroY = Y-50;
	primMenorGiroZ = Z-50;
};
bool Comunicacao::getTap(short tap){
	return !(tap==0);
}











