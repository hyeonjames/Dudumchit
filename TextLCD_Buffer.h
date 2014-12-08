/*
	2013년 가을학기 마이크로프로세서응용

	TextLCD_Buffer.h

	실습 키트의 2x16 Text LCD를 손쉽게 다루기 위한 더블 버퍼링 기능을 제공합니다.

	학생 여러분은 
	먼저 TextLCD.h의 윗부분에 있는 프레임 간격 및 포트 설정을 자신의 환경에 맞게 바꾸고
	메인 루프에 LCD_UPDATE(); 한 줄만 추가해 둔 다음
	출력을 바꾸고 싶을 때마다 buffer_LCD[] 배열의 각 칸에 원하는 문자를 넣어 두면
	라이브러리 안에서 자동적으로 LCD에 명령을 보내 화면을 갱신해 줍니다.

	TextLCD_Buffer.h.h에 있는 매크로 함수를 사용하려면
	프로젝트에 TextLCD.h, TextLCD.c, TextLCD_Buffer.c 파일이 포함되어 있어야 합니다.

	TextLCD_Buffer.h 라이브러리는 데이터 메모리를 68바이트(TextLCD.c에 있는 3바이트 포함)만큼 사용합니다.
*/

#pragma once
#include "TextLCD.h"

/* 자동 명령어 전송을 위해 추가로 사용하는 내부 state 값, 모두 READY 상태에서 파생됨 */
#define INTERNALSTATE_LCD_MOVECURSOR	INTERNALSTATE_LCD_READY
#define INTERNALSTATE_LCD_WRITEDATA		INTERNALSTATE_LCD_READY + 0x20

/* 버퍼 영역을 탐색할 때 사용하는 변수 */
extern unsigned char cursor_LCD;

/* 현재 LCD 화면에 '출력시켜 둔' 문자 목록 */
extern unsigned char window_LCD[0x20];


/*
	-------------------------------------------------------------
	이 주석 위에 있는 것들은 저언혀 신경쓸 필요 없습니다.
	-------------------------------------------------------------
*/

/*
	LCD 화면에 출력하고 싶은 문자들을 기록하는 버퍼 영역입니다.

	총 2x16칸이며
	LCD의 아랫줄 2번 칸에 'a'를 출력하고 싶다면
	buffer_LCD[16 + 2] = 'a';라고 적으면 됩니다.
	LCD 프레임이 돌돌 돌면서 버퍼 영역 변화를 감지한 다음
	알아서 명령어를 만들어 LCD에 보내줍니다.
*/
extern unsigned char buffer_LCD[0x20];

/*
	학생 여러분의 메인 루프에 딱 한 번 추가해야 할 매크로 함수입니다.

	버퍼 영역을 탐색하여 다시 출력할 칸을 찾은 다음 커서를 그 칸으로 옮기고
	해당 칸에 버퍼 영역에 있는 문자를 출력해 줍니다.
	LCD 프레임은 매우 빠른 속도로 돌기 때문에
	대부분의 상황에서 여러분이 이 함수의 내부 구조를 알 필요는 없습니다.
	그러니 그냥 쓰세요 ㅋ
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
