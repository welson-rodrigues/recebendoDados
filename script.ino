
#include "WiFi.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050.h>

// Configurações do display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Sensor MPU6050
MPU6050 mpu;

// Variáveis com dados do sensor
int16_t ax, ay, az;
int16_t gx, gy, gz;
float temperatureC;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro ao inicializar o display!");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Inicialização do MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("Falha na conexão com o MPU6050");
    while (1);
  }

  display.setCursor(0, 0);
  display.println("MPU6050 Iniciado!");
  display.display();
  delay(1000);
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  int16_t tempRaw = mpu.getTemperature();
  temperatureC = (tempRaw / 340.0) + 36.53;


  // Mostra os dados no display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Acelerometro:");
  display.print("X: "); display.println(ax);
  display.print("Y: "); display.println(ay);
  display.print("Z: "); display.println(az);



  display.println("Temp:");
  display.print(temperatureC);
  display.println(" C");

  display.println("Giroscopio:");
  display.print("X: "); display.println(gx);
  display.print("Y: "); display.println(gy);
  display.print("Z: "); display.println(gz);

  display.display();
  delay(500);
}
