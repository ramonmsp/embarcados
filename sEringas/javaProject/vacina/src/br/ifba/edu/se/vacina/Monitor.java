package br.ifba.edu.se.vacina;

import java.util.ArrayList;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;

import org.primefaces.component.carousel.Carousel;
import org.primefaces.model.chart.MeterGaugeChartModel;

import br.ifba.edu.se.vacina.conector.SingleConector;

@ManagedBean(name = "monitor")
public class Monitor {

	private MeterGaugeChartModel modeloMedidorTemperatura;
	private MeterGaugeChartModel modeloMedidorUmidade;
	private MeterGaugeChartModel modeloMedidorLuminosidade;
	private Informacao info = new Informacao();
	private Carousel carrossel;
	

	
	

	@PostConstruct
	public void iniciar() {
		configurarMedidores();
	}

	private void configurarMedidores() {
		modeloMedidorTemperatura = criarModeloTemperatura();
		modeloMedidorTemperatura.setTitle("Temperatura");
		modeloMedidorTemperatura.setGaugeLabel("ºC");
		modeloMedidorTemperatura.setSeriesColors("66cc66,93b75f,E7E658,cc6666");
        

		modeloMedidorUmidade = criarModeloUmidade();
		modeloMedidorUmidade.setTitle("Umidade");
		modeloMedidorUmidade.setGaugeLabel("%");

		modeloMedidorLuminosidade = criarModeloLuminosidade();
		modeloMedidorLuminosidade.setTitle("Luminosidade");
		modeloMedidorLuminosidade.setGaugeLabel("%");
		modeloMedidorTemperatura.setMin(-20);
	}

	public MeterGaugeChartModel getModeloMedidorTemperatura() {
		return modeloMedidorTemperatura;
	}

	public MeterGaugeChartModel getModeloMedidorUmidade() {
		return modeloMedidorUmidade;
	}

	public MeterGaugeChartModel getModeloMedidorLuminosidade() {
		return modeloMedidorLuminosidade;
	}

	private MeterGaugeChartModel criarModeloTemperatura() {
		List<Number> marcadores = new ArrayList<Number>();
		marcadores.add(-20);
		marcadores.add(-15);
		marcadores.add(-10);
		marcadores.add(-5);
		marcadores.add(0);
		marcadores.add(5);
		marcadores.add(10);
		marcadores.add(15);
		marcadores.add(20);
		marcadores.add(25);
		marcadores.add(30);
		marcadores.add(35);

		return new MeterGaugeChartModel(0, marcadores);

	}

	private MeterGaugeChartModel criarModeloUmidade() {
		List<Number> marcadores = new ArrayList<Number>();
		marcadores.add(0);
		marcadores.add(10);
		marcadores.add(20);
		marcadores.add(30);
		marcadores.add(40);
		marcadores.add(50);
		marcadores.add(60);
		marcadores.add(70);
		marcadores.add(80);
		marcadores.add(90);
		marcadores.add(100);

		return new MeterGaugeChartModel(0, marcadores);
	}

	private MeterGaugeChartModel criarModeloLuminosidade() {
		List<Number> marcadores = new ArrayList<Number>();
		marcadores.add(0);
		marcadores.add(10);
		marcadores.add(20);
		marcadores.add(30);
		marcadores.add(40);
		marcadores.add(50);
		marcadores.add(60);
		marcadores.add(70);
		marcadores.add(80);
		marcadores.add(90);
		marcadores.add(100);

		return new MeterGaugeChartModel(0, marcadores);
	}

	public int getTemp() {
		return SingleConector.getInformacao().getTemperatura();
	}

	public int getUmid() {
		return SingleConector.getInformacao().getUmidade();
	}

	public int getLum() {
		return SingleConector.getInformacao().getLuminosidade();
	}
	public void lerParaTabela() {
		SingleConector.getInformacao().getLuminosidade();
		SingleConector.getInformacao().getUmidade();
		SingleConector.getInformacao().getTemperatura();
	}
	public void lerSensores() {

		Informacao info = SingleConector.getInformacao();

		System.out.println("Temperatura = " + info.getTemperatura());
		System.out.println("Luminosidade = " + info.getLuminosidade());
		System.out.println("Umidade = " + info.getUmidade());

		// // atualizar os valores nos medidores
		modeloMedidorTemperatura.setValue(info.getTemperatura());
		modeloMedidorUmidade.setValue(info.getUmidade());
		modeloMedidorLuminosidade.setValue(info.getLuminosidade());
		

	}

}
