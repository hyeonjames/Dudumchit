/*
	2013�� �����б� ����ũ�����μ�������

	TIMER3.h

	ATMega128�� TIMER / COUNTER 3�� ���� �������� if������ ����ϱ� ���� �������� �����ؾ� �� ���������� ���ǵǾ� �ֽ��ϴ�.
*/

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

/*
	----------------------------------------------------------------
	TIMER3 ���� �κ�
	----------------------------------------------------------------
*/

/*
	TIMER3�� 1�ʿ� �� frame�� �߻���ų���� �����մϴ�.
*/
#define TIMER3_FRAMES_PER_SECOND	60

/*
	TIMER3�� �� frame�� �߻���Ű�� ���� �� �� °��Ÿ��� �� ���� [1 ~ 255] ������ ������ �����մϴ�.
*/
#define TIMER3_TICKS_PER_FRAME		1

/*
	TIMER3�� ������ �����մϴ�.
	1, 8, 64, 256, 1024 �߿��� ������ �� �ֽ��ϴ�(�� ���� ���� ������ ������ �߻���Ŵ).

	������ �ʹ� ũ�ų� �ʹ� ���� ��� ������ �������� ��� �߻��ϴ�
	��� �� �ߴ� ������ ���� �����ؼ� ����ϼ���.
	��� ������ ��� �߻���Ű�� TICKS_PER_FRAME ���� ���ݾ� Ű�� ������.
	�׷��� �� �Ǹ� �������� ������ ��û�ϼ���.
*/
#define TIMER3_PRESCALE_FACTOR		64


/*
	���� frame�� �� ��° frame������ ��Ÿ���� ���Դϴ�.
	�������� ���� ������ �ȿ��� �� ���� ���� ���� �ð��� ������ �� �ֽ��ϴ�.

	����:
		16bit �����̹Ƿ� 60FPS �������� �� 18�� ������ ������ overflow�� �߻��ϴ�
		kit�� �� �̻� ���� �����ؾ� �� ��찡 ����� ������ ó�� ��ƾ�� �߰��ؾ� �մϴ�.
		( �׳� 15�и��� kit�� ���� �Ѵ� ���� ��õ )
*/
extern unsigned int TIMER3_current_frame;


/*
	----------------------------------------------------------------
	TIMER3 ���̺귯�� ���� �ڵ� �κ�
	
	�� �κ��� �Ű澲�� �ʾƵ� �˴ϴ�.
	�� ������ ���� �Ʒ��� �ִ� ��ũ�� �Լ� �κи� Ȯ���ϼ���.
	----------------------------------------------------------------
*/


/*
	TIMER3 ���̺귯�� ���ο��� ����ϴ� tick���Դϴ�( �� ���� �ٲٸ� �� �� ).
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
	TIMER3 ���̺귯�� ��ũ�� �Լ� ���� �κ�
	----------------------------------------------------------------
*/

/* TIMER3�� �ʱ�ȭ�մϴ�. main() ���� �� �κп� ���� �θ� �˴ϴ�. */
#define TIMER3_INITIALIZE() ( TCCR3A = 0b00000000, TCCR3B = 0b00001000, ETIMSK |= 0b00010000, OCR3A = TIMER3_CLOCKS_PER_TICK )

/*
	TIMER3�� �մϴ�. ���� while���� ���۵Ǳ� �ٷ� �� �κп� ���� �θ� �˴ϴ�.

	����: �� ��ũ�� �Լ��� ȣ���� ���� sei()�� ȣ���ؼ� ���ͷ�Ʈ�� ����� �δ� ���� ���� ������!
*/
#define TIMER3_START() ( TCCR3B |= TIMER3_PRESCALE_BIT )

/* TIMER3�� ���ϴ�. �Ƹ� ��κ��� ��Ȳ���� �� ��ũ�� �Լ��� �� ���� ���� ���Դϴ�. */
#define TIMER3_STOP() ( TCCR3B &= 0b11111000, TCNT3 = 0 )

/*
	���� �������� if�� ���ǽĿ� ��, TIMER3�� �˻��ϰ� �����Ű�� ��ũ�� �Լ��Դϴ�.
	���ǽĿ� �� �Լ� ȣ��ĸ� �ϳ� ������
	������ ������ FPS�� �°� ���� ������ �ڵ带 ������ �� �ְ� �˴ϴ�.
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
