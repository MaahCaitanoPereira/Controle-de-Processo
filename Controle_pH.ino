// Define pino de entrada do sinal de pH

const int pinoPh = A0;

float tempo;

// Variáveis

unsigned long int avgValuepH;

// Somatório dos 6 valores de tensão lidos para o sensor de pH

int buf[10],temp; // buf = vetor onde são guardados os 10 valores de tensão para uma medida

// de pH, temp = variável usada para excluir 2 maiores e 2 menores valores

// detensão lidos no sensor //de pH

// Iniciando a comunicação serial.

void setup()

{ Serial.begin(9600);

Serial.println ("Inicio");

Serial.println("Tempo [s] / pH");}

// Laço contínuo

//////////////// Leitura de pH///////////////////

// Lendo 10 valores de pH com uma distância de tempo de 10 ms

void loop()

{ for(int i=0;i<10;i++)

{ buf[i]=analogRead(pinoPh);

delay(100); }

// Excluindo os 2 maiores e 2 menores valores de tensão lidos no sensor de pH

for(int i=0;i<9;i++)

{ for(int j=i+1;j<10;j++)

{ if(buf[i]>buf[j])

{ temp=buf[i];

buf[i]=buf[j];

buf[j]=temp; } } }

// Somando os 6 valores de tensão restantes da leitura de pH

avgValuepH=0;

for(int i=2;i<8;i++)

avgValuepH+=buf[i];

// Converte o valor numérico para valor de tensão V (dividido por 6 pois foram somados 6 valores); Tabela de conversão 0 V = 0 numérico; 5V = 1023

float pHVol=(float)avgValuepH*5.0/1024/6;

// Converte o valor de tensão [V] para pH

float phValue = -5.70 * pHVol + 21.34;

// Mostrando na serial

///////////// leitura de tempo ////////////////////

// Lendo tempo desde o início da medida em ms

tempo = millis();

// convertendo ms para segundos

tempo = tempo/1000;

//mostrando o valor de tempo na serial

Serial.print (tempo);

Serial.print (" ");

//mostrando o valor de pH na serial

Serial.println (phValue);

// Tempo em ms para a próxima leitura

int tempo_para_proxima_leitura = 20; // [valor em ms]

delay(tempo_para_proxima_leitura);
}
