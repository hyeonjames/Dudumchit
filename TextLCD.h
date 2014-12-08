/*
	2013년 가을학기 마이크로프로세서응용

	TextLCD.h

	실습 키트의 2x16 Text LCD를 조작하기 위한 상수 / 변수들을 선언합니다.

	학생 여러분은 이 파일에서
	윗부분에 있는 프레임 간격 및 포트 설정을 자신의 환경에 맞게 바꾸고
	중간 내용은 무시한 채 맨 아래에 있는 매크로 함수 세 개만 보고 쓰면 됩니다.

	TextLCD.h에 있는 매크로 함수를 사용하려면
	프로젝트에 TextLCD.c 파일이 포함되어 있어야 합니다.

	주의: TextLCD_Buffer.h를 include하여 더블 버퍼링 라이브러리를 사용하는 경우
		  이 파일 윗부분의 환경 설정, 메인 루프 안에 LCD_UPDATE() 호출 구문 추가, buffer_LCD[] 배열에 원하는 문자 기록
		  ...을 제외한 다른 변수 / 함수는 전혀 볼 필요 없습니다.
		  자세한 내용은 TextLCD_Buffer.h의 주석을 참고하세요.

	TextLCD.h 라이브러리는 데이터 메모리를 3바이트만큼 사용합니다.
*/

#pragma once

#include <avr/io.h>

/*
	LCD에 명령어를 보내는 프레임 간격을 지정합니다.

	주의: 너무 작게 잡으면 LCD 오작동이 일어날 수 있으며
		  너무 크게 잡으면 LCD의 반응 속도가 그만큼 느려지게 됩니다.
		  따라서 이 값은 정상 작동 가능한 수준에서 가장 작은 값으로 설정하는 편이 좋습니다.
		  TextLCD_Buffer.h 라이브러리를 쓴다면 0x20 ~ 0x30,
		  그냥 TextLCD.h 라이브러리만 쓴다면 0x20 ~ 0x80 사이의 값이 좋겠군요.
*/
#define TICKS_PER_LCD_FRAME 0x80

/*
	LCD와 연결할 포트를 설정합니다.

	데이터를 보내는 LCD_DATA 포트는 8bit를 모두 사용하며
	컨트롤 신호를 보내는 LCD_CTRL 포트는 하위 3bit만 사용합니다.
	이 라이브러리에선 LCD_CTRL 포트의 상위 5bit를 전혀 건드리지 않으니
	필요한 경우 남는 핀을 다른 모듈과 연결할 때 사용할 수 있습니다.
*/
#define DDR_LCD_DATA DDRC
#define DDR_LCD_CTRL DDRG

#define PORT_LCD_DATA PORTC
#define PORT_LCD_CTRL PORTG

/*
	메인 루프에서 값을 1씩 증가시키며 주기적으로 프레임 코드를 실행시키기 위한 변수입니다.
	실습 시간에 매번 쓰던 방식대로 if문을 써서 코드를 작성하면 됩니다.
*/
extern unsigned char tick_LCD;

/*
	--------------------------------------------------------
	여기서부터 아래에 있는 내용은
	맨 아래에 있는 세 매크로 함수를 제외하면
	전혀 몰라도 괜찮습니다.
	--------------------------------------------------------
*/


/* LCD 컨트롤 신호를 보내기 위해 사용하는 각 비트 정의 */
#define FLAG_LCD_E	0b100
#define FLAG_LCD_RW	0b010
#define FLAG_LCD_RS 0b001

/* LCD를 조작하기 위해 보내는 각 명령어 포맷 정의 */
#define CMD_LCD_ClearDisplay		0b00000001
#define CMD_LCD_ReturnHome			0b00000010
#define CMD_LCD_EntryModeSet		0b00000100
#define CMD_LCD_DisplayControl		0b00001000
#define CMD_LCD_CursorDisplayShift	0b00010000
#define CMD_LCD_FunctionSet			0b00100000
#define CMD_LCD_SetCGAddress		0b01000000
#define CMD_LCD_SetDDAddress		0b10000000

/*
	각 명령어마다 추가로 필요한 대기 시간 정의.
	0인 경우 다음 프레임에 바로 다른 작업을 할 수 있음을 의미.
	주의: 여기 있는 값은 그냥 적은게 아니라 LCD 모듈 특성에 맞추어 둔 것이니 수정하지 않는 편이 좋음.
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

/* LCD 프레임 안에서 사용하는 state값 */
#define INTERNALSTATE_LCD_INIT_PORT		0x01
#define INTERNALSTATE_LCD_INIT_FUNC		0x02
#define INTERNALSTATE_LCD_INIT_ON		0x04
#define INTERNALSTATE_LCD_INIT_CLEAR	0x08
#define INTERNALSTATE_LCD_READY			0x10

/*
	LCD 프레임에서 사용하는 변수 선언(위의 tick 변수를 포함하여 총 3바이트).
	각 변수는 TextLCD.c에 정의되어 있음.
*/
extern unsigned char internalState_LCD;
extern unsigned char cooldown_LCD;

/* 각 비트 이름(E, RW, RS)을 argument로 받아 해당 비트를 1 또는 0으로 설정하는 매크로 함수 */
#define LCD_SET_FLAG(name) ( PORT_LCD_CTRL |= FLAG_LCD_##name )
#define LCD_CLR_FLAG(name) ( PORT_LCD_CTRL &= ~FLAG_LCD_##name )

/* LCD에 명령어를 전송하기 위해 E bit를 아주아주 잠깐 1로 만들었다 0으로 되돌리는 매크로 함수 */
#define LCD_PULSE() ( LCD_SET_FLAG(E), LCD_CLR_FLAG(E) )


/*
	-------------------------------------------------------------
	이 주석 위에 있는 복잡한 내용은 저언혀 신경쓸 필요 없습니다.
	-------------------------------------------------------------
*/

/*
	LCD_SEND_CMD(command, arg)

	명령어 하나를 LCD로 보내는 매크로 함수입니다.

	command: 보낼 명령어 이름입니다. 사용 가능한 명령어 목록은 실습자료를 참고하세요.
	arg: 이동할 위치, 모드 등과 같이 명령어 뒤에 붙여 같이 보낼 비트값입니다.

	주의: LCD_SEND_CMD()와 LCD_SEND_DATA() 매크로 함수는 같은 프레임에 동시에 쓸 수 없으며
		  한 프레임에 한 번만 호출해야 됩니다.
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

	데이터(현재 커서 위치에 출력할 문자) 하나를 LCD로 보내는 매크로 함수입니다.

	data: 보낼 문자 값입니다. 사용 가능한 문자 목록은 실습자료를 참고하세요.	

	주의: LCD_SEND_CMD()와 LCD_SEND_DATA() 매크로 함수는 같은 프레임에 동시에 쓸 수 없으며
		  한 프레임에 한 번만 호출해야 됩니다.
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

	현재 LCD를 사용할 수 있는지 여부를 판단할 때 사용하는 매크로 함수입니다.
	이 함수를 LCD 프레임 안에서 호출하여 결과식이 1일 때만 위의 두 매크로 함수를 사용하세요.	

	주의: LCD_CHECK() 매크로 함수는 한 프레임에 한 번만 호출해야 되며
		  반드시 호출해야 합니다.
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

