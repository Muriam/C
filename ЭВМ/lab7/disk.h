#include<stdio.h>
#include<stdlib.h>
// С - цилиндры, H - число головок, S - число секторов на дорожку
typedef struct
{
  unsigned long int C:10, H:4, S:6;
} tCHS;
typedef struct
{
  unsigned long int C:10, H:8, S:6;
} tLARGE;
typedef struct
{
  unsigned long int C:16, H:4, S:8;
} tIDECHS;
typedef unsigned long int tLBA;
typedef struct
{
  unsigned char active;   
  tLARGE startCHS;        
  unsigned char type;     
  tLARGE endCHS;           
  tLBA startLBA;         
  unsigned int size; 
} tPartition;

int g_lba2chs (tLBA, tCHS *);
int g_lba2large (tLBA, tLARGE *);
int g_lba2idechs (tLBA, tIDECHS *);
int g_chs2large (tCHS,  tLARGE *);
int g_chs2idechs (tCHS, tIDECHS *);
int g_chs2lba (tCHS, tLBA *);
int g_large2chs (tLARGE, tCHS *);
int g_large2idechs (tLARGE, tIDECHS *); 
int g_large2lba (tLARGE, tLBA *);
int g_idechs2chs (tIDECHS, tCHS *);
int g_idechs2lagre (tIDECHS, tLARGE *);
int g_idechs2lba (tIDECHS, tLBA *);

int a_lba2chs (tCHS, tLBA, tCHS *);
int a_lba2large (tLARGE, tLBA, tLARGE *);
int a_lba2idechs (tIDECHS,  tLBA, tIDECHS *);
int a_chs2lba (tCHS, tCHS, tLBA *);
int a_large2lba (tLARGE, tLARGE, tLBA *);
int a_idechs2lba (tIDECHS, tIDECHS, tLBA *);
int a_large2chs (tLARGE, tCHS, tLARGE, tCHS *);
int a_large2idechs (tLARGE, tIDECHS, tLARGE, tIDECHS *);
int a_chs2large (tCHS, tLARGE, tCHS, tLARGE *);
int a_idechs2large (tIDECHS, tLARGE, tIDECHS, tLARGE *);
int a_chs2idechs (tCHS, tIDECHS, tCHS, tIDECHS *);
int a_idechs2chs (tIDECHS, tCHS, tIDECHS, tCHS *); 
