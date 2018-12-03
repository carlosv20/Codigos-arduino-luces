// Sensibilidad del sensor en V/A
float SENSIBILITY = 0.100; // Modelo 20A
int SAMPLESNUMBER = 800;
float mA;
//Movimiento
int avoid = 3; // define the obstacle avoidance sensor interface
int val ;// define numeric variables val
boolean encender = false;
// Pin para Relé y variable
const int rele = 7;
boolean interruptor = true;
const int rele2 = 8;
boolean interruptor2 = true;
//lectura del serial
int option;
//Lectura proximidad
int option2;
void setup() {
  Serial.begin(9600);
  // definen pines
  pinMode(rele, OUTPUT);
  pinMode(rele2, OUTPUT);
  //movimiento
  pinMode (avoid, INPUT) ;// define the
  //obstacle avoidance sensor output interface
}
void printMeasure(String prefix, float value, String postfix)
{
  Serial.print(prefix);
  Serial.print(value, 3);
  Serial.println(postfix);
}
void loop() {
  // movimiento
  evitar();
  // leer el serial
  delay(0);
  if (Serial.available() > 0) {
    //leemos la opcion enviada
    option = Serial.read();
    if (option == 'p') {
      interruptor = true;
    }
    if (option == 'a') {
      interruptor = false;
    }
  }
  //Condicional del interruptor / rele
  if (interruptor == true) {
    digitalWrite(rele, HIGH);
    if (val == 1) {
      digitalWrite(rele2, HIGH);
    } else {
      digitalWrite(rele2, LOW);
    }
  }
  if (interruptor == false) {
    digitalWrite(rele, LOW);
    if (val == 0) {
      digitalWrite(rele2, LOW);
    } else {
      digitalWrite(rele2, LOW);
    }
  }
  //Condicional del interruptor2 / rele2
  //Sensor de corriente
  float current = getCorriente(SAMPLESNUMBER);
  float currentRMS = 0.707 * current;
  float power = 230.0 * currentRMS;
  if (interruptor == false) {
    current = 0;
  }
  printMeasure("Intensidad: ", current, "A ,");
  // printMeasure("Irms: ", currentRMS, "A ,");
  //printMeasure("Potencia: ", power, "W");
  delay(1000);
  //Imprimir en el serial
  //estado interruptor / rele
  //Serial.print("Estado luz ");
  //Serial.print(interruptor);
  //Serial.println();
}
float getCorriente(int samplesNumber)
{
  float intensidadFinal;
  float voltage;
  float corrienteSum = 0;
  for (int i = 0; i < samplesNumber; i++)
  {
    voltage = analogRead(A0) * 5.0 / 1023.0;
    corrienteSum += (voltage - 2.5) / SENSIBILITY;
  }
  intensidadFinal = corrienteSum / samplesNumber;
  if ( intensidadFinal < 0) {
    intensidadFinal = intensidadFinal * (-1);
  } else {
    intensidadFinal;
  }
  return (intensidadFinal);
}
void evitar() {
  val = digitalRead (avoid) ;// digital interface will be assigned a value of 3 to read val
  Serial.println(val);
  if (val == HIGH) // When the obstacle avoidance sensor detects a signal, LED flashes
  {
    encender = true;
  }
  else
  {
    encender = false;
  }
}
