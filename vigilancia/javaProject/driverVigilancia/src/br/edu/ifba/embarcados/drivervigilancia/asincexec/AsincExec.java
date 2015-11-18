package br.edu.ifba.embarcados.drivervigilancia.asincexec;

import java.util.ArrayList;
import java.util.List;

import br.edu.ifba.embarcados.drivervigilancia.conector.FabricaConectores;
import br.edu.ifba.embarcados.drivervigilancia.conector.IComunicacaoSensores;
import br.edu.ifba.embarcados.drivervigilancia.mail.JavaMailApp;
import br.edu.ifba.embarcados.drivervigilancia.sirene.Inalterado;
import br.edu.ifba.embarcados.drivervigilancia.sirene.Sirene;
import br.edu.ifba.embarcados.drivervigilancia.sound.AlarmSound;

public class AsincExec implements Runnable{
	
	private String porta;
	private boolean continuar = true;
	private List<IListenerAcelerometro> listeners;
	private Sirene frame = new Sirene();
	private Inalterado tela = new Inalterado();
	
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
					tela.setVisible(true);
					System.out.println("Acel");
					notificar(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ());
					System.out.println("Giro");
					notificar(conector.getGiroX(), conector.getGiroY(), conector.getGiroZ());
				}
				else {
					try {
					tela.setVisible(false);		
					frame.setVisible(true);
					System.out.println("Mexeu");
					System.out.println("Acel");
					notificar(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ());
					System.out.println("Giro");
					notificar(conector.getGiroX(), conector.getGiroY(), conector.getGiroZ());
					AlarmSound.audio("alarme_001.mp3");
					AlarmSound.audio("alarme_002.mp3");
					JavaMailApp.sendMail();
					continuar = false;

					
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
				
				try {
					Thread.sleep(50);
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
			//listener.notificarVibração(conector.getTap());
		}
	}
}
