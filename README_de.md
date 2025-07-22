[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver STS21

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/sts21/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der STS21, der neue Temperatursensor von Sensirion, setzt neue Maßstäbe in puncto Größe und Intelligenz: Eingebettet in ein reflow-lötbares Dual Flat No Leads (DFN)-Gehäuse mit 3 x 3 mm Grundfläche und 1,1 mm Höhe liefert er kalibrierte, linearisierte Signale im digitalen I2C-Format. Dank der gleichen CMOSens®-Technologie wie Sensirions erfolgreiche und industrieerprobte SHT2x-Feuchtigkeits- und Temperatursensoren bietet der STS21 überlegene Leistung und Zuverlässigkeit. Die Temperaturgenauigkeit von ±0,2 °C ermöglicht den Einsatz des STS21 in Anwendungen mit hohen Anforderungen an die Temperaturgenauigkeit. Jeder Sensor wird einzeln kalibriert und geprüft. Die Chargenbezeichnung ist auf dem Sensor aufgedruckt, und ein elektronischer Identifikationscode ist auf dem Chip gespeichert – dieser kann per Befehl ausgelesen werden. Darüber hinaus kann die Auflösung des STS21 per Befehl geändert werden (11 Bit bis 14 Bit), ein schwacher Batteriestand kann erkannt werden und eine Prüfsumme trägt zur Verbesserung der Kommunikationszuverlässigkeit bei. Durch die vorgenommenen Verbesserungen und die Miniaturisierung des Sensors wurde das Preis-Leistungs-Verhältnis verbessert – und letztendlich sollte jedes Gerät vom hochmodernen Energiesparmodus profitieren.

LibDriver STS21 ist der voll funktionsfähige Treiber von STS21, der von LibDriver eingeführt wurde. Er bietet Funktionen für die Temperaturanzeige im Dauermodus und die Temperaturanzeige im Einzelmodus. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver STS21-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver STS21 IIC.

/test enthält den Testcode des LibDriver STS21-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver STS21-Beispielcode.

/doc enthält das LibDriver STS21-Offlinedokument.

/Datenblatt enthält STS21-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/sts21/index.html](https://www.libdriver.com/docs/sts21/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.