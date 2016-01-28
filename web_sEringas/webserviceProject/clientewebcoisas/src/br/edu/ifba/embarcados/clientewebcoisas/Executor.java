package br.edu.ifba.embarcados.clientewebcoisas;

import br.edu.ifba.embarcados.clientewebcoisas.conector.Conector;

public class Executor {

	public static void main(String[] args) throws InterruptedException {
		Conector conector = new Conector();

		while (true) {
			Integer id = conector.getId();
			System.out.println("id = " + id);
			
			System.out.println("Sensores...");
			
			Integer umidade = conector.getUmidade();
			System.out.println("Umidade = " + umidade);
			Integer temperatura = conector.getTemperatura();
			System.out.println("Temperatura = " + temperatura);
			Integer luminosidade = conector.getLuminosidade();
			System.out.println("Luminosidade = " + luminosidade);
			
			System.out.println("Final de leitura!");
			System.out.println("...");
			
			
			Thread.sleep(1000);
		}
	}
}
