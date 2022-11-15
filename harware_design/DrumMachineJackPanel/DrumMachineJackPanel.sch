EESchema Schematic File Version 4
LIBS:DrumMachineJackPanel-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Device:R_POT_US RV1
U 1 1 63748F84
P 1250 1100
F 0 "RV1" V 1137 1100 50  0000 C CNN
F 1 "500k" V 1046 1100 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 1250 1100 50  0001 C CNN
F 3 "~" H 1250 1100 50  0001 C CNN
	1    1250 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 950  1400 950 
Wire Wire Line
	1400 950  1400 1100
$Comp
L Connector:Conn_01x01_Female J1
U 1 1 637499C6
P 900 1100
F 0 "J1" H 792 875 50  0000 C CNN
F 1 "CYNA1-1" H 792 966 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 900 1100 50  0001 C CNN
F 3 "~" H 900 1100 50  0001 C CNN
	1    900  1100
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J7
U 1 1 6374A0E0
P 1600 1100
F 0 "J7" H 1628 1126 50  0000 L CNN
F 1 "CYNA1-W3" H 1628 1035 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1600 1100 50  0001 C CNN
F 3 "~" H 1600 1100 50  0001 C CNN
	1    1600 1100
	1    0    0    -1  
$EndComp
Connection ~ 1400 1100
$Comp
L Device:R_POT_US RV2
U 1 1 6374C559
P 1250 1550
F 0 "RV2" V 1137 1550 50  0000 C CNN
F 1 "500k" V 1046 1550 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 1250 1550 50  0001 C CNN
F 3 "~" H 1250 1550 50  0001 C CNN
	1    1250 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 1400 1400 1400
Wire Wire Line
	1400 1400 1400 1550
$Comp
L Connector:Conn_01x01_Female J2
U 1 1 6374C561
P 900 1550
F 0 "J2" H 792 1325 50  0000 C CNN
F 1 "CYNA2-1" H 792 1416 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 900 1550 50  0001 C CNN
F 3 "~" H 900 1550 50  0001 C CNN
	1    900  1550
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J8
U 1 1 6374C567
P 1600 1550
F 0 "J8" H 1628 1576 50  0000 L CNN
F 1 "CYNA2-W3" H 1628 1485 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1600 1550 50  0001 C CNN
F 3 "~" H 1600 1550 50  0001 C CNN
	1    1600 1550
	1    0    0    -1  
$EndComp
Connection ~ 1400 1550
$Comp
L Device:R_POT_US RV3
U 1 1 6374D679
P 1250 2000
F 0 "RV3" V 1137 2000 50  0000 C CNN
F 1 "500k" V 1046 2000 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 1250 2000 50  0001 C CNN
F 3 "~" H 1250 2000 50  0001 C CNN
	1    1250 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 1850 1400 1850
Wire Wire Line
	1400 1850 1400 2000
$Comp
L Connector:Conn_01x01_Female J3
U 1 1 6374D681
P 900 2000
F 0 "J3" H 792 1775 50  0000 C CNN
F 1 "CYNA3-1" H 792 1866 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 900 2000 50  0001 C CNN
F 3 "~" H 900 2000 50  0001 C CNN
	1    900  2000
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J9
U 1 1 6374D687
P 1600 2000
F 0 "J9" H 1628 2026 50  0000 L CNN
F 1 "CYNA3-W3" H 1628 1935 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1600 2000 50  0001 C CNN
F 3 "~" H 1600 2000 50  0001 C CNN
	1    1600 2000
	1    0    0    -1  
$EndComp
Connection ~ 1400 2000
$Comp
L Device:R_POT_US RV4
U 1 1 6374E415
P 1250 2450
F 0 "RV4" V 1137 2450 50  0000 C CNN
F 1 "500k" V 1046 2450 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 1250 2450 50  0001 C CNN
F 3 "~" H 1250 2450 50  0001 C CNN
	1    1250 2450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 2300 1400 2300
Wire Wire Line
	1400 2300 1400 2450
$Comp
L Connector:Conn_01x01_Female J4
U 1 1 6374E41D
P 900 2450
F 0 "J4" H 792 2225 50  0000 C CNN
F 1 "CYNA4-1" H 792 2316 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 900 2450 50  0001 C CNN
F 3 "~" H 900 2450 50  0001 C CNN
	1    900  2450
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J10
U 1 1 6374E423
P 1600 2450
F 0 "J10" H 1628 2476 50  0000 L CNN
F 1 "CYNA4-W3" H 1628 2385 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1600 2450 50  0001 C CNN
F 3 "~" H 1600 2450 50  0001 C CNN
	1    1600 2450
	1    0    0    -1  
$EndComp
Connection ~ 1400 2450
$Comp
L Device:R_POT_US RV5
U 1 1 6374EA0B
P 1250 2900
F 0 "RV5" V 1137 2900 50  0000 C CNN
F 1 "500k" V 1046 2900 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 1250 2900 50  0001 C CNN
F 3 "~" H 1250 2900 50  0001 C CNN
	1    1250 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 2750 1400 2750
Wire Wire Line
	1400 2750 1400 2900
$Comp
L Connector:Conn_01x01_Female J5
U 1 1 6374EA13
P 900 2900
F 0 "J5" H 792 2675 50  0000 C CNN
F 1 "CYNA5-1" H 792 2766 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 900 2900 50  0001 C CNN
F 3 "~" H 900 2900 50  0001 C CNN
	1    900  2900
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J11
U 1 1 6374EA19
P 1600 2900
F 0 "J11" H 1628 2926 50  0000 L CNN
F 1 "CYNA5-W3" H 1628 2835 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1600 2900 50  0001 C CNN
F 3 "~" H 1600 2900 50  0001 C CNN
	1    1600 2900
	1    0    0    -1  
$EndComp
Connection ~ 1400 2900
$Comp
L Device:R_POT_US RV6
U 1 1 6374F0B1
P 1250 3350
F 0 "RV6" V 1137 3350 50  0000 C CNN
F 1 "500k" V 1046 3350 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 1250 3350 50  0001 C CNN
F 3 "~" H 1250 3350 50  0001 C CNN
	1    1250 3350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1250 3200 1400 3200
Wire Wire Line
	1400 3200 1400 3350
$Comp
L Connector:Conn_01x01_Female J6
U 1 1 6374F0B9
P 900 3350
F 0 "J6" H 792 3125 50  0000 C CNN
F 1 "CYNA6-1" H 792 3216 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 900 3350 50  0001 C CNN
F 3 "~" H 900 3350 50  0001 C CNN
	1    900  3350
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J12
U 1 1 6374F0BF
P 1600 3350
F 0 "J12" H 1628 3376 50  0000 L CNN
F 1 "CYNA6-W3" H 1628 3285 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1600 3350 50  0001 C CNN
F 3 "~" H 1600 3350 50  0001 C CNN
	1    1600 3350
	1    0    0    -1  
$EndComp
Connection ~ 1400 3350
Wire Notes Line
	750  650  3650 650 
Wire Notes Line
	3650 650  3650 3600
Wire Notes Line
	3650 3600 750  3600
Wire Notes Line
	750  3600 750  650 
Text Notes 1650 800  0    50   ~ 0
CYNARE SHIMMER ADJUST
$Comp
L Connector:Barrel_Jack J13
U 1 1 6376C607
P 4650 1050
F 0 "J13" H 4707 1375 50  0000 C CNN
F 1 "Barrel_Jack" H 4707 1284 50  0000 C CNN
F 2 "mason_parts:BarrelJack_Horizontal" H 4700 1010 50  0001 C CNN
F 3 "~" H 4700 1010 50  0001 C CNN
	1    4650 1050
	1    0    0    -1  
$EndComp
$Comp
L Connector:DIN-5_180degree J16
U 1 1 63778119
P 8300 1650
F 0 "J16" H 8300 1283 50  0000 C CNN
F 1 "MIDI_IN" H 8300 1374 50  0000 C CNN
F 2 "mason_parts:DIN5_MIDI" H 8300 1650 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 8300 1650 50  0001 C CNN
	1    8300 1650
	-1   0    0    1   
$EndComp
$Comp
L Connector:DIN-5_180degree J17
U 1 1 63779ED5
P 8300 2800
F 0 "J17" H 8300 2433 50  0000 C CNN
F 1 "MIDI_OUT" H 8300 2524 50  0000 C CNN
F 2 "mason_parts:DIN5_MIDI" H 8300 2800 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 8300 2800 50  0001 C CNN
	1    8300 2800
	-1   0    0    1   
$EndComp
$Comp
L Connector:DIN-5_180degree J18
U 1 1 6377B0C5
P 8300 3750
F 0 "J18" H 8300 3383 50  0000 C CNN
F 1 "MIDI_THRU" H 8300 3474 50  0000 C CNN
F 2 "mason_parts:DIN5_MIDI" H 8300 3750 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 8300 3750 50  0001 C CNN
	1    8300 3750
	-1   0    0    1   
$EndComp
$Comp
L power:Earth #PWR0101
U 1 1 6377CB3D
P 8300 1950
F 0 "#PWR0101" H 8300 1700 50  0001 C CNN
F 1 "Earth" H 8300 1800 50  0001 C CNN
F 2 "" H 8300 1950 50  0001 C CNN
F 3 "~" H 8300 1950 50  0001 C CNN
	1    8300 1950
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0102
U 1 1 6377D376
P 8300 3100
F 0 "#PWR0102" H 8300 2850 50  0001 C CNN
F 1 "Earth" H 8300 2950 50  0001 C CNN
F 2 "" H 8300 3100 50  0001 C CNN
F 3 "~" H 8300 3100 50  0001 C CNN
	1    8300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0103
U 1 1 6377D93A
P 8300 4050
F 0 "#PWR0103" H 8300 3800 50  0001 C CNN
F 1 "Earth" H 8300 3900 50  0001 C CNN
F 2 "" H 8300 4050 50  0001 C CNN
F 3 "~" H 8300 4050 50  0001 C CNN
	1    8300 4050
	1    0    0    -1  
$EndComp
NoConn ~ 8600 3750
NoConn ~ 8000 3750
NoConn ~ 8600 2800
NoConn ~ 8000 2800
NoConn ~ 8600 1650
NoConn ~ 8000 1650
$Comp
L Connector:Conn_01x05_Male J15
U 1 1 637C2463
P 6800 2800
F 0 "J15" H 6908 3181 50  0000 C CNN
F 1 "MIDI_CONN" H 6908 3090 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B5B-XH-A_1x05_P2.50mm_Vertical" H 6800 2800 50  0001 C CNN
F 3 "~" H 6800 2800 50  0001 C CNN
	1    6800 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 1750 7500 1750
Wire Wire Line
	7500 1750 7500 2600
Wire Wire Line
	7500 2600 7000 2600
Wire Wire Line
	8600 1750 8600 2450
Wire Wire Line
	8600 2450 7550 2450
Wire Wire Line
	7550 2450 7550 2700
Wire Wire Line
	7550 2700 7000 2700
Wire Wire Line
	8000 2900 7500 2900
Wire Wire Line
	7500 2900 7500 2800
Wire Wire Line
	7500 2800 7000 2800
NoConn ~ 8600 2900
Wire Wire Line
	8000 3850 7150 3850
Wire Wire Line
	7150 3850 7150 3000
Wire Wire Line
	7150 3000 7000 3000
Wire Wire Line
	8600 3850 8800 3850
Wire Wire Line
	8800 3850 8800 3250
Wire Wire Line
	8800 3250 7300 3250
Wire Wire Line
	7300 3250 7300 2900
Wire Wire Line
	7300 2900 7000 2900
$Comp
L Connector:Conn_01x03_Male J14
U 1 1 63856CB5
P 5750 1050
F 0 "J14" H 5722 1074 50  0000 R CNN
F 1 "PWR_IN_CONN" H 5722 983 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B3B-XH-A_1x03_P2.50mm_Vertical" H 5750 1050 50  0001 C CNN
F 3 "~" H 5750 1050 50  0001 C CNN
	1    5750 1050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4950 950  5550 950 
Wire Wire Line
	5550 1050 4950 1050
Wire Wire Line
	4950 1050 4950 1150
Wire Wire Line
	4950 1150 5550 1150
Connection ~ 4950 1150
$Comp
L Connector:AudioJack2_Dual_Switch J19
U 1 1 638680FA
P 4800 2350
F 0 "J19" H 4807 2775 50  0000 C CNN
F 1 "MIX_LINE" H 4807 2684 50  0000 C CNN
F 2 "mason_parts:NMJ4HFD2" H 4750 2550 50  0001 C CNN
F 3 "~" H 4750 2550 50  0001 C CNN
	1    4800 2350
	1    0    0    -1  
$EndComp
NoConn ~ 5000 2250
NoConn ~ 5000 2450
$Comp
L Connector:AudioJack3_Dual_Switch J20
U 1 1 6386DB18
P 4850 3150
F 0 "J20" H 4807 3575 50  0000 C CNN
F 1 "MIX_HEADPHONE" H 4807 3484 50  0000 C CNN
F 2 "mason_parts:NRJ6HH-AU" H 4800 3150 50  0001 C CNN
F 3 "~" H 4800 3150 50  0001 C CNN
	1    4850 3150
	1    0    0    -1  
$EndComp
NoConn ~ 5050 3050
NoConn ~ 5050 3250
NoConn ~ 5050 3450
$Comp
L power:Earth #PWR0104
U 1 1 63871176
P 5050 2950
F 0 "#PWR0104" H 5050 2700 50  0001 C CNN
F 1 "Earth" H 5050 2800 50  0001 C CNN
F 2 "" H 5050 2950 50  0001 C CNN
F 3 "~" H 5050 2950 50  0001 C CNN
	1    5050 2950
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR0105
U 1 1 63871602
P 5000 2150
F 0 "#PWR0105" H 5000 1900 50  0001 C CNN
F 1 "Earth" H 5000 2000 50  0001 C CNN
F 2 "" H 5000 2150 50  0001 C CNN
F 3 "~" H 5000 2150 50  0001 C CNN
	1    5000 2150
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
