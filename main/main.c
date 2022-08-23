#include 	<stdio.h>
#include	<string.h>
#include	"esp_event_loop.h"	//	for usleep

#include	"neopixel.h"
#include	<esp_log.h>

#define	NEOPIXEL_PORT	25
#define	NR_LED		10
//#define	NR_LED		3
#define	NEOPIXEL_WS2812
//#define	NEOPIXEL_SK6812
#define	NEOPIXEL_RMT_CHANNEL		RMT_CHANNEL_2

	pixel_settings_t px;
	uint32_t		pixels[NR_LED];

static	void
intialise_neopixel()
{

	int		i;
	int		rc;

	rc = neopixel_init(NEOPIXEL_PORT, NEOPIXEL_RMT_CHANNEL);
	ESP_LOGE("main", "neopixel_init rc = %d", rc);
	usleep(1000*1000);

	for	( i = 0 ; i < NR_LED ; i ++ )	{
		pixels[i] = 0;
	}
	px.pixels = (uint8_t *)pixels;
	px.pixel_count = NR_LED;
#ifdef	NEOPIXEL_WS2812
	strcpy(px.color_order, "GRB");
#else
	strcpy(px.color_order, "GRBW");
#endif

	memset(&px.timings, 0, sizeof(px.timings));
	px.timings.mark.level0 = 1;
	px.timings.space.level0 = 1;
	px.timings.mark.duration0 = 12;
#ifdef	NEOPIXEL_WS2812
	px.nbits = 24;
	px.timings.mark.duration1 = 14;
	px.timings.space.duration0 = 7;
	px.timings.space.duration1 = 16;
	px.timings.reset.duration0 = 600;
	px.timings.reset.duration1 = 600;
#endif
#ifdef	NEOPIXEL_SK6812
	px.nbits = 32;
	px.timings.mark.duration1 = 12;
	px.timings.space.duration0 = 6;
	px.timings.space.duration1 = 18;
	px.timings.reset.duration0 = 900;
	px.timings.reset.duration1 = 900;
#endif
	px.brightness = 0x80;
	np_show(&px, NEOPIXEL_RMT_CHANNEL);

	

}

void red()
{
		for	( int j = 0 ; j < NR_LED ; j ++ )	
		{
			np_set_pixel_rgbw(&px, j , 255, 0, 0, 0);
		}
		np_show(&px, NEOPIXEL_RMT_CHANNEL);
	     
}

void blue()
{
		for	( int j = 0 ; j < NR_LED ; j ++ )	
		{
			np_set_pixel_rgbw(&px, j , 0, 0, 255, 0);
		}
		np_show(&px, NEOPIXEL_RMT_CHANNEL);
	     
}

void green()
{
		for	( int j = 0 ; j < NR_LED ; j ++ )	
		{
			np_set_pixel_rgbw(&px, j , 0, 255, 0, 0);
		}
		np_show(&px, NEOPIXEL_RMT_CHANNEL);
	     
}

void amber()
{
		for	( int j = 0 ; j < NR_LED ; j ++ )	
		{
			np_set_pixel_rgbw(&px, j , 255, 198, 0, 0);
		}
		np_show(&px, NEOPIXEL_RMT_CHANNEL);
	     
}

extern	void
app_main (void)
{
	intialise_neopixel();
	while (1) {
		usleep(50000*10);
		//ESP_LOGE("main", "fact = %d", fact)
		red();
usleep(50000*10);
blue();
usleep(50000*10);
green();
usleep(50000*10);
amber();
	}
}

