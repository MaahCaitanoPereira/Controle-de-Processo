double rele = A1;   //saída para relé 

  double doubleMap(double x, double in_min, double in_max, double out_min, double out_max) 
  {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

double treal;
double t;
double talvo;
double va;
double dmenor;
double dmaior;
double pmenor;
double pmaior;


void setup() 
{
  Serial.begin(9600);      //inicia a comunicação Serial
  pinMode(rele, INPUT);
}

void loop() 
{
  t=analogRead(rele);
  talvo= t/10.24;
  
  while(Serial.available()>0){
    treal = Serial.parseFloat();
    delay(1500);}

    if(treal>1){ 
      dmenor= (treal - 20.00);   // dmenor: o menor limite do intervalo atual do valor
      dmaior= (treal + 20.00);   // dmaior: o maior limite do intervalo atual do valor
      pmenor= (treal - 1.00);    // pmenor: o menor limite do intervalo alvo
      pmaior= (treal + 1.00);    // pmaior: o maior limite do intervalo alvo

      // talvo: o número que esta com ruido
      va= map(talvo,dmenor,dmaior,pmenor,pmaior);   // map(talvo, dmenor, dmaior, pmenor, pmaior);

      Serial.print("Temperatura ");
      Serial.print(va);
      Serial.print("\t");
      Serial.print(" Temperatura no visor ");
      Serial.println(treal);
      }
      delay(1000);
}
