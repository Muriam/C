/* �������� ���������, ������������, ������� ��� ����������� ������ ������� � ���������� ������� */
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#define SIZE 10


int main()
{
	int array[SIZE] = {1, 5, 1, 8, 43, 5, 1, 1, 8, 8}; //����������� �������
	int pass, i, hold; //�����������: �������� ��������, �������� c��������, ��������� ������ 
	

	setlocale(LC_ALL, "Rus");  


	
/* ����� �� ����� ��������� ������� */		
	printf("�������� ������ \n");
	
	for (i = 1; i < SIZE; i++)
	printf("%d\n", array[i]);


	
/* ���������� ������� �������� � ����� �� ����� ���������������� ������� */	

    for (pass=1; pass <= SIZE; pass++) //���� ��� �������� ����� ��������
	{
		for (i=0; i<SIZE - 1; i++) //���� ��� �������� ����� ��������� �� ������ ��������
		{		
		//�������� �������� �������� � �������� �� �������, ���� ������ ������� ������ �������
		if (array[i] > array[i+1])
		 {
			hold = array[i];
			array[i] = array[i+1];
			array[i+1] = hold;	
		 } 
		} 
	} 
	
	printf("\n");
	printf("�������������� ������ \n");
	for (i=0; i<SIZE; i++)
	{
		printf("%1d \n", array[i]);
	}
	
	
/* ������� ���������� ���������� �����, � ����� �� ����� */
	int number;  //����������� �����, �� ������� ���� � ���������� ���� � �������
	int kol = 0; //����������� ��������
	
	printf("\n������� ����� ");
 	scanf("%d", &number);
	
	
	printf("\n���-�� ����� "); 
	for (i=0; i<SIZE; i++)         // ��� ������ ������� ����
	{	
		if ( array[i] == number)   // ���� ������� ������� = ���������� ����� � ���������
    		{	
    		kol++;    // ��������� ��������
		}
	}
	printf("%d", kol);
	   
    
	getch();
	return 0;
}






