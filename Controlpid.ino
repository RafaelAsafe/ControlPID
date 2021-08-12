float PWMPin = 3; // pino do PWM
float InPin = A1; // pino leitura V0
float PWM = 0 ;// variavel que registra o valor a ser enviado
double V = 0; //ler tensão
//PID
float Kp = 1.5; //ganho proporcional
float Ki = 3; //ganho integral
float Kd = 3; //ganho derivativo
float dt = 10; //variação de tempo entre um ciclo e outro
double ek = 0; //erro passado
double ek1 = 0; //erro atual
float p = 0; // proporcional
float i = 0; // integral
float d = 0; //derivativoM
float pid = 0; //junção de todos os ganhos
float uk = 0; // saida do controlador
float ck = 0; // voltz em porcentagem
float setp = 1; // setpoint
//Apresentação

void setup() {
  Serial.begin(9600);
  pinMode(PWMPin, OUTPUT); // configura pino como saída


}

void loop() {
    /*Serial.println("----------------*--------------------------- ");
    Serial.print("inpin ");
    Serial.println(analogRead(InPin));*/
  V = analogRead(InPin); // registra a leitura em v //printar columb // printar o numero de eletrons(concatenar)
  V = ((V * 5) / 1023);
  Serial.print("Setp:");
  Serial.print(setp); //printa volts
  Serial.print(" V:");
  Serial.print(V);//printa volts
  Serial.println();
  //Cálculo do erro
  ek1 = setp - V ;
    /*Serial.print("ek1 ");
    Serial.print(ek1);
    Serial.println("");*/
  //PID
  // proporcional
  p = Kp * ek1;
  /* Serial.print(p);
    Serial.print("/");*/
  //integral
  if (PWM >= 0 && PWM <= 255)
  {
    i += ((ek + ek1 / 2) * dt * Ki);
  }
  /*else if(PWM>255){
    i=i;
    } */
  else
  {
    i = 0;
  }
  /*Serial.print(i);
    Serial.print("/");*/
  //derivativo
  d = Kd * ((ek - ek1) / dt);
  /* Serial.println(d);*/

  // soma de todos os componentes
  pid = p + i + d;
   /* Serial.print("pid ");
    Serial.print(pid);
    Serial.println("");*/
  //adicionando controlador
  //implementar no circuito

  PWM = map(pid, -4098, 4098, 0, 255) ; //sinal pwm que será aplicado // 
  analogWrite(PWMPin, PWM); // enviando sinal pwm para o pino
   /*Serial.print("pwm ");
   Serial.print(PWM);
   Serial.println("");*/
  uk = (PWM * 100 / 255);
   ek = ek1;
  delay(dt); // define o tempo de atualização do circuito
}
