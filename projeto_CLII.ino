
#include <math.h>
#include <Servo.h>
//Pesos da rede neural
float camada_entrada1[3][3] = {{0.5994415 , -0.5862342 , -0.33743876}, {-0.37520385, -0.24663334,  0.42943838}, {-0.5815196 ,  0.9285167 , -0.19369899}};
float matrix1[1][3];
float camada_entrada2[1][3] = {{0.05185409, 0.74422216, 0.55846107}};
float matrix2[1][3];
float camada_oculta1[3][4] = {{0.32014424,  0.00230874,  0.7614521 , -0.51178944}, {-0.9733894 ,  0.03552462,  0.08648542, -0.99902064}, {-0.6601802 ,  0.13706253, -0.05031076,  0.84222966}};
float matrix3[1][4];
float camada_oculta2[1][4] = {-2.608262 ,  1.2402312,  2.3638933,  1.3725291};
float matrix4[1][4];
float camada_saida1[4][4] = {{-0.571775  ,  1.4523959 , -4.6908927 ,  0.12480743}, {0.36534378, -5.380796  ,  0.51688284,  0.52336127}, {-3.2923992 ,  1.5994979 ,  0.04918078, -0.17859001}, {3.316598  ,  0.05604243, -5.322128  , -0.5367407}};
float matrix5[1][4];
float camada_saida2[1][4] = {0.9296987, -2.2398202, -1.0377976, -1.3314041};
float matrix6[1][4];
//Distância no momento
float distance;
//variaveis
float lenght_of_time;
int pos;
int i,j,k1,k2;
float temp;
int linA,colA,linB,colB;
int maior;
//matriz das distâncias no momento
float matrix_of_distances[1][3];
//controle do servo
Servo myservo;
//setando portas
#define TRIG 8
#define ECHO 9

//função sigmoide de ativação do neurônio
float sigmoid(float x)
{
  return 1/(1 + exp(-x));
}
//função de procura de obstáculos (distância para os obstáculos)
float search() {
  digitalWrite(TRIG, LOW);
  delay(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  lenght_of_time = pulseIn(ECHO, HIGH);

  distance = lenght_of_time / 58;

  return distance;
}
//distância da esquerda
float look_left()
{
  for (pos = 90; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  distance = search();
  for (pos = 180; pos >= 90; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
  return distance;
}
//distância da direita
float look_right()
{
  for (pos = 90; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
  distance = search();
  for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  return distance;
}

void setup()
{
  Serial.begin(9600);
  myservo.attach(7);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  //completando a matriz de distâncias
  distance = search();
  matrix_of_distances[0][1] = distance;
  matrix_of_distances[0][0] = look_left();
  matrix_of_distances[0][2] = look_right();

  //calculos e classificação
  linA = 1;
  colA = 3;
  linB = 3;
  colB = 3;
  for(k1=0;k1<linA;k1++)
  {
      for(k2=0;k2<colB;k2++)
      {
          temp=0.0;
          for(i=0;i<colA;i++)
          {
              temp=temp+matrix_of_distances[k1][i]*camada_entrada1[i][k2];
          }
          matrix1[k1][k2]= sigmoid(temp);
      }
  }/*
  linA = 1;
  colA = 3;
  linB = 1;
  colB = 3;
  for(k1=0;k1<linA;k1++)
  {
      for(k2=0;k2<colB;k2++)
      {
          temp=0.0;
          for(i=0;i<colA;i++)
          {
              temp=temp+matrix1[k1][i]*camada_entrada2[i][k2];
          }
          matrix2[k1][k2]=temp;
      }
  }*/
  linA = 1;
  colA = 3;
  linB = 3;
  colB = 4;
  for(k1=0;k1<linA;k1++)
  {
      for(k2=0;k2<colB;k2++)
      {
          temp=0.0;
          for(i=0;i<colA;i++)
          {
              temp=temp+matrix1[k1][i]*camada_oculta1[i][k2];
          }
          matrix3[k1][k2]= temp;
      }
  }/*
  linA = 1;
  colA = 4;
  linB = 4;
  colB = 4;
  for(k1=0;k1<linA;k1++)
  {
      for(k2=0;k2<colB;k2++)
      {
          temp=0.0;
          for(i=0;i<colA;i++)
          {
              temp=temp+matrix3[k1][i]*camada_oculta2[i][k2];
          }
          matrix4[k1][k2]= sigmoid(temp);
      }
  }*/
  linA = 1;
  colA = 4;
  linB = 4;
  colB = 4;
  for(k1=0;k1<linA;k1++)
  {
      for(k2=0;k2<colB;k2++)
      {
          temp=0.0;
          for(i=0;i<colA;i++)
          {
              temp=temp+matrix3[k1][i]*camada_saida1[i][k2];
          }
          matrix5[k1][k2]= sigmoid(temp);
      }
  }/*
  linA = 1;
  colA = 4;
  linB = 1;
  colB = 4;
  for(k1=0;k1<linA;k1++)
  {
      for(k2=0;k2<colB;k2++)
      {
          temp=0.0;
          for(i=0;i<colA;i++)
          {
              temp=temp+matrix5[k1][i]*camada_saida2[i][k2];
          }
          matrix6[k1][k2]= sigmoid(temp);
      }
  }*/
  //transmissão dos resultados da classificação
  Serial.println('--');
  Serial.println(matrix5[0][0]);
  Serial.println(matrix5[0][1]);
  Serial.println(matrix5[0][2]);
  Serial.println(matrix5[0][3]);
  Serial.println('--');
  for(int i=0; i < 4; i++)
  {
    if(i==0)
    {
      maior = i;
    }
    if(matrix5[0][i] > matrix5[0][maior])
    {
      maior = i;
    }
  }
  Serial.println(maior);
  Serial.println('--');
  digitalWrite(maior+10, HIGH);
  delay(1500);
  digitalWrite(maior+10, LOW);
}
