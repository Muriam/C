#include <stdio.h>
#include <conio.h>
#include <locale.h> 
#include <string.h>
 
int main()
{
  setlocale(LC_ALL, "rus");
	 
    char  v;
    int a;	    
	    
    do
    {
    printf("введите число ");
    scanf("%d", &a);
    printf("%d ", a+1);
         
    printf("\nпродолжить?<y><n>\n");
    v = getch();
    } while(v!='n');
 
    getch;
    return 0;
}
