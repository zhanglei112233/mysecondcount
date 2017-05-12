
#include "ble_nus.h"
#include "app_error.h"


extern ble_nus_t           m_nus;                                      /**< Structure to identify the Nordic UART Service. */

void SendStr2App( uint8_t * p_string, uint16_t length)
{
			uint32_t       err_code;
	    
	    if(length > 20)
			{
				  length = 20;
			}
			err_code = ble_nus_string_send(&m_nus, p_string, length);
			if (err_code != NRF_ERROR_INVALID_STATE)
			{
					APP_ERROR_CHECK(err_code);
			}
}
