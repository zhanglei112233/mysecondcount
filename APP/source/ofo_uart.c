#include <stdio.h>
#include "ofo_uart.h"
#include "ofo_config.h"
#include "nordic_common.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "ofo_buzz.h"
#include "nrf_delay.h"

uint8_t UartSt = 0;
/**@brief   Function for handling app_uart events.
 *
 * @details This function will receive a single character from the app_uart module and append it to 
 *          a string. The string will be be sent over BLE when the last character received was a 
 *          'new line' i.e '\n' (hex 0x0D) or if the string has reached a length of 
 *          @ref NUS_MAX_DATA_LENGTH.
 */
/**@snippet [Handling the data received over UART] */
void uart_event_handle(app_uart_evt_t * p_event)
{
    static uint8_t data_array[BLE_NUS_MAX_DATA_LEN];
    static uint8_t index = 0;
//    uint32_t       err_code;

    switch (p_event->evt_type)
    {
        case APP_UART_DATA_READY:
            UNUSED_VARIABLE(app_uart_get(&data_array[index++]));
				
				    if(data_array[index] == 0x31)
						{
							KeyCVoice();
							index = 0;
						}
				    if(data_array[index] == 0x32)
						{
							KeyVoice();
							index = 0;
						}
				    if(data_array[index] == 0x33)
						{
							VoicePasswordOK();
							index = 0;
						}
				    if(data_array[index] == 0x34)
						{
							VoicePasswordErr();
							index = 0;
						}
            break;

        case APP_UART_COMMUNICATION_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default:
            break;
    }
}
/**@snippet [Handling the data received over UART] */


/**@brief  Function for initializing the UART module.
 */
/**@snippet [UART Initialization] */
void uart_init(void)
{
    uint32_t                     err_code;
	
		if(UartSt == 3)
		{
				app_uart_close();
				app_uart_flush();
				nrf_delay_ms(2);
		}
    const app_uart_comm_params_t comm_params =
    {
        RX_PIN_NUMBER,
        TX_PIN_NUMBER,
        RTS_PIN_NUMBER,
        CTS_PIN_NUMBER,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        UART_BAUDRATE_BAUDRATE_Baud38400
    };

    APP_UART_FIFO_INIT( &comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_event_handle,
                       APP_IRQ_PRIORITY_LOW,
                       err_code);
    APP_ERROR_CHECK(err_code);
}

/* [Handling the data received over UART] */
void uart_send(char *SenStr ,uint16_t SenLen)
{
		unsigned char i = 0;
		for(i = 0;i< SenLen ; i++)
		{
				app_uart_put(SenStr[i]);
		}
}

/**@snippet [UART Initialization] */
