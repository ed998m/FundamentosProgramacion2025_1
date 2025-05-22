#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  byte status = mpu.begin();
  while(status != 0) {
    Serial.println("Error: Conecta el MPU6050 y reinicia");
    delay(1000);
  }

  Serial.println("Calibrando... No muevas el sensor");
  delay(1000);
  mpu.calcGyroOffsets();
  Serial.println("¡Listo! Enviando datos...");
}

void loop() {
  mpu.update();
  
  // 1. Obtener voltaje de la placa (via pin A0)
  float voltage = analogRead(A0) * (5.0 / 1023.0); // Conversión ADC a voltaje
  
  // 2. Obtener datos del acelerómetro (en g)
  float accelX = mpu.getAccX();
  float accelY = mpu.getAccY();
  float accelZ = mpu.getAccZ();
  
  // 3. Enviar todos los datos por Serial (formato clave=valor)
  Serial.print("R="); Serial.print(mpu.getAngleX(), 1);    // Roll
  Serial.print("|P="); Serial.print(mpu.getAngleY(), 1);   // Pitch
  Serial.print("|Y="); Serial.print(mpu.getAngleZ(), 1);   // Yaw
  Serial.print("|AX="); Serial.print(accelX, 2);          // Acelerómetro X
  Serial.print("|AY="); Serial.print(accelY, 2);          // Acelerómetro Y
  Serial.print("|AZ="); Serial.print(accelZ, 2);          // Acelerómetro Z
  Serial.print("|V="); Serial.print(voltage, 2);          // Voltaje
  Serial.println(); // Fin de línea

  delay(15); // Ajusta según necesidad
}