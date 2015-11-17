package br.edu.ifba.embarcados.drivervigilancia;

import br.edu.ifba.embarcados.drivervigilancia.asincexec.AsincExec;

public class Executor {

	public static void main(String[] args) throws InterruptedException {
		ListenerAcelerometro listener = new ListenerAcelerometro();
		
		AsincExec asinc = new AsincExec("/dev/ttyUSB0"); 
		
		asinc.addListener(listener);
		
		Thread t = new Thread(asinc);
		t.start();
		
		for(int i = 0; i<10; i++) {
			Thread.sleep(3000);
		}
		asinc.setContinuar(false);
		t.join();
	}

}
