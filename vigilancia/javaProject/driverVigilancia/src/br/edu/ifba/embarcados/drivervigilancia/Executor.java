package br.edu.ifba.embarcados.drivervigilancia;

import br.edu.ifba.embarcados.drivervigilancia.asincexec.AsincExec;

public class Executor {

	public static void main(String[] args) throws InterruptedException {
		ListenerAcelerometro listener = new ListenerAcelerometro();
		
		AsincExec asinc = new AsincExec("/dev/ttyUSB0"); 
		
		asinc.addListener(listener);
		
		Thread t = new Thread(asinc);
		Thread.sleep(50000);

		t.start();
		
		// FIXME não esta parando a thread (setContinuar(false))
		//asinc.stopThread();
		t.join();
	}

}
