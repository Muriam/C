#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mt.h"
#include "bigchar.h"
#define P 0 // флаги
#define O 1
#define M 2
#define T 3
#define E 4

int main(){ 
	// адрес (он же instuctionCounter)
	int iC = 23;
	// инициализируем флаги нулями
	sc_regInit();
	// очищаем экран
	mt_clrscr();
	//mt_setbgcolor(BLACK);
	mt_setfgcolor(WHITE);
	// получим размеры экрана
	int r, c;
	mt_getscreensize(&r,&c);
	sc_memoryInit();
	sc_memorySet(23,0x3c4); // устанавливаем значение в ячейку (для примера)
	// Рисуем рамки
	bc_box(0,0,13,72); // для памяти
	bc_box(0,73,4,75); // для accumulator
	bc_box(4,73,3,75); // для instruction
	bc_box(7,73,3,75); // для operation
	bc_box(10,73,3,75); // для flags
	bc_box(13,52,10,75); // для keys
	bc_box(13,0,10,51); // для Больших символов
	// Заголовок для вывода памяти
	mt_gotoXY(1,4*7+5);
	write(1,"Memory",6);
	int i,j = 0,value,k=2;
	// Выводим все ячейки памяти с 1 до 100
	for(i = 1; i <= 100; i++,j++){
		sc_memoryGet(i,&value); // получаем значение в ячейке
	    	mt_gotoXY(k,j*7+2); // переходим в нужное для вывода мето
		if(i == iC){ // если выводится выделенная ячейка, то меняем ей фоновый цвет
			mt_setbgcolor(GREEN); 
		}
		char buf1[8]; // временная переменная для хранения выводимого значения
		int l1 = sprintf(buf1,"+%.4x",value); // пишем во вр.переменную наше число в 16ом виде в 4 знака
		write(1,buf1,5);
		if(i%10==0){ // если позиция кратна 10, то переносим на следующую строку
			k++;
			j = -1;
		}
		if(i == iC){ // если мы меняли фон для вывода выделенной ячейки, то возвращаем цвет обратно
			mt_setbgcolor(BLACK);
		}
	}
	// Далее вывод заголовка для блока и вывод текста
	// accumulator 
	mt_gotoXY(1,11*7-3); 
	write(1,"accumulator",11);
	mt_gotoXY(2,11*7);
	write(1,"+0000",5);
	// instuctionCounter
	mt_gotoXY(4,11*7-3);
	write(1,"instuctionCounter",17);
	mt_gotoXY(5,11*7);
	sc_memoryGet(iC,&value); // получем значение ячейки по позиции
	char buf2[8];
	int l2 = sprintf(buf2,"+%.4x",iC); // записываем значение в строку
	write(1,buf2,l2); // выводим строку
	// Operation
	mt_gotoXY(7,11*7-1);
	write(1,"Operation",9);
	mt_gotoXY(8,11*7);
	write(1,"+00:00",6);
	// Flags. Проверяем каждый флаг и если один из них 1, то выводим его, иначе не выводим
	mt_gotoXY(10,11*7);
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
	// Блок Keys
	mt_gotoXY(13,8*7);
	write(1,"Keys",4);
	mt_gotoXY(14,8*7-2);
	write(1,"l - load",8);
	mt_gotoXY(15,8*7-2);
	write(1,"s - save",8);
	mt_gotoXY(16,8*7-2);
	write(1,"r - run",7);
	mt_gotoXY(17,8*7-2);
	write(1,"t - step",8);
	mt_gotoXY(18,8*7-2);
	write(1,"i - reset",9);
	mt_gotoXY(19,8*7-2);
	write(1,"F5 - accumulator",17);
	mt_gotoXY(20,8*7-2);
	write(1,"F6 - instructionCounter",23);
	// BigChar
	sc_memoryGet(iC,&value); // получаем значение из ячейки
	char buf1[8];
	int l1 = sprintf(buf1,"+%.4x",value); // записываем это значение в строку
	int mass[8];
	for(i = 0; i < 5; i++){ // проходимся по всем символам строки
		switch(buf1[i]){ // создаем массив с индексами символов, которые будем выводить в большом размере
			case 'a': mass[i] = 10; break;
			case 'b': mass[i] = 11; break;
			case 'c': mass[i] = 12; break;
			case 'd': mass[i] = 13; break;
			case 'e': mass[i] = 14; break;
			case 'f': mass[i] = 15; break;
			case '+': mass[i] = 16; break;
			default: mass[i] = buf1[i] - '0'; break;
		}
	}
	bc_printbigchar(big[mass[0]],14,2,BLACK,WHITE); // выводим большие символы
	bc_printbigchar(big[mass[1]],14,11,BLACK,WHITE);
	bc_printbigchar(big[mass[2]],14,20,BLACK,WHITE);
	bc_printbigchar(big[mass[3]],14,29,BLACK,WHITE);
	bc_printbigchar(big[mass[4]],14,38,BLACK,WHITE);
	// возвращаем в начало
   	mt_gotoXY(24,1);
   	return 0;
}
