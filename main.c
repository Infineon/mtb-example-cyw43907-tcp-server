/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the CYW43907 TCP Server Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
*******************************************************************************
* $ Copyright 2021-2023 Cypress Semiconductor $
*******************************************************************************/

/* Header file includes. */
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/* FreeRTOS header file. */
#include <FreeRTOS.h>
#include <task.h>

/* TCP server task header file. */
#include "tcp_server.h"

/*******************************************************************************
* Macros
********************************************************************************/
/* RTOS related macros for TCP server task. */
#define TCP_SERVER_TASK_STACK_SIZE                (1024 * 5)
#define TCP_SERVER_TASK_PRIORITY                  (1)


/*******************************************************************************
* Global Variables
********************************************************************************/
/* This enables RTOS aware debugging. */
volatile int uxTopUsedPriority;

/* TCP server task handle. */
TaskHandle_t server_task_handle;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CYW43907 CPU. It does
*    1. UART console output and input.
*    2. LED ON/OFF based on the TCP packet received.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    /* This enables RTOS aware debugging in OpenOCD. */
    uxTopUsedPriority = configMAX_PRIORITIES - 1 ;

    /* Initialize the board support package. */
    CY_ASSERT(CY_RSLT_SUCCESS == cybsp_init()) ;
    
    /* Enable global interrupts. */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port. */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, 
                        CY_RETARGET_IO_BAUDRATE);

    /* \x1b[2J\x1b[;H - ANSI ESC sequence to clear screen. */
    printf("\x1b[2J\x1b[;H");
    
    printf("****************** "
           "CYW43907 TCP Server"
           "****************** \r\n\n");
   /* Create the task to establish a connection to a TCP client. */
    xTaskCreate(tcp_server_task, "Network task", TCP_SERVER_TASK_STACK_SIZE, NULL, 
               TCP_SERVER_TASK_PRIORITY, &server_task_handle);

    /* Start the FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* Should never get here. */
    CY_ASSERT(0);
}

/* [] END OF FILE */
