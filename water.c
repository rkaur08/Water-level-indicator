#include<pic.h>

#define LCD PORTB
#define RS RD6
#define EN RD7

#define key3 RD2
#define key2 RD1
#define key1 RD0

#define LED1 RC2
#define LED2 RC1
#define LED3 RC0

#define RL RC3
#define buzz RD3

char W[10]="WELCOME ";
char E[10]="EMPTY   ";
char L[10]="LOW     ";
char H[10]="HALF    ";
char F[10]="FULL    ";

char l0,l1,l2,l3;
int i;

void level1();
void level2();
void level3();
void level0();

void cmd();
void data();
void latch();

void delay(unsigned int);


void main()
{
ANSELH=0X00;
TRISB=0X00;
TRISC=0X00;
TRISD=0X07;
PORTC=0X00;
PORTD=0X00;

LED1=0;LED2=0;LED3=0;
RL=0;
buzz=0;

LCD=0X30;
cmd();
LCD=0X0E;
cmd();
LCD=0X01;
cmd();
LCD=0X80;
cmd();

for(int n=0;n<8;n++)
{
LCD=W[n];
data();
}
delay(60000);
delay(60000);

LCD=0X01;
cmd();

l0=0;l1=0;l2=0;l3=0;
while(1)
{

if(key1 == 1 && key2 == 1 && key3 == 1 && l0==0)
{
l0=1;l1=0;l2=0;l3=0;
level0();
}
else if(key1 == 0&& key2 == 1 && key3 == 1 && l1==0)
{
l0=0;l1=1;l2=0;l3=0;
level1();
}
else if(key1 == 0 && key2 == 0 && key3 == 1 && l2==0)
{
l0=0;l1=0;l2=1;l3=0;
level2();
}
else if(key1 == 0 && key2 == 0 && key3 == 0 && l3==0)
{
l0=0;l1=0;l2=0;l3=1;
level3();
}

}
}
		
void cmd()
{
RS=0;
latch();
}

void data()
{
RS=1;
latch();
}

void latch()
{
EN=1;
delay(50);
EN=0;
delay(100);
}

void delay(unsigned int x)
{
while(x>0)
{
x--;
}
}

void level0()
{
LED1=0;LED2=0;LED3=0;

for(int j=0;j<6;j++)
{
buzz=1;
delay(10000);
buzz=0;
delay(10000);

}
LCD=0X80;
cmd();
for(i=0;i<8;i++)
{
LCD=E[i];
data();
}
buzz=0;
RL=1;
}

void level1()
{
LED1=1;LED2=0;LED3=0;
buzz=0;
LCD=0X80;
cmd();
for(i=0;i<8;i++)
{
LCD=L[i];
data();
}
}

void level2()
{
LED1=0;LED2=1;LED3=0;
buzz=0;
LCD=0X80;
cmd();
for(i=0;i<8;i++)
{
LCD=H[i];
data();
}
}

void level3()
{
LED1=0;LED2=0;LED3=1;
buzz=1;
delay(60000);
delay(60000);

LCD=0X80;
cmd();
for(i=0;i<8;i++)
{
LCD=F[i];
data();
}
buzz=0;
RL=0;
}
