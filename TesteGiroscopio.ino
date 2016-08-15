#include "MPU6050.h"
#include <Wire.h>
#include "I2Cdev.h"


//INT NO PINO 2

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;


double accZangle;

double gyroZangle = 180;

unsigned long timer;

//----- Porta do Motor -----
const int B_mais_pwm =5; // Portas que não funcionam 7,6,5,4
const int B_menos    =4; // Portas que funcioam 5,4,3,2
const int A_mais_pwm =3;
const int A_menos    =2;

const int PinAc = 2; // Pino de interrupção 

void setup() {

  Wire.begin();

    //----- Motor -----  
  pinMode(B_menos, OUTPUT); 
  pinMode(A_menos, OUTPUT);

  pinMode(PinAc, OUTPUT); 

  // Inicializando a comunicação serial
  // funciona em 8MHz ou em 16MHz
  Serial.begin(38400);

  // Iniciando dispositivos
  Serial.println("Inicializando cominicacao I2C...");

  accelgyro.initialize();

  // Testando a conexão com a MPU6050
  Serial.print("Testando a conexao com MPU6050...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 conectada com sucesso" : "Falha na conexao com a MPU6050");

  timer = micros();
}

void loop()
{
  
  acGiroD();
  acGiroE();
}

void acGiroD()
{
  //CURVA PARA DIREITA
  accelgyro.initialize();
  gyroZangle = 180;

  do
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    accZangle = (atan2(ax, ay) + PI) * RAD_TO_DEG;

    double gyroZrate = -((double)gz / 131.0);

    gyroZangle += gyroZrate * ((double)(micros() - timer) / 1000000);

    delay(1);
    timer = micros();
    //Serial.println(gyroZangle);

    
    //COMANDO DE GIRO PARA DIREITA
    motor_direita(100);
    delay(10);


  } while (gyroZangle < 260);

}

void acGiroE() {
  //CURVA PARA ESQUERDA
  accelgyro.initialize();
  gyroZangle = 180;

  do
  {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    accZangle = (atan2(ax, ay) + PI) * RAD_TO_DEG;

    double gyroZrate = -((double)gz / 131.0);

    gyroZangle += gyroZrate * ((double)(micros() - timer) / 1000000);

    delay(1);
    timer = micros();
    //Serial.println(gyroZangle);


    //COMANDO DE GIRO PARA ESQUERDA
    motor_esquerda(100);
    delay(10);
 
    

  } while (gyroZangle > 103);

}


