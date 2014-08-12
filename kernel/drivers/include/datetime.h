#ifndef DATETIME_H
#define DATETIME_H

#include <port.h>
#include <string.h>
#include <pic8259.h>

#define RTC_IRQ			(0x08)

#define CMOS_CMD		(0x70)
#define CMOS_DATA		(0x71)

#define REG_SECOND		(0x00)
#define REG_MINUTE		(0x02)
#define REG_HOUR		(0x04)
#define REG_DAY			(0x07)
#define REG_MONTH		(0x08)
#define REG_YEAR		(0x09)

typedef struct 
{
	u8 second;
	u8 minute;
	u8 hour;
	u8 day;
	u8 month;
	u8 year;
	u8 century;

} __attribute__((packed)) RTC_DATETIME;

// void RTC_init();

u8 is_updating();

u8 get_RTC_register(u32 reg); 

/**
 * Wait for non-updating state and copy the date time register value.
 * @param  rtc [description]
 * @return     status
 */
u32 wait_RTC(RTC_DATETIME *rtc);

/**
 * Get RTC value without inconsistant by waiting two non-updating state and same value read.
 * @param  rtc [description]
 * @return     [description]
 */
u32 get_RTC(RTC_DATETIME *rtc);

/**
 * Convert the BCD coding RTC value to binary presentation.
 * @param  rtc [description]
 * @return     [description]
 */
u32 BCD2BIN(RTC_DATETIME *rtc);


#endif