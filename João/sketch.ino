#include <WiFi.h>
#include <HTTPClient.h>
#include <SoftwareSerial.h>

#define led_verde 2 // Pino utilizado para controle do led verda
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led azul

const int pinoBotao = 18;  // número do pino botão
int estadoBotao = 0;  // variável que lê o status do botão

const int Pinpldr = 4;  // Número do pino do ldr(sensor luz)
int limiteLuz=600;

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_amarelo,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);

  // Inicialização das entradas
  pinMode(pinoBotao, INPUT); // inicializa o botão como input

  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(115200); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  // Verifica estado do botão
  estadoBotao = digitalRead(pinoBotao);
  if (estadoBotao == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

    if (httpResponseCode>0) {
      Serial.print("HTTP respondeu: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Error no código: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi desconetado");
  }
}

void loop() {
  int ldrstatus=analogRead(Pinpldr);

  if(ldrstatus>=limiteLuz){
    Serial.print("Está escuro acenda o led amarelo");
    Serial.println(ldrstatus);
    digitalWrite(led_amarelo , HIGH);
    delay(1000)
    digitalWrite(led_amarelo , LOW);

  }else{
    Serial.print("está claro, fucione normalmente");
    Serial.println(ldrstatus);
  
    digitalWrite(led_vermelho , LOW);
    digitalWrite(led_verde, HIGH);
    delay(3000)
    digitalWrite(led_verde, LOW);
    digitalWrite(led_amarelo , HIGH);
    delay(2000)
    digitalWrite(led_amarelo , LOW);
    digitalWrite(led_vermelho , HIGH);
    delay(5000)
  }

  if(led_vermelho = HIGH && int estadoBotao = 1){
    delay(1000)
    digitalWrite(led_verde, HIGH);
    return
  }
}