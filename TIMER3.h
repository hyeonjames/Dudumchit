/*
	2013년 가을학기 마이크로프로세서응용

	TIMER3.h

	ATMega128의 TIMER / COUNTER 3을 메인 프레임의 if문에서 사용하기 위해 여러분이 변경해야 할 설정값들이 정의되어 있습니다.
*/

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

/*
	----------------------------------------------------------------
	TIMER3 설정 부분
	----------------------------------------------------------------
*/

/*
	TIMER3가 1초에 몇 frame을 발생시킬지를 설정합니다.
*/
#define TIMER3_FRAMES_PER_SECOND	60

/*
	TIMER3가 한 frame을 발생시키기 위해 몇 번 째깍거리게 할 지를 [1 ~ 255] 사이의 값으로 설정합니다.
*/
#define TIMER3_TICKS_PER_FRAME		1

/*
	TIMER3의 배율을 설정합니다.
	1, 8, 64, 256, 1024 중에서 설정할 수 있습니다(그 외의 값은 컴파일 오류를 발생시킴).

	배율이 너무 크거나 너무 작은 경우 컴파일 과정에서 경고가 발생하니
	경고가 안 뜨는 적절한 값을 선택해서 사용하세요.
	모든 설정이 경고를 발생시키면 TICKS_PER_FRAME 값을 조금씩 키워 보세요.
	그래도 안 되면 조교에게 도움을 요청하세요.
*/
#define TIMER3_PRESCALE_FACTOR		64


/*
	현재 frame이 몇 번째 frame인지를 나타내는 값입니다.
	여러분의 메인 프레임 안에서 이 값을 토대로 현재 시각을 유추할 수 있습니다.

	주의:
		16bit 변수이므로 60FPS 기준으로 약 18분 정도가 지나면 overflow가 발생하니
		kit를 그 이상 오래 실행해야 할 경우가 생기면 별도의 처리 루틴을 추가해야 합니다.
		( 그냥 15분마다 kit를 껐다 켜는 것을 추천 )
*/
extern unsigned int TIMER3_current_frame;


/*
	----------------------------------------------------------------
	TIMER3 라이브러리 내부 코드 부분
	
	이 부분은 신경쓰지 않아도 됩니다.
	이 파일의 가장 아래에 있는 매크로 함수 부분만 확인하세요.
	----------------------------------------------------------------
*/


/*
	TIMER3 라이브러리 내부에서 사용하는 tick값입니다( 이 값은 바꾸면 안 됨 ).
*/
extern volatile unsigned char TIMER3_tick;

#define TIMER3_CLOCKS_PER_TICK		( 14745600UL / TIMER3_PRESCALE_FACTOR / TIMER3_FRAMES_PER_SECOND / TIMER3_TICKS_PER_FRAME )

#if TIMER3_PRESCALE_FACTOR == 1

	#define TIMER3_PRESCALE_BIT	0b00001001

#elif TIMER3_PRESCALE_FACTOR == 8

	#define TIMER3_PRESCALE_BIT	0b00001010

#elif TIMER3_PRESCALE_FACTOR == 64

	#define TIMER3_PRESCALE_BIT	0b00001011

#elif TIMER3_PRESCALE_FACTOR == 256

	#define TIMER3_PRESCALE_BIT	0b00001100

#elif TIMER3_PRESCALE_FACTOR == 1024

	#define TIMER3_PRESCALE_BIT	0b00001101

#else

	#error TIMER3_PRESCALE_FACTOR must be within 1, 8, 64, 256, 1024.

#endif


/*
	----------------------------------------------------------------
	TIMER3 라이브러리 매크로 함수 정의 부분
	----------------------------------------------------------------
*/

/* TIMER3를 초기화합니다. main() 가장 윗 부분에 적어 두면 됩니다. */
#define TIMER3_INITIALIZE() ( TCCR3A = 0b00000000, TCCR3B = 0b00001000, ETIMSK |= 0b00010000, OCR3A = TIMER3_CLOCKS_PER_TICK )

/*
	TIMER3를 켭니다. 메인 while문이 시작되기 바로 전 부분에 적어 두면 됩니다.

	주의: 이 매크로 함수를 호출한 다음 sei()를 호출해서 인터럽트를 허용해 두는 것을 잊지 마세요!
*/
#define TIMER3_START() ( TCCR3B |= TIMER3_PRESCALE_BIT )

/* TIMER3를 끕니다. 아마 대부분의 상황에서 이 매크로 함수를 쓸 일은 없을 것입니다. */
#define TIMER3_STOP() ( TCCR3B &= 0b11111000, TCNT3 = 0 )

/*
	메인 프레임의 if문 조건식에 들어갈, TIMER3를 검사하고 진행시키는 매크로 함수입니다.
	조건식에 이 함수 호출식만 하나 적으면
	위에서 설정한 FPS에 맞게 메인 프레임 코드를 실행할 수 있게 됩니다.
*/
#define TIMER3_CHECK() 									\
		(												\
			TIMER3_tick >= TIMER3_TICKS_PER_FRAME ?		\
			(											\
				TIMER3_tick -= TIMER3_TICKS_PER_FRAME,	\
				++TIMER3_current_frame,					\
				1										\
			) : 0										\
		)
