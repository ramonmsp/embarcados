/*
 * Executor.cpp
 *
 *Testa a comunicacao com o arduino, retornando e exibindo
 *Testa valores dos eixos do acelerometro.
 *
 *
 *
 *  Created on: 15/10/2015
 *      Author: Ramon e Randler
 */

#include "Comunicacao.h"
#include "iostream"
using namespace std;

struct Leitura { //struct (estrutura de dados) e usado pra dar mais performance, ja q os dados n serao enviados um a um
	short acelX, acelY, acelZ, gyroX, gyroY, gyroZ, stateTap; //aqui sera do tipo short pq o int do pc usa 4 bytes, mas o que vem do arduino eh de 2 bytes;
	//o tipo short usa tbm 2 bytes e, por isso, vai ser compativel....
	//int giroX, giroY, giroZ;
};

int main(int argc, char **argv) {

	//criar uma instancia da classe de comunicacao
	Comunicacao com = Comunicacao("/dev/ttyACM1"); //verificar a porta correta na interface do arduino, no linux sera diferente

	//iniciou a comunicacao
	if (com.iniciar() == EXIT_SUCCESS) {  //se foi iniciado com sucesso
		char ci, cf;
		Leitura eixos;

		while (true) {//vai fazer o loop pra pegar os resultados do loop do arduino
			//realizar a leitura do caractere i que representa o inicio
			int resultado = com.ler((char*) &ci, sizeof(ci)); //manda ler e capta o resultado
			if (resultado == EXIT_SUCCESS && (ci == 'I')) { //se o resultado for sucesso e ele tiver encontrado o i
				resultado = com.ler((char*) &eixos, sizeof(eixos)); //vai ler o conteudo de dados depois do i na estrutura
				if (resultado == EXIT_SUCCESS) {  //se leu os dados ok
					resultado = com.ler((char*) &cf, sizeof(cf)); //o resultado sera a leitura do f
					if (resultado == EXIT_SUCCESS && (cf == 'F')) { //se leu tudo certinho, vai imprimir
						cout << "Acelerômetro" << endl;
						cout << "X = " << eixos.acelX << endl;
						cout << "Y = " << eixos.acelY << endl;
						cout << "Z = " << eixos.acelZ << endl;
						cout << "Giroscópio" << endl;
						cout << "X = " << eixos.gyroX << endl;
						cout << "Y = " << eixos.gyroY << endl;
						cout << "Z = " << eixos.gyroZ << endl;
						cout << "tap: " << endl;
						cout << "Vibra:  " << eixos.stateTap << endl;

					}
				}
			}
			Sleep(200);//pra n ficar o tempo todo batendo no arduino, ele vai esperar o mesmo tempo q o arduino leva pra enviar
		}
	}

	return EXIT_SUCCESS;
}

