/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
/* Driver Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/Capture.h>
// #include <ti/drivers/Watchdog.h>

#include "inttypes.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"


#define arr_size(x)  sizeof(x)/sizeof(x[0]) // For calculating array size

/* Driver configuration */
#include "ti_drivers_config.h"

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* 1 second delay */
    static char line[256];
    uint8_t char_counter = 0;


    uint32_t time = 1;
    char        input;
    const char  echoPrompt[] = "Echoing characters:\r\n";
    UART_Handle uart;
    UART_Params uartParams;

    /**
     * PWM Initializsation
    */
    PWM_Handle pwm;
    PWM_Params pwmParams;
    uint32_t   dutyValue;


    /* Call driver init functions */
    GPIO_init();
    // I2C_init();
    // SPI_init();
    UART_init();
    PWM_init();

  // Initialize the PWM parameters
    PWM_Params_init(&pwmParams);
    pwmParams.idleLevel = PWM_IDLE_LOW;      // Output low when PWM is not running
    pwmParams.periodUnits = PWM_PERIOD_HZ;   // Period is in Hz
    pwmParams.periodValue = 10e3;             // 1MHz
    pwmParams.dutyUnits = PWM_DUTY_FRACTION; // Duty is in fractional percentage
    pwmParams.dutyValue = 0;                 // 0% initial duty cycle

    // Open the PWM instance
    pwm = PWM_open(CONFIG_PWM_0, &pwmParams);

    if (pwm == NULL) {
        // PWM_open() failed
        while (1);
    }

    PWM_start(pwm);                          // start PWM with 0% duty cycle

    dutyValue = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * 50) / 100);
    PWM_setDuty(pwm, dutyValue);  // set duty cycle to 37%
    // Watchdog_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }

    UART_write(uart, echoPrompt, sizeof(echoPrompt));

    while (1) {
         sleep(time);
         GPIO_toggle(CONFIG_GPIO_LED_0);
         while(uart != NULL){
             UART_read(uart, &input, 1);
             // UART_write(uart, &input, 1);
             if ((input == '\n') || (input == '\r')) {
                 //line[char_counter] = 0;

                 UART_write(uart,"\n", 1);
                 UART_write(uart, line, char_counter);
                 break;
             }
             else {
                 line[char_counter] = input;
                 char_counter++;
             }
         }
         char_counter = 0;
         if (line[0] == 'D'){
             int num = strTonum(line, arr_size(line));
             dutyValue = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * num) / 100);
             PWM_setDuty(pwm, dutyValue);  // set duty cycle to 37%
         }
    }
}

int strTonum(char *input_line, int loop_size)
{
  int NUMBER, i;
  char copy_line[loop_size];
  for(i = 0; i < (loop_size-1); i++)
  {
      copy_line[i] = input_line[i+1];
  }
  NUMBER = atoi(copy_line);
  return NUMBER;
}
