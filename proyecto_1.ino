const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 3;
const int motorPin = 5;

long duracion;
int distancia;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  digitalWrite(trigPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(motorPin, LOW);

  Serial.begin(9600);
}

void loop() {
  distancia = medirDistancia();

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Muy lejos: nada
  if (distancia > 100) {
    noTone(buzzerPin);
    digitalWrite(motorPin, LOW);
    delay(200);
  }

  // Distancia media: solo buzzer lento
  else if (distancia > 60 && distancia <= 100) {
    digitalWrite(motorPin, LOW);

    tone(buzzerPin, 1000);
    delay(150);
    noTone(buzzerPin);
    delay(250);
  }

  // Cerca: solo buzzer más rápido
  else if (distancia > 30 && distancia <= 60) {
    digitalWrite(motorPin, LOW);

    tone(buzzerPin, 1500);
    delay(100);
    noTone(buzzerPin);
    delay(120);
  }

  // Muy cerca: buzzer + motor
  else if (distancia <= 30) {
    digitalWrite(motorPin, HIGH);

    tone(buzzerPin, 2000);
    delay(120);
    noTone(buzzerPin);
    delay(80);
  }

  // Si no detecta bien
  else {
    noTone(buzzerPin);
    digitalWrite(motorPin, LOW);
    delay(200);
  }
}

int medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH, 30000);

  if (duracion == 0) {
    return 999;
  }

  int dist = duracion * 0.034 / 2;
  return dist;
}