# STM32_Serial_Frame

#### 项目基于STM32F103C8T6芯片，可移植到其他芯片中。

#### 项目基于FreeRTOS和STM32 CubeMX工具包，其中有修改stm32f1xx_hal_uart.c(文件在根目录下)文件，针对STM32CUBEMX工具自动生成的代码，只需将\Drivers\STM32F1xx_HAL_Driver\Src中的同名文件替换即可。

#### 项目中采用循环队列方式存储收发数据，队列空间大小可在UsartDriver.c中进行修改。

#### 项目代码可免费使用。

##### 如有Bug，望反馈交流（QQ：2281280195）。

##### 用户代码在文件 /src/UserTask.c， 用户可针对修改

#####  作者：Awesome                                      
#####  时间： 2018-11-23
