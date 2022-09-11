
int motA0 = 12;
int motA1 = 13;

int motB0 = 10;
int motB1 = 11;

int enable1 = 2;
int enable2 = 3;

int echo = 6;
int triger = 7;

int vel = 150;

int distancia, luz;

int sen0 = A0; 
int sen1 = A1; 

unsigned int referenciaBlanco = 100;
unsigned int referenciaSinSuperficie = 20;

void setup()
{
  delay(3000);
  Serial.begin(9600);
  Serial.println("setting up");

  pinMode(sen0, INPUT);
  pinMode(sen1, INPUT);

  pinMode(motA0, OUTPUT);
  pinMode(motA1, OUTPUT);
  pinMode(motB0, OUTPUT);
  pinMode(motB1, OUTPUT);

  pinMode(echo, INPUT);
  pinMode(triger, OUTPUT);
  digitalWrite(triger, LOW);
  digitalWrite(motA0, LOW);
  digitalWrite(motA1, LOW);
  digitalWrite(motB0, LOW);
  digitalWrite(motB1, LOW);

  analogWrite(enable1, 255);
  analogWrite(enable2, 255);

  Serial.println("setted up");
}
int cont = 1;
void loop()
{
  Serial.println("Running");
distancia = distancia_medida();
int lecturaCNY70s0 = analogRead(sen0);
int lecturaCNY70s1 = analogRead(sen1);

while(distancia > 20)
  {
    lecturaCNY70s0 = analogRead(sen0);
    lecturaCNY70s1 = analogRead(sen1);
    
    if(EstaEnNegro(lecturaCNY70s0,lecturaCNY70s1)){
      atras();
    }
    else{
      izquierda();
    }
    distancia = distancia_medida();
  }
  detener();
  
  while(distancia <= 20)
  {
    lecturaCNY70s0 = analogRead(sen0);
    lecturaCNY70s1 = analogRead(sen1);
    if(EstaEnNegro(lecturaCNY70s0,lecturaCNY70s1)){
      atras();
      break;
    }else{
      adelante();
    }
    luz = 901;//analogRead(A1);
    distancia = distancia_medida();
  }
}

bool EstaEnNegro(int lecturaCNY70s0, int lecturaCNY70s1){
  Serial.println(lecturaCNY70s0);
  Serial.println(lecturaCNY70s1);
  if(lecturaCNY70s0 <= 5 || lecturaCNY70s1 <= 5) {
    Serial.println("Linea Negra");
    return true;
    
  }
  else if(lecturaCNY70s0 >= 6|| lecturaCNY70s1 >= 6){
    Serial.println("Superficie Blanca");
    return false;
  }
}

long distancia_medida()
{

  long t;
  long d;

  digitalWrite(triger, HIGH);
  delayMicroseconds(10);
  digitalWrite(triger, LOW);

  t = pulseIn(echo, HIGH);
  d = t / 59;
  
  return d;
}

void detener()
{
  Serial.println("Stopping");
  digitalWrite(motB0, LOW);
  digitalWrite(motB1, LOW);
  digitalWrite(motA0, LOW);
  digitalWrite(motA1, LOW);
}

void atras()
{
  Serial.println("atras");
  digitalWrite(motB0, LOW);
  digitalWrite(motB1, HIGH);
  digitalWrite(motA0, HIGH);
  digitalWrite(motA1, LOW);
  delay(200);
}

void adelante()
{
  Serial.println("adelante");
  digitalWrite(motB0, LOW);
  digitalWrite(motB1, HIGH);
  digitalWrite(motA0, LOW);
  digitalWrite(motA1, HIGH);
}
void derecha()
{
  Serial.println("derecha");
  digitalWrite(motB0, LOW);
  digitalWrite(motB1, HIGH);
  digitalWrite(motA0, LOW);
  digitalWrite(motA1, HIGH);
}
void izquierda()
{
//  Serial.println("izquierda");
  digitalWrite(motB0, LOW);
  digitalWrite(motB1, HIGH);
  digitalWrite(motA0, HIGH);
  digitalWrite(motA1, LOW);
}
