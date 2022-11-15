EESchema Schematic File Version 4
LIBS:DrumMachineControlBoard-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 18
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 10250 700  550  300 
U 6303B621
F0 "LED Drivers" 50
F1 "LED Drivers.sch" 50
$EndSheet
$Sheet
S 10250 1250 550  300 
U 630732CB
F0 "rotaryEncoders" 50
F1 "rotaryEncoders.sch" 50
$EndSheet
$Sheet
S 10250 1800 550  300 
U 63087759
F0 "ButtonInput" 50
F1 "ButtonInput.sch" 50
$EndSheet
$Sheet
S 10250 2350 550  300 
U 63273844
F0 "AnalogIn" 50
F1 "AnalogIn.sch" 50
$EndSheet
$Sheet
S 10250 2900 550  300 
U 632E70C0
F0 "OutputMixer" 50
F1 "OutputMixer.sch" 50
$EndSheet
$Sheet
S 10250 3450 550  300 
U 63354E9E
F0 "TrigOuts" 50
F1 "TrigOuts.sch" 50
$EndSheet
$Sheet
S 10250 4000 550  300 
U 633A1785
F0 "ExternalTrigger" 50
F1 "ExternalTrigger.sch" 50
$EndSheet
NoConn ~ 13100 -2400
$Sheet
S 10250 4550 550  300 
U 63378239
F0 "GlitchVoice" 50
F1 "GlitchVoice.sch" 50
$EndSheet
$Sheet
S 10250 5100 550  300 
U 63557541
F0 "MIDI" 50
F1 "MIDI.sch" 50
$EndSheet
$Sheet
S 10250 5650 550  300 
U 6310CF2F
F0 "ExternalPots" 50
F1 "ExternalPots.sch" 50
$EndSheet
$Sheet
S 10250 6150 550  300 
U 632A94C5
F0 "LCD" 50
F1 "LCD.sch" 50
$EndSheet
$Comp
L power:Earth #PWR0105
U 1 1 6313BD75
P 1850 1050
F 0 "#PWR0105" H 1850 800 50  0001 C CNN
F 1 "Earth" H 1850 900 50  0001 C CNN
F 2 "" H 1850 1050 50  0001 C CNN
F 3 "~" H 1850 1050 50  0001 C CNN
	1    1850 1050
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0107
U 1 1 6313CFC7
P 2950 4500
F 0 "#PWR0107" H 2950 4250 50  0001 C CNN
F 1 "Earth" H 2950 4350 50  0001 C CNN
F 2 "" H 2950 4500 50  0001 C CNN
F 3 "~" H 2950 4500 50  0001 C CNN
	1    2950 4500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0115
U 1 1 6313D7D7
P 4050 1050
F 0 "#PWR0115" H 4050 900 50  0001 C CNN
F 1 "+5V" V 4065 1178 50  0000 L CNN
F 2 "" H 4050 1050 50  0001 C CNN
F 3 "" H 4050 1050 50  0001 C CNN
	1    4050 1050
	0    1    1    0   
$EndComp
Text GLabel 4050 1550 2    50   BiDi ~ 0
AUD_BCLK
Text GLabel 4050 1650 2    50   BiDi ~ 0
AUD_LRCLK
Text GLabel 4050 1350 2    50   BiDi ~ 0
AUD_MCLK
Text GLabel 1850 1850 0    50   BiDi ~ 0
T_TO_A
Text GLabel 1850 1950 0    50   BiDi ~ 0
A_TO_T
Text GLabel 1850 1750 0    50   BiDi ~ 0
MEM_CS
Text GLabel 1850 2250 0    50   BiDi ~ 0
MEM_MOSI
Text GLabel 4050 2350 2    50   BiDi ~ 0
MEM_SCK
Text GLabel 1850 2150 0    50   BiDi ~ 0
LCD_CS
Text GLabel 950  2750 0    50   BiDi ~ 0
LCD_MOSI
Text GLabel 950  2850 0    50   BiDi ~ 0
LCD_SCK
Text GLabel 1850 3350 0    50   BiDi ~ 0
LED_LATCH
Text GLabel 1850 3150 0    50   BiDi ~ 0
LED_SERIAL
Text GLabel 1850 3250 0    50   BiDi ~ 0
LED_CLK
Text GLabel 1850 2950 0    50   BiDi ~ 0
DataEncA
Text GLabel 1850 3050 0    50   BiDi ~ 0
DataEncB
Text GLabel 4050 3150 2    50   BiDi ~ 0
TempoEncA
Text GLabel 4050 3250 2    50   BiDi ~ 0
TempoEncB
Text GLabel 4050 2150 2    50   BiDi ~ 0
MUX_A
Text GLabel 4050 2050 2    50   BiDi ~ 0
MUX_B
Text GLabel 4050 1950 2    50   BiDi ~ 0
MUX_C
Text GLabel 4050 1850 2    50   BiDi ~ 0
AUD_SDA
Text GLabel 4050 1750 2    50   BiDi ~ 0
AUD_SCL
Text GLabel 4050 2750 2    50   BiDi ~ 0
MUX1_DAT
Text GLabel 4050 2850 2    50   BiDi ~ 0
MUX2_DAT
Text GLabel 4050 3350 2    50   BiDi ~ 0
MUX3_DAT
Text GLabel 4050 2650 2    50   BiDi ~ 0
MUX4_DAT
Text GLabel 4050 2550 2    50   BiDi ~ 0
MUX5_DAT
Text GLabel 4050 2250 2    50   BiDi ~ 0
MUX0_DAT
Text GLabel 1850 1350 0    50   BiDi ~ 0
KICK_PWM
Text GLabel 1850 1450 0    50   BiDi ~ 0
SNARE_PWM
Text GLabel 1850 1550 0    50   BiDi ~ 0
CYN1_PWM
Text GLabel 1850 1650 0    50   BiDi ~ 0
CYN2_PWM
Text GLabel 1850 2050 0    50   BiDi ~ 0
GLITCH_PWM
Text GLabel 1850 1250 0    50   BiDi ~ 0
MIDI_OUT
Text GLabel 1850 1150 0    50   BiDi ~ 0
MIDI_IN
Text GLabel 4050 2950 2    50   BiDi ~ 0
FILTER_PWM
Text GLabel 4050 1450 2    50   BiDi ~ 0
MUX6_DAT
NoConn ~ 4050 3600
NoConn ~ 4050 3700
NoConn ~ 4050 3800
NoConn ~ 4050 3900
NoConn ~ 4050 4000
NoConn ~ 4050 4100
NoConn ~ 2650 4500
NoConn ~ 3100 4500
NoConn ~ 3250 4500
NoConn ~ 1850 4200
NoConn ~ 1850 4100
NoConn ~ 1850 4000
NoConn ~ 1850 3900
NoConn ~ 1850 3800
NoConn ~ 1850 3650
NoConn ~ 1850 3550
NoConn ~ 1850 2450
NoConn ~ 4050 2450
NoConn ~ 4050 1150
NoConn ~ 4050 900 
$Comp
L power:+3.3V #PWR05
U 1 1 63247B32
P 2800 4500
F 0 "#PWR05" H 2800 4350 50  0001 C CNN
F 1 "+3.3V" H 2815 4673 50  0000 C CNN
F 2 "" H 2800 4500 50  0001 C CNN
F 3 "" H 2800 4500 50  0001 C CNN
	1    2800 4500
	-1   0    0    1   
$EndComp
Text GLabel 1850 2550 0    50   BiDi ~ 0
LCD_RST
Text GLabel 1850 2650 0    50   BiDi ~ 0
LCD_DC
Text GLabel 1850 2350 0    50   BiDi ~ 0
MEM_MISO
$Comp
L power:Earth #PWR0221
U 1 1 63208D90
P 2350 5100
F 0 "#PWR0221" H 2350 4850 50  0001 C CNN
F 1 "Earth" H 2350 4950 50  0001 C CNN
F 2 "" H 2350 5100 50  0001 C CNN
F 3 "~" H 2350 5100 50  0001 C CNN
	1    2350 5100
	0    1    1    0   
$EndComp
NoConn ~ 3450 5500
Text GLabel 2300 5800 0    50   BiDi ~ 0
MEM_CS
Text GLabel 2300 6300 0    50   BiDi ~ 0
MEM_MOSI
Text GLabel 2300 6400 0    50   BiDi ~ 0
MEM_MISO
Text GLabel 3600 6400 2    50   BiDi ~ 0
MEM_SCK
Text GLabel 2300 5900 0    50   BiDi ~ 0
T_TO_A
Text GLabel 2300 6000 0    50   BiDi ~ 0
A_TO_T
NoConn ~ 2450 6100
NoConn ~ 2450 6200
NoConn ~ 2450 5700
NoConn ~ 2450 5600
NoConn ~ 2450 5500
NoConn ~ 2450 5400
NoConn ~ 2450 5300
NoConn ~ 2450 5200
NoConn ~ 3450 6000
NoConn ~ 3450 6100
NoConn ~ 3450 6200
NoConn ~ 3450 6300
NoConn ~ 2450 6800
NoConn ~ 2450 6950
NoConn ~ 2450 7100
NoConn ~ 3450 7000
NoConn ~ 3450 7100
NoConn ~ 3450 7200
NoConn ~ 3450 7500
NoConn ~ 3450 7300
Text GLabel 5100 7200 2    50   BiDi ~ 0
D_Aud_R
Text GLabel 5100 7400 2    50   BiDi ~ 0
D_Aud_L
NoConn ~ 3100 4850
NoConn ~ 2900 4850
$Comp
L teensy:Teensy4.1 U5
U 1 1 630E849F
P 2950 3200
F 0 "U5" H 2950 5765 50  0000 C CNN
F 1 "Teensy4.1" H 2950 5674 50  0000 C CNN
F 2 "teensy pretty:Teensy41" H 2550 3600 50  0001 C CNN
F 3 "" H 2550 3600 50  0001 C CNN
	1    2950 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR025
U 1 1 632B6240
P 4050 1250
F 0 "#PWR025" H 4050 1100 50  0001 C CNN
F 1 "+3.3V" V 4065 1378 50  0000 L CNN
F 2 "" H 4050 1250 50  0001 C CNN
F 3 "" H 4050 1250 50  0001 C CNN
	1    4050 1250
	0    1    1    0   
$EndComp
$Sheet
S 9400 2900 550  300 
U 6341C53F
F0 "Noise" 50
F1 "Noise.sch" 50
$EndSheet
Text GLabel 4050 3050 2    50   BiDi ~ 0
CLOCK_IN
$Comp
L Connector:Conn_01x01_Female J?
U 1 1 636D367B
P 1650 2750
AR Path="/6303B621/636D367B" Ref="J?"  Part="1" 
AR Path="/636D367B" Ref="J46"  Part="1" 
F 0 "J46" H 1678 2776 50  0000 L CNN
F 1 "Clock_Out" H 1800 2750 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1650 2750 50  0001 C CNN
F 3 "~" H 1650 2750 50  0001 C CNN
	1    1650 2750
	-1   0    0    1   
$EndComp
NoConn ~ 950  2750
NoConn ~ 950  2850
$Sheet
S 9400 3450 550  300 
U 6370FEA3
F0 "power_conns" 50
F1 "power_conns.sch" 50
$EndSheet
$Sheet
S 9400 3950 550  350 
U 6346700D
F0 "SpeakerAmp" 50
F1 "SpeakerAmp.sch" 50
$EndSheet
$Sheet
S 9400 2350 550  300 
U 630FA783
F0 "PWM Out" 50
F1 "PWM Out.sch" 50
$EndSheet
$Comp
L Connector:Conn_01x01_Female J28
U 1 1 635C6C6F
P 4900 7400
F 0 "J28" H 4928 7426 50  0000 L CNN
F 1 "Teensy_Audio_OUT_L" H 4928 7335 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 4900 7400 50  0001 C CNN
F 3 "~" H 4900 7400 50  0001 C CNN
	1    4900 7400
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J23
U 1 1 635C6FCF
P 4900 7200
F 0 "J23" H 4928 7226 50  0000 L CNN
F 1 "Teensy_Audio_OUT_R" H 4928 7135 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 4900 7200 50  0001 C CNN
F 3 "~" H 4900 7200 50  0001 C CNN
	1    4900 7200
	-1   0    0    1   
$EndComp
NoConn ~ 3450 6700
NoConn ~ 3450 6800
NoConn ~ 3450 6900
NoConn ~ 3450 7400
NoConn ~ 2450 5800
NoConn ~ 2300 5800
NoConn ~ 2300 5900
NoConn ~ 2300 6000
NoConn ~ 2300 6300
NoConn ~ 2300 6400
NoConn ~ 2450 6400
NoConn ~ 2450 6300
NoConn ~ 2450 6000
NoConn ~ 2450 5900
NoConn ~ 2450 5100
NoConn ~ 2350 5100
$Comp
L power:+5V #PWR024
U 1 1 632B3794
P 3600 5100
F 0 "#PWR024" H 3600 4950 50  0001 C CNN
F 1 "+5V" V 3615 5228 50  0000 L CNN
F 2 "" H 3600 5100 50  0001 C CNN
F 3 "" H 3600 5100 50  0001 C CNN
	1    3600 5100
	0    1    1    0   
$EndComp
Text GLabel 3600 5900 2    50   BiDi ~ 0
AUD_SDA
Text GLabel 3600 5800 2    50   BiDi ~ 0
AUD_SCL
Text GLabel 3600 5700 2    50   BiDi ~ 0
AUD_LRCLK
Text GLabel 3600 5600 2    50   BiDi ~ 0
AUD_BCLK
Text GLabel 3600 5400 2    50   BiDi ~ 0
AUD_MCLK
$Comp
L power:+3.3V #PWR0222
U 1 1 6320BBAF
P 3600 5300
F 0 "#PWR0222" H 3600 5150 50  0001 C CNN
F 1 "+3.3V" V 3615 5428 50  0000 L CNN
F 2 "" H 3600 5300 50  0001 C CNN
F 3 "" H 3600 5300 50  0001 C CNN
	1    3600 5300
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0220
U 1 1 6320854A
P 3600 5200
F 0 "#PWR0220" H 3600 4950 50  0001 C CNN
F 1 "Earth" H 3600 5050 50  0001 C CNN
F 2 "" H 3600 5200 50  0001 C CNN
F 3 "~" H 3600 5200 50  0001 C CNN
	1    3600 5200
	0    -1   -1   0   
$EndComp
$Comp
L modular_synth:Teensy_Audio_Shield U25
U 1 1 631EAD29
P 3000 6300
F 0 "U25" H 2937 4977 50  0000 C CNN
F 1 "Teensy_Audio_Shield" H 2937 4886 50  0000 C CNN
F 2 "" H 3000 6950 50  0001 C CNN
F 3 "" H 3000 6950 50  0001 C CNN
	1    3000 6300
	1    0    0    -1  
$EndComp
NoConn ~ 3850 5200
NoConn ~ 3450 5100
NoConn ~ 3450 5200
NoConn ~ 3450 5300
NoConn ~ 3450 5400
NoConn ~ 3450 5600
NoConn ~ 3450 5700
NoConn ~ 3450 5800
NoConn ~ 3450 5900
NoConn ~ 3600 5100
NoConn ~ 3600 5200
NoConn ~ 3600 5300
NoConn ~ 3600 5400
NoConn ~ 3600 5600
NoConn ~ 3600 5700
NoConn ~ 3600 5800
NoConn ~ 3600 5900
NoConn ~ 3450 6400
NoConn ~ 3600 6400
$Comp
L Connector:Conn_01x01_Female J54
U 1 1 636C4AD8
P 1650 2850
F 0 "J54" H 2100 2850 50  0000 C CNN
F 1 "Teensy_27" H 1850 2850 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1650 2850 50  0001 C CNN
F 3 "~" H 1650 2850 50  0001 C CNN
	1    1650 2850
	-1   0    0    1   
$EndComp
$Sheet
S 9400 4500 550  350 
U 6372203A
F0 "Decoupling" 50
F1 "Decoupling.sch" 50
$EndSheet
$Sheet
S 9400 5100 550  300 
U 63A851CD
F0 "JackPanel" 50
F1 "JackPanel.sch" 50
$EndSheet
$EndSCHEMATC
