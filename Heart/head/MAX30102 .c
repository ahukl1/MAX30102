#include "MAX30102.h"
int maxim_max30102_write_reg(uint8_t uch_addr, uint8_t uch_data){
	  HAL_I2C_Mem_Write(&hi2c1, I2C_WRITE_ADDR,uch_addr, I2C_MEMADD_SIZE_8BIT,&uch_data,1, 1000);
}

int maxim_max30102_reset()
{
	    maxim_max30102_write_reg(REG_MODE_CONFIG,0x40);
		    maxim_max30102_write_reg(REG_MODE_CONFIG,0x03);
maxim_max30102_write_reg(REG_INTR_ENABLE_1,0x40); // INTR setting

maxim_max30102_write_reg(REG_INTR_ENABLE_2,0x50);

maxim_max30102_write_reg(REG_FIFO_WR_PTR,0x00); //FIFO_WR_PTR[4:0]

maxim_max30102_write_reg(REG_OVF_COUNTER,0x00);  //OVF_COUNTER[4:0]

maxim_max30102_write_reg(REG_FIFO_RD_PTR,0x00) ; //FIFO_RD_PTR[4:0]

 maxim_max30102_write_reg(REG_FIFO_CONFIG,0x0f);  //sample avg = 1, fifo rollover=false, fifo almost full = 17
maxim_max30102_write_reg(REG_MODE_CONFIG,0x03)  ; //0x02 for Red only, 0x03 for SpO2 mode 0x07 multimode LED
 maxim_max30102_write_reg(REG_SPO2_CONFIG,0x27);  // SPO2_ADC range = 4096nA, SPO2 sample rate (100 Hz), LED pulseWidth (400uS) 
maxim_max30102_write_reg(REG_LED1_PA,0x24) ;  //Choose value for ~ 7mA for LED1
maxim_max30102_write_reg(REG_LED2_PA,0x24) ;  // Choose value for ~ 7mA for LED2
maxim_max30102_write_reg(REG_PILOT_PA,0x7f) ;  // Choose value for ~ 25mA for Pilot LED
		  maxim_max30102_write_reg(0x03,0x00);
		  maxim_max30102_write_reg(0x21,0x01);

}

