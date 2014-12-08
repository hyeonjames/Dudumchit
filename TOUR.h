/*
	2013�� �����б� ����ũ�����μ�������

	TOUR.h

	�ǽ� kit�� �ִ� Piezo module�� ����Ͽ� �Ҹ��� ���� ���� �ʿ��� ��ҵ��� �����մϴ�.
*/


/*
	TOUR ���̺귯�� ��� ���:

	0. ���� �� ���� 'TOUR ���� �κ�'�� ã�� ����
	   �� ������� ���� ������ �� �а�
	   �ڽ��� ����� ȯ�濡 �´� ������ ������ �����ϼ���.
	   
	   - ����: Piezo�� AVR ���� ī���� �� �� ����ϹǷ� ������ Ư�� ��(PB5)���� ���� �� �ֽ��ϴ�.

	1. �Ҹ��� �� '�Ǻ�'�� �ش��ϴ� unsigned char �迭�� �����ϰ�
	   �� ��ɾ �ۼ��Ͽ� �迭 �ʱ���� ä�켼��.

	2. �ڽ��� main() �ȿ� �ִ� ���� while���� �����ϱ� �� �κ�(DDRA, srand() �̷��� ���� �κ�)��
	   TOUR_INITIALIZE() ��ũ�� �Լ� ȣ�� ������ �߰��ϼ���.

	3. �ڽ��� main() �ȿ� �ִ� ���� while����
	   TOUR_UPDATE() ��ũ�� �Լ� ȣ�� ������ �߰��ϼ���.

   	4. ���ָ� ���� / �簳�ϰ� ���� �ڵ� ��ġ��
	   TOUR_PLAY() ��ũ�� �Լ� ȣ�� ������ �߰��ϼ���.
*/

#pragma once

/*
	----------------------------
	TOUR ���� �κ� ����
	----------------------------
*/

/* �ʱ� BPM��. ������ [50, 305] (�� ���� ���� �ٲ� �� T ��ɾ��� -50 ��Ģ�� ���� ���� ���� BPM���� ����ؾ� ��) */
#define TOUR_DEFAULT_BPM 60

/* �ʱ� ��Ÿ�갪. ������ [0, 255] */
#define TOUR_DEFAULT_OCTAVE 5

/* '5��Ÿ�� �� ��(880Hz)'�� ���� pulse�� �ʺ� (���ɻ��� ������ 4��Ÿ�� ��� 5��Ÿ�� ���, �� ���� �ٲ� ���� ���� ����) */
#define TOUR_WIDTH_BASIC 	4197UL		/* ����: �� ����� ������ �ݵ�� UL �Ǵ� L�� �ٿ� �־� ��! */

/* 1BPM(1�� �ȿ� 4����ǥ 1�� ����)���� 64����ǥ �ϳ��� ���̸�ŭ(3.75��) ���� ���� ���� �� �� ������ ���ƾ� �ϴ��� (�� ���� ���� �׻� �ٲ�� ��) */
#define TOUR_TICKS_BASIC	325000UL	/* ����: �� ����� ������ �ݵ�� UL �Ǵ� L�� �ٿ� �־� ��! */

/*
	----------------------------
	TOUR ���� �κ� ��. ���� �� �Ʒ��� �ִ� ��ũ�� �Լ��� ���� �װŸ� ���� ��.
	----------------------------
*/

/* 64����ǥ �ϳ��� ���̿� �ش��ϴ� tick�� */
extern unsigned long TOUR_current_ticks_per_64th_note;

/* TOUR �������� ������ ���� tick�� */
extern unsigned long TOUR_tick;

/* ���� ������ ��Ÿ�갪 */
extern unsigned char TOUR_current_octave;

/* ���� �������� ���� �󸶳� ���Ҵ��� - 1�� ��� ���� �����ӿ� ���� ���� */
extern unsigned char TOUR_remained_duration;

/* ���� �������� ���� pulse �ʺ� */
extern unsigned int TOUR_current_width;

/* Uwaaang ������ ������ pulse �ʺ� */
extern unsigned int TOUR_uwaaang_width_start;

/* Uwaaang ������ ���� pulse �ʺ� */
extern unsigned int TOUR_uwaaang_width_end;

/* Uwaaang ������ ��ü ���� - 0�� ��� Uwaaang ���ָ� �ϰ� ���� ������ �ǹ�, Uwaaang ���ָ� �����ϴ� ������ �����ӿ��� �� ���� 0���� �ʱ�ȭ�� �� */
extern unsigned int TOUR_uwaaang_duration;

/* ���� �������� �Ǻ� �迭�� ���� ��ġ(�Ǵ� M ��ɾ�� ��ũ�� ��ġ) */
extern unsigned char *TOUR_current_score;

/* �Ǻ� �迭 ���� �̹��� ������ ��ġ */
extern unsigned char *TOUR_current_data;

/* Piezo ����� ���� trigger ���� */
extern unsigned char TOUR_enabled;


/* �־��� bpm���� 64����ǥ �ϳ��� ���̿� �ش��ϴ� tick���� ����ϱ� ���� ��ũ�� �Լ� */
#define TOUR_GET_TICKS_PER_64TH_NOTE_FROM_BPM(bpm)	( TOUR_TICKS_BASIC / ( bpm ) )


/* 4��Ÿ�� ���鿡 ���� pulse�� �ʺ� */
#define TOUR_WIDTH_REST		0UL
#define TOUR_WIDTH_C		(TOUR_WIDTH_BASIC * 100 / 119)
#define TOUR_WIDTH_C_SHARP	(TOUR_WIDTH_BASIC * 100 / 126)
#define TOUR_WIDTH_D_FLAT	(TOUR_WIDTH_BASIC * 100 / 126)
#define TOUR_WIDTH_D		(TOUR_WIDTH_BASIC * 100 / 133)
#define TOUR_WIDTH_D_SHARP	(TOUR_WIDTH_BASIC * 100 / 141)
#define TOUR_WIDTH_E_FLAT	(TOUR_WIDTH_BASIC * 100 / 141)
#define TOUR_WIDTH_E		(TOUR_WIDTH_BASIC * 100 / 150)
#define TOUR_WIDTH_F		(TOUR_WIDTH_BASIC * 100 / 159)
#define TOUR_WIDTH_F_SHARP	(TOUR_WIDTH_BASIC * 100 / 168)
#define TOUR_WIDTH_G_FLAT	(TOUR_WIDTH_BASIC * 100 / 168)
#define TOUR_WIDTH_G		(TOUR_WIDTH_BASIC * 100 / 178)
#define TOUR_WIDTH_G_SHARP	(TOUR_WIDTH_BASIC * 100 / 189)
#define TOUR_WIDTH_A_FLAT	(TOUR_WIDTH_BASIC * 100 / 189)
#define TOUR_WIDTH_A		(TOUR_WIDTH_BASIC * 100 / 200)
#define TOUR_WIDTH_A_SHARP	(TOUR_WIDTH_BASIC * 100 / 212)
#define TOUR_WIDTH_B_FLAT	(TOUR_WIDTH_BASIC * 100 / 212)
#define TOUR_WIDTH_B		(TOUR_WIDTH_BASIC * 100 / 224)

/* �־��� ��Ÿ���� Ư�� ���� ���� �ʺ� ����� ����ϱ� ���� ��ũ�� �Լ� */
#define TOUR_WIDTH(name, oct)	( oct > 4 ? TOUR_WIDTH_##name >> ( oct - 4 ) : TOUR_WIDTH_##name << ( 4 - oct ) )


/*
	----------------------------
	TOUR ���̺귯�� �Լ� ���� ����. �� �Ʒ��� �ִ� �� �Լ��� �� ���� ����ϸ� ��.
	----------------------------
*/

/*
	TOUR_INITIALIZE()

	��Ʈ ���� �� Timer1 �ʱ�ȭ�� �����մϴ�.
	�ٸ� �ʱ�ȭ �ڵ��� �Բ� ���� while���� ���۵Ǳ� �� �κп� �� �Լ��� ȣ���ϴ� ������ �߰��ϼ���.
*/
#define TOUR_INITIALIZE() ( DDRB |= 0b00100000, TCCR1A = 0b01000000, TCCR1B = 0b00001010 )

/*
	TOUR_PLAY()

	�־��� �Ǻ� �迭�� ������ �������� ���� TOUR �����Ӻ��� Piezo ���ָ� �����մϴ�.
	���ָ� �����ϰų� �簳�ϰ� ���� �κп� �� �Լ��� ȣ���ϴ� ������ �߰��ϼ���.
	���� �ʱ�ȭ �ڵ� �ٷ� �Ʒ��� ���� �ξ �˴ϴ�.
*/
#define TOUR_PLAY(score) ( TOUR_current_score = ( score ), TOUR_current_data = ( score ), TOUR_remained_duration = 1, TOUR_enabled = 1 )

/*
	TOUR_STOP()

	Piezo ���ָ� �ߴ��մϴ�.
	���ָ� �ٽ� �����Ϸ��� TOUR_PLAY()�� �� ȣ���ϼ���.
*/
#define TOUR_STOP() ( OCR1A = 0, TOUR_enabled = 0 )

/*
	TOUR_UPDATE()

	Piezo ���ָ� ���� TOUR ������ �ڵ尡 ��� �ִ� �Լ��Դϴ�.
	���� while�� �ȿ� �� �Լ��� ȣ���ϴ� ������ �� �� ���� �߰��ϼ���.
*/
#define TOUR_UPDATE()																			\
		do																						\
		{																						\
			if ( TOUR_enabled )																	\
			{																					\
				if ( TOUR_tick >= TOUR_current_ticks_per_64th_note )							\
				{																				\
					--TOUR_remained_duration;													\
																								\
					if ( TOUR_remained_duration == 0 )											\
					{																			\
						while ( TOUR_remained_duration == 0 )									\
						{																		\
							switch ( *TOUR_current_data )										\
							{																	\
							case 'C':															\
								TOUR_current_width = TOUR_WIDTH(C, TOUR_current_octave);		\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'D':															\
								TOUR_current_width = TOUR_WIDTH(D, TOUR_current_octave);		\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'E':															\
								TOUR_current_width = TOUR_WIDTH(E, TOUR_current_octave);		\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'F':															\
								TOUR_current_width = TOUR_WIDTH(F, TOUR_current_octave);		\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'G':															\
								TOUR_current_width = TOUR_WIDTH(G, TOUR_current_octave);		\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'A':															\
								TOUR_current_width = TOUR_WIDTH(A, TOUR_current_octave);		\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'B':															\
								TOUR_current_width = TOUR_WIDTH(B, TOUR_current_octave);		\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'H':															\
								TOUR_current_width = TOUR_WIDTH(C_SHARP, TOUR_current_octave);	\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'I':															\
								TOUR_current_width = TOUR_WIDTH(D_SHARP, TOUR_current_octave);	\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'J':															\
								TOUR_current_width = TOUR_WIDTH(F_SHARP, TOUR_current_octave);	\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'K':															\
								TOUR_current_width = TOUR_WIDTH(G_SHARP, TOUR_current_octave);	\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'L':															\
								TOUR_current_width = TOUR_WIDTH(A_SHARP, TOUR_current_octave);	\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'T':															\
								++TOUR_current_data;											\
								TOUR_current_ticks_per_64th_note = TOUR_GET_TICKS_PER_64TH_NOTE_FROM_BPM((int)*TOUR_current_data + 50);	\
								++TOUR_current_data;											\
								break;															\
							case 'O':															\
								++TOUR_current_data;											\
								TOUR_current_octave = *TOUR_current_data;						\
								++TOUR_current_data;											\
								break;															\
							case 'U':															\
								++TOUR_current_data;											\
								TOUR_uwaaang_duration = *TOUR_current_data;						\
								++TOUR_current_data;											\
								switch ( *TOUR_current_data )												\
								{																			\
								case 'C':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(C, TOUR_uwaaang_duration);		\
									break;																	\
								case 'D':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(D, TOUR_uwaaang_duration);		\
									break;																	\
								case 'E':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(E, TOUR_uwaaang_duration);		\
									break;																	\
								case 'F':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(F, TOUR_uwaaang_duration);		\
									break;																	\
								case 'G':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(G, TOUR_uwaaang_duration);		\
									break;																	\
								case 'A':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(A, TOUR_uwaaang_duration);		\
									break;																	\
								case 'B':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(B, TOUR_uwaaang_duration);		\
									break;																	\
								case 'H':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(C_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								case 'I':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(D_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								case 'J':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(F_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								case 'K':																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(G_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								default:																	\
									TOUR_uwaaang_width_start = TOUR_WIDTH(A_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								}																			\
																								\
								++TOUR_current_data;											\
								TOUR_uwaaang_duration = *TOUR_current_data;						\
								++TOUR_current_data;											\
								switch ( *TOUR_current_data )												\
								{																			\
								case 'C':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(C, TOUR_uwaaang_duration);			\
									break;																	\
								case 'D':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(D, TOUR_uwaaang_duration);			\
									break;																	\
								case 'E':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(E, TOUR_uwaaang_duration);			\
									break;																	\
								case 'F':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(F, TOUR_uwaaang_duration);			\
									break;																	\
								case 'G':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(G, TOUR_uwaaang_duration);			\
									break;																	\
								case 'A':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(A, TOUR_uwaaang_duration);			\
									break;																	\
								case 'B':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(B, TOUR_uwaaang_duration);			\
									break;																	\
								case 'H':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(C_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								case 'I':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(D_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								case 'J':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(F_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								case 'K':																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(G_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								default:																	\
									TOUR_uwaaang_width_end = TOUR_WIDTH(A_SHARP, TOUR_uwaaang_duration);	\
									break;																	\
								}																			\
								++TOUR_current_data;											\
								TOUR_uwaaang_duration = *TOUR_current_data;						\
								++TOUR_current_data;											\
																								\
								TOUR_current_width = TOUR_uwaaang_width_start;					\
								TOUR_remained_duration = TOUR_uwaaang_duration;					\
								break;															\
							case 'R':															\
								TOUR_current_width = TOUR_WIDTH_REST;							\
								++TOUR_current_data;											\
								TOUR_remained_duration = *TOUR_current_data;					\
								++TOUR_current_data;											\
								break;															\
							case 'M':															\
								++TOUR_current_data;											\
								TOUR_current_score = TOUR_current_data;							\
								break;															\
							case '$':															\
								TOUR_current_width = TOUR_WIDTH_REST;							\
								TOUR_current_data = TOUR_current_score;							\
								TOUR_remained_duration = 1;										\
								TOUR_enabled = 0;												\
								break;															\
							default:															\
								TOUR_current_data = TOUR_current_score;							\
								break;															\
							}																	\
						}																		\
																								\
						OCR1A = TOUR_current_width;												\
					}																			\
					else if ( TOUR_uwaaang_duration != 0 )										\
					{																			\
						TOUR_current_width = TOUR_uwaaang_width_end - ( (long)TOUR_uwaaang_width_end - TOUR_uwaaang_width_start ) * TOUR_remained_duration / TOUR_uwaaang_duration;	\
						OCR1A = TOUR_current_width;												\
																								\
						if ( TOUR_remained_duration == 1 )										\
							TOUR_uwaaang_duration = 0;											\
					}																			\
																								\
					TOUR_tick = 0;																\
				}																				\
				else																			\
					++TOUR_tick;																\
			}																					\
		}																						\
		while ( 0 )

