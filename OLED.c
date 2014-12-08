#include "OLED.h"

struct OLED_Bitmap bitmaps_OLED[OLED_NUMBER_OF_BITMAPS];

struct OLED_Object objects_OLED[OLED_MAX_NUMBER_OF_OBJECTS];
struct OLED_Object* z_heads_OLED[OLED_MAX_Z_INDEX + 1];
struct OLED_Object* z_tails_OLED[OLED_MAX_Z_INDEX + 1];

struct OLED_Object* unused_objects_OLED;

struct OLED_Object* current_object_OLED;
struct OLED_Object* first_object_OLED;

unsigned char triggers_OLED = OLED_TRG_COMPLETED;

#if OLED_TEST != 0

	/*
		R, G, B ���� ���� 16bit ���� �ڵ带 ����ϴ� ��ũ�� �Լ��Դϴ�.
		�Ʒ��� �ִ� colors_OLED[] �迭�� �ʱ���� ä�� �� Ȱ���ϼ���.
		�� ���̺귯������ 16bit mode�� ����ϰ� ������ R, G, B�� ���� 5, 6, 5bit�� ����Ͽ� ���� ǥ���մϴ�.
	
		���� ��:
			��		R	G	B
			Black	0	0	0

			White	31	63	31

			Red		31	0	0
			Green	0	63	0
			Blue	0	0	31

			Cyan	0	63	31
			Magenta	31	0	31
			Yellow	31	63	0
	*/
	#define COLOR(R, G, B)		( (R) << 11 | (G) << 5 | (B) )

	/*
		R: 0 ~ 31, G: 0 ~ 63, B: 0 ~ 31�� �Է��ϱ� �ʹ� �����ٸ�
		RGB ��� 0 ~ 255 ������ ���� �Է��ϸ� �˾Ƽ� ������ ������ ��ȯ�� �ִ� �� ��ũ�� �Լ��� ����ϼ���.
	*/
	#define COLOR256(R, G, B)	( (R) >> 3 << 11 | (G) >> 2 << 5 | (B) >> 3 )


	/*
		TEST mode���� bitmap ��� object�� �׸� �� ���� �ܻ� ����Դϴ�.
		�ܻ� ���� �ٲٷ��� ��� ���Ͽ��� OLED_NUMBER_OF_BITMAPS���� �ٲ�� �Ѵٴ� ���� ���� ������.
	*/
	unsigned int colors_OLED[OLED_NUMBER_OF_BITMAPS] =	{	COLOR(31, 0, 0),	COLOR(0, 63, 0),	COLOR(0, 0, 31),	COLOR(0, 0, 0)
														};
#endif
