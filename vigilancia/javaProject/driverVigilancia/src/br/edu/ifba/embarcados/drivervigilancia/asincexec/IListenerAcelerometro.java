package br.edu.ifba.embarcados.drivervigilancia.asincexec;

public interface IListenerAcelerometro {
	
	public void notificarMovimento(int x, int y, int z);
	public void notificarVibração(int tap);

}
