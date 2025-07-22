[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver STS21

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sts21/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

Sensirion的新型溫度感測器STS21即將在尺寸和智慧方面設定新的標準：嵌入3 x 3mm管脚和1.1mm高度的回流焊雙扁平無引線（DFN）封裝中，它以數位I2C格式提供校準、線性化的訊號。 STS21採用與Sensirion成功並經行業驗證的SHT2x濕度和溫度感測器相同的CMOSens ® 科技，提供卓越的效能和可靠性。 ±0.2°C溫度規格允許在對溫度精度要求高的應用中實施STS21。 每個感測器都單獨校準和測試。 批次標識列印在感測器上，電子標識碼存儲在晶片上–可以通過命令讀取。 此外，STS21的分辯率可以通過命令更改（11比特到14比特），可以檢測到電池電量不足，校驗和有助於提高通信可靠性。 隨著感測器的改進和小型化，效能價格比得到了提高——最終，任何設備都應受益於最先進的節能操作模式。

LibDriver STS21是LibDriver推出的STS21全功能驅動，該驅動提供溫度連續模式讀取和溫度單次模式讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver STS21的源文件。

/interface目錄包含了LibDriver STS21與平台無關的IIC總線模板。

/test目錄包含了LibDriver STS21驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver STS21編程範例。

/doc目錄包含了LibDriver STS21離線文檔。

/datasheet目錄包含了STS21數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/sts21/index.html](https://www.libdriver.com/docs/sts21/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。