#include <datetime.h>

/*void RTC_init()
{
	_enable_irq(RTC_IRQ);
}*/

u8 is_updating()
{
	return get_RTC_register(0xA) & 0x80;
}

u8 get_RTC_register(u32 reg)
{
	u8 ret;
	__asm__ ("cli");

	outportb(CMOS_CMD, reg);
	ret = inportb(CMOS_DATA);

	__asm__ ("sti");

	return ret;
}

u32 wait_RTC(RTC_DATETIME *rtc)
{
	while ( is_updating() ); 
	rtc->second		=	get_RTC_register(REG_SECOND);
	rtc->minute		=	get_RTC_register(REG_MINUTE);
	rtc->hour		=	get_RTC_register(REG_HOUR);
	rtc->day		=	get_RTC_register(REG_DAY);
	rtc->month		=	get_RTC_register(REG_MONTH);
	rtc->year		=	get_RTC_register(REG_YEAR);

	return 0;
}

u32 get_RTC(RTC_DATETIME *rtc)
{
	RTC_DATETIME last_rtc ;
	u8 register_b;

	wait_RTC(rtc);
	do {
		mcpy((u8 *)&last_rtc , (u8 *)rtc, sizeof(RTC_DATETIME));
		wait_RTC(rtc);

	} while (mcmp((u8 *)rtc, (u8 *)&last_rtc , sizeof(RTC_DATETIME)));

	register_b = get_RTC_register(0xB);

	if ( !(register_b & 0x04) )
		BCD2BIN(rtc);

	return 0;
}


u32 BCD2BIN(RTC_DATETIME *rtc)
{
	rtc->second		=	(rtc->second & 0x0F) + rtc->second / 16 * 10;
	rtc->minute		=	(rtc->minute & 0x0F) + rtc->minute / 16 * 10;
	rtc->hour		=	(rtc->hour & 0x0F) + ((rtc->hour & 0x70) / 16 * 10) | (rtc->hour & 0x80);
	rtc->day		=	(rtc->day & 0x0F) + rtc->day / 16 * 10;
	rtc->month		=	(rtc->month & 0x0F) + rtc->month / 16 * 10;
	rtc->year		=	(rtc->year & 0x0F) + rtc->year / 16 * 10;

	return 0;
}