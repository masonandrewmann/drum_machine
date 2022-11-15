EESchema Schematic File Version 4
LIBS:DrumMachineControlBoard-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 18 18
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
L Connector:Barrel_Jack J74
U 1 1 63A87DA6
P 2850 1700
F 0 "J74" H 2907 2025 50  0000 C CNN
F 1 "Barrel_Jack" H 2907 1934 50  0000 C CNN
F 2 "mason_parts:BarrelJack_Horizontal" H 2900 1660 50  0001 C CNN
F 3 "~" H 2900 1660 50  0001 C CNN
	1    2850 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack3_Dual_Switch J76
U 1 1 63A8A0D0
P 3500 3550
F 0 "J76" H 3457 3975 50  0000 C CNN
F 1 "MIX_HEADPHONE" H 3457 3884 50  0000 C CNN
F 2 "mason_parts:NRJ6HH-AU" H 3450 3550 50  0001 C CNN
F 3 "~" H 3450 3550 50  0001 C CNN
	1    3500 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_Dual_Switch J75
U 1 1 63A8AC55
P 3500 2750
F 0 "J75" H 3507 3175 50  0000 C CNN
F 1 "MIX_LINE" H 3507 3084 50  0000 C CNN
F 2 "mason_parts:NMJ4HFD2" H 3450 2950 50  0001 C CNN
F 3 "~" H 3450 2950 50  0001 C CNN
	1    3500 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J79
U 1 1 63A8D723
P 3750 1700
F 0 "J79" H 3722 1632 50  0000 R CNN
F 1 "Conn_01x03_Male" H 3722 1723 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B3B-XH-A_1x03_P2.50mm_Vertical" H 3750 1700 50  0001 C CNN
F 3 "~" H 3750 1700 50  0001 C CNN
	1    3750 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	3550 1800 3400 1800
Wire Wire Line
	3550 1700 3400 1700
Wire Wire Line
	3400 1700 3400 1800
Connection ~ 3400 1800
Wire Wire Line
	3400 1800 3150 1800
Wire Wire Line
	3550 1600 3150 1600
$Comp
L power:Earth #PWR077
U 1 1 63A8EC34
P 3700 2550
F 0 "#PWR077" H 3700 2300 50  0001 C CNN
F 1 "Earth" H 3700 2400 50  0001 C CNN
F 2 "" H 3700 2550 50  0001 C CNN
F 3 "~" H 3700 2550 50  0001 C CNN
	1    3700 2550
	0    -1   -1   0   
$EndComp
NoConn ~ 3700 2650
NoConn ~ 3700 2850
$Comp
L power:Earth #PWR078
U 1 1 63A8F3C8
P 3700 3350
F 0 "#PWR078" H 3700 3100 50  0001 C CNN
F 1 "Earth" H 3700 3200 50  0001 C CNN
F 2 "" H 3700 3350 50  0001 C CNN
F 3 "~" H 3700 3350 50  0001 C CNN
	1    3700 3350
	0    -1   -1   0   
$EndComp
NoConn ~ 3700 3450
NoConn ~ 3700 3650
$Comp
L Device:R_POT_US RV36
U 1 1 63A9EC4F
P 2300 5150
F 0 "RV36" V 2187 5150 50  0000 C CNN
F 1 "500k" V 2096 5150 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 2300 5150 50  0001 C CNN
F 3 "~" H 2300 5150 50  0001 C CNN
	1    2300 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 5150 2450 5000
Wire Wire Line
	2450 5000 2300 5000
$Comp
L Connector:Conn_01x01_Female J80
U 1 1 63A9FF11
P 1950 5150
F 0 "J80" H 1842 4925 50  0000 C CNN
F 1 "CYNA1-1" H 1842 5016 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1950 5150 50  0001 C CNN
F 3 "~" H 1950 5150 50  0001 C CNN
	1    1950 5150
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J88
U 1 1 63AA0B1E
P 2650 5150
F 0 "J88" H 2678 5176 50  0000 L CNN
F 1 "CYNA1-W3" H 2678 5085 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 2650 5150 50  0001 C CNN
F 3 "~" H 2650 5150 50  0001 C CNN
	1    2650 5150
	1    0    0    -1  
$EndComp
Connection ~ 2450 5150
$Comp
L Device:R_POT_US RV37
U 1 1 63AA1ED4
P 2300 5600
F 0 "RV37" V 2187 5600 50  0000 C CNN
F 1 "500k" V 2096 5600 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 2300 5600 50  0001 C CNN
F 3 "~" H 2300 5600 50  0001 C CNN
	1    2300 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 5600 2450 5450
Wire Wire Line
	2450 5450 2300 5450
$Comp
L Connector:Conn_01x01_Female J81
U 1 1 63AA1EDC
P 1950 5600
F 0 "J81" H 1842 5375 50  0000 C CNN
F 1 "CYNA2-1" H 1842 5466 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1950 5600 50  0001 C CNN
F 3 "~" H 1950 5600 50  0001 C CNN
	1    1950 5600
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J89
U 1 1 63AA1EE2
P 2650 5600
F 0 "J89" H 2678 5626 50  0000 L CNN
F 1 "CYNA2-W3" H 2678 5535 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 2650 5600 50  0001 C CNN
F 3 "~" H 2650 5600 50  0001 C CNN
	1    2650 5600
	1    0    0    -1  
$EndComp
Connection ~ 2450 5600
$Comp
L Device:R_POT_US RV38
U 1 1 63AA3FA4
P 2300 6050
F 0 "RV38" V 2187 6050 50  0000 C CNN
F 1 "500k" V 2096 6050 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 2300 6050 50  0001 C CNN
F 3 "~" H 2300 6050 50  0001 C CNN
	1    2300 6050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 6050 2450 5900
Wire Wire Line
	2450 5900 2300 5900
$Comp
L Connector:Conn_01x01_Female J82
U 1 1 63AA3FAC
P 1950 6050
F 0 "J82" H 1842 5825 50  0000 C CNN
F 1 "CYNA3-1" H 1842 5916 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1950 6050 50  0001 C CNN
F 3 "~" H 1950 6050 50  0001 C CNN
	1    1950 6050
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J90
U 1 1 63AA3FB2
P 2650 6050
F 0 "J90" H 2678 6076 50  0000 L CNN
F 1 "CYNA3-W3" H 2678 5985 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 2650 6050 50  0001 C CNN
F 3 "~" H 2650 6050 50  0001 C CNN
	1    2650 6050
	1    0    0    -1  
$EndComp
Connection ~ 2450 6050
$Comp
L Device:R_POT_US RV41
U 1 1 63AA3FB9
P 2300 6500
F 0 "RV41" V 2187 6500 50  0000 C CNN
F 1 "500k" V 2096 6500 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 2300 6500 50  0001 C CNN
F 3 "~" H 2300 6500 50  0001 C CNN
	1    2300 6500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 6500 2450 6350
Wire Wire Line
	2450 6350 2300 6350
$Comp
L Connector:Conn_01x01_Female J85
U 1 1 63AA3FC1
P 1950 6500
F 0 "J85" H 1842 6275 50  0000 C CNN
F 1 "CYNA4-1" H 1842 6366 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1950 6500 50  0001 C CNN
F 3 "~" H 1950 6500 50  0001 C CNN
	1    1950 6500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J91
U 1 1 63AA3FC7
P 2650 6500
F 0 "J91" H 2678 6526 50  0000 L CNN
F 1 "CYNA4-W3" H 2678 6435 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 2650 6500 50  0001 C CNN
F 3 "~" H 2650 6500 50  0001 C CNN
	1    2650 6500
	1    0    0    -1  
$EndComp
Connection ~ 2450 6500
$Comp
L Device:R_POT_US RV42
U 1 1 63AA78FD
P 2300 6950
F 0 "RV42" V 2187 6950 50  0000 C CNN
F 1 "500k" V 2096 6950 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 2300 6950 50  0001 C CNN
F 3 "~" H 2300 6950 50  0001 C CNN
	1    2300 6950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 6950 2450 6800
Wire Wire Line
	2450 6800 2300 6800
$Comp
L Connector:Conn_01x01_Female J86
U 1 1 63AA7905
P 1950 6950
F 0 "J86" H 1842 6725 50  0000 C CNN
F 1 "CYNA5-1" H 1842 6816 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1950 6950 50  0001 C CNN
F 3 "~" H 1950 6950 50  0001 C CNN
	1    1950 6950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J97
U 1 1 63AA790B
P 2650 6950
F 0 "J97" H 2678 6976 50  0000 L CNN
F 1 "CYNA5-W3" H 2678 6885 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 2650 6950 50  0001 C CNN
F 3 "~" H 2650 6950 50  0001 C CNN
	1    2650 6950
	1    0    0    -1  
$EndComp
Connection ~ 2450 6950
$Comp
L Device:R_POT_US RV43
U 1 1 63AA7912
P 2300 7400
F 0 "RV43" V 2187 7400 50  0000 C CNN
F 1 "500k" V 2096 7400 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 2300 7400 50  0001 C CNN
F 3 "~" H 2300 7400 50  0001 C CNN
	1    2300 7400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 7400 2450 7250
Wire Wire Line
	2450 7250 2300 7250
$Comp
L Connector:Conn_01x01_Female J87
U 1 1 63AA791A
P 1950 7400
F 0 "J87" H 1842 7175 50  0000 C CNN
F 1 "CYNA6-1" H 1842 7266 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 1950 7400 50  0001 C CNN
F 3 "~" H 1950 7400 50  0001 C CNN
	1    1950 7400
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J98
U 1 1 63AA7920
P 2650 7400
F 0 "J98" H 2678 7426 50  0000 L CNN
F 1 "CYNA6-W3" H 2678 7335 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 2650 7400 50  0001 C CNN
F 3 "~" H 2650 7400 50  0001 C CNN
	1    2650 7400
	1    0    0    -1  
$EndComp
Connection ~ 2450 7400
$Comp
L Device:R_POT_US RV44
U 1 1 63AB2268
P 4200 5150
F 0 "RV44" V 4087 5150 50  0000 C CNN
F 1 "500k" V 3996 5150 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 4200 5150 50  0001 C CNN
F 3 "~" H 4200 5150 50  0001 C CNN
	1    4200 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 5150 4350 5000
Wire Wire Line
	4350 5000 4200 5000
$Comp
L Connector:Conn_01x01_Female J99
U 1 1 63AB2270
P 3850 5150
F 0 "J99" H 3742 4925 50  0000 C CNN
F 1 "CYNB1-1" H 3742 5016 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 3850 5150 50  0001 C CNN
F 3 "~" H 3850 5150 50  0001 C CNN
	1    3850 5150
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J130
U 1 1 63AB2276
P 4550 5150
F 0 "J130" H 4578 5176 50  0000 L CNN
F 1 "CYNB1-W3" H 4578 5085 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 4550 5150 50  0001 C CNN
F 3 "~" H 4550 5150 50  0001 C CNN
	1    4550 5150
	1    0    0    -1  
$EndComp
Connection ~ 4350 5150
$Comp
L Device:R_POT_US RV45
U 1 1 63AB227D
P 4200 5600
F 0 "RV45" V 4087 5600 50  0000 C CNN
F 1 "500k" V 3996 5600 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 4200 5600 50  0001 C CNN
F 3 "~" H 4200 5600 50  0001 C CNN
	1    4200 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 5600 4350 5450
Wire Wire Line
	4350 5450 4200 5450
$Comp
L Connector:Conn_01x01_Female J100
U 1 1 63AB2285
P 3850 5600
F 0 "J100" H 3742 5375 50  0000 C CNN
F 1 "CYNB2-1" H 3742 5466 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 3850 5600 50  0001 C CNN
F 3 "~" H 3850 5600 50  0001 C CNN
	1    3850 5600
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J131
U 1 1 63AB228B
P 4550 5600
F 0 "J131" H 4578 5626 50  0000 L CNN
F 1 "CYNB2-W3" H 4578 5535 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 4550 5600 50  0001 C CNN
F 3 "~" H 4550 5600 50  0001 C CNN
	1    4550 5600
	1    0    0    -1  
$EndComp
Connection ~ 4350 5600
$Comp
L Device:R_POT_US RV46
U 1 1 63AB2292
P 4200 6050
F 0 "RV46" V 4087 6050 50  0000 C CNN
F 1 "500k" V 3996 6050 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 4200 6050 50  0001 C CNN
F 3 "~" H 4200 6050 50  0001 C CNN
	1    4200 6050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 6050 4350 5900
Wire Wire Line
	4350 5900 4200 5900
$Comp
L Connector:Conn_01x01_Female J103
U 1 1 63AB229A
P 3850 6050
F 0 "J103" H 3742 5825 50  0000 C CNN
F 1 "CYNB3-1" H 3742 5916 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 3850 6050 50  0001 C CNN
F 3 "~" H 3850 6050 50  0001 C CNN
	1    3850 6050
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J132
U 1 1 63AB22A0
P 4550 6050
F 0 "J132" H 4578 6076 50  0000 L CNN
F 1 "CYNB3-W3" H 4578 5985 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 4550 6050 50  0001 C CNN
F 3 "~" H 4550 6050 50  0001 C CNN
	1    4550 6050
	1    0    0    -1  
$EndComp
Connection ~ 4350 6050
$Comp
L Device:R_POT_US RV47
U 1 1 63AB22A7
P 4200 6500
F 0 "RV47" V 4087 6500 50  0000 C CNN
F 1 "500k" V 3996 6500 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 4200 6500 50  0001 C CNN
F 3 "~" H 4200 6500 50  0001 C CNN
	1    4200 6500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 6500 4350 6350
Wire Wire Line
	4350 6350 4200 6350
$Comp
L Connector:Conn_01x01_Female J112
U 1 1 63AB22AF
P 3850 6500
F 0 "J112" H 3742 6275 50  0000 C CNN
F 1 "CYNB4-1" H 3742 6366 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 3850 6500 50  0001 C CNN
F 3 "~" H 3850 6500 50  0001 C CNN
	1    3850 6500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J141
U 1 1 63AB22B5
P 4550 6500
F 0 "J141" H 4578 6526 50  0000 L CNN
F 1 "CYNB4-W3" H 4578 6435 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 4550 6500 50  0001 C CNN
F 3 "~" H 4550 6500 50  0001 C CNN
	1    4550 6500
	1    0    0    -1  
$EndComp
Connection ~ 4350 6500
$Comp
L Device:R_POT_US RV48
U 1 1 63AB22BC
P 4200 6950
F 0 "RV48" V 4087 6950 50  0000 C CNN
F 1 "500k" V 3996 6950 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 4200 6950 50  0001 C CNN
F 3 "~" H 4200 6950 50  0001 C CNN
	1    4200 6950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 6950 4350 6800
Wire Wire Line
	4350 6800 4200 6800
$Comp
L Connector:Conn_01x01_Female J128
U 1 1 63AB22C4
P 3850 6950
F 0 "J128" H 3742 6725 50  0000 C CNN
F 1 "CYNB5-1" H 3742 6816 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 3850 6950 50  0001 C CNN
F 3 "~" H 3850 6950 50  0001 C CNN
	1    3850 6950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J143
U 1 1 63AB22CA
P 4550 6950
F 0 "J143" H 4578 6976 50  0000 L CNN
F 1 "CYNB5-W3" H 4578 6885 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 4550 6950 50  0001 C CNN
F 3 "~" H 4550 6950 50  0001 C CNN
	1    4550 6950
	1    0    0    -1  
$EndComp
Connection ~ 4350 6950
$Comp
L Device:R_POT_US RV51
U 1 1 63AB22D1
P 4200 7400
F 0 "RV51" V 4087 7400 50  0000 C CNN
F 1 "500k" V 3996 7400 50  0000 C CNN
F 2 "mason_parts:masonsPotentiometer_Alpha_RD901F-40-00D_Single_Vertical" H 4200 7400 50  0001 C CNN
F 3 "~" H 4200 7400 50  0001 C CNN
	1    4200 7400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 7400 4350 7250
Wire Wire Line
	4350 7250 4200 7250
$Comp
L Connector:Conn_01x01_Female J129
U 1 1 63AB22D9
P 3850 7400
F 0 "J129" H 3742 7175 50  0000 C CNN
F 1 "CYNB6-1" H 3742 7266 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 3850 7400 50  0001 C CNN
F 3 "~" H 3850 7400 50  0001 C CNN
	1    3850 7400
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J144
U 1 1 63AB22DF
P 4550 7400
F 0 "J144" H 4578 7426 50  0000 L CNN
F 1 "CYNB6-W3" H 4578 7335 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill1mm" H 4550 7400 50  0001 C CNN
F 3 "~" H 4550 7400 50  0001 C CNN
	1    4550 7400
	1    0    0    -1  
$EndComp
Connection ~ 4350 7400
NoConn ~ 3700 3850
Text GLabel 3700 2750 2    50   BiDi ~ 0
LINE_OUT
$Comp
L Amplifier_Operational:TL072 U33
U 1 1 63721881
P 5450 3050
F 0 "U33" H 5550 2800 50  0000 C CNN
F 1 "TL072" H 5550 2900 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5450 3050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 5450 3050 50  0001 C CNN
	1    5450 3050
	-1   0    0    1   
$EndComp
$Comp
L Amplifier_Operational:TL072 U33
U 2 1 63725EE2
P 5450 3750
F 0 "U33" H 5550 3500 50  0000 C CNN
F 1 "TL072" H 5600 3600 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5450 3750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 5450 3750 50  0001 C CNN
	2    5450 3750
	-1   0    0    1   
$EndComp
$Comp
L Amplifier_Operational:TL072 U33
U 3 1 6372839F
P 6050 1600
F 0 "U33" H 6008 1646 50  0000 L CNN
F 1 "TL072" H 6008 1555 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6050 1600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 6050 1600 50  0001 C CNN
	3    6050 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3050 5150 2700
Wire Wire Line
	5150 2700 5750 2700
Wire Wire Line
	5750 2700 5750 2950
Wire Wire Line
	5750 3650 5750 3400
Wire Wire Line
	5750 3400 5150 3400
Wire Wire Line
	5150 3400 5150 3750
$Comp
L power:+12V #PWR079
U 1 1 6372B80D
P 5950 1300
F 0 "#PWR079" H 5950 1150 50  0001 C CNN
F 1 "+12V" H 5965 1473 50  0000 C CNN
F 2 "" H 5950 1300 50  0001 C CNN
F 3 "" H 5950 1300 50  0001 C CNN
	1    5950 1300
	1    0    0    -1  
$EndComp
$Comp
L power:-12V #PWR080
U 1 1 6372C2F1
P 5950 1900
F 0 "#PWR080" H 5950 2000 50  0001 C CNN
F 1 "-12V" H 5965 2073 50  0000 C CNN
F 2 "" H 5950 1900 50  0001 C CNN
F 3 "" H 5950 1900 50  0001 C CNN
	1    5950 1900
	-1   0    0    1   
$EndComp
$Comp
L Device:R_POT_TRIM_US RV53
U 1 1 6372D866
P 6600 3150
F 0 "RV53" H 6532 3104 50  0000 R CNN
F 1 "10k" H 6532 3195 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Runtron_RM-065_Vertical" H 6600 3150 50  0001 C CNN
F 3 "~" H 6600 3150 50  0001 C CNN
	1    6600 3150
	-1   0    0    1   
$EndComp
$Comp
L power:Earth #PWR081
U 1 1 6372F2B4
P 6600 3300
F 0 "#PWR081" H 6600 3050 50  0001 C CNN
F 1 "Earth" H 6600 3150 50  0001 C CNN
F 2 "" H 6600 3300 50  0001 C CNN
F 3 "~" H 6600 3300 50  0001 C CNN
	1    6600 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 3150 5850 3150
Wire Wire Line
	5850 3150 5850 3850
Wire Wire Line
	5850 3850 5750 3850
Connection ~ 5850 3150
Wire Wire Line
	5850 3150 5750 3150
Text GLabel 6700 2900 2    50   BiDi ~ 0
LINE_OUT
Wire Wire Line
	6700 2900 6600 2900
Wire Wire Line
	6600 2900 6600 3000
Wire Wire Line
	5150 3050 4100 3050
Wire Wire Line
	4100 3050 4100 3550
Wire Wire Line
	4100 3550 3700 3550
Connection ~ 5150 3050
Wire Wire Line
	5150 3750 3700 3750
Connection ~ 5150 3750
$EndSCHEMATC
