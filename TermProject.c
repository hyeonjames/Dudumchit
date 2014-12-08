#include "TermProject.h"
#include<math.h>
#include<stdlib.h>
#include "OLED.h"
#include"imageData.h"
#include "TIMER3.h"
#include <avr/pgmspace.h>
unsigned char nstate2 = 0; // 보조 상태
unsigned char btn_input = 0, before_btn_input = 0;
float dance_ratio=1;
unsigned char ready_timer = 0;
unsigned char tick=0;
unsigned long score=0;
unsigned int combo = 0;
unsigned int next_computer_dance_frame = 0;
unsigned char dance_frame_tick=0,n_comframe=0;
unsigned char dances[9]={0};
const unsigned char def_scores[] = {
	100,75,50,25,0 // Perfect,Great,Good,Bad,Miss의 기본 점수. 여기에 (combo/5)+1이 곱해지면서 점수가 들어감
};
struct OLED_Object* me;
struct OLED_Object* com;
struct OLED_Object* score_num[5];
struct OLED_Object*	obj_score;
struct OLED_Object* effect;
struct OLED_Object*	obj_hearts[MAX_HEART];
unsigned char me_dance_num=0,com_dance_num = 0;
unsigned int effect_timer = 0;

#define HEART_BROKEN_INDEX	0


#define SCORE_REFRESH()			(		\
		score_num[0]->idx_bitmap = NUMBERS_INDEX + score/10000,			\
		score_num[1]->idx_bitmap = NUMBERS_INDEX + (score/1000)%10,		\
		score_num[2]->idx_bitmap = NUMBERS_INDEX + (score/100)%10,		\
		score_num[3]->idx_bitmap = NUMBERS_INDEX + (score/10)%10,		\
		score_num[4]->idx_bitmap = NUMBERS_INDEX + (score)%10,			\
		OLED_INVALIDATE_OBJECT_SIMPLE(score_num[0]),					\
		OLED_INVALIDATE_OBJECT_SIMPLE(score_num[1]),					\
		OLED_INVALIDATE_OBJECT_SIMPLE(score_num[2]),					\
		OLED_INVALIDATE_OBJECT_SIMPLE(score_num[3]),					\
		OLED_INVALIDATE_OBJECT_SIMPLE(score_num[4]),					\
		OLED_INVALIDATE()												\
		)
unsigned int next_judge_end_frame;
unsigned char me_danced; // 내가 춤을 췄나?
unsigned char judged,judge_comframe;
void doeffect(unsigned char);
#define COMBO_REFRESH()	(\
		buffer_LCD[29] = (combo/5+1)/10 + '0',	\
		buffer_LCD[30] = (combo/5+1)%10 + '0',	\
		buffer_LCD[0] = (combo/10000) + '0',	\
		buffer_LCD[1] = (combo/1000)%10 + '0',	\
		buffer_LCD[2] = (combo/100)%10 + '0',	\
		buffer_LCD[3] = (combo/10)%10 + '0',	\	
		buffer_LCD[4] = combo%10 + '0'			\
		)
void btn_pressed(unsigned btn_input){

	if(PUSHED && nstate != GAME_SCORE_ANIMATION && nstate != GAME_OVER){
		if(btn_input == 7){
			nstate = GAME_START;
			TOUR_STOP();
			nstate2 = 0;
			SCORE_REFRESH();
			clearLCD(0,0,16);
			clearLCD(1,0,16);
			PRINT(0,0,"00000     COMBO");
			PRINT(1,0,"SCORE RATE [x01]");
		} else {
			if(btn_input == 8) btn_input = dances[judge_comframe]%7;
			DANCE(btn_input);
			if(nstate == GAME_DANCE && nstate2 == 1){
				//내가 추는 차례!
				TOUR_PLAY(effect_sounds[btn_input-1]);

				if(!judged){
					if((btn_input!=0 && (me_danced || (btn_input != dances[judge_comframe])))){
						doeffect(4); // bad!
						me_danced = 1;
					} else if(!(!me_danced && btn_input==0 && dances[judge_comframe])) {
						unsigned int frame = (next_judge_end_frame-TIMER3_current_frame)/2;
						if(frame >= dance_frame_tick*4/5){
							doeffect(5);
						} else if(frame >= dance_frame_tick*3/5){
							doeffect(4);
						} else if(frame>= dance_frame_tick*2/5){
							doeffect(3);
						} else if(frame >= dance_frame_tick/5){
							doeffect(2);
						} else {
							doeffect(1);
						}
						if(btn_input) me_danced = 1;
					}
				}

			}
		}
	}
}

int main(void){
	DDRB = 0xFF;
	TOUR_INITIALIZE();
	TIMER3_INITIALIZE();
	DDR_PUSH_BUTTON	=	0x00;
	OLED_INITIALIZE();

	//Bitmap Initialize
	BITMAP_INIT(NUMBERS_INDEX+1,ONE,0);
	BITMAP_INIT(NUMBERS_INDEX,ZERO,0);
	BITMAP_INIT(NUMBERS_INDEX+2,TWO,0);
	BITMAP_INIT(NUMBERS_INDEX+3,THREE,0);
	BITMAP_INIT(NUMBERS_INDEX+4,FOUR,0);
	BITMAP_INIT(NUMBERS_INDEX+5,FIVE,0);
	BITMAP_INIT(NUMBERS_INDEX+6,SIX,0);
	BITMAP_INIT(NUMBERS_INDEX+7,SEVEN,0);
	BITMAP_INIT(NUMBERS_INDEX+8,EIGHT,0);
	BITMAP_INIT(NUMBERS_INDEX+9,NINE,0);
	BITMAP_INIT(EFFECT_INDEX+1,perfect,0xf81f);
	BITMAP_INIT(EFFECT_INDEX+2,GREAT,0x7E0);
	BITMAP_INIT(EFFECT_INDEX+3,GOOD,0b1111100000);
	BITMAP_INIT(EFFECT_INDEX+4,BAD,31);
	BITMAP_INIT(EFFECT_INDEX+5,MISS,0xf800);
	BITMAP_INIT(DANCE_INDEX,basic1,0x0);
	BITMAP_INIT(DANCE_INDEX+1,beside,0);
	BITMAP_INIT(DANCE_INDEX+2,dudumchit,0);
	BITMAP_INIT(DANCE_INDEX+3,heart3,0);
	BITMAP_INIT(DANCE_INDEX+4,jackson,0);
	BITMAP_INIT(DANCE_INDEX+5,superman,0);
	BITMAP_INIT(DANCE_INDEX+6,arm,0);

	BITMAP_INIT(HEART_INDEX,life,0xf800);
	//BITMAP_INIT(DANCE_INDEX+7,die,0);
	BITMAP_INIT(MNOTE_INDEX,musicnote,0);
	BITMAP_INIT(MNOTE_CHECKED_INDEX,musicnote,0x7E0);
	BITMAP_INIT(MNOTE_NONE_INDEX,nonote,0);
	BITMAP_INIT(MNOTE_NONE_CHECKED_INDEX,nonote,0x7E0);
	BITMAP_INIT(SCORE_INDEX,img_score,0);
	BITMAP_INIT(OVER_INDEX,img_over,0);
	BITMAP_INIT(OVER_INDEX+1,img_over2,0);
	TIMER3_START();
	sei();


	while(1) {
	//	cli();
		LCD_UPDATE();
		OLED_UPDATE();
		TOUR_UPDATE();
		btn_input = INPUT_PUSH_BUTTON;
		if(PUSHED){
			if(btn_input & 0x01) btn_pressed (1);
			else if(btn_input & 0x02) btn_pressed(2);
			else if(btn_input & 0x04) btn_pressed(3);
			else if(btn_input & 0x10) btn_pressed(4);
			else if(btn_input & 0x20) btn_pressed(5);
			else if(btn_input & 0x40) btn_pressed(6);
			else if(nstate == GAME_STOPPED) btn_pressed((btn_input & 0x08) ? 7 : 0);
			else if(btn_input & 0x80) btn_pressed(8);
			else btn_pressed(0);
		}
		before_btn_input = btn_input;

		if ( TIMER3_CHECK() )
		{

			if(TIMER3_current_frame >= effect_timer){
				//OLED_HIDE_OBJECT(effect);
				effect->idx_bitmap = 0;
				OLED_INVALIDATE_OBJECT_SIMPLE(effect);
				OLED_INVALIDATE();
			}
			switch(nstate){
			case GAME_STOPPED:
				game_stopped();
				break;
			case GAME_START:
				game_start();
				break;
			case GAME_DANCE:
				game_dance();
				break;
			case GAME_SCORE_ANIMATION:
				game_animation();
			case GAME_OVER:
				game_over();
				break;
			}
	//	sei();
		}
	}
}
void createHearts(){
	int i;
	for(i=0;i<MAX_HEART;i++){
		obj_hearts[i] = OLED_CREATE_OBJECT(0,0);
		obj_hearts[i]->idx_bitmap = HEART_INDEX;
		obj_hearts[i]->left = i * WIDTH_life;
		obj_hearts[i]->right = i * WIDTH_life+ 15;
		obj_hearts[i]->top = 0; obj_hearts[i]->bottom = HEIGHT_life-1;
		OLED_INVALIDATE_OBJECT_SIMPLE(obj_hearts[i]);
	}
	OLED_INVALIDATE();
}
unsigned char hearts_count = 8;
void refreshHearts(){
	register int i;
	register struct OLED_Object* obj;
	for(i=0;i<hearts_count;i++){
		obj = obj_hearts[i];
		obj->idx_bitmap = HEART_INDEX;
		OLED_INVALIDATE_OBJECT_SIMPLE(obj);
	}
	for(;i<MAX_HEART;i++)
	{
		obj = obj_hearts[i];
		obj->idx_bitmap = HEART_BROKEN_INDEX;
		OLED_INVALIDATE_OBJECT_SIMPLE(obj);
	}
	OLED_INVALIDATE();
}
struct OLED_Object* obj_me_musicnotes[8],*obj_com_musicnotes[8];

void CreateObjectsMain(){
	int i;


	me = OLED_CREATE_OBJECT(0,0);
	me->idx_bitmap = DANCE_INDEX;
	me->left = 16;
	me->right = 47;
	me->top = 32;
	me->bottom = 95;
	OLED_INVALIDATE_OBJECT_SIMPLE(me);
	
	com = OLED_CREATE_OBJECT(0,0);
	com->left = 80;
	com->idx_bitmap = DANCE_INDEX;
	com->right = 111;
	com->top = 32;
	com->bottom = 95;
	OLED_INVALIDATE_OBJECT_SIMPLE(com);


	obj_score = OLED_CREATE_OBJECT(0,0);
	obj_score->left = 20;
	obj_score->right = 67;
	obj_score->top = 16;
	obj_score->bottom = 31;
	obj_score->idx_bitmap = SCORE_INDEX;
	OLED_INVALIDATE_OBJECT_SIMPLE(obj_score);
	for(i=0;i<5;i++){
		struct OLED_Object* obj=score_num[i] = OLED_CREATE_OBJECT(0,0);
		obj->left = i*8 + 68;
		obj->right = obj->left + 7;
		obj->top = 16;
		obj->bottom = 31;
		obj->idx_bitmap = NUMBERS_INDEX;
		OLED_INVALIDATE_OBJECT_SIMPLE(obj);
	}
	for(i=0;i<8;i++){
		struct OLED_Object* obj = obj_me_musicnotes[i] = OLED_CREATE_OBJECT(0,0);
		obj->left = (i/4)*48;
		obj->right = obj->left + 15;
		obj->top = (i%4)*16 + 32;
		obj->bottom = obj->top + 15;
		obj->idx_bitmap = 0;
		OLED_INVALIDATE_OBJECT_SIMPLE(obj);
	}
	for(i=0;i<8;i++){
		struct OLED_Object* obj = obj_com_musicnotes[i] = OLED_CREATE_OBJECT(0,0);
		obj->left = (i/4)*48 + 64;
		obj->right = obj->left + 15;
		obj->top = (i%4)*16 + 32;
		obj->bottom = obj->top + 15;
		obj->idx_bitmap = 0;
		OLED_INVALIDATE_OBJECT_SIMPLE(obj);
	}
	effect = OLED_CREATE_OBJECT(0,0);
	effect->idx_bitmap = 0;
	effect->left = 32;
	effect->right = 95;
	effect->top = 96;
	effect->bottom = 127;
	OLED_INVALIDATE_OBJECT_SIMPLE(effect);
	createHearts();

	OLED_INVALIDATE();
}
void game_stopped(){
	if(nstate2==0){
		PRINT(0,0,"Press 4 btn");
		nstate2 = 1;
		CreateObjectsMain();
	}
	if(!TOUR_enabled){
		TOUR_PLAY(stopped_bgsound);
	}
	if(CHECK_TIME(next_computer_dance_frame)){
		unsigned char rnd = rand()%7;
		COMDANCE(rnd);
		next_computer_dance_frame = AFTER(30);
	}
}
unsigned char dance_count;

void makeComputerDances(unsigned char count){
	int i;
	n_comframe = 0;
	dance_count = count;
	for(i=0;i<count;i++){
		dances[i] = rand()%7;
	}
	dances[count] = 7;
	dance_frame_tick = (GAME_SPEED/count); // 여기가 게임 속도조절. GAME_SPEED 는 TermProject.h에 있음.
											// 
	MNOTE_CLEAR(obj_me_musicnotes);
	//PRINT(1,0,"Computer Dance!");
	next_computer_dance_frame = AFTER(dance_frame_tick);
}
unsigned int next_dance_frame;
void game_start(){
	//setting
	srand(TIMER3_current_frame*TIMER3_FRAMES_PER_SECOND*TIMER3_TICKS_PER_FRAME+ TIMER3_tick);
	TIMER_RESET;
	makeComputerDances(8); // game_dance 부분에 makeComputerDances 바꾸고 여기도 수정해줘야됨

	nstate = GAME_DANCE;
	nstate2 = 0;

	next_computer_dance_frame = AFTER(SECOND(1));
}
void doeffect(unsigned char idx){
	effect->idx_bitmap = EFFECT_INDEX + idx;
	OLED_INVALIDATE_OBJECT_SIMPLE(effect);
	OLED_INVALIDATE();
	effect_timer = AFTER(SECOND(1));
	if(idx >= 4){
		hearts_count--;
		if(hearts_count == 0){
			nstate = GAME_SCORE_ANIMATION;
			nstate2 = 0;
			return ;
		}
		refreshHearts();
		combo = 0;
		COMBO_REFRESH();
	} else {
		if(idx == 1){
			hearts_count ++ ;
			if(hearts_count> MAX_HEART) hearts_count = MAX_HEART;
			refreshHearts();
		}
		combo++;
		COMBO_REFRESH();

	}
	score += def_scores[idx] * (combo/5 + 1);
	SCORE_REFRESH();
	judged = 1;
}

void game_dance(){
	int i;
	if(CHECK_TIME(next_computer_dance_frame)){
		if(dances[n_comframe] >= 7){
			if(nstate2 == 0){
				COMDANCE(0);
				n_comframe = 0;
				judged = 0;
				MNOTE_CLEAR(obj_com_musicnotes);
				nstate2 = 1;
				next_computer_dance_frame = AFTER(SECOND(1));
				next_judge_end_frame = next_computer_dance_frame + dance_frame_tick/2;
			} else {
				COMDANCE(0);
				makeComputerDances(8); // 여기서 8이 GAME_SPEED초 동안 춤추는 횟수, 8 이하만 됨.
				judge_comframe = 0;
				nstate2 = 0;
				next_computer_dance_frame = AFTER(SECOND(1));
				next_judge_end_frame = 0;
			}
		} else {
			COMDANCE(dances[n_comframe]);
			next_computer_dance_frame += (dance_frame_tick);
			if(nstate2==0) {
				TOUR_PLAY(effect_sounds[dances[n_comframe]-1]);
				if(n_comframe>0 )  MNOTE_UNCHECK(obj_com_musicnotes[n_comframe-1],dances[n_comframe-1]);
				MNOTE_CHECK(obj_com_musicnotes[n_comframe],dances[n_comframe]);
			}else {
				if(n_comframe>0) MNOTE_UNCHECK(obj_me_musicnotes[n_comframe-1],dances[n_comframe-1]);
				MNOTE_CHECK(obj_me_musicnotes[n_comframe],dances[n_comframe]);
			}
			n_comframe++;
		}
	}
	if(next_judge_end_frame && CHECK_TIME(next_judge_end_frame) && dances[judge_comframe] < 7){
		if(!judged){
			if(!dances[judge_comframe] && (me_dance_num > DANCE_INDEX)){
				doeffect(4); // BAD !
			} else if( dances[judge_comframe] && !me_danced ) {
				doeffect(5);
			} else if( !dances[judge_comframe] && me_dance_num == DANCE_INDEX)	{
				doeffect(1);
			}
			me_danced = 0;
			next_judge_end_frame += dance_frame_tick;
			judge_comframe++;
		}
		judged = 0;
	}
}
void clearLCD(char line,char pos,char len){
	unsigned char* buffer = buffer_LCD+(line*16+pos);
	while(len--) *(buffer++) = ' ';
}

void game_over(){

	struct OLED_Object *obj;
	if(nstate2==0){
		TOUR_PLAY(close);
					
		obj = OLED_CREATE_OBJECT(0,0);
		obj->idx_bitmap = OVER_INDEX + score/50000;
		obj->left = 0;
		obj->right = 127;
		obj->top = 32;
		obj->bottom = 95;
		OLED_INVALIDATE_OBJECT_SIMPLE(obj);
		OLED_INVALIDATE();
		nstate2 = 1;
	}
}
unsigned char animation_num,animation_idx,animation_end;
unsigned int animation_frame,animation_div=10;
void game_animation(){
	int i;
	if(nstate2==0){
		TIMER_RESET;
		OBJECT_HIDE(me);
		OBJECT_HIDE(com);
		OBJECT_HIDE(effect);
		for(i=0;i<8;i++) OBJECT_HIDE(obj_hearts[i]);
		for(i=0;i<8;i++) OBJECT_HIDE(obj_me_musicnotes[i]);
		for(i=0;i<8;i++) OBJECT_HIDE(obj_com_musicnotes[i]);
		for(i=0;i<5;i++){
			score_num[i]->idx_bitmap = NUMBERS_INDEX;
			OLED_INVALIDATE_OBJECT_SIMPLE(score_num[i]);
		}
		nstate2 = 1;
		animation_num = 0;
		animation_idx = 4;
		animation_end = score%10;
		animation_frame = AFTER(6);
	}
	else {
		if(CHECK_TIME(animation_frame)){
			animation_num++;
			if(animation_num > animation_end ){
				if(animation_idx == 0){
					nstate = GAME_OVER;
					nstate2 = 0;
					return ;
				}
				animation_idx--;
				animation_num=0;
				animation_end = (score/animation_div)%10;
				animation_div*=10;
			}
			animation_frame = AFTER(6);
		}
	}
	score_num[animation_idx]->idx_bitmap = animation_num + NUMBERS_INDEX;
	OLED_INVALIDATE_OBJECT_SIMPLE(score_num[animation_idx]);
	OLED_INVALIDATE();
}
