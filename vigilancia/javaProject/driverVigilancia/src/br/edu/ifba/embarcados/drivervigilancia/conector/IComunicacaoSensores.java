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
	
	public int getTap();
	public int finalizar();
}
