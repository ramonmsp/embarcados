#include "DHT.h"
#include "RCSwitch.h"

//diretivas de compilação
//#define MIDDLEWARE
#define DAEMON

//intancia do emissor e do receptor
RCSwitch emissor = RCSwitch();
RCSwitch receptor = RCSwitch();

//Total de controles de RF possiveis
#define RFID_LIMITE_INFER 6
#define RFID_LIMITE_SUPER 12
//definindo qual será esse RF
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
#ifdef MIDDLEWARE
struct InfoRF{
  int id;
  int umidade;
  int temperatura;
  int luminosidade;
} infoRF;
#endif

#ifdef DAEMON
  long infoRF;
#endif

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
  ldrValor = map(ldrValor, 1023,0,0,100);
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
boolean RFIDValido(long rf) {
  boolean valido = false;

#ifdef MIDDLEWARE
  infoRF.id = rf  >> DESLOCAMENTO_RFID;
  if((infoRF.id >= RFID_LIMITE_INFER) &&
      (infoRF.id <= RFID_LIMITE_SUPER)){
    valido = true;
  }
#endif

#ifdef DAEMON
  long id = rf  >> DESLOCAMENTO_RFID;
  if((id >= RFID_LIMITE_INFER) &&
      (id <= RFID_LIMITE_SUPER)){
    valido = true;
  }
#endif
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

#ifdef MIDDLEWARE
   char buff[sizeof(InfoRF)] = {0};   
   memcpy(&buff, &infoRF, sizeof(InfoRF));
   
   Serial.write('I');
   Serial.write((uint8_t*) &buff, sizeof(InfoRF));
   Serial.write('F');
#endif

#ifdef DAEMON
   Serial.write('I');
   Serial.write((uint8_t*) &infoRF, sizeof(infoRF));
   Serial.write('F');
#endif   
}

// ----------------------------- Metodos de Extração de valores ----------------------------
#ifdef MIDDLEWARE
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
#endif

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
      
#ifdef MIDDLEWARE      
    infoRF.umidade = extrairUmidade(info);
    infoRF.temperatura = extrairTemperatura(info);
    infoRF.luminosidade = extrairLuminosidade(info);
#endif

#ifdef DAEMON 
    infoRF = info;
#endif  
    enviarParaUSB();
    }
  }


}

