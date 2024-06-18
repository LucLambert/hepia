/*
 * SSP.h
 *
 *  Created on: Mar 1, 2022
 *      Author: luclaptop
 */

#ifndef SSP_H_
#define SSP_H_

void ssp_config();
void ssp_send_char(uint8_t c);
void ssp_send(char* str, uint32_t length);

#endif /* SSP_H_ */
