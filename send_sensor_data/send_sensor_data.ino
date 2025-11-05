#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Credenciais da sua rede Wi-Fi
const char* ssid = "HTOIOT";
const char* password = "iot123456";

// Configuração do ThingSpeak
String apiKey = "TG0WAU5CS4XL214F"; // Ex: AAAAXXXXBBBBCCCC
const char* server = "api.thingspeak.com";

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Conexão Wi-Fi
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Gera um valor aleatório para simular um sensor (entre 0 e 100)
  int valorSensor = random(101); 
  
  // Monta a URL para o HTTP GET
  // O formato é: api.thingspeak.com/update?api_key=SEU_KEY&field1=VALOR
  String url = "http://api.thingspeak.com/update?api_key=";
  url += apiKey;
  url += "&field1="; // 'field1' deve ser o nome que você definiu no seu canal
  url += String(valorSensor); // Adiciona o valor simulado
  
  Serial.print("Enviando GET para: ");
  Serial.println(url);

  WiFiClient client;
  HTTPClient http;

  // Inicia a conexão
  http.begin(client, url); 
  
  // Executa a requisição GET
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    // Requisição bem-sucedida, imprime o código e a resposta
    String payload = http.getString();
    Serial.print("Código HTTP: ");
    Serial.println(httpCode);
    Serial.print("Resposta do Servidor: ");
    Serial.println(payload); // ThingSpeak retorna um número > 0 se o envio for OK
  } else {
    // Erro na requisição
    Serial.print("Erro no HTTP GET. Código: ");
    Serial.println(httpCode);
  }
  
  http.end(); // Fecha a conexão
  
  // ThingSpeak tem um limite de 15 segundos entre atualizações.
  Serial.println("Aguardando 20 segundos...");
  delay(20000); 
}
