package br.edu.ifba.embarcados.drivervigilancia.asincexec;

import java.util.ArrayList;
import java.util.List;

import br.edu.ifba.embarcados.drivervigilancia.conector.FabricaConectores;
import br.edu.ifba.embarcados.drivervigilancia.conector.IComunicacaoSensores;

public class AsincExec implements Runnable{
	
	private String porta;
	private boolean continuar;
	private List<IListenerAcelerometro> listeners;
	
	public AsincExec(String porta) {
		this.porta = porta;
		listeners = new ArrayList<IListenerAcelerometro>();
		
	}
	public void addListener(IListenerAcelerometro listener){
		listeners.add(listener);
	}

	public void setContinuar(boolean continuar){
		this.continuar = continuar;
	}
	
	@Override
	public void run() {
		
		IComunicacaoSensores conector = FabricaConectores.getConector();
		if(conector.iniciar(porta) == 0) {
			
			continuar = true;
			
			while(continuar){
				if (conector.ler() == 0) {
					System.out.println("Acel");
					notificar(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ());
					System.out.println("Giro");
					notificar(conector.getGiroX(), conector.getGiroY(), conector.getGiroZ());
				}
				else{
					System.out.println("Mexeu");
				}
				
				
				
					try {
						Thread.sleep(300);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
	
			}
			conector.finalizar();
		}

		
	}
	
	private void notificar(int x, int y, int z){
		for (IListenerAcelerometro listener : listeners) {
			listener.notificarMovimento(x, y, z);
		}
	}
}
