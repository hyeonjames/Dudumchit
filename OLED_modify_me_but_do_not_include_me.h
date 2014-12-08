/*
	2013년 가을학기 마이크로프로세서응용

	OLED_modify_me_but_do_not_include_me.h

	실습 키트의 128x128 OLED를 조작하기 위해 여러분이 변경해야 할 설정값들이 정의되어 있습니다.

	OLED를 쓰기 위해, 여러분은 이 파일에 있는 내용만 잘 이해하고 쓰면 됩니다.
*/

#include <avr/io.h>

#pragma once


/*
	TEST mode를 사용할 것인지 여부를 설정합니다.
	이 값이 0인 경우 설정한 실제 bitmap을 사용하여 object를 화면에 그립니다.
	이 값이 0이 아닌 경우 각 bitmap 대신 단색을 사용하여 object를 화면에 그립니다.
*/
#define OLED_TEST					0


/*
	구형 키트를 사용할 경우 이 값을 0이 아닌 값으로 만들어 두면
	라이브러리 코드를 아주 약간 느리게 실행해서 안정성을 높여 줍니다.
	만약 이 값을 0으로 둬도 OLED가 잘 동작한다면 그냥 0으로 두고 쓰세요.
*/
#define OLED_2010_MODE				1


/*
	----------------------------------------------------------------------
	포트 설정 부분

	맨날 하는 부분이니 설명은 생략합니다.
	CTRL port: 모든 핀 사용
			   주의: 실제로는 0~4번 핀만 쓰지만 성능상의 문제로 다른 핀을 다른 용도로 쓸 순 없습니다.
					 역시 성능상의 문제로... CTRL port는 PORT A ~ E 중 하나를 쓰는 것이 좋습니다.
					 왜인지는 직접 컴파일해보면 알게 될 듯?
	DATA port: 모든 핀 사용
			   주의: CTRL port와 마찬가지 이유로 PORT A ~ E 중 하나를 쓰는 것이 좋습니다.
	----------------------------------------------------------------------
*/
#define DDR_OLED_CTRL	DDRF
#define DDR_OLED_DATA	DDRD

#define PORT_OLED_CTRL	PORTF
#define PORT_OLED_DATA	PORTD

/*
	----------------------------------------------------------------------
	리소스 설정 부분

	OLED는 꽤 많은 리소스 메모리를 필요로 하므로
	프로그램에서 딱 필요한 만큼만 리소스 크기를 잡아 두는 편이 좋습니다.
	----------------------------------------------------------------------
*/

/*
	프로그램에서 얼마나 많은 bitmap 배열을 사용할 것인지를 나타냅니다.
*/
#define OLED_NUMBER_OF_BITMAPS		50

/*
	프로그램에서 동시에 얼마나 많은 object를 화면에 그릴 것인지를 나타냅니다.
*/
#define OLED_MAX_NUMBER_OF_OBJECTS	40

/*
	각 object를 화면에 그리기 위해 얼마나 많은 'layer'를 사용할 것인지를 나타냅니다.
	z-index 값이 클수록 더 늦게 그려지며 결과적으로 다른 object들보다 위에 있는 것처럼 보이게 됩니다.
	같은 z-index 값을 가진 object들 중에서는 나중에 CREATE된 object가 더 늦게 그려집니다.
*/
#define OLED_MAX_Z_INDEX			3

/*
	배경색으로 사용할 색상을 나타냅니다.
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
#define OLED_BGCOLOR_R		31
#define OLED_BGCOLOR_G		63
#define OLED_BGCOLOR_B		31


/*
	TEST mode일 때 각 bitmap 번호에 따라 object를 칠할 색상을 나타내는 배열입니다.
	이건 extern 선언이니 여기서 색상을 입력할 순 없고
	OLED.c에 있는 이 변수 선언에서 배열 초기값을 설정해 주면 됩니다.
*/
#if OLED_TEST != 0
	
	extern unsigned int colors_OLED[OLED_NUMBER_OF_BITMAPS];

#endif



/*
	----------------------------------------------------------------------
	OLED.h에 있는 라이브러리 구조체 / 함수 설명 부분
	(이 아래에 있는 내용은 컴파일되지 않음, 그냥 설명용임)
	----------------------------------------------------------------------
*/
#ifdef THESE_CODES_ARE_JUST_FOR_EXAMPLE

	OLED 라이브러리 사용 방법

	0. 먼저 이 헤더 파일의 위에 있는 각 상수값을 여러분의 프로그램에 맞게 설정하세요.
	
		-	TEST mode는 개발 초기에 이진수 마스터가 아직 이미지 파일을 준비하지 못 했을 때 특히 유용합니다.
			/* 이 mode를 쓸 때는 OLED.c에 있는 colors_OLED[] 초기값을 설정해서
			각 이미지 대신 사용할 색상을 정해 놓아야 합니다. */

		-	PORT 설정은 뭐 매일 하는 일이니 설명은 생략.
			단, OLED는 엄청나게 많은 작업을 하기 때문에 상대적으로 느린 PORTF, PORTG는 쓰지 말아야 합니다.
			/* 이 PORT들을 쓰면 프로그램 크기가 어마어마하게 커짐 -> 개느려짐 */

		-	BITMAP 수, OBJECT 최대량, Z-INDEX 최대값은 작게 잡을수록 Data memory를 절약할 수 있으니
			여러분 프로그램에서 사용할 딱 그만큼만 잡아 두고 쓰세요.
			/* 컴파일했을 때 Data 메모리가 100% 이상 Full 되면 Fail */

		-	배경색은 kit를 켜면 OLED에 맨 처음 표시되는 바로 그 색입니다.
			RGB 숫자 잡기가 좀 까다롭긴 하지만 한 번 정해 두면 안 바꾸는 값이니 그냥 잘 정하세요.

	1. TEST mode를 쓰지 않는 경우,
	   수업자료실의 이미지 변환 프로그램을 써서 각 비트맵별 헤더/코드 파일을 얻은 다음
	   그 파일들을 프로젝트에 추가하고
	   메인 코드 파일에서 비트맵 헤더 파일을 include하고
	   main() 시작 부분에 bitmaps_OLED[] 배열 할당식을 적으세요.

	    -	새 파일을 프로젝트에 추가할 땐 먼저 해당 파일들을 프로젝트 폴더에 옮겨 둔 다음 드래그 & 드롭 하세요.

		-	할당 예제: bitmaps_OLED[] 배열의 0번 칸에 box_1 비트맵을 할당할 경우
			
				bitmaps_OLED[0].ptr_data = (prog_uint16_t*)box_1;
				bitmaps_OLED[0].width = 32;
				bitmaps_OLED[0].height = 32;
				/* width랑 height는 box_1.h에 적혀 있음 */

				이렇게 할당하면 이제 '0번 비트맵'은 box_1을 말하는 것이 됩니다.

	2. main() 시작 부분에 OLED_INITIALIZE();를 적으세요.

	3. 메인 while문 안에 OLED_UPDATE();를 적으세요.
	   보통 출력 프레임은 입력 프레임 아래, 메인 프레임 위에 적습니다.

	4. 메인 프레임에서는 다음과 같은 라이브러리 함수를 쓸 수 있습니다:

		OLED_OBJECT_CREATE(z-index, isScalable)

			-	새 object(화면에 출력할 어떤 물건 하나)를 생성하고 그 object의 포인터를 반환합니다.
				새 object의 z-index는 주어진 값으로 설정됩니다.
				/* z-index가 클수록 화면상의 위에 위치하게 됩니다. 값 범위는 [0 ~ OLED_MAX_Z_INDEX]입니다. */
				isScalable이 0이 아니면 비트맵 크기와 object 크기가 다를 때 자동으로 확대/축소를 해 줍니다. (대신 더 느립니다)
				isScalable이 0이면 object를 그릴 때 비트맵을 그냥 가져와 그립니다. (항상 object 크기를 비트맵 크기와 같게 설정해 두어야 합니다)
				체력 게이지같이 길이가 들쑥날쑥해지는 그림을 그릴 때 scale 기능을 사용하세요.

			-	반환된 포인터는 재발급이 불가능하니, 여러분이 직접 변수를 선언해서 값을 기록해 두어야 합니다.

			-	방금 만든 object엔 아무 것도 들어 있지 않습니다. 여러분이 직접 -> 연산자로 설정해 주어야 합니다.

			-	설정 예제:

					struct OLED_Object* ptr_object = OLED_OBJECT_CREATE(0, 0);	/* z-index가 0이고 scale 기능을 안 쓰는 새 object 생성 */					
					ptr_object->idx_bitmap = 0;		/* 이 object를 그릴 때 '0번 비트맵'을 사용 */
					ptr_object->left = 0;			/* 이 object의 가장 왼쪽 픽셀의 x좌표는 0 */
					ptr_object->top = 0;			/* 이 object의 가장 윗 픽셀의 y좌표는 0 */
					ptr_object->right = 9;			/* 이 object의 가장 오른쪽 픽셀의 x좌표는 9 */
					ptr_object->bottom = 9;			/* 이 object의 가장 아랫 픽셀의 y좌표는 9 */

					이렇게 설정하면 ptr_object는 '0번 비트맵'을 사용하여 (0, 0)에서 그리기 시작하는 10x10픽셀 그림이 됩니다.
					/* OLED_Object 구조체에는 이것들 말고도 다른 변수들이 더 있지만 그 값들은 절대 변경하면 안 됩니다! */
					
			-	주의: 갓 만들어진 object는 화면에 출력되지 않습니다.
					  아래에서 설명할 OLED_INVALIDATE_SIMPLE(ptr_object);를 호출해야 화면에 그려지게 됩니다.


		OLED_OBJECT_DELETE(ptr_object)
		OLED_OBJECT_DELETE_SIMPLE(ptr_object)

			-	해당 포인터가 가리키는 object를 완전히 제거합니다.
				제거된 object는 다음 CREATE에서 재활용될때까지 화면에 영향을 주지 않습니다.

			-	일반 버전은 object를 제거하기 전에 먼저 화면에서 지웁니다.
				간소화 버전은 이러한 지우기 과정을 하지 않습니다.

			-	실제 DELETE 작업을 수행하려면 메인 프레임이 끝나기 전에 OLED_INVALIDATE();를 한 번 호출해 주어야 합니다.


		OLED_OBJECT_HIDE(ptr_object)
		OLED_OBJECT_SHOW(ptr_object)

			-	해당 포인터가 가리키는 object를 화면에서 잠시 지우고, 지웠던 object를 다시 화면에 표시합니다.

			-	지워진 object는 다시 표시할 때까지 그리기 작업에 영향을 주지 않습니다.

			-	실제 HIDE / SHOW 작업을 수행하려면 메인 프레임이 끝나기 전에 OLED_INVALIDATE();를 한 번 호출해 주어야 합니다.


		OLED_OBJECT_FREEZE(ptr_object)
		OLED_OBJECT_UNFREEZE(ptr_object)

			-	Freeze란 어떤 object가 아래에서 설명할 'invalidation chain'에 영향을 받거나 주지 않도록 하는 것을 말합니다.

			-	대부분의 경우에 이 함수는 필요하지 않습니다.
				만약 극단적으로 성능을 높여야 할 필요가 있다면, 조교와 상의하여 이 함수를 사용함으로써 필요한 반응성을 확보할 수 있습니다.

			-	실제 FREEZE / UNFREEZE 작업을 수행하려면 메인 프레임이 끝나기 전에 OLED_INVALIDATE();를 한 번 호출해 주어야 합니다.


		OLED_INVALIDATE_OBJECT(ptr_object)
		OLED_INVALIDATE_OBJECT_SIMPLE(ptr_object)

			-	Invalidate란 어떤 object를 설정 변경, 겹침 등의 이유로 다시 그리도록 하는 것을 말합니다.
				이 중, '겹침'에 해당하는 invalidation은 'invalidation chain'을 통해 자동으로 수행됩니다.
				(어떤 object를 INVALIDATE하면 그 object와 겹쳐 있는 모든 object들을 같이 INVALIDATE해 줍니다)

			-	일반 버전은 object를 다시 그리기 전에 먼저 화면에서 지웁니다. ( object 위치가 바뀐 경우 이걸 호출 )
				간소화 버전은 이러한 지우기 과정을 하지 않습니다. ( CREATE 후 처음 그리거나 같은 위치에 다시 그리는 경우 이걸 호출 )

			-	실제 INVALIDATE 작업을 수행하려면 메인 프레임이 끝나기 전에 OLED_INVALIDATE();를 한 번 호출해 주어야 합니다.


		OLED_INVALIDATE()

			-	전체 object 목록을 재검토하여
				INVALIDATE, HIDE, SHOW, FREEZE, UNFREEZE된 object들을 처리하도록 지시하는 함수입니다.

			-	따라서 이번 메인 프레임에서 이러한 작업을 여러분이 수행했다면, 메인 프레임이 끝나기 전에 이 함수를 호출해 주어야 합니다.
				/* 한 프레임 안에서 여러 번 호출하는 것은 무방합니다 */


		OLED_REFRESH()

			-	OLED_INVALIDATE()의 강화판입니다.
				전체 화면을 배경색으로 말끔히 칠하고
				모든 HIDE | FREEZE 상태가 아닌 object들을 화면에 다 다시 그려줍니다.

			-	화면이 잠시 깜빡이긴 하겠지만,
				만약 화면이 내 마음대로 잘 보이지 않는다면
				이를 해결할 수 있는 가장 원초적이고 깨끗한 방법입니다.
			

	5. 이러한 매크로 함수들을 시기적절하게 호출하고
	   기록해 둔 object 포인터들을 통해 각 object의 상태를 조절하면서
	   적절히 OLED_INVALIDATE()를 호출해 주면
	   여러분의 텀 프로젝트에서 맞닥뜨릴 대부분의 상황에서
	   그럭저럭 괜찮은 그리기 성능을 보여줄 수 있을 것입니다.

	6. 그럼에도 불구하고 몇몇 팀들은 추가적인 튜닝 작업이 필요할 수 있으니
	   라이브러리 쓰다가 잘 안 되는 부분이 생기면
	   지체하지 말고 조교에게 도움을 요청하세요!

#endif
