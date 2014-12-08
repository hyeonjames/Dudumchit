/*
	2013�� �����б� ����ũ�����μ�������

	OLED.h

	�ǽ� ŰƮ�� 128x128 OLED�� �����ϱ� ���� ���̺귯������ ����ϴ� ���� ��ҵ��� ��� �ֽ��ϴ�.

	----------------------------------------- ���� -----------------------------------------
	�л� �������� �� ������ ���� �׹� ����� �Ű澲�� �ʾƵ� �˴ϴ�.
	���, ������ ���õ� OLED_modify_me_but_do_not_include_me.h�� �ִ� ���븸 �� ���� ����
	�ش� ���Ͽ� ����� ��ũ�� �Լ���, OLED_Object ����ü ��� �����鸸 ������ �ٲٸ鼭 ���� �˴ϴ�.
	----------------------------------------------------------------------------------------
*/

#include <avr/io.h>
#include <avr/pgmspace.h>

#pragma once

#include "OLED_modify_me_but_do_not_include_me.h"


/*
	----------------------------------------------------------------------
	�� �Ʒ��� ������ �����ϴ� ��� ����ϰų� �ɰ��� ���۵��� ����ų �� ������
	Ȥ�ó� �������� ���α׷����� �̼��� Ʃ�� �۾��� �ʿ��� ���
	�ݵ�� ���� �������� ������ �Ƿ��ϼ���.
	----------------------------------------------------------------------
*/

/*
	----------------------------------------------------------------------
	OLED module �������̽� ���� �κ�
	----------------------------------------------------------------------
*/

/* OLED control flag�� �� ��ġ ���� */
#define OLED_FLAG_CS	0b00001
#define OLED_FLAG_RST	0b00010
#define OLED_FLAG_DC	0b00100
#define OLED_FLAG_RW	0b01000
#define OLED_FLAG_E		0b10000

/* �ش� flag�� bit�� 1�� ����(�ٸ� bit�� �״�� ��) */
#define OLED_SET_FLAG(name) 	( PORT_OLED_CTRL |= OLED_FLAG_##name )

/* �ش� flag�� bit�� 0���� ����(�ٸ� bit�� �״�� ��) */
#define OLED_CLR_FLAG(name)		( PORT_OLED_CTRL &= ~OLED_FLAG_##name )

/* OLED module�� �����ϱ� ���� ��ɾ� �϶� - �� ��ɾ��� �ǹ̴� datasheet ���� -> ���� �� */
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

/* OLED�� �ش� ��ɾ ������ ��ũ�� �Լ� */
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

/* OLED�� �ش� ��ɾ ������ ��ũ�� �Լ�(���� ŰƮ ����) */
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

/* OLED�� �ش� ������(��ɾ��� argument)�� ������ ��ũ�� �Լ� */
#define OLED_WRITE_DATA(data)																			\
		do																								\
		{																								\
			PORT_OLED_CTRL = OLED_FLAG_RST | OLED_FLAG_DC | OLED_FLAG_E;								\
			PORT_OLED_DATA = ( data );																	\
			asm("NOP");																					\
			PORT_OLED_CTRL = OLED_FLAG_CS | OLED_FLAG_RST | OLED_FLAG_DC | OLED_FLAG_RW | OLED_FLAG_E;	\
		}																								\
		while ( 0 )

/* R, G, B ������ ���� ���� �����ϱ� ���� ��ɾ�� argument�� ������ ��ũ�� �Լ� */
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

/* ���� R, G, B ������ �������� 16bit format���� ������ ���� ������ */
#define OLED_BGCOLOR_HIGH	( ( OLED_BGCOLOR_R << 3 ) | ( OLED_BGCOLOR_G >> 3 ) )
#define OLED_BGCOLOR_LOW	( ( ( OLED_BGCOLOR_G & 0b111 ) << 5 ) | OLED_BGCOLOR_B )

/* ��ü ȭ���� �������� ĥ�ϴ� ��ũ�� �Լ� */
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

/* OLED module�� ����ϱ� ���� �ʱ�ȭ �۾��� �����ϴ� ��ũ�� �Լ� */
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
	OLED ���̺귯�� ���� �κ�
	----------------------------------------------------------------------
*/

/* �̹��� ��Ʈ�� �ϳ��� ���� ������ ��� ����ü */
struct OLED_Bitmap
{
	prog_uint16_t *ptr_data;
	unsigned char width;
	unsigned char height;
	unsigned int color;
};

/* ȭ�鿡 �׸� � ��ü �ϳ��� ���� ������ ��� ����ü */
struct OLED_Object
{
	/* �� object�� �׸� �� ����� ��Ʈ�� ��ȣ */
	unsigned char idx_bitmap;

	/* �� object�� ��ġ�� ���� ��� ��ǥ */
	unsigned char left;
	unsigned char top;

	/* �� object�� ��ġ�� ���� �ϴ� ��ǥ(scalable flag�� 1�� ���� ���) */
	unsigned char right;
	unsigned char bottom;

	/*
		�� �Ʒ��� �ִ� �������� OLED ���̺귯�� ���ο��� �����ϹǷ�
		���� �Ű澲�� �ʾƵ� ������
		������ ���Ƿ� �����ϸ� ���۵��� ������ �� �� �ֽ��ϴ�.
	*/

	/* �Ʒ��� ���� flag���� ��� ���� ���� */
	unsigned char flags;

	/* visible flag�� 1�� �� �� object�� ���� �׷��� ȭ����� ��ǥ */
	unsigned char rendered_left;
	unsigned char rendered_top;
	unsigned char rendered_right;
	unsigned char rendered_bottom;

	/* �ڷᱸ�� ������ ���� ����ϴ� �߰� ������ ������ */
	struct OLED_Object* previous;
	struct OLED_Object* next;
};

/*
	flag list:

		0b76543210
		  csvrfhdi
	
		i: invalidated - �� object�� �ٽ� �׷��� ���� �ǹ�
		d: delete triggered - �� object�� ������ �����ؾ� ���� �ǹ�
		h: hide triggered - �� object�� ȭ�鿡�� ������ ���� �ǹ�
		f: freeze triggered - �� object�� invalidation chain�� ������ �ްų� ���� �ʵ��� ������ ���� �ǹ�

		r: frozen - �� object�� invalidation chain�� ������ �ްų� ���� ������ �ǹ�
		v: visible - �� object�� ���� ȭ�鿡 ǥ�õǾ� ������ �ǹ�
		s: scalable - �� object�� �׸� �� Ȯ�� / ��� ����� ����ؼ� �׸����� �����Ǿ� ������ �ǹ�
		c: invalidation chain checked - invalidation chain ��� ���������� ����ϴ� flag, �� object�� invalidation chaining�� �̹� �� �� ���������� �ǹ�
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
	�־��� z_index�� �׸��� �Ӽ��� ���� ���ο� object�� �����ϰ� �����͸� ��ȯ
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
	
		i: invalidated - �� object�� �ٽ� �׷��� ���� �ǹ�
		d: delete triggered - �� object�� ������ �����ؾ� ���� �ǹ�
		h: hide triggered - �� object�� ȭ�鿡�� ������ ���� �ǹ�
		f: freeze triggered - �� object�� invalidation chain�� ������ �ްų� ���� �ʵ��� ������ ���� �ǹ�

		r: frozen - �� object�� invalidation chain�� ������ �ްų� ���� ������ �ǹ�
		v: visible - �� object�� ���� ȭ�鿡 ǥ�õǾ� ������ �ǹ�
		s: scalable - �� object�� �׸� �� Ȯ�� / ��� ����� ����ؼ� �׸����� �����Ǿ� ������ �ǹ�
		c: invalidation chain checked - invalidation chain ��� ���������� ����ϴ� flag, �� object�� invalidation chain ��꿡 �̹� �� �� ���ԵǾ����� �ǹ�
*/

/*
	�ش� object�� ȭ�鿡�� ����� ������ ����(frozen ���¿��ٸ� ������)
*/
#define OLED_DELETE_OBJECT(ptr_object)		( ( ptr_object )->flags = ( ( ptr_object )->flags & ~OLED_OBJECT_FLAG_FROZEN ) | OLED_OBJECT_FLAG_DELETE_TRIGGERED | OLED_OBJECT_FLAG_HIDE_TRIGGERED )

/*
	�ش� object�� ȭ�鿡 �״�� �ΰ� ������ ����(frozen ���¿��ٸ� ���������� �� �ǹ̴� ����)
*/
#define OLED_DELETE_OBJECT_SIMPLE(ptr_object)	( ( ptr_object )->flags = ( ( ptr_object )->flags & ~OLED_OBJECT_FLAG_FROZEN ) | OLED_OBJECT_FLAG_DELETE_TRIGGERED )

/*
	�ش� object�� ȭ�鿡�� ����� freeze
*/
#define OLED_HIDE_OBJECT(ptr_object)		( ( ptr_object )->flags |= OLED_OBJECT_FLAG_HIDE_TRIGGERED | OLED_OBJECT_FLAG_FREEZE_TRIGGERED )

/*
	�ش� object�� ȭ�鿡 �ٽ� ǥ��(frozen ���¿��ٸ� ������)
*/
#define OLED_SHOW_OBJECT(ptr_object)		( ( ptr_object )->flags = ( ptr_object )->flags & ~( OLED_OBJECT_FLAG_HIDE_TRIGGERED | OLED_OBJECT_FLAG_FREEZE_TRIGGERED | OLED_OBJECT_FLAG_FROZEN ) | OLED_OBJECT_FLAG_INVALIDATED )

/*
	�ش� object�� �ٽ� �׸��� �ʵ��� freeze(ȭ�� �����ڸ� ���, �ϴ� ���� ǥ���ϴ� object�� ��� ������ �θ� ��)
*/
#define OLED_FREEZE_OBJECT(ptr_object)		( ( ptr_object )->flags |= OLED_OBJECT_FLAG_FREEZE_TRIGGERED )

/*
	�ش� object�� �ʿ�� �ٽ� �׸� �� �ֵ��� frozen ���¸� ����
*/
#define OLED_UNFREEZE_OBJECT(ptr_object)	( ( ptr_object )->flags = ( ptr_object )->flags & ~( OLED_OBJECT_FLAG_FROZEN | OLED_OBJECT_FLAG_FREEZE_TRIGGERED ) )

/*
	�ش� object�� ���� ��ġ�� �ٽ� �׸����� ����(���� ��ġ���� ����� ���� ����)
*/
#define OLED_INVALIDATE_OBJECT_SIMPLE(ptr_object)	( ( ptr_object )->flags |= OLED_OBJECT_FLAG_INVALIDATED )

/*
	�ش� object�� ���� ��ġ���� ����� ���� ��ġ�� �ٽ� �׸����� ����
*/
#define OLED_INVALIDATE_OBJECT(ptr_object)	( ( ptr_object )->flags |= OLED_OBJECT_FLAG_HIDE_TRIGGERED | OLED_OBJECT_FLAG_INVALIDATED )

/*
	OLED ���̺귯���� invalidation check�� �ٽ� �� �ʿ伺�� �������� �˸�
*/
#define OLED_INVALIDATE()	( triggers_OLED |= OLED_TRG_INVALIDATED )

/*
	OLED ���̺귯���� ȭ�� ��ü�� �ٽ� �׸� �ʿ伺�� �������� �˸�
*/
#define OLED_REFRESH()		( triggers_OLED |= OLED_TRG_REFRESH_REQUESTED )



/*
	TEST mode���� �ƴ����� ���� �޶����� �׸��� �Լ�.
	����: �������� �� �Լ��� ���� ȣ���� ���� ����.
*/
#if OLED_TEST == 0

/* TEST mode�� �ƴ� �� ���� bitmap�� ����Ͽ� �׸� */
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

/* TEST mode�� �� colors_OLED[]�� �ִ� �ܻ��� �� �ϳ��� ����Ͽ� �׸� */
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

/* TEST mode�� �� ��� �ȼ��� �ܻ����� ĥ�ϱ� ������ scaling�� ���� ����ؼ� �� �ʿ䰡 ���� */
#define OLED_RENDER_OBJECT_WITH_SCALING(ptr_object)		OLED_RENDER_OBJECT(ptr_object)

#endif

/*
	OLED �������� ������ ���� �Ŵ� ��ũ�� �Լ�
*/
#define OLED_UPDATE()																																		\
		do																																					\
		{																																					\
			/* OLED ���� �۾��� ���� �Ϸ���� �ʾҰų� �� �۾��� ���� ��쿡�� �ڵ� ���� */																	\
			if ( triggers_OLED != OLED_TRG_COMPLETED )																										\
			{																																				\
				triggers_OLED &= ~OLED_TRG_COMPLETED;																										\
																																							\
				/* 1. �� object�� �����Ǿ� object list�� �����ؾ� �ϴ� ��� */																				\
				if ( triggers_OLED & OLED_TRG_CREATED )																										\
				{																																			\
					register unsigned char index;																											\
					register unsigned char nextIndex;																										\
																																							\
					/* �� tail�� ���� head�� ����ǰ� ���� */																								\
					for ( index = 0; index <= OLED_MAX_Z_INDEX; ++index )																					\
					{																																		\
						if ( z_tails_OLED[index] != 0 )																										\
						{																																	\
							nextIndex = index + 1;																											\
																																							\
							while ( nextIndex != OLED_MAX_Z_INDEX + 1 && z_tails_OLED[nextIndex] == 0 )														\
								++nextIndex;																												\
																																							\
							/* ������ tail�� ù head�� ����ǰ� ���� */																						\
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
								/* ù head�� ��ü ����Ʈ�� ù object�� �� */																				\
								first_object_OLED = z_heads_OLED[nextIndex];																				\
								break;																														\
							}																																\
							/* ������ tail�� �ƴ� ��� ��� ã�� ���� head�� ����ǰ� ���� */																\
							else																															\
							{																																\
								z_tails_OLED[index]->next = z_heads_OLED[nextIndex];																		\
								z_heads_OLED[nextIndex]->previous = z_tails_OLED[index];																	\
							}																																\
						}																																	\
					}																																		\
																																							\
					/* object ������ ���� - ���� OLED �����ӿ��� �׸��⸦ ó������ �� �� �ְ� */															\
					current_object_OLED = first_object_OLED;																								\
																																							\
					triggers_OLED &= ~OLED_TRG_CREATED;																										\
				}																																			\
																																							\
				/* 2. ��ü ȭ�� �ٽ� �׸��� ��û�� ���� ���  */																							\
				else if ( triggers_OLED & OLED_TRG_REFRESH_REQUESTED )																						\
				{																																			\
					/* ���� ��ü ȭ���� �������� ä�� */																									\
					OLED_CLEAR_SCREEN();																													\
																																							\
					/* ���� object�� 1�� �̻��� ���� �ٽ� �׸��� ���� */																					\
					if ( first_object_OLED != 0 )																											\
					{																																		\
						/* ��� visible and not frozen object�� invalidate�ϰ� object ������ ���� */														\
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
					/* refresh ��û�� ó���ϸ鼭 ��� object�� invalidate�������Ƿ� */																		\
					/* ���� chain ����� �� �ʿ䰡 ������ -> INVALIDATED flag�� ���� clear */																\
					triggers_OLED &= ~( OLED_TRG_REFRESH_REQUESTED | OLED_TRG_INVALIDATED );																\
				}																																			\
																																							\
				/* 3. invalidation chain�� �ٽ� ����ؾ� �ϴ� ��� */																						\
				else if ( triggers_OLED & OLED_TRG_INVALIDATED )																							\
				{																																			\
					/* ���� object�� 1�� �̻��� ���� chaining ���� */																						\
					if ( first_object_OLED != 0 )																											\
					{																																		\
						register unsigned char check_completed;																								\
						register struct OLED_Object* pos_chaining_object;																					\
																																							\
						do																																	\
						{																																	\
							check_completed = 1;																											\
																																							\
							/* 3-1. ��� ( invalidated or hide triggered ) and not ( frozen or checked ) object�� ���� */									\
							/* �ش� object�� ��ġ�� ��� visible and not ( frozen or hide triggered or checked ) object���� invalidate */					\
							current_object_OLED = first_object_OLED;																						\
																																							\
							do																																\
							{																																\
								if ( ( current_object_OLED->flags & ( OLED_OBJECT_FLAG_INVALIDATED | OLED_OBJECT_FLAG_HIDE_TRIGGERED ) ) != 0 &&			\
									( current_object_OLED->flags & ( OLED_OBJECT_FLAG_FROZEN | OLED_OBJECT_FLAG_INVALIDATION_CHAIN_CHECKED ) ) == 0 )		\
								{																															\
									/* chaining�� �����ϱ� ���� ���� c flag�� set */																		\
									current_object_OLED->flags |= OLED_OBJECT_FLAG_INVALIDATION_CHAIN_CHECKED;												\
																																							\
									/* 3-1-1. chaining ���� */																								\
									pos_chaining_object = current_object_OLED;																				\
																																							\
									do																														\
									{																														\
										/* �켱 flag �˻� */																								\
										if ( ( pos_chaining_object->flags &																					\
											( OLED_OBJECT_FLAG_VISIBLE | OLED_OBJECT_FLAG_FROZEN | OLED_OBJECT_FLAG_HIDE_TRIGGERED |						\
												OLED_OBJECT_FLAG_INVALIDATION_CHAIN_CHECKED ) ) == OLED_OBJECT_FLAG_VISIBLE )								\
										{																													\
											/* ��ħ �˻�: o1�� o2�� ��ġ���� Ȯ���� �� */																	\
											/* o2.left > o1.right || o2.top > o1.bottom || o2.right < o1.left || o2.bottom < o1.top�̸� ���� �� ��ħ */		\
											/* o2.left <=o1.right && o2.top <=o1.bottom && o2.right >=o1.left && o2.bottom >=o1.top�̸� �׻� ��ħ */		\
																																							\
											/* chaining�� ������ object�� invalidated object��� �� ��ġ ��ǥ�� ��ġ���� ���� Ȯ�� */						\
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
											/* chaining�� ������ object�� hide triggered object��� ���� ��ġ ��ǥ�� ��ġ���� ���� Ȯ�� */					\
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
						/* 3-2. ����� ������ ��� object�� c flag�� clear�ϰ� object ������ ���� */														\
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
				/* 4. ���� trigger�� ���� ��� ���� �׸��� �۾� ���� */																						\
				else																																		\
				{																																			\
					/* ���� object�� 1�� �̻��� ���� �۾� ���� */																							\
					if ( first_object_OLED != 0 )																											\
					{																																		\
						register struct OLED_Object* pos_object_to_render = current_object_OLED;															\
																																							\
						do																																	\
						{																																	\
							/* frozen ���°� �ƴ� object�� ���� */																							\
							if ( ( pos_object_to_render->flags & OLED_OBJECT_FLAG_FROZEN ) == 0 )															\
							{																																\
								/* 4-1. hide_triggered object ó�� */																						\
								if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_HIDE_TRIGGERED )														\
								{																															\
									/* visible object�� ��� ���� ����� �۾� ���� �� visible flag�� clear */												\
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
								/* 4-2. invalidated object ó�� */																							\
								if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_INVALIDATED )															\
								{																															\
									/* �׸��� �Լ� �Ἥ ȭ�鿡 �׸� (scaling flag�� ���� �ٸ� �Լ� ���) */													\
									if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_SCALABLE )															\
										OLED_RENDER_OBJECT_WITH_SCALING(pos_object_to_render);																\
									else																													\
										OLED_RENDER_OBJECT(pos_object_to_render);																			\
																																							\
									/* �׸� ��ġ ��� */																									\
									pos_object_to_render->rendered_left = pos_object_to_render->left;														\
									pos_object_to_render->rendered_top = pos_object_to_render->top;															\
									pos_object_to_render->rendered_right = pos_object_to_render->right;														\
									pos_object_to_render->rendered_bottom = pos_object_to_render->bottom;													\
																																							\
									pos_object_to_render->flags =																							\
										( pos_object_to_render->flags & ~OLED_OBJECT_FLAG_INVALIDATED ) | OLED_OBJECT_FLAG_VISIBLE;							\
								}																															\
																																							\
								/* 4-3. delete triggered object ó�� */																						\
								if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_DELETE_TRIGGERED )														\
								{																															\
									register unsigned char index;																							\
									register struct OLED_Object* backup_pos_object_to_render_next = pos_object_to_render->next;								\
																																							\
									/* 4-3-1. ��ũ�� ����Ʈ ���� */																							\
									pos_object_to_render->previous->next = pos_object_to_render->next;														\
									pos_object_to_render->next->previous = pos_object_to_render->previous;													\
																																							\
									/* 4-3-2. z-index table ���� */																							\
									for ( index = 0; index <= OLED_MAX_Z_INDEX; ++index )																	\
									{																														\
										/* �����Ϸ��� object�� tail�̶�� */																				\
										if ( pos_object_to_render == z_tails_OLED[index] )																	\
										{																													\
											/* tail�̸鼭 ���ÿ� head��� �ش� z_index�� ���� object�� �ϳ��� ������ �� ������ ��� 0���� ���� */			\
											if ( pos_object_to_render == z_heads_OLED[index] )																\
											{																												\
												z_heads_OLED[index] = 0;																					\
												z_tails_OLED[index] = 0;																					\
											}																												\
											/* �׷��� �ʴٸ� tail �缳�� */																					\
											else																											\
											{																												\
												z_tails_OLED[index] = pos_object_to_render->previous;														\
											}																												\
											break;																											\
										}																													\
										/* �����Ϸ��� object�� tail�� �ƴϰ� head��� head �缳�� */														\
										else if ( pos_object_to_render == z_heads_OLED[index] )																\
										{																													\
											z_heads_OLED[index] = pos_object_to_render->next;																\
																																							\
											break;																											\
										}																													\
									}																														\
																																							\
									/* 4-3-3. first object�� ��� �����ߴٸ� first object ������ ���� */													\
									if ( pos_object_to_render == first_object_OLED )																		\
									{																														\
										/* ���̻� object�� ���� ���(first object �ϳ��ۿ� �����µ� �װ� ���� ����� �ִ� ���) ������ ���� */				\
										if ( pos_object_to_render->next == pos_object_to_render )															\
										{																													\
											first_object_OLED = 0;																							\
										}																													\
										/* �׷��� ���� ��� ���� index�� ���� head�� first object�� �� */													\
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
									/* 4-3-4. unused list�� object ���� */																					\
									if ( unused_objects_OLED == 0 )																							\
									{																														\
										/* unused list�� ��� �־��ٸ� �׳� �߰� */																			\
										unused_objects_OLED = pos_object_to_render;																			\
										pos_object_to_render->next = 0;																						\
									}																														\
									else																													\
									{																														\
										/* �׷��� �ʴٸ� list�� ���� �տ� ���� */																			\
										pos_object_to_render->next = unused_objects_OLED;																	\
										unused_objects_OLED = pos_object_to_render;																			\
									}																														\
																																							\
									/* ������ object�� flag �ʱ�ȭ */																						\
									pos_object_to_render->flags = 0;																						\
																																							\
									/* ���� object���� �׸��� �۾��� �簳�� �� �ֵ��� ǥ�� �� ���� ����(���ŵ� object�� freeze�� �ʿ� ����) */				\
									pos_object_to_render = backup_pos_object_to_render_next;																\
									break;																													\
								}																															\
																																							\
																																							\
								/* 4-4. freeze_triggered object�� frozen ���·� ���� */																		\
								if ( pos_object_to_render->flags & OLED_OBJECT_FLAG_FREEZE_TRIGGERED )														\
								{																															\
									pos_object_to_render->flags =																							\
										( pos_object_to_render->flags & ~OLED_OBJECT_FLAG_FREEZE_TRIGGERED ) | OLED_OBJECT_FLAG_FROZEN;						\
								}																															\
																																							\
								/* ���� object���� �׸��� �۾��� �簳�� �� �ֵ��� ǥ�� �� ���� ���� */														\
								pos_object_to_render = pos_object_to_render->next;																			\
								break;																														\
							}																																\
																																							\
							pos_object_to_render = pos_object_to_render->next;																				\
						}																																	\
						while ( pos_object_to_render != current_object_OLED );																				\
																																							\
						/* 4-5. �� �̻� �׸� object�� ���� ��� trigger�� �ٽ� �����ɶ����� OLED ������ ���� */												\
						if ( pos_object_to_render == 0 || pos_object_to_render == current_object_OLED )														\
							triggers_OLED = OLED_TRG_COMPLETED;																								\
						/* �׷��� ���� ��� ������ �׸� object ǥ�� �� ������ ���� */																		\
						else																																\
							current_object_OLED = pos_object_to_render;																						\
					}																																		\
					/* 5. ���� object�� �ϳ��� ���ٸ� trigger�� �ٽ� �����ɶ����� OLED ������ ���� */														\
					else																																	\
						triggers_OLED = OLED_TRG_COMPLETED;																									\
				}																																			\
			}																																				\
		}																																					\
		while ( 0 )
