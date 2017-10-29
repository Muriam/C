#include"disk.h"
struct partition_table {
	tPartition table[4];
	struct partition_table *next;
} *first,*temp,*last; // таблица будет представлять из себя список

	tPartition tm;
	tIDECHS geomet;
	tLARGE geom,adr;
	tLBA disk,adres=1;

int main(){
	int t,k=0,b=1,free_size,type_oc,bool_oc;
	char c;
	geom.C=1023; // максимальные значения С, H, S
	geom.H=255;
	geom.S=63;
	first=malloc(sizeof(struct partition_table)); // выделяем память под первый элемент
 
	last=first;
 
	printf("Введите IDECHS геометрию диска\n");
	metka: printf("C:"); 
	scanf("%d",&t); // считываем значение C
	if(t>geom.C){ printf("Error\n"); goto metka; }
	geomet.C=t;
	metka1: printf("H:");
	scanf("%d",&t); // считываем значение H
	if(t>geom.H){ printf("Error\n"); goto metka1; }
	geomet.H=t;
	metka2: printf("S:");
	scanf("%d",&t); // считываем значение S
	if(t>geom.S){ printf("Error\n"); goto metka1; }
	geomet.S=t;

	g_idechs2lba(geomet,&disk); // расчитываем размер чиска по геометрии
	printf("Размер диска %.2f Gb\n",(float) disk/(1024*2048)); // выводим размер диска
	free_size=disk/2; 
	do{
  		do{
		   printf("Свободного места: %d Кб\n",free_size); // выводим оставшееся место
		   printf("Размер раздела (Кб):"); 
		   scanf("%d",&t); // считываем размер раздела
		} while (t>free_size); // пока если свободное место
		if(t==0) break;
		free_size-=t; // вычитаем из свободного места размер раздела
		tm.startLBA=adres; // запоминаем начало LBA адреса
		tm.size=t; // запоминаем размер раздела
		adres+=tm.size; // запоминаем конечный адрес
		if(a_lba2large(geom,tm.startLBA,&adr)) // переводим из LBA в CHS
		   tm.startCHS=adr; // запоминаем CHS адрес
		else
		   tm.startCHS=geom; 
		if (a_lba2large(geom,adres,&adr)) // переводим конец LBA в CHS
		   tm.endCHS=adr; // запоминаем конечный CHS адрес
		else
		   tm.endCHS=geom;
		bool_oc=1;
		while (bool_oc){
		   bool_oc=0;
		   printf("Тип ОС:\n"); // выводим архитектуры ОС
		   printf("1 - FAT16\n");
		   printf("2 - FAT32\n");
		   printf("3 - Linux swap\n");
		   printf("4 - Linux\n");
		   printf("5 - HPFS/NTFS\n");
		   scanf("%d",&type_oc);
		   switch (type_oc){ // в зависимости от выбора сохраняем флаги ОС
			case 1:
			     tm.type=0x04;
			break;
			case 2:
			     tm.type=0x0c;
			break;
			case 3:
			     tm.type=0x82;
			break;
			case 4:
			     tm.type=0x83;
			break;
			case 5:
			     tm.type=0x07;
			break;
			default:
			     bool_oc=1;
   		   }
	  	}
		tm.active=0;
		if(b){
		   printf("Установить раздел активным (y/n)\n"); 
		   do{
		    scanf("%c",&c); // считываем выбор 
		   } while((c!='n')&&(c!='y'));
		   if ((c=='y')){
		    tm.active=0x80; // если выбор y, то помечаем раздел флагом
		    b=0;
		   }
		}
		if (((tm.startCHS.C==geom.C)&&(tm.startCHS.H==geom.H)&&(tm.startCHS.S==geom.S))||(k==3)){
		   last->table[k]=tm;
		   last->table[k].type=0x05;
		   if (k!=3)
		    last->table[k+1].startLBA=0;
		   temp=malloc(sizeof(struct partition_table));
		   last->next=temp;
		   last=temp;
		   last->table[0]=tm;
		   last->table[1].startLBA=0;
		   k=1;
		} else {
		   last->table[k]=tm;
		   last->table[++k].startLBA=0;
		}
	 } while (free_size!=0);
	 printf("Актв # CHS нач # ОС # CHS кон     # LBA нач   #  Размер\n");
	 temp=first;
 	while (temp!=NULL){ // пока не дошли до конца списка
		  int i;
		  //printf("Адрес сектора где расположена таблица %d\n",temp->table[0].startLBA);
		  for (i=0;i<4;i++){ 
		 	 if (temp->table[i].startLBA==0) break;
			 printf("%2x%5d%4d%3d%4x%5d%4d%3d%13ld%13d\n",temp->table[i].active,temp->table[i].startCHS.C,temp->table[i].startCHS.H,temp->table[i].startCHS.S,temp->table[i].type,temp->table[i].endCHS.C,temp->table[i].endCHS.H,temp->table[i].endCHS.S,temp->table[i].startLBA,temp->table[i].size); // выводим все данные о разделе
		  }
  		  temp=temp->next; // переходим к следующему разделу
	}
	return 0;
}
