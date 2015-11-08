/*
 * Executor.cpp
 *
 *  Created on: 29/10/2015
 *      Author: Ramon Maciel
 */

#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char**argv){

	int temperatura = 36;
	int pressaoSistolica = 8;
	int pressaoDiastolica = 12;
	int batimentos = 100;

	int info = 0;

	cout << "tam = " << sizeof(info) << endl;

	info = info | (temperatura << 24);

	info = info | (pressaoSistolica << 16);

	info = info | (pressaoDiastolica << 8);

	info = info | batimentos;


	cout << "info = " << info << endl;

	// informacao enviada pelo RF transmissor (deslocamento de bits)

	int temperaturaRec = (info & 4278190080) >> 24;
	int pressaoSistolicaRec = (info & 16711680) >> 16;
	int pressaoDiastolicaRec = (info & 65280) >> 8;
	int batimentosRec = (info & 255);
	// informacao recepcionada e decodificada pelo receptor

	cout << "Temperatura = " << temperaturaRec << endl;
	cout << "Pressão Diastólica = " << pressaoDiastolicaRec << endl;
	cout << "Pressão Sistólica = " << pressaoSistolicaRec << endl;
	cout << "Batimentos = " << batimentosRec << endl;
}

