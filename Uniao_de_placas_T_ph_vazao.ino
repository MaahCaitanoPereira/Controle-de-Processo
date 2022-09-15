//Este codigo eh para ser usado no VisualStudioCODE, usar as seguintes extensoes: Arduino; C/C++, PlatformIO IDE, e json.
//Recomendo videos tutoriais do programa, pois precisa de mais extensoes e configuracoes alem destas
//Para este codigo, na aba da extensao PlatformIO IDE digitou se, para salvar um txt: 
/*
[env:megaatmega2560]
platform = atmelavr
board = megaatmega2560
framework = arduino
monitor_filters = log2file, default // salva o txt
*/
/////////////////////////////////////////////////////////////////////////// Codigo para aba em C/C++/////////////////////////////////////////////////////

#include <Arduino.h>

// DECLARACAO DE VARIAVEIS//

double tempo;

/////////////////////////////////////////////Temperatura///////////////////////////////////////
float rele = A1;   //saída para relé de maior potência

  //////FUNCAO MAP///////
  float doubleMap(float x, float in_min, float in_max, float out_min, float out_max) 
  {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

float treal;
float bits;
float talvo;
float va;
float dmenor;
float dmaior;
float pmenor;
float pmaior;

///////////////////////////////////////////////PH/////////////////////////////////////////////
const int pinoPh = A0;
unsigned long int avgValuepH;
int buf[10],t; 

/////////////////////////////////////////////BOMBA///////////////////////////////////////////
const int control_a = 6; // Bomba esquerda
const int control_b = 7; // Bomba direita

const int pino1 = 8;  // Direita da ponte H
const int pino2 = 9;  // Direita da ponte H
const int pino3 = 10;  // Esquerda da ponte H
const int pino4 = 11;  // Esquerda da ponte H

int velo_a;
int velo_b;
//////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  Serial.begin(9600);

  //Temperatura e PH//
  pinMode(rele, INPUT);
  pinMode(pinoPh, INPUT);

  //Bombas//
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
/////////////////////////////////////////////Valores de entrada///////////////////////////////////////////////////
  while(Serial.available()>0){
    treal = Serial.parseFloat();
    velo_a = Serial.parseInt();
    velo_b = Serial.parseInt();
    }
/////////////////////////////////////////////Temperatura///////////////////////////////////////////////////
  bits = analogRead(rele);
  talvo = bits/10.24;
 
    if(treal>1){ //Sempre calibrar
      dmenor= (treal - 20.00);   // dmenor: o menor limite do intervalo atual do valor
      dmaior= (treal + 20.00);   // dmaior: o maior limite do intervalo atual do valor
      pmenor= (treal - 0.50);    // pmenor: o menor limite do intervalo alvo
      pmaior= (treal + 0.50);    // pmaior: o maior limite do intervalo alvo

      // talvo: o número que aparece no sensor
      va= map(talvo,dmenor,dmaior,pmenor,pmaior);   // map(talvo, dmenor, dmaior, pmenor, pmaior);
    }
///////////////////////////////////////////////PH/////////////////////////////////////////////
for(int i=0;i<10;i++)
    {buf[i]=analogRead(pinoPh);
    }

for(int i=0;i<9;i++)
    {for(int j=i+1;j<10;j++)
      {if(buf[i]>buf[j])
        {t=buf[i];
          buf[i]=buf[j];
          buf[j]=t; 
    } } }

avgValuepH=0;

for(int i=2;i<8;i++)
avgValuepH+=buf[i];
float pHVol=(float)avgValuepH*5.0/1024/6;
float phValue = -5.70 * pHVol + 21.34;

/////////////////////////////////////////////BOMBA///////////////////////////////////////////
  digitalWrite(pino1, LOW);
  digitalWrite(pino2, HIGH);
  digitalWrite(pino3, LOW);
  digitalWrite(pino4, HIGH);
  
  analogWrite(control_a, velo_a);
  analogWrite(control_b, velo_b);
 
/////////////////////////////////////SerialPrint/////////////////////////////////////////

tempo= (millis())/1000;
Serial.print(tempo);
Serial.print("\t");

Serial.print("(T.Ambiente -- T. Calculada -- pH -- Bomba E.-- Bomba D.)   ");
Serial.print(treal);
Serial.print("   ");
Serial.print(va);
Serial.print("   ");
Serial.print(phValue);
Serial.print("   ");
Serial.print(velo_a);
Serial.print("   ");
Serial.println(velo_b);
delay(1000);
}
