#pragma once
#include<string.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include "TextLCD_Buffer.h"
#include "TOUR.h"
#define	DDR_PUSH_BUTTON	DDRA
#define	INPUT_PUSH_BUTTON	PINA
#define	SECOND(s)	(s*TIMER3_FRAMES_PER_SECOND)
#define GAME_SPEED		SECOND(4) // 4ÃÊ.
#define EFFECT_INDEX	10
#define DANCE_INDEX		1
#define SCORE_INDEX		34
#define OVER_INDEX		35
#define NUMBERS_INDEX	20
#define HEART_INDEX		31
#define MAX_HEART	8
#define COMBO_INDEX		0
#define MNOTE_INDEX		33
#define MNOTE_CHECKED_INDEX	37
#define MNOTE_NONE_INDEX	38
#define MNOTE_NONE_CHECKED_INDEX	39
#define TIMER_RESET		(TIMER3_current_frame = 0)
#define DANCE(p)	(	\
			me_dance_num = p+DANCE_INDEX,\
			me->idx_bitmap = me_dance_num,\
			OLED_INVALIDATE_OBJECT_SIMPLE(me),	\
			OLED_INVALIDATE()\
		)
#define COMDANCE(p)	(	\
			com_dance_num = p+DANCE_INDEX,\
			com->idx_bitmap = com_dance_num,\
			OLED_INVALIDATE_OBJECT_SIMPLE(com),	\
			OLED_INVALIDATE()		\
		)
#define MNOTE_SET_SUB(a,b)	( (a)->idx_bitmap = (b)!=0 ? MNOTE_INDEX : 0, OLED_INVALIDATE_OBJECT_SIMPLE(a),OLED_INVALIDATE())
#define MNOTE_SET(arr,dance)	(\
		MNOTE_SET_SUB((arr)[0],(dance)[0]),	\
		MNOTE_SET_SUB((arr)[1],(dance)[1]),	\
		MNOTE_SET_SUB((arr)[2],(dance)[2]),	\
		MNOTE_SET_SUB((arr)[3],(dance)[3]),	\
		MNOTE_SET_SUB((arr)[4],(dance)[4]),	\
		MNOTE_SET_SUB((arr)[5],(dance)[5]),	\
		MNOTE_SET_SUB((arr)[6],(dance)[6]),	\
		MNOTE_SET_SUB((arr)[7],(dance)[7]),	\
		)
#define MNOTE_CLEAR(arr)	(\
			OBJECT_HIDE(arr[0]),\
			OBJECT_HIDE(arr[1]),\
			OBJECT_HIDE(arr[2]),\
			OBJECT_HIDE(arr[3]),\
			OBJECT_HIDE(arr[4]),\
			OBJECT_HIDE(arr[5]),\
			OBJECT_HIDE(arr[6]),\
			OBJECT_HIDE(arr[7])	\
		)
#define MNOTE_CHECK(a,b)	(\
			(a)->idx_bitmap = (b) ? MNOTE_CHECKED_INDEX : MNOTE_NONE_CHECKED_INDEX,	\
			OLED_INVALIDATE_OBJECT_SIMPLE(a),\
			OLED_INVALIDATE()	\
			)
#define MNOTE_UNCHECK(a,b)	(\
			(a)->idx_bitmap = (b) ? MNOTE_INDEX : MNOTE_NONE_INDEX,	\
			OLED_INVALIDATE_OBJECT_SIMPLE(a),\
			OLED_INVALIDATE()	\
			)
#define GAME_OVER	6
#define CHECK_TIME(t)	(TIMER3_current_frame >= (t))
#define PUSHED	(btn_input != before_btn_input)
#define GAME_STOPPED	0
#define GAME_READY		1
#define	GAME_START		2
#define GAME_COMDANCE	3
#define GAME_DANCE		4
#define AFTER(f)	(TIMER3_current_frame+(f))
#define GAME_SCORE_ANIMATION	5
#define OBJECT_HIDE(obj) ( obj->idx_bitmap = 0, OLED_INVALIDATE_OBJECT_SIMPLE(obj),OLED_INVALIDATE())
#define BITMAP_INIT(num,pic,col)	(	\
			bitmaps_OLED[(num)].ptr_data = (prog_uint16_t*)pic,\
			bitmaps_OLED[(num)].width = WIDTH_##pic,	\
			bitmaps_OLED[(num)].height = HEIGHT_##pic,	\
			bitmaps_OLED[(num)].color=col			)
#define TICKS_PER_FRAME	0x80
#define PRINT(line,pos,text) memcpy((char*)(buffer_LCD+(line*16+pos)),text,strlen(text))
void game_stopped();
void game_ready();
void game_start();
void game_comdance();
void game_dance();
void game_over();
void game_animation();
unsigned char nstate = 0;
void	clearLCD(char,char,char);

unsigned char P1[] ={	'T', 255,

						'O', 6, 'C', 4, '$'	




						};

unsigned char P2[] ={	'T', 255,

						'O', 6, 'D', 4, '$'	




						};

unsigned char P3[] ={	'T', 255,

						'O', 6, 'E', 4, '$'	




						};

unsigned char P4[] ={	'T', 255,

						'O', 6, 'F', 4, '$'	




						};

unsigned char P5[] ={	'T', 255,

						'O', 6, 'G', 4, '$'	




						};




unsigned char P6[] ={	'T', 255,

						'O', 6, 'F', 4, '$'	




						};

unsigned char WRONG[] ={	'T', 255,

						'O', 3, 'B', 4, '$'	




						};







//±â»Ú´Ù ±¸ÁÖ¿À¼Ì³×
unsigned char stopped_bgsound[]={	'T', 26,
	'O', 6,
	'C', 4, 'R', 4,	'O', 5, 'B', 6, 'A', 2,	'G', 12, 'F', 4,
	'E', 6, 'R', 2, 'D', 6, 'R', 2, 'C', 4, 'R', 8, 'G', 4,
	'A', 8, 'R', 4, 'A', 4, 'B', 8, 'R', 4, 'B', 4,
	'O', 6, 'C', 24, 'R', 4, 'C', 3, 'R', 1,
	'C', 4, 'O', 5, 'B', 2, 'R', 2, 'A', 2, 'R', 2, 'G', 2, 'R', 2, 'G', 6, 'F', 2, 'E', 2, 'R', 2, 'O', 6, 'C', 3, 'R', 1,
	'C', 4, 'O', 5, 'B', 2, 'R', 2, 'A', 2, 'R', 2, 'G', 2, 'R', 2, 'G', 6, 'F', 2, 'E', 2, 'R', 2, 'E', 3, 'R', 1,
	'E', 2, 'R', 2, 'E', 2, 'R', 2, 'E', 2, 'R', 2, 'E', 2, 'F', 2, 'G', 8, 'R', 4, 'F', 2, 'E', 2,
	'D', 2, 'R', 2, 'D', 2, 'R', 2, 'D', 2, 'R', 2, 'D', 2, 'E', 2, 'F', 8, 'R', 4, 'E', 2, 'D', 2,
	'C', 2, 'R', 2, 'O', 6, 'C', 8, 'O', 5, 'A', 2, 'R', 2, 'G', 6, 'F', 2, 'E', 2, 'R', 2, 'F', 2, 'R', 2,
	'E', 2, 'R', 6, 'D', 2, 'R', 6, 'C', 2, 'R', 14,
	'$'};




/*  Å¬·ÎÂ¡ »£»£»£ºü~~~ */

unsigned char close[]={	'T',26,

							'O', 5, 'G', 3, 'R', 1,'G', 3, 'R', 1,'G', 3,'R', 1,'I', 25, 'R', 3, 'F', 3, 'R', 1, 'F', 3, 'R', 1,'F', 3, 'R', 1, 'D', 25, '$'

	

						};

/* Æ²·ÈÀ» ¶§ È¿°úÀ½!! */

unsigned char hyogwa[] = {		'T', 26,

								 'U', 5, 'L', 3, 'L', 10, '$'

						};	

unsigned char* effect_sounds[]={
	P1,P2,P3,P4,P5,P6
};
