EESchema Schematic File Version 4
LIBS:DrumMachineControlBoard-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 18
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
L Device:R_US R112
U 1 1 633A26D3
P 1200 1750
F 0 "R112" V 995 1750 50  0000 C CNN
F 1 "10k" V 1086 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1240 1740 50  0001 C CNN
F 3 "~" H 1200 1750 50  0001 C CNN
	1    1200 1750
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R116
U 1 1 633A2D80
P 1700 1300
F 0 "R116" H 1632 1254 50  0000 R CNN
F 1 "10k" H 1632 1345 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1740 1290 50  0001 C CNN
F 3 "~" H 1700 1300 50  0001 C CNN
	1    1700 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	1700 1450 1700 1550
$Comp
L power:Earth #PWR0284
U 1 1 633A3D78
P 1700 1950
F 0 "#PWR0284" H 1700 1700 50  0001 C CNN
F 1 "Earth" H 1700 1800 50  0001 C CNN
F 2 "" H 1700 1950 50  0001 C CNN
F 3 "~" H 1700 1950 50  0001 C CNN
	1    1700 1950
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J3
U 1 1 633A83C7
P 850 2000
F 0 "J3" H 780 2475 50  0000 C CNN
F 1 "BD_TRIG_IN" H 780 2384 50  0000 C CNN
F 2 "mason_parts:PJ301-BM" H 850 2000 50  0001 C CNN
F 3 "" H 850 2000 50  0001 C CNN
	1    850  2000
	-1   0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0285
U 1 1 633A93DE
P 800 1950
F 0 "#PWR0285" H 800 1700 50  0001 C CNN
F 1 "Earth" H 800 1800 50  0001 C CNN
F 2 "" H 800 1950 50  0001 C CNN
F 3 "~" H 800 1950 50  0001 C CNN
	1    800  1950
	1    0    0    -1  
$EndComp
Text GLabel 1700 1500 2    50   BiDi ~ 0
ExtTrig1
$Comp
L Device:R_US R113
U 1 1 633B0786
P 1200 2900
F 0 "R113" V 995 2900 50  0000 C CNN
F 1 "10k" V 1086 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1240 2890 50  0001 C CNN
F 3 "~" H 1200 2900 50  0001 C CNN
	1    1200 2900
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R117
U 1 1 633B078C
P 1700 2450
F 0 "R117" H 1632 2404 50  0000 R CNN
F 1 "10k" H 1632 2495 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1740 2440 50  0001 C CNN
F 3 "~" H 1700 2450 50  0001 C CNN
	1    1700 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	1700 2600 1700 2700
$Comp
L power:Earth #PWR0287
U 1 1 633B0799
P 1700 3100
F 0 "#PWR0287" H 1700 2850 50  0001 C CNN
F 1 "Earth" H 1700 2950 50  0001 C CNN
F 2 "" H 1700 3100 50  0001 C CNN
F 3 "~" H 1700 3100 50  0001 C CNN
	1    1700 3100
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J4
U 1 1 633B079F
P 850 3150
F 0 "J4" H 780 3625 50  0000 C CNN
F 1 "SN_TRIG_IN" H 780 3534 50  0000 C CNN
F 2 "mason_parts:PJ301-BM" H 850 3150 50  0001 C CNN
F 3 "" H 850 3150 50  0001 C CNN
	1    850  3150
	-1   0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0288
U 1 1 633B07A5
P 800 3100
F 0 "#PWR0288" H 800 2850 50  0001 C CNN
F 1 "Earth" H 800 2950 50  0001 C CNN
F 2 "" H 800 3100 50  0001 C CNN
F 3 "~" H 800 3100 50  0001 C CNN
	1    800  3100
	1    0    0    -1  
$EndComp
Text GLabel 1700 2650 2    50   BiDi ~ 0
ExtTrig2
$Comp
L Device:R_US R114
U 1 1 633BC0F9
P 1200 4050
F 0 "R114" V 995 4050 50  0000 C CNN
F 1 "10k" V 1086 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1240 4040 50  0001 C CNN
F 3 "~" H 1200 4050 50  0001 C CNN
	1    1200 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R118
U 1 1 633BC0FF
P 1700 3600
F 0 "R118" H 1632 3554 50  0000 R CNN
F 1 "10k" H 1632 3645 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1740 3590 50  0001 C CNN
F 3 "~" H 1700 3600 50  0001 C CNN
	1    1700 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	1700 3750 1700 3850
$Comp
L power:Earth #PWR0290
U 1 1 633BC10C
P 1700 4250
F 0 "#PWR0290" H 1700 4000 50  0001 C CNN
F 1 "Earth" H 1700 4100 50  0001 C CNN
F 2 "" H 1700 4250 50  0001 C CNN
F 3 "~" H 1700 4250 50  0001 C CNN
	1    1700 4250
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J5
U 1 1 633BC112
P 850 4300
F 0 "J5" H 780 4775 50  0000 C CNN
F 1 "CYN1_TRIG_IN" H 780 4684 50  0000 C CNN
F 2 "mason_parts:PJ301-BM" H 850 4300 50  0001 C CNN
F 3 "" H 850 4300 50  0001 C CNN
	1    850  4300
	-1   0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0291
U 1 1 633BC118
P 800 4250
F 0 "#PWR0291" H 800 4000 50  0001 C CNN
F 1 "Earth" H 800 4100 50  0001 C CNN
F 2 "" H 800 4250 50  0001 C CNN
F 3 "~" H 800 4250 50  0001 C CNN
	1    800  4250
	1    0    0    -1  
$EndComp
Text GLabel 1700 3800 2    50   BiDi ~ 0
ExtTrig3
$Comp
L Device:R_US R115
U 1 1 633BC125
P 1200 5200
F 0 "R115" V 995 5200 50  0000 C CNN
F 1 "10k" V 1086 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1240 5190 50  0001 C CNN
F 3 "~" H 1200 5200 50  0001 C CNN
	1    1200 5200
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R119
U 1 1 633BC12B
P 1700 4750
F 0 "R119" H 1632 4704 50  0000 R CNN
F 1 "10k" H 1632 4795 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1740 4740 50  0001 C CNN
F 3 "~" H 1700 4750 50  0001 C CNN
	1    1700 4750
	-1   0    0    1   
$EndComp
Wire Wire Line
	1700 4900 1700 5000
$Comp
L power:Earth #PWR0293
U 1 1 633BC138
P 1700 5400
F 0 "#PWR0293" H 1700 5150 50  0001 C CNN
F 1 "Earth" H 1700 5250 50  0001 C CNN
F 2 "" H 1700 5400 50  0001 C CNN
F 3 "~" H 1700 5400 50  0001 C CNN
	1    1700 5400
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J6
U 1 1 633BC13E
P 850 5450
F 0 "J6" H 780 5925 50  0000 C CNN
F 1 "CYN2_TRIG_IN" H 780 5834 50  0000 C CNN
F 2 "mason_parts:PJ301-BM" H 850 5450 50  0001 C CNN
F 3 "" H 850 5450 50  0001 C CNN
	1    850  5450
	-1   0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0294
U 1 1 633BC144
P 800 5400
F 0 "#PWR0294" H 800 5150 50  0001 C CNN
F 1 "Earth" H 800 5250 50  0001 C CNN
F 2 "" H 800 5400 50  0001 C CNN
F 3 "~" H 800 5400 50  0001 C CNN
	1    800  5400
	1    0    0    -1  
$EndComp
Text GLabel 1700 4950 2    50   BiDi ~ 0
ExtTrig4
$Comp
L Device:R_US R120
U 1 1 633CB693
P 2700 1750
F 0 "R120" V 2495 1750 50  0000 C CNN
F 1 "10k" V 2586 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2740 1740 50  0001 C CNN
F 3 "~" H 2700 1750 50  0001 C CNN
	1    2700 1750
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R124
U 1 1 633CB699
P 3200 1300
F 0 "R124" H 3132 1254 50  0000 R CNN
F 1 "10k" H 3132 1345 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3240 1290 50  0001 C CNN
F 3 "~" H 3200 1300 50  0001 C CNN
	1    3200 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 1450 3200 1550
$Comp
L power:Earth #PWR0296
U 1 1 633CB6A6
P 3200 1950
F 0 "#PWR0296" H 3200 1700 50  0001 C CNN
F 1 "Earth" H 3200 1800 50  0001 C CNN
F 2 "" H 3200 1950 50  0001 C CNN
F 3 "~" H 3200 1950 50  0001 C CNN
	1    3200 1950
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J7
U 1 1 633CB6AC
P 2350 2000
F 0 "J7" H 2280 2475 50  0000 C CNN
F 1 "GLITCH_TRIG_IN" H 2280 2384 50  0000 C CNN
F 2 "mason_parts:PJ301-BM" H 2350 2000 50  0001 C CNN
F 3 "" H 2350 2000 50  0001 C CNN
	1    2350 2000
	-1   0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0297
U 1 1 633CB6B2
P 2300 1950
F 0 "#PWR0297" H 2300 1700 50  0001 C CNN
F 1 "Earth" H 2300 1800 50  0001 C CNN
F 2 "" H 2300 1950 50  0001 C CNN
F 3 "~" H 2300 1950 50  0001 C CNN
	1    2300 1950
	1    0    0    -1  
$EndComp
Text GLabel 3200 1500 2    50   BiDi ~ 0
ExtTrig5
$Comp
L Device:R_US R121
U 1 1 633CB6BF
P 2700 2900
F 0 "R121" V 2495 2900 50  0000 C CNN
F 1 "10k" V 2586 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2740 2890 50  0001 C CNN
F 3 "~" H 2700 2900 50  0001 C CNN
	1    2700 2900
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R125
U 1 1 633CB6C5
P 3200 2450
F 0 "R125" H 3132 2404 50  0000 R CNN
F 1 "10k" H 3132 2495 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3240 2440 50  0001 C CNN
F 3 "~" H 3200 2450 50  0001 C CNN
	1    3200 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 2600 3200 2700
$Comp
L power:Earth #PWR0299
U 1 1 633CB6D2
P 3200 3100
F 0 "#PWR0299" H 3200 2850 50  0001 C CNN
F 1 "Earth" H 3200 2950 50  0001 C CNN
F 2 "" H 3200 3100 50  0001 C CNN
F 3 "~" H 3200 3100 50  0001 C CNN
	1    3200 3100
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J8
U 1 1 633CB6D8
P 2350 3150
F 0 "J8" H 2280 3625 50  0000 C CNN
F 1 "DIGI1_TRIG_IN" H 2280 3534 50  0000 C CNN
F 2 "mason_parts:PJ301-BM" H 2350 3150 50  0001 C CNN
F 3 "" H 2350 3150 50  0001 C CNN
	1    2350 3150
	-1   0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0300
U 1 1 633CB6DE
P 2300 3100
F 0 "#PWR0300" H 2300 2850 50  0001 C CNN
F 1 "Earth" H 2300 2950 50  0001 C CNN
F 2 "" H 2300 3100 50  0001 C CNN
F 3 "~" H 2300 3100 50  0001 C CNN
	1    2300 3100
	1    0    0    -1  
$EndComp
Text GLabel 3200 2650 2    50   BiDi ~ 0
ExtTrig6
$Comp
L Device:R_US R122
U 1 1 633CB6EB
P 2700 4050
F 0 "R122" V 2495 4050 50  0000 C CNN
F 1 "10k" V 2586 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2740 4040 50  0001 C CNN
F 3 "~" H 2700 4050 50  0001 C CNN
	1    2700 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R126
U 1 1 633CB6F1
P 3200 3600
F 0 "R126" H 3132 3554 50  0000 R CNN
F 1 "10k" H 3132 3645 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3240 3590 50  0001 C CNN
F 3 "~" H 3200 3600 50  0001 C CNN
	1    3200 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 3750 3200 3850
$Comp
L power:Earth #PWR0302
U 1 1 633CB6FE
P 3200 4250
F 0 "#PWR0302" H 3200 4000 50  0001 C CNN
F 1 "Earth" H 3200 4100 50  0001 C CNN
F 2 "" H 3200 4250 50  0001 C CNN
F 3 "~" H 3200 4250 50  0001 C CNN
	1    3200 4250
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J9
U 1 1 633CB704
P 2350 4300
F 0 "J9" H 2280 4775 50  0000 C CNN
F 1 "DIGI2_TRIG_IN" H 2280 4684 50  0000 C CNN
F 2 "mason_parts:PJ301-BM" H 2350 4300 50  0001 C CNN
F 3 "" H 2350 4300 50  0001 C CNN
	1    2350 4300
	-1   0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0303
U 1 1 633CB70A
P 2300 4250
F 0 "#PWR0303" H 2300 4000 50  0001 C CNN
F 1 "Earth" H 2300 4100 50  0001 C CNN
F 2 "" H 2300 4250 50  0001 C CNN
F 3 "~" H 2300 4250 50  0001 C CNN
	1    2300 4250
	1    0    0    -1  
$EndComp
Text GLabel 3200 3800 2    50   BiDi ~ 0
ExtTrig7
$Comp
L Device:R_US R123
U 1 1 633CB717
P 2700 5200
F 0 "R123" V 2495 5200 50  0000 C CNN
F 1 "10k" V 2586 5200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2740 5190 50  0001 C CNN
F 3 "~" H 2700 5200 50  0001 C CNN
	1    2700 5200
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R127
U 1 1 633CB71D
P 3200 4750
F 0 "R127" H 3132 4704 50  0000 R CNN
F 1 "10k" H 3132 4795 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3240 4740 50  0001 C CNN
F 3 "~" H 3200 4750 50  0001 C CNN
	1    3200 4750
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 4900 3200 5000
$Comp
L power:Earth #PWR0305
U 1 1 633CB72A
P 3200 5400
F 0 "#PWR0305" H 3200 5150 50  0001 C CNN
F 1 "Earth" H 3200 5250 50  0001 C CNN
F 2 "" H 3200 5400 50  0001 C CNN
F 3 "~" H 3200 5400 50  0001 C CNN
	1    3200 5400
	1    0    0    -1  
$EndComp
$Comp
L modular_synth:AudioJack_Switched_Mono J10
U 1 1 633CB730
P 2350 5450
F 0 "J10" H 2280 5925 50  0000 C CNN
F 1 "DIGI3_TRIG_IN" H 2280 5834 50  0000 C CNN
F 2 "mason_parts:PJ301-BM" H 2350 5450 50  0001 C CNN
F 3 "" H 2350 5450 50  0001 C CNN
	1    2350 5450
	-1   0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0306
U 1 1 633CB736
P 2300 5400
F 0 "#PWR0306" H 2300 5150 50  0001 C CNN
F 1 "Earth" H 2300 5250 50  0001 C CNN
F 2 "" H 2300 5400 50  0001 C CNN
F 3 "~" H 2300 5400 50  0001 C CNN
	1    2300 5400
	1    0    0    -1  
$EndComp
Text GLabel 3200 4950 2    50   BiDi ~ 0
ExtTrig8
Text Notes 850  900  0    50   ~ 0
NOTE: THIS CONFIGURATION INVERTS\nTHE LOGIC LEVEL\nGATE = 0v\nNO GATE = 3.3V
$Comp
L Device:D_Small D10
U 1 1 63111485
P 1400 1900
F 0 "D10" V 1400 1968 50  0000 L CNN
F 1 "D_Small" V 1445 1968 50  0001 L CNN
F 2 "Diode_SMD:D_SOD-123" V 1400 1900 50  0001 C CNN
F 3 "~" V 1400 1900 50  0001 C CNN
	1    1400 1900
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0277
U 1 1 631134F9
P 1400 2000
F 0 "#PWR0277" H 1400 1750 50  0001 C CNN
F 1 "Earth" H 1400 1850 50  0001 C CNN
F 2 "" H 1400 2000 50  0001 C CNN
F 3 "~" H 1400 2000 50  0001 C CNN
	1    1400 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1800 1400 1750
Wire Wire Line
	1400 1750 1350 1750
$Comp
L Device:D_Small D11
U 1 1 63116B73
P 1400 3050
F 0 "D11" V 1354 3118 50  0000 L CNN
F 1 "D_Small" V 1445 3118 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 1400 3050 50  0001 C CNN
F 3 "~" V 1400 3050 50  0001 C CNN
	1    1400 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 2950 1400 2900
Wire Wire Line
	1350 2900 1400 2900
$Comp
L power:Earth #PWR0278
U 1 1 63118144
P 1400 3150
F 0 "#PWR0278" H 1400 2900 50  0001 C CNN
F 1 "Earth" H 1400 3000 50  0001 C CNN
F 2 "" H 1400 3150 50  0001 C CNN
F 3 "~" H 1400 3150 50  0001 C CNN
	1    1400 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D12
U 1 1 63118D49
P 1400 4200
F 0 "D12" V 1354 4268 50  0000 L CNN
F 1 "D_Small" V 1445 4268 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 1400 4200 50  0001 C CNN
F 3 "~" V 1400 4200 50  0001 C CNN
	1    1400 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 4100 1400 4050
$Comp
L power:Earth #PWR0279
U 1 1 63119E8F
P 1400 4300
F 0 "#PWR0279" H 1400 4050 50  0001 C CNN
F 1 "Earth" H 1400 4150 50  0001 C CNN
F 2 "" H 1400 4300 50  0001 C CNN
F 3 "~" H 1400 4300 50  0001 C CNN
	1    1400 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4050 1350 4050
$Comp
L Device:D_Small D13
U 1 1 6311B549
P 1400 5350
F 0 "D13" V 1354 5418 50  0000 L CNN
F 1 "D_Small" V 1445 5418 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 1400 5350 50  0001 C CNN
F 3 "~" V 1400 5350 50  0001 C CNN
	1    1400 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 5250 1400 5200
Wire Wire Line
	1350 5200 1400 5200
$Comp
L power:Earth #PWR0280
U 1 1 6311CDD5
P 1400 5450
F 0 "#PWR0280" H 1400 5200 50  0001 C CNN
F 1 "Earth" H 1400 5300 50  0001 C CNN
F 2 "" H 1400 5450 50  0001 C CNN
F 3 "~" H 1400 5450 50  0001 C CNN
	1    1400 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D14
U 1 1 6311E69F
P 2900 1900
F 0 "D14" V 2854 1968 50  0000 L CNN
F 1 "D_Small" V 2945 1968 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 2900 1900 50  0001 C CNN
F 3 "~" V 2900 1900 50  0001 C CNN
	1    2900 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 1800 2900 1750
Wire Wire Line
	2850 1750 2900 1750
$Comp
L power:Earth #PWR0281
U 1 1 6311FE2A
P 2900 2000
F 0 "#PWR0281" H 2900 1750 50  0001 C CNN
F 1 "Earth" H 2900 1850 50  0001 C CNN
F 2 "" H 2900 2000 50  0001 C CNN
F 3 "~" H 2900 2000 50  0001 C CNN
	1    2900 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D15
U 1 1 6312145A
P 2900 3050
F 0 "D15" V 2854 3118 50  0000 L CNN
F 1 "D_Small" V 2945 3118 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 2900 3050 50  0001 C CNN
F 3 "~" V 2900 3050 50  0001 C CNN
	1    2900 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 2950 2900 2900
Wire Wire Line
	2850 2900 2900 2900
$Comp
L power:Earth #PWR0282
U 1 1 63122ABD
P 2900 3150
F 0 "#PWR0282" H 2900 2900 50  0001 C CNN
F 1 "Earth" H 2900 3000 50  0001 C CNN
F 2 "" H 2900 3150 50  0001 C CNN
F 3 "~" H 2900 3150 50  0001 C CNN
	1    2900 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Small D16
U 1 1 63124759
P 2900 4200
F 0 "D16" V 2854 4268 50  0000 L CNN
F 1 "D_Small" V 2945 4268 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 2900 4200 50  0001 C CNN
F 3 "~" V 2900 4200 50  0001 C CNN
	1    2900 4200
	0    1    1    0   
$EndComp
$Comp
L Device:D_Small D17
U 1 1 631252F3
P 2900 5350
F 0 "D17" V 2854 5418 50  0000 L CNN
F 1 "D_Small" V 2945 5418 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 2900 5350 50  0001 C CNN
F 3 "~" V 2900 5350 50  0001 C CNN
	1    2900 5350
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0348
U 1 1 63125FF4
P 2900 5450
F 0 "#PWR0348" H 2900 5200 50  0001 C CNN
F 1 "Earth" H 2900 5300 50  0001 C CNN
F 2 "" H 2900 5450 50  0001 C CNN
F 3 "~" H 2900 5450 50  0001 C CNN
	1    2900 5450
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0349
U 1 1 631266F5
P 2900 4300
F 0 "#PWR0349" H 2900 4050 50  0001 C CNN
F 1 "Earth" H 2900 4150 50  0001 C CNN
F 2 "" H 2900 4300 50  0001 C CNN
F 3 "~" H 2900 4300 50  0001 C CNN
	1    2900 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4050 2900 4050
Wire Wire Line
	2900 4100 2900 4050
Wire Wire Line
	2900 5250 2900 5200
Wire Wire Line
	2900 5200 2850 5200
$Comp
L power:+3.3V #PWR0211
U 1 1 63248683
P 1700 1150
F 0 "#PWR0211" H 1700 1000 50  0001 C CNN
F 1 "+3.3V" H 1715 1323 50  0000 C CNN
F 2 "" H 1700 1150 50  0001 C CNN
F 3 "" H 1700 1150 50  0001 C CNN
	1    1700 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0212
U 1 1 6324911F
P 3200 1150
F 0 "#PWR0212" H 3200 1000 50  0001 C CNN
F 1 "+3.3V" H 3215 1323 50  0000 C CNN
F 2 "" H 3200 1150 50  0001 C CNN
F 3 "" H 3200 1150 50  0001 C CNN
	1    3200 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0213
U 1 1 6324973E
P 3200 2300
F 0 "#PWR0213" H 3200 2150 50  0001 C CNN
F 1 "+3.3V" H 3215 2473 50  0000 C CNN
F 2 "" H 3200 2300 50  0001 C CNN
F 3 "" H 3200 2300 50  0001 C CNN
	1    3200 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0214
U 1 1 63249B35
P 1700 2300
F 0 "#PWR0214" H 1700 2150 50  0001 C CNN
F 1 "+3.3V" H 1715 2473 50  0000 C CNN
F 2 "" H 1700 2300 50  0001 C CNN
F 3 "" H 1700 2300 50  0001 C CNN
	1    1700 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0215
U 1 1 63249ED0
P 1700 3450
F 0 "#PWR0215" H 1700 3300 50  0001 C CNN
F 1 "+3.3V" H 1715 3623 50  0000 C CNN
F 2 "" H 1700 3450 50  0001 C CNN
F 3 "" H 1700 3450 50  0001 C CNN
	1    1700 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0216
U 1 1 6324A420
P 3200 3450
F 0 "#PWR0216" H 3200 3300 50  0001 C CNN
F 1 "+3.3V" H 3215 3623 50  0000 C CNN
F 2 "" H 3200 3450 50  0001 C CNN
F 3 "" H 3200 3450 50  0001 C CNN
	1    3200 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0217
U 1 1 6324ACDA
P 3200 4600
F 0 "#PWR0217" H 3200 4450 50  0001 C CNN
F 1 "+3.3V" H 3215 4773 50  0000 C CNN
F 2 "" H 3200 4600 50  0001 C CNN
F 3 "" H 3200 4600 50  0001 C CNN
	1    3200 4600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0218
U 1 1 6324B1E5
P 1700 4600
F 0 "#PWR0218" H 1700 4450 50  0001 C CNN
F 1 "+3.3V" H 1715 4773 50  0000 C CNN
F 2 "" H 1700 4600 50  0001 C CNN
F 3 "" H 1700 4600 50  0001 C CNN
	1    1700 4600
	1    0    0    -1  
$EndComp
NoConn ~ 1050 1850
NoConn ~ 1050 3000
NoConn ~ 2550 3000
NoConn ~ 2550 1850
NoConn ~ 1050 4150
NoConn ~ 1050 5300
NoConn ~ 2550 5300
NoConn ~ 2550 4150
$Comp
L Transistor_BJT:MMBT3904 Q3
U 1 1 63495272
P 1600 1750
F 0 "Q3" H 1791 1796 50  0000 L CNN
F 1 "MMBT3904" H 1791 1705 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1800 1675 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 1600 1750 50  0001 L CNN
	1    1600 1750
	1    0    0    -1  
$EndComp
Connection ~ 1400 1750
$Comp
L Transistor_BJT:MMBT3904 Q4
U 1 1 63496CC2
P 1600 2900
F 0 "Q4" H 1791 2946 50  0000 L CNN
F 1 "MMBT3904" H 1791 2855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1800 2825 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 1600 2900 50  0001 L CNN
	1    1600 2900
	1    0    0    -1  
$EndComp
Connection ~ 1400 2900
$Comp
L Transistor_BJT:MMBT3904 Q5
U 1 1 634978F4
P 1600 4050
F 0 "Q5" H 1791 4096 50  0000 L CNN
F 1 "MMBT3904" H 1791 4005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1800 3975 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 1600 4050 50  0001 L CNN
	1    1600 4050
	1    0    0    -1  
$EndComp
Connection ~ 1400 4050
$Comp
L Transistor_BJT:MMBT3904 Q6
U 1 1 63498350
P 1600 5200
F 0 "Q6" H 1791 5246 50  0000 L CNN
F 1 "MMBT3904" H 1791 5155 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 1800 5125 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 1600 5200 50  0001 L CNN
	1    1600 5200
	1    0    0    -1  
$EndComp
Connection ~ 1400 5200
$Comp
L Transistor_BJT:MMBT3904 Q10
U 1 1 63498E68
P 3100 5200
F 0 "Q10" H 3291 5246 50  0000 L CNN
F 1 "MMBT3904" H 3291 5155 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3300 5125 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 3100 5200 50  0001 L CNN
	1    3100 5200
	1    0    0    -1  
$EndComp
Connection ~ 2900 5200
$Comp
L Transistor_BJT:MMBT3904 Q9
U 1 1 63499D5B
P 3100 4050
F 0 "Q9" H 3291 4096 50  0000 L CNN
F 1 "MMBT3904" H 3291 4005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3300 3975 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 3100 4050 50  0001 L CNN
	1    3100 4050
	1    0    0    -1  
$EndComp
Connection ~ 2900 4050
$Comp
L Transistor_BJT:MMBT3904 Q8
U 1 1 6349A6FB
P 3100 2900
F 0 "Q8" H 3291 2946 50  0000 L CNN
F 1 "MMBT3904" H 3291 2855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3300 2825 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 3100 2900 50  0001 L CNN
	1    3100 2900
	1    0    0    -1  
$EndComp
Connection ~ 2900 2900
$Comp
L Transistor_BJT:MMBT3904 Q7
U 1 1 6349AFDF
P 3100 1750
F 0 "Q7" H 3291 1796 50  0000 L CNN
F 1 "MMBT3904" H 3291 1705 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3300 1675 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 3100 1750 50  0001 L CNN
	1    3100 1750
	1    0    0    -1  
$EndComp
Connection ~ 2900 1750
$EndSCHEMATC
