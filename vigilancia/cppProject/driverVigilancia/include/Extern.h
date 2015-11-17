/*
 * Extern.h
 *
 *  Created on: 15/10/2015
 *      Author: Ramon e Randler
 */

#ifndef EXTERN_H_
#define EXTERN_H_

#ifdef __cplusplus
extern "C"{
#endif

int iniciar (char* porta);
int ler();
int getAcelX();
int getAcelY();
int getAcelZ();

int getGiroX();
int getGiroY();
int getGiroZ();

short verificaAcel(short x, short y, short z);

//verifica alteração no gyro
short verificaGiro(short x, short y, short z);

//Captura o primeiro valor de entrada
void setPrimeiroAcel(short X, short Y, short Z);

void setPrimeiroGiro(short X, short Y, short Z);

bool getTap(short tap);

int finalizar();

#ifdef __cplusplus
}
#endif

#endif /* EXTERN_H_ */
