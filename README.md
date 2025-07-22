[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver STS21

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sts21/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

STS21, the new temperature sensor of Sensirion is about to set new standards in terms of size and intelligence: Embedded in a reflow solderable Dual Flat No leads (DFN) package of 3 x 3mm foot print and 1.1mm height it provides calibrated, linearized signals in digital, I2C format.Using the same CMOSens® technology as Sensirion‟s successful and industry proven SHT2x humidity and temperature sensors, the STS21 offers superior performance and reliability. The ±0.2°C temperature specification allows for implementation of the STS21 in applications with high demands on temperature accuracy.Every sensor is individually calibrated and tested. Lot identification is printed on the sensor and an electronic identification code is stored on the chip – which can be read out by command. Furthermore, the resolution of STS21 can be changed by command (11bit up to 14bit), low battery can be detected and a checksum helps to improve communication reliability.With made improvements and the miniaturization of the sensor the performance-to-price ratio has been improved – and eventually, any device should benefit from the cutting edge energy saving operation mode.

LibDriver STS21 is a full-featured driver of STS21 launched by LibDriver.It provides functions of temperature continuous mode reading and temperature single mode reading. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver STS21 source files.

/interface includes LibDriver STS21 IIC platform independent template.

/test includes LibDriver STS21 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver STS21 sample code.

/doc includes LibDriver STS21 offline document.

/datasheet includes STS21 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

### Document

Online documents: [https://www.libdriver.com/docs/sts21/index.html](https://www.libdriver.com/docs/sts21/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.