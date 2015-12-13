package br.edu.ifba.embarcados.drivervigilancia.movimento;

public class Movimento implements IMovimento {
	
	private static int primMenorAcelX;
	private static int primMenorAcelY;
	private static int primMenorAcelZ;
	private static int primMenorGiroX;
	private static int primMenorGiroY;
	private static int primMenorGiroZ;
	
	private static int primMaiorAcelX;
	private static int primMaiorAcelY;
	private static int primMaiorAcelZ;
	private static int primMaiorGiroX;
	private static int primMaiorGiroY;
	private static int primMaiorGiroZ;
	

	@Override
	public boolean verificaAcel(int x, int y, int z) {
		boolean saida = false;
		if((x < primMenorAcelX || x > primMaiorAcelX) &&
				(y < primMenorAcelY || y > primMaiorAcelY) &&
				(z < primMenorAcelZ || z > primMaiorAcelZ)){
			saida = true;
		}
		return saida;
	}

	@Override
	public boolean verificaGiro(int x, int y, int z) {
		boolean saida = false;
		if((x < primMenorGiroX || x > primMaiorGiroX) &&
				(y < primMenorGiroY || y > primMaiorGiroY) &&
				(z < primMenorGiroZ || z > primMaiorGiroZ)){
			saida = true;
		}
		return saida;
	}

	@Override
	public void setPrimeirosAcel(int x, int y, int z) {
		primMaiorAcelX = x+50;
		primMaiorAcelY = y+50;
		primMaiorAcelZ = z+50;

		primMenorAcelX = x-50;
		primMenorAcelY = y-50;
		primMenorAcelZ = z-50;
		
	}

	@Override
	public void setPrimeirosGiro(int x, int y, int z) {
		primMaiorGiroX = x+500;
		primMaiorGiroY = y+500;
		primMaiorGiroZ = z+500;

		primMenorGiroX = x-500;
		primMenorGiroY = y-500;
		primMenorGiroZ = z-500;
		
	}

	@Override
	public boolean podeLer(int x, int y, int z) {
		boolean saida = false;
		if(((x != 0) && (y != 0) && (z != 0))  && 
				!(x > 300 || x < -300) &&  !(y > 300 || y < -300) && !(z > 300 || z < -300)){
			saida =true;
		}		
		return saida;
	}

	@Override
	public boolean getTap(int tap) {
		return !(tap==0);
	}

}
