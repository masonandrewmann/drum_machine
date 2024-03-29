EESchema Schematic File Version 4
LIBS:DrumMachineControlBoard-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 18
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74HC595 U?
U 1 1 631C92FD
P 1950 2300
AR Path="/6303B621/631C92FD" Ref="U?"  Part="1" 
AR Path="/63354E9E/631C92FD" Ref="U18"  Part="1" 
F 0 "U18" H 2150 2950 50  0000 C CNN
F 1 "74HC595" H 2200 2850 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 1950 2300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 1950 2300 50  0001 C CNN
	1    1950 2300
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 631C9348
P 1950 3000
AR Path="/6303B621/631C9348" Ref="#PWR?"  Part="1" 
AR Path="/63354E9E/631C9348" Ref="#PWR0379"  Part="1" 
F 0 "#PWR0379" H 1950 2750 50  0001 C CNN
F 1 "Earth" H 1950 2850 50  0001 C CNN
F 2 "" H 1950 3000 50  0001 C CNN
F 3 "~" H 1950 3000 50  0001 C CNN
	1    1950 3000
	1    0    0    -1  
$EndComp
Text GLabel 1550 2100 0    50   BiDi ~ 0
LED_CLK
$Comp
L power:Earth #PWR?
U 1 1 631C934F
P 1500 2550
AR Path="/6303B621/631C934F" Ref="#PWR?"  Part="1" 
AR Path="/63354E9E/631C934F" Ref="#PWR0380"  Part="1" 
F 0 "#PWR0380" H 1500 2300 50  0001 C CNN
F 1 "Earth" H 1500 2400 50  0001 C CNN
F 2 "" H 1500 2550 50  0001 C CNN
F 3 "~" H 1500 2550 50  0001 C CNN
	1    1500 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 2550 1500 2500
Wire Wire Line
	1500 2500 1550 2500
Wire Wire Line
	1500 2200 1550 2200
Text GLabel 1550 2400 0    50   BiDi ~ 0
LED_LATCH
Wire Wire Line
	1500 1900 1550 1900
Text GLabel 1500 1900 0    50   BiDi ~ 0
LED_SR_OUT
$Comp
L power:+5V #PWR0195
U 1 1 631A9F5A
P 1950 1700
F 0 "#PWR0195" H 1950 1550 50  0001 C CNN
F 1 "+5V" H 1965 1873 50  0000 C CNN
F 2 "" H 1950 1700 50  0001 C CNN
F 3 "" H 1950 1700 50  0001 C CNN
	1    1950 1700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0210
U 1 1 631FFF0F
P 1500 2200
F 0 "#PWR0210" H 1500 2050 50  0001 C CNN
F 1 "+5V" V 1515 2328 50  0000 L CNN
F 2 "" H 1500 2200 50  0001 C CNN
F 3 "" H 1500 2200 50  0001 C CNN
	1    1500 2200
	0    -1   -1   0   
$EndComp
Text Notes 7400 1000 0    50   ~ 0
IS THE LED WRITE/FILL A BLOCKING FUNCCTION\nI DO HAVE 5 SRs in series, could take a sec to fill up
Text Notes 7500 1200 0    50   ~ 0
THO IT DOESNT HAPPEN VERY OFTEN SO MAYBE
Text Notes 7500 1300 0    50   ~ 0
ITS NOT TOO BAD?\n
$Comp
L modular_synth:AudioJack_Switched_Mono J133
U 1 1 632D1D29
P 5600 1250
F 0 "J133" H 5700 1500 50  0000 L CNN
F 1 "BD_TRIG_OUT" H 5700 1400 50  0000 L CNN
F 2 "mason_parts:PJ301-BM" H 5600 1250 50  0001 C CNN
F 3 "~" H 5600 1250 50  0001 C CNN
	1    5600 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 1100 5400 1050
$Comp
L modular_synth:AudioJack_Switched_Mono J134
U 1 1 632D275C
P 4050 3300
F 0 "J134" H 4150 3550 50  0000 L CNN
F 1 "SN_TRIG_OUT" H 4150 3450 50  0000 L CNN
F 2 "mason_parts:PJ301-BM" H 4050 3300 50  0001 C CNN
F 3 "~" H 4050 3300 50  0001 C CNN
	1    4050 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3150 3850 3100
$Comp
L modular_synth:AudioJack_Switched_Mono J135
U 1 1 632D318F
P 7000 2800
F 0 "J135" H 7100 3050 50  0000 L CNN
F 1 "CYN1_TRIG_OUT" H 7100 2950 50  0000 L CNN
F 2 "mason_parts:PJ301-BM" H 7000 2800 50  0001 C CNN
F 3 "~" H 7000 2800 50  0001 C CNN
	1    7000 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2650 6800 2600
$Comp
L modular_synth:AudioJack_Switched_Mono J136
U 1 1 632D3A56
P 7000 3850
F 0 "J136" H 7100 4100 50  0000 L CNN
F 1 "CYN2_TRIG_OUT" H 7100 4000 50  0000 L CNN
F 2 "mason_parts:PJ301-BM" H 7000 3850 50  0001 C CNN
F 3 "~" H 7000 3850 50  0001 C CNN
	1    7000 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 3700 6800 3650
Wire Wire Line
	4000 5200 4000 5100
$Comp
L modular_synth:AudioJack_Switched_Mono J138
U 1 1 632D4E25
P 6550 6500
F 0 "J138" H 6650 6750 50  0000 L CNN
F 1 "DIGI1_TRIG_OUT" H 6650 6650 50  0000 L CNN
F 2 "mason_parts:PJ301-BM" H 6550 6500 50  0001 C CNN
F 3 "~" H 6550 6500 50  0001 C CNN
	1    6550 6500
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J139
U 1 1 632D5138
P 6500 5450
F 0 "J139" H 6600 5700 50  0000 L CNN
F 1 "DIGI2_TRIG_OUT" H 6600 5600 50  0000 L CNN
F 2 "mason_parts:PJ301-BM" H 6500 5450 50  0001 C CNN
F 3 "~" H 6500 5450 50  0001 C CNN
	1    6500 5450
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J140
U 1 1 632D556F
P 4050 6450
F 0 "J140" H 4150 6700 50  0000 L CNN
F 1 "DIGI3_TRIG_OUT" H 4150 6600 50  0000 L CNN
F 2 "mason_parts:PJ301-BM" H 4050 6450 50  0001 C CNN
F 3 "~" H 4050 6450 50  0001 C CNN
	1    4050 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 6350 6350 6300
Wire Wire Line
	6300 5300 6300 5250
Wire Wire Line
	3850 6300 3850 6250
$Comp
L modular_synth:AudioJack_Switched_Mono J137
U 1 1 632DF2B1
P 4200 5350
F 0 "J137" H 4300 5600 50  0000 L CNN
F 1 "GLITCH_TRIG_OUT" H 4300 5500 50  0000 L CNN
F 2 "mason_parts:PJ301-BM" H 4200 5350 50  0001 C CNN
F 3 "~" H 4200 5350 50  0001 C CNN
	1    4200 5350
	1    0    0    -1  
$EndComp
Text GLabel 4100 5400 2    50   BiDi ~ 0
GLITCH_GATE
$Comp
L power:Earth #PWR033
U 1 1 635C3CDE
P 5650 1200
F 0 "#PWR033" H 5650 950 50  0001 C CNN
F 1 "Earth" H 5650 1050 50  0001 C CNN
F 2 "" H 5650 1200 50  0001 C CNN
F 3 "~" H 5650 1200 50  0001 C CNN
	1    5650 1200
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR034
U 1 1 635C5B04
P 4100 3250
F 0 "#PWR034" H 4100 3000 50  0001 C CNN
F 1 "Earth" H 4100 3100 50  0001 C CNN
F 2 "" H 4100 3250 50  0001 C CNN
F 3 "~" H 4100 3250 50  0001 C CNN
	1    4100 3250
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR035
U 1 1 635C6ADA
P 7050 2750
F 0 "#PWR035" H 7050 2500 50  0001 C CNN
F 1 "Earth" H 7050 2600 50  0001 C CNN
F 2 "" H 7050 2750 50  0001 C CNN
F 3 "~" H 7050 2750 50  0001 C CNN
	1    7050 2750
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR036
U 1 1 635C807D
P 7050 3800
F 0 "#PWR036" H 7050 3550 50  0001 C CNN
F 1 "Earth" H 7050 3650 50  0001 C CNN
F 2 "" H 7050 3800 50  0001 C CNN
F 3 "~" H 7050 3800 50  0001 C CNN
	1    7050 3800
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR038
U 1 1 635C971A
P 6600 6450
F 0 "#PWR038" H 6600 6200 50  0001 C CNN
F 1 "Earth" H 6600 6300 50  0001 C CNN
F 2 "" H 6600 6450 50  0001 C CNN
F 3 "~" H 6600 6450 50  0001 C CNN
	1    6600 6450
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR039
U 1 1 635CA9C3
P 6550 5400
F 0 "#PWR039" H 6550 5150 50  0001 C CNN
F 1 "Earth" H 6550 5250 50  0001 C CNN
F 2 "" H 6550 5400 50  0001 C CNN
F 3 "~" H 6550 5400 50  0001 C CNN
	1    6550 5400
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR040
U 1 1 635CB573
P 4100 6400
F 0 "#PWR040" H 4100 6150 50  0001 C CNN
F 1 "Earth" H 4100 6250 50  0001 C CNN
F 2 "" H 4100 6400 50  0001 C CNN
F 3 "~" H 4100 6400 50  0001 C CNN
	1    4100 6400
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR037
U 1 1 635CD2C5
P 4250 5300
F 0 "#PWR037" H 4250 5050 50  0001 C CNN
F 1 "Earth" H 4250 5150 50  0001 C CNN
F 2 "" H 4250 5300 50  0001 C CNN
F 3 "~" H 4250 5300 50  0001 C CNN
	1    4250 5300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 5400 4000 5400
Wire Wire Line
	4000 5400 4000 5200
Connection ~ 4000 5200
$Comp
L Transistor_FET:2N7000 Q15
U 1 1 632D0195
P 4900 1250
F 0 "Q15" H 5106 1296 50  0000 L CNN
F 1 "2N7000" H 5106 1205 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 5100 1175 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 4900 1250 50  0001 L CNN
	1    4900 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R110
U 1 1 632D28A2
P 5000 900
F 0 "R110" H 5068 946 50  0000 L CNN
F 1 "2k2" H 5068 855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5040 890 50  0001 C CNN
F 3 "~" H 5000 900 50  0001 C CNN
	1    5000 900 
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R104
U 1 1 632D411B
P 4550 1250
F 0 "R104" V 4345 1250 50  0000 C CNN
F 1 "470" V 4436 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4590 1240 50  0001 C CNN
F 3 "~" H 4550 1250 50  0001 C CNN
	1    4550 1250
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0223
U 1 1 632E0B7A
P 5000 1450
F 0 "#PWR0223" H 5000 1200 50  0001 C CNN
F 1 "Earth" H 5000 1300 50  0001 C CNN
F 2 "" H 5000 1450 50  0001 C CNN
F 3 "~" H 5000 1450 50  0001 C CNN
	1    5000 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0224
U 1 1 632E10E2
P 5000 750
F 0 "#PWR0224" H 5000 600 50  0001 C CNN
F 1 "+12V" H 5015 923 50  0000 C CNN
F 2 "" H 5000 750 50  0001 C CNN
F 3 "" H 5000 750 50  0001 C CNN
	1    5000 750 
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q22
U 1 1 632E3F96
P 3450 6450
F 0 "Q22" H 3656 6496 50  0000 L CNN
F 1 "2N7000" H 3656 6405 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 3650 6375 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 3450 6450 50  0001 L CNN
	1    3450 6450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R193
U 1 1 632E3F9C
P 3550 6100
F 0 "R193" H 3618 6146 50  0000 L CNN
F 1 "2k2" H 3618 6055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3590 6090 50  0001 C CNN
F 3 "~" H 3550 6100 50  0001 C CNN
	1    3550 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R191
U 1 1 632E3FA2
P 3100 6450
F 0 "R191" V 2895 6450 50  0000 C CNN
F 1 "470" V 2986 6450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3140 6440 50  0001 C CNN
F 3 "~" H 3100 6450 50  0001 C CNN
	1    3100 6450
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0225
U 1 1 632E3FA8
P 3550 6650
F 0 "#PWR0225" H 3550 6400 50  0001 C CNN
F 1 "Earth" H 3550 6500 50  0001 C CNN
F 2 "" H 3550 6650 50  0001 C CNN
F 3 "~" H 3550 6650 50  0001 C CNN
	1    3550 6650
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0244
U 1 1 632E3FAE
P 3550 5950
F 0 "#PWR0244" H 3550 5800 50  0001 C CNN
F 1 "+12V" H 3565 6123 50  0000 C CNN
F 2 "" H 3550 5950 50  0001 C CNN
F 3 "" H 3550 5950 50  0001 C CNN
	1    3550 5950
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q16
U 1 1 632F221A
P 3350 3300
F 0 "Q16" H 3556 3346 50  0000 L CNN
F 1 "2N7000" H 3556 3255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 3550 3225 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 3350 3300 50  0001 L CNN
	1    3350 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R111
U 1 1 632F2220
P 3450 2950
F 0 "R111" H 3518 2996 50  0000 L CNN
F 1 "2k2" H 3518 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3490 2940 50  0001 C CNN
F 3 "~" H 3450 2950 50  0001 C CNN
	1    3450 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R105
U 1 1 632F2226
P 3000 3300
F 0 "R105" V 2795 3300 50  0000 C CNN
F 1 "470" V 2886 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3040 3290 50  0001 C CNN
F 3 "~" H 3000 3300 50  0001 C CNN
	1    3000 3300
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0245
U 1 1 632F222C
P 3450 3500
F 0 "#PWR0245" H 3450 3250 50  0001 C CNN
F 1 "Earth" H 3450 3350 50  0001 C CNN
F 2 "" H 3450 3500 50  0001 C CNN
F 3 "~" H 3450 3500 50  0001 C CNN
	1    3450 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0265
U 1 1 632F2232
P 3450 2800
F 0 "#PWR0265" H 3450 2650 50  0001 C CNN
F 1 "+12V" H 3465 2973 50  0000 C CNN
F 2 "" H 3450 2800 50  0001 C CNN
F 3 "" H 3450 2800 50  0001 C CNN
	1    3450 2800
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q17
U 1 1 632F4B97
P 6400 2800
F 0 "Q17" H 6606 2846 50  0000 L CNN
F 1 "2N7000" H 6606 2755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6600 2725 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 6400 2800 50  0001 L CNN
	1    6400 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R175
U 1 1 632F4B9D
P 6500 2450
F 0 "R175" H 6568 2496 50  0000 L CNN
F 1 "2k2" H 6568 2405 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6540 2440 50  0001 C CNN
F 3 "~" H 6500 2450 50  0001 C CNN
	1    6500 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R106
U 1 1 632F4BA3
P 6050 2800
F 0 "R106" V 5845 2800 50  0000 C CNN
F 1 "470" V 5936 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6090 2790 50  0001 C CNN
F 3 "~" H 6050 2800 50  0001 C CNN
	1    6050 2800
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0267
U 1 1 632F4BA9
P 6500 3000
F 0 "#PWR0267" H 6500 2750 50  0001 C CNN
F 1 "Earth" H 6500 2850 50  0001 C CNN
F 2 "" H 6500 3000 50  0001 C CNN
F 3 "~" H 6500 3000 50  0001 C CNN
	1    6500 3000
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0269
U 1 1 632F4BAF
P 6500 2300
F 0 "#PWR0269" H 6500 2150 50  0001 C CNN
F 1 "+12V" H 6515 2473 50  0000 C CNN
F 2 "" H 6500 2300 50  0001 C CNN
F 3 "" H 6500 2300 50  0001 C CNN
	1    6500 2300
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q18
U 1 1 632F7780
P 6400 3850
F 0 "Q18" H 6606 3896 50  0000 L CNN
F 1 "2N7000" H 6606 3805 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6600 3775 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 6400 3850 50  0001 L CNN
	1    6400 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R176
U 1 1 632F7786
P 6500 3500
F 0 "R176" H 6568 3546 50  0000 L CNN
F 1 "2k2" H 6568 3455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6540 3490 50  0001 C CNN
F 3 "~" H 6500 3500 50  0001 C CNN
	1    6500 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R107
U 1 1 632F778C
P 6050 3850
F 0 "R107" V 5845 3850 50  0000 C CNN
F 1 "470" V 5936 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6090 3840 50  0001 C CNN
F 3 "~" H 6050 3850 50  0001 C CNN
	1    6050 3850
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0275
U 1 1 632F7792
P 6500 4050
F 0 "#PWR0275" H 6500 3800 50  0001 C CNN
F 1 "Earth" H 6500 3900 50  0001 C CNN
F 2 "" H 6500 4050 50  0001 C CNN
F 3 "~" H 6500 4050 50  0001 C CNN
	1    6500 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0336
U 1 1 632F7798
P 6500 3350
F 0 "#PWR0336" H 6500 3200 50  0001 C CNN
F 1 "+12V" H 6515 3523 50  0000 C CNN
F 2 "" H 6500 3350 50  0001 C CNN
F 3 "" H 6500 3350 50  0001 C CNN
	1    6500 3350
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q19
U 1 1 63302B6A
P 3450 5400
F 0 "Q19" H 3656 5446 50  0000 L CNN
F 1 "2N7000" H 3656 5355 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 3650 5325 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 3450 5400 50  0001 L CNN
	1    3450 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R188
U 1 1 63302B70
P 3550 5050
F 0 "R188" H 3618 5096 50  0000 L CNN
F 1 "2k2" H 3618 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3590 5040 50  0001 C CNN
F 3 "~" H 3550 5050 50  0001 C CNN
	1    3550 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R108
U 1 1 63302B76
P 3100 5400
F 0 "R108" V 2895 5400 50  0000 C CNN
F 1 "470" V 2986 5400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3140 5390 50  0001 C CNN
F 3 "~" H 3100 5400 50  0001 C CNN
	1    3100 5400
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0337
U 1 1 63302B7C
P 3550 5600
F 0 "#PWR0337" H 3550 5350 50  0001 C CNN
F 1 "Earth" H 3550 5450 50  0001 C CNN
F 2 "" H 3550 5600 50  0001 C CNN
F 3 "~" H 3550 5600 50  0001 C CNN
	1    3550 5600
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0342
U 1 1 63302B82
P 3550 4900
F 0 "#PWR0342" H 3550 4750 50  0001 C CNN
F 1 "+12V" H 3565 5073 50  0000 C CNN
F 2 "" H 3550 4900 50  0001 C CNN
F 3 "" H 3550 4900 50  0001 C CNN
	1    3550 4900
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q20
U 1 1 63304D08
P 5850 6500
F 0 "Q20" H 6056 6546 50  0000 L CNN
F 1 "2N7000" H 6056 6455 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6050 6425 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 5850 6500 50  0001 L CNN
	1    5850 6500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R189
U 1 1 63304D0E
P 5950 6150
F 0 "R189" H 6018 6196 50  0000 L CNN
F 1 "2k2" H 6018 6105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5990 6140 50  0001 C CNN
F 3 "~" H 5950 6150 50  0001 C CNN
	1    5950 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R109
U 1 1 63304D14
P 5500 6500
F 0 "R109" V 5295 6500 50  0000 C CNN
F 1 "470" V 5386 6500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5540 6490 50  0001 C CNN
F 3 "~" H 5500 6500 50  0001 C CNN
	1    5500 6500
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0343
U 1 1 63304D1A
P 5950 6700
F 0 "#PWR0343" H 5950 6450 50  0001 C CNN
F 1 "Earth" H 5950 6550 50  0001 C CNN
F 2 "" H 5950 6700 50  0001 C CNN
F 3 "~" H 5950 6700 50  0001 C CNN
	1    5950 6700
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0346
U 1 1 63304D20
P 5950 6000
F 0 "#PWR0346" H 5950 5850 50  0001 C CNN
F 1 "+12V" H 5965 6173 50  0000 C CNN
F 2 "" H 5950 6000 50  0001 C CNN
F 3 "" H 5950 6000 50  0001 C CNN
	1    5950 6000
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q21
U 1 1 6330AA97
P 5850 5450
F 0 "Q21" H 6056 5496 50  0000 L CNN
F 1 "2N7000" H 6056 5405 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6050 5375 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 5850 5450 50  0001 L CNN
	1    5850 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R192
U 1 1 6330AA9D
P 5950 5100
F 0 "R192" H 6018 5146 50  0000 L CNN
F 1 "2k2" H 6018 5055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5990 5090 50  0001 C CNN
F 3 "~" H 5950 5100 50  0001 C CNN
	1    5950 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R190
U 1 1 6330AAA3
P 5500 5450
F 0 "R190" V 5295 5450 50  0000 C CNN
F 1 "470" V 5386 5450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5540 5440 50  0001 C CNN
F 3 "~" H 5500 5450 50  0001 C CNN
	1    5500 5450
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0356
U 1 1 6330AAA9
P 5950 5650
F 0 "#PWR0356" H 5950 5400 50  0001 C CNN
F 1 "Earth" H 5950 5500 50  0001 C CNN
F 2 "" H 5950 5650 50  0001 C CNN
F 3 "~" H 5950 5650 50  0001 C CNN
	1    5950 5650
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0357
U 1 1 6330AAAF
P 5950 4950
F 0 "#PWR0357" H 5950 4800 50  0001 C CNN
F 1 "+12V" H 5965 5123 50  0000 C CNN
F 2 "" H 5950 4950 50  0001 C CNN
F 3 "" H 5950 4950 50  0001 C CNN
	1    5950 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1900 2900 1900
Wire Wire Line
	2900 1900 2900 1200
Wire Wire Line
	2900 1200 2950 1200
Wire Wire Line
	2350 2000 2900 2000
Wire Wire Line
	2900 2000 2900 2250
Wire Wire Line
	2900 2250 2950 2250
Wire Wire Line
	2350 2100 2850 2100
Wire Wire Line
	2850 2100 2850 3300
Wire Wire Line
	5800 2800 5900 2800
Wire Wire Line
	2350 2200 2800 2200
Wire Wire Line
	2800 2200 2800 4350
Wire Wire Line
	5750 3850 5900 3850
Wire Wire Line
	2350 2300 2750 2300
Wire Wire Line
	2750 2300 2750 5400
Wire Wire Line
	2750 5400 2950 5400
Wire Wire Line
	2350 2400 2700 2400
Wire Wire Line
	2700 2400 2700 6450
Wire Wire Line
	2700 6450 2950 6450
Wire Wire Line
	2350 2500 2650 2500
Wire Wire Line
	2650 2500 2650 6800
Wire Wire Line
	2600 6900 2600 2600
Wire Wire Line
	2600 2600 2350 2600
Wire Wire Line
	5000 1050 5400 1050
Connection ~ 5000 1050
Connection ~ 5400 1050
Wire Wire Line
	5400 1050 5400 1000
Wire Wire Line
	3450 3100 3850 3100
Connection ~ 3450 3100
Connection ~ 3850 3100
Wire Wire Line
	3850 3100 3850 3050
Wire Wire Line
	6500 2600 6800 2600
Connection ~ 6500 2600
Connection ~ 6800 2600
Wire Wire Line
	6800 2600 6800 2550
Wire Wire Line
	6800 3650 6500 3650
Connection ~ 6800 3650
Wire Wire Line
	6800 3650 6800 3600
Connection ~ 6500 3650
Wire Wire Line
	5300 6900 5300 6500
Wire Wire Line
	5300 6500 5350 6500
Wire Wire Line
	2600 6900 5300 6900
Wire Wire Line
	5250 6800 5250 5450
Wire Wire Line
	5250 5450 5350 5450
Wire Wire Line
	2650 6800 5250 6800
Wire Wire Line
	3550 5200 4000 5200
Connection ~ 3550 5200
Wire Wire Line
	6350 6300 5950 6300
Connection ~ 6350 6300
Wire Wire Line
	6350 6300 6350 6250
Connection ~ 5950 6300
Wire Wire Line
	3550 6250 3850 6250
Connection ~ 3550 6250
Connection ~ 3850 6250
Wire Wire Line
	3850 6250 3850 6200
Wire Wire Line
	5950 5250 6300 5250
Connection ~ 5950 5250
Connection ~ 6300 5250
Wire Wire Line
	6300 5250 6300 5200
Text GLabel 5800 2800 0    50   BiDi ~ 0
CYN_TRIG_1
Text GLabel 5750 3850 0    50   BiDi ~ 0
CYN_TRIG_2
Text GLabel 2950 2250 2    50   BiDi ~ 0
MUTE_LED
Text GLabel 4400 1250 0    50   BiDi ~ 0
BD_TRIG_OUT
Text GLabel 2350 2800 3    50   BiDi ~ 0
SR_U18_OUT
$Comp
L Connector:Conn_01x01_Female J70
U 1 1 636B5CDE
P 3150 1200
F 0 "J70" H 3178 1226 50  0000 L CNN
F 1 "SR_AUX_5" H 3178 1135 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 3150 1200 50  0001 C CNN
F 3 "~" H 3150 1200 50  0001 C CNN
	1    3150 1200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J69
U 1 1 636B6B54
P 3000 4350
F 0 "J69" H 3028 4376 50  0000 L CNN
F 1 "SR_AUX_6" H 3028 4285 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 3000 4350 50  0001 C CNN
F 3 "~" H 3000 4350 50  0001 C CNN
	1    3000 4350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
