[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver STS21

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sts21/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

Sensirion社の新型温度センサーSTS21は、サイズとインテリジェンスの両面で新たな基準を確立しようとしています。リフローはんだ付け可能なDFN（Dual Flat No Leads）パッケージ（3 x 3mm、高さ1.1mm）に収められており、デジタルI2Cフォーマットで校正済み・線形化された信号を提供します。業界で実証済みのSensirion社製湿度・温度センサーSHT2xと同じCMOSens®技術を採用したSTS21は、優れた性能と信頼性を提供します。±0.2℃の温度仕様により、温度精度が厳しく要求されるアプリケーションにもSTS21を実装できます。すべてのセンサーは個別に校正および試験されています。センサーにはロットIDが印刷され、チップには電子識別コードが保存されており、コマンドで読み取ることができます。さらに、STS21 の解像度はコマンド (11 ビットから 14 ビットまで) で変更でき、低電池を検出でき、チェックサムにより通信の信頼性が向上します。センサーの改良と小型化により、性能と価格の比率が向上し、最終的にはあらゆるデバイスが最先端の省エネ動作モードの恩恵を受けることができるようになります。

LibDriver STS21 は、LibDriver によってリリースされた STS21 のフル機能ドライバーです。温度連続モード読み取りと温度単一モード読み取りの機能を提供します。LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver STS21のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver STS21用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver STS21ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver STS21プログラミング例が含まれています。

/ docディレクトリには、LibDriver STS21オフラインドキュメントが含まれています。

/ datasheetディレクトリには、STS21データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/sts21/index.html](https://www.libdriver.com/docs/sts21/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。