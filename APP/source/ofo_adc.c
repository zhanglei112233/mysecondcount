#include "nrf_adc.h"
#include "nrf_soc.h"

volatile int32_t adc_sample;

/**
 * @brief ADC interrupt handler.
 */
void ADC_IRQHandler(void)
{
    nrf_adc_conversion_event_clean();
   // adc_sample = nrf_adc_result_get();
	  adc_sample = (nrf_adc_result_get()*(3.5*5/2)); 

}

/**
 * @brief ADC initialization.
 */
void adc_config(void)
{
    const nrf_adc_config_t nrf_adc_config = NRF_ADC_CONFIG_DEFAULT;

    // Initialize and configure ADC
    nrf_adc_configure( (nrf_adc_config_t *)&nrf_adc_config);
    nrf_adc_input_select(NRF_ADC_CONFIG_INPUT_3);
    nrf_adc_int_enable(ADC_INTENSET_END_Enabled << ADC_INTENSET_END_Pos);
    NVIC_SetPriority(ADC_IRQn, NRF_APP_PRIORITY_LOW);
    NVIC_EnableIRQ(ADC_IRQn);
	
	  nrf_adc_start();
}
