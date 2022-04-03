#ifndef __MS5837_H
#define __MS5837_H
#include <stdint.h>

//model
#define MS5837_30BA 0x00
#define MS5837_02BA 0x01

#define MS5837_ADDR               0x76  
#define MS5837_RESET              0x1E
#define MS5837_ADC_READ           0x00
#define MS5837_CONVERT_D1_8192    0x4A
#define MS5837_CONVERT_D2_8192    0x5A

//传感器PROM起始地址
#define MS5837_PROM_READ          0xA0
//压力灵敏度
#define MS5837_READ_C1            0xA2
//压力补偿
#define MS5837_READ_C2            0xA4
//温度压力灵敏度系数
#define MS5837_READ_C3            0xA6
//温度系数的压力补偿
#define MS5837_READ_C4            0xA8
//参考温度
#define MS5837_READ_C5            0xAA
//温度系数的温度
#define MS5837_READ_C6            0xAC

//kg/m^3 (997 freshwater, 1029 for seawater)
#define FRESH_WATER_DENSITY 997
#define SEA_WATER_DENSITY 1029

static const float Pa = 100.0f;
static const float Bar = 0.001f;
static const float mBar = 1.0f;

static const float temperature_c = 100.0f;

struct MS5837_Attribute
{
	uint8_t model; //MS5837 model (Default:MS5837_30BA)
	float fluidDensity; //Fluid density (Default:SEA_WATER_DENSITY)
	float tempertureUnit; //Temperature unit (Default:C)
	float pressureUnit; //Pressure unit (Default:mBar)
};
typedef struct MS5837_Attribute MS5837_Attribute_t;

struct MS5837_OriginData
{
    int32_t OriginTemperature;
	int32_t OriginPressure;
	uint16_t SensorOriginData[8];
	uint32_t D1;
	uint32_t D2;
};
typedef struct MS5837_OriginData MS5837_OriginData_t;

struct MS5837_Data
{
    float temperture;
    float pressure;
};
typedef struct MS5837_Data MS5837_Data_t;

struct MS5837_FIR_Parameter
{
    float filter[10];
    float sum;
    uint8_t cnt;
};
typedef struct MS5837_FIR_Parameter MS5837_FIR_Parameter_t;




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

void MS5837_Init(void);
void MS5837_getData(float* output_temperature, float* output_pressure);
void MS5837_ReadDepth(float* output_depth);
void MS5837_ReadDepth_filtered(float* output_depth);

#endif
