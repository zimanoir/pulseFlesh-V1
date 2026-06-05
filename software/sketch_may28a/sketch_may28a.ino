#include <WiFi.h>
#include <ArduinoOSCWiFi.h> // Библиотека для работы с OSC на ESP32

// НАСТРОЙКИ WI-FI (Ваши данные)
const char* ssid     = "zimanoir"; 
const char* password = "zimazima"; 

// НАСТРОЙКИ OSC (Ваш компьютер с Max/MSP)
const char* oscHost = "172.20.10.7"; // IP компьютера
const int oscPort = 6660;             // Порт для Max

// Пины подключения AD8232 (к вашей плате)
const int ECG_OUTPUT_PIN = 36; // Пин VP
const int LO_PLUS_PIN = 21;    // Пин D21
const int LO_MINUS_PIN = 15;   // Пин D15

void setup() {
  Serial.begin(115200);

  pinMode(LO_PLUS_PIN, INPUT);
  pinMode(LO_MINUS_PIN, INPUT);

  // Подключение к Wi-Fi
  Serial.print("Подключение к ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Ждем подключения
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi подключен!");
  Serial.print("IP-адрес ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int ecgValue = 0;

  // Проверка контакта электродов
  if ((digitalRead(LO_PLUS_PIN) == 1) || (digitalRead(LO_MINUS_PIN) == 1)) {
    ecgValue = 0; // Если отвалились — шлем 0
  } else {
    ecgValue = analogRead(ECG_OUTPUT_PIN); // Читаем ЭКГ
    
    // Ваша проверка на высокий пик
    if (ecgValue > 2500){
      Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    }
  }

  // ОТПРАВКА OSC СООБЩЕНИЯ в Max/MSP
  OscWiFi.send(oscHost, oscPort, "/electrodes/ecg", ecgValue);

  // Локальный мониторинг в Serial
  Serial.println(ecgValue);

  // Задержка 5 мс для стабильности потока данных
  delay(5); 
}