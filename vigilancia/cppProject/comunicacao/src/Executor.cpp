/*
 * Executor.cpp
 *
 *	Testa a comunicacção com o arduino, retornando
 *	e exibindo valores dos exitos do acelerometro.
 *  Created on: 15/10/2015
 *      Author: Ramon Maciel
 */
#include "Comunicacao.h"
#include "iostream"
using namespace std;
struct Eixos {
  short acelX, acelY, acelZ;
};

int main(int argc, char **argv) {

	//criar uma instancia da classe de comunicação
	Comunicacao com = Comunicacao("/dev/ttyUSB2");
	//inicia a comunicacao testando para o sucesso
	if (com.iniciar() == EXIT_SUCCESS) {
		char ci, cf;
		Eixos eixos;
		//enquanto estiver executando
		while(true){
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
					cout << "X = " << eixos.acelX << endl;
					cout << "Y = " << eixos.acelY << endl;
					cout << "Z = " << eixos.acelZ << endl;

				}
			}
		}
		Sleep(100);
		}
	}

	return EXIT_SUCCESS;
}



