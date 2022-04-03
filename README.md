# ROV_WaterDepthAnalysisBoard-MS5837

A opensource AnalysisBoard for MS5837 Water Depth Sensor

[![License: GPL-3.0](https://img.shields.io/badge/license-GPL--3.0-blue)](https://github.com/redlightASl/ROV_OS-Nitori/blob/master/LICENSE)

一套开源的MS5837水深传感器解算板

* 硬件部分

  stm32f103c8t6核心板，可以使用gd32作为替换

  板载

  * 两个I2C传感器连接座
  	* SCL：PB6
  	* SDA：PB7
  * 板载LED（PB8）
  * 可选连接到5V/3.3V的ADC1（PA1）

  引出

  * ADC1（PA2、PA3）
  * UART1（PA9、PA10）
  * 调试接口（SWD+JTAG）
  * NRST复位引脚
  * LED端口（PB8）
  * 两个普通IO pin（PB9、PB10）
  * SPI1（PA5、PA6、PA7）

* 软件部分

	分别用

	* Arduino：基于https://github.com/bluerobotics/BlueRobotics_MS5837_Library的ms5837库
	* stm32 HAL库：基于https://github.com/ekinbasarkomur/STM32_MS5837的ms5837库
	* stm32 标准库：根据已有函数和正点原子软件i2c编写的ms5837库
	
	进行了实现

