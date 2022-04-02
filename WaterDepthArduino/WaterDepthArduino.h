/**
 * @file WaterDepthArduino.h
 * @brief WaterDepthArduino BSP settings
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022  RedlightASl
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date    <th>Version  <th>Author  <th>Description
 * <tr><td>2022-04-02  <td>1.0      <td>wangh   <td>Content
 * </table>
 */
#ifndef __WDA_BSP_H
#define __WDA_BSP_H

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


#endif
