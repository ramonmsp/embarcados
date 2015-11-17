package br.edu.ifba.embarcados.drivervigilancia;

import br.edu.ifba.embarcados.drivervigilancia.asincexec.IListenerAcelerometro;

public class ListenerAcelerometro implements IListenerAcelerometro{

	@Override
	public void notificarMovimento(int x, int y, int z) {
		System.out.println("X = " + x);
		System.out.println("Y = " + y);
		System.out.println("Z = " + z);		
	}

	@Override
	public void notificarVibração(int tap) {
		if (tap == 1)
		System.out.println("Objeto foi tocado");
		
	}
	
}
