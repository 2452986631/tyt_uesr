sbit R1 = P3 ^ 0;
sbit R2 = P3 ^ 1;
sbit R3 = P3 ^ 2;
sbit R4 = P3 ^ 3;
sbit C1 = P4 ^ 4;
sbit C2 = P4 ^ 2;
sbit C3 = P3 ^ 5;
sbit C4 = P3 ^ 4;

//矩阵键盘
unsigned char key_scan()
{
	static unsigned char key_sat = 0;
	unsigned char key_return = 0, key_press;
	unsigned char keyr, keyc;
	R3 = 0; R4 = 0; 
	C1 = 1; C2 = 1; C3 = 1; C4 = 1;
	if   (C1 == 0) 	  keyc = 0x70;
	else if (C2 == 0) keyc = 0xb0;
	else if (C3 == 0) keyc = 0xd0;
	else if (C4 == 0) keyc = 0xe0;
	else keyc = 0xf0;
	
	R3 = 1; R4 = 1; 
	C1 = 0; C2 = 0; C3 = 0; C4 = 0;
	if (R3 == 0)      keyr = 0x0b;
	else if (R4 == 0) keyr = 0x07;
	else              keyr = 0x0f;
	
	key_press = keyc | keyr;

	switch (key_sat)
	{
	case 0:
		if (key_press != 0xff) key_sat = 1;
		break;
	case 1:
		if (key_press != 0xff)
		{
			if (key_press == 0x77) key_return = 4;
			if (key_press == 0xb7) key_return = 8;
			if (key_press == 0xd7) key_return = 12;
			if (key_press == 0xe7) key_return = 16;
			if (key_press == 0xbb) key_return = 9;
			key_sat = 2;
		}
		else key_sat = 0;
		break;
		
	case 2:
		if (key_press == 0xff) key_sat = 0;
		break;
	}
	return key_return;
}