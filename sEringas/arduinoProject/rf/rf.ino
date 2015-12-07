#include "DHT.h"
#include "RCSwitch.h"

//intancia do emissor e do receptor
RCSwitch emissor = RCSwitch();
RCSwitch receptor = RCSwitch();

//Total de controles de RF possiveis
#define RFID_LIMITE_INFER 6
#define RFID_LIMITE_SUPER 12
#define RFID 6

#define DESLOCAMENTO_RFID 26
#define DESLOCAMENTO_UMID 18
#define DESLOCAMENTO_TEMP 10

//setando pinos e tipo de DHT(11 ou 22) 
#define LDR_PIN 0  
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

//instancia de DHT
DHT dht(DHTPIN, DHTTYPE);

//-------------------------------- Struct ------------------------------------------------
struct InfoRF{
  int id;
  int umidade;
  int temperatura;
  int luminosidade;
} infoRF;

//-------------------------------- SETUP --------------------------------------------------
void setup() {
  Serial.begin(9600);
  
  dht.begin();
  
  emissor.enableTransmit(4);
  receptor.enableReceive(0);

}
//------------------------------- lerSensores ----------------------------------------
long lerSensoresRF() {
  
  long ldrValor = analogRead(LDR_PIN); 
  long umidadeValor = dht.readHumidity();
  long temperaturaValor = dht.readTemperature();

  long rf = RFID;  
  long info = rf << DESLOCAMENTO_RFID;
  info = info | (umidadeValor << DESLOCAMENTO_UMID);
  info = info | (temperaturaValor << DESLOCAMENTO_TEMP);
  info = info | ldrValor;

  return info;
}

//-------------------------------- RFIDValido ---------------------------------
boolean RFIDValido(long info) {
  boolean valido = false;
  infoRF.id = info  >> DESLOCAMENTO_RFID;
  if((infoRF.id >= RFID_LIMITE_INFER) &&
      (infoRF.id <= RFID_LIMITE_SUPER)){
    valido = true;
  }
  return valido;
}

//------------------------------- Emitir ------------------------------------------- 
void emitir (long info) {
  emissor.send(info, 32);
}

//------------------------------- Receber ------------------------------------------- 
long receber() {
  long info = -1;
  
  if (receptor.available()) {
    info = receptor.getReceivedValue();
    receptor.resetAvailable();
  }  
  return info;
}

//---------------------------- Enviar para USB ----------------------------------------------
//metodo para enviar
void enviarParaUSB(){
   char buff[sizeof(InfoRF)] = {0};
   
   memcpy(&buff, &infoRF, sizeof(InfoRF));
   Serial.write((uint8_t*) &buff, sizeof(InfoRF));
   
}

// ----------------------------- Metodos de Extração de valores ----------------------------
int extrairTemperatura(long info) {
  int temperatura = (info & 261120) >> DESLOCAMENTO_TEMP;

  return temperatura;
}

int extrairUmidade(long info) {
  int umidade = (info & 66846720) >> DESLOCAMENTO_UMID;

  return umidade;
}

int extrairLuminosidade(long info) {
  int luminosidade = (info & 1023);

  return luminosidade;
}


//------------------------------- LOOP -----------------------------------------------------
void loop() {

  //Emissao de dados
  long info = lerSensoresRF();
  emitir(info);


  delay(50);

  //Recepcao de dados
  info = receber();
  if (info != -1) {
    if (RFIDValido(info)) {

    infoRF.umidade = extrairUmidade(info);
    infoRF.temperatura = extrairTemperatura(info);
    infoRF.luminosidade = extrairLuminosidade(info);
  //  enviarParaUSB();

      Serial.println();
      int luminosidade = extrairLuminosidade(info);
      Serial.print("A luminosidade eh de: ");
      Serial.print(luminosidade);
      Serial.println(" lumens");

      int temperatura = extrairTemperatura(info);

      Serial.print("A temperatura eh de ");
      Serial.print(temperatura);
      Serial.println("*C");
  
      int umidade = extrairUmidade(info); 
      
      Serial.print("A umidade eh de ");
      Serial.print(umidade);
      Serial.println("% ");


    }
  }


}

