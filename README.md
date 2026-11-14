# Keychain
Creating a keychain PCB badge

<img width="1920" height="1065" alt="project banner v2" src="https://github.com/user-attachments/assets/535a8c2b-b3ab-4d10-8c0b-560cb3a86534" />


## Purpose

This is a personalized PCB that aims to be carried around on a keychain, a fun PCB badge similar to the ones at opensauce. I hope this could be an interesting way to introduce myself in an interactive manner if I'm at any tech conferences or the like.

## Usage and Info

Uses either a CR2032 or USB-C to power a CH32V003 MCU, toggled between using a 2 way switch.

a LIS331HH communicates to the board to activate the LED's based on the motion associated.

Programmable input is available through the headers.

The back silkscreen plugs my [github account](https://github.com/antelliJ) through a link and a QR code

The front silkscreens include some random things I thought would be interesting, like a ruler and fun hints to get people interested in what the board can actually do

[![View PCB on KiCanvas](https://hack.club/pcb-badge)](https://kicanvas.org/?repo=https%3A%2F%2Fgithub.com%2FantelliJ%2FKeychainPCB%2Ftree%2Fmain%2FPCB)

<img width="373" height="244" alt="Screenshot 2026-10-26 170049" src="https://github.com/user-attachments/assets/1095c329-964d-406a-bbc1-da838116114e" />


### File structure
`\PCB\` includes files relevant for the pcb and manufacturing. 
<br>
    `\PCB\production` are the files used for PCB manufacturing

`\Code\` is intended for all the code, which is basically empty at the moment. Eventually it will have the custom firmware.

### Features (mostly planned)
Shake to wake, various taps can cycle through the different animations.
One of which that would show a morse code representation of my name, among other small animations with the leds.

## Bill of Materials
A nicely formatted excel sheet is provided at `\PCB\production\Keychain-Bom.xlsx`
The below is just a static version of that...

| Designator                      | Footprint                            | Quantity | Price         | Value                         | JLCPCB Part #（optional） | MPN                                        | Links                                                                                                                                                              |
| ------------------------------- | ------------------------------------ | -------- | ------------- | ----------------------------- | ----------------------- | ------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| U2                              | LIS3DH breakout Board                | 1        |  $       3.15 | LIS3DH                        |                         | LIS3DHTR                                   | [https://www.aliexpress.com/item/1005010373628490.html](https://www.aliexpress.com/item/1005010373628490.html)                                                     |
| U4                              | TSSOP-20_4.4x6.5mm_P0.65mm           | 1        |  $       1.54 | CH32V003FxPx                  | C5187096                | CH32V003F4P6                               | [CH32V003F4P6 \| Microcontrollers \| WCH \| LCSC](https://www.lcsc.com/product-detail/C5187096.html)                                                               |
| U1                              | TO-252-3_TabPin2                     | 1        |  $       1.02 | AMS1117CD-3.3                 | C6186                   | AMS1117-3.3                                | [AMS1117-3.3 \| Voltage Regulators - Linear, Low Drop Out (LDO) Regulators \| Advanced Monolithic Systems \| LCSC](https://www.lcsc.com/product-detail/C6186.html) |
| D2                              | LED_RGB_1210                         | 1        |  $       0.68 | LED_RABG                      | C375572                 | E6C1209RGBC3UDA                            | [https://www.lcsc.com/product-detail/C375572.html](https://www.lcsc.com/product-detail/C375572.html)                                                               |
| R7                              | 0805                                 | 1        |  $       0.66 | 330 (RK led)                  | C17437                  | 0805W8F1200T5E                             | [https://www.lcsc.com/product-detail/C17437.html](https://www.lcsc.com/product-detail/C17437.html)                                                                 |
| C2, C4                          | 0805                                 | 2        |  $       0.63 | 10uF                          | C15850                  | CL21A106KAYNNNE                            | [https://www.lcsc.com/product-detail/C15850.html](https://www.lcsc.com/product-detail/C15850.html)                                                                 |
| J1                              | PinHeader_1x04_P2.54mm_Vertical      | 1        |  $       0.62 | Conn_01x04_Pin                | C52016392               | HX PH254-01-04-Z-L11.5 straight pin header | [https://www.lcsc.com/product-detail/C52016392.html](https://www.lcsc.com/product-detail/C52016392.html)                                                           |
| D1, D10, D3, D4, D5, D6, D8, D9 | 0805                                 | 8        |  $       0.62 | Red LED                       | C84256                  | NCD0805R1                                  | [https://www.lcsc.com/product-detail/C84256.html](https://www.lcsc.com/product-detail/C84256.html)                                                                 |
| R10, R11                        | 0805                                 | 2        |  $       0.55 | 5k1                           | C27834                  | 0805W8F5101T5E                             | [0805W8F5101T5E \| Chip Resistor - Surface Mount \| UNI-ROYAL \| LCSC](https://www.lcsc.com/product-detail/C27834.html)                                            |
| R1, R2, R3, R4                  | 0805                                 | 4        |  $       0.43 | 100                           | C17408                  | 0805W8F1000T5E                             | [0805W8F1000T5E \| Chip Resistor - Surface Mount \| UNI-ROYAL \| LCSC](https://www.lcsc.com/product-detail/C17408.html)                                            |
| SW1                             | SW-SMD_MST-12D18G4-SPDT-SLIDE-SWITCH | 1        |  $       0.40 | MST-12D18G4 SPDT SLIDE SWITCH | C49023767               | MST-12D18G4 SPDT Slide Switch              | [MST-12D18G4 SPDT Slide Switch \| Slide Switches \| SHOU HAN \| LCSC](https://www.lcsc.com/product-detail/C49023767.html)                                          |
| J2                              | USB_C_Receptacle_GCT_USB4085         | 1        |  $       0.38 | USB_C_Receptacle_PowerOnly_6P | C668623                 | TYPE-C 6P(073)                             | [https://www.lcsc.com/product-detail/C668623.html](https://www.lcsc.com/product-detail/C668623.html)                                                               |
| R12, R8, R9                     | 0805                                 | 3        |  $       0.30 | 4k7                           | C17673                  | 0805W8F4701T5E                             | [0805W8F4701T5E \| Chip Resistor - Surface Mount \| UNI-ROYAL \| LCSC](https://www.lcsc.com/product-detail/C17673.html)                                            |
| BT1                             | BatteryHolder_Keystone_1058_1x2032   | 1        |  $       0.30 | Battery_Cell                  | C5239862                | BS-02-A1AJ010                              | [https://www.lcsc.com/product-detail/C5239862.html](https://www.lcsc.com/product-detail/C5239862.html)                                                             |
| C1, C3                          | 0805                                 | 2        |  $       0.28 | 100nF                         | C49678                  | CC0805KRX7R9BB104                          | [https://www.lcsc.com/product-detail/C49678.html](https://www.lcsc.com/product-detail/C49678.html)                                                                 |
| BZ1                             | Buzzer_12x9.5RM7.6                   | 1        |  $       0.19 | Piezo buzzer (passive)        | C76871                  | PS1240P02BT                                | [https://www.lcsc.com/product-detail/C76871.html](https://www.lcsc.com/product-detail/C76871.html)                                                                 |
| Total for Components |  $11.75 | | | | | | |


** You may notice that r5 and r6 are missing, I included them in the schematic for the blue and green LEDs in the center RGB LED, but I don't think there is enough power for it to make it worth it? If anything it would just reduce the brightness from whatever it already is. Those pads should just be wired together if using the gerber files as is.


<img width="445" height="260" alt="Screenshot 2026-10-26 150503" src="https://github.com/user-attachments/assets/64c53be0-da23-482e-ad9f-b652866a296f" />



## References
A lot of things were picked up on the way of creating this project, with it being my first proper PCB

used [Spreadsheet to Markdown](https://tabletomarkdown.com/convert-spreadsheet-to-markdown/) to make the above BOM in the readme
