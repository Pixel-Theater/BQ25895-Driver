# TI BQ25895 datasheet

Converted from PDF to Markdown using [Marker](https://github.com/datalab-to/marker).


---

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)** SLUSC88A –MARCH 2015–REVISED MAY 2016

### **bq25895 I <sup>2</sup>C Controlled Single Cell 5-A Fast Charger with MaxChargeTM for High Input Voltage and Adjustable Voltage 3.1-A Boost Operation**

Technical [Documents](http://www.ti.com/product/bq25895?dcmp=dsproject&hqs=td&#doctype2)

## **1 Features**

- <sup>1</sup> High Efficiency 5-A, 1.5-MHz Switch Mode Buck Charge
  - 93% Charge Efficiency at 2 A and 91% Charge Efficiency at 3 A Charge Current
  - Optimize for High Voltage Input (9 V to 12 V)
  - Low Power PFM mode for Light Load Operations
- Boost Mode Operation with Adjustable Output from 4.5 V to 5.5 V
  - Selectable 500-KHz to 1.5-MHz Boost Converter with up to 3.1-A Output
  - 93% Boost Efficiency at 5 V at 1 A Output
- Integrated Control to Switch Between Charge and Boost Mode
- Single Input to Support USB Input and Adjustable High Voltage Adapters
  - Support 3.9-V to 14-V Input Voltage Range
  - Input Current Limit (100 mA to 3.25 A with 50 mA resolution) to Support USB2.0, USB3.0 standard and High Voltage Adapters
  - Maximum Power Tracking by Input Voltage Limit up-to 14V for Wide Range of Adapters
  - Auto Detect USB SDP, CDP, DCP, and Nonstandard Adapters
- Input Current Optimizer (ICO) to Maximize Input Power without Overloading Adapters
- Resistance Compensation (IRCOMP) from Charger Output to Cell Terminal
- Highest Battery Discharge Efficiency with 11-mΩ Battery Discharge MOSFET up to 9 A
- Integrated ADC for System Monitor (Voltage, Temperature, Charge Current)
- Narrow VDC (NVDC) Power Path Management
  - Instant-on Works with No Battery or Deeply Discharged Battery
  - Ideal Diode Operation in Battery Supplement Mode
- BATFET Control to Support Ship Mode, Wake Up, and Full System Reset
- Flexible Autonomous and I <sup>2</sup>C Mode for Optimal System Performance
- High Integration includes all MOSFETs, Current Sensing and Loop Compensation
- 12-µA Low Battery Leakage Current to Support Ship Mode

- High Accuracy
  - ±0.5% Charge Voltage Regulation
  - ±5% Charge Current Regulation
  - ±7.5% Input Current Regulation
- Safety
  - Battery Temperature Sensing for Charge and Boost Mode
  - Thermal Regulation and Thermal Shutdown

# **2 Applications**

- Power Bank, Mobile Wi-Fi Hotspot
- Wireless Bluetooth Speaker
- Portable Internet Devices

# **3 Description**

The bq25895 is a highly-integrated 5-A switch-mode battery charge management and system power path management device for single cell Li-Ion and Lipolymer battery. The devices support high input voltage fast charging. The low impedance power path optimizes switch-mode operation efficiency, reduces battery charging time and extends battery life during discharging phase. The I <sup>2</sup>C Serial interface with charging and system settings makes the device a truly flexible solution.

## **Device Information[\(1\)](#page-0-0)**

| PART NUMBER | PACKAGE   | BODY SIZE (NOM) |  |
|-------------|-----------|-----------------|--|
| bq25895     | WQFN (24) | 4.00mm x 4.00mm |  |
|             |           |                 |  |

(1) For all available packages, see the orderable addendum at the end of the datasheet.

## **Simplified Schematic**

![](_page_0_Figure_48.jpeg)

An IMPORTANT NOTICE at the end of this data sheet addresses availability, warranty, changes, use in safety-critical applications, intellectual property matters and other important disclaimers. PRODUCTION DATA.

## **4 Revision History**

**Changes from Original (March 2015) to Revision A Page**

2

# **5 Description (cont.)**

The device supports a wide range of input sources, including standard USB host port, USB charging port, and USB compliant adjustable high voltage adapter. To support fast charging using adjustable high voltage adapter, the bq25895 provides support MaxChargeTM using D+/D– pins and DSEL pin for USB switch control. In addition, the device includes interface to support adjustable high voltage adapter using input current pulse protocol. To set the default input current limit, device uses the built-in USB interface. The device is compliant with USB 2.0 and USB 3.0 power spec with input current and voltage regulation. In addition, the Input Current Optimizer (ICO) supports the detection of maximum power point detection of the input source without overload. The device supports battery boost operation by supplying adjustable 4.5V-5.5V on PMID pin with up to 3.1A with integrated charge and boost mode detection

![](_page_2_Picture_0.jpeg)

## **6 Pin Configuration and Functions**

![](_page_2_Figure_4.jpeg)

### **Pin Functions**

| PIN  |     |         |                                                                                                                                                                                                                                                                                                                                                |  |
|------|-----|---------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--|
| NAME | NO. | TYPE(1) | DESCRIPTION                                                                                                                                                                                                                                                                                                                                    |  |
| VBUS | 1   | P       | Charger Input Voltage. The internal n-channel reverse block MOSFET (RBFET) is connected between VBUS and PMID with VBUS on source. Place a 1-µF ceramic capacitor from VBUS to PGND and place it as close as possible to IC.                                                                                                             |  |
| D+   | 2   | AIO     | Positive line of the USB data line pair. D+/D- based USB host/charging port detection. The detection includes data contact detection (DCD), primary and secondary detection in BC1.2, and Adjustable high voltage adapter (MaxCharge).                                                                                                   |  |
| D–   | 3   | AIO     | Negative line of the USB data line pair. D+/D- based USB host/charging port detection. The detection includes data contact detection (DCD), primary and secondary detection in BC1.2, and Adjustable high voltage adapter (MaxCharge).                                                                                                   |  |
| STAT | 4   | DO      | Open drain charge status output to indicate various charger operation. Connect to the pull up rail via 10-kΩ resistor. LOW indicates charge in progress. HIGH indicates charge complete or charge disabled. When any fault condition occurs, STAT pin blinks in 1 Hz. The STAT pin function can be disabled when STAT_DIS bit is set. |  |
| SCL  | 5   | DI      | 2C Interface clock. I Connect SCL to the logic rail through a 10-kΩ resistor.                                                                                                                                                                                                                                                            |  |
| SDA  |     | DIO     | 2C Interface data. I Connect SDA to the logic rail through a 10-kΩ resistor.                                                                                                                                                                                                                                                             |  |
| INT  | 7   | DO      | Open-drain Interrupt Output. Connect the INT to a logic rail via 10-kΩ resistor. The INT pin sends active low, 256-µs pulse to host to report charger device status and fault.                                                                                                                                                           |  |
| OTG  | 8   | DI      | Boost mode enable pin. The boost mode is activated when OTG_CONFIG =1, OTG pin is high, and no input source is detected at VBUS                                                                                                                                                                                                          |  |
| CE   | 9   | DI      | Active low Charge Enable pin. Battery charging is enabled when CHG_CONFIG = 1 and CE pin = Low. CE pin must be pulled High or Low.                                                                                                                                                                                                          |  |

(1) DI (Digital Input), DO (Digital Output), DIO (Digital Input/Output), AI (Analog Input), AO (Analog Output), AIO (Analog Input/Output)

3

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)** SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

### **Pin Functions (continued)**

| PIN       |       |         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |  |
|-----------|-------|---------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--|
| NAME      | NO.   | TYPE(1) | DESCRIPTION                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |  |
| ILIM      | 10    | AI      | Input current limit Input. ILIM pin sets the maximum input current and can be used to monitor input current ILIM pin sets the maximum input current limit by regulating the ILIM voltage at 0.8 V. A resistor is connected from ILIM pin to ground to set the maximum limit as IINMAX = KILIM/RILIM . The actual input current limit is the lower limit set by ILIM pin (when EN_ILIM bit is high) or IIINLIM register bits. Input current limit of less than 500 mA is not support on ILIM pin. ILIM pin can also be used to monitor input current when the voltage is below 0.8V. The input current is proportional to the voltage on ILIM pin and can be calculated by IIN = (KILIM x VILIM) / (RILIM x 0.8) The ILIM pin function can be disabled when EN_ILIM bit is 0. |  |
| TS        | 11    | AI      | Temperature qualification voltage input. Connect a negative temperature coefficient thermistor. Program temperature window with a resistor divider from REGN to TS to GND. Charge suspends when either TS pin is out of range. Recommend 103AT-2 thermistor.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |  |
| QON       | 12    | DI      | BATFET enable/reset control input. When BATFET is in ship mode, a logic low of tSHIPMODE (typical 1sec) duration turns on BATFET to exit shipping mode. . When VBUS is not plugged-in, a logic low of tQON_RST (typical 10sec) duration resets SYS (system power) by turning BATFET off for tBATFET_RST (typical 0.3sec) and then re-enable BATFET to provide full system power reset. The pin contains an internal pull-up to maintain default high logic                                                                                                                                                                                                                                                                                                                      |  |
| BAT       | 13,14 | P       | Battery connection point to the positive terminal of the battery pack. The internal BATFET is connected between BAT and SYS. Connect a 10uF closely to the BAT pin.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |  |
| SYS       | 15,16 | P       | System connection point. The internal BATFET is connected between BAT and SYS. When the battery falls below the minimum system voltage, switch-mode converter keeps SYS above the minimum system voltage. Connect a 20uF closely to the SYS pin.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |  |
| PGND      | 17,18 | P       | Power ground connection for high-current power converter node. Internally, PGND is connected to the source of the n-channel LSFET. On PCB layout, connect directly to ground connection of input and output capacitors of the charger. A single point connection is recommended between power PGND and the analog GND near the IC PGND pin.                                                                                                                                                                                                                                                                                                                                                                                                                                              |  |
| SW        | 19,20 | P       | Switching node connecting to output inductor. Internally SW is connected to the source of the n-channel HSFET and the drain of the n-channel LSFET. Connect the 0.047µF bootstrap capacitor from SW to BTST.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |  |
| BTST      | 21    | P       | PWM high side driver positive supply. Internally, the BTST is connected to the anode of the boost-strap diode. Connect the 0.047µF bootstrap capacitor from SW to BTST.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |  |
| REGN      | 22    | P       | PWM low side driver positive supply output. Internally, REGN is connected to the cathode of the boost-strap diode. Connect a 4.7µF (10 V rating) ceramic capacitor from REGN to analog GND. The capacitor should be placed close to the IC. REGN also serves as bias rail of TS pin.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |  |
| PMID      | 23    | DO      | Battery boost mode output. Connected to the drain of the reverse blocking MOSFET (RBFET) and the drain of HSFET. The minimum capacitance required on PMID to PGND is 40µF for up-to 2.4A output and 60µF for up-to 3.1A output                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |  |
| DSEL      | 24    | DO      | Open-drain D+/D- multiplexer selection control. Connect the DSEL to a logic rail via 10-KΩ resistor. The pin is normally float and pull-up by external resistor. During Input Source Type Detection , the pin drives low to indicate the device D+/D- detection is in progress and needs to take control of D+, D- signals. When detection is completed, the pin keeps low when DCP or MaxCharge is detected. The pin returns to float and pulls high by external resistor when other input source type is detected                                                                                                                                                                                                                                                                |  |
| PowerPAD™ |       | P       | Exposed pad beneath the IC for heat dissipation. Always solder PowerPAD Pad to the board, and have vias on the PowerPAD plane star-connecting to PGND and ground plane for high-current power converter.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |  |

![](_page_4_Picture_0.jpeg)

## **7 Specifications**

## **7.1 Absolute Maximum Ratings(1)**

over operating free-air temperature range (unless otherwise noted)

|                                     |                                       | MIN  | MAX | VALUE |
|-------------------------------------|---------------------------------------|------|-----|-------|
|                                     | VBUS (converter not switching)        | –2   | 22  | V     |
|                                     | PMID (converter not switching)        | –0.3 | 22  | V     |
|                                     | STAT                                  | –0.3 | 20  | V     |
|                                     | DSEL                                  | –0.3 | 20  | V     |
|                                     | BTST                                  | –0.3 | 20  | V     |
|                                     | SW                                    | –2   | 16  | V     |
| Voltage range (with respect to GND) | BAT, SYS (converter not switching)    | –0.3 | 6   | V     |
|                                     | SDA, SCL, INT, OTG, REGN, TS, CE, QON | –0.3 | 7   | V     |
|                                     | D+, D–                                | –0.3 | 7   | V     |
|                                     | BTST TO SW                            | –0.3 | 7   | V     |
|                                     | PGND to GND                           | –0.3 | 0.3 | V     |
|                                     | ILIM                                  | –0.3 | 5   | V     |
|                                     | INT, STAT                             |      | 6   | mA    |
| Output sink current                 | DSEL                                  | 6    | mA  |       |
| Junction temperature                |                                       | –40  | 150 | °C    |
| Storage temperature range, Tstg     |                                       | –65  | 150 | °C    |

(1) Stresses beyond those listed under absolute maximum ratings may cause permanent damage to the device. These are stress ratings only, and functional operation of the device at these or any other conditions beyond those indicated under recommended operating conditions is not implied. Exposure to absolute-maximum-rated conditions for extended periods may affect device reliability. All voltage values are with respect to the network ground terminal unless otherwise noted.

## **7.2 ESD Ratings**

|      |                         |                                                                       | VALUE | UNIT |
|------|-------------------------|-----------------------------------------------------------------------|-------|------|
|      |                         | Human body model (HBM), per ANSI/ESDA/JEDEC JS-001 (1)                | ±2000 | V    |
| VESD | Electrostatic discharge | Charged device model (CDM), per JEDEC specification JESD22-C101(2) | ±250  | V    |

(1) JEDEC document JEP155 states that 500-V HBM allows safe manufacturing with a standard ESD control process.

(2) JEDEC document JEP157 states that 250-V CDM allows safe manufacturing with a standard ESD control process.

## **7.3 Recommended Operating Conditions**

over operating free-air temperature range (unless otherwise noted)

|      |                                          | MIN | NOM                                | MAX   | UNIT |
|------|------------------------------------------|-----|------------------------------------|-------|------|
| VIN  | Input voltage                            | 3.9 |                                    | 14(1) | V    |
| IIN  | Input current (VBUS)                     |     |                                    | 3.25  | A    |
| ISYS | Output current (SW)                      |     |                                    | 5     | A    |
| VBAT | Battery voltage                          |     |                                    | 4.608 | V    |
| IBAT | Fast charging current                    |     |                                    | 5     | A    |
|      | Discharging current with internal MOSFET |     | Up to 6 (continuos)                |       | A    |
|      |                                          |     | 9 (peak) (Up to 1 sec duration) |       | A    |
| TA   | Operating free-air temperature range     | –40 |                                    | 85    | °C   |

(1) The inherent switching noise voltage spikes should not exceed the absolute maximum rating on either the BTST or SW pins. A tight layout minimizes switching noise.

## **7.4 Thermal Information**

|           |                                              | bq25895    |      |  |
|-----------|----------------------------------------------|------------|------|--|
|           | THERMAL METRIC(1)                            | RTW (WQFN) | UNIT |  |
|           |                                              | 24-PINS    |      |  |
| RθJA      | Junction-to-ambient thermal resistance       | 32.2       | °C/W |  |
| RθJC((op) | Junction-to-case (top) thermal resistance    | 34.8       | °C/W |  |
| RθJB      | Junction-to-board thermal resistance         | 8.8        | °C/W |  |
| ψJT       | Junction-to-top characterization parameter   | 0.5        | °C/W |  |
| ψJB       | Junction-to-board characterization parameter | 8.8        | °C/W |  |
| RθJC(bot) | Junction-to-case (bottom) thermal resistance | 2.0        | °C/W |  |

(1) For more information about traditional and new thermal metrics, see the *Semiconductor and IC Package Thermal Metrics* application report, [SPRA953.](http://www.ti.com/lit/pdf/spra953)

## **7.5 Electrical Characteristics**

|                    | PARAMETER                                                | TEST CONDITIONS                                                                               | MIN | TYP | MAX | UNIT |
|--------------------|----------------------------------------------------------|-----------------------------------------------------------------------------------------------|-----|-----|-----|------|
| QUIESCENT CURRENTS |                                                          |                                                                                               |     |     |     |      |
| IBAT               |                                                          | VBAT = 4.2 V, V(VBUS) < V(UVLO), leakage between BAT and VBUS                              |     |     | 5   | µA   |
|                    | Battery discharge current (BAT, SW, SYS) in buck mode | High-Z mode, no VBUS, BATFET disabled (REG09[5]=1), battery monitor disabled, TJ < 85°C |     | 12  | 23  | µA   |
|                    |                                                          | High-Z mode, no VBUS, BATFET enabled (REG09[5]=0), battery monitor disabled, TJ < 85°C  |     | 32  | 60  | µA   |
| I(VBUS_HIZ)        | Input supply current (VBUS) in buck mode                 | V(VBUS)= 5 V, High-Z mode, no battery, battery monitor disabled                            |     | 15  | 35  | µA   |
|                    | when High-Z mode is enabled                              | V(VBUS)= 12 V, High-Z mode, no battery, battery monitor disabled                           |     | 25  | 50  | µA   |
| I(VBUS)            |                                                          | VBUS > V(UVLO), VBUS > VBAT, converter not switching                                       |     | 1.5 | 3   | mA   |
|                    | Input supply current (VBUS) in buck mode                 | VBUS > V(UVLO), VBUS > VBAT, converter switching, VBAT = 3.2 V, ISYS = 0A               |     | 3   |     | mA   |
|                    |                                                          | VBUS > V(UVLO), VBUS > VBAT, converter switching, VBAT = 3.8 V, ISYS = 0 A              |     | 3   |     | mA   |
| I(BOOST)           | Battery discharge current in boost mode                  | VBAT = 4.2 V, boost mode, I(VBUS)= 0 A, converter switching                                |     | 5   |     | mA   |

![](_page_6_Picture_0.jpeg)

|                   | PARAMETER                                  | TEST CONDITIONS                                                 | MIN  | TYP              | MAX                               | UNIT |
|-------------------|--------------------------------------------|-----------------------------------------------------------------|------|------------------|-----------------------------------|------|
| VBUS/BAT POWER UP |                                            |                                                                 |      |                  |                                   |      |
| V(VBUS_OP)        | VBUS operating range                       |                                                                 | 3.9  |                  | 14                                | V    |
| V(VBUS_UVLOZ)     | 2C, no battery VBUS for active I        |                                                                 | 3.6  |                  |                                   | V    |
| V(SLEEP)          | Sleep mode falling threshold               |                                                                 | 25   | 65               | 120                               | mV   |
| V(SLEEPZ)         | Sleep mode rising threshold                |                                                                 | 130  | 250              | 370                               | mV   |
|                   | VBUS over-voltage rising threshold         |                                                                 | 14   |                  | 14.6                              | V    |
| V(ACOV)           | VBUS over-voltage falling threshold        |                                                                 | 13.5 |                  | 14                                | V    |
| VBAT(UVLOZ)       | Battery for active I2C, no VBUS            |                                                                 | 2.3  |                  |                                   | V    |
| VBAT(DPL)         | Battery depletion falling threshold        |                                                                 | 2.15 |                  | 2.5                               | V    |
| VBAT(DPLZ)        | Battery depletion rising threshold         |                                                                 | 2.35 |                  | 2.7                               | V    |
| V(VBUSMIN)        | Bad adapter detection threshold            |                                                                 |      | 3.8              |                                   | V    |
| I(BADSRC)         | Bad adapter detection current source       |                                                                 |      | 30               |                                   | mA   |
|                   | POWER-PATH MANAGEMENT                      |                                                                 |      |                  |                                   |      |
|                   | Typical system regulation voltage          | I(SYS) = 0 A, VBAT> VSYS(MIN), BATFET Disabled (REG09[5]=1)  |      | VBAT+ 50 mV   |                                   | V    |
| VSYS              |                                            | Isys = 0 A, VBAT< VSYS(MIN), BATFET Disabled (REG09[5]=1)    |      | VBAT + 150 mV |                                   | V    |
| VSYS(MIN)         | Minimum DC system voltage output           | VBAT< VSYS(MIN), SYS_MIN = 3.5 V (REG03[3:1]=101), ISYS= 0 A | 3.50 | 3.65             |                                   | V    |
| VSYS(MAX)         | Maximum DC system voltage output           | VBAT = 4.35 V, SYS_MIN = 3.5V (REG03[3:1]=101), ISYS= 0 A    |      | 4.40             | 4.42                              | V    |
|                   | Top reverse blocking MOSFET(RBFET) on      | TJ = –40°C to +85°C                                             |      | 27               | 38                                | mΩ   |
| RON(RBFET)        | resistance between VBUS and PMID           | TJ = –40°C to +125°C                                            |      | 27               | 44 39 47 24 28 3.7 | mΩ   |
|                   | Top switching MOSFET (HSFET) on-resistance | TJ = –40°C to +85°C                                             |      | 27               |                                   | mΩ   |
| RON(HSFET)        | between PMID and SW                        | TJ = –40°C to +125°C                                            |      | 27               |                                   | mΩ   |
|                   | Bottom switching MOSFET (LSFET) on         | TJ = –40°C to +85°C                                             |      | 16               |                                   | mΩ   |
| RON(LSFET)        | resistance between SW and GND              | TJ = –40°C to +125°C                                            |      | 16               |                                   | mΩ   |
| V(FWD)            | BATFET forward voltage in supplement mode  | BAT discharge current 10 mA                                     |      | 30               |                                   | mV   |
| VBAT(GD)          | Battery good comparator rising threshold   | VBAT rising                                                     | 3.4  | 3.55             |                                   | V    |
| VBAT(GD_HYST)     | Battery good comparator falling threshold  | VBAT falling                                                    |      | 100              |                                   | mV   |

|                       | PARAMETER                                    | TEST CONDITIONS                                                                                          | MIN   | TYP | MAX      | UNIT |
|-----------------------|----------------------------------------------|----------------------------------------------------------------------------------------------------------|-------|-----|----------|------|
| BATTERY CHARGER       |                                              |                                                                                                          |       |     |          |      |
| VBAT(REG_RANG E)   | Typical charge voltage range                 |                                                                                                          | 3.840 |     | 4.608    | V    |
| VBAT(REG_STEP)        | Typical charge voltage step                  |                                                                                                          |       | 16  |          | mV   |
| VBAT(REG)             | Charge voltage resolution accuracy           | VBAT = 4.208 V (REG06[7:2]=010111) or VBAT = 4.352 V (REG06[7:2]=100000) TJ = –40°C to +85°C | -0.5% |     | 0.5%     |      |
| I(CHG_REG__RAN GE) | Typical fast charge current regulation range |                                                                                                          | 0     |     | 5056     | mA   |
| I(CHG_REG_STEP )   | Typical fast charge current regulation step  |                                                                                                          |       | 64  |          | mA   |
|                       |                                              | VBAT = 3.1 V or 3.8 V, ICHG = 128 mA TJ = –40°C to +85°C                                           | -20%  |     | 20%      |      |
| I(CHG_REG_ACC)        | Fast charge current regulation accuracy      | VBAT= 3.1 V or 3.8 V, ICHG = 256 mA TJ = –40°C to +85°C                                            | -10%  |     | 10%      |      |
|                       |                                              | VBAT= 3.1 V or 3.8 V, ICHG=1792 mA TJ = –40°C to +85°C                                             | -5%   |     | 5%       |      |
|                       | Battery LOWV falling threshold               | Fast charge to precharge, BATLOWV (REG06[1]) = 1                                                      | 2.6   | 2.8 | 2.9      | V    |
| VBAT(LOWV)            | Battery LOWV rising threshold                | Precharge to fast charge, BATLOWV (REG06[1])=1 (Typical 200-mV hysteresis)                         | 2.8   | 3   | 3.1      | V    |
| I(PRECHG_RANG E)   | Precharge current range                      |                                                                                                          | 64    |     | 1024     | mA   |
| I(PRECHG_STEP)        | Typical precharge current step               |                                                                                                          |       | 64  |          | mA   |
| I(PRECHG_ACC)         | Precharge current accuracy                   | VBAT=2.6 V, IPRECHG = 256 mA                                                                             | –10%  |     | +10%     |      |
| I(TERM_RANGE)         | Termination current range                    |                                                                                                          | 64    |     | 1024     | mA   |
| I(TERM_STEP)          | Typical termination current step             |                                                                                                          |       | 64  |          | mA   |
| I(TERM_ACC)           | Termination current accuracy                 | ITERM = 256 mA, ICHG<= 1344 mA TJ = –20°C to +85°C                                                 | –12%  |     | 12%      |      |
|                       |                                              | ITERM = 256 mA, ICHG> 1344 mA TJ = –20°C to +85°C                                                     | –20%  |     | 20%      |      |
| V(SHORT)              | Battery short voltage                        | VBAT falling                                                                                             |       | 2   |          | V    |
| V(SHORT_HYST)         | Battery short voltage hysteresis             | VBAT rising                                                                                              |       | 200 |          | mV   |
| I(SHORT)              | Battery short current                        | VBAT < 2.2 V                                                                                             |       | 100 |          | mA   |
|                       |                                              | VBAT falling, VRECHG (REG06[0]=0) = 0                                                                 |       | 100 |          | mV   |
| V(RECHG)              | Recharge threshold below VBATREG             | VBAT falling, VRECHG (REG06[0]=0) = 1                                                                 |       | 200 |          | mV   |
| IBAT(LOAD)            | Battery discharge load current               | VBAT = 4.2 V                                                                                             | 15    |     |          | mA   |
| ISYS(LOAD)            | System discharge load current                | VSYS = 4.2 V                                                                                             | 30    |     |          | mA   |
|                       | SYS-BAT MOSFET (BATFET) on-resistance        | TJ = 25°C                                                                                                |       | 11  | 13 19 | mΩ   |
| RON(BATFET)           |                                              | TJ = –40°C to +125°C                                                                                     |       | 11  |          | mΩ   |

![](_page_8_Picture_0.jpeg)

|                                    | PARAMETER                                                                             | TEST CONDITIONS                                 | MIN   | TYP  | MAX  | UNIT  |
|------------------------------------|---------------------------------------------------------------------------------------|-------------------------------------------------|-------|------|------|-------|
| INPUT VOLTAGE / CURRENT REGULATION |                                                                                       |                                                 |       |      |      |       |
| VIN(DPM_RANGE)                     | Typical Input voltage regulation range                                                |                                                 | 3.9   |      | 15.3 | V     |
| VIN(DPM_STEP)                      | Typical Input voltage regulation step                                                 |                                                 |       | 100  |      | mV    |
| VIN(DPM_ACC)                       | Input voltage regulation accuracy                                                     | VINDPM = 4.4 V, 9 V                             | 3%    |      | 3%   |       |
| IIN(DPM_RANGE)                     | Typical Input current regulation range                                                |                                                 | 100   |      | 3250 | mA    |
| IIN(DPM_STEP)                      | Typical Input current regulation step                                                 |                                                 |       | 50   |      | mA    |
| IIN(DPM100_ACC)                    | Input current 100-mA regulation accuracy VBAT = 5 V, current pulled from SW        | IINLIM (REG00[5:0]) =100 mA                     | 85    | 90   | 100  | mA    |
|                                    |                                                                                       | USB150, IINLIM (REG00[5:0]) = 150 mA         | 125   | 135  | 150  | mA    |
|                                    | Input current regulation accuracy                                                     | USB500, IINLIM (REG00[5:0]) = 500 mA         | 440   | 470  | 500  | mA    |
| IIN(DPM_ACC)                       | VBAT = 5 V, current pulled from SW                                                    | USB900, IINLIM (REG00[5:0]) = 900 mA         | 750   | 825  | 900  | mA    |
|                                    |                                                                                       | Adapter 1.5 A, IINLIM (REG00[5:0]) = 1500 mA | 1300  | 1400 | 1500 | mA    |
| IIN(START)                         | Input current regulation during system start up                                       | VSYS = 2.2 V, IINLIM (REG00[5:0])> = 200 mA  |       |      | 200  | mA    |
| KILIM                              | IINMAX = KILIM/RILIM                                                                  | Input current regulation by ILIM pin = 1.5 A | 320   | 355  | 390  | A x Ω |
| D+/D- DETECTION                    |                                                                                       |                                                 |       |      |      |       |
| V(0P6_VSRC)                        | D+/D– voltage source (0.6 V)                                                          |                                                 | 0.5   | 0.6  | 0.7  | V     |
| V(3p45_VSRC)                       | D+/D– voltage source (3.45 V)                                                         |                                                 | 3.3   | 3.45 | 3.6  | V     |
| I(10UA_ISRC)                       | D+ connection check current source                                                    |                                                 | 7     | 10   | 14   | µA    |
| I(100UA_ISINK)                     | D+/D– current sink (100 µA)                                                           |                                                 | 50    | 100  | 150  | µA    |
| I(DPDM_LKG)                        | D+/D– Leakage current                                                                 | D–, switch open                                 | –1    |      | 1    | µA    |
|                                    |                                                                                       | D+, switch open                                 | –1    |      | 1    | µA    |
| I(1P6MA_ISINK)                     | D+/D– current sink (1.6 mA)                                                           |                                                 | 1.45  | 1.60 | 1.75 | µA    |
| V(0P4_VTH)                         | D+/D– low comparator threshold                                                        |                                                 | 250   |      | 400  | mV    |
| V(0P8_VTH)                         | D+ low comparator threshold                                                           |                                                 |       |      | 0.8  | V     |
| V(2P7_VTH)                         | D+/D– comparator threshold for non-standard adapter detection (divider 1, 3, or 4) |                                                 | 2.55  |      | 2.85 | V     |
| V(2P0_VTH)                         | D+/D– comparator threshold for non-standard adapter detection (divider 1, 3)       |                                                 | 1.85  |      | 2.15 | V     |
| V(1P2_VTH)                         | D+/D– comparator threshold for non-standard adapter detection (divider 2)          |                                                 | 1.05  |      | 1.35 | V     |
| R(D–_DWN)                          | D– pulldown for connection check                                                      |                                                 | 14.25 |      | 24.8 | kΩ    |

![](_page_9_Picture_1.jpeg)

|                                     | PARAMETER                                                         | TEST CONDITIONS                                                          | MIN    | TYP    | MAX    | UNIT |  |
|-------------------------------------|-------------------------------------------------------------------|--------------------------------------------------------------------------|--------|--------|--------|------|--|
| BAT OVER-VOLTAGE/CURRENT PROTECTION |                                                                   |                                                                          |        |        |        |      |  |
| VBAT(OVP)                           | Battery over-voltage threshold                                    | VBAT rising, as percentage of VBAT(REG)                               |        | 104%   |        |      |  |
| VBAT(OVP_HYST)                      | Battery over-voltage hysteresis                                   | VBAT falling, as percentage of VBAT(REG)                              |        | 2%     |        |      |  |
| IBAT(FET_OCP)                       | System over-current threshold                                     |                                                                          | 9      |        |        | A    |  |
|                                     | THERMAL REGULATION AND THERMAL SHUTDOWN                           |                                                                          |        |        |        |      |  |
| TREG                                | Junction temperature regulation accuracy                          | REG08[1:0] = 11                                                          |        | 120    |        | °C   |  |
| TSHUT                               | Thermal shutdown rising temperature                               | Temperature rising                                                       |        | 160    |        | °C   |  |
| TSHUT(HYS)                          | Thermal shutdown hysteresis                                       | Temperature falling                                                      |        | 30     |        | °C   |  |
| V(LTF)                              | Cold temperature threshold, TS pin voltage rising threshold    | As percentage to V(REGN)                                                 | 72.75% | 73.25% | 73.75% |      |  |
| V(LTF_HYS)                          | Cold temperature hysteresis, TS pin voltage falling            | As percentage to V(REGN)                                                 |        | 0.4%   |        |      |  |
| V(HTF)                              | Hot temperature TS pin voltage rising threshold                   | As percentage to V(REGN)                                                 | 47.75% | 48.25% | 48.75% |      |  |
| V(TCO)                              | Cut-off temperature TS pin voltage falling threshold           | As percentage to V(REGN)                                                 | 44.25% | 44.75% | 45.25% |      |  |
|                                     | COLD/HOT THERMISTOR COMPARATOR (BOOST MODE)                       |                                                                          |        |        |        |      |  |
| V(BCOLD1)                           | Cold temperature threshold 1, TS pin voltage rising threshold  | As percentage to VREGN REG01[5] = 1 (Approximately –20°C w/ 103AT) | 79.5%  | 80%    | 80.5%  |      |  |
| V(BCOLD1_HYS)                       | Cold temperature threshold 1, TS pin voltage falling threshold | As percentage to VREGN REG01[5] = 1                                   |        | 1%     |        |      |  |
| V(BHOT2)                            | Hot temperature threshold 2, TS pin voltage falling threshold  | As percentage to VREGN REG01[7:6] = 10 (Approx. 65°C w/ 103AT)     | 30.75% | 31.25% | 31.75% |      |  |
| V(BHOT2_HYS)                        | Hot temperature threshold 2, TS pin voltage rising threshold   | As percentage to VREGN REG01[7:6] =10                                 |        | 3%     |        |      |  |
| PWM                                 |                                                                   |                                                                          |        |        |        |      |  |
| FSW                                 | PWM switching frequency, and digital clock                        | Oscillator frequency                                                     | 1.32   |        | 1.68   | MHz  |  |
| DMAX                                | Maximum PWM duty cycle                                            |                                                                          |        | 97%    |        |      |  |
| BOOST MODE OPERATION                |                                                                   |                                                                          |        |        |        |      |  |
| V(OTG_REG_RAN GE)                | Typical boost mode regulation voltage range                       |                                                                          | 4.55   |        | 5.55   | V    |  |
| V(OTG_REG_STE P)                 | Typical boost mode regulation voltage step                        |                                                                          |        | 64     |        | mV   |  |
| V(OTG_REG_ACC )                  | Boost mode regulation voltage accuracy                            | I(PMID) = 0 A, BOOSTV=5.126V (REG0A[7:4] = 1001)                      | –3%    |        | 3%     |      |  |
| V(OTG_BAT)                          | Battery voltage exiting boost mode                                | BAT falling                                                              | 2.6    |        | 2.9    | V    |  |
| I(OTG)                              | Boost mode output current range                                   |                                                                          | 3.1    |        |        | A    |  |
| V(OTG_OVP)                          | Boost mode over-voltage threshold                                 | Rising threshold                                                         | 5.8    | 6      |        | V    |  |

![](_page_10_Picture_0.jpeg)

|                                     | PARAMETER                                 | TEST CONDITIONS                                       | MIN          | TYP   | MAX   | UNIT |
|-------------------------------------|-------------------------------------------|-------------------------------------------------------|--------------|-------|-------|------|
| REGN LDO                            |                                           |                                                       |              |       |       |      |
| V(REGN)                             | REGN LDO output voltage                   | V(VBUS) = 9 V, I(REGN) = 40 mA                        | 5.6          | 6     | 6.4   | V    |
|                                     |                                           | V(VBUS) = 5 V, I(REGN) = 20 mA                        | 4.7          | 4.8   |       | V    |
| I(REGN)                             | REGN LDO current limit                    | V(VBUS) = 9 V, V(REGN) = 3.8 V                        | 50           |       |       | mA   |
|                                     | ANALOG-TO-DIGITAL CONVERTER (ADC)         |                                                       |              |       |       |      |
| RES                                 | Resolution                                | Rising threshold                                      |              | 7     |       | bits |
| VBAT(RANGE)                         | Typical battery voltage range             | V(VBUS) > VBAT + V(SLEEP) or OTG mode is enabled   | 2.304        |       | 4.848 | V    |
|                                     |                                           | V(VBUS) < VBAT + V(SLEEP) and OTG mode is disabled | VSYS_MI N |       | 4.848 | V    |
| V(BAT_RES)                          | Typical battery voltage resolution        |                                                       |              | 20    |       | mV   |
| V(SYS_RANGE)                        | Typical system voltage range              | V(VBUS) > VBAT + V(SLEEP) or OTG mode is enabled   | 2.304        |       | 4.848 | V    |
|                                     |                                           | V(VBUS) < VBAT + V(SLEEP) and OTG mode is disabled | VSYS_MI N |       | 4.848 | V    |
| V(SYS_RES)                          | Typical system voltage resolution         |                                                       |              | 20    |       | mV   |
| V(VBUS_RANGE)                       | Typical VVBUS voltage range               | V(VBUS) > VBAT + V(SLEEP) or OTG mode is enabled   | 2.6          |       | 15.3  | V    |
| V(VBUS_RES)                         | Typical VVBUS voltage resolution          |                                                       |              | 100   |       | mV   |
| IBAT(RANGE)                         | Typical battery charge current range      | V(VBUS) > VBAT + V(SLEEP) and VBAT > VBAT(SHORT)   | 0            |       | 6.4   | A    |
| IBAT(RES)                           | Typical battery charge current resolution |                                                       |              | 50    |       | mA   |
| V(TS_RANGE)                         | Typical TS voltage range                  |                                                       | 21%          |       | 80%   |      |
| V(TS_RES)                           | Typical TS voltage resolution             |                                                       |              | 0.47% |       |      |
|                                     | LOGIC I/O PIN (OTG, CE, PSEL, QON)        |                                                       |              |       |       |      |
| VIH                                 | Input high threshold level                |                                                       | 1.3          |       |       |      |
| VIL                                 | Input low threshold level                 |                                                       |              |       | 0.4   | V    |
| IIN(BIAS)                           | High Level Leakage Current                | Pull-up rail 1.8 V                                    |              |       | 1     | µA   |
| V(QON)                              | Internal /QON pull-up                     | Battery only mode                                     |              | BAT   |       | V    |
|                                     |                                           | V(VBUS) = 9 V                                         |              | 5.8   |       | V    |
|                                     |                                           | V(VBUS) = 5 V                                         |              | 4.3   |       | V    |
| R(QON)                              | Internal /QON pull-up resistance          |                                                       |              | 200   |       | kΩ   |
| LOGIC I/O PIN (INT, STAT, PG, DSEL) |                                           |                                                       |              |       |       |      |
| VOL                                 | Output low threshold level                | Sink current = 5 mA, sink current                     |              |       | 0.4   | V    |
| IOUT_BIAS                           | High level leakage current                | Pull-up rail 1.8 V                                    |              |       | 1     | µA   |
| 2C INTERFACE (SCL, SDA) I        |                                           |                                                       |              |       |       |      |
| VIH                                 | Input high threshold level, SCL and SDA   | Pull-up rail 1.8 V                                    | 1.3          |       |       |      |
| VIL                                 | Input low threshold level                 | Pull-up rail 1.8 V                                    |              |       | 0.4   | V    |
| VOL                                 | Output low threshold level                | Sink current = 5 mA, sink current                     |              |       | 0.4   | V    |
| IBIAS                               | High level leakage current                | Pull-up rail 1.8 V                                    |              |       | 1     | µA   |

# **7.6 Timing Requirements**

|                                  |                                                         |  |                                                   | MIN  | NOM  | MAX  | UNIT                                                                                         |
|----------------------------------|---------------------------------------------------------|--|---------------------------------------------------|------|------|------|----------------------------------------------------------------------------------------------|
| VBUS/BAT POWER UP                |                                                         |  |                                                   |      |      |      |                                                                                              |
| tBADSRC                          | Bad Adapter detection duration                          |  |                                                   |      | 30   |      | msec                                                                                         |
| D+/D- DETECTION                  |                                                         |  |                                                   |      |      |      |                                                                                              |
|                                  |                                                         |  |                                                   |      |      |      | Chargin g timer with tSDP_DE USB10 mins 2 FAULT 0 in default mode |
|                                  | BAT OVER-VOLTAGE PROTECTION                             |  |                                                   |      |      |      |                                                                                              |
| tBATOVP                          | Battery over-voltage deglitch time to disable charge |  |                                                   |      | 1    |      | µs                                                                                           |
| BATTERY CHARGER                  |                                                         |  |                                                   |      |      |      |                                                                                              |
| tRECHG                           | Recharge deglitch time                                  |  |                                                   |      | 20   |      | ms                                                                                           |
| CURRENT PULSE CONTROL            |                                                         |  |                                                   |      |      |      |                                                                                              |
| tPUMPX_STOP                      | Current pulse control stop pulse                        |  |                                                   | 430  |      | 570  | ms                                                                                           |
| tPUMPX_ON1                       | Current pulse control long on pulse                     |  |                                                   | 240  |      | 360  | ms                                                                                           |
| tPUMPX_ON2                       | Current pulse control short on pulse                    |  |                                                   | 70   |      | 130  | ms                                                                                           |
| tPUMPX_OFF                       | Current pulse control off pulse                         |  |                                                   | 70   |      | 130  | ms                                                                                           |
| tPUMPX_DLY                       | Current pulse control stop start delay                  |  |                                                   | 80   |      | 225  | ms                                                                                           |
| BATTERY MONITOR                  |                                                         |  |                                                   |      |      |      |                                                                                              |
| tCONV                            | Conversion time                                         |  | CONV_RATE(REG02[6]) = 0                           |      | 8    | 1000 | ms                                                                                           |
| QON AND SHIPMODE TIMING          |                                                         |  |                                                   |      |      |      |                                                                                              |
| tSHIPMODE                        | QON low time to turn on BATFET and exit ship mode    |  | TJ = –10°C to +60°C                               | 1.25 |      | 2.25 | s                                                                                            |
| tQON_RST                         | QON low time to enable full system reset                |  | TJ = –10°C to +60°C                               | 12   |      | 18   | s                                                                                            |
| tBATFET_RST                      | BATFET off time during full system reset                |  | TJ = –10°C to +60°C                               | 350  |      | 550  | ms                                                                                           |
| tSM_DLY                          | Enter ship mode delay                                   |  | TJ = –10°C to +60°C                               | 10   |      | 15   | s                                                                                            |
| I2C INTERFACE                    |                                                         |  |                                                   |      |      |      |                                                                                              |
| fSCL                             | SCL clock frequency                                     |  |                                                   |      |      | 400  | kHz                                                                                          |
| DIGITAL CLOCK and WATCHDOG TIMER |                                                         |  |                                                   |      |      |      |                                                                                              |
| fLPDIG                           | Digital low power clock                                 |  | REGN LDO disabled                                 | 18   | 30   | 45   | kHz                                                                                          |
| fDIG                             | Digital clock                                           |  | REGN LDO enabled                                  | 1320 | 1500 | 1680 | kHz                                                                                          |
| tWDT                             | Watchdog reset time                                     |  | WATCHDOG (REG07[5:4])=11, REGN LDO disabled | 100  | 160  |      | s                                                                                            |
|                                  |                                                         |  | WATCHDOG (REG07[5:4])=11, REGN LDO             | 136  | 160  |      | s                                                                                            |

enabled

![](_page_12_Picture_0.jpeg)

## **7.7 Typical Characteristics**

![](_page_12_Figure_4.jpeg)

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)** SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

![](_page_13_Picture_1.jpeg)

### **Typical Characteristics (continued)**

![](_page_13_Figure_4.jpeg)

![](_page_14_Picture_0.jpeg)

## **8 Detailed Description**

The device is a highly integrated 5-A siwtch-mode battery charger for single cell Li-Ion and Li-polymer battery. It is highly integrated with the input reverse-blocking FET (RBFET, Q1), high-side siwtching FET (HSFET, Q2) , low-side switching FET (LSFET, Q3), and battery FET (BATFET, Q4). The device also integrates the boostrap diode for the high-side gate drive.

## **8.1 Functional Block Diagram**

![](_page_14_Figure_6.jpeg)

![](_page_15_Picture_1.jpeg)

## **8.2 Feature Description**

### **8.2.1 Device Power-On-Reset (POR)**

The internal bias circuits are powered from the higher voltage of VBUS and BAT. When VBUS rises above VVBUS\_UVLOZ or BAT rises above VBAT\_UVLOZ , the sleep comparator, battery depletion comparator and BATFET driver are active. I <sup>2</sup>C interface is ready for communication and all the registers are reset to default value. The host can access all the registers after POR.

### **8.2.2 Device Power Up from Battery without Input Source**

If only battery is present and the voltage is above depletion threshold (VBAT\_DPLZ), the BATFET turns on and connects battery to system. The REGN LDO stays off to minimize the quiescent current. The low RDS(ON) of BATFET and the low quiescent current on BAT minimize the conduction loss and maximize the battery run time. The device always monitors the discharge current through BATFET (*[Supplement](#page-20-0) Mode*). When the system is overloaded or shorted (IBAT > IBATFET\_OCP), the device turns off BATFET immediately and set BATFET\_DIS bit to indicate BATFET is disabled until the input source plugs in again or one of the methods describe in *[BATFET](#page-25-0) Enable (Exit [Shipping](#page-25-0) Mode)* is applied to re-enable BATFET.

### **8.2.3 Device Power Up from Input Source**

When an input source is plugged in, the device checks the input source voltage to turn on REGN LDO and all the bias circuits. It detects and sets the input current limit before the buck converter is started when AUTO\_DPDM\_EN bit is set. The power up sequence from input source is as listed:

- 1. Power Up REGN LDO
- 2. Poor Source Qualification
- 3. *Input Source Type [Detection](#page-16-0)* based on D+/D- to set default Input Current Limit (IINLIM) register and input source type
- 4. Input Voltage Limit Threshold Setting (VINDPM threshold)
- 5. Converter Power-up

## *8.2.3.1 Power Up REGN Regulation (LDO)*

The REGN LDO supplies internal bias circuits as well as the HSFET and LSFET gate drive. The LDO also provides bias rail to TS external resistors. The pull-up rail of STAT can be connected to REGN as well. The REGN is enabled when all the below conditions are valid.

- 1. VBUS above VVBUS\_UVLOZ
- 2. VBUS above VBAT + VSLEEPZ in buck mode or VBUS below VBAT + VSLEEP in boost mode
- 3. After 220 ms delay is completed

If one of the above conditions is not valid, the device is in high impedance mode (HIZ) with REGN LDO off. The device draws less than IVBUS\_HIZ from VBUS during HIZ state. The battery powers up the system when the device is in HIZ.

### *8.2.3.2 Poor Source Qualification*

After REGN LDO powers up, the device checks the current capability of the input source. The input source has to meet the following requirements in order to start the buck converter.

- 1. VBUS voltage below VACOV
- 2. VBUS voltage above VVBUSMIN when pulling IBADSRC (typical 30mA)

Once the input source passes all the conditions above, the status register bit VBUS\_GD is set high and the INT pin is pulsed to signal to the host. If the device fails the poor source detection, it repeats poor source qualification every 2 seconds.

![](_page_16_Picture_0.jpeg)

### **[www.ti.com](http://www.ti.com)** SLUSC88A –MARCH 2015–REVISED MAY 2016

## **Feature Description (continued)**

### <span id="page-16-0"></span>*8.2.3.3 Input Source Type Detection*

After the VBUS\_GD bit is set and REGN LDO is powered, the charger device runs *Input Source Type [Detection](#page-16-0)* when AUTO\_DPDM\_EN bit is set.

The bq25895 follows the USB Battery Charging Specification 1.2 (BC1.2) and to detect input source (SDP/CDP/DCP) and non-standard adapter through USB D+/D- lines. In addition, when USB DCP is detected, it initiates adjustable high voltage adapter handshake on D+/D-. The device supports MaxCharge™ handshake when MAXC\_EN or HVDCP\_EN is set.

After input source type detection, an INT pulse is asserted to the host. In addition, the following registers and pin are changed:

- 1. Input Current Limit (IINLIM) register is changed to set current limit
- 2. PG\_STAT bit is set
- 3. SDP\_STAT bit is updated to indicate USB100 or other input source

The host can over-write IINLIM register to change the input current limit if needed. The charger input current is always limited by the lower of IINLIM register or ILIM pin at all-time regardless of Input Current Optimizer (ICO) is enable or disabled.

When AUTO\_DPDM\_EN is disabled, the *Input Source Type [Detection](#page-16-0)* is bypassed. The Input Current Limit (IINLIM) register, VBUS\_STAT, and SPD\_STAT bits are unchanged from previous values.

### **8.2.3.3.1 D+/D– Detection Sets Input Current Limit**

The bq25890 contains a D+/D– based input source detection to set the input current limit automatically. The D+/D- detection includes standard USB BC1.2, non-standard adapter, and adjustable high voltage adapter detections. When input source is plugged-in, the device starts standard USB BC1.2 detections. The USB BC1.2 is capable to identify Standard Downstream Port (SDP), Charging Downstream Port (CDP), and Dedicated Charging Port (DCP). When the Data Contact Detection (DCD) timer of 500ms is expired, the non-standard adapter detection is applied to set the input current limit.

When DCP is detected, the device initates adjustable high voltage adapter handshake including MaxCharge™, etc. The handshake connects combinations of voltage source(s) and/or current sink on D+/D- to signal input source to raise output voltage from 5 V to 9 V / 12 V. The adjustable high voltage adapter handshake can be disabled by clearing MAXC\_EN and/or HVDCP\_EN bits .

![](_page_16_Figure_15.jpeg)

Copyright © 2015–2016, Texas Instruments Incorporated *Submit [Documentation](http://www.go-dsp.com/forms/techdoc/doc_feedback.htm?litnum=SLUSC88A&partnum=bq25895) Feedback*

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

| NON-STANDARD ADAPTER | D+ THRESHOLD        | D- THRESHOLD        | INPUT CURRENT LIMIT |
|-------------------------|---------------------|---------------------|---------------------|
| Divider 1               | VD+ within V2P7_VTH | VD- within V2P0_VTH | 2.1A                |
| Divider 2               | VD+ within V1P2_VTH | VD- within V1P2_VTH | 2A                  |
| Divider 3               | VD+ within V2P0_VTH | VD- within V2P7_VTH | 1A                  |
| Divider 4               | VD+ within V2P7_VTH | VD- within V2P7_VTH | 2.4A                |

### **Table 1. Non-Standard Adapter Detection**

### **Table 2. Adjustable High Voltage Adapter D+/D- Output Configurations**

| ADJUSTABLE HIGH VOLTAGE HANDSHAKE | D+           | D-           | OUTPUT |
|-----------------------------------|--------------|--------------|--------|
| MaxCharge (12V)                   | I1P6MA_ISINK | V3p45_VSRC   | 12 V   |
| MaxCharge (9V)                    | V3p45_VSRC   | I1P6MA_ISINK | 9 V    |

After the *Input Source Type [Detection](#page-16-0)* is done, an INT pulse is asserted to the host. In addition, the following registers including Input Current Limit register (IINLIM), VBUS\_STAT, and SDP\_STAT are updated as below:

| D+/D- DETECTION  | INPUT CURRENT LIMIT (IINLIM) | SDP_STAT | VBUS_STAT |
|------------------|---------------------------------|----------|-----------|
| USB SDP (USB500) | 500 mA                          | 1        | 001       |
| USB CDP          | 1.5 A                           | 1        | 010       |
| USB DCP          | 3.25 A                          | 1        | 011       |
| Divider 3        | 1 A                             | 1        | 110       |
| Divider 1        | 2.1 A                           | 1        | 110       |
| Divider 4        | 2.4 A                           | 1        | 110       |
| Divider 2        | 2 A                             | 1        | 110       |
| MaxCharge        | 1.5 A                           | 1        | 100       |
| Unknown Adapter  | 500 mA                          | 1        | 101       |

### **Table 3. bq25895 Result**

![](_page_18_Picture_0.jpeg)

### **8.2.3.3.2 Force Input Current Limit Detection**

In host mode, the host can force the device to run by setting FORCE\_DPDM bit. After the detection is completed, FORCE\_DPDM bit returns to 0 by itself and Input Result is updated.

## *8.2.3.4 Input Voltage Limit Threshold Setting (VINDPM Threshold)*

The device supports wide range of input voltage limit (3.9 V – 14 V) for high voltage charging and provides two methods to set Input Voltage Limit (VINDPM) threshold to facilitate autonomous detection.

1. Absolute VINDPM (FORCE\_VINDPM=1)

By setting FORCE\_VINDPM bit to 1, the VINDPM threshold setting algorithm is disabled. Register VINDPM is writable and allows host to set the absolute threshold of VINDPM function.

2. Relative VINDPM based on VINDPM\_OS registers (FORCE\_VINDPM=0) (Default)

When FORCE\_VINDPM bit is 0 (default), the VINDPM threshold setting algorithm is enabled. The VINDPM register is read only and the charger controls the register by using VINDPM Threshold setting algorithm. The algorithm allows a wide range of adapter (VVBUS\_OP) to be used with flexible VINDPM threshold.

After Input Voltage Limit Threshold is set, an INT pulse is generated to signal to the host.

### *8.2.3.5 Converter Power-Up*

After the input current limit is set, the converter is enabled and the HSFET and LSFET start switching. If battery charging is disabled, BATFET turns off. Otherwise, BATFET stays on to charge the battery.

The device provides soft-start when system rail is ramped up. When the system rail is below 2.2 V, the input current limit is forced to the lower of 200 mA or IINLIM register setting. After the system rises above 2.2 V, the device limits input current to the lower value of ILIM pin and IILIM register (ICO\_EN = 0) or IDPM\_LIM register (ICO\_EN = 1).

As a battery charger, the device deploys a highly efficient 1.5 MHz step-down switching regulator. The fixed frequency oscillator keeps tight control of the switching frequency under all conditions of input voltage, battery voltage, charge current and temperature, simplifying output filter design.

A type III compensation network allows using ceramic capacitors at the output of the converter. An internal sawtooth ramp is compared to the internal error control signal to vary the duty cycle of the converter. The ramp height is proportional to the PMID voltage to cancel out any loop gain variation due to a change in input voltage.

In order to improve light-load efficiency, the device switches to PFM control at light load when battery is below minimum system voltage setting or charging is disabled. During the PFM operation, the switching duty cycle is set by the ratio of SYS and VBUS.

### **8.2.4 Input Current Optimizer (ICO)**

The device provides innovative Input Current Optimizer (ICO) to identify maximum power point without overload the input source. The algorithm automatically identify maximum input current limit of power source without entering VINDPM to avoid input source overload.

This feature is enabled by default (ICO\_EN=1) and can be disabled by setting ICO\_EN bit to 0. After DCP or MaxCharge type input source is detected based on the procedures previously described (*Input [Source](#page-16-0) Type [Detection](#page-16-0)* ). The algorithm runs automatically when ICO\_EN bit is set. The algorithm can also be forced to execute by setting FORCE\_ICO bit regardless of input source type detected.

The actual input current limit used by the *Dynamic Power [Management](#page-19-0)* is reported in IDPM\_LIM register while Input Current Optimizer is enabled (ICO\_EN = 1) or set by IINLIM register when the algorithm is disabled (ICO\_EN = 0). In addition, the current limit is clamped by ILIM pin unless EN\_ILIM bit is 0 to disable ILIM pin function.

![](_page_19_Picture_1.jpeg)

### **8.2.5 Boost Mode Operation from Battery**

The device supports boost converter operation to deliver power from the battery to other portable devices through PMID pin. The boost mode output current rating supports maximum output current up to 3.1 A to charge smartphone and tablet at fast charging rate. The boost operation can be enabled if the conditions are valid:

- 1. BAT above BATLOWV
- 2. VBUS less than BAT+VSLEEP (in sleep mode)
- 3. Boost mode operation is enabled (OTG pin HIGH and OTG\_CONFIG bit =1)
- 4. Voltage at TS (thermistor) pin is within range configured by Boost Mode Temperature Monitor as configured by BHOT and BCOLD bits
- 5. After 30 ms delay from boost mode enable

In boost mode, the device employs a 500 KHz or 1.5 MHz (selectable using BOOST\_FREQ bit) step-up switching regulator based on system requirements. To avoid frequency change during boost mode operations, write to boost frequency configuration bit (BOOST\_FREQ) is ignored when OTG\_CONFIG is set.

During boost mode, the status register VBUS\_STAT bits is set to 111, the VBUS output is 5V by default (selectable via BOOSTV register bits). The boost output is maintained when BAT is above VOTG\_BAT threshold

### **8.2.6 Power Path Management**

The device accommodates a wide range of input sources from USB, wall adapter, to car battery. The device provides automatic power path selection to supply the system (SYS) from input source (VBUS), battery (BAT), or both.

### *8.2.6.1 Narrow VDC Architecture*

The device deploys Narrow VDC architecture (NVDC) with BATFET separating system from battery. The minimum system voltage is set by SYS\_MIN bits. Even with a fully depleted battery, the system is regulated above the minimum system voltage (default 3.5 V).

When the battery is below minimum system voltage setting, the BATFET operates in linear mode (LDO mode), and the system is regulated above the minimum system voltage setting. As the battery voltage rises above the minimum system voltage, BATFET is fully on and the voltage difference between the system and battery is the VDS of BATFET. The status register VSYS\_STAT bit goes high when the system is in minimum system voltage regulation.

![](_page_19_Figure_17.jpeg)

**Figure 10. V(SYS) vs V(BAT)**

### <span id="page-19-0"></span>*8.2.6.2 Dynamic Power Management*

To meet maximum current limit in USB spec and avoid over loading the adapter, the device features Dynamic Power Management (DPM), which continuously monitors the input current and input voltage. When input source is over-loaded, either the current exceeds the input current limit (IINLIM or IDPM\_LIM) or the voltage falls below the input voltage limit (VINDPM). The device then reduces the charge current until the input current falls below the input current limit and the input voltage rises above the input voltage limit.

![](_page_20_Picture_0.jpeg)

When the charge current is reduced to zero, but the input source is still overloaded, the system voltage starts to drop. Once the system voltage falls below the battery voltage, the device automatically enters the *[Supplement](#page-20-0) [Mode](#page-20-0)* where the BATFET turns on and battery starts discharging so that the system is supported from both the input source and battery.

During DPM mode, the status register bits VDPM\_STAT (VINDPM) and/or IDPM\_STAT (IINDPM) is/are set high. [Figure](#page-20-1) 11 shows the DPM response with 9V/1.2A adapter, 3.2-V battery, 2.8-A charge current and 3.4-V minimum system voltage setting.

![](_page_20_Figure_5.jpeg)

**Figure 11. DPM Response**

### <span id="page-20-1"></span><span id="page-20-0"></span>*8.2.6.3 Supplement Mode*

<span id="page-20-2"></span>When the system voltage falls below the battery voltage, the BATFET turns on and the BATFET gate is regulated the gate drive of BATFET so that the minimum BATFET VDS stays at 30 mV when the current is low. This prevents oscillation from entering and exiting the *[Supplement](#page-20-0) Mode*. As the discharge current increases, the BATFET gate is regulated with a higher voltage to reduce RDS(ON) until the BATFET is in full conduction. At this point onwards, the BATFET VDS linearly increases with discharge current. [Figure](#page-20-2) 12 shows the V-I curve of the BATFET gate regulation operation. BATFET turns off to exit *[Supplement](#page-20-0) Mode* when the battery is below battery depletion threshold.

![](_page_20_Figure_9.jpeg)

**Figure 12. BATFET V-I Curve**

### **8.2.7 Battery Charging Management**

The device charges 1-cell Li-Ion battery with up to 5-A charge current for high capacity battery. The 11-mΩ BATFET improves charging efficiency and minimize the voltage drop during discharging.

### *8.2.7.1 Autonomous Charging Cycle*

With battery charging is enabled (CHG\_CONFIG bit = 1 and CE pin is low), the device autonomously completes a charging cycle without host involvement. The device default charging parameters are listed in [Table](#page-21-0) 4. The host can always control the charging operations and optimize the charging parameters by writing to the corresponding registers through I <sup>2</sup>C.

<span id="page-21-0"></span>

| bq25895  |
|----------|
| 4.208 V  |
| 2.048 A  |
| 128 mA   |
| 256 mA   |
| Cold/Hot |
| 12 hour  |
|          |

**Table 4. Charging Parameter Default Setting**

A new charge cycle starts when the following conditions are valid:

- Converter starts
- Battery charging is enabled by setting CHG\_CONFIG bit, /CE pin is low and ICHG register is not 0 mA
- No thermistor fault on TS pin
- No safety timer fault
- BATFET is not forced to turn off (BATFET\_DIS bit = 0)

The charger device automatically terminates the charging cycle when the charging current is below termination threshold, charge voltage is above recharge threshold, and device not in DPM mode or thermal regulation. When a full battery voltage is discharged below recharge threshold (threshold selectable via VRECHG bit), the device automatically starts a new charging cycle. After the charge is done, either toggle CE pin or CHG\_CONFIG bit can initiate a new charging cycle.

The STAT output indicates the charging status of charging (LOW), charging complete or charge disable (HIGH) or charging fault (Blinking). The STAT output can be disabled by setting STAT\_DIS bit. In addition, the status register (CHRG\_STAT) indicates the different charging phases: 00-charging disable, 01-precharge, 10-fast charge (constant current) and constant voltage mode, 11-charging done. Once a charging cycle is completed, an INT is asserted to notify the host.

### *8.2.7.2 Battery Charging Profile*

The device charges the battery in three phases: preconditioning, constant current and constant voltage. At the beginning of a charging cycle, the device checks the battery voltage and regulates current / voltage.

| VBAT      | CHARGING CURRENT | REG DEFAULT SETTING | CHRG_STAT |
|-----------|------------------|---------------------|-----------|
| < 2 V     | IBATSHORT        | –                   | 01        |
| 2 V – 3 V | IPRECHG          | 128 mA              | 01        |
| > 3 V     | ICHG             | 2048 mA             | 10        |

**Table 5. Charging Current Setting**

![](_page_22_Picture_0.jpeg)

If the charger device is in DPM regulation or thermal regulation during charging, the charging current can be less than the programmed value. In this case, termination is temporarily disabled and the charging safety timer is counted at half the clock rate.

![](_page_22_Figure_4.jpeg)

**Figure 13. Battery Charging Profile**

## *8.2.7.3 Charging Termination*

The device terminates a charge cycle when the battery voltage is above recharge threshold, and the current is below termination current. After the charging cycle is completed, the BATFET turns off. The converter keeps running to power the system, and BATFET can turn on again to engage *[Supplement](#page-20-0) Mode*.

When termination occurs, the status register CHRG\_STAT is set to 11, and an INT pulse is asserted to the host. Termination is temporarily disabled when the charger device is in input current, voltage or thermal regulation. Termination can be disabled by writing 0 to EN\_TERM bit prior to charge termination.

### *8.2.7.4 Resistance Compensation (IRCOMP)*

For high current charging system, resistance between charger output and battery cell terminal such as board routing, connector, MOSFETs and sense resistor can force the charging process to move from constant current to constant voltage too early and increase charge time. To speed up the charging cycle, the device provides resistance compensation (IRCOMP) feature which can extend the constant current charge time to delivery maximum power to battery.

The device allows the host to compensate for the resistance by increasing the voltage regulation set point based on actual charge current and the resistance as shown below. For safe operation, the host should set the maximum allowed regulation voltage register (VCLAMP) and the minimum resistance compensation (BATCOMP).

VREG\_ACTUAL = VREG + min(ICHRG\_ACTUAL x BATCOMP, VCLAMP) (1)

## *8.2.7.5 Thermistor Qualification*

### **8.2.7.5.1 Cold/Hot Temperature Window in Charge Mode**

The device continuously monitors battery temperature by measuring the voltage between the TS pins and ground, typically determined by a negative temperature coefficient thermistor (NTC) and an external voltage divider. The device compares this voltage against its internal thresholds to determine if charging is allowed. To initiate a charge cycle, the battery temperature must be within the VLTF to VHTF thresholds. During the charge cycle the battery temperature must be within the VLTF to VTCO thresholds, else the device suspends charging and waits until the battery temperature is within the VLTF to VHTF range.

Copyright © 2015–2016, Texas Instruments Incorporated *Submit [Documentation](http://www.go-dsp.com/forms/techdoc/doc_feedback.htm?litnum=SLUSC88A&partnum=bq25895) Feedback*

![](_page_23_Picture_1.jpeg)

![](_page_23_Figure_3.jpeg)

![](_page_23_Figure_4.jpeg)

<span id="page-23-0"></span>When the TS fault occurs, the fault register REG0C[2:0] indicates the actual condition on each TS pin and an INT is asserted to the host. The STAT pin indicates the fault when charging is suspended.

![](_page_23_Figure_6.jpeg)

**Figure 15. TS Pin Thermistor Sense Thresholds**

<span id="page-23-1"></span>Assuming a 103AT NTC thermistor on the battery pack as shown in [Figure](#page-23-0) 14, the value RT1 and RT2 can be determined by using [Equation](#page-23-1) 2:

$$
RT2 = \frac{V_{VREF} \times RTH_{COLD} \times RTH_{HOT} \times \left(\frac{1}{V_{LTF}} - \frac{1}{V_{TCO}}\right)}{RTH_{HOT} \times \left(\frac{V_{VREF}}{V_{TCO}} - 1\right) - RTH_{COLD} \times \left(\frac{V_{VREF}}{V_{LTF}} - 1\right)}
$$
  
$$
RT1 = \frac{\frac{V_{VREF}}{V_{LTF}} - 1}{\frac{1}{RT2} + \frac{1}{RTH_{COLD}}}
$$

Select 0°C to 45°C range for Li-ion or Li-polymer battery, RTHCOLD = 27.28 kΩ RTHHOT = 4.91 kΩ RT1 = 5.21 kΩ RT2 = 29.87 kΩ

(2)

![](_page_24_Picture_0.jpeg)

### **8.2.7.5.2 Cold/Hot Temperature Window in Boost Mode**

For battery protection during boost mode, the device monitors the battery temperature to be within the VBCOLDx to VBHOTx thresholds unless boost mode temperature is disabled by setting BHOT bits to 11. When temperature is outside of the temperature thresholds, the boost mode and BATFET are disabled and BATFET\_DIS bit is set to reduce leakage current on PMID. Once temperature returns within thresholds, the host can clear BATFET\_DIS bit or provide logic low to high transition on QON pin to enable BATFET and boost mode.

|                      | Temperature Range to Boost |  |  |  |
|----------------------|-------------------------------|--|--|--|
| VREF                 |                               |  |  |  |
| V BCOLDx             | Boost Disable                 |  |  |  |
| ( -10ºC / 20ºC)      |                               |  |  |  |
|                      |                               |  |  |  |
|                      | Boost Enable                  |  |  |  |
| V BHOTx           |                               |  |  |  |
| (55ºC / 60ºC / 65ºC) |                               |  |  |  |
|                      | Boost Disable                 |  |  |  |
| AGND                 |                               |  |  |  |

**Figure 16. TS Pin Thermistor Sense Thresholds in Boost Mode**

### *8.2.7.6 Charging Safety Timer*

The device has built-in safety timer to prevent extended charging cycle due to abnormal battery conditions. The safety timer is 4 hours when the battery is below VBATLOWV threshold. The user can program fast charge safety timer through I <sup>2</sup>C (CHG\_TIMER bits). When safety timer expires, the fault register CHRG\_FAULT bits are set to 11 and an INT is asserted to the host. The safety timer feature can be disabled via I2C by setting EN\_TIMER bit.

During input voltage, current or thermal regulation, the safety timer counts at half clock rate as the actual charge current is likely to be below the register setting. For example, if the charger is in input current regulation (IDPM\_STAT = 1) throughout the whole charging cycle, and the safety time is set to 5 hours, the safety timer will expire in 10 hours. This half clock rate feature can be disabled by writing 0 to TMR2X\_EN bit.

### **8.2.8 Battery Monitor**

The device includes a battery monitor to provide measurements of VBUS voltage, battery voltage, system voltage, thermistor ratio, and charging current, and charging current based on the device's modes of operation. The measurements are reported in Battery Monitor Registers (REG0E-REG12). The battery monitor can be configured as two conversion modes by using CONV\_RATE bit: one-shot conversion (default) and 1 second continuous conversion.

For one-shot conversion (CONV\_RATE = 0), the CONV\_START bit can be set to start the conversion. During the conversion, the CONV\_START is set and it is cleared by the device when conversion is completed. The conversion result is ready after tCONV (maximum 1 second).

For continuous conversion (CONV\_RATE = 1), the CONV\_RATE bit can be set to initiate the conversion. During active conversion, the CONV\_START is set to indicate conversion is in progress. The battery monitor provides conversion result every 1 second automatically. The battery monitor exits continuous conversion mode when CONV\_RATE is cleared.

When battery monitor is active, the REGN power is enabled and can increase device quiescent current.

|                                |          | MODES OF OPERATION |            |                        |                      |  |  |
|--------------------------------|----------|--------------------|------------|------------------------|----------------------|--|--|
| PARAMETER                      | REGISTER | CHARGE MODE     | BOOST MODE | DISABLE CHARGE MODE | BATTERY ONLY MODE |  |  |
| Battery Voltage (VBAT)         | REG0E    | Yes                | Yes        | Yes                    | Yes                  |  |  |
| System Voltage (VSYS)          | REG0F    | Yes                | Yes        | Yes                    | Yes                  |  |  |
| Temperature (TS) Voltage (VTS) | REG10    | Yes                | Yes        | Yes                    | Yes                  |  |  |
| VBUS Voltage (VVBUS)           | REG11    | Yes                | Yes        | Yes                    | NA                   |  |  |
| Charge Current (IBAT)          | REG12    | Yes                | NA         | NA                     | NA                   |  |  |

## **Table 6. Battery Monitor Modes of Operation**

## **8.2.9 Status Outputs (STAT, and INT)**

### *8.2.9.1 Charging Status Indicator (STAT)*

The device indicates charging state on the open drain STAT pin. The STAT pin can drive LED as shown in [Figure](#page-49-0) 47. The STAT pin function can be disable by setting STAT\_DIS bit.

### **Table 7. STAT Pin State**

| CHARGING STATE                                                                                                                  | STAT INDICATOR   |
|---------------------------------------------------------------------------------------------------------------------------------|------------------|
| Charging in progress (including recharge)                                                                                       | LOW              |
| Charging complete                                                                                                               | HIGH             |
| Sleep mode, charge disable                                                                                                      | HIGH             |
| Charge suspend (Input overvoltage, TS fault, timer fault, input or system overvoltage). Boost Mode suspend (due to TS Fault) | blinking at 1 Hz |

## *8.2.9.2 Interrupt to Host (INT)*

In some applications, the host does not always monitor the charger operation. The INT notifies the system on the device operation. The following events will generate 256-µs INT pulse.

- USB/adapter source identified (through PSEL or DPDM detection, with OTG pin)
- Good input source detected
  - VBUS above battery (not in sleep)
  - VBUS below VACOV threshold
  - VBUS above VVBUSMIN (typical 3.8 V) when IBADSRC (typical 30 mA) current is applied (not a poor source)
- Input removed
- Charge Complete
- Any FAULT event in REG0C

When a fault occurs, the charger device sends out INT and keeps the fault state in REG0C until the host reads the fault register. Before the host reads REG0C and all the faults are cleared, the charger device would not send any INT upon new faults. To read the current fault status, the host has to read REG0C two times consecutively. The 1 st read reports the pre-existing fault register status and the 2 nd read reports the current fault register status.

## **8.2.10 BATET (Q4) Control**

### *8.2.10.1 BATFET Disable Mode (Shipping Mode)*

To extend battery life and minimize power when system is powered off during system idle, shipping, or storage, the device can turn off BATFET so that the system voltage is zero to minimize the battery leakage current. When the host set BATFET\_DIS bit, the charger can turn off BATFET immediately or delay by tSM\_DLY as configurated by BATFET\_DLY bit.

## <span id="page-25-0"></span>*8.2.10.2 BATFET Enable (Exit Shipping Mode)*

When the BATFET is disabled (in shipping mode) and indicated by setting BATFET\_DIS, one of the following events can enable BATFET to restore system power:

1. Plug in adapter

![](_page_26_Picture_0.jpeg)

- 2. Clear BATFET\_DIS bit
- 3. Set REG\_RST bit to reset all registers including BATFET\_DIS bit to default (0)
- 4. A logic high to low transition on QON pin with tSHIPMODE deglitch time to enable BATFET to exit shipping mode

### *8.2.10.3 BATFET Full System Reset*

The BATFET functions as a load switch between battery and system when input source is not plugged-in. By changing the state of BATFET from off to on, system connects to SYS can be effectively have a power-on-reset. The QON pin supports push-button interface to reset system power without host by change the state of BATFET.

When the QON pin is driven to logic low for tQON\_RST (typical 15 seconds) while input source is not plugged in and BATFET is enabled (BATFET\_DIS=0), the BATFET is turned off for tBATFET\_RST and then it is re-enabled to reset system power. This function can be disabled by setting BATFET\_RST\_EN bit to 0.

### **8.2.11 Current Pulse Control Protocol**

The device provides the control to generate the VBUS current pulse protocol to communicate with adjustable high voltage adapter in order to signal adapter to increase or decrease output voltage. To enable the interface, the EN\_PUMPX bit must be set. Then the host can select the increase/decrease voltage pulse by setting one of the PUMPX\_UP or PUMPX\_DN bit (but not both) to start the VBUS current pulse sequence. During the current pulse sequence, the PUMPX\_UP and PUMPX\_DN bits are set to indicate pulse sequence is in progress and the device pulses the input current limit between current limit set forth by IINLIM or IDPM\_LIM register and the 100mA current limit (IINDPM100\_ACC). When the pulse sequence is completed, the input current limit is returned to value set by IINLIM or IDPM\_LIM register and the PUMPX\_UP or PUMPX\_DN bit is cleared. In addition, the EN\_PUMPX can be cleared during the current pulse sequence to terminate the sequence and force charger to return to input current limit as set forth by the IINLIM or IDPM\_LIM register immediately. When EN\_PUMPX bit is low, write to PUMPX\_UP and PUMPX\_DN bit would be ignored and have no effect on VBUS current limit.

### **8.2.12 Input Current Limit on ILIM**

For safe operation, the device has an additional hardware pin on ILIM to limit maximum input current on ILIM pin. The input maximum current is set by a resistor from ILIM pin to ground as:

$$
I_{\text{INMAX}} = \frac{K_{\text{ILIM}}}{R_{\text{ILIM}}} \tag{3}
$$

The actual input current limit is the lower value between ILIM setting and register setting (IINLIM). For example, if the register setting is 111111 for 3.25 A, and ILIM has a 260-Ω resistor (KILIM = 390 max.) to ground for 1.5 A, the input current limit is 1.5 A. ILIM pin can be used to set the input current limit rather than the register settings when EN\_ILIM bit is set. The device regulates ILIM pin at 0.8 V. If ILIM voltage exceeds 0.8 V, the device enters input current regulation (Refer to *Dynamic Power [Management](#page-19-0)* section).

<span id="page-26-0"></span>The ILIM pin can also be used to monitor input current when EN\_ILIM is enabled. The voltage on ILIM pin is proportional to the input current. ILIM pin can be used to monitor the input current following [Equation](#page-26-0) 4:

$$
I_{IN} = \frac{K_{ILIM} \times V_{ILIM}}{R_{ILIM} \times 0.8 \text{ V}}
$$

(4)

For example, if ILIM pin is set with 260-Ω resistor, and the ILIM voltage is 0.4 V, the actual input current 0.615 A - 0.75 A (based on KILM specified). If ILIM pin is open, the input current is limited to zero since ILIM voltage floats above 0.8 V. If ILIM pin is short, the input current limit is set by the register.

The ILIM pin function can be disabled by setting EN\_ILIM bit to 0. When the pin is disabled, both input current limit function and monitoring function are not available.

### **8.2.13 Thermal Regulation and Thermal Shutdown**

### **8.2.13.0.1 Thermal Protection in Buck Mode**

The device monitors the internal junction temperature T<sup>J</sup> to avoid overheat the chip and limits the IC surface temperature in buck mode. When the internal junction temperature exceeds the preset thermal regulation limit (TREG bits), the device lowers down the charge current. The wide thermal regulation range from 60ºC to 120ºC allows the user to optimize the system thermal performance.

![](_page_27_Picture_1.jpeg)

During thermal regulation, the actual charging current is usually below the programmed battery charging current. Therefore, termination is disabled, the safety timer runs at half the clock rate, and the status register THERM\_STAT bit goes high.

Additionally, the device has thermal shutdown to turn off the converter and BATFET when IC surface temperature exceeds TSHUT. The fault register CHRG\_FAULT is set to 10 and an INT is asserted to the host. The BATFET and converter is enabled to recover when IC temperature is below TSHUT\_HYS.

### **8.2.13.0.2 Thermal Protection in Boost Mode**

The device monitors the internal junction temperature to provide thermal shutdown during boost mode. When IC surface temperature exceeds TSHUT, BATFET is turned off to disable battery discharge. When IC surface temperature is below TSHUT\_HYS, the host can use one of the method describes in section *[BATFET](#page-25-0) Enable (Exit [Shipping](#page-25-0) Mode)* to recover.

### **8.2.14 Voltage and Current Monitoring in Buck and Boost Mode**

### *8.2.14.1 Voltage and Current Monitoring in Buck Mode*

The device closely monitors the input and system voltage, as well as HSFET current for safe buck and boost mode operations.

### **8.2.14.1.1 Input Overvoltage (ACOV)**

The input voltage for buck mode operation is VVBUS\_OP. If VBUS voltage exceeds VACOV, the device stops switching immediately. During input over voltage (ACOV), the fault register CHRG\_FAULT bits sets to 01. An INT is asserted to the host..

### **8.2.14.1.2 System Overvoltage Protection (SYSOVP)**

The charger device clamps the system voltage during load transient so that the components connect to system would not be damaged due to high voltage. When SYSOVP is detected, the converter stops immediately to clamp the overshoot.

### *8.2.14.2 Current Monitoring in Boost Mode*

The device closely monitors the VBUS voltage, as well as LSFET current to ensure safe boost mode operation.

### **8.2.14.2.1 Boost Mode Overvoltage Protection**

When PMID voltage rises above regulation target and exceeds VOTG\_OVP, the device enters overvoltage protection which stops switching and pauses boost mode (OTG\_CONFIG bit remains set) until OVP fault is removed. During the overvoltage, the fault register bit (BOOST\_FAULT) is set high to indicate fault in boost operation. An INT is also asserted to the host.

### **8.2.15 Battery Protection**

### *8.2.15.1 Battery Overvoltage Protection (BATOVP)*

The battery overvoltage limit is clamped at 4% above the battery regulation voltage. When battery over voltage occurs, the charger device immediately disables charge. The fault register BAT\_FAULT bit goes high and an INT is asserted to the host.

### *8.2.15.2 Battery Over-Discharge Protection*

When battery is discharged below VBAT\_DPL, the BAe batterTFET is turned off to protect battery from over discharge. To recover from over-discharge, an input source is required at VBUS. When an input source is plugged in, the BATFET turns on. Thy is charged with IBATSHORT (typically 100 mA) current when the VBAT < VSHORT, or precharge current as set in IPRECHG register when the battery voltage is between VSHORT and VBATLOWV.

![](_page_28_Picture_0.jpeg)

### *8.2.15.3 System Overcurrent Protection*

When the system is shorted or significantly overloaded (IBAT > IBATOP) so that its current exceeds the overcurrent limit, the device latches off BATFET. Section *BATFET Enable (Exit [Shipping](#page-25-0) Mode)* can reset the latch-off condition and turn on BATFET

### **8.2.16 Serial Interface**

The device uses I <sup>2</sup>C compatible interface for flexible charging parameter programming and instantaneous device status reporting. I <sup>2</sup>C is a bi-directional 2-wire serial interface. Only two open-drain bus lines are required: a serial data line (SDA) and a serial clock line (SCL). Devices can be considered as masters or slaves when performing data transfers. A master is the device which initiates a data transfer on the bus and generates the clock signals to permit that transfer. At that time, any device addressed is considered a slave.

The device operates as a slave device with address 6BH, receiving control inputs from the master device like micro controller or a digital signal processor through REG00-REG14. Register read beyond REG14 (0x14) returns 0xFF. The I <sup>2</sup>C interface supports both standard mode (up to 100 kbits), and fast mode (up to 400 kbits). When the bus is free, both lines are HIGH. The SDA and SCL pins are open drain and must be connected to the positive supply voltage via a current source or pull-up resistor.

### *8.2.16.1 Data Validity*

The data on the SDA line must be stable during the HIGH period of the clock. The HIGH or LOW state of the data line can only change when the clock signal on the SCL line is LOW. One clock pulse is generated for each data bit transferred.

![](_page_28_Figure_10.jpeg)

**Figure 17. Bit Transfer on the I <sup>2</sup>C Bus**

### *8.2.16.2 START and STOP Conditions*

All transactions begin with a START (S) and can be terminated by a STOP (P). A HIGH to LOW transition on the SDA line while SCl is HIGH defines a START condition. A LOW to HIGH transition on the SDA line when the SCL is HIGH defines a STOP condition.

START and STOP conditions are always generated by the master. The bus is considered busy after the START condition, and free after the STOP condition.

START (S) STOP (P) SDA SCL SDA SCL **[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)** SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

**Figure 18. START and STOP conditions**

## *8.2.16.3 Byte Format*

Every byte on the SDA line must be 8 bits long. The number of bytes to be transmitted per transfer is unrestricted. Each byte has to be followed by an Acknowledge bit. Data is transferred with the Most Significant Bit (MSB) first. If a slave cannot receive or transmit another complete byte of data until it has performed some other function, it can hold the clock line SCL low to force the master into a wait state (clock stretching). Data transfer then continues when the slave is ready for another byte of data and release the clock line SCL.

![](_page_29_Figure_4.jpeg)

**Figure 19. Data Transfer on the I <sup>2</sup>C Bus**

## *8.2.16.4 Acknowledge (ACK) and Not Acknowledge (NACK)*

The acknowledge takes place after every byte. The acknowledge bit allows the receiver to signal the transmitter that the byte was successfully received and another byte may be sent. All clock pulses, including the acknowledge 9 th clock pulse, are generated by the master.

The transmitter releases the SDA line during the acknowledge clock pulse so the receiver can pull the SDA line LOW and it remains stable LOW during the HIGH period of this clock pulse.

When SDA remains HIGH during the 9 th clock pulse, this is the Not Acknowledge signal. The master can then generate either a STOP to abort the transfer or a repeated START to start a new transfer.

## *8.2.16.5 Slave Address and Data Direction Bit*

After the START, a slave address is sent. This address is 7 bits long followed by the eighth bit as a data direction bit (bit R/W). A zero indicates a transmission (WRITE) and a one indicates a request for data (READ).

![](_page_29_Figure_12.jpeg)

![](_page_30_Picture_0.jpeg)

### *8.2.16.6 Single Read and Write*

![](_page_30_Figure_4.jpeg)

### **Figure 21. Single Write**

![](_page_30_Figure_6.jpeg)

**Figure 22. Single Read**

If the register address is not defined, the charger IC send back NACK and go back to the idle state.

### *8.2.16.7 Multi-Read and Multi-Write*

The charger device supports multi-read and multi-write on REG00 through REG14 except REG0C.

![](_page_30_Figure_11.jpeg)

**Figure 23. Multi-Write**

![](_page_30_Figure_13.jpeg)

### **Figure 24. Multi-Read**

REG0C is a fault register. It keeps all the fault information from last read until the host issues a new read. For example, if Charge Safety Timer Expiration fault occurs but recovers later, the fault register REG0C reports the fault when it is read the first time, but returns to normal when it is read the second time. In order to get the fault information at present, the host has to read REG0C for the second time. The only exception is NTC\_FAULT which always reports the actual condition on the TS pin. In addition, REG0C does not support multi-read and multi-write.

![](_page_31_Picture_1.jpeg)

## **8.3 Device Functional Modes**

### **8.3.1 Host Mode and Default Mode**

The device is a host controlled charger, but it can operate in default mode without host management. In default mode, the device can be used an autonomous charger with no host or while host is in sleep mode. When the charger is in default mode, WATCHDOG\_FAULT bit is HIGH. When the charger is in host mode, WATCHDOG\_FAULT bit is LOW.

After power-on-reset, the device starts in default mode with watchdog timer expired, or default mode. All the registers are in the default settings.

In default mode, the device keeps charging the battery with 12-hour fast charging safety timer. At the end of the 12-hour, the charging is stopped and the buck converter continues to operate to supply system load. Any write command to device transitions the charger from default mode to host mode. All the device parameters can be programmed by the host. To keep the device in host mode, the host has to reset the watchdog timer by writing 1 to WD\_RST bit before the watchdog timer expires (WATCHDOG\_FAULT bit is set), or disable watchdog timer by setting WATCHDOG bits=00.

When the watchdog timer (WATCHDOG\_FAULT bit = 1) is expired, the device returns to default mode and all registers are reset to default values except IINLIM, VINDPM, VINDPM\_OS, BATFET\_RST\_EN, BATFET\_DLY, and BATFET\_DIS bits.

![](_page_31_Figure_9.jpeg)

**Figure 25. Watchdog Timer Flow Chart**

![](_page_32_Picture_0.jpeg)

### **8.4 Register Maps**

I2C Slave Address: 6AH (1101010B + R/W)

### **8.4.1 REG00**

### **Figure 26. REG00**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 0   | 1   | 0   | 0   | 1   | 0   | 0   | 0   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

| Bit | Field     | Type | Reset                     | Description                                                                 |                                                                                                                                                                                                                                                |  |  |
|-----|-----------|------|---------------------------|-----------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--|--|
| 7   | EN_HIZ    | R/W  | by REG_RST by Watchdog | Enable HIZ Mode 0 – Disable (default) 1 – Enable                      |                                                                                                                                                                                                                                                |  |  |
| 6   | EN_ILIM   | R/W  | by REG_RST by Watchdog | Enable ILIM Pin 0 – Disable 1 – Enable (default: Enable ILIM pin (1)) |                                                                                                                                                                                                                                                |  |  |
| 5   | IINLIM[5] | R/W  | by REG_RST                | 1600mA                                                                      | Input Current Limit                                                                                                                                                                                                                            |  |  |
| 4   | IINLIM[4] | R/W  | by REG_RST                | 800mA                                                                       | Offset: 100mA Range: 100mA (000000) – 3.25A (111111)                                                                                                                                                                                        |  |  |
| 3   | IINLIM[3] | R/W  | by REG_RST                | 400mA                                                                       | Default:0001000 (500mA)                                                                                                                                                                                                                        |  |  |
| 2   | IINLIM[2] | R/W  | by REG_RST                | 200mA                                                                       | (Actual input current limit is the lower of I2C or ILIM pin) IINLIM bits are changed automaticallly after input source                                                                                                                      |  |  |
| 1   | IINLIM[1] | R/W  | by REG_RST                | 100mA                                                                       | type detection is completed                                                                                                                                                                                                                    |  |  |
| 0   | IINLIM[0] | R/W  | by REG_RST                | 50mA                                                                        | USB Host SDP w/ OTG=Hi (USB500) = 500mA USB Host SDP w/ OTG=Lo (USB100) = 500mA USB CDP = 1.5A USB DCP = 3.25A Adjustable High Voltage (MaxCharge) DCP = 1.5A Unknown Adapter = 500mA Non-Standard Adapter = 1A/2A/2.1A/2.4A |  |  |

### **Table 8. REG00**

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

### **8.4.2 REG01**

### **Figure 27. REG01**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 0   | 0   | 0   | 0   | 0   | 1   | 1   | 0   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 9. REG01**

| Bit | Field        | Type | Reset                     | Description                                                                                                                                                                                                          |                                                                                                                                    |  |
|-----|--------------|------|---------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------|--|
| 7   | BHOT[1]      | R/W  | by REG_RST by Watchdog | Boost Mode Hot Temperature Monitor Threshold 00 – VBHOT1 Threshold (34.75%) (default) 01 – VBHOT0 Threshold (Typ. 37.75%) 10 – VBHOT2 Threshold (Typ. 31.25%) 11 – Disable boost mode thermal protection |                                                                                                                                    |  |
| 6   | BHOT[0]      | R/W  | by REG_RST by Watchdog |                                                                                                                                                                                                                      |                                                                                                                                    |  |
| 5   | BCOLD        | R/W  | by REG_RST by Watchdog | Boost Mode Cold Temperature Monitor Threshold 0 – VBCOLD0 Threshold (Typ. 77%) (default) 1 – VBCOLD1 Threshold (Typ. 80%)                                                                                      |                                                                                                                                    |  |
| 4   | VINDPM_OS[4] | R/W  | by REG_RST                | 1600mV                                                                                                                                                                                                               | Input Voltage Limit Offset                                                                                                         |  |
| 3   | VINDPM_OS[3] | R/W  | by REG_RST                | 800mV                                                                                                                                                                                                                | Default: 600mV (00110) Range: 0mV – 3100mV                                                                                      |  |
| 2   | VINDPM_OS[2] | R/W  | by REG_RST                | 400mV                                                                                                                                                                                                                | Minimum VINDPM threshold is clamped at 3.9V                                                                                        |  |
| 1   | VINDPM_OS[1] | R/W  | by REG_RST                | 200mV                                                                                                                                                                                                                | Maximum VINDPM threshold is clamped at 15.3V When VBUS at noLoad is ≤ 6V, the VINDPM_OS is used                                 |  |
| 0   | VINDPM_OS[0] | R/W  | by REG_RST                | 100mV                                                                                                                                                                                                                | to calculate VINDPM threhold When VBUS at noLoad is > 6V, the VINDPM_OS multiple by 2 is used to calculate VINDPM threshold. |  |

![](_page_34_Picture_0.jpeg)

### **8.4.3 REG02**

### **Figure 28. REG02**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 10. REG02**

| Bit | Field        | Type | Reset                     | Description                                                                                                                                                                                                                      |
|-----|--------------|------|---------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 7   | CONV_START   | R/W  | by REG_RST by Watchdog | ADC Conversion Start Control 0 – ADC conversion not active (default). 1 – Start ADC Conversion This bit is read-only when CONV_RATE = 1. The bit stays high during ADC conversion and during input source detection. |
| 6   | CONV_RATE    | R/W  | by REG_RST by Watchdog | ADC Conversion Rate Selection 0 – One shot ADC conversion (default) 1 – Start 1s Continuous Conversion                                                                                                                     |
| 5   | BOOST_FREQ   | R/W  | by REG_RST by Watchdog | Boost Mode Frequency Selection 0 – 1.5MHz 1 – 500KHz (default) Note: Write to this bit is ignored when OTG_CONFIG is enabled.                                                                                           |
| 4   | ICO_EN       | R/W  | by REG_RST                | Input Current Optimizer (ICO) Enable 0 – Disable ICO Algorithm 1 – Enable ICO Algorithm (default)                                                                                                                          |
| 3   | HVDCP_EN     | R/W  | by REG_RST                | High Voltage DCP Enable 0 – Disable HVDCP handshake 1 – Enable HVDCP handshake (default)                                                                                                                                   |
| 2   | MAXC_EN      | R/W  | by REG_RST                | MaxCharge Adapter Enable 0 – Disable MaxCharge handshake 1 – Enable MaxCharge handshake (default)                                                                                                                          |
| 1   | FORCE_DPDM   | R/W  | by REG_RST by Watchdog | Force D+/D- Detection 0 – Not in D+/D- or PSEL detection (default) 1 – Force D+/D- detection                                                                                                                               |
| 0   | AUTO_DPDM_EN | R/W  | by REG_RST                | Automatic D+/D- Detection Enable 0 –Disable D+/D- or PSEL detection when VBUS is plugged-in 1 –Enable D+/D- or PEL detection when VBUS is plugged-in (default)                                                             |

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

### **8.4.4 REG03**

### **Figure 29. REG03**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0  |
|-----|-----|-----|-----|-----|-----|-----|----|
| 0   | 0   | 0   | 1   | 1   | 0   | 1   | 0  |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | RW |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 11. REG03**

| Bit | Field       | Type | Reset                     | Description                                                                                 |                                 |
|-----|-------------|------|---------------------------|---------------------------------------------------------------------------------------------|---------------------------------|
| 7   | BAT_LOADEN  | R/W  | by REG_RST by Watchdog | Battery Load (IBATLOAD) Enable 0 – Disabled (default) 1 – Enabled                     |                                 |
| 6   | WD_RST      | R/W  | by REG_RST by Watchdog | I2C Watchdog Timer Reset 0 – Normal (default) 1 – Reset (Back to 0 after timer reset) |                                 |
| 5   | OTG_CONFIG  | R/W  | by REG_RST by Watchdog | Boost (OTG) Mode Configuration 0 – OTG Disable 1 – OTG Enable (default)               |                                 |
| 4   | CHG_CONFIG  | R/W  | by REG_RST by Watchdog | Charge Enable Configuration 0 - Charge Disable 1- Charge Enable (default)             |                                 |
| 3   | SYS_MIN[2]  | R/W  | by REG_RST                | 0.4V                                                                                        | Minimum System Voltage Limit    |
| 2   | SYS_MIN[1]  | R/W  | by REG_RST                | 0.2V                                                                                        | Offset: 3.0V Range 3.0V-3.7V |
| 1   | SYS_MIN[02] | R/W  | by REG_RST                | 0.1V                                                                                        | Default: 3.5V (101)             |
| 0   | Reserved    | R/W  | by REG_RST by Watchdog | Reserved (default = 0)                                                                      |                                 |

![](_page_36_Picture_0.jpeg)

### **8.4.5 REG04**

### **Figure 30. REG04**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 0   | 0   | 1   | 0   | 0   | 0   | 0   | 0   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 12. REG04**

| Bit | Field    | Type | Reset                        | Description                                                                                                                            |                                                                                                               |  |  |
|-----|----------|------|------------------------------|----------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------|--|--|
| 7   | EN_PUMPX | R/W  | by Softwareby by Watchdog | Current pulse control Enable 0 - Disable Current pulse control (default) 1- Enable Current pulse control (PUMPX_UP and PUMPX_DN) |                                                                                                               |  |  |
| 6   | ICHG[6]  | R/W  | by Softwareby by Watchdog | 4096mA                                                                                                                                 |                                                                                                               |  |  |
| 5   | ICHG[5]  | R/W  | by Softwareby by Watchdog | 2048mA                                                                                                                                 |                                                                                                               |  |  |
| 4   | ICHG[4]  | R/W  | by Softwareby by Watchdog | 1024mA                                                                                                                                 | Fast Charge Current Limit Offset: 0mA Range: 0mA (0000000) – 5056mA (1001111)                           |  |  |
| 3   | ICHG[3]  | R/W  | by Softwareby by Watchdog | 512mA                                                                                                                                  | Default: 2048mA (0100000) Note:                                                                            |  |  |
| 2   | ICHG[2]  | R/W  | by Softwareby by Watchdog | 256mA                                                                                                                                  | ICHG=000000 (0mA) disables charge ICHG > 1001111 (5056mA) is clamped to register value 1001111 (5056mA) |  |  |
| 1   | ICHG[1]  | R/W  | by Softwareby by Watchdog | 128mA                                                                                                                                  |                                                                                                               |  |  |
| 0   | ICHG[0]  | R/W  | by Softwareby by Watchdog | 64mA                                                                                                                                   |                                                                                                               |  |  |

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

### **8.4.6 REG05**

### **Figure 31. REG05**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 0   | 0   | 0   | 1   | 0   | 0   | 1   | 1   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 13. REG05**

| Bit | Field      | Type | Reset                        | Description |                                               |  |
|-----|------------|------|------------------------------|-------------|-----------------------------------------------|--|
| 7   | IPRECHG[3] | R/W  | by Softwareby by Watchdog | 512mA       |                                               |  |
| 6   | IPRECHG[2] | R/W  | by Softwareby by Watchdog | 256mA       | Precharge Current Limit Offset: 64mA       |  |
| 5   | IPRECHG[1] | R/W  | by Softwareby by Watchdog | 128mA       | Range: 64mA – 1024mA Default: 128mA (0001) |  |
| 4   | IPRECHG[0] | R/W  | by Softwareby by Watchdog | 64mA        |                                               |  |
| 3   | ITERM[3]   | R/W  | by Softwareby by Watchdog | 512mA       |                                               |  |
| 2   | ITERM[2]   | R/W  | by Softwareby by Watchdog | 256mA       | Termination Current Limit Offset: 64mA     |  |
| 1   | ITERM[1]   | R/W  | by Softwareby by Watchdog | 128mA       | Range: 64mA – 1024mA Default: 256mA (0011) |  |
| 0   | ITERM[0]   | R/W  | by Softwareby by Watchdog | 64mA        |                                               |  |

![](_page_38_Picture_0.jpeg)

### **8.4.7 REG06**

### **Figure 32. REG06**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 0   | 1   | 0   | 1   | 1   | 1   | 1   | 0   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 14. REG06**

| Bit | Field   | Type | Reset                        | Description                                                                                                                                                             |                                                                                          |  |
|-----|---------|------|------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------|--|
| 7   | VREG[5] | R/W  | by Softwareby by Watchdog | 512mV                                                                                                                                                                   |                                                                                          |  |
| 6   | VREG[4] | R/W  | by Softwareby by Watchdog | 256mV                                                                                                                                                                   | Charge Voltage Limit                                                                     |  |
| 5   | VREG[3] | R/W  | by Softwareby by Watchdog | 128mV                                                                                                                                                                   | Offset: 3.840V Range: 3.840V – 4.608V (110000)                                        |  |
| 4   | VREG[2] | R/W  | by Softwareby by Watchdog | 64mV                                                                                                                                                                    | Default: 4.208V (010111) Note: VREG > 110000 (4.608V) is clamped to register value |  |
| 3   | VREG[1] | R/W  | by Softwareby by Watchdog | 32mV                                                                                                                                                                    | 110000 (4.608V)                                                                          |  |
| 2   | VREG[0] | R/W  | by Softwareby by Watchdog | 16mV                                                                                                                                                                    |                                                                                          |  |
| 1   | BATLOWV | R/W  | by Softwareby by Watchdog | Battery Precharge to Fast Charge Threshold 0 – 2.8V 1 – 3.0V (default)                                                                                            |                                                                                          |  |
| 0   | VRECHG  | R/W  | by Softwareby by Watchdog | Battery Recharge Threshold Offset (below Charge Voltage Limit) 0 – 100mV (VRECHG) below VREG (REG06[7:2]) (default) 1 – 200mV (VRECHG) below VREG (REG06[7:2]) |                                                                                          |  |

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

### **8.4.8 REG07**

### **Figure 33. REG07**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 1   | 0   | 0   | 1   | 1   | 1   | 0   | 1   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 15. REG07**

| Bit | Field        | Type | Reset                        | Description                                                                                 |
|-----|--------------|------|------------------------------|---------------------------------------------------------------------------------------------|
| 7   | EN_TERM      | R/W  | by Softwareby by Watchdog | Charging Termination Enable 0 – Disable 1 – Enable (default)                          |
| 6   | STAT_DIS     | R/W  | by Softwareby by Watchdog | STAT Pin Disable 0 – Enable STAT pin function (default) 1 – Disable STAT pin function |
| 5   | WATCHDOG[1]  | R/W  | by Softwareby by Watchdog | I2C Watchdog Timer Setting 00 – Disable watchdog timer                                   |
| 4   | WATCHDOG[0]  | R/W  | by Softwareby by Watchdog | 01 – 40s (default) 10 – 80s 11 – 160s                                                 |
| 3   | EN_TIMER     | R/W  | by Softwareby by Watchdog | Charging Safety Timer Enable 0 – Disable 1 – Enable (default)                         |
| 2   | CHG_TIMER[1] | R/W  | by Softwareby by Watchdog | Fast Charge Timer Setting 00 – 5 hrs                                                     |
| 1   | CHG_TIMER[0] | R/W  | by Softwareby by Watchdog | 01 – 8 hrs 10 – 12 hrs (default) 11 – 20 hrs                                          |
| 0   | Reserved     | R/W  |                              | Reserved (Default = 1)                                                                      |

![](_page_40_Picture_0.jpeg)

### **8.4.9 REG08**

### **Figure 34. REG08**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 0   | 0   | 0   | 0   | 0   | 0   | 1   | 1   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 16. REG08**

| Bit | Field       | Type | Reset                        | Description                                                                                  |                                                                                                 |  |  |
|-----|-------------|------|------------------------------|----------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------|--|--|
| 7   | BAT_COMP[2] | R/W  | by Softwareby by Watchdog | 80mΩ                                                                                         |                                                                                                 |  |  |
| 6   | BAT_COMP[1] | R/W  | by Softwareby by Watchdog | 40mΩ                                                                                         | IR Compensation Resistor Setting Range: 0 – 140mΩ Default: 0Ω (000) (i.e. Disable IRComp) |  |  |
| 5   | BAT_COMP[0] | R/W  | by Softwareby by Watchdog | 20mΩ                                                                                         |                                                                                                 |  |  |
| 4   | VCLAMP[2]   | R/W  | by Softwareby by Watchdog | 128mV                                                                                        | IR Compensation Voltage Clamp                                                                   |  |  |
| 3   | VCLAMP[1]   | R/W  | by Softwareby by Watchdog | 64mV                                                                                         | above VREG (REG06[7:2]) Offset: 0mV Range: 0-224mV                                        |  |  |
| 2   | VCLAMP[0]   | R/W  | by Softwareby by Watchdog | 32mV                                                                                         | Default: 0mV (000)                                                                              |  |  |
| 1   | TREG[1]     | R/W  | by Softwareby by Watchdog | Thermal Regulation Threshold 00 – 60°C 01 – 80°C 10 – 100°C 11 – 120°C (default) |                                                                                                 |  |  |
| 0   | TREG[0]     | R/W  | by Softwareby by Watchdog |                                                                                              |                                                                                                 |  |  |

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

### **8.4.10 REG09**

### **Figure 35. REG09**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 0   | 1   | 0   | 0   | 0   | 1   | 0   | 0   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 17. REG09**

| Bit | Field         | Type | Reset                        | Description                                                                                                                                                                                                               |
|-----|---------------|------|------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 7   | FORCE_ICO     | R/W  | by Softwareby by Watchdog | Force Start Input Current Optimizer (ICO) 0 – Do not force ICO (default) 1 – Force ICO Note: This bit is can only be set only and always returns to 0 after ICO starts                                        |
| 6   | TMR2X_EN      | R/W  | by Softwareby by Watchdog | Safety Timer Setting during DPM or Thermal Regulation 0 – Safety timer not slowed by 2X during input DPM or thermal regulation 1 – Safety timer slowed by 2X during input DPM or thermal regulation (default) |
| 5   | BATFET_DIS    | R/W  | by Softwareby                | Force BATFET off to enable ship mode 0 – Allow BATFET turn on (default) 1 – Force BATFET off                                                                                                                        |
| 4   | Reserved      | R/W  |                              | Reserved (Default = 0)                                                                                                                                                                                                    |
| 3   | BATFET_DLY    | R/W  | by Softwareby                | BATFET turn off delay control 0 – BATFET turn off immediately when BATFET_DIS bit is set (default) 1 – BATFET turn off delay by tSM_DLY when BATFET_DIS bit is set                                                  |
| 2   | BATFET_RST_EN | R/W  | by Softwareby                | BATFET full system reset enable 0 – Disable BATFET full system reset 1 – Enable BATFET full system reset (default)                                                                                                  |
| 1   | PUMPX_UP      | R/W  | by Softwareby by Watchdog | Current pulse control voltage up enable 0 – Disable (default) 1 – Enable Note: This bit is can only be set when EN_PUMPX bit is set and returns to 0 after current pulse control sequence is completed     |
| 0   | PUMPX_DN      | R/W  | by Softwareby by Watchdog | Current pulse control voltage down enable 0 – Disable (default) 1 – Enable Note: This bit is can only be set when EN_PUMPX bit is set and returns to 0 after current pulse control sequence is completed   |

![](_page_42_Picture_0.jpeg)

### **8.4.11 REG0A**

### **Figure 36. REG0A**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 1   | 0   | 0   | 1   | 0   | 0   | 1   | 1   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 18. REG0A**

| Bit | Field     | Type | Reset                        | Description            |                                                |  |
|-----|-----------|------|------------------------------|------------------------|------------------------------------------------|--|
| 7   | BOOSTV[3] | R/W  | by Softwareby by Watchdog | 512mV                  |                                                |  |
| 6   | BOOSTV[2] | R/W  | by Softwareby by Watchdog | 256mV                  | Boost Mode Voltage Regulation Offset: 4.55V |  |
| 5   | BOOSTV[1] | R/W  | by Softwareby                | 128mV                  | Range: 4.55V – 5.51V Default: 5.126V (1001) |  |
| 4   | BOOSTV[0] | R/W  | by Softwareby by Watchdog | 64mV                   |                                                |  |
| 3   | Reserved  | R/W  | by Software by Watchdog   | Reserved (default = 0) |                                                |  |
| 2   | Reserved  | R/W  | by Software by Watchdog   | Reserved (default = 0) |                                                |  |
| 1   | Reserved  | R/W  | by Software by Watchdog   | Reserved (default = 1) |                                                |  |
| 0   | Reserved  | R/W  | by Software by Watchdog   | Reserved (default = 1) |                                                |  |

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

### **8.4.12 REG0B**

### **Figure 37. REG0B**

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|
| x | x | x | x | x | x | x | x |
| R | R | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 19. REG0B**

| Bit | Field        | Type | Reset | Description                                                                                                                                                                                                                                                  |  |  |
|-----|--------------|------|-------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--|--|
| 7   | VBUS_STAT[2] | R    | N/A   | VBUS Status register                                                                                                                                                                                                                                         |  |  |
| 6   | VBUS_STAT[1] | R    | N/A   | bq25895 000: No Input 001: USB Host SDP                                                                                                                                                                                                                   |  |  |
| 5   | VBUS_STAT[0] | R    | N/A   | 010: USB CDP (1.5A) 011: USB DCP (3.25A) 100: Adjustable High Voltage DCP (MaxCharge) (1.5A) 101: Unknown Adapter (500mA) 110: Non-Standard Adapter (1A/2A/2.1A/2.4A) 111: OTG Note: Software current limit is reported in IINLIM register |  |  |
| 4   | CHRG_STAT[1] | R    | N/A   | Charging Status                                                                                                                                                                                                                                              |  |  |
| 3   | CHRG_STAT[0] | R    | N/A   | 00 – Not Charging 01 – Pre-charge ( < VBATLOWV) 10 – Fast Charging 11 – Charge Termination Done                                                                                                                                                     |  |  |
| 2   | PG_STAT      | R    | N/A   | Power Good Status 0 – Not Power Good 1 – Power Good                                                                                                                                                                                                    |  |  |
| 1   | SDP_STAT     | R    | N/A   | USB Input Status 0 – USB100 input is detected 1 – USB500 input is detected Note: This bit always read 1 when VBUS_STAT is not 001                                                                                                                   |  |  |
| 0   | VSYS_STAT    | R    | N/A   | VSYS Regulation Status 0 – Not in VSYSMIN regulation (BAT > VSYSMIN) 1 – In VSYSMIN regulation (BAT < VSYSMIN)                                                                                                                                         |  |  |

![](_page_44_Picture_0.jpeg)

### **8.4.13 REG0C**

### **Figure 38. REG0C**

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|
| x | x | x | x | x | x | x | x |
| R | R | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 20. REG0C**

| Bit | Field          | Type | Reset | Description                                                                                                                                                |
|-----|----------------|------|-------|------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 7   | WATCHDOG_FAULT | R    | N/A   | Watchdog Fault Status Status 0 – Normal 1- Watchdog timer expiration                                                                                 |
| 6   | BOOST_FAULT    | R    | N/A   | Boost Mode Fault Status 0 – Normal 1 – VBUS overloaded in OTG, or VBUS OVP, or battery is too low in boost mode                                   |
| 5   | CHRG_FAULT[1]  | R    | N/A   | Charge Fault Status                                                                                                                                        |
| 4   | CHRG_FAULT[0]  | R    | N/A   | 00 – Normal 01 – Input fault (VBUS > VACOV or VBAT < VBUS < VVBUSMIN(typical 3.8V) ) 10 - Thermal shutdown 11 – Charge Safety Timer Expiration |
| 3   | BAT_FAULT      | R    | N/A   | Battery Fault Status 0 – Normal 1 – BATOVP (VBAT > VBATOVP)                                                                                          |
| 2   | NTC_FAULT[2]   | R    | N/A   | NTC Fault Status                                                                                                                                           |
| 1   | NTC_FAULT[1]   | R    | N/A   | Buck Mode: 000 – Normal                                                                                                                                 |
| 0   | NTC_FAULT[0]   | R    | N/A   | 001 – TS Cold 010 – TS Hot Boost Mode: 000 – Normal 101 – TS Cold 110 – TS Hot                                                              |

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

### **8.4.14 REG0D**

### **Figure 39. REG0D**

| 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |
|-----|-----|-----|-----|-----|-----|-----|-----|
| 0   | 0   | 0   | 1   | 0   | 0   | 1   | 0   |
| R/W | R/W | R/W | R/W | R/W | R/W | R/W | R/W |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 21. REG0D**

| Bit | Field        | Type | Reset         | Description                                                                                                         |                                                                              |  |  |
|-----|--------------|------|---------------|---------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------|--|--|
| 7   | FORCE_VINDPM | R/W  | by Softwareby | VINDPM Threshold Setting Method 0 – Run Relative VINDPM Threshold (default) 1 – Run Absolute VINDPM Threshold |                                                                              |  |  |
| 6   | VINDPM[6]    | R/W  | by Softwareby | 6400mV                                                                                                              | Absolute VINDPM Threshold                                                    |  |  |
| 5   | VINDPM[5]    | R/W  | by Softwareby | 3200mV                                                                                                              | Offset: 2.6V Range: 3.9V (0001101) – 15.3V (1111111)                      |  |  |
| 4   | VINDPM[4]    | R/W  | by Softwareby | 1600mV                                                                                                              | Default: 4.4V (0010010)                                                      |  |  |
| 3   | VINDPM[3]    | R/W  | by Softwareby | 800mV                                                                                                               | Note: Value < 0001101 is clamped to 3.9V (0001101)                        |  |  |
| 2   | VINDPM[2]    | R/W  | by Softwareby | 400mV                                                                                                               | Register is read only when FORCE_VINDPM=0 and can                            |  |  |
| 1   | VINDPM[1]    | R/W  | by Softwareby | 200mV                                                                                                               | be written by internal control based on relative VINDPM threshold setting |  |  |
| 0   | VINDPM[0]    | R/W  | by Softwareby | 100mV                                                                                                               | Register can be read/write when FORCE_VINDPM = 1                             |  |  |

### **8.4.15 REG0E**

### **Figure 40. REG0E**

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| R | R | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 22. REG0E**

| Bit | Field      | Type | Reset | Description                                                          |                                                              |  |
|-----|------------|------|-------|----------------------------------------------------------------------|--------------------------------------------------------------|--|
| 7   | THERM_STAT | R    | N/A   | Thermal Regulation Status 0 – Normal 1 – In Thermal Regulation |                                                              |  |
| 6   | BATV[6]    | R    | N/A   | 1280mV                                                               |                                                              |  |
| 5   | BATV[5]    | R    | N/A   | 640mV                                                                |                                                              |  |
| 4   | BATV[4]    | R    | N/A   | 320mV                                                                | ADC conversion of Battery Voltage (VBAT)                     |  |
| 3   | BATV[3]    | R    | N/A   | 160mV                                                                | Offset: 2.304V Range: 2.304V (0000000) – 4.848V (1111111) |  |
| 2   | BATV[2]    | R    | N/A   | 80mV                                                                 | Default: 2.304V (0000000)                                    |  |
| 1   | BATV[1]    | R    | N/A   | 40mV                                                                 |                                                              |  |
| 0   | BATV[0]    | R    | N/A   | 20mV                                                                 |                                                              |  |

![](_page_46_Picture_0.jpeg)

### **8.4.16 REG0F**

## **Figure 41. REG0F**

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| R | R | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 23. REG0F**

| Bit | Field    | Type | Reset | Description              |                                                              |  |
|-----|----------|------|-------|--------------------------|--------------------------------------------------------------|--|
| 7   | Reserved | R    | N/A   | Reserved: Always reads 0 |                                                              |  |
| 6   | SYSV[6]  | R    | N/A   | 1280mV                   |                                                              |  |
| 5   | SYSV[5]  | R    | N/A   | 640mV                    |                                                              |  |
| 4   | SYSV[4]  | R    | N/A   | 320mV                    | ADDC conversion of System Voltage (VSYS)                     |  |
| 3   | SYSV[3]  | R    | N/A   | 160mV                    | Offset: 2.304V Range: 2.304V (0000000) – 4.848V (1111111) |  |
| 2   | SYSV[2]  | R    | N/A   | 80mV                     | Default: 2.304V (0000000)                                    |  |
| 1   | SYSV[1]  | R    | N/A   | 40mV                     |                                                              |  |
| 0   | SYSV[0]  | R    | N/A   | 20mV                     |                                                              |  |

### **8.4.17 REG10**

### **Figure 42. REG10**

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| R | R | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 24. REG10**

| Bit | Field    | Type | Reset | Description              |                                                         |  |
|-----|----------|------|-------|--------------------------|---------------------------------------------------------|--|
| 7   | Reserved | R    | N/A   | Reserved: Always reads 0 |                                                         |  |
| 6   | TSPCT[6] | R    | N/A   | 29.76%                   |                                                         |  |
| 5   | TSPCT[5] | R    | N/A   | 14.88%                   |                                                         |  |
| 4   | TSPCT[4] | R    | N/A   | 7.44%                    | ADC conversion of TS Voltage (TS) as percentage of REGN |  |
| 3   | TSPCT[3] | R    | N/A   | 3.72%                    | Offset: 21% Range 21% (0000000) – 80% (1111111)      |  |
| 2   | TSPCT[2] | R    | N/A   | 1.86%                    | Default: 21% (0000000)                                  |  |
| 1   | TSPCT[1] | R    | N/A   | 0.93%                    |                                                         |  |
| 0   | TSPCT[0] | R    | N/A   | 0.465%                   |                                                         |  |

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

### **8.4.18 REG11**

### **Figure 43. REG11**

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| R | R | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 25. REG11**

| Bit | Field    | Type | Reset | Description                                                    |                                                        |  |
|-----|----------|------|-------|----------------------------------------------------------------|--------------------------------------------------------|--|
| 7   | VBUS_GD  | R    | N/A   | VBUS Good Status 0 – Not VBUS attached 1 – VBUS Attached |                                                        |  |
| 6   | VBUSV[6] | R    | N/A   | 6400mV                                                         |                                                        |  |
| 5   | VBUSV[5] | R    | N/A   | 3200mV                                                         |                                                        |  |
| 4   | VBUSV[4] | R    | N/A   | 1600mV                                                         | ADC conversion of VBUS voltage (VBUS)                  |  |
| 3   | VBUSV[3] | R    | N/A   | 800mV                                                          | Offset: 2.6V Range 2.6V (0000000) – 15.3V (1111111) |  |
| 2   | VBUSV[2] | R    | N/A   | 400mV                                                          | Default: 2.6V (0000000)                                |  |
| 1   | VBUSV[1] | R    | N/A   | 200mV                                                          |                                                        |  |
| 0   | VBUSV[0] | R    | N/A   | 100mV                                                          |                                                        |  |

### **8.4.19 REG12**

### **Figure 44. REG12**

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| R | R | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 26. REG12**

| Bit | Field    | Type | Reset | Description    |                                                     |  |  |
|-----|----------|------|-------|----------------|-----------------------------------------------------|--|--|
| 7   | Unused   | R    | N/A   | Always reads 0 |                                                     |  |  |
| 6   | ICHGR[6] | R    | N/A   | 3200mV         |                                                     |  |  |
| 5   | ICHGR[5] | R    | N/A   | 1600mV         | ADC conversion of Charge Current (IBAT) when VBAT > |  |  |
| 4   | ICHGR[4] | R    | N/A   | 800mV          | VBATSHORT Offset: 0mA                            |  |  |
| 3   | ICHGR[3] | R    | N/A   | 400mV          | Range 0mA (0000000) – 6350mA (1111111)              |  |  |
| 2   | ICHGR[2] | R    | N/A   | 200mV          | Default: 0mA (0000000) Note:                     |  |  |
| 1   | ICHGR[1] | R    | N/A   | 100mV          | This register returns 0000000 for VBAT < VBATSHORT  |  |  |
| 0   | ICHGR[0] | R    | N/A   | 50mV           |                                                     |  |  |

![](_page_48_Picture_0.jpeg)

### **8.4.20 REG13**

### **Figure 45. REG13**

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|---|---|---|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| R | R | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 27. REG13**

| Bit | Field       | Type | Reset | Description                                      |                                                                                                                                                        |  |  |
|-----|-------------|------|-------|--------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------|--|--|
| 7   | VDPM_STAT   | R    | N/A   | VINDPM Status 0 – Not in VINDPM 1 – VINDPM |                                                                                                                                                        |  |  |
| 6   | IDPM_STAT   | R    | N/A   | IINDPM Status 0 – Not in IINDPM 1 – IINDPM |                                                                                                                                                        |  |  |
| 5   | IDPM_LIM[5] | R    | N/A   | 1600mA                                           |                                                                                                                                                        |  |  |
| 4   | IDPM_LIM[4] | R    | N/A   | 800mA                                            |                                                                                                                                                        |  |  |
| 3   | IDPM_LIM[3] | R    | N/A   | 400mA                                            | Input Current Limit in effect while Input Current Optimizer (ICO) is enabled Offset: 100mA (default) Range 100mA (0000000) – 3.25mA (1111111) |  |  |
| 2   | IDPM_LIM[2] | R    | N/A   | 200mA                                            |                                                                                                                                                        |  |  |
| 1   | IDPM_LIM[1] | R    | N/A   | 100mA                                            |                                                                                                                                                        |  |  |
| 0   | IDPM_LIM[0] | R    | N/A   | 50mA                                             |                                                                                                                                                        |  |  |

### **8.4.21 REG14**

### **Figure 46. REG14**

| 7   | 6   | 5 | 4 | 3 | 2 | 1 | 0 |
|-----|-----|---|---|---|---|---|---|
| 0   | 0   | 0 | 0 | 0 | 0 | 0 | 0 |
| R/W | R/W | R | R | R | R | R | R |

LEGEND: R/W = Read/Write; R = Read only; -n = value after reset

### **Table 28. REG14**

| Bit | Field         | Type | Reset | Description                                                                                                                                                                          |  |  |  |
|-----|---------------|------|-------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--|--|--|
| 7   | REG_RST       | R/W  | N/A   | Register Reset 0 – Keep current register setting (default) 1 – Reset to default register value and reset safety timer Note: Reset to 0 after register reset is completed |  |  |  |
| 6   | ICO_OPTIMIZED | R/W  | N/A   | Input Current Optimizer (ICO) Status 0 – Optimization is in progress 1 – Maximum Input Current Detected                                                                        |  |  |  |
| 5   | PN[2]         | R/W  | N/A   |                                                                                                                                                                                      |  |  |  |
| 4   | PN[1]         | R/W  | N/A   | Device Configuration 111: bq25895                                                                                                                                                 |  |  |  |
| 3   | PN[0]         | R/w  | N/A   |                                                                                                                                                                                      |  |  |  |
| 2   | TS_PROFILE    | R/W  | N/A   | Temperature Profile 0 – Cold/Hot (default)                                                                                                                                        |  |  |  |
| 1   | DEV_REV[1]    | R/W  | N/A   |                                                                                                                                                                                      |  |  |  |
| 0   | DEV_REV[0]    | R/W  | N/A   | Device Revision: 01                                                                                                                                                                  |  |  |  |

# **9 Application and Implementation**

### **NOTE**

Information in the following applications sections is not part of the TI component specification, and TI does not warrant its accuracy or completeness. TI's customers are responsible for determining suitability of components for their purposes. Customers should validate and test their design implementation to confirm system functionality.

## **9.1 Application Information**

A typical application consists of the device configured as an I <sup>2</sup>C controlled power path management device and a single cell battery charger for Li-Ion and Li-polymer batteries used in a wide range of smartphones and other portable devices. It integrates an input reverse-block FET (RBFET, Q1), high-side switching FET (HSFET, Q2), low-side switching FET (LSFET, Q3), and BATFET (Q4) between the system and battery. The device also integrates a bootstrap diode for the high-side gate drive.

## **9.2 Typical Application**

![](_page_49_Figure_8.jpeg)

**Figure 47. bq25895 with D+/D- Interface and 2.4 A Boost Mode Output**

## <span id="page-49-0"></span>**9.2.1 Design Requirements**

For this design example, use the parameters shown in [Table](#page-49-1) 29.

### **Table 29. Design Parameter**

<span id="page-49-1"></span>

| PARAMETERS          | VALUES        |  |  |  |
|---------------------|---------------|--|--|--|
| Input voltage range | 3.9 V to 14 V |  |  |  |
| Input current limit | 1.5 A         |  |  |  |
| Fast charge current | 5000 mA       |  |  |  |
| Output voltage      | 4.352 V       |  |  |  |

### **9.2.2 Detailed Design Procedure**

### *9.2.2.1 Inductor Selection*

The device has 1.5 MHz switching frequency to allow the use of small inductor and capacitor values. The Inductor saturation current should be higher than the charging current (ICHG) plus half the ripple current (IRIPPLE):

*<sup>f</sup>* s x L I I + (1/2) I BAT CHG RIPPLE <sup>³</sup> The inductor ripple current depends on input voltage (VBUS), duty cycle (D = VBAT/VVBUS), switching frequency (fs) and inductance (L):

$$
I_{RIPPLE} = \frac{V_{BUS} \times D \times (1-D)}{f \times L}
$$

(6)

(5)

The maximum inductor ripple current happens with D = 0.5 or close to 0.5. Usually inductor ripple is designed in the range of (20–40%) maximum charging current as a trade-off between inductor size and efficiency for a practical design.

### *9.2.2.2 Buck Input Capacitor*

Input capacitor should have enough ripple current rating to absorb input switching ripple current. The worst case RMS ripple current is half of the charging current when duty cycle is 0.5. If the converter does not operate at 50% duty cycle, then the worst case capacitor RMS current IPMID occurs where the duty cycle is closest to 50% and can be estimated by [Equation](#page-50-0) 7:

$$
P_{\text{MID}} = I_{\text{CHG}} \times \sqrt{D \times (1 - D)}
$$
 (7)

<span id="page-50-0"></span>Low ESR ceramic capacitor such as X7R or X5R is preferred for input decoupling capacitor and should be placed to the drain of the high side MOSFET and source of the low side MOSFET as close as possible. Voltage rating of the capacitor must be higher than normal input voltage level. 25 V rating or higher capacitor is preferred for up to 14-V input voltage. 8.2-μF capacitance is suggested for typical of 3 A – 5 A charging current.

### *9.2.2.3 System Output Capacitor*

Output capacitor also should have enough ripple current rating to absorb output switching ripple current. The output capacitor RMS current ICOUT is given:

RIPPLE CSYS RIPPLE I I = 0.29 x I 2 x 3 » (8)

The output capacitor voltage ripple can be calculated as follows:

$$
\Delta V_O = \frac{V_{SYS}}{8 \text{ LC}_{SYS}/s^2} \left( 1 - \frac{V_{SYS}}{V_{BUS}} \right)
$$
 (9)

At certain input/output voltage and switching frequency, the voltage ripple can be reduced by increasing the output filter LC. The charger device has internal loop compensator. To get good loop stability, 1-µH and minimum of 20-µF output capacitor is recommended. The preferred ceramic capacitor is 6V or higher rating, X7R or X5R.

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

![](_page_51_Picture_2.jpeg)

### **9.2.3 Application Curves**

![](_page_51_Figure_5.jpeg)

![](_page_52_Figure_0.jpeg)

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)**

![](_page_52_Figure_2.jpeg)

**[bq25895](http://www.ti.com/product/bq25895?qgpn=bq25895)** SLUSC88A –MARCH 2015–REVISED MAY 2016 **[www.ti.com](http://www.ti.com)**

![](_page_53_Picture_1.jpeg)

### **9.3 System Examples**

![](_page_53_Figure_4.jpeg)

**Figure 59. bq25895 with D+/D- Interface, 3.1 A Boost Mode Output, and no Thermistor Connections**

![](_page_54_Picture_0.jpeg)

## **10 Power Supply Recommendations**

In order to provide an output voltage on SYS, the device requires a power supply between 3.9 V and 14 V input with at least 100-mA current rating connected to VBUS or a single-cell Li-Ion battery with voltage > VBATUVLO connected to BAT. The source current rating needs to be at least 3 A in order for the buck converter of the charger to provide maximum output power to SYS.

## **11 Layout**

## **11.1 Layout Guidelines**

The switching node rise and fall times should be minimized for minimum switching loss. Proper layout of the components to minimize high frequency current path loop (see [Figure](#page-54-0) 60) is important to prevent electrical and magnetic field radiation and high frequency resonant problems. Here is a PCB layout priority list for proper layout. Layout PCB according to this specific order is essential.

- 1. Place input capacitor as close as possible to PMID pin and GND pin connections and use shortest copper trace connection or GND plane.
- 2. Place inductor input terminal to SW pin as close as possible. Minimize the copper area of this trace to lower electrical and magnetic field radiation but make the trace wide enough to carry the charging current. Do not use multiple layers in parallel for this connection. Minimize parasitic capacitance from this area to any other trace or plane.
- 3. Put output capacitor near to the inductor and the IC. Ground connections need to be tied to the IC ground with a short copper trace connection or GND plane.
- 4. Route analog ground separately from power ground. Connect analog ground and connect power ground separately. Connect analog ground and power ground together using power pad as the single ground connection point. Or using a 0Ω resistor to tie analog ground to power ground.
- 5. Use single ground connection to tie charger power ground to charger analog ground. Just beneath the IC. Use ground copper pour but avoid power pins to reduce inductive and capacitive noise coupling.
- 6. Decoupling capacitors should be placed next to the IC pins and make trace connection as short as possible.
- 7. It is critical that the exposed power pad on the backside of the IC package be soldered to the PCB ground. Ensure that there are sufficient thermal vias directly under the IC, connecting to the ground plane on the other layers.
- 8. The via size and number should be enough for a given current path.

See the EVM design for the recommended component placement with trace and via locations. For the VQFN information, refer to [SCBA017](http://www.ti.com/lit/pdf/SCBA017) and [SLUA271](http://www.ti.com/lit/pdf/SLUA271).

## <span id="page-54-0"></span>**11.2 Layout Example**

![](_page_54_Figure_18.jpeg)

**Figure 60. High Frequency Current Path**

# **12 Device and Documentation Support**

## **12.1 Trademarks**

PowerPAD is a trademark of Texas Instruments. All other trademarks are the property of their respective owners.

## **12.2 Electrostatic Discharge Caution**

![](_page_55_Picture_6.jpeg)

These devices have limited built-in ESD protection. The leads should be shorted together or the device placed in conductive foam during storage or handling to prevent electrostatic damage to the MOS gates.

## **12.3 Glossary**

[SLYZ022](http://www.ti.com/lit/pdf/SLYZ022) — *TI Glossary*.

This glossary lists and explains terms, acronyms, and definitions.

## **13 Mechanical, Packaging, and Orderable Information**

The following pages include mechanical, packaging, and orderable information. This information is the most current data available for the designated devices. This data is subject to change without notice and revision of this document. For browser-based versions of this data sheet, refer to the left-hand navigation.

![](_page_56_Picture_0.jpeg)

## **13.1 Package Option Addendum**

### **13.1.1 Packaging Information**

| Orderable Device | Status (1) | Package Type | Package Drawing | Pins | Package Qty | Eco Plan (2)               | Lead/Ball Finish | MSL Peak Temp (3)  | Op Temp (°C) | Device Marking(4)(5) |
|------------------|------------|-----------------|--------------------|------|----------------|----------------------------|------------------|--------------------|--------------|----------------------|
| BQ25895RTWR      | ACTIVE     | WQFN            | RTW                | 24   | 3000           | Green (RoHS & no Sb/Br) | CU NIPDAU        | Level-1-260C-UNLIM | -40 to 85    | BQ25895              |
| BQ25895RTWT      | ACTIVE     | WQFN            | RTW                | 24   | 250            | Green (RoHS & no Sb/Br) | CU NIPDAU        | Level-1-260C-UNLIM | -40 to 85    | BQ25895              |

(1) The marketing status values are defined as follows:

**ACTIVE:** Product device recommended for new designs.

**LIFEBUY:** TI has announced that the device will be discontinued, and a lifetime-buy period is in effect.

**NRND:** Not recommended for new designs. Device is in production to support existing customers, but TI does not recommend using this part in a new design.

**PRE\_PROD** Unannounced device, not in production, not available for mass market, nor on the web, samples not available.

**PREVIEW:** Device has been announced but is not in production. Samples may or may not be available.

**OBSOLETE:** TI has discontinued the production of the device.

(2) Eco Plan - The planned eco-friendly classification: Pb-Free (RoHS), Pb-Free (RoHS Exempt), or Green (RoHS & no Sb/Br) - please check <http://www.ti.com/productcontent> for the latest availability information and additional product content details.

**TBD:** The Pb-Free/Green conversion plan has not been defined.

**Pb-Free (RoHS):** TI's terms "Lead-Free" or "Pb-Free" mean semiconductor products that are compatible with the current RoHS requirements for all 6 substances, including the requirement that lead not exceed 0.1% by weight in homogeneous materials. Where designed to be soldered at high temperatures, TI Pb-Free products are suitable for use in specified lead-free processes.

**Pb-Free (RoHS Exempt):** This component has a RoHS exemption for either 1) lead-based flip-chip solder bumps used between the die and package, or 2) lead-based die adhesive used between the die and leadframe. The component is otherwise considered Pb-Free (RoHS compatible) as defined above.

**Green (RoHS & no Sb/Br)**: TI defines "Green" to mean Pb-Free (RoHS compatible), and free of Bromine (Br) and Antimony (Sb) based flame retardants (Br or Sb do not exceed 0.1% by weight in homogeneous material)

- (3) MSL, Peak Temp. -- The Moisture Sensitivity Level rating according to the JEDEC industry standard classifications, and peak solder temperature.
- (4) There may be additional marking, which relates to the logo, the lot trace code information, or the environmental category on the device
- (5) Multiple Device markings will be inside parentheses. Only on Device Marking contained in parentheses and separated by a "~" will appear on a device. If a line is indented then it is a continuation of the previous line and the two combined represent the entire Device Marking for that device.

**Important Information and Disclaimer:** The information provided on this page represents TI's knowledge and belief as of the date that it is provided. TI bases its knowledge and belief on information provided by third parties, and makes no representation or warranty as to the accuracy of such information. Efforts are underway to better integrate information from third parties. TI has taken and continues to take reasonable steps to provide representative and accurate information but may not have conducted destructive testing or chemical analysis on incoming materials and chemicals. TI and TI suppliers consider certain information to be proprietary, and thus CAS numbers and other limited information may not be available for release.

In no event shall TI's liability arising out of such information exceed the total purchase price of the TI part(s) at issue in this document sold by TI to Customer on an annual basis.

![](_page_57_Picture_1.jpeg)

### **13.1.2 Tape and Reel Information**

![](_page_57_Figure_4.jpeg)

![](_page_57_Figure_5.jpeg)

## Reel Width (W1)

### **QUADRANT ASSIGNMENTS FOR PIN 1 ORIENTATION IN TAPE**

![](_page_57_Figure_8.jpeg)

| Device      | Package Type | Package Drawing | Pins | SPQ  | Reel Diameter (mm) | Reel Width W1 (mm) | A0 (mm) | B0 (mm) | K0 (mm) | P1 (mm) | W (mm) | Pin1 Quadrant |
|-------------|-----------------|--------------------|------|------|--------------------------|--------------------------|------------|------------|------------|------------|-----------|------------------|
| BQ25895RTWR | WQFN            | RTW                | 24   | 3000 | 330.0                    | 12.4                     | 4.3        | 4.3        | 1.3        | 8.0        | 12.0      | Q2               |
| BQ25895RTWT | WQFN            | RTW                | 24   | 250  | 180.0                    | 12.4                     | 4.25       | 4.25       | 1.15       | 8.0        | 12.0      | Q2               |

![](_page_58_Picture_0.jpeg)

![](_page_58_Figure_3.jpeg)

| Device      | Package Type | Package Drawing | Pins | SPQ  | Length (mm) | Width (mm) | Height (mm) |
|-------------|--------------|-----------------|------|------|-------------|------------|-------------|
| BQ25895RTWT | WQFN         | RTW             | 24   | 250  | 210.0       | 185.0      | 35.0        |
| BQ25895RTWR | WQFN         | RTW             | 24   | 3000 | 367.0       | 367.0      | 35.0        |

![](_page_59_Picture_0.jpeg)

## **PACKAGING INFORMATION**

| Orderable Device | Status | Package Type | Package | Pins | Package | Eco Plan                   | Lead/Ball Finish | MSL Peak Temp       | Op Temp (°C) | Device Marking | Samples |
|------------------|--------|--------------|---------|------|---------|----------------------------|------------------|---------------------|--------------|----------------|---------|
|                  | (1)    |              | Drawing |      | Qty     | (2)                        | (6)              | (3)                 |              | (4/5)          |         |
| BQ25895RTWR      | ACTIVE | WQFN         | RTW     | 24   | 3000    | Green (RoHS & no Sb/Br) | CU NIPDAU        | Level-2-260C-1 YEAR | -40 to 85    | BQ25895        |         |
| BQ25895RTWT      | ACTIVE | WQFN         | RTW     | 24   | 250     | Green (RoHS & no Sb/Br) | CU NIPDAU        | Level-2-260C-1 YEAR | -40 to 85    | BQ25895        |         |

**(1)** The marketing status values are defined as follows:

**ACTIVE:** Product device recommended for new designs.

**LIFEBUY:** TI has announced that the device will be discontinued, and a lifetime-buy period is in effect.

**NRND:** Not recommended for new designs. Device is in production to support existing customers, but TI does not recommend using this part in a new design.

**PREVIEW:** Device has been announced but is not in production. Samples may or may not be available.

**OBSOLETE:** TI has discontinued the production of the device.

**(2)** Eco Plan - The planned eco-friendly classification: Pb-Free (RoHS), Pb-Free (RoHS Exempt), or Green (RoHS & no Sb/Br) - please check<http://www.ti.com/productcontent>for the latest availability information and additional product content details.

**TBD:** The Pb-Free/Green conversion plan has not been defined.

**Pb-Free (RoHS):** TI's terms "Lead-Free" or "Pb-Free" mean semiconductor products that are compatible with the current RoHS requirements for all 6 substances, including the requirement that lead not exceed 0.1% by weight in homogeneous materials. Where designed to be soldered at high temperatures, TI Pb-Free products are suitable for use in specified lead-free processes. **Pb-Free (RoHS Exempt):** This component has a RoHS exemption for either 1) lead-based flip-chip solder bumps used between the die and package, or 2) lead-based die adhesive used between the die and leadframe. The component is otherwise considered Pb-Free (RoHS compatible) as defined above.

**Green (RoHS & no Sb/Br):** TI defines "Green" to mean Pb-Free (RoHS compatible), and free of Bromine (Br) and Antimony (Sb) based flame retardants (Br or Sb do not exceed 0.1% by weight in homogeneous material)

**(3)** MSL, Peak Temp. - The Moisture Sensitivity Level rating according to the JEDEC industry standard classifications, and peak solder temperature.

**(4)** There may be additional marking, which relates to the logo, the lot trace code information, or the environmental category on the device.

**(5)** Multiple Device Markings will be inside parentheses. Only one Device Marking contained in parentheses and separated by a "~" will appear on a device. If a line is indented then it is a continuation of the previous line and the two combined represent the entire Device Marking for that device.

**(6)** Lead/Ball Finish - Orderable Devices may have multiple material finish options. Finish options are separated by a vertical ruled line. Lead/Ball Finish values may wrap to two lines if the finish value exceeds the maximum column width.

**Important Information and Disclaimer:**The information provided on this page represents TI's knowledge and belief as of the date that it is provided. TI bases its knowledge and belief on information provided by third parties, and makes no representation or warranty as to the accuracy of such information. Efforts are underway to better integrate information from third parties. TI has taken and continues to take reasonable steps to provide representative and accurate information but may not have conducted destructive testing or chemical analysis on incoming materials and chemicals. TI and TI suppliers consider certain information to be proprietary, and thus CAS numbers and other limited information may not be available for release.

![](_page_60_Picture_0.jpeg)

# **PACKAGE OPTION ADDENDUM**

<www.ti.com> 10-May-2016

In no event shall TI's liability arising out of such information exceed the total purchase price of the TI part(s) at issue in this document sold by TI to Customer on an annual basis.

# **PACKAGE MATERIALS INFORMATION**

## **TAPE AND REEL INFORMATION**

![](_page_61_Figure_4.jpeg)

![](_page_61_Figure_5.jpeg)

![](_page_61_Figure_7.jpeg)

| *All dimensions are nominal |                 |                    |      |      |                          |                          |            |            |            |            |           |                  |
|-----------------------------|-----------------|--------------------|------|------|--------------------------|--------------------------|------------|------------|------------|------------|-----------|------------------|
| Device                      | Package Type | Package Drawing | Pins | SPQ  | Reel Diameter (mm) | Reel Width W1 (mm) | A0 (mm) | B0 (mm) | K0 (mm) | P1 (mm) | W (mm) | Pin1 Quadrant |
| BQ25895RTWR                 | WQFN            | RTW                | 24   | 3000 | 330.0                    | 12.4                     | 4.25       | 4.25       | 1.15       | 8.0        | 12.0      | Q2               |
| BQ25895RTWT                 | WQFN            | RTW                | 24   | 250  | 180.0                    | 12.4                     | 4.25       | 4.25       | 1.15       | 8.0        | 12.0      | Q2               |

# **PACKAGE MATERIALS INFORMATION**

<www.ti.com> 15-Mar-2017

![](_page_62_Figure_4.jpeg)

\*All dimensions are nominal

| Device      | Package Type | Package Drawing | Pins | SPQ  | Length (mm) | Width (mm) | Height (mm) |
|-------------|--------------|-----------------|------|------|-------------|------------|-------------|
| BQ25895RTWR | WQFN         | RTW             | 24   | 3000 | 367.0       | 367.0      | 35.0        |
| BQ25895RTWT | WQFN         | RTW             | 24   | 250  | 210.0       | 185.0      | 35.0        |

![](_page_63_Figure_1.jpeg)

![](_page_64_Figure_7.jpeg)

![](_page_64_Picture_9.jpeg)

![](_page_65_Figure_3.jpeg)

![](_page_65_Picture_11.jpeg)

### **IMPORTANT NOTICE**

Texas Instruments Incorporated (TI) reserves the right to make corrections, enhancements, improvements and other changes to its semiconductor products and services per JESD46, latest issue, and to discontinue any product or service per JESD48, latest issue. Buyers should obtain the latest relevant information before placing orders and should verify that such information is current and complete.

TI's published terms of sale for semiconductor products [\(http://www.ti.com/sc/docs/stdterms.htm\)](http://www.ti.com/sc/docs/stdterms.htm) apply to the sale of packaged integrated circuit products that TI has qualified and released to market. Additional terms may apply to the use or sale of other types of TI products and services.

Reproduction of significant portions of TI information in TI data sheets is permissible only if reproduction is without alteration and is accompanied by all associated warranties, conditions, limitations, and notices. TI is not responsible or liable for such reproduced documentation. Information of third parties may be subject to additional restrictions. Resale of TI products or services with statements different from or beyond the parameters stated by TI for that product or service voids all express and any implied warranties for the associated TI product or service and is an unfair and deceptive business practice. TI is not responsible or liable for any such statements.

Buyers and others who are developing systems that incorporate TI products (collectively, "Designers") understand and agree that Designers remain responsible for using their independent analysis, evaluation and judgment in designing their applications and that Designers have full and exclusive responsibility to assure the safety of Designers' applications and compliance of their applications (and of all TI products used in or for Designers' applications) with all applicable regulations, laws and other applicable requirements. Designer represents that, with respect to their applications, Designer has all the necessary expertise to create and implement safeguards that (1) anticipate dangerous consequences of failures, (2) monitor failures and their consequences, and (3) lessen the likelihood of failures that might cause harm and take appropriate actions. Designer agrees that prior to using or distributing any applications that include TI products, Designer will thoroughly test such applications and the functionality of such TI products as used in such applications.

TI's provision of technical, application or other design advice, quality characterization, reliability data or other services or information, including, but not limited to, reference designs and materials relating to evaluation modules, (collectively, "TI Resources") are intended to assist designers who are developing applications that incorporate TI products; by downloading, accessing or using TI Resources in any way, Designer (individually or, if Designer is acting on behalf of a company, Designer's company) agrees to use any particular TI Resource solely for this purpose and subject to the terms of this Notice.

TI's provision of TI Resources does not expand or otherwise alter TI's applicable published warranties or warranty disclaimers for TI products, and no additional obligations or liabilities arise from TI providing such TI Resources. TI reserves the right to make corrections, enhancements, improvements and other changes to its TI Resources. TI has not conducted any testing other than that specifically described in the published documentation for a particular TI Resource.

Designer is authorized to use, copy and modify any individual TI Resource only in connection with the development of applications that include the TI product(s) identified in such TI Resource. NO OTHER LICENSE, EXPRESS OR IMPLIED, BY ESTOPPEL OR OTHERWISE TO ANY OTHER TI INTELLECTUAL PROPERTY RIGHT, AND NO LICENSE TO ANY TECHNOLOGY OR INTELLECTUAL PROPERTY RIGHT OF TI OR ANY THIRD PARTY IS GRANTED HEREIN, including but not limited to any patent right, copyright, mask work right, or other intellectual property right relating to any combination, machine, or process in which TI products or services are used. Information regarding or referencing third-party products or services does not constitute a license to use such products or services, or a warranty or endorsement thereof. Use of TI Resources may require a license from a third party under the patents or other intellectual property of the third party, or a license from TI under the patents or other intellectual property of TI.

TI RESOURCES ARE PROVIDED "AS IS" AND WITH ALL FAULTS. TI DISCLAIMS ALL OTHER WARRANTIES OR REPRESENTATIONS, EXPRESS OR IMPLIED, REGARDING RESOURCES OR USE THEREOF, INCLUDING BUT NOT LIMITED TO ACCURACY OR COMPLETENESS, TITLE, ANY EPIDEMIC FAILURE WARRANTY AND ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT OF ANY THIRD PARTY INTELLECTUAL PROPERTY RIGHTS. TI SHALL NOT BE LIABLE FOR AND SHALL NOT DEFEND OR INDEMNIFY DESIGNER AGAINST ANY CLAIM, INCLUDING BUT NOT LIMITED TO ANY INFRINGEMENT CLAIM THAT RELATES TO OR IS BASED ON ANY COMBINATION OF PRODUCTS EVEN IF DESCRIBED IN TI RESOURCES OR OTHERWISE. IN NO EVENT SHALL TI BE LIABLE FOR ANY ACTUAL, DIRECT, SPECIAL, COLLATERAL, INDIRECT, PUNITIVE, INCIDENTAL, CONSEQUENTIAL OR EXEMPLARY DAMAGES IN CONNECTION WITH OR ARISING OUT OF TI RESOURCES OR USE THEREOF, AND REGARDLESS OF WHETHER TI HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

Unless TI has explicitly designated an individual product as meeting the requirements of a particular industry standard (e.g., ISO/TS 16949 and ISO 26262), TI is not responsible for any failure to meet such industry standard requirements.

Where TI specifically promotes products as facilitating functional safety or as compliant with industry functional safety standards, such products are intended to help enable customers to design and create their own applications that meet applicable functional safety standards and requirements. Using products in an application does not by itself establish any safety features in the application. Designers must ensure compliance with safety-related requirements and standards applicable to their applications. Designer may not use any TI products in life-critical medical equipment unless authorized officers of the parties have executed a special contract specifically governing such use. Life-critical medical equipment is medical equipment where failure of such equipment would cause serious bodily injury or death (e.g., life support, pacemakers, defibrillators, heart pumps, neurostimulators, and implantables). Such equipment includes, without limitation, all medical devices identified by the U.S. Food and Drug Administration as Class III devices and equivalent classifications outside the U.S.

TI may expressly designate certain products as completing a particular qualification (e.g., Q100, Military Grade, or Enhanced Product). Designers agree that it has the necessary expertise to select the product with the appropriate qualification designation for their applications and that proper product selection is at Designers' own risk. Designers are solely responsible for compliance with all legal and regulatory requirements in connection with such selection.

Designer will fully indemnify TI and its representatives against any damages, costs, losses, and/or liabilities arising out of Designer's noncompliance with the terms and provisions of this Notice.

> Mailing Address: Texas Instruments, Post Office Box 655303, Dallas, Texas 75265 Copyright © 2017, Texas Instruments Incorporated
