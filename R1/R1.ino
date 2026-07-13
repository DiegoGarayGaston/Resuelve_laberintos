/*
====================================================
      CONFIGURACION DE PINES
====================================================
*/

// ---------- TB6612FNG ----------

// Motor A (Izquierdo)
const byte PWMA = 5;
const byte AIN1 = 2;
const byte AIN2 = 3;

// Motor B (Derecho)
const byte PWMB = 6;
const byte BIN1 = 7;
const byte BIN2 = 8;

// Standby
const byte STBY = 4;


// ---------- ULTRASONICO IZQUIERDO ----------
const byte TRIG_LEFT = 6;
const byte ECHO_LEFT = 5;

// ---------- ULTRASONICO CENTRO ----------
const byte TRIG_FRONT = 4;
const byte ECHO_FRONT = 3;

// ---------- ULTRASONICO DERECHO ----------
const byte TRIG_RIGHT = A1;
const byte ECHO_RIGHT = A2;


//====================================================
// CONFIGURACION
//====================================================

const int VELOCIDAD = 180;     // 0 - 255

void setup()
{
    Serial.begin(9600);

    // Motor A
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);

    // Motor B
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);

    // Standby
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);

    // Sensores
    pinMode(TRIG_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);

    pinMode(TRIG_FRONT, OUTPUT);
    pinMode(ECHO_FRONT, INPUT);

    pinMode(TRIG_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);
}

void loop()
{
    int izquierda = medirDistancia(TRIG_LEFT, ECHO_LEFT);
    int frente    = medirDistancia(TRIG_FRONT, ECHO_FRONT);
    int derecha   = medirDistancia(TRIG_RIGHT, ECHO_RIGHT);

    Serial.print("Izq: ");
    Serial.print(izquierda);

    Serial.print("  Frente: ");
    Serial.print(frente);

    Serial.print("  Der: ");
    Serial.println(derecha);

    delay(200);
}


//====================================================
// FUNCIONES ULTRASONICOS
//====================================================

int medirDistancia(byte trig, byte echo)
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);

    digitalWrite(trig, LOW);

    long tiempo = pulseIn(echo, HIGH, 30000);

    if (tiempo == 0)
        return 400;   // Sin detección

    return tiempo * 0.0343 / 2;
}


//====================================================
// FUNCIONES DE MOVIMIENTO
//====================================================

void avanzar(int velocidad)
{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

    analogWrite(PWMA, velocidad);
    analogWrite(PWMB, velocidad);
}

void retroceder(int velocidad)
{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);

    analogWrite(PWMA, velocidad);
    analogWrite(PWMB, velocidad);
}

void girarIzquierda(int velocidad)
{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

    analogWrite(PWMA, velocidad);
    analogWrite(PWMB, velocidad);
}

void girarDerecha(int velocidad)
{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);

    analogWrite(PWMA, velocidad);
    analogWrite(PWMB, velocidad);
}

void detener()
{
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
}