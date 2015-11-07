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

struct Eixos {
  int acelX, acelY, acelZ;
  
};
Eixos eixos;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init()) {
    Serial.println("Verificar ligação do sensor!");
    while (1);
  }

  gyro.enableDefault();
  acel.powerOn();
}

void loop() {
  
  gyro.read();

  Serial.print("G ");
  Serial.print("X: ");
  Serial.print((int)gyro.g.x);
  Serial.print(" Y: ");
  Serial.print((int)gyro.g.y);
  Serial.print(" Z: ");
  Serial.println((int)gyro.g.z);

  delay(50);
  
  acel.readAccel(&eixos.acelX, &eixos.acelY, &eixos.acelZ);
  
  Serial.print("A ");
  Serial.print("X:  ");
  Serial.print(eixos.acelX);
  Serial.print(" Y:  ");
  Serial.print(eixos.acelY);
  Serial.print(" Z:  ");
  Serial.println(eixos.acelZ);

  delay(500);
}
