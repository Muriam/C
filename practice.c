/* программа реализует сложение и вычитание в hex, а также перевод из hex в dec*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <math.h>
#include <string.h>


int N = 10; //максимальное кол-во разрядов в числе

/* перевод 16-ичной цифры(разряда) в десятичное число */
int hex_to_dec(char hex_digit)
{
    switch(hex_digit)
	{
    case '0' :
        return 0;
        break;
    case '1' :
        return 1;
        break;
    case '2' :
        return 2;
        break;
    case '3' :
        return 3;
        break;
    case '4' :
        return 4;
        break;
    case '5' :
        return 5;
        break;
    case '6' :
        return 6;
        break;
    case '7' :
        return 7;
        break;
    case '8' :
        return 8;
        break;
    case '9' :
        return 9;
        break;
    case 'a' :
    case 'A' :
        return 10;
        break;
    case 'b' :
    case 'B' :
        return 11;
        break;
    case 'c' :
    case 'C' :
        return 12;
        break;
    case 'd' :
    case 'D' :
        return 13;
        break;
    case 'e' :
    case 'E' :
        return 14;
        break;
    case 'f' :
    case 'F' :
        return 15;
        break;
    default :
        return 0;
    }
}

/* десятичное число в шестнадцатиричную цифру */
char dec_to_hex(int dec_number)
{
    switch(dec_number)
	{
    case 0 :
        return '0';
        break;
    case 1 :
        return '1';
        break;
    case 2 :
        return '2';
        break;
    case 3 :
        return '3';
        break;
    case 4 :
        return '4';
        break;
    case 5 :
        return '5';
        break;
    case 6 :
        return '6';
        break;
    case 7 :
        return '7';
        break;
    case 8 :
        return '8';
        break;
    case 9 :
        return '9';
        break;
    case 10 :
        return 'a';
        break;
    case 11 :
        return 'b';
        break;
    case 12 :
        return 'c';
        break;
    case 13 :
        return 'd';
        break;
    case 14 :
        return 'e';
        break;
    case 15 :
        return 'f';
        break;
    default :
        return '0';
    }
}

/* поразрядное сложение */
int hex_slozhenie(char hex_digit1, char hex_digit2)
{
    int num1 = hex_to_dec(hex_digit1);
    int num2 = hex_to_dec(hex_digit2);
    return num1 + num2;
}

/* поразрядное вычитание */
int hex_substitute(char hex_digit1, char hex_digit2)
{
    int num1 = hex_to_dec(hex_digit1);
    int num2 = hex_to_dec(hex_digit2);
    return num1 - num2;
}


/* инициализация числа */
void initialize_number(char* hex_number)
{
    int i;
    for (i = 0; i < N; i++)
        hex_number[i]='0';
}

/* сдвиг разрядов */
void sdvig(char *hex_number)
{
    int pos, i;
    pos = N - 1;

    while (hex_number[pos]== '0')
        pos--;
    i = 0;
    
    while (i < N - pos)
	{
        hex_number[N - 1 - i] = hex_number[pos - i - 1];
        i++;
    }
    
    for (i = 0; i < N - pos; i++)
	{
        hex_number[i] = '0';
    }
}

//////////////////////////////////////////////////////////////////

/* функция перевода из 16-ричной в 10-ную систему счисления */
int HEX_TO_DEC(char st[10])
{
    int i, s, k, p;
    s = 0;
    p = strlen(st) - 1;
    for (i = 0; st[i] != '\0'; i++)
    {
        switch (toupper(st[i]))
        {
            case 'A':
                k = 10;
                break;
            case 'B':
                k = 11;
                break;
            case 'C':
                k = 12;
                break;
            case 'D':
                k = 13;
                break;
            case 'E':
                k = 14;
                break;
            case 'F':
                k = 15;
                break;
            case '1':
                k = 1;
                break;
            case '2':
                k = 2;
                break;
            case '3':
                k = 3;
                break;
            case '4':
                k = 4;
                break;
            case '5':
                k = 5;
                break;
            case '6':
                k = 6;
                break;
            case '7':
                k = 7;
                break;
            case '8':
                k = 8;
                break;
            case '9':
                k = 9;
                break;
            case '0':
                k = 0;
                break;
        }
        s = s + k * pow(16, p);
        p--;
    }
    printf("%d", s);
    return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	
	
    char hex_chislo1[N];
    char hex_chislo2[N];
    char result_hexnumber[N];
    int sum, add, i, min, dif;
    int n = 1;
    char c;

   do{
    initialize_number(hex_chislo1);
    initialize_number(hex_chislo2);
    
    		
    printf("введите число 1 (в hex, макс. 10 цифр) ", N);
    scanf("%s", hex_chislo1);
    sdvig(hex_chislo1);

    printf("введите число 2 (в hex, макс. 10 цифр) ", N);
    scanf("%s", hex_chislo2);
    sdvig(hex_chislo2);

    printf("\n%s \n\n", hex_chislo1);
    printf("%s \n\nПодсчитать...\n\n", hex_chislo2);


	  printf("\n\n\nСУММА\n");
    add = 0; //переменная для хранения единицы в старший разряд
    for (i = N - 1; i >= 0; i--)
	 {
        sum = hex_slozhenie(hex_chislo1[i], hex_chislo2[i]) + add;
        add = 0;
        if (sum >= 16)
		{
            sum -= 16;
            add++;
        }
        else
            add = 0;
        result_hexnumber[i] = dec_to_hex(sum);
        printf("%c + %c :    ", hex_chislo1[i], hex_chislo2[i]);
        printf("сумма =   %d - %d ", sum, add);
        printf("= %c\n", result_hexnumber[i]);

    }
    printf("\nрезультат = ");
    for (i = 0; i < N; i++)
        printf("%c", result_hexnumber[i]);
        
///////////////////////////////////////////////////////////////////
 			
 	printf ("\n\n\nРАЗНОСТЬ\n");
    min = 0; //переменная для хранения единицы в старший разряд
    for (i = N - 1; i >= 0; i--)
	{
        dif = hex_substitute(hex_chislo1[i], hex_chislo2[i]) - min;
        min = 0;
        if (dif < 0)
		    {
            dif += 16;
            min++;
        }
        else
            min = 0;
        result_hexnumber[i] = dec_to_hex(dif);
        printf("%c - %c :    ", hex_chislo1[i], hex_chislo2[i]);
        printf("разность =   %d - %d ", dif, min);
        printf("= %c\n", result_hexnumber[i]);

    }
    printf("\nрезультат = ");
    for (i = 0; i < N; i++)
        printf("%c", result_hexnumber[i]);   
        
//////////////////////////////////////////////////////////////////
	
	printf("\n\n\n******************************************************\n");
	printf("\nперевод числа из 16-ричной в 10-ную систему счисления\n");
	char s[10];
  char ch;
  printf("\nвведите hex число ");
  scanf("%s", s);
  printf("\nрезультат перевода в dec ");
  HEX_TO_DEC(s);
  scanf(s);   
	printf("\n\n");
	
	printf("\nПродолжить?<y><n>\n");
  c = getch();
  } while(c!='n');
	
    return 0;
}
