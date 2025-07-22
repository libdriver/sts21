[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver STS21

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sts21/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

Sensirion的新型温度传感器STS21即将在尺寸和智能方面设定新的标准：嵌入3 x 3mm管脚和1.1mm高度的回流焊双扁平无引线（DFN）封装中，它以数字I2C格式提供校准、线性化的信号。STS21采用与Sensirion成功并经行业验证的SHT2x湿度和温度传感器相同的CMOSens®技术，提供卓越的性能和可靠性。±0.2°C温度规格允许在对温度精度要求高的应用中实施STS21。每个传感器都单独校准和测试。批次标识打印在传感器上，电子标识码存储在芯片上–可以通过命令读取。此外，STS21的分辨率可以通过命令更改（11位到14位），可以检测到电池电量不足，校验和有助于提高通信可靠性。随着传感器的改进和小型化，性能价格比得到了提高——最终，任何设备都应受益于最先进的节能操作模式。

LibDriver STS21是LibDriver推出的STS21全功能驱动，该驱动提供温度连续模式读取和温度单次模式读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver STS21的源文件。

/interface目录包含了LibDriver STS21与平台无关的IIC总线模板。

/test目录包含了LibDriver STS21驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver STS21编程范例。

/doc目录包含了LibDriver STS21离线文档。

/datasheet目录包含了STS21数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_sts21_basic.h"

uint8_t res;
uint32_t i;
float temperature;

/* basic init */
res = sts21_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    sts21_interface_delay_ms(1000);

    /* read data */
    res = sts21_basic_read((float *)&temperature);
    if (res != 0)
    {
        (void)sts21_basic_deinit();

        return 1;
    }

    /* output */
    sts21_interface_debug_print("sts21: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
    sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature);
    
    ...
}

...
    
/* basic deinit */
(void)sts21_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/sts21/index.html](https://www.libdriver.com/docs/sts21/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。