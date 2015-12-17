package br.ifba.edu.se.vacina;


public class Informacao {

	private int umidade;
	private int luminosidade;
	private int temperatura;

	public Informacao() {
	}

	public Informacao(int umidade, int luminosidade, int temperatura) {
		this.umidade = umidade;
		this.luminosidade = luminosidade;
		this.temperatura = temperatura;
	}

	public int getUmidade() {
		return umidade;
	}

	public void setUmidade(int umidade) {
		this.umidade = umidade;
	}

	public int getLuminosidade() {
		return luminosidade;
	}

	public void setLuminosidade(int luminosidade) {
		this.luminosidade = luminosidade;
	}

	public int getTemperatura() {
		return temperatura;
	}

	public void setTemperatura(int temperatura) {
		this.temperatura = temperatura;
	}

}
