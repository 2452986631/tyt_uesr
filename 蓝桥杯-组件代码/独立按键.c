//独立按键
void Key_button()
{
	static unsigned char status=0;
	switch(status)
	{
		case 0:
		{
			P3=0x0f; if(P3!=0x0f) status=1;
		}break;
		case 1:
		{
			P3=0x0f; 
			if(P3!=0x0f)
			{
				if(P30==0) {key_value=1; status=2;}
				if(P31==0) {key_value=2; status=2;}
				if(P32==0) {key_value=3; status=2;}
				if(P33==0) {key_value=4; status=2;}
			}
			else status=0;
		}break;
		case 2:
		{
			P3=0x0f; if(P3==0x0f) status=0;
		} break;
	}
}
