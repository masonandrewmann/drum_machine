#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#define LCD_SCK 13
#define LCD_MOSI 11
#define LCD_MISO 12
//#define LCD_DC 2
#define LCD_DC 25
#define LCD_CS 10
//#define LCD_RST 3
#define LCD_RST 24

SPISettings settingsA(32000, MSBFIRST, SPI_MODE0); 

// End of constructor list

u8g2_t u8g2;


void setup(void) {
//  Serial.begin(115200);

  u8g2_Setup_pcd8544_84x48_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_spi, u8x8_stm32_gpio_and_delay);
  u8x8_SetPin_4Wire_HW_SPI(u8g2_GetU8x8(&u8g2), LCD_CS, LCD_DC, LCD_RST);
//  u8g2_Setup_pcd8544_84x48_f(&u8g2, U8G2_R0, u8x8_byte_4wire_sw_spi, u8x8_stm32_gpio_and_delay);

  u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
  u8g2_SetPowerSave(&u8g2, 0); // wake up display  
}

void loop(void) {
  u8g2_ClearBuffer(&u8g2);
//  Serial.println("clear complete");
  u8g2_DrawStr(&u8g2, 0, 11, "Hello World!");
//  u8g2_DrawLine(&u8g2, 2, 2, 20, 20);
//  u8g2_DrawLine(&u8g2, 2, 8, 20, 28);
//  u8g2_DrawLine(&u8g2, 2, 8, 20, 29);
//  Serial.println("draw complete");
//  u8g2.drawString(0,11,"Hello World!");
  u8g2_SendBuffer(&u8g2);
//  Serial.println("loop end");
  delay(2000);  
}

//
//uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
//{
//  /* STM32 supports HW SPI, Remove unused cases like U8X8_MSG_DELAY_XXX & U8X8_MSG_GPIO_XXX */
//  switch(msg)
//  {
//  case U8X8_MSG_GPIO_AND_DELAY_INIT:
//    /* Insert codes for initialization */
//    //this gets done by HAL init so we don't need anything here
////    pinMode(LCD_CS, OUTPUT);
////    pinMode(LCD_DC, OUTPUT);
////    pinMode(LCD_RST, OUTPUT);
////    pinMode(LCD_MOSI, OUTPUT);
////    SPI.setMOSI(LCD_MOSI); 
////    SPI.setMISO(1);
////    SPI.setSCK(LCD_SCK);
//    SPI.begin();
////    Serial.println("pins setup");
//    break;
//  case U8X8_MSG_DELAY_MILLI:
//    /* ms Delay */
////    HAL_Delay(arg_int);
//    delay(arg_int);
////    Serial.print("delayMillis: ");
////    Serial.println(arg_int);
//    break;
//    //Function which delays 10us
//  case U8X8_MSG_DELAY_10MICRO:
////    for (uint16_t n = 0; n < 320; n++)
////    {
//////      __NOP();
////    }
////    Serial.println("delay micros");
//    delayMicroseconds(10);
//    break;
//    //Function which delays 100ns
//  case U8X8_MSG_DELAY_100NANO:
////  Serial.println("delay  nanos");
//    __asm__("nop");
//    break;
//
//  case U8X8_MSG_GPIO_CS:
//    /* Insert codes for SS pin control */
////    HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, arg_int);
////    HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, arg_int);
//      digitalWrite(LCD_CS, arg_int);
////      Serial.print("CS: ");
////      Serial.println(arg_int);
//      
//    break;
//  case U8X8_MSG_GPIO_DC:
//    /* Insert codes for DC pin control */
////    HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, arg_int);
//    digitalWrite(LCD_DC, arg_int);
////      Serial.print("DC: ");
////      Serial.println(arg_int);
//    break;
//  case U8X8_MSG_GPIO_RESET:
//    /* Insert codes for RST pin control */
////    HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, arg_int);
//    digitalWrite(LCD_RST, arg_int);
////          Serial.print("RST: ");
////      Serial.println(arg_int);
//    break;
//  }
//  return 1;
//}


//uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
//{
//  switch(msg) {
//  case U8X8_MSG_BYTE_SEND:
//    /* Insert codes to transmit data */
////    if(HAL_SPI_Transmit(&hspi1, arg_ptr, arg_int, TX_TIMEOUT) != HAL_OK) return 0;
////      Serial.println("transfer send begin");
//      SPI.transfer(arg_int);
////      Serial.println("transfer send complete");
//    break;
//  case U8X8_MSG_BYTE_INIT:
//    /* Insert codes to begin SPI transmission */
////    Serial.println("transfer init");
//    SPI.beginTransaction(settingsA);
//    u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
//    __asm__("nop"); // delay nanoseconds?
//    break;
//  case U8X8_MSG_BYTE_SET_DC:
//    /* Control DC pin, U8X8_MSG_GPIO_DC will be called */
////    u8x8_gpio_SetDC(u8x8, arg_int);
//    digitalWrite(LCD_DC, HIGH);
//    break;
//  case U8X8_MSG_BYTE_START_TRANSFER:
//    /* Select slave, U8X8_MSG_GPIO_CS will be called */
////    Serial.println("transfer start");
//    u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
////    Serial.println("transfer complete");
////    HAL_Delay(1);
//    __asm__("nop");
//    break;
//  case U8X8_MSG_BYTE_END_TRANSFER:
////    HAL_Delay(1);
//    __asm__("nop");
//    /* Insert codes to end SPI transmission */
////    Serial.println("transfer end begin");
//    u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
//    SPI.endTransaction();
////    Serial.println("transfer end complete");
//    break;
//  default:
//    return 0;
//  }
//  return 1;
//}

uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  uint8_t i;
  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
    
      for( i = 0; i < U8X8_PIN_CNT; i++ )
  if ( u8x8->pins[i] != U8X8_PIN_NONE )
  {
    if ( i < U8X8_PIN_OUTPUT_CNT )
    {
      pinMode(u8x8->pins[i], OUTPUT);
    }
    else
    {
#ifdef INPUT_PULLUP
      pinMode(u8x8->pins[i], INPUT_PULLUP);
#else
      pinMode(u8x8->pins[i], OUTPUT);
      digitalWrite(u8x8->pins[i], 1);
#endif 
    }
  }
    
      break;

#ifndef __AVR__ 
    /* this case is not compiled for any AVR, because AVR uC are so slow */
    /* that this delay does not matter */
    case U8X8_MSG_DELAY_NANO:
      delayMicroseconds(arg_int==0?0:1);
      break;
#endif
    
    case U8X8_MSG_DELAY_10MICRO:
      /* not used at the moment */
      break;
    
    case U8X8_MSG_DELAY_100NANO:
      /* not used at the moment */
      break;
   
    case U8X8_MSG_DELAY_MILLI:
      delay(arg_int);
      break;
    case U8X8_MSG_DELAY_I2C:
      /* arg_int is 1 or 4: 100KHz (5us) or 400KHz (1.25us) */
      delayMicroseconds(arg_int<=2?5:2);
      break;
    case U8X8_MSG_GPIO_I2C_CLOCK:
    case U8X8_MSG_GPIO_I2C_DATA:
      if ( arg_int == 0 )
      {
  pinMode(u8x8_GetPinValue(u8x8, msg), OUTPUT);
  digitalWrite(u8x8_GetPinValue(u8x8, msg), 0);
      }
      else
      {
#ifdef INPUT_PULLUP
  pinMode(u8x8_GetPinValue(u8x8, msg), INPUT_PULLUP);
#else
  pinMode(u8x8_GetPinValue(u8x8, msg), OUTPUT);
  digitalWrite(u8x8_GetPinValue(u8x8, msg), 1);
#endif 
      }
      break;
    default:
      if ( msg >= U8X8_MSG_GPIO(0) )
      {
  i = u8x8_GetPinValue(u8x8, msg);
  if ( i != U8X8_PIN_NONE )
  {
    if ( u8x8_GetPinIndex(u8x8, msg) < U8X8_PIN_OUTPUT_CNT )
    {
      digitalWrite(i, arg_int);
    }
    else
    {
      if ( u8x8_GetPinIndex(u8x8, msg) == U8X8_PIN_OUTPUT_CNT )
      {
        // call yield() for the first pin only, u8x8 will always request all the pins, so this should be ok
        yield();
      }
      u8x8_SetGPIOResult(u8x8, digitalRead(i) == 0 ? 0 : 1);
    }
  }
  break;
      }
      
      return 0;
  }
  return 1;
}


uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
  uint8_t i;
  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
    
      for( i = 0; i < U8X8_PIN_CNT; i++ )
  if ( u8x8->pins[i] != U8X8_PIN_NONE )
  {
    if ( i < U8X8_PIN_OUTPUT_CNT )
    {
      pinMode(u8x8->pins[i], OUTPUT);
    }
    else
    {
#ifdef INPUT_PULLUP
      pinMode(u8x8->pins[i], INPUT_PULLUP);
#else
      pinMode(u8x8->pins[i], OUTPUT);
      digitalWrite(u8x8->pins[i], 1);
#endif 
    }
  }
    
      break;

#ifndef __AVR__ 
    /* this case is not compiled for any AVR, because AVR uC are so slow */
    /* that this delay does not matter */
    case U8X8_MSG_DELAY_NANO:
      delayMicroseconds(arg_int==0?0:1);
      break;
#endif
    
    case U8X8_MSG_DELAY_10MICRO:
      /* not used at the moment */
      break;
    
    case U8X8_MSG_DELAY_100NANO:
      /* not used at the moment */
      break;
   
    case U8X8_MSG_DELAY_MILLI:
      delay(arg_int);
      break;
    case U8X8_MSG_DELAY_I2C:
      /* arg_int is 1 or 4: 100KHz (5us) or 400KHz (1.25us) */
      delayMicroseconds(arg_int<=2?5:2);
      break;
    case U8X8_MSG_GPIO_I2C_CLOCK:
    case U8X8_MSG_GPIO_I2C_DATA:
      if ( arg_int == 0 )
      {
  pinMode(u8x8_GetPinValue(u8x8, msg), OUTPUT);
  digitalWrite(u8x8_GetPinValue(u8x8, msg), 0);
      }
      else
      {
#ifdef INPUT_PULLUP
  pinMode(u8x8_GetPinValue(u8x8, msg), INPUT_PULLUP);
#else
  pinMode(u8x8_GetPinValue(u8x8, msg), OUTPUT);
  digitalWrite(u8x8_GetPinValue(u8x8, msg), 1);
#endif 
      }
      break;
    default:
      if ( msg >= U8X8_MSG_GPIO(0) )
      {
  i = u8x8_GetPinValue(u8x8, msg);
  if ( i != U8X8_PIN_NONE )
  {
    if ( u8x8_GetPinIndex(u8x8, msg) < U8X8_PIN_OUTPUT_CNT )
    {
      digitalWrite(i, arg_int);
    }
    else
    {
      if ( u8x8_GetPinIndex(u8x8, msg) == U8X8_PIN_OUTPUT_CNT )
      {
        // call yield() for the first pin only, u8x8 will always request all the pins, so this should be ok
        yield();
      }
      u8x8_SetGPIOResult(u8x8, digitalRead(i) == 0 ? 0 : 1);
    }
  }
  break;
      }
      
      return 0;
  }
  return 1;
}
