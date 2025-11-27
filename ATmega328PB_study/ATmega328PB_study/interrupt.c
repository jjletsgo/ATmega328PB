/*
 * interrupt.c
 *
 * ATmega128 외부 인터럽트 INT1 설정 및 ISR
 */

#include "interrupt.h"

// ISR과 main에서 같이 쓰는 플래그
volatile uint8_t INT1_flag = 0;

// 전역 인터럽트 enable
void set_global_INT(void) {
    sei();
}

// INT1 설정: PD1(INT1), Falling edge 트리거
void setup_INT1(void) {
    // 여기서는 글로벌 인터럽트는 건드리지 않음 (main에서 set_global_int()로 켜게 함)

    // 1) INT1 잠깐 disable (Interrupt 레지스터 설정하려면 이 순서 지켜야함)
    EIMSK &= ~(1 << INT1); 

    // 2) 트리거 조건 설정: Falling edge
    //    ISC11 = 1, ISC10 = 0
    EICRA &= ~((1 << ISC11) | (1 << ISC10)); // 둘 다 0으로 클리어
    EICRA |=  (1 << ISC11);                  // ISC11만 1로 세트 -> INT1의 Falling Edge에서 INT1 인터럽트가 트리거되도록 설정

    // 3) 이전에 남아 있을 수 있는 INTF1 플래그 클리어
    EIFR |= (1 << INTF1); //INTF1에 1을 WRITE하면 CLEAR 됨.

    // 4) INT1 enable
    EIMSK |= (1 << INT1);
	
	DDRD &= ~(1<<3); //PD3=INT1을 입력으로 설정
	PORTD |= (1<<3); //PD3=INT1에 풀업 저항 설정
}

// INT1 인터럽트 서비스 루틴
ISR(INT1_vect) {
	INT1_flag = 1;      // 토글 말고 "발생했다"로 고정
}

// int1_flag 읽기
uint8_t get_flag(void) {
    uint8_t flag = INT1_flag;
	INT1_flag = 0; 
	return flag;
}
