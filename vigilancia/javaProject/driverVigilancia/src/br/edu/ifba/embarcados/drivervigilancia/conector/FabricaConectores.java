package br.edu.ifba.embarcados.drivervigilancia.conector;

import com.sun.jna.Native;
import com.sun.jna.Platform;

public class FabricaConectores {
	
	public static IComunicacaoSensores getConector(){
		IComunicacaoSensores conector = null;
		
		if (Platform.isWindows()) {
			conector = (IComunicacaoSensores) Native.loadLibrary("driverVigilancia.dll", IComunicacaoSensores.class);
		} else if (Platform.isLinux()){			
			conector = (IComunicacaoSensores) Native.loadLibrary("driverVigilancia.so", IComunicacaoSensores.class);
		}	
		
		return conector;
		
	}
}
