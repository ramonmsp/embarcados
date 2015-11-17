package br.edu.ifba.embarcados.drivervigilancia.conector;

import com.sun.jna.Library;

public interface IComunicacaoSensores extends Library {
	
	public int iniciar(String porta);
	public int ler();
	public int getAcelX();
	public int getAcelY();
	public int getAcelZ();
	
	public int getGiroX();
	public int getGiroY();
	public int getGiroZ();
	
	public short verificaAcel(short x, short y, short z);

	//verifica alteração no gyro
	public short verificaGiro(short x, short y, short z);

	//Captura o primeiro valor de entrada
	public void setPrimeiroAcel(short X, short Y, short Z);

	public void setPrimeiroGiro(short X, short Y, short Z);

	public boolean getTap(short tap);
	public int finalizar();
}
