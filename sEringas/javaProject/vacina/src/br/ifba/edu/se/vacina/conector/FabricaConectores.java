package br.ifba.edu.se.vacina.conector;

import br.ifba.edu.se.vacina.IComunicacaoRF;

import com.sun.jna.Native;
import com.sun.jna.Platform;

public class FabricaConectores {
	public static IComunicacaoRF getConector(String libPath) {
		IComunicacaoRF comRF = null;

		if (Platform.isWindows()) {
			comRF = (IComunicacaoRF) Native.loadLibrary(libPath
					+ "/vacina.dll", IComunicacaoRF.class);
		} else if (Platform.isLinux()) {
			comRF = (IComunicacaoRF) Native.loadLibrary(libPath
					+ "/vacina.so", IComunicacaoRF.class);
		}
		return comRF;
	}
}
