/*
 * Wdg.h
 *
 *  Created on: 10 ago. 2021
 *      Author: uid87544
 */

#ifndef MICROCONTROLLER_WDG_WDG_H_
#define MICROCONTROLLER_WDG_WDG_H_

#define WGD_CHECK_POINT_500ms     ((uint8)0)
#define WGD_CHECK_POINT_100ms     ((uint8)1)


void Wdg_Init(void);

void Wdg_Feed(uint8 check_point);

#endif /* MICROCONTROLLER_WDG_WDG_H_ */
