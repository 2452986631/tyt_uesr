//串口TXD与RXD引脚为P32与P31
sbit R1 = P3 ^ 0;
sbit R2 = P3 ^ 1;
sbit R3 = P3 ^ 2;
sbit R4 = P3 ^ 3;

sbit C1 = P4 ^ 4;
sbit C2 = P4 ^ 2;
sbit C3 = P3 ^ 5;
sbit C4 = P3 ^ 4;
//被注释的代码是使用串口的时候需要注释
//没有使用串口的时候不需要注释
//矩阵键盘
void Key_Borad()
{
	static unsigned char status=0;
  unsigned char keyr,keyc,key_press;

  //R1=1; R2=1; 
  R3=1; R4=1; 
  C1=0; C2=0; C3=0; C4=0; 
  if(R1==0) keyr=0xe0;
  else if(R2==0) keyr=0xd0;
  else if(R3==0) keyr=0xb0;
  else if(R4==0) keyr=0x70;
  else keyr=0xf0;
  //R1=0; R2=0; 
  R3=0; R4=0; 
  C1=1; C2=1; C3=1; C4=1; 
  if(C1==0) keyc=0x07;
  else if(C2==0) keyc=0x0b;
  else if(C3==0) keyc=0x0d;
  else if(C4==0) keyc=0x0e;
  else keyc=0x0f;
 
	key_press= keyr | keyc;
	switch(status)
	{
		case 0: { if(key_press!=0xff) status=1; } break;
		case 1:
		{
			if(key_press!=0xff)
			{
//				if(key_press==0xe7) key_value=1;
//				if(key_press==0xeb) key_value=2;
//				if(key_press==0xed) key_value=3;
//				if(key_press==0xee) key_value=4;

//				if(key_press==0xd7) key_value=5;
//				if(key_press==0xdb) key_value=6;
//				if(key_press==0xdd) key_value=7;
//				if(key_press==0xde) key_value=8;

				if(key_press==0xb7) key_value=9;
				if(key_press==0xbb) key_value=10;
				if(key_press==0xbd) key_value=11;
				if(key_press==0xbe) key_value=12;

				if(key_press==0x77) key_value=13;
				if(key_press==0x7b) key_value=14;
				if(key_press==0x7d) key_value=15;
				if(key_press==0x7e) key_value=16;
				status=2;
			}
			else status=0;
		}break;
		case 2:
		{
			if(key_press==0xff) status=0;
		}break;
	}
}