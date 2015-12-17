package br.ifba.edu.se.vacina;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.bean.ViewScoped;

import br.ifba.edu.se.vacina.Informacao;

@ManagedBean(name = "carrossel")
public class Carrossel implements Serializable {

	//private static List<Informacao> info_ = new ArrayList<Informacao>();
	private static Informacao info_ = new Informacao();

	public static void setInformacao(Informacao info) {
		info_ = info;
	}

	public Informacao getInformacao() {
		return info_;
	}
}
