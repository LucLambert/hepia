/*
 * touchscreen.h
 *
 *  Created on: 13 août 2016
 *      Author: cma
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdbool.h>
#include <stdint.h>
#include "I2C.h"

#define TOUCH_INT_PIN 11
#define TOUCH_I2C_ADDR 0x38<<1

#define TOUCH_MAX_DATA_RX     50
#define TOUCH_MAX_WIDTH       240
#define LTOUCH_MAX_HEIGHT     320

#define TOUCH_INIT_I2C_FAILED -13
#define TOUCH_RX_TOO_LONG     -12
#define TOUCH_NOT_INITIALISED -11
#define TOUCH_NOERROR          0


// event structure of the touchscreen
typedef struct
{
	uint16_t x1;
    uint16_t y1;
    uint8_t p1_pressure;
    uint16_t x2;
    uint16_t y2;
    uint8_t p2_pressure;
    uint8_t gesture;
    uint8_t nb_points;
} ts_event_t;



/* Initialise the touchscreen, either in standard mode or "interrupt" mode.
 * if is_ts_int=true, the interrupt routine EINT3_IRQHandler will be activated.
 * The interrupt will be called when a touch is detected.
 * Typically, the code of the interrupt could be:
 * if (LPC_GPIOINT->IO2IntStatF&(1<<TOUCH_INT_PIN))
 * {
 *    LPC_GPIOINT->IO2IntClr=1<<TOUCH_INT_PIN;     // clear interrupt source
 *    ts_event=touchscreen_read();				   // get and store touchscreen information
 * }
 * But to avoid latency, touchscreen_read() could be called from a background task too.
 * Return: error code: TOUCH_NOERROR or one of the error code defined above
 */
int init_touchscreen(bool is_ts_int);

/* functions used for polling the touchscreen.
*  Return: true if the touchscreen is pressed, false otherwise
*/
bool is_ts_pressed();				// very short

/* Gets the touchscreen status by filling the structure ts_event_t.
 * Take care to test the returned field "nb_points": if it is 0, ignore
 * the values of ts_event.
 * Parameter: ts_event: pointer on the strcture to be filled
 * Return: error code: TOUCH_NOERROR or one of the error code defined above
 */
int touchscreen_status(ts_event_t *ts_event);		// return complete structure

/* Wait that a finger touches the screen and get the coordinates of the point touched.
 * Parameter: pointers on x and y to be filled by the pixel coordinates of the point touched
 * Return: error code: TOUCH_NOERROR or one of the error code defined above
 */
int wait_for_touching(int *x, int *y);


#endif /* TOUCHSCREEN_H_ */
