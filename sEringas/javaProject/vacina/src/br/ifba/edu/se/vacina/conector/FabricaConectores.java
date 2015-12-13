package br.ifba.edu.se.vacina.conector;

import br.ifba.edu.se.vacina.IComunicacaoRF;

import com.sun.jna.Native;
import com.sun.jna.Platform;

public class FabricaConectores {
	public static IComunicacaoRF getConector(String libPath) {
		IComunicacaoRF comRF = null;

		if (Platform.isWindows()) {
			comRF = (IComunicacaoRF) Native.loadLibrary(libPath
					+ "/comunicacaorf.so", IComunicacaoRF.class);
		} else if (Platform.isLinux()) {
			comRF = (IComunicacaoRF) Native.loadLibrary(libPath
					+ "/comunicacaorf.dll", IComunicacaoRF.class);
		}
		return comRF;
	}
}