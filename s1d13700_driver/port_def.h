/*
 * File:   pord_def.h
 * Author: ynki9
 *
 * Created on April 12, 2011, 8:53 PM
 */

#ifndef PORD_DEF_H
#define	PORD_DEF_H

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4

#define get_gpio_port(x) (x)/32
#define get_gpio_pin(x) (x)%32
#define get_gpio_mmap(x) (void*)(0xFFE02800 + ((x)*0x00004000))

#define PORT_A (void*)0xFFE02800
#define PORT_B (void*)0xFFE02C00
#define PORT_C (void*)0xFFE03000
#define PORT_D (void*)0xFFE03400
#define PORT_E (void*)0xFFE03800


#define PIO_PER 0x0000
#define PIO_PDR 0x0004
#define PIO_PSR 0x0008
#define PIO_OER 0x0010
#define PIO_ODR 0x0014
#define PIO_OSR 0x0018
#define PIO_SODR 0x0030
#define PIO_CODR 0x0034
#define PIO_PDSR 0x003C
#define PIO_PUDR 0x0060
#define PIO_PUER 0x0064
#define PIO_ASR 0x0070
#define PIO_OWER 0x00A0
#define PIO_ODSR 0x0038



/**********J5**********/

//#define J5_1 UNDEFINED
//#define J5_2 UNDEFINED
#define J5_3_PIO 0
#define J5_4_PIO 1
#define J5_5_PIO 2
#define J5_6_PIO 3
#define J5_7_PIO 4
#define J5_8_PIO 5
#define J5_9_PIO 6
#define J5_10_PIO 7
#define J5_11_PIO 8
#define J5_12_PIO 9
#define J5_13_PIO 21
#define J5_14_PIO 22
#define J5_15_PIO 23
#define J5_16_PIO 24
#define J5_17_PIO 25
#define J5_18_PIO 26
#define J5_19_PIO 27
#define J5_20_PIO 28
#define J5_21_PIO 29
#define J5_22_PIO 30
#define J5_23_PIO 31
#define J5_24_PIO 32
#define J5_25_PIO 33
#define J5_26_PIO 34
#define J5_27_PIO 35
#define J5_28_PIO 36
#define J5_29_PIO 37
#define J5_30_PIO 38
#define J5_31_PIO 20
//#define J5_32 UNDEFINED
//#define J5_33 UNDEFINED
//#define J5_34 UNDEFINED
//#define J5_35 UNDEFINED
//#define J5_36 UNDEFINED


/**********J6**********/

//#define J6_1 UNDEFINED
//#define J6_2 UNDEFINED
//#define J6_3 UNDEFINED
//#define J6_4 UNDEFINED
//#define J6_5 UNDEFINED
//#define J6_6 UNDEFINED
#define J6_7_PIO 39
#define J6_8_PIO 40
#define J6_9_PIO 41
#define J6_10_PIO 42
#define J6_11_PIO 43
#define J6_12_PIO 44
#define J6_13_PIO 45
#define J6_14_PIO 46
#define J6_15_PIO 47
#define J6_16_PIO 48
#define J6_17_PIO 49
#define J6_18_PIO 50
#define J6_19_PIO 51
#define J6_20_PIO 52
#define J6_21_PIO 53
#define J6_22_PIO 54
#define J6_23_PIO 55
#define J6_24_PIO 56
#define J6_25_PIO 57
#define J6_26_PIO 58
#define J6_27_PIO 59
//#define J6_28 UNDEFINED
//#define J6_29 UNDEFINED
//#define J6_30 UNDEFINED
//#define J6_31 UNDEFINED
//#define J6_32 UNDEFINED
//#define J6_33 UNDEFINED
//#define J6_34 UNDEFINED
//#define J6_35 UNDEFINED
//#define J6_36 UNDEFINED


/**********J7**********/

#define J7_1_PIO 131
#define J7_2_PIO 132
#define J7_3_PIO 133
#define J7_4_PIO 134
#define J7_5_PIO 135
#define J7_6_PIO 95
#define J7_7_PIO 96
#define J7_8_PIO 97
#define J7_9_PIO 136
#define J7_10_PIO 137
#define J7_11_PIO 138
#define J7_12_PIO 139
#define J7_13_PIO 140
#define J7_14_PIO 103
#define J7_15_PIO 104
#define J7_16_PIO 105
#define J7_17_PIO 141
#define J7_18_PIO 142
#define J7_19_PIO 143
#define J7_20_PIO 144
#define J7_21_PIO 145
#define J7_22_PIO 146
#define J7_23_PIO 112
#define J7_24_PIO 113
#define J7_25_PIO 129
#define J7_26_PIO 130
#define J7_27_PIO 84
#define J7_28_PIO 85
#define J7_29_PIO 86
//#define J7_30 UNDEFINED
//#define J7_31 UNDEFINED
//#define J7_32 UNDEFINED
//#define J7_33 UNDEFINED
//#define J7_34 UNDEFINED
//#define J7_35 UNDEFINED
//#define J7_36 UNDEFINED
#endif