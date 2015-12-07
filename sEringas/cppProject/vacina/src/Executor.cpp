/*
 * Executor.cpp
 *
 *  Created on: 26/11/2015
 *      Author: root
 */
#include <iostream>
#include <Comunicacao.h>

using namespace std;

struct InfoRF {
	short id;
	short batimentos;
	short temperatura;
	bool movimento;
};

int main(int argc, char **argv) {

	InfoRF info = {0};
	Comunicacao com("/dev/ttyUSB0");
	com.iniciar();


	while(true){
		if(com.ler((char*) &info, sizeof(InfoRF)) == 0){
			cout << "id = " << info.id << endl;
			cout << "temp = " << info.temperatura << endl;
			cout << "bat = " << info.batimentos<< endl;
			cout << "mov = " << info.movimento<< endl;

		}

		Sleep(50);
	}


	return 0;
}





