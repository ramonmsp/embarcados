package br.edu.ifba.embarcados.drivervigilancia.asincexec;

public interface IListenerAcelerometro {
	
	public void notificarMovimento(int x, int y, int z);
	
	// FIXME nunca utilize acentuação ou caracteres especiais ao nomear funcoes
	public void notificarVibração();

}
