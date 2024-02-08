//	ESCLAVO
    
#include <Wire.h>

int engine = 0;
int enginePin = 0;
bool isEngineAvailable = false;
int valorSensor = 0;
int sensorPin = 0;

#define positivoPin 7
 
void setup() {

  pinMode(positivoPin, OUTPUT);
  //digitalWrite(positivoPin, HIGH);
  
  pinMode(2, OUTPUT); // Pines en modo salida
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  //digitalWrite(2, HIGH);
 
  Wire.begin(1); // Unimos este dispositivo al bus I2C con dirección 1
  
  Wire.onReceive(receiveEvent); // Registramos el evento al recibir datos
  
  Serial.begin(9600); // Iniciamos el monitor serie para monitorear la comunicación
}
 
void loop() {
  delay(300);

  if(isEngineAvailable){

    digitalWrite(enginePin, HIGH);

    Serial.print("----ACTIVA MOTOR -----"); 
    delay(400);
    Serial.print("----ACTIVA SENSOR -----"); 

    sensorPin = enginePin + 4;
    Serial.print("Sensooooor: " + sensorPin); 
    
    unsigned long startTime = millis();  // Obtén el tiempo actual

    while (millis() - startTime <= 3000) {  // Ejecuta durante 3 segundos (3000 milisegundos)
    
    Serial.println(millis() - startTime);

    valorSensor = digitalRead(sensorPin); 

    if (valorSensor == LOW) {
      Serial.println("Detectado obstaculo");
      break;
    }
    // digitalWrite(enginePin, HIGH);
    // delay(3600);
    // digitalWrite(enginePin, LOW);

    // engine = 0;
    // enginePin = 0;
    // isEngineAvailable = false;

    }

    digitalWrite(enginePin, LOW);

    engine = 0;
    enginePin = 0;
    isEngineAvailable = false;
    valorSensor = 0;
    sensorPin = 0;

  }
}

int receiveEvent(int howMany) {

    if (Wire.available() == 1) // Si hay UN SOLO byte disponible
  {
    engine = Wire.read(); // Leemos el primero que será el pin
    // Serial.print("MOTOR A ACTIVAR: ");
    // Serial.println(engine);
    enginePin = engine + 1;
    // Serial.print("PIN A ACTIVAR: ");
    // Serial.println(enginePin);

    isEngineAvailable = true;

  }
}
