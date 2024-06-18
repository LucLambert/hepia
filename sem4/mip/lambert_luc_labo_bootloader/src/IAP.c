/*
 * IAP.c
 *
 *  Created on: May 17, 2022
 *      Author: luclaptop
 */
#include "IAP.h"

#define IAP_CMD_PREPARE_SECTOR 50
#define IAP_CMD_COPY_RAM_TO_FLASH 51
#define IAP_CMD_ERASE_SECTOR 52
#define IAP_CMD_BLANK_CHECK_SECTOR 53
#define IAP_CMD_READ_PART_ID_NBR 54
#define IAP_CMD_READ_BOOT_CODE_VERSION_NBR 55
#define IAP_CMD_READ_DEVICE_SERIAL_NBR 58
#define IAP_CMD_COMPARE 56
#define IAP_CMD_REINVOKE_ISP 57

typedef void (*IAP)(unsigned int [],unsigned int[]);

IAP iap_entry = (IAP) IAP_LOCATION;


void iap_exec_cmd(unsigned int cmd[],unsigned int output[]){
	__disable_irq();
	iap_entry(cmd, output);
	__enable_irq();
}

iap_status_code iap_prepare_sector(unsigned int start_sector, unsigned int end_sector){
	unsigned int cmd[5] = {IAP_CMD_PREPARE_SECTOR,start_sector,end_sector};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
	return output[0];
}

iap_status_code iap_copy_ram_to_flash(unsigned int dst, unsigned int src, unsigned int size, unsigned int cpu_frequency){
	if(size<=256)
		size = 256;
	else if(size>256 && size<=512)
		size = 512;
	else if(size>512 && size<=1024)
		size = 1024;
	else if(size>1024 && size<=4096)
			size = 4096;
	else
		return IAP_INVALID_CMD;
	unsigned int cmd[5] = {IAP_CMD_COPY_RAM_TO_FLASH, dst, src, size, cpu_frequency};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
	return output[0];
}

iap_status_code iap_erase_sector(unsigned int start, unsigned int end, unsigned int cpu_frequency){
	unsigned int cmd[5] = {IAP_CMD_ERASE_SECTOR, start, end, cpu_frequency};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
	return output[0];
}

iap_status_code iap_blank_check_sector(unsigned int start, unsigned int end, unsigned int result[]){
	unsigned int cmd[5] = {IAP_CMD_BLANK_CHECK_SECTOR, start, end};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
	if(output[0]==IAP_SECTOR_NOT_BLANK){
		result[0]=output[1];
		result[1]=output[2];
	}
	return output[0];
}

iap_status_code iap_read_part_id_nbr(unsigned int *  result){
	unsigned int cmd[5] = {IAP_CMD_READ_PART_ID_NBR};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
	*result = output[1];
	return output[0];
}

iap_status_code iap_read_boot_code_version_nbr(unsigned int *  result){
	unsigned int cmd[5] = {IAP_CMD_READ_BOOT_CODE_VERSION_NBR};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
	*result = ((((output[1]>>8) & 0xFF)<<8) | (output[1]&0xFF));
	return output[0];
}

iap_status_code iap_read_device_serial_nbr(unsigned int result[]){
	unsigned int cmd[5] = {IAP_CMD_READ_DEVICE_SERIAL_NBR};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
	result[0] = output[1];
	result[1] = output[2];
	result[2] = output[3];
	result[3] = output[4];
	return output[0];
}

iap_status_code iap_compare(unsigned int dest, unsigned int src, unsigned int size, unsigned int * result){
	unsigned int cmd[5] = {IAP_CMD_COMPARE, dest, src, size};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
	*result = output[1];
	return output[0];
}

void iap_reinvoke_isp(){
	unsigned int cmd[5] = {IAP_CMD_REINVOKE_ISP};
	unsigned int output[5];
	iap_exec_cmd(cmd, output);
}

iap_status_code iap_write_to_flash(unsigned int start_sector, unsigned int end_sector,unsigned int dst, unsigned int src, unsigned int size, unsigned int cpu_frequency){

	iap_status_code code;

	code = iap_prepare_sector(start_sector,end_sector);
	if(code != IAP_CMD_SUCCESS)
		return code;
	code = iap_erase_sector(start_sector, end_sector, cpu_frequency);
	if(code != IAP_CMD_SUCCESS)
			return code;
	code = iap_prepare_sector(start_sector,end_sector);
		if(code != IAP_CMD_SUCCESS)
			return code;
	code = iap_copy_ram_to_flash(dst, src, size, cpu_frequency);

	return code;
}

uint8_t iap_get_sector(unsigned int dest){
	uint8_t sector = 0;
	if(dest<0x1000){
		sector=0;
	}else if(dest<0x2000){
		sector=1;
	}else if(dest<0x3000){
		sector=2;
	}else if(dest<0x4000){
		sector=3;
	}else if(dest<0x5000){
		sector=4;
	}else if(dest<0x6000){
		sector=5;
	}else if(dest<0x7000){
		sector=6;
	}else if(dest<0x8000){
		sector=7;
	}else if(dest<0x9000){
		sector=8;
	}else if(dest<0xA000){
		sector=9;
	}else if(dest<0xB000){
		sector=10;
	}else if(dest<0xC000){
		sector=11;
	}else if(dest<0xD000){
		sector=12;
	}else if(dest<0xE000){
		sector=13;
	}else if(dest<0xF000){
		sector=14;
	}else if(dest<0x10000){
		sector=15;
	}else if(dest<0x18000){
		sector=16;
	}else if(dest<0x20000){
		sector=17;
	}else if(dest<0x28000){
		sector=18;
	}else if(dest<0x30000){
		sector=19;
	}else if(dest<0x38000){
		sector=20;
	}else if(dest<0x40000){
		sector=21;
	}else if(dest<0x48000){
		sector=22;
	}else if(dest<0x50000){
		sector=23;
	}else if(dest<0x58000){
		sector=24;
	}else if(dest<0x60000){
		sector=25;
	}else if(dest<0x68000){
		sector=26;
	}else if(dest<0x70000){
		sector=27;
	}else if(dest<0x78000){
		sector=28;
	}else if(dest<0x80000){
		sector=29;
	}
	return sector;
}
