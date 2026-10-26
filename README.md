# Keychain
Creating a keychain PCB badge

<img width="1920" height="1080" alt="project banner" src="https://github.com/user-attachments/assets/06839e6f-121c-4707-a285-967971cb2c6f" />

## Purpose

This is a personalized PCB that aims to be carried around on a keychain, a fun PCB badge similar to the ones at opensauce. I hope this could be an interesting way to introduce myself in an interactive manner if I'm at any tech conferences or the like.

## Usage and Info

Uses either a CR2032 or USB-C to power a CH32V003 MCU, toggled between using a 2 way switch.

a LIS331HH communicates to the board to activate the LED's based on the motion associated.

Programmable input is available through the headers.

The back silkscreen plugs my [github account](https://github.com/antelliJ) through a link and a QR code

The front silkscreens include some random things I thought would be interesting, like a ruler and fun hints to get people interested in what the board can actually do


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
| Designator                      | Footprint                            | Quantity | Value                         | JLCPCB Part #（optional） | MPN                                        |
| ------------------------------- | ------------------------------------ | -------- | ----------------------------- | ----------------------- | ------------------------------------------ |
| BT1                             | BatteryHolder_Keystone_1058_1x2032   | 1        | Battery_Cell                  |                         |                                            |
| BZ1                             | Buzzer_12x9.5RM7.6                   | 1        | Piezo buzzer (passive)        | C76871                  | PS1240P02BT                                |
| C1, C3                          | 0805                                 | 2        | 100nF                         | C49678                  | CC0805KRX7R9BB104                          |
| C2, C4                          | 0805                                 | 2        | 10uF                          | C15850                  | CL21A106KAYNNNE                            |
| D1, D10, D3, D4, D5, D6, D8, D9 | 0805                                 | 8        | Red LED                       | C84256                  | NCD0805R1                                  |
| D2                              | LED_RGB_1210                         | 1        | LED_RABG                      | C375572                 | E6C1209RGBC3UDA                            |
| J1                              | PinHeader_1x04_P2.54mm_Vertical      | 1        | Conn_01x04_Pin                | C52016392               | HX PH254-01-04-Z-L11.5 straight pin header |
| J2                              | USB_C_Receptacle_GCT_USB4085         | 1        | USB_C_Receptacle_PowerOnly_6P | C668623                 | TYPE-C 6P(073)                             |
| R1, R2, R3, R4                  | 0805                                 | 4        | 100                           | C17408                  | 0805W8F1000T5E                             |
| R10, R11                        | 0805                                 | 2        | 5k1                           | C27834                  | 0805W8F5101T5E                             |
| R12, R8, R9                     | 0805                                 | 3        | 4k7                           | C17673                  | 0805W8F4701T5E                             |
|                                 |                                      |          |                               |                         |                                            |
| R7                              | 0805                                 | 1        | 330 (RK led)                  | C17437                  | 0805W8F1200T5E                             |
| SW1                             | SW-SMD_MST-12D18G4-SPDT-SLIDE-SWITCH | 1        | MST-12D18G4 SPDT SLIDE SWITCH | C49023767               | MST-12D18G4 SPDT Slide Switch              |
| U1                              | TO-252-3_TabPin2                     | 1        | AMS1117CD-3.3                 | C6186                   | AMS1117-3.3                                |
| U2                              | LGA-16_3x3mm_P0.5mm_LayoutBorder3x5y | 1        | LIS3DH                        | C15134                  | LIS3DHTR                                   |
| U4                              | TSSOP-20_4.4x6.5mm_P0.65mm           | 1        | CH32V003FxPx                  | C5187096                | CH32V003F4P6                               |

** You may notice that r5 and r6 are missing, I included them in the schematic for the blue and green LEDs in the center RGB LED, but I don't think there is enough power for it to make it worth it? If anything it would just reduce the brightness from whatever it already is. Those pads should just be wired together if using the gerber files as is.



## References
A lot of things were picked up on the way of creating this priject, with it being my first proper PCB

used [Table to Markdown](https://tabletomarkdown.com/convert-spreadsheet-to-markdown/) to make the above BOM in the readme