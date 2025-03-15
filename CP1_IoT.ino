#include <ArduinoJson.h> // Inclui a biblioteca ArduinoJson
#include <DHT.h>          // Inclui a biblioteca DHT
#include <Servo.h>        // Inclui a biblioteca Servo

// --- Definição dos pinos ---
const int pino_dht = 2;   // Pino do sensor DHT11
const int pino_ldr = A0;  // Pino do sensor LDR
const int pino_servo = 9; // Pino do servo motor

// --- Variáveis globais ---
float temperatura, umidade, temperaturaFahrenheit; // Variáveis para armazenar temperatura e umidade
int luminosidade;                                  // Variável para armazenar luminosidade
DHT dht(pino_dht, DHT11);                           // Objeto DHT
Servo myservo;                                     // Objeto Servo

// --- Função setup ---
void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  dht.begin();         // Inicializa o sensor DHT11
  myservo.attach(pino_servo); // Conecta o servo ao pino

  Serial.println("======================================");
  Serial.println("CP1 -- : )");
  Serial.println("======================================");
}

// --- Função loop ---
void loop() {
  leitura_sensores(); // Chama a função para leitura dos sensores
  controle_servo();   // Chama a função para controle do servo
}

// --- Função para leitura dos sensores ---
void leitura_sensores() {
  static unsigned long lastReadTime = 0;
  if (millis() - lastReadTime >= 3000) {
    lastReadTime = millis();

    // --- Leitura dos sensores ---
    temperatura = dht.readTemperature();
    umidade = dht.readHumidity();
    luminosidade = analogRead(pino_ldr);

    // --- Conversão para Fahrenheit ---
    temperaturaFahrenheit = temperatura;
    // --- Verificação de erros ---
    if (isnan(umidade) || isnan(temperatura)) {
      Serial.println("[MonteCarloDigital]:( ERRO: Falha na leitura do sensor DHT!");
      return;
    }

    // --- Criação do documento JSON ---
    StaticJsonDocument<200> doc;
    doc["sensor"] = "DHT11";
    doc["temperatura"] = temperaturaFahrenheit;
    doc["umidade"] = umidade;
    doc["luminosidade"] = luminosidade;

    // --- Serialização do JSON ---
    String json;
    serializeJson(doc, json);
    Serial.println(json); // Envia o JSON pela serial
  }
}

// --- Função para controle do servo motor ---
void controle_servo() {
  if (Serial.available() > 0) {
    int comando = Serial.parseInt();
    switch (comando) {
      case 1:
        myservo.write(0);  // Ângulo 1: 0 graus
        break;
      case 2:
        myservo.write(90); // Ângulo 2: 90 graus
        break;
      case 3:
        myservo.write(180); // Ângulo 3: 180 graus
        break;
      default:
        Serial.println("Comando inválido!");
    }
  }
}