#include <ModbusRTUSlave.h>

#include <Wire.h>
#include <Adafruit_ADS1X15.h>
 
#define MODBUS_SERIAL Serial
#define MODBUS_BAUD 19200
#define MODBUS_CONFIG SERIAL_8N1
#define MODBUS_UNIT_ID 1

const int16_t dePin = 13;
ModbusRTUSlave modbus(MODBUS_SERIAL, dePin);
const uint8_t numHoldingRegisters = 6;
uint16_t holdingRegisters[numHoldingRegisters];

Adafruit_ADS1115 ads;

void setup() {
  modbus.configureHoldingRegisters(holdingRegisters, numHoldingRegisters);
  MODBUS_SERIAL.begin(MODBUS_BAUD, MODBUS_CONFIG);
  modbus.begin(MODBUS_UNIT_ID, MODBUS_BAUD, MODBUS_CONFIG);

  ads.begin();  // Инициализация модуля ADS1115
}

void loop() {
  int16_t adc0;
  adc0 = ads.readADC_SingleEnded(0);  // Чтение значения с аналогового входа 0
  
  modbus.poll();
  holdingRegisters[0] = adc0;
}
