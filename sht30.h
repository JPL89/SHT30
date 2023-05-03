// @File		SHT30.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		01/05/23
//
//
// Copyright (C) 2023  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef SHT30_H
#define SHT30_H

#define SHT30_SLA_W 0x88
#define SHT30_SLA_R 0x89

void SHT30_Repeat(void)
{
    Wire_Start();
    Wire_Write( SHT30_SLA_W );
    Wire_Write( 0x2c ); 
    Wire_Write( 0x06 ); 
    Wire_Stop();    
}

void SHT30_Read_Temp(unsigned int *t, unsigned int *h)
{
    unsigned char data[6];
    
    Wire_Start();
    Wire_Write( SHT30_SLA_W );
    Wire_Write( 0xE0 ); 
    Wire_Write( 0x00 ); 
    Wire_Start();
    Wire_Write( SHT30_SLA_R );   
    data[0] = Wire_Ack(); 
    data[1] = Wire_Ack(); 
    data[2] = Wire_Ack(); 
    data[3] = Wire_Ack(); 
    data[4] = Wire_Ack(); 
    data[5] = Wire_Nack(); 
    Wire_Stop(); 
    
    unsigned int temp = (unsigned int) (data[0] << 8) | data[1];
    unsigned int humi = (unsigned int) (data[3] << 8) | data[4];
	
    *t = (unsigned int) (((temp * 175.72) / 65535.0) - 46.85);
    *h = (unsigned int) (((humi * 125.0) / 65536.0) - 6);
}  

#endif
