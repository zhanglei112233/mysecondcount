#ifndef FLASH_H
#define FLASH_H
#include "pstorage_platform.h"

#define BLE_NAME_ADD			0
#define Lock_No_ADD				1
#define BLECode_ADD				2

#define BLE_NAME_LEN			16
#define Lock_No_LEN				16
#define BLECode_LEN				16

/*写参数*/
void WriteParm(pstorage_size_t index, uint8_t *data, pstorage_size_t len);
/*读参数*/
void Readparm(pstorage_size_t index, uint8_t *data, pstorage_size_t len);
void flash_init(void);
void flash_test(void);
#endif
