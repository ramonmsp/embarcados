package br.ifba.edu.se.vacina.leitor;

import br.ifba.edu.se.vacina.conector.SingleConector;

public class LeitorAssincrono implements Runnable {

	private boolean continuar;

	@Override
	public void run() {
		continuar = true;

		while (continuar) {

			SingleConector.ler();

			try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}

	}

	public void parar() {
		continuar = false;
	}

}
