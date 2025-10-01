#include <ModbusRTUSlave.h>

#include <Wire.h>
#include <Adafruit_ADS1X15.h>

#include <7semi_DS18B20.h>
 
#define MODBUS_SERIAL Serial
#define MODBUS_BAUD 19200
#define MODBUS_CONFIG SERIAL_8N1
#define MODBUS_UNIT_ID 1

const int16_t dePin = 13;
ModbusRTUSlave modbus(MODBUS_SERIAL, dePin);
const uint8_t numHoldingRegisters = 6;
uint16_t holdingRegisters[numHoldingRegisters];

Adafruit_ADS1115 ads;

DS18B20_7semi sensor(11);  // data pin

void setup() {
  modbus.configureHoldingRegisters(holdingRegisters, numHoldingRegisters);
  MODBUS_SERIAL.begin(MODBUS_BAUD, MODBUS_CONFIG);
  modbus.begin(MODBUS_UNIT_ID, MODBUS_BAUD, MODBUS_CONFIG);

  ads.begin();  // Инициализация модуля ADS1115

  uint8_t count = sensor.searchDevices();
}

void loop() {
  int16_t adc0;
  int16_t adc3;
  adc0 = ads.readADC_SingleEnded(0);  // Чтение значения с аналогового входа 0
  adc3 = ads.readADC_SingleEnded(3);  // Чтение значения с аналогового входа 3
  holdingRegisters[0] = adc0;
  holdingRegisters[3] = adc3;

  uint8_t addr[8];
  if (sensor.getAddress(0, addr)) {
    float t = sensor.readTemperature(addr);
    holdingRegisters[2] = t * 100;
  }

  modbus.poll();

  analogWrite(3, holdingRegisters[1]);      // отправляем на мосфет
  
  delay(100);
}
