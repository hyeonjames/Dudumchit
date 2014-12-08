

박자를 바꾸려면 TermProject.c 파일에 game_start() 에서 makeComptuerDances(8) << 여기서 8부분을 고치고
똑같이 game_dance()에서 makeComputerDances(8) 이부분 똑같이 고쳐주셈

만약에 빌드 에러가 나면 Build-ReBuild All을 해봐

TermProject.h 에 #define GAME_SPEED SECOND(4) 라고 되있는데 만약 makeComputerDances(8) 로 하면 4초동안 8번 춤을 춘다는 뜻임



