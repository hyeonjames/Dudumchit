/*
	2013년 가을학기 마이크로프로세서응용

	TextLCD.c

	실습 키트의 2x16 Text LCD를 조작하기 위해 라이브러리에서 사용하는 변수들이 정의되어 있습니다.

	학생 여러분은 이 파일의 내용을 전혀 신경쓰지 않아도 됩니다.
	(오히려, 여기 있는 변수들의 값을 맘대로 바꾸면 라이브러리 오작동의 원인이 됩니다)

	TextLCD.h에 있는 매크로 함수를 사용하려면
	프로젝트에 이 파일이 반드시 포함되어 있어야 합니다.

	TextLCD.h 라이브러리는 데이터 메모리를 3바이트만큼 사용합니다.
*/

#include "TextLCD.h"

/* LCD 프레임을 굴리기 위한 tick 변수 */
unsigned char tick_LCD = 0;

/* LCD 프레임 안에서 사용하는 state 변수 */
unsigned char internalState_LCD = INTERNALSTATE_LCD_INIT_PORT;

/* 각 명령어의 수행 시간만큼 다음 프레임을 지연시키기 위한 쿨다운 변수 */
unsigned char cooldown_LCD = COOLDOWN_LCD_STARTUP;
