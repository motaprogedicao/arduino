#include<Wire.h>
//Endereço I2C hexadecimal do sensor MPU 6050
const int endereco_sensor=0x68; //signal_path_reset
int giroX, giroY, giroZ, acelX, acelY, acelZ, temperatura;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

//Inicializa o MPU-6050
Wire.begin();
Wire.beginTransmission(MPU);
Wire.write(0x6B); //
Wire.write(0);
Wire.endTransmission(true); //Não permitindo que entre em modo sleep

//Configura giroscópio no fundo de escala para +/-2000º /s
Wire.beginTransmission(MPU);
Wire.write(0x1B);//endereço/registro onde esta sendo gravado o dado
Wire.write(0x00011000);
Wire.endTransmission();

//Configura acelerometro no fundo de escala para +/-2000º /s
Wire.beginTransmission(MPU);
Wire.write(0x1C);
Wire.write(0b00011000);
Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Iniciar transmissão de dados
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); //Endereço onde irão começar a ser recebidos os dados ACCEL_XOUT_H
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); //14 bytes pois será feita a leitura de todos os registros de uma vez

  //Armazena o valor dos sensores nas variaveis correspondentes de 2 em 2 bytes
  acelX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acelY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_XOUT_L)
  acelZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_XOUT_L)
  
  temperatura = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0X42 (ACCEL_XOUT_L)
  giroX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (ACCEL_XOUT_L)
  giroY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (ACCEL_XOUT_L)
  giroZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (ACCEL_XOUT_L)
 
/*
  Leitura do Primeiro Byte:

Wire.read() lê o primeiro byte dos dados I2C. Suponha que o valor lido seja 0x12 (em hexadecimal), o que é 00010010 em binário.
Deslocamento do Primeiro Byte:
Wire.read() << 8 desloca esse byte 8 bits à esquerda. Portanto, 0x12 se torna 0x1200 (em hexadecimal), que é 00010010 00000000 em binário.
Leitura do Segundo Byte:
Wire.read() lê o próximo byte dos dados I2C. Suponha que o valor lido seja 0x34 (em hexadecimal), que é 00110100 em binário.
Combinação dos Bytes:
A operação | combina os dois bytes. O resultado é 0x1200 | 0x34, que é 00010010 00110100 em binário. Em hexadecimal, isso resulta em 0x1234.

Resultado Final
acelX: Recebe o valor combinado de 16 bits. Se o primeiro byte era 0x12 e o segundo byte era 0x34, o valor final de acelX será 0x1234,
 que é o valor completo de 16 bits obtido a partir da leitura dos dois bytes do sensor.
A linha acelX = Wire.read() << 8 | Wire.read(); realiza a leitura de dois bytes consecutivos do barramento I2C e os combina em um valor de 16 bits. 
O primeiro Wire.read() fornece a parte alta (bytes mais significativos) do valor de 16 bits após o deslocamento, 
e o segundo Wire.read() fornece a parte baixa (bytes menos significativos).
 A combinação desses dois bytes resulta no valor final armazenado na variável acelX.

 */

//Imprimindo na Serial os valores obtidos
Serial.print(acelX / 2048); //é dividido por 2048 por conta do fundo de escala de 16g do acelerometro
Serial.print(" ");
Serial.print(acelY / 2048); 
Serial.print(" ");
Serial.print(acelZ / 2048); 
/*
Serial.print(GyrX / 16.4); 
Serial.print(" ");
Serial.print(GyrY / 16.4); 
Serial.print(" ");
Serial.print(GyrZ / 16.4); //dividido por 16.4 por conta do fundo de escala de -2000 do giroscopio
*/
delay(100);


}
