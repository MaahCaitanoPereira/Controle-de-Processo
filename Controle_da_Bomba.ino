// Funciona no seguintes valores: entre 210 e 255

const int control_a = 6; // Controla entrada a esquerda   USANDO ESSE 
const int control_b = 5; // Controla entrada a direita

const int pino1 = 8;   // Entrada a direita
const int pino2 = 9;   // Entrada a direita 
const int pino3 = 11;  // Entrada a esquerda  USANDO ESSE
const int pino4 = 10;  // Entrada e esquerda  USANDO ESSE 

int velo;
double tempo;

void setup() 
{
  Serial.begin(9600);
  pinMode(pino1, OUTPUT);
  pinMode(pino2, OUTPUT);
  pinMode(pino3, OUTPUT);
  pinMode(pino4, OUTPUT);
  pinMode(control_a, OUTPUT);
  pinMode(control_b, OUTPUT);

  digitalWrite(pino1, LOW);
  digitalWrite(pino2, LOW);
  digitalWrite(pino3, LOW);
  digitalWrite(pino4, LOW);
  digitalWrite(control_a, LOW);
  digitalWrite(control_b, LOW);
}

void loop() 
{
  tempo = (millis()/1000);
  digitalWrite(pino1, LOW);
  digitalWrite(pino2, HIGH);
  digitalWrite(pino3, LOW);
  digitalWrite(pino4, HIGH);


  while(Serial.available()>0){
  velo = Serial.parseInt();
  delay(2000);}
  
  analogWrite(control_a, velo);
  analogWrite(control_b, velo);
  Serial.print(tempo);
  Serial.print("\t");
  Serial.print(" Digite a velocidade");
  Serial.print("\t");
  Serial.println(velo);
  
  delay(1000);
}
