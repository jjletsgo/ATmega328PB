/*
 * spi.c
 *
 * Created: 2025-11-22 오후 9:22:37
 *  Author: User
 */ 

#include "spi.h"

void SPI_MasterInit(void)     
{
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0); //SPI허용, SPI 마스터로 동작, 시스템 클럭을 16으로 분주해서 사용
	/* Set MOSI and SCK output, all others input */
	DDRB|= ( 1<< 2) | (1 << 3) | (1 << 5); //SS,SCK,MOSI를 OUTPUT으로 설정(사용하는 칩에 맞게 수정 필수!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
	PORTB |= (1<<2);  // SS idle high
}
void SPI_MasterTransmit(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));   
}
