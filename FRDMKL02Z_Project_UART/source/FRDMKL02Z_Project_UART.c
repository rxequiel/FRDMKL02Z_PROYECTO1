/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    FRDMKL02Z_Project_UART.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"


#include "sdk_hal_uart0.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
/*
 * @brief   Application entry point.
 */
//------funcion para enceder o apagar los leds -----
void led(uint8_t entrada){
	// con este switch se eligira segun la letra ingresada que led se enciende y apaga
	switch(entrada){
	case 'A': GPIO_PortClear(GPIOB, 1u << 10u);printf("LED AZUL ON\r\n");break;
	case 'a': GPIO_PortSet(GPIOB, 1u << 10u);printf("LED AZUL OFF\r\n");break;
	case 'R': GPIO_PortClear(GPIOB, 1u << 6u);printf("LED ROJO ON\r\n");break;
	case 'r': GPIO_PortSet(GPIOB, 1u << 6u);printf("LED ROJO OFF\r\n");break;
	case 'V': GPIO_PortClear(GPIOB, 1u << 7u);printf("LED VERDE ON\r\n");break;
	case 'v': GPIO_PortSet(GPIOB, 1u << 7u);printf("LED VERDE OFF\r\n");break;
	case 'M': GPIO_PortClear(GPIOB, 1u << 10u);GPIO_PortClear(GPIOB, 1u << 6u);printf("LED MAGENTA ON\r\n");break;
	case 'm': GPIO_PortSet(GPIOB, 1u << 10u);GPIO_PortSet(GPIOB, 1u << 6u);printf("LED MAGENTA OFF\r\n");break;
	default: printf("la tecla presionada es incorrecta");
	}

}
int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    (void)uart0Inicializar(115200); //llamamos a la función de inicializar el puerto UART0

   while(1) {
    	status_t status;    //nos permitira conocer el estado de la lectura de datos del serial
    	uint8_t nuevo_byte; //almacenara el dato ingresado a traves del  serial

    	if(uart0NuevosDatosEnBuffer()>0){
    		status=uart0LeerByteDesdeBufferCircular(&nuevo_byte);
    		if(status==kStatus_Success){

    			led(nuevo_byte); //hacemos un llamado a la funcion que contiene las ordenes de los leds segun la letra que se ingrese

    		}else{
    			printf("error\r\n"); //en caso de haber problemas con el UART0 notificara con un error
    		}
    	}
    }
    return 0 ;


}

