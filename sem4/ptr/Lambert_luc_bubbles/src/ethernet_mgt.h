/*
 * ethernet_mgt.h
 *
 * Description: Ethernet driver. Note: RX/TX buffers must be in RAM2
 *              since SRAM is deactivated during WFI (the DMA can not copy data during a WFI in SRAM)
 * Created on: 13.4.2018
 * Author: Pilloux V.
 */

#ifndef ETHERNET_MGT_H_
#define ETHERNET_MGT_H_

/* Description: callback prototype for ethernet_init()
 *
 * Parameter: data: pointer on data to be received
 *            length: data length [bytes]
 */
typedef void (*rx_eth_callback_t)(void *data, int len);

/* Description: initialise Ethernet connection. RX/TX buffers MUST be declared in RAM2
 *              since SRAM is deactivated during WFI (the DMA can not copy data during a WFI in SRAM)
 *
 * Parameters:
 *      tx_double_buf: pointer on the transmission double buffer (can be NULL if not used)
 *      rx_double_buf: pointer on the receiving double buffer    (can be NULL if not used)
 *      double_len_tx: maximum length of the transmission double buffers
 *      double_len_rx: maximum length of the receiving double buffers
 *      rx_callback: pointer on a callback function which is called
 *                   each time data is received by Ethernet. If rx_callback==NULL,
 *                   no callback is used.
 *      Return: pointer on the data frame to be filled for transmission
 */
unsigned char *ethernet_init(unsigned char *tx_double_buf, int double_len_tx, unsigned char *rx_double_buf,
		           int double_len_rx, rx_eth_callback_t rx_callback);

/* Description: send raw data to Ethernet (no address management)
 *
 * Parameter: length: data length [bytes]. Note that length can be lower than double_len/2
 *                    but not bigger
 *             blocking: if true, waits the frame transmission
 * Return: pointer on the next data frame to transmit
 */
unsigned char *send_eth(int length, bool blocking);

/* Description: receive raw data from Ethernet (no address management).
 *              This function blocks until data is received.
 *
 * Parameter: length: pointer on the received data length [bytes]
 * Return:    pointer on the received data
 */
unsigned char *rec_eth(int *length);

#endif /* ETHERNET_MGT_H_ */
