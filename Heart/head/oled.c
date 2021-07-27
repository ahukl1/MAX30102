#include "oled.h"
struct oled_pot * start_pot[8];
void write(unsigned char data,int type){
	switch(type)
	{
		case 0:HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);break;
		case 1:HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);break;
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1,&data,1,1000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
}
void OLED_WrCmd(uint8_t command){
  write(command,0);
}
void OLED_WrData(uint8_t data){
  write(data,1);
}
void OLED_Init(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	unsigned int a;
	for(a=0;a<5000;a++);
	OLED_WrCmd(0xAE);//--turn off oled panel
 	OLED_WrCmd(0x00);//---set low column address
 	OLED_WrCmd(0x10);//---set high column address
 	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0xB0);
 	OLED_WrCmd(0x81);//--set contrast control register
 	OLED_WrCmd(0xFF); // Set SEG Output Current Brightness
 	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
 	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
 	OLED_WrCmd(0xa6);//--set normal display
 	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
 	OLED_WrCmd(0x3f);//--1/64 duty``
 	OLED_WrCmd(0xd3);//-set display offset Shift Mapping RAM Counter (0x00~0x3F)
 	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
 	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
 	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
 	OLED_WrCmd(0xda);//--set com pins hardware configuration
 	OLED_WrCmd(0x12);
 	OLED_WrCmd(0xdb);//--set vcomh
 	OLED_WrCmd(0x40);//Set VCOM Deselect Level
 	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
 	OLED_WrCmd(0x02);//
 	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
 	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
 	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7)
 	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Clear();//OLED清屏
}
void OLED_Clear(void){
unsigned char i,n;
  for(i=0; i<8; i++)
  {
    OLED_WrCmd(0xb0+i); //设置页地址（0~7）
    OLED_WrCmd(0x00); //设置显示位置—列低地址
    OLED_WrCmd(0x10); //设置显示位置—列高地址
    for(n=0; n<128; n++)	OLED_WrData(0x00); //写0x00到屏幕寄存器上
  }
}
void OLED_Start(void){
   unsigned char i,n;
  for(i=0; i<8; i++)
  {
    OLED_WrCmd(0xb0+i); //设置页地址（0~7）
    OLED_WrCmd(0x00); //设置显示位置—列低地址
    OLED_WrCmd(0x10); //设置显示位置—列高地址
    for(n=0; n<128; n++)	OLED_WrData(start[i][n]); //写0x00到屏幕寄存器上
  }
}
void OLED_Close_page(void){
  unsigned char i,n;
  for(i=0; i<8; i++)
  {
    OLED_WrCmd(0xb0+i); //设置页地址（0~7）
    OLED_WrCmd(0x00); //设置显示位置—列低地址
    OLED_WrCmd(0x10); //设置显示位置—列高地址
    for(n=0; n<128; n++)	OLED_WrData(close_img[i][n]); //写0x00到屏幕寄存器上
  }
}
void OLED_page2(void){
unsigned char i,n;
  for(i=0; i<8; i++)
  {
    OLED_WrCmd(0xb0+i); //设置页地址（0~7）
    OLED_WrCmd(0x00); //设置显示位置—列低地址
    OLED_WrCmd(0x10); //设置显示位置—列高地址
    for(n=0; n<128; n++)	OLED_WrData(page_2[i][n]); //写0x00到屏幕寄存器上
  }
}
void OLED_SetPos(uint8_t x, uint8_t y){
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd(x&0x0f);
}
void OLED_DrawPoint(unsigned char x,unsigned char y)
{
	unsigned char pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	OLED_SetPos(x,pos);
	OLED_WrData(temp);
 
}
void OLED_ON(void){
  WriteCmd(0X8D);  //设置电荷泵
  WriteCmd(0X14);  //开启电荷泵
  WriteCmd(0XAF);  //OLED唤醒
	}
void OLED_OFF(void){
  WriteCmd(0X8D);  //设置电荷泵
  WriteCmd(0X10);  //关闭电荷泵
  WriteCmd(0XAE);  //OLED休眠
}
void OLED_ShowChar(int x,int y,char txt[]){
	 int i,j;
	  y=y*8;
	 OLED_WrCmd(0xb0+2*x);
	 OLED_WrCmd(0x10|((0xf0&y)>>4));
	 OLED_WrCmd(0x00|(0x0f&y));
	 for(i=0;txt[i]!='\0';i++){
		 if(txt[i]-' '<0||txt[i]-' '>94) continue;
		 for(j=0;j<8;j++){
			 OLED_WrData(asc2_1206[txt[i]-' '][j]);
		 }
	 }
	 OLED_WrCmd(0xb0+2*x+1);
	 OLED_WrCmd(0x10|((0xf0&y)>>4));
	 OLED_WrCmd(0x00|(0x0f&y));
	 for(i=0;txt[i]!='\0';i++){
		 if(txt[i]-' '<0||txt[i]-' '>94) continue;
		 for(j=0;j<8;j++){
			 OLED_WrData(asc2_1206[txt[i]-' '][j+8]);
		 }
	 }
}
void OLED_ShowWord(int x,int y,int f){
	 int i,j;
	 y=y*8;
	 OLED_WrCmd(0xb0+2*x);
	 OLED_WrCmd(0x10|((0xf0&y)>>4));
	 OLED_WrCmd(0x00|(0x0f&y));
	 for(i=0;i<16;i++){
		 OLED_WrData(word[f][i]);
	 }
	 OLED_WrCmd(0xb0+2*x+1);
	 OLED_WrCmd(0x10|((0xf0&y)>>4));
	 OLED_WrCmd(0x00|(0x0f&y));
	 for(i=0;i<16;i++){
		 OLED_WrData(word[f][i+16]);
	 }
}
void OLED_ShowNum(int y,int x,int num)
{
	int j;
	x=x*8;
	OLED_WrCmd(0xb0+2*y);
	 OLED_WrCmd(0x10|((0xf0&x)>>4));
	 OLED_WrCmd(0x00|(0x0f&x));
		 for(j=0;j<8;j++){
			 OLED_WrData(font_num[num][j]);
		 }

	 OLED_WrCmd(0xb0+2*y+1);
	 OLED_WrCmd(0x10|((0xf0&x)>>4));
	 OLED_WrCmd(0x00|(0x0f&x));
		 for(j=0;j<8;j++){
			 OLED_WrData(font_num[num][j+8]);
		 }
}
void OLED_ShowNums(int y,int x,int num,int len)
{
	int i;
	int dat;
	dat=num;
	for (i=0;i<len;i++){
		OLED_ShowNum(y,x+len-i-1,dat%10);
		dat=dat/10;
	}
}