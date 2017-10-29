#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "mt.h"
#include "bigchar.h"
#include "memorylib.h"
#include "lab5.h"
#define P 0 // флаги
#define O 1
#define M 2
#define T 3
#define E 4

int verifMemory(int t){
	int op, com;
	sc_commandDecode(t,&com,&op);
	int mass[40] = {0x10,0x11,0x20,0x21,0x30,0x31,0x32,0x33,0x40,0x41,0x42,0x43,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x60,0x61,0x62, 0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x70,0x71,0x72,0x73,0x74,0x75,0x76};
	int status = -1;
	int i;
	for(i = 0; i < 40; i++){
		if(2*mass[i] == com){
			status = 0;
			break;
		}
	}
	return status;
}

int main(){ 
	int iC = 1;
	int status = 1,t; // для считывания
	int statusAc = 1, t1; // статус фиксации аккумулятора, врем.хранение
	int statusIc = 1; // статус фиксации аккумулятора, врем.хранение
	char temp[4], temp1[4]; // для считывания значения
	// инициализируем флагиx
	sc_regInit();
	mt_setfgcolor(WHITE);
	// получим размеры экрана
	int r, c;
	mt_getscreensize(&r,&c);
	sc_memoryInit();
	// метка для возврата к нем по надобности перерисовки
	metka:
	// очищаем экран
	mt_clrscr();
	// Рамки
	bc_box(0,0,13,72); // для памяти
	bc_box(0,73,4,75); // для accumulator
	bc_box(4,73,3,75); // для instruction
	bc_box(7,73,3,75); // для operation
	bc_box(10,73,3,75); // для flags
	bc_box(13,52,10,75); // для keys
	bc_box(13,0,10,51); // для BigChar
	mt_gotoXY(1,4*7+5);
	write(1,"Memory",6);
	int i,j = 0,value,k=2;
	// memory
	for(i = 1; i <= 100; i++,j++){
		sc_memoryGet(i,&value);
		if(i == iC && statusIc == 1){
			mt_setbgcolor(RED);
		}
	    	mt_gotoXY(k,j*7+2);
		char buf1[8];
		int l1 = sprintf(buf1,"+%.4x",value);
		write(1,buf1,5);
		if(i%10==0){
			k++;
			j = -1;
		}
		if(i == iC && statusIc == 1){
			mt_setbgcolor(BLACK);
		}
	}
	// accumulator
	mt_gotoXY(1,11*7-3);
	write(1,"accumulator",11);
	mt_gotoXY(2,11*7);
	if(statusAc == 1){
		sc_memoryGet(iC,&value);
		char buf3[8];
		int l3 = sprintf(buf3,"+%.4x",value);
		write(1,buf3,l3);
	} else if(statusAc == 0){
		char buf3[8];
		int l3 = sprintf(buf3,"+%.4x",t1);
		write(1,buf3,l3);
	}
	// instuctionCounter
	mt_gotoXY(4,11*7-3);
	write(1,"instuctionCounter",17);
	mt_gotoXY(5,11*7);
	sc_memoryGet(iC,&value);
	char buf2[8];
	int l2 = sprintf(buf2,"+%.4x",iC);
	write(1,buf2,l2);
	// Operation
	mt_gotoXY(7,11*7-1);
	write(1,"Operation",9);
	mt_gotoXY(8,11*7);
	write(1,"+00:00",6);
	// Flags
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
	// Keys
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
	// Вывод BigChar
	sc_memoryGet(iC,&value);
	char buf1[8];
	int l1 = sprintf(buf1,"+%.4x",value);
	int mass[8];
	for(i = 0; i < 5; i++){
		switch(buf1[i]){
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
	bc_printbigchar(big[mass[0]],14,2,BLACK,WHITE);
	bc_printbigchar(big[mass[1]],14,11,BLACK,WHITE);
	bc_printbigchar(big[mass[2]],14,20,BLACK,WHITE);
	bc_printbigchar(big[mass[3]],14,29,BLACK,WHITE);
	bc_printbigchar(big[mass[4]],14,38,BLACK,WHITE);
	// обработка клавиш	
	// возвращаем в начало
   	mt_gotoXY(24,1);
	rk_mytermregime(0,50,0,0,1); // переводим терминал в режим, когда выводятся аналоги букв из перечисления
	enum keys key;
	while(1) {
	    rk_readkey(&key); // считываем клавишу
	    switch(key){
		    case 2: sc_memorySave("lab5.memory"); break; // если кнопка s, то сохраняем оперативную память в файл
		    case 1: sc_memoryLoad("lab5.memory"); goto metka; break; // если кнопка l, то загружаем оперативную память из файла
		    case 9: if(iC > 10) iC -= 10; goto metka; break; // если кнопка вверх, то перемещаем позицию на 10 ячеек назад
		    case 8: if(iC <= 90) iC += 10; goto metka; break; // если кнопка вниз, то перемещаем позицию на 10 ячеек вперед
		    case 10: if(iC > 1) iC--; goto metka; break; // если кнопка назад, то перемещаем на одну позицию назад
		    case 11: if(iC < 100) iC++; goto metka; break; // если кнопка вперед, то перемещаем на одну позицию вперед
		    case 12: { // если кнопка Enter
			if(status == 1){ // если статус считывания равен 1
				write(1,"Input: ",7);
				rk_mytermregime(1,0,50,1,1); // переводим терминал в режим обычного считывания
				read(1,&temp,4); // считываем 4 символа
				sscanf(temp,"%x",&t); // считываем в переменную типа int
				status = 0;
				mt_clrscr();
				goto metka;
			} else if(status == 0){
				if(verifMemory(t) == 0)
   					sc_memorySet(iC,t); // записываем считанное значение в память по выбранному адресу
				rk_mytermregime(0,50,0,0,1);
				status = 1;
				mt_clrscr();
				goto metka;
			}
		    } break;
		    case 6: { // если нажата F5
			if(statusAc == 1){
				sc_memoryGet(iC,&t1); // получаем значение из выделенной ячейки
				statusAc = 0;
			} else if(statusAc == 0){
				sc_memorySet(iC,t1); // заносим значение из Аккумулятора в выделенную ячейку памяти
				statusAc = 1;
				goto metka;
			}
	  	    } break;
		    case 7: { // если начата F6
			if(statusIc == 1){
				write(1,"Input: ",7);
				rk_mytermregime(1,0,50,1,1); 
				read(1,&temp1,4); // считываем значение для instructionCounter
				sscanf(temp1,"%x",&t);
				iC = t; // переход по введенной позиции
				mt_clrscr();
				goto metka;
			}
			
		    } break;
	    }
	}
	rk_mytermregime(1,0,50,1,1);
   	return 0;
}
