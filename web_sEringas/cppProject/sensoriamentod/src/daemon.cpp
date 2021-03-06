/*
 * daemon.cpp
 *
 *
 * Leitor de  sensores que executa em background
 * no linux, Pode ser iniciado e parado
 * a partir de linha de comando
 *
 *
 *  Created on: 07/01/2016
 *      Author: Randler Ferraz
 */
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>

#include "../includes/comunicacao.h"

using namespace std;

#define ARQUIVO_LOG 	"/home/randler/arquivos_initid/sensoriamento.log"
#define ARQUIVO_PIPE 	"/home/randler/arquivos_initid/sensoriamento_p"
#define PORTA			"/dev/ttyACM0"

bool continuar = true;
int sensores = 0;

Comunicacao com = NULL;

//------------------------------------------ DAEMONIZE ---------------------------------------------------

int daemonize() {
	int resultado = EXIT_SUCCESS;

	pid_t daemon_id = 0;
	pid_t sid = 0;

	// PASSO 1: criar umm processo clonado a partir do main
	daemon_id = fork();
	if (daemon_id < 0) {
		//se flahar, o id do processo eh menos que 0
		cout << "Falha de criação do daemon!" << endl;

		//nao faz nada não desiste da execução
		resultado = EXIT_FAILURE;
	} else {
		/**se o daemon for criado, finaliza o processo
		 * original -> O teste condicional abaixo
		 * garante que somente sera finalizado o processo original
		 *
		 */

		if (daemon_id > 0) {
			cout << "Daemon criado! Saindo do processo principal" << endl;

			exit(0);
		}

		// configura sessao de execucao do daemon
		umask(0);

		sid = setsid();
		if (sid < 0) {
			exit(1);
		}

		// desliga os recursos de entrada e saida de dados
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}

	return resultado;
}


//------------------------------------------ FUNCAO DE PIPE ----------------------------------------------

bool pipeIniciado() {
	// cria o arquivo de PIPE
	// arquivo de alto desempenho, eh um produtor consumidor
	// no caso da distribuição ELEMENTARY deve ser feito a permissao com - 0x666 -
	int resultado = mkfifo(ARQUIVO_PIPE, 0x666);

	return (resultado != -1);

}

// ----------------------------------------- ENVIAR PARA PIPE -------------------------------------------------

int enviarParaPipe(int sensores) {
	int bytes = 0;

	//abrir o PIPE (abrir arquivo)
	int apipe = open(ARQUIVO_PIPE, O_RDWR);

	if (apipe != -1) {

		//converter sensores inteiros para string
		// a integracao funciona mehlor com strings
		stringstream ss;
		ss << sensores;
		string strSensores = ss.str();

		// escreve a string de sensores do PIPE
		bytes = write(apipe, strSensores.c_str(), strSensores.length());
	}

	// fechar o PIPE
	close(apipe);

	return bytes;
}

// ----------------------------------------- LER SENSORES -----------------------------
int lerSensores() {

	int sensores = -1;
		char ci = 0, cf = 0;

		if ((com.ler(&ci,sizeof(char)) == 0) && (ci == 'I')) {
			int is = 0;
			if (com.ler((char*) &is, sizeof(is)) == 0) {
				if ((com.ler(&cf,sizeof(char)) == 0) && (cf == 'F')) {
					 sensores = is;
				}
			}
		}

	return sensores;
}

// ----------------------------------------- TRATAR SINAL ------------------------------------
void tratarSinal(int sinal) {
	// tratamento para os sinais de parada do daemon (o daemon deve parar)
	switch (sinal) {
	case SIGHUP:
		continuar = false;
		break;
	case SIGTERM:
		continuar = false;
		break;
	case SIGQUIT:
		continuar = false;
		break;
	default:
		break;
	}

}

// ----------------------------------------- TRATAMENTO DE SINAIS ----------------------------

void iniciarTratamentoSinais() {
	//mapeamento entre sinal e funcao de tratamento de sinais
	signal(SIGHUP, tratarSinal);
	signal(SIGTERM, tratarSinal);
	signal(SIGINT, tratarSinal);
	signal(SIGQUIT, tratarSinal);
}

//------------------------------------------ MAIN ------------------------------------------------------

int main(int arg, char* argv[]) {

	// se for possivel criar o daemon
	if(daemonize() == EXIT_SUCCESS){
		// inicia-se o tratamento de sinais
		iniciarTratamentoSinais();

		// e o log para registro de operacoes
		ofstream log(ARQUIVO_LOG, ios_base::out | ios_base::app);
		log << "Arquivo de log iniciado!" << endl;


		//inicia comunicacao com o arduino
		com = Comunicacao(PORTA);
		if(com.iniciar() != 0){
			log << "Falha de inicializacao da comunicacao com sensores" << endl;
			exit(1);
		}

		log << "Pipe sendo criado" << endl;
		if(!pipeIniciado()){
			log << "Falha na inicializacao do PIPE" << endl;
			exit(2);
		}



		// executa em loop interrompivel...
		continuar = true;
		while(continuar){
			// ... a leitura dos sensores
			int sensores = lerSensores();

			log << "Enviando sensores: " << sensores << endl;

			// ... e o envio para o PIPE
			enviarParaPipe(sensores);

			sleep(1);
		}

		// remove o arquivo de PIPE apos uso/finalizacao
		unlink(ARQUIVO_PIPE);

		//finaliza a comunicacao com o arduino
		com.finalizar();

		log << "Daemon de sensoriamento finaliado" << endl;
	}
	return 0;
}

// startar pela linha de comando -> CAMINHO   chmod+x init.d   ./init.d status    ./init.d start    tail -f CAMINHO_SALVO/sensoriamentod.log
