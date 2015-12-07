/*
 * Extern.h
 *
 *  Created on: 03/12/2015
 *      Author: root
 */

#ifndef EXTERN_H_
#define EXTERN_H_

#ifdef __cplusplus
extern "C" {
#endif

	int iniciar(char* porta);
	int ler();
	int getId();
	int getBatimentos();
	int getTemperatura();
	int getMovimento();
	int finalizar();

#ifdef __cplusplus
}
#endif

#endif /* EXTERN_H_ */
