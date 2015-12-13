package br.edu.ifba.embarcados.drivervigilancia.movimento;

public interface IMovimento {
	
	public boolean verificaAcel(int x, int y, int z);
	public boolean verificaGiro(int x, int y, int z);
	public void setPrimeirosAcel(int x, int y, int z);
	public void setPrimeirosGiro(int x, int y, int z);
	public boolean podeLer(int x, int y, int z);
	public  boolean getTap(int tap);

}
