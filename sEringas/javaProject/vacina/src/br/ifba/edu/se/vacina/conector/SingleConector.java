package br.ifba.edu.se.vacina.conector;

import java.util.concurrent.Semaphore;

import br.ifba.edu.se.vacina.IComunicacaoRF;
import br.ifba.edu.se.vacina.Informacao;

public class SingleConector {

	private static final String PORTA = "/dev/ttyUSB0";
	private static IComunicacaoRF comRF = null;
	private static Informacao info;

	private static Semaphore semaforo;

	public static void iniciarComunicacaoRF(String libPath) {
		info = new Informacao();
		comRF = FabricaConectores.getConector(libPath);
		if (comRF.iniciar(PORTA) == 0) {
			System.out.println("Acesso a sensores iniciado com sucesso.");
			dispensarPrimeirasLeituras();
			semaforo = new Semaphore(1, true);
		} else {
			System.out.println("Não tem acesso aos sensores.");
		}
	}

	public static int ler() {
		try {
			semaforo.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		int resultado = comRF.ler();

		if (resultado == 0) {
			info.setTemperatura(comRF.getTemperatura());
			info.setBatimentos(comRF.getBatimentos());
			info.setMovimentos(comRF.getMovimento());
		}
		semaforo.release();
		return resultado;
	}

	// segunda unidade [sem semaforo]
	// public static IComunicacaoRF getConector() {
	// return comRF;
	// }

	public static void dispensarPrimeirasLeituras() {

		for (int i = 0; i < 10; i++) {
			comRF.ler();
			System.out.println("dispensando leitura [B/T/M]"
					+ comRF.getBatimentos() + "/" + comRF.getTemperatura()
					+ "/" + comRF.getMovimento());

			try {
				// segunda unidade 1000
				Thread.sleep(50);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public static Informacao getInformacao() {
		Informacao info_ = new Informacao();

		try {
			semaforo.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		info_.setBatimentos(info.getBatimentos());
		info_.setMovimentos(info.getMovimentos());
		info_.setTemperatura(info.getTemperatura());

		semaforo.release();

		return info_;
	}

	public static void finalizar() {
		comRF.finalizar();
	}
}