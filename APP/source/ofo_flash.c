#include <stdbool.h>
#include <stdio.h>
#include "nrf_error.h"
#include "pstorage.h"
#include "ofo_flash.h"
#include "app_error.h"

#define M_BLOCK_SIZE   32                          /**< Maximum size should be less than or equal to PSTORAGE_MAX_BLOCK_SIZE .**/
#define M_BLOCK_COUNT  16 

bool     store_flag=false;
bool     update_flag=false;
bool     load_flag=false;
bool     clear_flag=false;
pstorage_handle_t m_flash_handle;
pstorage_handle_t base_flash_handle;

static void flash_pstorage_cb_handler(pstorage_handle_t * handle,uint8_t op_code,uint32_t result, uint8_t * p_data, uint32_t data_len) 
{ 
		switch(op_code) 
		{ 
				case PSTORAGE_STORE_OP_CODE:	
							if (result == NRF_SUCCESS) 
							{ 
							 store_flag=true;
							} 
							break; 
				case PSTORAGE_UPDATE_OP_CODE: 
							if (result == NRF_SUCCESS) 
							{ 
								update_flag=true;
							} 
							break; 
				case PSTORAGE_LOAD_OP_CODE: 
							if (result == NRF_SUCCESS) 
							{ 
								load_flag=true;
							} 
							break; 
				case PSTORAGE_CLEAR_OP_CODE: 
							if (result == NRF_SUCCESS) 
							{ 
								clear_flag=true;
							} 
							break; 
				default: 
						break; 
		} 
} 

 void flash_regeist()
{
		pstorage_module_param_t param;
		uint32_t retval;
		param.block_size = M_BLOCK_SIZE;
		param.block_count = M_BLOCK_COUNT;
		param.cb = flash_pstorage_cb_handler;
		retval = pstorage_register(&param, &base_flash_handle);
		if (retval == NRF_SUCCESS)
		{
			// Registration successful.
		}
		else
		{
			// Failed to register, take corrective action.
		}
}

 void flash_init(void)
{
		uint32_t retval;
		retval = pstorage_init();
		if(retval == NRF_SUCCESS)
		{

		}
		else
		{

		}
    
		flash_regeist();
}

void clear_flash(void) 
{ 
		uint32_t err_code; 
		err_code = pstorage_clear(&base_flash_handle,M_BLOCK_SIZE*M_BLOCK_COUNT); 
		APP_ERROR_CHECK(err_code); 
} 

void storage_flash(pstorage_size_t block_num,uint8_t *p_source_data,uint16_t dat_length,uint16_t offset ) 
{ 
		uint32_t err_code; 
		err_code= pstorage_block_identifier_get(&base_flash_handle, block_num, &m_flash_handle);
		APP_ERROR_CHECK(err_code);
		err_code = pstorage_store(&m_flash_handle, p_source_data, dat_length, offset); 
		APP_ERROR_CHECK(err_code); 
} 
void update_flash(pstorage_size_t block_num,uint8_t *p_source_data,pstorage_size_t dat_length,pstorage_size_t offset ) 
{ 
		uint32_t err_code; 
		err_code= pstorage_block_identifier_get(&base_flash_handle, block_num, &m_flash_handle);
		APP_ERROR_CHECK(err_code); 
		err_code =pstorage_update(&m_flash_handle, p_source_data, dat_length, offset); 
		APP_ERROR_CHECK(err_code); 
} 
void load_flash(pstorage_size_t block_num,uint8_t * p_source_data,pstorage_size_t dat_length,pstorage_size_t offset) 
{ 
		 uint32_t err_code; 
		 err_code = pstorage_block_identifier_get(&base_flash_handle,block_num,&m_flash_handle); 
		 APP_ERROR_CHECK(err_code); 
		 err_code = pstorage_load(p_source_data, &m_flash_handle,dat_length,offset); 
		 APP_ERROR_CHECK(err_code); 
} 

/*写参数*/
void WriteParm(pstorage_size_t index, uint8_t *data, pstorage_size_t len)
{
	update_flash(index, data, len, 0); //update data	
	while(!update_flag);
	update_flag = false;
}
/*读参数*/
void Readparm(pstorage_size_t index, uint8_t *data, pstorage_size_t len)
{
	load_flash(index, data, len, 0);
	while(!load_flag);
	load_flag = false;
}

void flash_test(void)
{
	uint8_t data[BLE_NAME_LEN] ;
	
	WriteParm(BLE_NAME_ADD ,"0123456789ABCDEF" ,BLE_NAME_LEN);
	Readparm(BLE_NAME_ADD ,data ,BLE_NAME_LEN);
	printf("read test %s\r\n",data);
}





/*
广播名称的前3个字符必须是”ofo“
密钥的前1个字符必须是“1“
设备地址的前1个字符必须是"1"

*/
//void ParmInit(void)
//{
//	memcpy(&Hard_parm_Ram,&Hard_parm,sizeof(Hard_parm));
/////////////////////////////////////////	
//	Readparm(Lock_No_ADD,Hard_parm_Ram.Lock_No,Lock_No_LEN);
//	if((Hard_parm_Ram.Lock_No[0]=='1'))
//	{
//	}
//	else
//	{
//		memcpy(Hard_parm_Ram.Lock_No,&Hard_parm.Lock_No,sizeof(Hard_parm.Lock_No));
//	}
////////////////////////////	
//	Readparm(Lock_No_ADD,Hard_parm_Ram.BLECode,BLECode_LEN);
//	if(Hard_parm_Ram.BLECode[0] == '1')
//	{
//		
//	}
//	else
//	{
//			memcpy(Hard_parm_Ram.BLECode,&Hard_parm.BLECode,sizeof(Hard_parm.BLECode));
//	}
////////////////////////	
//	Readparm(Lock_No_ADD,Hard_parm_Ram.Lock_No,Lock_No_LEN);
//	if((Hard_parm_Ram.BLE_NAME[0]=='o')&&(Hard_parm_Ram.BLE_NAME[0]=='f')&&(Hard_parm_Ram.BLE_NAME[0]=='o'))
//	{
//	}
//	else
//	{
//		memcpy(Hard_parm_Ram.BLE_NAME,&Hard_parm.BLE_NAME,sizeof(Hard_parm.BLE_NAME));
//	}
//	
//	memset(&gsm_data,0,sizeof(gsm_data));

//}
