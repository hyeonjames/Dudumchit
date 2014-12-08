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
		R, G, B 값을 토대로 16bit 색상 코드를 계산하는 매크로 함수입니다.
		아래에 있는 colors_OLED[] 배열의 초기식을 채울 때 활용하세요.
		이 라이브러리에선 16bit mode를 사용하고 있으며 R, G, B를 각각 5, 6, 5bit씩 사용하여 색을 표현합니다.
	
		설정 예:
			색		R	G	B
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
		R: 0 ~ 31, G: 0 ~ 63, B: 0 ~ 31로 입력하기 너무 귀찮다면
		RGB 모두 0 ~ 255 사이의 값을 입력하면 알아서 적절한 범위로 변환해 주는 이 매크로 함수를 사용하세요.
	*/
	#define COLOR256(R, G, B)	( (R) >> 3 << 11 | (G) >> 2 << 5 | (B) >> 3 )


	/*
		TEST mode에서 bitmap 대신 object를 그릴 때 쓰는 단색 목록입니다.
		단색 수를 바꾸려면 헤더 파일에서 OLED_NUMBER_OF_BITMAPS값을 바꿔야 한다는 점을 잊지 마세요.
	*/
	unsigned int colors_OLED[OLED_NUMBER_OF_BITMAPS] =	{	COLOR(31, 0, 0),	COLOR(0, 63, 0),	COLOR(0, 0, 31),	COLOR(0, 0, 0)
														};
#endif
