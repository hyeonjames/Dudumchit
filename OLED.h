/*
	2013년 가을학기 마이크로프로세서응용

	OLED.h

	실습 키트의 128x128 OLED를 조작하기 위해 라이브러리에서 사용하는 여러 요소들이 들어 있습니다.

	----------------------------------------- 주의 -----------------------------------------
	학생 여러분은 이 파일을 전혀 네버 절대로 신경쓰지 않아도 됩니다.
	대신, 별도로 마련된 OLED_modify_me_but_do_not_include_me.h에 있는 내용만 잘 읽은 다음
	해당 파일에 설명된 매크로 함수들, OLED_Object 구조체 멤버 변수들만 적절히 바꾸면서 쓰면 됩니다.
	----------------------------------------------------------------------------------------
*/

#include <avr/io.h>
#include <avr/pgmspace.h>

#pragma once

#include "OLED_modify_me_but_do_not_include_me.h"


/*
	----------------------------------------------------------------------
	이 아래의 내용을 수정하는 경우 경미하거나 심각한 오작동을 일으킬 수 있으니
	혹시나 여러분의 프로그램에서 미세한 튜닝 작업이 필요한 경우
	반드시 먼저 조교에게 진찰을 의뢰하세요.
	----------------------------------------------------------------------
*/

/*
	----------------------------------------------------------------------
	OLED module 인터페이스 관련 부분
	----------------------------------------------------------------------
*/

/* OLED control flag별 핀 위치 정의 */
#define OLED_FLAG_CS	0b00001
#define OLED_FLAG_RST	0b00010
#define OLED_FLAG_DC	0b00100
#define OLED_FLAG_RW	0b01000
#define OLED_FLAG_E		0b10000

/* 해당 flag의 bit를 1로 만듦(다른 bit는 그대로 둠) */
#define OLED_SET_FLAG(name) 	( PORT_OLED_CTRL |= OLED_FLAG_##name )

/* 해당 flag의 bit를 0으로 만듦(다른 bit는 그대로 둠) */
#define OLED_CLR_FLAG(name)		( PORT_OLED_CTRL &= ~OLED_FLAG_##name )

/* OLED module을 조작하기 위한 명령어 일람 - 각 명령어의 의미는 datasheet 참고 -> 몰라도 됨 */
#define OLED_CMD_NOP		0x00
#define OLED_CMD_SWRESET	0x01
#define OLED_CMD_SLPIN		0x10
#define OLED_CMD_SLPOUT		0x11
#define OLED_CMD_PTLON		0x12
#define OLED_CMD_NORON		0x13
#define OLED_CMD_INVOFF		0x20
#define OLED_CMD_INVON		0x21
#define OLED_CMD_ALLPON		0x23
#define OLED_CMD_ALLPOFF	0x28
#define OLED_CMD_DISPON		0x29
#define OLED_CMD_CASET		0x2A
#define OLED_CMD_RASET		0x2B
#define OLED_CMD_RAMWR		0x2C
#define OLED_CMD_PLTAR		0x30
#define OLED_CMD_VSCRDEF	0x33
#define OLED_CMD_TEOFF		0x34
#define OLED_CMD_TEON		0x35
#define OLED_CMD_MADCTL		0x36
#define OLED_CMD_VSCRSADD	0x37
#define OLED_CMD_COLMOD		0x3A
#define OLED_CMD_SETLUM		0x51
#define OLED_CMD_OTPWR		0xB1
#define OLED_CMD_FUSEL		0xB3
#define OLED_CMD_LINGLUT	0xB9
#define OLED_CMD_ISEGABC	0xBA
#define OLED_CMD_VPSET		0xBD
#define OLED_CMD_GLUT		0xBE
#define OLED_CMD_SETDO		0xC8
#define OLED_CMD_HORSCR		0xC9
#define OLED_CMD_SETMUX		0xCA
#define OLED_CMD_PHLEN		0xCD
#define OLED_CMD_SECPLEN	0xCE
#define OLED_CMD_SSPS		0xCF
#define OLED_CMD_SDCOSCF	0xD2
#define OLED_CMD_SETVCOMH	0xD3
#define OLED_CMD_GPIO		0xD7
#define OLED_CMD_COMLOK		0xFD

#if OLED_2010_MODE == 0

/* OLED에 해당 명령어를 보내는 매크로 함수 */
#define OLED_WRITE_COMMAND(cmd)															\
		do																				\
		{																				\
			PORT_OLED_CTRL = OLED_FLAG_RST | OLED_FLAG_E;								\
			PORT_OLED_DATA = OLED_CMD_##cmd;											\
			asm("NOP");																	\
			PORT_OLED_CTRL = OLED_FLAG_CS | OLED_FLAG_RST | OLED_FLAG_RW | OLED_FLAG_E;	\
		}																				\
		while ( 0 )

#else

/* OLED에 해당 명령어를 보내는 매크로 함수(구형 키트 버전) */
#define OLED_WRITE_COMMAND(cmd)															\
		do																				\
		{																				\
			PORT_OLED_CTRL = OLED_FLAG_RST | OLED_FLAG_RW | OLED_FLAG_CS | OLED_FLAG_E;	\
			PORT_OLED_CTRL = OLED_FLAG_RST | OLED_FLAG_RW | OLED_FLAG_E;				\
			PORT_OLED_CTRL = OLED_FLAG_RST | OLED_FLAG_E;								\
			PORT_OLED_DATA = OLED_CMD_##cmd;											\
			asm("NOP");																	\
			PORT_OLED_CTRL = OLED_FLAG_RST | OLED_FLAG_RW | OLED_FLAG_E;				\
			PORT_OLED_CTRL = OLED_FLAG_DC | OLED_FLAG_RST | OLED_FLAG_RW | OLED_FLAG_E;	\
			PORT_OLED_CTRL = OLED_FLAG_CS | OLED_FLAG_DC | OLED_FLAG_RST | OLED_FLAG_RW | OLED_FLAG_E;	\
		}																				\
		while ( 0 )

#endif

/* OLED에 해당 데이터(명령어의 argument)를 보내는 매크로 함수 */
#define OLED_WRITE_DATA(data)																			\
		do																								\
		{																								\
			PORT_OLED_CTRL = OLED_FLAG_RST | OLED_FLAG_DC | OLED_FLAG_E;								\
			PORT_OLED_DATA = ( data );																	\
			asm("NOP");																					\
			PORT_OLED_CTRL = OLED_FLAG_CS | OLED_FLAG_RST | OLED_FLAG_DC | OLED_FLAG_RW | OLED_FLAG_E;	\
		}																								\
		while ( 0 )

/* R, G, B 각각의 감마 값을 설정하기 위한 명령어와 argument를 보내는 매크로 함수 */
#define OLED_WRITE_GAMMA()																				\
		do																								\
		{																								\
			OLED_WRITE_COMMAND(GLUT);																	\
																										\
			OLED_WRITE_DATA(0x01); OLED_WRITE_DATA(0x04); OLED_WRITE_DATA(0x07); OLED_WRITE_DATA(0x09);	\
			OLED_WRITE_DATA(0x0B); OLED_WRITE_DATA(0x0C); OLED_WRITE_DATA(0x0D); OLED_WRITE_DATA(0x0E);	\
			OLED_WRITE_DATA(0x0F); OLED_WRITE_DATA(0x10); OLED_WRITE_DATA(0x11); OLED_WRITE_DATA(0x12);	\
			OLED_WRITE_DATA(0x13); OLED_WRITE_DATA(0x16); OLED_WRITE_DATA(0x1D); OLED_WRITE_DATA(0x21);	\
			OLED_WRITE_DATA(0x23); OLED_WRITE_DATA(0x24); OLED_WRITE_DATA(0x2E); OLED_WRITE_DATA(0x31);	\
			OLED_WRITE_DATA(0x32); OLED_WRITE_DATA(0x37); OLED_WRITE_DATA(0x41); OLED_WRITE_DATA(0x43);	\
			OLED_WRITE_DATA(0x4C); OLED_WRITE_DATA(0x51); OLED_WRITE_DATA(0x54); OLED_WRITE_DATA(0x61);	\
			OLED_WRITE_DATA(0x68); OLED_WRITE_DATA(0x6F); OLED_WRITE_DATA(0x75); OLED_WRITE_DATA(0x7F);	\
																										\
			OLED_WRITE_DATA(0x01); OLED_WRITE_DATA(0x08); OLED_WRITE_DATA(0x0E); OLED_WRITE_DATA(0x13);	\
			OLED_WRITE_DATA(0x17); OLED_WRITE_DATA(0x1A); OLED_WRITE_DATA(0x1C); OLED_WRITE_DATA(0x1E);	\
			OLED_WRITE_DATA(0x1F); OLED_WRITE_DATA(0x20); OLED_WRITE_DATA(0x21); OLED_WRITE_DATA(0x22);	\
			OLED_WRITE_DATA(0x23); OLED_WRITE_DATA(0x25); OLED_WRITE_DATA(0x2B); OLED_WRITE_DATA(0x30);	\
			OLED_WRITE_DATA(0x31); OLED_WRITE_DATA(0x33); OLED_WRITE_DATA(0x37); OLED_WRITE_DATA(0x39);	\
			OLED_WRITE_DATA(0x41); OLED_WRITE_DATA(0x43); OLED_WRITE_DATA(0x47); OLED_WRITE_DATA(0x50);	\
			OLED_WRITE_DATA(0x52); OLED_WRITE_DATA(0x55); OLED_WRITE_DATA(0x61); OLED_WRITE_DATA(0x63);	\
			OLED_WRITE_DATA(0x64); OLED_WRITE_DATA(0x70); OLED_WRITE_DATA(0x74); OLED_WRITE_DATA(0x7F);	\
																										\
			OLED_WRITE_DATA(0x01); OLED_WRITE_DATA(0x04); OLED_WRITE_DATA(0x07); OLED_WRITE_DATA(0x09);	\
			OLED_WRITE_DATA(0x0B); OLED_WRITE_DATA(0x0C); OLED_WRITE_DATA(0x0D); OLED_WRITE_DATA(0x0E);	\
			OLED_WRITE_DATA(0x0F); OLED_WRITE_DATA(0x10); OLED_WRITE_DATA(0x11); OLED_WRITE_DATA(0x12);	\
			OLED_WRITE_DATA(0x13); OLED_WRITE_DATA(0x16); OLED_WRITE_DATA(0x1E); OLED_WRITE_DATA(0x21);	\
			OLED_WRITE_DATA(0x22); OLED_WRITE_DATA(0x25); OLED_WRITE_DATA(0x2D); OLED_WRITE_DATA(0x30);	\
			OLED_WRITE_DATA(0x32); OLED_WRITE_DATA(0x37); OLED_WRITE_DATA(0x41); OLED_WRITE_DATA(0x43);	\
			OLED_WRITE_DATA(0x4C); OLED_WRITE_DATA(0x51); OLED_WRITE_DATA(0x56); OLED_WRITE_DATA(0x62);	\
			OLED_WRITE_DATA(0x69); OLED_WRITE_DATA(0x70); OLED_WRITE_DATA(0x77); OLED_WRITE_DATA(0x7F);	\
		}																								\
		while ( 0 )

/* 배경색 R, G, B 설정을 바탕으로 16bit format으로 구성한 배경색 데이터 */
#define OLED_BGCOLOR_HIGH	( ( OLED_BGCOLOR_R << 3 ) | ( OLED_BGCOLOR_G >> 3 ) )
#define OLED_BGCOLOR_LOW	( ( ( OLED_BGCOLOR_G & 0b111 ) << 5 ) | OLED_BGCOLOR_B )

/* 전체 화면을 배경색으로 칠하는 매크로 함수 */
#define OLED_CLEAR_SCREEN()										\
		do														\
		{														\
			register unsigned char row;							\
			register unsigned char column;						\
																\
			OLED_WRITE_COMMAND(CASET);							\
			OLED_WRITE_DATA(0);									\
			OLED_WRITE_DATA(127);								\
																\
			OLED_WRITE_COMMAND(RASET);							\
			OLED_WRITE_DATA(0);									\
			OLED_WRITE_DATA(127);								\
																\
			OLED_WRITE_COMMAND(RAMWR);							\
			for ( row = 0; row < 128; ++row )					\
				for ( column = 0; column < 128; ++column )		\
				{												\
					OLED_WRITE_DATA(OLED_BGCOLOR_HIGH);			\
					OLED_WRITE_DATA(OLED_BGCOLOR_LOW);			\
				}												\
		}														\
		while ( 0 )

/* OLED module을 사용하기 위한 초기화 작업을 수행하는 매크로 함수 */
#define OLED_INITIALIZE()														\
		do																		\
		{																		\
			register unsigned char i;											\
																				\
			DDR_OLED_CTRL = 0xFF;												\
			DDR_OLED_DATA = 0xFF;												\
																				\
			PORT_OLED_CTRL = 0b11111;											\
			PORT_OLED_DATA = 0;													\
																				\
			OLED_CLR_FLAG(RST);													\
																				\
			for ( i = 0; i < OLED_MAX_Z_INDEX; ++i )							\
			{																	\
				z_heads_OLED[i] = 0;											\
				z_tails_OLED[i] = 0;											\
			}																	\
																				\
			current_object_OLED = &objects_OLED[0];								\
			unused_objects_OLED = &objects_OLED[OLED_MAX_NUMBER_OF_OBJECTS - 1];\
																				\
			current_object_OLED->previous = unused_objects_OLED;				\
			current_object_OLED->next = current_object_OLED + 1;				\
																				\
			unused_objects_OLED->previous = unused_objects_OLED - 1;			\
			unused_objects_OLED->next = current_object_OLED;					\
			++current_object_OLED;												\
																				\
			while ( current_object_OLED != unused_objects_OLED )				\
			{																	\
				current_object_OLED->previous = current_object_OLED - 1;		\
				current_object_OLED->next = current_object_OLED + 1;			\
				++current_object_OLED;											\
			}																	\
																				\
			current_object_OLED = 0;											\
																				\
			OLED_SET_FLAG(RST);													\
																				\
			OLED_WRITE_COMMAND(SWRESET);										\
			OLED_WRITE_COMMAND(COMLOK);											\
			OLED_WRITE_DATA(0x12);												\
			OLED_WRITE_COMMAND(COMLOK);											\
			OLED_WRITE_DATA(0xB3);												\
			OLED_WRITE_COMMAND(SLPIN);											\
																				\
			OLED_WRITE_COMMAND(SDCOSCF);										\
			OLED_WRITE_DATA(0x10);												\
																				\
			OLED_WRITE_COMMAND(SETMUX);											\
			OLED_WRITE_DATA(0x7F);												\
																				\
			OLED_WRITE_COMMAND(SETDO);											\
			OLED_WRITE_DATA(0x00);												\
																				\
			OLED_WRITE_COMMAND(MADCTL);											\
			OLED_WRITE_DATA(0x88);												\
			OLED_WRITE_DATA(0x01);												\
																				\
			OLED_WRITE_COMMAND(COLMOD);											\
			OLED_WRITE_DATA(0x05);												\
																				\
			OLED_WRITE_COMMAND(TEON);											\
			OLED_WRITE_DATA(0x01);												\
																				\
			OLED_WRITE_COMMAND(FUSEL);											\
			OLED_WRITE_DATA(0x03);												\
																				\
			OLED_WRITE_COMMAND(ISEGABC);										\
			OLED_WRITE_DATA(0xC3);												\
			OLED_WRITE_COMMAND(ISEGABC + 1);									\
			OLED_WRITE_DATA(0x55);												\
			OLED_WRITE_COMMAND(ISEGABC + 2);									\
			OLED_WRITE_DATA(0x87);												\
																				\
			OLED_WRITE_COMMAND(SETLUM);											\
			OLED_WRITE_DATA(0xF0);												\
																				\
			OLED_WRITE_GAMMA();													\
																				\
			OLED_WRITE_COMMAND(PHLEN);											\
			OLED_WRITE_DATA(0x32);												\
																				\
			OLED_WRITE_COMMAND(VPSET);											\
			OLED_WRITE_DATA(0x09);												\
																				\
			OLED_WRITE_COMMAND(SECPLEN);										\
			OLED_WRITE_DATA(0x0B);												\
																				\
			OLED_WRITE_COMMAND(SSPS);											\
			OLED_WRITE_DATA(0x03);												\
																				\
			OLED_WRITE_COMMAND(SETVCOMH);										\
			OLED_WRITE_DATA(0x04);												\
																				\
			OLED_WRITE_COMMAND(DISPON);											\
			OLED_WRITE_COMMAND(INVOFF);											\
			OLED_WRITE_COMMAND(NORON);											\
			OLED_WRITE_COMMAND(SLPOUT);											\
																				\
			OLED_CLEAR_SCREEN();												\
		}																		\
		while ( 0 )


/*
	----------------------------------------------------------------------
	OLED 라이브러리 관련 부분
	----------------------------------------------------------------------
*/

/* 이미지 비트맵 하나에 대한 정보를 담는 구조체 */
struct OLED_Bitmap
{
	prog_uint16_t *ptr_data;
	unsigned char width;
	unsigned char height;
	unsigned int color;
};

/* 화면에 그릴 어떤 물체 하나에 대한 정보를 담는 구조체 */
struct OLED_Object
{
	/* 이 object를 그릴 때 사용할 비트맵 번호 */
	unsigned char idx_bitmap;

	/* 이 object가 위치할 좌측 상단 좌표 */
	unsigned char left;
	unsigned char top;

	/* 이 object가 위치할 우측 하단 좌표(scalable flag가 1일 때만 사용) */
	unsigned char right;
	unsigned char bottom;

	/*
		이 아래에 있는 변수들은 OLED 라이브러리 내부에서 조작하므로
		전혀 신경쓰지 않아도 좋으며
		오히려 임의로 수정하면 오작동의 원인이 될 수 있습니다.
	*/

	/* 아래에 적힌 flag들을 모아 놓은 변수 */
	unsigned char flags;

	/* visible flag가 1일 때 이 object가 현재 그려진 화면상의 좌표 */
	unsigned char rendered_left;
	unsigned char rendered_top;
	unsigned char rendered_right;
	unsigned char rendered_bottom;

	/* 자료구조 유지를 위해 사용하는 추가 포인터 변수들 */
	struct OLED_Object* previous;
	struct OLED_Object* next;
};

/*
	flag list:

		0b76543210
		  csvrfhdi
	
		i: invalidated - 이 object를 다시 그려야 함을 의미
		d: delete triggered - 이 object를 완전히 제거해야 함을 의미
		h: hide triggered - 이 object를 화면에서 지워야 함을 의미
		f: freeze triggered - 이 object를 invalidation chain에 영향을 받거나 주지 않도록 만들어야 함을 의미

		r: frozen - 이 object가 invalidation chain에 영향을 받거나 주지 않음을 의미
		v: visible - 이 object가 현재 화면에 표시되어 있음을 의미
		s: scalable - 이 object를 그릴 때 확대 / 축소 기능을 사용해서 그리도록 설정되어 있음을 의미
		c: invalidation chain checked - invalidation chain 계산 과정에서만 사용하는 flag, 이 object가 invalidation chaining을 이미 한 번 수행했음을 의미
*/
#define OLED_OBJECT_FLAG_INVALIDATED				0b00000001
#define	OLED_OBJECT_FLAG_DELETE_TRIGGERED			0b00000010
#define OLED_OBJECT_FLAG_HIDE_TRIGGERED				0b00000100
#define OLED_OBJECT_FLAG_FREEZE_TRIGGERED			0b00001000
#define OLED_OBJECT_FLAG_FROZEN						0b00010000
#define OLED_OBJECT_FLAG_VISIBLE					0b00100000
#define OLED_OBJECT_FLAG_SCALABLE					0b01000000
#define OLED_OBJECT_FLAG_INVALIDATION_CHAIN_CHECKED	0b10000000


extern struct OLED_Bitmap bitmaps_OLED[OLED_NUMBER_OF_BITMAPS];

extern struct OLED_Object objects_OLED[OLED_MAX_NUMBER_OF_OBJECTS];
extern struct OLED_Object* z_heads_OLED[OLED_MAX_Z_INDEX + 1];
extern struct OLED_Object* z_tails_OLED[OLED_MAX_Z_INDEX + 1];

extern struct OLED_Object* unused_objects_OLED;

extern struct OLED_Object* first_object_OLED;
extern struct OLED_Object* current_object_OLED;


#define OLED_TRG_CREATED			0b00000001
#define OLED_TRG_INVALIDATED		0b00000010
#define OLED_TRG_REFRESH_REQUESTED	0b00000100
#define OLED_TRG_COMPLETED			0b10000000

extern unsigned char triggers_OLED;

/*
	주어진 z_index와 그리기 속성을 가진 새로운 object를 생성하고 포인터를 반환
*/
#define OLED_CREATE_OBJECT(z_index, isScalable)													\
		(																						\
			current_object_OLED = unused_objects_OLED,											\
																								\
			unused_objects_OLED->next == 0 ?													\
			(																					\
				unused_objects_OLED = 0															\
			) :																					\
			(																					\
				unused_objects_OLED->previous->next = unused_objects_OLED->next,				\
				unused_objects_OLED->next->previous = unused_objects_OLED->previous,			\
				unused_objects_OLED = unused_objects_OLED->next									\
			),																					\
																								\
			z_tails_OLED[(z_index)] == 0 ?														\
			(																					\
				current_object_OLED->previous = current_object_OLED,							\
				current_object_OLED->next = current_object_OLED,								\
				z_heads_OLED[(z_index)] = current_object_OLED									\
			) :																					\
			(																					\
				current_object_OLED->previous = z_tails_OLED[(z_index)],						\
				current_object_OLED->next = z_tails_OLED[(z_index)]->next,						\
				z_tails_OLED[(z_index)]->next->previous = current_object_OLED,					\
				z_tails_OLED[(z_index)]->next = current_object_OLED								\
			),																					\
																								\
			z_tails_OLED[(z_index)] = current_object_OLED,										\
																								\
			current_object_OLED->flags = (isScalable) ? OLED_OBJECT_FLAG_SCALABLE : 0,			\
																								\
			triggers_OLED |= OLED_TRG_CREATED,													\
																								\
			current_object_OLED																	\
		)

/*
	flag list:

		0b76543210
		  csvrfhdi
	
		i: invalidated - 이 object를 다시 그려야 함을 의미
		d: delete triggered - 이 object를 완전히 제거해야 함을 의미
		h: hide triggered - 이 object를 화면에서 지워야 함을 의미
		f: freeze triggered - 이 object를 invalidation chain에 영향을 받거나 주지 않도록 만들어야 함을 의미

		r: frozen - 이 object가 invalidation chain에 영향을 받거나 주지 않음을 의미
		v: visible - 이 object가 현재 화면에 표시되어 있음을 의미
		s: scalable - 이 object를 그릴 때 확대 / 축소 기능을 사용해서 그리도록 설정되어 있음을 의미
		c: invalidation chain checked - invalidation chain 계산 과정에서만 사용하는 flag, 이 object가 invalidation chain 계산에 이미 한 번 포함되었음을 의미
*/

/*
	해당 object를 화면에서 지우고 완전히 제거(frozen 상태였다면 해제됨)
*/
#define OLED_DELETE_OBJECT(ptr_object)		( ( ptr_object )->flags = ( ( ptr_object )->flags & ~OLED_OBJECT_FLAG_FROZEN ) | OLED_OBJECT_FLAG_DELETE_TRIGGERED | OLED_OBJECT_FLAG_HIDE_TRIGGERED )

/*
	해당 object를 화면에 그대로 두고 완전히 제거(frozen 상태였다면 해제되지만 별 의미는 없음)
*/
#define OLED_DELETE_OBJECT_SIMPLE(ptr_object)	( ( ptr_object )->flags = ( ( ptr_object )->flags & ~OLED_OBJECT_FLAG_FROZEN ) | OLED_OBJECT_FLAG_DELETE_TRIGGERED )

/*
	해당 object를 화면에서 지우고 freeze
*/
#define OLED_HIDE_OBJECT(ptr_object)		( ( ptr_object )->flags |= OLED_OBJECT_FLAG_HIDE_TRIGGERED | OLED_OBJECT_FLAG_FREEZE_TRIGGERED )

/*
	해당 object를 화면에 다시 표시(frozen 상태였다면 해제됨)
*/
#define OLED_SHOW_OBJECT(ptr_object)		( ( ptr_object )->flags = ( ptr_object )->flags & ~( OLED_OBJECT_FLAG_HIDE_TRIGGERED | OLED_OBJECT_FLAG_FREEZE_TRIGGERED | OLED_OBJECT_FLAG_FROZEN ) | OLED_OBJECT_FLAG_INVALIDATED )

/*
	해당 object를 다시 그리지 않도록 freeze(화면 가장자리 장식, 하늘 등을 표현하는 object인 경우 설정해 두면 됨)
*/
#define OLED_FREEZE_OBJECT(ptr_object)		( ( ptr_object )->flags |= OLED_OBJECT_FLAG_FREEZE_TRIGGERED )

/*
	해당 object를 필요시 다시 그릴 수 있도록 frozen 상태를 해제
*/
#define OLED_UNFREEZE_OBJECT(ptr_object)	( ( ptr_object )->flags = ( ptr_object )->flags & ~( OLED_OBJECT_FLAG_FROZEN | OLED_OBJECT_FLAG_FREEZE_TRIGGERED ) )

/*
	해당 object를 현재 위치에 다시 그리도록 설정(기존 위치에서 지우는 과정 생략)
*/
#define OLED_INVALIDATE_OBJECT_SIMPLE(ptr_object)	( ( ptr_object )->flags |= OLED_OBJECT_FLAG_INVALIDATED )

/*
	해당 object를 기존 위치에서 지우고 현재 위치에 다시 그리도록 설정
*/
#define OLED_INVALIDATE_OBJECT(ptr_object)	( ( ptr_object )->flags |= OLED_OBJECT_FLAG_HIDE_TRIGGERED | OLED_OBJECT_FLAG_INVALIDATED )

/*
	OLED 라이브러리가 invalidation check를 다시 할 필요성이 생겼음을 알림
*/
#define OLED_INVALIDATE()	( triggers_OLED |= OLED_TRG_INVALIDATED )

/*
	OLED 라이브러리가 화면 전체를 다시 그릴 필요성이 생겼음을 알림
*/
#define OLED_REFRESH()		( triggers_OLED |= OLED_TRG_REFRESH_REQUESTED )



/*
	TEST mode인지 아닌지에 따라 달라지는 그리기 함수.
	주의: 여러분이 이 함수를 직접 호출할 일은 없음.
*/
#if OLED_TEST == 0

/* TEST mode가 아닐 땐 실제 bitmap을 사용하여 그림 */
#define OLED_RENDER_OBJECT(ptr_object)															\
		do																						\
		{																						\
			register unsigned int write_count = 												\
				( (ptr_object)->bottom - (ptr_object)->top + 1 ) *								\
				( (ptr_object)->right - (ptr_object)->left + 1 ) / 16;							\
																								\
			register unsigned int* ptr_data = bitmaps_OLED[ptr_object->idx_bitmap].ptr_data;	\
			register unsigned int color=bitmaps_OLED[ptr_object->idx_bitmap].color;																	\
			unsigned char col_high = color>>8,col_low = color&0xFF;																				\
			char i;\
			register unsigned int bits;															\
			if(ptr_object->idx_bitmap == 0) ptr_data = NULL;										\
			OLED_WRITE_COMMAND(CASET);															\
			OLED_WRITE_DATA((ptr_object)->left);												\
			OLED_WRITE_DATA((ptr_object)->right);												\
			OLED_WRITE_COMMAND(RASET);															\
			OLED_WRITE_DATA((ptr_object)->top);													\
			OLED_WRITE_DATA((ptr_object)->bottom);												\
																								\
			OLED_WRITE_COMMAND(RAMWR);															\
			do																					\
			{																					\
				if(ptr_data != NULL){															\
					bits = pgm_read_word_near(ptr_data++);											\
					for(i=0;i<16;i++) {															\
						if(((bits>>(15-i))&0x01)){															\
							OLED_WRITE_DATA(col_high);														\
							OLED_WRITE_DATA(col_low);	\
						} else {																	\
							OLED_WRITE_DATA(0xff);													\
							OLED_WRITE_DATA(0xff);													\
						}																			\
					}																				\
				} else {																			\
					for(i=0;i<16;i++) {																\
						OLED_WRITE_DATA(0xff);														\
						OLED_WRITE_DATA(0xff);														\
					}																				\
				}																				\
			}																					\
			while ( --write_count );															\
		}																						\
		while ( 0 )

#define OLED_RENDER_OBJECT_WITH_SCALING(ptr_object)														\
		do																								\
		{																								\
			register unsigned char row = 0,i;																\
			register unsigned char column = 0;															\
																										\
			register unsigned int* ptr_data = bitmaps_OLED[ptr_object->idx_bitmap].ptr_data;			\
			register unsigned char rows_origin = bitmaps_OLED[ptr_object->idx_bitmap].height;			\
			register unsigned char columns_origin = bitmaps_OLED[ptr_object->idx_bitmap].width;			\
			register unsigned int color=bitmaps_OLED[ptr_object->idx_bitmap].color;																\
			register unsigned char col_high = color<<8,col_row = color&0xFF;																							\
			register unsigned int bits;				\
			OLED_WRITE_COMMAND(CASET);																	\
			OLED_WRITE_DATA((ptr_object)->left);														\
			OLED_WRITE_DATA((ptr_object)->right);														\
			OLED_WRITE_COMMAND(RASET);																	\
			OLED_WRITE_DATA((ptr_object)->top);															\
			OLED_WRITE_DATA((ptr_object)->bottom);														\
																										\
			OLED_WRITE_COMMAND(RAMWR);																	\
			rows_origin /= 16;																		\
			for ( row = 0; row < rows_origin;													\
				++row )							\
			{																							\
				for ( column = 0; column < columns_origin;									\
					++column ) 		\
				{																						\
					bits = *(ptr_data + row * columns_origin + column);	\
																										\
						for(i=0;i<16;i++) {																\
							if((bits >> (15-i)) & 0x01){																	\
								OLED_WRITE_DATA(col_high);															\
								OLED_WRITE_DATA(col_row);															\
							} else {																		\
								OLED_WRITE_DATA(0xff);													\
								OLED_WRITE_DATA(0xff);														\
							}																				\
						} 																					\
				}																						\
			}																							\
		}																								\
		while ( 0 )

#else

/* TEST mode일 땐 colors_OLED[]에 있는 단색들 중 하나를 사용하여 그림 */
#define OLED_RENDER_OBJECT(ptr_object)														\
		do																					\
		{																					\
			register unsigned int write_count = 											\
				( (ptr_object)->bottom - (ptr_object)->top + 1 ) *							\
				( (ptr_object)->right - (ptr_object)->left + 1 );							\
																							\
			register unsigned char color_high = colors_OLED[(ptr_object)->idx_bitmap] >> 8;	\
			register unsigned char color_low = colors_OLED[(ptr_object)->idx_bitmap];		\
																							\
			OLED_WRITE_COMMAND(CASET);														\
			OLED_WRITE_DATA((ptr_object)->left);											\
			OLED_WRITE_DATA((ptr_object)->right);											\
			OLED_WRITE_COMMAND(RASET);														\
			OLED_WRITE_DATA((ptr_object)->top);												\
			OLED_WRITE_DATA((ptr_object)->bottom);											\
																							\
			OLED_WRITE_COMMAND(RAMWR);														\
			do																				\
			{																				\
				OLED_WRITE_DATA(color_high);												\
				OLED_WRITE_DATA(color_low);													\
			}																				\
			while ( --write_count );														\
		}																					\
		while ( 0 )

/* TEST mode일 땐 모든 픽셀을 단색으로 칠하기 때문에 scaling을 굳이 계산해서 할 필요가 없음 */
#define OLED_RENDER_OBJECT_WITH_SCALING(ptr_object)		OLED_RENDER_OBJECT(ptr_object)

#endif

/*
	OLED 프레임을 돌리기 위한 거대 매크로 함수
*/
#define OLED_UPDATE()																																		\
		do																																					\
		{																																					\
			/* OLED 관련 작업이 아직 완료되지 않았거나 새 작업이 생긴 경우에만 코드 실행 */																	\
			if ( triggers_OLED != OLED_TRG_COMPLETED )																										\
			{																																				\
				triggers_OLED &= ~OLED_TRG_COMPLETED;																										\
																																							\
				/* 1. 새 object가 생성되어 object list를 갱신해야 하는 경우 */																				\
				if ( triggers_OLED & OLED_TRG_CREATED )																										\
				{																																			\
					register unsigned char index;																											\
					register unsigned char nextIndex;																										\
																																							\
					/* 각 tail이 다음 head와 연결되게 만듦 */																								\
					for ( index = 0; index <= OLED_MAX_Z_INDEX; ++index )																					\
					{																																		\
						if ( z_tails_OLED[index] != 0 )																										\
						{																																	\
							nextIndex = index + 1;																											\
																																							\
							while ( nextIndex != OLED_MAX_Z_INDEX + 1 && z_tails_OLED[nextIndex] == 0 )														\
								++nextIndex;																												\
																																							\
							/* 마지막 tail은 첫 head와 연결되게 만듦 */																						\
							if ( nextIndex == OLED_MAX_Z_INDEX + 1 )																						\
							{																																\
								nextIndex = 0;																												\
																																							\
								while ( z_tails_OLED[nextIndex] == 0 )																						\
									++nextIndex;																											\
																																							\
								z_tails_OLED[index]->next = z_heads_OLED[nextIndex];																		\
								z_heads_OLED[nextIndex]->previous = z_tails_OLED[index];																	\
																																							\
								/* 첫 head가 전체 리스트의 첫 object가 됨 */																				\
								first_object_OLED = z_heads_OLED[nextIndex];																				\
								break;																														\
							}																																\
							/* 마지막 tail이 아닌 경우 방금 찾은 다음 head와 연결되게 만듦 */																\
							else																															\
							{																																\
								z_tails_OLED[index]->next = z_heads_OLED[nextIndex];																		\
								z_heads_OLED[nextIndex]->previous = z_tails_OLED[index];																	\
							}																																\
						}																																	\
					}																																		\
																																							\
					/* object 포인터 리셋 - 다음 OLED 프레임에서 그리기를 처음부터 할 수 있게 */															\
					current_object_OLED = first_object_OLED;																								\
																																							\
					triggers_OLED &= ~OLED_TRG_CREATED;																										\
				}																																			\
																																							\
				/* 2. 전체 화면 다시 그리기 요청을 받은 경우  */																							\
				else if ( triggers_OLED & OLED_TRG_REFRESH_REQUESTED )																						\
				{																																			\
					/* 먼저 전체 화면을 배경색으로 채움 */																									\
					OLED_CLEAR_SCREEN();																													\
																																							\
					/* 현재 object가 1개 이상일 때만 다시 그리기 수행 */																					\
					if ( first_object_OLED != 0 )																											\
					{																																		\
						/* 모든 visible and not frozen object를 invalidate하고 object 포인터 리셋 */														\
						current_object_OLED = first_object_OLED;																							\
																																							\
						do																																	\
						{																																	\
							if ( ( current_object_OLED->flags & ( OLED_OBJECT_FLAG_VISIBLE | OLED_OBJECT_FLAG_FROZEN ) ) == OLED_OBJECT_FLAG_VISIBLE )		\
								OLED_INVALIDATE_OBJECT_SIMPLE(current_object_OLED);																			\
							current_object_OLED = current_object_OLED->next;																				\
						}																																	\
						while ( current_object_OLED != first_object_OLED );																					\
					}																																		\
																																							\
					/* refresh 요청을 처리하면서 모든 object를 invalidate시켰으므로 */																		\
					/* 굳이 chain 계산을 할 필요가 없어짐 -> INVALIDATED flag도 같이 clear */																\
					triggers_OLED &= ~( OLED_TRG_REFRESH_REQUESTED | OLED_TRG_INVALIDATED );																\
				}																																			\
																																							\
				/* 3. invalidation chain을 다시 계산해야 하는 경우 */																						\
				else if ( triggers_OLED & OLED_TRG_INVALIDATED )																							\
				{																																			\
					/* 현재 object가 1개 이상일 때만 chaining 수행 */																						\
					if ( first_object_OLED != 0 )																											\
					{																																		\
						register unsigned char check_completed;																								\
						register struct OLED_Object* pos_chaining_object;																					\
																																							\
						do																																	\
						{																																	\
							check_completed = 1;																											\
																																							\
							/* 3-1. 모든 ( invalidated or hide triggered ) and not ( frozen or checked ) object에 대해 */									\
							/* 해당 object와 겹치는 모든 visible and not ( frozen or hide triggered or checked ) object들을 invalidate */					\
							current_object_OLED = first_object_OLED;																						\
																																							\
							do																																\
							{																																\
								if ( ( current_object_OLED->flags & ( OLED_OBJECT_FLAG_INVALIDATED | OLED_OBJECT_FLAG_HIDE_TRIGGERED ) ) != 0 &&			\
									( current_object_OLED->flags & ( OLED_OBJECT_FLAG_FROZEN | OLED_OBJECT_FLAG_INVALIDATION_CHAIN_CHECKED ) ) == 0 )		\
								{																															\
									/* chaining을 시작하기 전에 먼저 c flag를 set */																		\
									current_object_OLED->flags |= OLED_OBJECT_FLAG_INVALIDATION_CHAIN_CHECKED;												\
																																							\
									/* 3-1-1. chaining 시작 */																								\
									pos_chaining_object = current_object_OLED;																				\
																																							\
									do																														\
									{																														\
										/* 우선 flag 검사 */																								\
										if ( ( pos_chaining_object->flags &																					\
											( OLED_OBJECT_FLAG_VISIBLE | OLED_OBJECT_FLAG_FROZEN | OLED_OBJECT_FLAG_HIDE_TRIGGERED |						\
												OLED_OBJECT_FLAG_INVALIDATION_CHAIN_CHECKED ) ) == OLED_OBJECT_FLAG_VISIBLE )								\
										{																													\
											/* 겹침 검사: o1과 o2가 겹치는지 확인할 때 */																	\
											/* o2.left > o1.right || o2.top > o1.bottom || o2.right < o1.left || o2.bottom < o1.top이면 절대 안 겹침 */		\
											/* o2.left <=o1.right && o2.top <=o1.bottom && o2.right >=o1.left && o2.bottom >=o1.top이면 항상 겹침 */		\
																																							\
											/* chaining을 유발한 object가 invalidated object라면 새 위치 좌표와 겹치는지 여부 확인 */						\
											if ( current_object_OLED->flags & OLED_OBJECT_FLAG_INVALIDATED )												\
											{																												\
												if (	current_object_OLED->left	<= pos_chaining_object->right	&&										\
														current_object_OLED->top 	<= pos_chaining_object->bottom	&&										\
														current_object_OLED->right	>= pos_chaining_object->left 	&&										\
														current_object_OLED->bottom >= pos_chaining_object->top	)											\
												{																											\
													OLED_INVALIDATE_OBJECT_SIMPLE(pos_chaining_object);														\
													check_completed = 0;																					\
												}																											\
											}																												\
																																							\
											/* chaining을 유발한 object가 hide triggered object라면 현재 위치 좌표와 겹치는지 여부 확인 */					\
											if ( current_object_OLED->flags & OLED_OBJECT_FLAG_HIDE_TRIGGERED )												\
											{																												\
												if (	current_object_OLED->rendered_left		<= pos_chaining_object->right	&&							\
														current_object_OLED->rendered_top 		<= pos_chaining_object->bottom	&&							\
														current_object_OLED->rendered_right		>= pos_chaining_object->left 	&&							\
														current_object_OLED->rendered_bottom	>= pos_chaining_object->top	)								\
												{																											\
													OLED_INVALIDATE_OBJECT_SIMPLE(pos_chaining_object);														\
													check_completed = 0;																					\
												}																											\
											}																												\
										}																													\
																																							\
										pos_chaining_object = pos_chaining_object->next;																	\
									}																														\
									while ( pos_chaining_object != current_object_OLED );																	\
								}																															\
																																							\
								current_object_OLED = current_object_OLED->next;																			\
							}																																\
							while ( current_object_OLED != first_object_OLED );																				\
						}																																	\
						while ( check_completed == 0 );																										\
																																							\
						/* 3-2. 계산이 끝나면 모든 object의 c flag를 clear하고 object 포인터 리셋 */														\
						current_object_OLED = first_object_OLED;																							\
																																							\
						do																																	\
						{																																	\
							current_object_OLED->flags &= ~OLED_OBJECT_FLAG_INVALIDATION_CHAIN_CHECKED;														\
							current_object_OLED = current_object_OLED->next;																				\
						}																																	\
						while ( current_object_OLED != first_object_OLED );																					\
					}																																		\
																																							\
					triggers_OLED &= ~OLED_TRG_INVALIDATED;																									\
				}																																			\
																																							\
				/* 4. 전역 trigger가 없는 경우 실제 그리기 작업 수행 */																						\
				else																																		\
				{																																			\
					/* 현재 object가 1개 이상일 때만 작업 수행 */																							\
					if ( first_object_OLED != 0 )																											\
					{																																		\
						register struct OLED_Object* pos_object_to_render = current_object_OLED;															\
																																							\
						do																																	\
						{																																	\
							/* frozen 상태가 아닌 object에 대해 */																							\
							if ( ( pos_object_to_render->flags & OLED_OBJECT_FLAG_FROZEN ) == 0 )															\
							{																																\
								/* 4-1. hide_triggered object 처리 */																						\
								if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_HIDE_TRIGGERED )														\
								{																															\
									/* visible object인 경우 실제 지우기 작업 수행 후 visible flag를 clear */												\
									if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_VISIBLE )															\
									{																														\
										register unsigned int write_count = 																				\
											( pos_object_to_render->rendered_bottom - pos_object_to_render->rendered_top + 1 ) *							\
											( pos_object_to_render->rendered_right - pos_object_to_render->rendered_left + 1 );								\
																																							\
										OLED_WRITE_COMMAND(RASET);																							\
										OLED_WRITE_DATA(pos_object_to_render->rendered_top);																\
										OLED_WRITE_DATA(pos_object_to_render->rendered_bottom);																\
										OLED_WRITE_COMMAND(CASET);																							\
										OLED_WRITE_DATA(pos_object_to_render->rendered_left);																\
										OLED_WRITE_DATA(pos_object_to_render->rendered_right);																\
										OLED_WRITE_COMMAND(RAMWR);																							\
										do																													\
										{																													\
											OLED_WRITE_DATA(OLED_BGCOLOR_HIGH);																				\
											OLED_WRITE_DATA(OLED_BGCOLOR_LOW);																				\
										}																													\
										while ( --write_count );																							\
																																							\
										pos_object_to_render->flags &= ~OLED_OBJECT_FLAG_VISIBLE;															\
									}																														\
																																							\
									pos_object_to_render->flags &= ~OLED_OBJECT_FLAG_HIDE_TRIGGERED;														\
								}																															\
																																							\
								/* 4-2. invalidated object 처리 */																							\
								if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_INVALIDATED )															\
								{																															\
									/* 그리기 함수 써서 화면에 그림 (scaling flag에 따라 다른 함수 사용) */													\
									if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_SCALABLE )															\
										OLED_RENDER_OBJECT_WITH_SCALING(pos_object_to_render);																\
									else																													\
										OLED_RENDER_OBJECT(pos_object_to_render);																			\
																																							\
									/* 그린 위치 기록 */																									\
									pos_object_to_render->rendered_left = pos_object_to_render->left;														\
									pos_object_to_render->rendered_top = pos_object_to_render->top;															\
									pos_object_to_render->rendered_right = pos_object_to_render->right;														\
									pos_object_to_render->rendered_bottom = pos_object_to_render->bottom;													\
																																							\
									pos_object_to_render->flags =																							\
										( pos_object_to_render->flags & ~OLED_OBJECT_FLAG_INVALIDATED ) | OLED_OBJECT_FLAG_VISIBLE;							\
								}																															\
																																							\
								/* 4-3. delete triggered object 처리 */																						\
								if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_DELETE_TRIGGERED )														\
								{																															\
									register unsigned char index;																							\
									register struct OLED_Object* backup_pos_object_to_render_next = pos_object_to_render->next;								\
																																							\
									/* 4-3-1. 링크드 리스트 복원 */																							\
									pos_object_to_render->previous->next = pos_object_to_render->next;														\
									pos_object_to_render->next->previous = pos_object_to_render->previous;													\
																																							\
									/* 4-3-2. z-index table 복원 */																							\
									for ( index = 0; index <= OLED_MAX_Z_INDEX; ++index )																	\
									{																														\
										/* 제거하려는 object가 tail이라면 */																				\
										if ( pos_object_to_render == z_tails_OLED[index] )																	\
										{																													\
											/* tail이면서 동시에 head라면 해당 z_index를 가진 object가 하나도 없으니 두 포인터 모두 0으로 리셋 */			\
											if ( pos_object_to_render == z_heads_OLED[index] )																\
											{																												\
												z_heads_OLED[index] = 0;																					\
												z_tails_OLED[index] = 0;																					\
											}																												\
											/* 그렇지 않다면 tail 재설정 */																					\
											else																											\
											{																												\
												z_tails_OLED[index] = pos_object_to_render->previous;														\
											}																												\
											break;																											\
										}																													\
										/* 제거하려는 object가 tail은 아니고 head라면 head 재설정 */														\
										else if ( pos_object_to_render == z_heads_OLED[index] )																\
										{																													\
											z_heads_OLED[index] = pos_object_to_render->next;																\
																																							\
											break;																											\
										}																													\
									}																														\
																																							\
									/* 4-3-3. first object를 방금 제거했다면 first object 포인터 복원 */													\
									if ( pos_object_to_render == first_object_OLED )																		\
									{																														\
										/* 더이상 object가 없는 경우(first object 하나밖에 없었는데 그걸 지금 지우고 있는 경우) 포인터 리셋 */				\
										if ( pos_object_to_render->next == pos_object_to_render )															\
										{																													\
											first_object_OLED = 0;																							\
										}																													\
										/* 그렇지 않은 경우 가장 index가 작은 head가 first object가 됨 */													\
										else																												\
										{																													\
											for ( index = 0; index <= OLED_MAX_Z_INDEX; ++index )															\
											{																												\
												if ( z_heads_OLED[index] != 0 )																				\
												{																											\
													first_object_OLED = z_heads_OLED[index];																\
													break;																									\
												}																											\
											}																												\
										}																													\
									}																														\
																																							\
									/* 4-3-4. unused list에 object 연결 */																					\
									if ( unused_objects_OLED == 0 )																							\
									{																														\
										/* unused list가 비어 있었다면 그냥 추가 */																			\
										unused_objects_OLED = pos_object_to_render;																			\
										pos_object_to_render->next = 0;																						\
									}																														\
									else																													\
									{																														\
										/* 그렇지 않다면 list의 가장 앞에 연결 */																			\
										pos_object_to_render->next = unused_objects_OLED;																	\
										unused_objects_OLED = pos_object_to_render;																			\
									}																														\
																																							\
									/* 제거한 object의 flag 초기화 */																						\
									pos_object_to_render->flags = 0;																						\
																																							\
									/* 다음 object부터 그리기 작업을 재개할 수 있도록 표시 후 루프 종료(제거된 object는 freeze할 필요 없음) */				\
									pos_object_to_render = backup_pos_object_to_render_next;																\
									break;																													\
								}																															\
																																							\
																																							\
								/* 4-4. freeze_triggered object를 frozen 상태로 만듦 */																		\
								if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_FREEZE_TRIGGERED )														\
								{																															\
									pos_object_to_render->flags =																							\
										( pos_object_to_render->flags & ~OLED_OBJECT_FLAG_FREEZE_TRIGGERED ) | OLED_OBJECT_FLAG_FROZEN;						\
								}																															\
																																							\
								/* 다음 object부터 그리기 작업을 재개할 수 있도록 표시 후 루프 종료 */														\
								pos_object_to_render = pos_object_to_render->next;																			\
								break;																														\
							}																																\
																																							\
							pos_object_to_render = pos_object_to_render->next;																				\
						}																																	\
						while ( pos_object_to_render != current_object_OLED );																				\
																																							\
						/* 4-5. 더 이상 그릴 object가 없는 경우 trigger가 다시 설정될때까지 OLED 프레임 정지 */												\
						if ( pos_object_to_render == 0 || pos_object_to_render == current_object_OLED )														\
							triggers_OLED = OLED_TRG_COMPLETED;																								\
						/* 그렇지 않은 경우 다음에 그릴 object 표시 후 프레임 종료 */																		\
						else																																\
							current_object_OLED = pos_object_to_render;																						\
					}																																		\
					/* 5. 현재 object가 하나도 없다면 trigger가 다시 설정될때까지 OLED 프레임 정지 */														\
					else																																	\
						triggers_OLED = OLED_TRG_COMPLETED;																									\
				}																																			\
			}																																				\
		}																																					\
		while ( 0 )
