/*
	2013년 가을학기 마이크로프로세서응용

	TextLCD_Buffer.c

	실습 키트의 2x16 Text LCD를 손쉽게 다루기 위한 더블 버퍼링 기능을 제공합니다.


	학생 여러분은 이 파일의 내용을 전혀 신경쓰지 않아도 됩니다.
	(오히려, 여기 있는 변수들의 값을 맘대로 바꾸면 라이브러리 오작동의 원인이 됩니다)

	TextLCD_Buffer.h에 있는 매크로 함수를 사용하려면
	프로젝트에 TextLCD.c, TextLCD_Buffer.c 파일이 포함되어 있어야 합니다.

	TextLCD_Buffer.h 라이브러리는 데이터 메모리를 68바이트(TextLCD.c에 있는 3바이트 포함)만큼 사용합니다.
*/

#include "TextLCD_Buffer.h"

/* 버퍼 영역을 탐색할 때 사용하는 변수 */
unsigned char cursor_LCD = 0;

/* 현재 LCD 화면에 '출력시켜 둔' 문자 목록 */
unsigned char window_LCD[0x20] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
								   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

/* 지금 LCD 화면에 '출력시키고 싶은' 문자 목록, window_LCD와의 비교를 통해 '달라진 문자'를 찾아 write 명령을 보내게 됨 */
unsigned char buffer_LCD[0x20] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
								   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
