#include <stdio.h>
#include <unistd.h>
#include "mt.h"
#define P 0 // флаги
#define O 1
#define M 2
#define T 3
#define E 4
int main(){
	// инициализируем флагиx
	sc_regInit(P,0);
	// очищаем экран
	mt_clrscr();
	//mt_setbgcolor(BLACK);
	mt_setfgcolor(WHITE);
	// получим размеры экрана
	int r, c;
	mt_getscreensize(&r,&c);
	sc_memoryInit();
	sc_memorySet(23,0x3b0);
	mt_gotoXY(1,4*7+5);
	write(1,"Memory",6);
	int i,j = 0,value,k=2;
	// memory
	for(i = 1; i <= 100; i++,j++){
		sc_memoryGet(i,&value);
	        mt_gotoXY(k,j*7);
		char buf1[8];
		int l1 = sprintf(buf1,"+%.4x",value);
		write(1,buf1,5);
		if(i%10==0){
			k++;
			j = -1;
		}
	}
	// accumulator
	mt_gotoXY(1,11*7-3);
	write(1,"accumulator",11);
	mt_gotoXY(2,11*7);
	write(1,"+9999",5);
	// instuctionCounter
	mt_gotoXY(4,11*7-5);
	write(1,"instuctionCounter",17);
	mt_gotoXY(5,11*7);
	write(1,"+0000",5);
	// Operation
	mt_gotoXY(7,11*7-1);
	write(1,"Operation",9);
	mt_gotoXY(8,11*7);
	write(1,"+00:00",6);
	// Flags
	mt_gotoXY(9,11*7);
	write(1,"Flags",5);
	int reg;
	sc_regGet(P,&reg);
	if (reg){
		mt_gotoXY(10,11*7);
		write(1,"P",1);
	}
	sc_regGet(O,&reg);
	if (reg){
		mt_gotoXY(10,11*7-2);
		write(1,"O",1);
	}
	sc_regGet(M,&reg);
	if (reg){
		mt_gotoXY(10,11*7+2);
		write(1,"M",1);
	}
	sc_regGet(T,&reg);
	if (reg){
		mt_gotoXY(10,11*7+4);
		write(1,"T",1);
	}
	sc_regGet(E,&reg);
	if (reg){
		mt_gotoXY(10,11*7+6);
		write(1,"E",1);
	}
	// Keys
	mt_gotoXY(12,8*7);
	write(1,"Keys",4);
	
	// возвращаем в начало
	mt_gotoXY(18,1);
	return 0;
}
