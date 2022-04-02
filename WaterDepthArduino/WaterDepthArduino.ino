#include <stdint.h>
#include <Wire.h>
#include "MS5837.h"
//#include "WaterDepthArduino.h"

#define STATE_LED PB8
#define SENSER_SDA PB7
#define SENSER_SCL PB6
#define KEY_IN PB10
#define Q_OUT PB9


#define UART_FAST 921600
#define UART_REGULAR 115200

//kg/m^3 (997 freshwater, 1029 for seawater)
#define FRESH_WATER_DENSITY 997
#define SEA_WATER_DENSITY 1029


struct SensorData
{
  uint8_t Temperature_H;
  uint8_t Temperature_L;
  uint8_t DepthOfWater_H;
  uint8_t DepthOfWater_L;
};
typedef struct SensorData MS5837Data_t;

struct TemperatureData
{
  uint8_t Temp_H;
  uint8_t Temp_L;
};
typedef struct TemperatureData TemperatureData_t;

struct DepthDate
{
  uint8_t Depth_H;
  uint8_t Depth_L;
};
typedef struct DepthDate DepthDate_t;


MS5837 sensor;

//MS5837Data WString = { 0 };
//ReadData_Temp WTemp = { 0 };
//ReadData_Depth WDepth = { 0 };

void setup()
{
  pinMode(STATE_LED, OUTPUT);
  pinMode(Q_OUT, OUTPUT);
  digitalWrite(STATE_LED, LOW);
  digitalWrite(Q_OUT, LOW);
  pinMode(KEY_IN, INPUT);

  Serial.begin(UART_FAST);

  Wire.setSDA(SENSER_SDA);
  Wire.setSCL(SENSER_SCL);
  Wire.begin();

  // Initialize pressure sensor
  // Returns true if initialization was successful
  // We can't continue with the rest of the program unless we can initialize the sensor
  while (!sensor.init())
  {
    digitalWrite(STATE_LED, HIGH);
    delay(500);
    digitalWrite(STATE_LED, LOW);
    delay(500);
  }
  delay(500);
  digitalWrite(STATE_LED, LOW);

  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(SEA_WATER_DENSITY); // kg/m^3 (997 freshwater, 1029 for seawater)
}

void loop()
{
  sensor.read(); // Update pressure and temperature readings

  //  *WTemp = sensor.temperature() * 100;
  //  *WDepth = sensor.depth() * 100;
  //  Serial.write(WString, 4);

  Serial.print(sensor.depth());
  Serial.print("\t");
  Serial.print(sensor.temperature());
  Serial.print("\t");
  Serial.print(sensor.pressure());
  Serial.print("\t");
  Serial.println(sensor.altitude());
}
