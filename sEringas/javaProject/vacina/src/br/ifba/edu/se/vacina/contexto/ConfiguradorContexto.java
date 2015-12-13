package br.ifba.edu.se.vacina.contexto;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;

import br.ifba.edu.se.vacina.conector.SingleConector;
import br.ifba.edu.se.vacina.leitor.LeitorAssincrono;

import com.sun.faces.config.ConfigureListener;

public class ConfiguradorContexto extends ConfigureListener {

	private LeitorAssincrono leitor;
	private Thread tLeitor;

	@Override
	public void contextInitialized(ServletContextEvent sce) {
		super.contextInitialized(sce);
		ServletContext sc = sce.getServletContext();
		String libPath = sc.getRealPath("/WEB-INF/lib");

		SingleConector.iniciarComunicacaoRF(libPath);

		leitor = new LeitorAssincrono();
		tLeitor = new Thread(leitor);
		tLeitor.start();
	}

	@Override
	public void contextDestroyed(ServletContextEvent sce) {
		leitor.parar();
		try {
			tLeitor.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		SingleConector.finalizar();
		super.contextDestroyed(sce);
	}
}
