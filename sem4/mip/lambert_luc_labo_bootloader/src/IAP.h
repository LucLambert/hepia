/*
 * IAP.h
 *
 *  Created on: May 17, 2022
 *      Author: luclaptop
 */

#ifndef IAP_H_
#define IAP_H_

#include "LPC17xx.h"

#define IAP_LOCATION 0x1FFF1FF1

//#define IAP_CMD_SUCCESS 0
//#define IAP_INVALID_CMD 1
//#define IAP_SRC_ADDR_ERROR 2
//#define IAP_DST_ADDR_ERROR 3
//#define IAP_SRC_ADDR_NOT_MAPPED 4
//#define IAP_DST_ADDR_NOT_MAPPED 5
//#define IAP_COUNT_ERROR 6
//#define IAP_INVALID_SECTOR 7
//#define IAP_SECTOR_NOT_BLANK 8
//#define IAP_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION 9
//#define IAP_COMPARE_ERROR 10
//#define IAP_BUSY 11

typedef enum _iap_status_code {
	IAP_CMD_SUCCESS,
	IAP_INVALID_CMD,
	IAP_SRC_ADDR_ERROR,
	IAP_DST_ADDR_ERROR,
	IAP_SRC_ADDR_NOT_MAPPED,
	IAP_DST_ADDR_NOT_MAPPED,
	IAP_COUNT_ERROR,
	IAP_INVALID_SECTOR,
	IAP_SECTOR_NOT_BLANK,
	IAP_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
	IAP_COMPARE_ERROR,
	IAP_BUSY
} iap_status_code;

iap_status_code iap_prepare_sector(unsigned int start_sector, unsigned int end_sector);

iap_status_code iap_copy_ram_to_flash(unsigned int dst, unsigned int src, unsigned int size, unsigned int cpu_frequency);

iap_status_code iap_erase_sector(unsigned int start, unsigned int end, unsigned int cpu_frequency);

iap_status_code iap_blank_check_sector(unsigned int start, unsigned int end, unsigned int result[]);

iap_status_code iap_read_part_id_nbr(unsigned int *  result);

iap_status_code iap_read_boot_code_version_nbr(unsigned int *  result);

iap_status_code iap_read_device_serial_nbr(unsigned int result[]);

iap_status_code iap_compare(unsigned int dest, unsigned int src, unsigned int size, unsigned int * result);

void iap_reinvoke_isp();

iap_status_code iap_write_to_flash(unsigned int start_sector, unsigned int end_sector,unsigned int dst, unsigned int src, unsigned int size, unsigned int cpu_frequency);

uint8_t iap_get_sector(unsigned int dest);


#endif /* IAP_H_ */
