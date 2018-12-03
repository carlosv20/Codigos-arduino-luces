 //corriente
// Sensibilidad del sensor en V/A
float SENSIBILITY = 0.100; // Modelo 20A
int SAMPLESNUMBER = 800;
// Pin para Relé y variable
const int rele = 7;
boolean interruptor = false;
//lectura del serial
int option;

void setup() {
  Serial.begin(9600);
// definen pines
  pinMode(rele, OUTPUT);
   //llamado serial dht
}

void printMeasure(String prefix, float value, String postfix)
{
  Serial.print(prefix);
  Serial.print(value, 3);
  Serial.println(postfix);
}


void loop() 
{
  // leer el serial
   delay(0);
    if (Serial.available() > 0) {
  //leemos la opcion enviada
      option = Serial.read();
     if (option == 'p') {
      interruptor = false;
      }
     if (option == 'a') { 
      interruptor = true;
      }
}
  //Condicional del interruptor / rele

  if (interruptor == true) {
    digitalWrite(rele, LOW);
  }
  if (interruptor == false) {
    digitalWrite(rele, HIGH);
  }
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
