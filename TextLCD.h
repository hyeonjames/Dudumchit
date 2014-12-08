/*
	2013�� �����б� ����ũ�����μ�������

	TextLCD.h

	�ǽ� ŰƮ�� 2x16 Text LCD�� �����ϱ� ���� ��� / �������� �����մϴ�.

	�л� �������� �� ���Ͽ���
	���κп� �ִ� ������ ���� �� ��Ʈ ������ �ڽ��� ȯ�濡 �°� �ٲٰ�
	�߰� ������ ������ ä �� �Ʒ��� �ִ� ��ũ�� �Լ� �� ���� ���� ���� �˴ϴ�.

	TextLCD.h�� �ִ� ��ũ�� �Լ��� ����Ϸ���
	������Ʈ�� TextLCD.c ������ ���ԵǾ� �־�� �մϴ�.

	����: TextLCD_Buffer.h�� include�Ͽ� ���� ���۸� ���̺귯���� ����ϴ� ���
		  �� ���� ���κ��� ȯ�� ����, ���� ���� �ȿ� LCD_UPDATE() ȣ�� ���� �߰�, buffer_LCD[] �迭�� ���ϴ� ���� ���
		  ...�� ������ �ٸ� ���� / �Լ��� ���� �� �ʿ� �����ϴ�.
		  �ڼ��� ������ TextLCD_Buffer.h�� �ּ��� �����ϼ���.

	TextLCD.h ���̺귯���� ������ �޸𸮸� 3����Ʈ��ŭ ����մϴ�.
*/

#pragma once

#include <avr/io.h>

/*
	LCD�� ��ɾ ������ ������ ������ �����մϴ�.

	����: �ʹ� �۰� ������ LCD ���۵��� �Ͼ �� ������
		  �ʹ� ũ�� ������ LCD�� ���� �ӵ��� �׸�ŭ �������� �˴ϴ�.
		  ���� �� ���� ���� �۵� ������ ���ؿ��� ���� ���� ������ �����ϴ� ���� �����ϴ�.
		  TextLCD_Buffer.h ���̺귯���� ���ٸ� 0x20 ~ 0x30,
		  �׳� TextLCD.h ���̺귯���� ���ٸ� 0x20 ~ 0x80 ������ ���� ���ڱ���.
*/
#define TICKS_PER_LCD_FRAME 0x80

/*
	LCD�� ������ ��Ʈ�� �����մϴ�.

	�����͸� ������ LCD_DATA ��Ʈ�� 8bit�� ��� ����ϸ�
	��Ʈ�� ��ȣ�� ������ LCD_CTRL ��Ʈ�� ���� 3bit�� ����մϴ�.
	�� ���̺귯������ LCD_CTRL ��Ʈ�� ���� 5bit�� ���� �ǵ帮�� ������
	�ʿ��� ��� ���� ���� �ٸ� ���� ������ �� ����� �� �ֽ��ϴ�.
*/
#define DDR_LCD_DATA DDRC
#define DDR_LCD_CTRL DDRG

#define PORT_LCD_DATA PORTC
#define PORT_LCD_CTRL PORTG

/*
	���� �������� ���� 1�� ������Ű�� �ֱ������� ������ �ڵ带 �����Ű�� ���� �����Դϴ�.
	�ǽ� �ð��� �Ź� ���� ��Ĵ�� if���� �Ἥ �ڵ带 �ۼ��ϸ� �˴ϴ�.
*/
extern unsigned char tick_LCD;

/*
	--------------------------------------------------------
	���⼭���� �Ʒ��� �ִ� ������
	�� �Ʒ��� �ִ� �� ��ũ�� �Լ��� �����ϸ�
	���� ���� �������ϴ�.
	--------------------------------------------------------
*/


/* LCD ��Ʈ�� ��ȣ�� ������ ���� ����ϴ� �� ��Ʈ ���� */
#define FLAG_LCD_E	0b100
#define FLAG_LCD_RW	0b010
#define FLAG_LCD_RS 0b001

/* LCD�� �����ϱ� ���� ������ �� ��ɾ� ���� ���� */
#define CMD_LCD_ClearDisplay		0b00000001
#define CMD_LCD_ReturnHome			0b00000010
#define CMD_LCD_EntryModeSet		0b00000100
#define CMD_LCD_DisplayControl		0b00001000
#define CMD_LCD_CursorDisplayShift	0b00010000
#define CMD_LCD_FunctionSet			0b00100000
#define CMD_LCD_SetCGAddress		0b01000000
#define CMD_LCD_SetDDAddress		0b10000000

/*
	�� ��ɾ�� �߰��� �ʿ��� ��� �ð� ����.
	0�� ��� ���� �����ӿ� �ٷ� �ٸ� �۾��� �� �� ������ �ǹ�.
	����: ���� �ִ� ���� �׳� ������ �ƴ϶� LCD ��� Ư���� ���߾� �� ���̴� �������� �ʴ� ���� ����.
*/
#define COOLDOWN_LCD_STARTUP			0x40
#define COOLDOWN_LCD_PORT				0x40
#define COOLDOWN_LCD_ClearDisplay		0x20
#define COOLDOWN_LCD_ReturnHome			0x20
#define COOLDOWN_LCD_EntryModeSet		0
#define COOLDOWN_LCD_DisplayControl		0
#define COOLDOWN_LCD_FunctionSet		0
#define COOLDOWN_LCD_CursorDisplayShift	0
#define COOLDOWN_LCD_SetCGAddress		0
#define COOLDOWN_LCD_SetDDAddress		0
#define COOLDOWN_LCD_DATA				0

/* LCD ������ �ȿ��� ����ϴ� state�� */
#define INTERNALSTATE_LCD_INIT_PORT		0x01
#define INTERNALSTATE_LCD_INIT_FUNC		0x02
#define INTERNALSTATE_LCD_INIT_ON		0x04
#define INTERNALSTATE_LCD_INIT_CLEAR	0x08
#define INTERNALSTATE_LCD_READY			0x10

/*
	LCD �����ӿ��� ����ϴ� ���� ����(���� tick ������ �����Ͽ� �� 3����Ʈ).
	�� ������ TextLCD.c�� ���ǵǾ� ����.
*/
extern unsigned char internalState_LCD;
extern unsigned char cooldown_LCD;

/* �� ��Ʈ �̸�(E, RW, RS)�� argument�� �޾� �ش� ��Ʈ�� 1 �Ǵ� 0���� �����ϴ� ��ũ�� �Լ� */
#define LCD_SET_FLAG(name) ( PORT_LCD_CTRL |= FLAG_LCD_##name )
#define LCD_CLR_FLAG(name) ( PORT_LCD_CTRL &= ~FLAG_LCD_##name )

/* LCD�� ��ɾ �����ϱ� ���� E bit�� ���־��� ��� 1�� ������� 0���� �ǵ����� ��ũ�� �Լ� */
#define LCD_PULSE() ( LCD_SET_FLAG(E), LCD_CLR_FLAG(E) )


/*
	-------------------------------------------------------------
	�� �ּ� ���� �ִ� ������ ������ ������ �Ű澵 �ʿ� �����ϴ�.
	-------------------------------------------------------------
*/

/*
	LCD_SEND_CMD(command, arg)

	��ɾ� �ϳ��� LCD�� ������ ��ũ�� �Լ��Դϴ�.

	command: ���� ��ɾ� �̸��Դϴ�. ��� ������ ��ɾ� ����� �ǽ��ڷḦ �����ϼ���.
	arg: �̵��� ��ġ, ��� ��� ���� ��ɾ� �ڿ� �ٿ� ���� ���� ��Ʈ���Դϴ�.

	����: LCD_SEND_CMD()�� LCD_SEND_DATA() ��ũ�� �Լ��� ���� �����ӿ� ���ÿ� �� �� ������
		  �� �����ӿ� �� ���� ȣ���ؾ� �˴ϴ�.
*/
#define LCD_SEND_CMD(command, arg)							\
		(													\
			LCD_CLR_FLAG(RS), 								\
			PORT_LCD_DATA = CMD_LCD_##command | ( arg ),	\
			LCD_PULSE(),									\
			cooldown_LCD = COOLDOWN_LCD_##command			\
		)

/*
	LCD_SEND_DATA(data)

	������(���� Ŀ�� ��ġ�� ����� ����) �ϳ��� LCD�� ������ ��ũ�� �Լ��Դϴ�.

	data: ���� ���� ���Դϴ�. ��� ������ ���� ����� �ǽ��ڷḦ �����ϼ���.	

	����: LCD_SEND_CMD()�� LCD_SEND_DATA() ��ũ�� �Լ��� ���� �����ӿ� ���ÿ� �� �� ������
		  �� �����ӿ� �� ���� ȣ���ؾ� �˴ϴ�.
*/
#define LCD_SEND_DATA(data)						\
		(										\
			LCD_SET_FLAG(RS),					\
			PORT_LCD_DATA = ( data ),			\
			LCD_PULSE(),						\
			cooldown_LCD = COOLDOWN_LCD_DATA	\
		)

/*
	LCD_CHECK()

	���� LCD�� ����� �� �ִ��� ���θ� �Ǵ��� �� ����ϴ� ��ũ�� �Լ��Դϴ�.
	�� �Լ��� LCD ������ �ȿ��� ȣ���Ͽ� ������� 1�� ���� ���� �� ��ũ�� �Լ��� ����ϼ���.	

	����: LCD_CHECK() ��ũ�� �Լ��� �� �����ӿ� �� ���� ȣ���ؾ� �Ǹ�
		  �ݵ�� ȣ���ؾ� �մϴ�.
*/
#define LCD_CHECK()													\
		(															\
			cooldown_LCD > 0 ?										\
			(														\
				--cooldown_LCD,										\
				0													\
			) :														\
			internalState_LCD & INTERNALSTATE_LCD_READY ?			\
			1 :														\
			internalState_LCD & INTERNALSTATE_LCD_INIT_PORT ?		\
			(														\
				DDR_LCD_DATA = 0xFF,								\
				DDR_LCD_CTRL |= 0x07,								\
				cooldown_LCD = COOLDOWN_LCD_PORT,					\
				internalState_LCD = INTERNALSTATE_LCD_INIT_FUNC,	\
				0													\
			) :														\
			internalState_LCD & INTERNALSTATE_LCD_INIT_FUNC ?		\
			(														\
				LCD_SEND_CMD(FunctionSet, 0b11000),					\
				internalState_LCD = INTERNALSTATE_LCD_INIT_ON,		\
				0													\
			) :														\
			internalState_LCD & INTERNALSTATE_LCD_INIT_ON ?			\
			(														\
				LCD_SEND_CMD(DisplayControl, 0b100),				\
				internalState_LCD = INTERNALSTATE_LCD_INIT_CLEAR,	\
				0													\
			) :														\
			(														\
				LCD_SEND_CMD(ClearDisplay, 0),						\
				internalState_LCD = INTERNALSTATE_LCD_READY,		\
				0													\
			)														\
		)

