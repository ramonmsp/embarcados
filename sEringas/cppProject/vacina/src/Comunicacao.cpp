/*
 * Comunicacao.cpp
 *
 *  Created on: 08/10/2015
 *      Author: ramonmaciel
 */

#include "Comunicacao.h"
#ifdef __linux__
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#endif

Comunicacao::Comunicacao(char* porta) {
	hPorta = 0;
	this->porta = porta;

}

int Comunicacao::iniciar() {

	int resultado = EXIT_SUCCESS;

#if _WIN32 || _WIN64
	hPorta = CreateFile(porta, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hPorta == INVALID_HANDLE_VALUE) {
		resultado = GetLastError();
	} else {
		// configuracao da porta
		DCB dcb;
		memset(&dcb, 0, sizeof(dcb));
		dcb.DCBlenght = sizeof(dcb);
		dcb.BaudRate = CBR_9600;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;
		dcb.ByteSize = 8;

		if(!SetCommState(Hporta, &dcb)) {
			resultado = GetLastError();
		}
	}
#endif

#ifdef __linux__
	hPorta = open(porta, O_RDWR | O_NOCTTY | O_NDELAY);
	if(hPorta == -1) {
			resultado = errno;
	} else {
		fcntl(hPorta, F_SETFL, 0);
	}


#endif
		Sleep(2000);

		return resultado;
}
int Comunicacao::ler(char* buffer, long unsigned int bytesParaLer) {
	int resultado = EXIT_FAILURE;
	long unsigned int bytesLidos = 0;
#ifdef _WIN32 || _WIN64
	ReadFile(hPorta, buff, bytesParaLer, bytesLidos, NULL);
#endif

#ifdef __linux__
	bytesLidos = read(hPorta, (void*)buffer, bytesParaLer);
#endif
	if(bytesLidos == bytesParaLer){
		resultado = EXIT_SUCCESS;
	}


	return resultado;
}

int Comunicacao::finalizar() {
#if _WIN32 || _WIN64
	CloseHandle(hPorta);

#endif
#ifdef __linux__
	close(hPorta);
#endif

	return EXIT_SUCCESS;

}




