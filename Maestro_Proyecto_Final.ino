//MAESTRO
#include <Keypad.h>
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

#define arduinoPin 9

#define ledPin 12
int state = 0;

char receivedData[4];  // Array para almacenar los dígitos recibidos
int dataIndex = 0;     // Índice para seguir la posición actual en el array

const byte filas = 4;
const byte columnas = 4;

byte pinesF[filas] = {8,7,6,5};
byte pinesC[columnas] = {4,3,2};

char teclas[filas][columnas]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

Keypad teclado = Keypad(makeKeymap(teclas),pinesF, pinesC,filas,columnas);
char tecla;
String cadena;


void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(arduinoPin, OUTPUT);
  digitalWrite(arduinoPin, HIGH);
}
 
void loop()
{
  if(BT.available()){    // Si llega un dato por el puerto BT se envía al monitor serial

    // state = BT.read();
    // Serial.write(state);
    char incomingChar = BT.read();

    if (isdigit(incomingChar)) {  // Verifica si el carácter es un dígito
      receivedData[dataIndex] = incomingChar;
      dataIndex++;

      if (dataIndex == 4) {
        // Se ha recibido un número de 4 dígitos, realiza la acción necesaria
        int codigo = processData();

        validateData(codigo);

        // Restablece el índice para recibir el próximo número
        dataIndex = 0;
      }
    }

  }
 
  // if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  // {
  //    BT.write(Serial.read());
  // }
}




int processData() {
  // Convierte el array de caracteres en un número entero
  int receivedNumber = atoi(receivedData);

  Serial.print("String recibido: ");
  Serial.println(receivedData);

  // Realiza la acción necesaria con el número completo
  Serial.print("Número recibido: ");
  Serial.println(receivedNumber);

  return receivedNumber;

  // if (receivedNumber == 1234) {
  //   digitalWrite(ledPin, HIGH);
  //   delay(3000);
  //   digitalWrite(ledPin, LOW);
  // }
}

void validateData(int codigo){

  tecla = teclado.getKey();
  // cadena = "";
  // lcd.clear();         

  while(true){
      char tecla = teclado.waitForKey();
      if(tecla!='*'){
        cadena = cadena + tecla;

        Serial.print(tecla);
        // lcd.setCursor(0, 0);
        // lcd.print("tecla: " );
        // lcd.print(cadena);
      }
      else if(tecla=='#'){
        cadena = "";
        Serial.print(tecla);
        // lcd.setCursor(0, 0);
        // lcd.print("tecla: " );
        // lcd.print(cadena);
      }
      else{

        int codigoIngresado = atoi(cadena.c_str());

        Serial.print("Codigo Aplicacion: ");
        Serial.println(codigo);

        Serial.print("Codigo Ingresado: ");
        Serial.println(codigoIngresado);


        if(codigo == codigoIngresado){
          Serial.print("CODIGO CORRECTO!");
          break;
        }
        else{
           cadena = "";
          Serial.print("------------ CODIGO ERRORNEO - POR FAVOR INTENTE DE NUEVO ------------");
        }


        // break;
      }      
  }

}