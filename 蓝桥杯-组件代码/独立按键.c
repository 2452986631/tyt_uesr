//读取键值
unsigned char read_key(void)
{
   unsigned char key_temp;
   key_temp = (P3 & 0x0f);

   if (key_temp != 0x0f) //有按键按下
       key_press++;
   else
       key_press = 0;  //抖动

   if (key_press == 5)
   {
       key_press = 0;
       key_re = 1;
       switch (key_temp)
       {
       case 0x0e:
           key_value = 1;  //S1
           break;
       case 0x0d:
           key_value = 2;  //S5
           break;
       case 0x0b:
           key_value = 3;  //S9
           break;
       case 0x07:
           key_value = 4;  //S13
           break;
       }
   }
   //连续三次检测到按键被按下，并且该按键已经释放
   if ((key_re == 1) && (key_temp == 0x0f))
   {
       key_re = 0;
       return key_value;
   }
   return 0xff;  //无按键按下或被按下的按键未被释放    
}