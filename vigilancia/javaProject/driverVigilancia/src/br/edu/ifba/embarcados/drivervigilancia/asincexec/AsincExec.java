package br.edu.ifba.embarcados.drivervigilancia.asincexec;

import java.util.ArrayList;
import java.util.List;

import br.edu.ifba.embarcados.drivervigilancia.conector.FabricaConectores;
import br.edu.ifba.embarcados.drivervigilancia.conector.IComunicacaoSensores;
import br.edu.ifba.embarcados.drivervigilancia.mail.JavaMailApp;
import br.edu.ifba.embarcados.drivervigilancia.sound.AlarmSound;

public class AsincExec implements Runnable{
	
	private String porta;
	private boolean continuar = true;
	private List<IListenerAcelerometro> listeners;
	
	public AsincExec(String porta) {
		this.porta = porta;
		listeners = new ArrayList<IListenerAcelerometro>();
		
	}
	public void addListener(IListenerAcelerometro listener){
		listeners.add(listener);
	}

	public void stopThread(){
		this.continuar = false;
	}
	
	@Override
	public void run() {
		
		IComunicacaoSensores conector = FabricaConectores.getConector();
		if(conector.iniciar(porta) == 0) {
			
			while(continuar){
				if (conector.ler() == 0) {
					System.out.println("Acel");
					notificar(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ());
					System.out.println("Giro");
					notificar(conector.getGiroX(), conector.getGiroY(), conector.getGiroZ());
				}
				else{
					System.out.println("Mexeu");
					JavaMailApp.sendMail();
					AlarmSound.audio();
					continuar = false;
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