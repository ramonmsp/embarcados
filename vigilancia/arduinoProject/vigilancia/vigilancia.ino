/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low gyro data registers.
They can be converted to units of dps (degrees per second) using the
conversion factors specified in the datasheet for your particular
device and full scale setting (gain).

Example: An L3GD20H gives a gyro X axis reading of 345 with its
default full scale setting of +/- 245 dps. The So specification
in the L3GD20H datasheet (page 10) states a conversion factor of 8.75
mdps/LSB (least significant bit) at this FS setting, so the raw
reading of 345 corresponds to 345 * 8.75 = 3020 mdps = 3.02 dps.
*/

#include <Wire.h>
#include "L3G.h"
#include "ADXL345.h"

//objetos das bibliotecas do giroscopio e acelerometro, respectivamente
L3G gyro = L3G();
ADXL345 acel = ADXL345();

struct Leitura {
  int acelX, acelY, acelZ, gyroX, gyroY, gyroZ, stateTap;
  
};
Leitura leitura;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
// se giroscopio foi iniciado
  if (!gyro.init()) {
    Serial.println("Verificar ligação do sensor!");
    while (1);
  }

  gyro.enableDefault();
  acel.powerOn();
}
void enviarLeitura() {
  int tam = sizeof(leitura);
  char buffGyro[tam];
  memcpy(&buffGyro, &leitura, tam);
  Serial.write('I');
  Serial.write((uint8_t*)&buffGyro, tam);
  Serial.write('F');
}

void setStruct() {
    leitura.gyroX = (int)gyro.g.x;
    leitura.gyroY = (int)gyro.g.y;
    leitura.gyroZ = (int)gyro.g.z;
}
void loop() {
  byte interrupts = acel.getInterruptSource();
  leitura.stateTap = 0;
     
  gyro.read();
  setStruct();
  
  
  acel.readAccel(&leitura.acelX, &leitura.acelY, &leitura.acelZ);

  
  if(acel.triggered(interrupts, ADXL345_INT_SINGLE_TAP_BIT)){
    leitura.stateTap = 1;
  }
 
  enviarLeitura();
 
  delay(300);
}
