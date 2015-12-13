package br.edu.ifba.embarcados.drivervigilancia.asincexec;

import java.util.ArrayList;
import java.util.List;

import br.edu.ifba.embarcados.drivervigilancia.conector.FabricaConectores;
import br.edu.ifba.embarcados.drivervigilancia.conector.IComunicacaoSensores;
import br.edu.ifba.embarcados.drivervigilancia.mail.JavaMailApp;
import br.edu.ifba.embarcados.drivervigilancia.movimento.Movimento;
import br.edu.ifba.embarcados.drivervigilancia.sirene.Inalterado;
import br.edu.ifba.embarcados.drivervigilancia.sirene.Sirene;
import br.edu.ifba.embarcados.drivervigilancia.sound.AlarmSound;

public class AsincExec implements Runnable{
	
	private String porta;
	private boolean continuar = true;
	private List<IListenerAcelerometro> listeners;
	private Sirene frame = new Sirene();
	private Inalterado tela = new Inalterado();
	private Movimento mov = new Movimento();
	private boolean flag = true;	

	
	public AsincExec(String porta) {
		this.porta = porta;
		listeners = new ArrayList<IListenerAcelerometro>();
		
	}
	public void addListener(IListenerAcelerometro listener){
		listeners.add(listener);
	}

	private void stopFlag(){
		this.flag=false;
	}
	
	public void stopThread(){
		this.continuar = false;
	}
	
	@Override
	public void run() {
		
		IComunicacaoSensores conector = FabricaConectores.getConector();
		if(conector.iniciar(porta) == 0) {
			this.continuar = true;
			while(continuar){
				conector.ler();
				if(flag){
							mov.setPrimeirosAcel(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ());
							mov.setPrimeirosGiro(conector.getGiroX(), conector.getGiroY(), conector.getGiroZ());
							stopFlag();
						}
						
						if(mov.verificaAcel(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ()) ||
								mov.verificaGiro(conector.getGiroX(), conector.getGiroY(), conector.getGiroZ())
								){
							if(tela.isVisible() && !frame.isVisible())
								soarAlarme();
							System.out.println("-------------------- Mexeu --------------------------");
							System.out.println("Acel");
							notificar(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ());
							System.out.println("Giro");
							notificar(conector.getGiroX(), conector.getGiroY(), conector.getGiroZ());
							
							stopThread();
						}else{
							if(!tela.isVisible())
								vigiarObjeto();
							System.out.println("Acel");
							notificar(conector.getAcelX(), conector.getAcelY(), conector.getAcelZ());
							System.out.println("Giro");
							notificar(conector.getGiroX(), conector.getGiroY(), conector.getGiroZ());
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
	private void soarAlarme(){
		tela.setVisible(false);		
		frame.setVisible(true);
		AlarmSound.audio("alarme_001.mp3");
		AlarmSound.audio("alarme_002.mp3");
		JavaMailApp.sendMail();
			
	}
	private void vigiarObjeto(){
		tela.setVisible(true);
	}
	
	
}
