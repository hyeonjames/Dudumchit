/*
	2013�� �����б� ����ũ�����μ�������

	TextLCD_Buffer.h

	�ǽ� ŰƮ�� 2x16 Text LCD�� �ս��� �ٷ�� ���� ���� ���۸� ����� �����մϴ�.

	�л� �������� 
	���� TextLCD.h�� ���κп� �ִ� ������ ���� �� ��Ʈ ������ �ڽ��� ȯ�濡 �°� �ٲٰ�
	���� ������ LCD_UPDATE(); �� �ٸ� �߰��� �� ����
	����� �ٲٰ� ���� ������ buffer_LCD[] �迭�� �� ĭ�� ���ϴ� ���ڸ� �־� �θ�
	���̺귯�� �ȿ��� �ڵ������� LCD�� ����� ���� ȭ���� ������ �ݴϴ�.

	TextLCD_Buffer.h.h�� �ִ� ��ũ�� �Լ��� ����Ϸ���
	������Ʈ�� TextLCD.h, TextLCD.c, TextLCD_Buffer.c ������ ���ԵǾ� �־�� �մϴ�.

	TextLCD_Buffer.h ���̺귯���� ������ �޸𸮸� 68����Ʈ(TextLCD.c�� �ִ� 3����Ʈ ����)��ŭ ����մϴ�.
*/

#pragma once
#include "TextLCD.h"

/* �ڵ� ��ɾ� ������ ���� �߰��� ����ϴ� ���� state ��, ��� READY ���¿��� �Ļ��� */
#define INTERNALSTATE_LCD_MOVECURSOR	INTERNALSTATE_LCD_READY
#define INTERNALSTATE_LCD_WRITEDATA		INTERNALSTATE_LCD_READY + 0x20

/* ���� ������ Ž���� �� ����ϴ� ���� */
extern unsigned char cursor_LCD;

/* ���� LCD ȭ�鿡 '��½��� ��' ���� ��� */
extern unsigned char window_LCD[0x20];


/*
	-------------------------------------------------------------
	�� �ּ� ���� �ִ� �͵��� ������ �Ű澵 �ʿ� �����ϴ�.
	-------------------------------------------------------------
*/

/*
	LCD ȭ�鿡 ����ϰ� ���� ���ڵ��� ����ϴ� ���� �����Դϴ�.

	�� 2x16ĭ�̸�
	LCD�� �Ʒ��� 2�� ĭ�� 'a'�� ����ϰ� �ʹٸ�
	buffer_LCD[16 + 2] = 'a';��� ������ �˴ϴ�.
	LCD �������� ���� ���鼭 ���� ���� ��ȭ�� ������ ����
	�˾Ƽ� ��ɾ ����� LCD�� �����ݴϴ�.
*/
extern unsigned char buffer_LCD[0x20];

/*
	�л� �������� ���� ������ �� �� �� �߰��ؾ� �� ��ũ�� �Լ��Դϴ�.

	���� ������ Ž���Ͽ� �ٽ� ����� ĭ�� ã�� ���� Ŀ���� �� ĭ���� �ű��
	�ش� ĭ�� ���� ������ �ִ� ���ڸ� ����� �ݴϴ�.
	LCD �������� �ſ� ���� �ӵ��� ���� ������
	��κ��� ��Ȳ���� �������� �� �Լ��� ���� ������ �� �ʿ�� �����ϴ�.
	�׷��� �׳� ������ ��
*/
#define LCD_UPDATE()																									\
		(																												\
			tick_LCD >= TICKS_PER_LCD_FRAME ?																			\
			(																											\
				LCD_CHECK() ?																							\
				(																										\
					internalState_LCD == INTERNALSTATE_LCD_MOVECURSOR ?													\
					(																									\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
																														\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
																														\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
																														\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F,			\
						window_LCD[cursor_LCD] == buffer_LCD[cursor_LCD] ? ( ++cursor_LCD, cursor_LCD &= 0x1F			\
						):0):0):0):0):0):0):0):0																		\
						):0):0):0):0):0):0):0):0																		\
						):0):0):0):0):0):0):0):0																		\
						):0):0):0):0):0):0):0):0,																		\
																														\
						LCD_SEND_CMD(SetDDAddress, cursor_LCD >= 0x10 ? cursor_LCD + 0x30 : cursor_LCD),				\
						internalState_LCD = INTERNALSTATE_LCD_WRITEDATA													\
					) :																									\
					(																									\
						LCD_SEND_DATA(buffer_LCD[cursor_LCD]),															\
						window_LCD[cursor_LCD] = buffer_LCD[cursor_LCD],												\
						internalState_LCD = INTERNALSTATE_LCD_MOVECURSOR												\
					)																									\
				) :																										\
				0,																										\
				tick_LCD = 0																							\
			) :																											\
			++tick_LCD																									\
		)
