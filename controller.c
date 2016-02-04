// -*- mode: c; c-file-style: linux -*-
#include "controller.h"
#include "model.h"
#include "view.h"
#include <stdio.h>
int key_a = 0;
int key_b = 0;
int divider = 0;
static int flag = 0;
// 0 --> NORMAL
// 1 --> MIN
// 2 --> HOUR
// 3 --> MONTH
// 4 --> DAY

int A();
int B();
void timer();
void title_to_time();
void display_date();
void blink();
extern int increase_carry;
void increase(int which);

// timer_go() ---call---> timer()
//     timer_go: the CLK divider
//     timer:    actually modify the model

// title_to_time(), display_date(): push model to view

int A()
{
	static int prev_key_a = 0;
	int temp = 0;
	if (prev_key_a == 0 && key_a == 1) {
		temp = 1;
	}
	prev_key_a = key_a;
	return temp;
}

int B()
{
	static int prev_key_b = 0;
	int temp = 0;
	if (prev_key_b == 0 && key_b == 1) {
		temp = 1;
	}
	prev_key_b = key_b;
	return temp;
}

void timer()
{
	if (second >= 60) {
		second = 0;
		increase(1);
	}
	if(increase_carry) { increase(2); }
       	if(increase_carry) { increase(4); }
	if(increase_carry) { increase(3); }
}

int hide_zero(int n)
{
	return (n == 0) ? ' ' : n;
}

void display_time()
{
	int hour2 = ((hour % 12) == 0) ? 12 : (hour % 12);

	digit4 = minute % 10;
	digit3 = minute / 10;
	digit2 = hour2 % 10;
	digit1 = hide_zero(hour2 / 10);
}

void display_date()
{
	digit4 = day % 10;
	digit3 = hide_zero(day / 10);
	digit2 = month % 10;
	digit1 = hide_zero(month / 10);
}

void timer_go()
{
	if (++divider == 20) {
		divider = 0;
		second++;
		timer();
	}
}

int blink_hidden = 0;
int blink_timer;

void blink_reset()
{
	blink_timer = 0;
	blink_hidden = 0;
}

void blink()
{
	blink_timer++;
	if(blink_timer == 5) {
		blink_timer = 0;
		blink_hidden = !blink_hidden;
	}
	if(blink_hidden) {
		if(flag == 1 || flag == 4) {
			digit4 = digit3 = ' ';
		}
		else {
			digit2 = digit1 = ' ';
		}
	}
}

int increase_carry;

void increase(int which)
{
	increase_carry = 0;

	switch (which) {
	case 1:
		if (++minute > 59) {
			minute = 0;
			increase_carry = 1;
		}
		break;
	case 2:
		if (++hour > 23) {
			hour = 0;
			increase_carry = 1;
		}
		break;
	case 3:
		if (++month > 12) {
			month = 1;
			increase_carry = 1;
		}
		break;
	case 4:
		if (++day > month_num_days[month - 1]) {
			day = 1;
			increase_carry = 1;
		}
		break;
	}
}

int fast_inc_enabled = 0;
int fast_inc_timer1 = 0;
int fast_inc_timer2 = 0;

void timer_int()
{
	if(fast_inc_enabled) {
		if(key_b == 0) {
			fast_inc_enabled = 0;
		}
		else if(++fast_inc_timer2 >= 2) {
			fast_inc_timer2 = 0;
			increase(flag);
		}
	}
	else {
		if (key_b == 1) {
			if(++fast_inc_timer1 >= 20) {
				fast_inc_timer1 = 0;
				fast_inc_timer2 = 0;
				fast_inc_enabled = 1;
			}
		}
		else {
			fast_inc_timer1 = 0;
		}
	}

	timer_go();
	if (flag == 0) {
		if(key_b == 1) {
			display_date();
			colon = 0;
		}
		else {
			display_time();
			if (divider % 10 == 0)
				colon = !colon;
		}
	}
	else {
		if(flag == 1 || flag == 2) {
			colon = 1;
			display_time();
			
			if(flag == 2) {
				digit3 = (hour >= 12) ? 'P' : 'A';
				digit4 = ' ';
			}
		}
		else {
			colon = 0;
			display_date();
		}
		if(key_b == 1) {
			blink_reset();
		}
		else {
			blink();
		}
	}

	if (A()) {
		if (++flag > 4) {
			flag = 0;
		}
	}
	if (B()) {
		increase(flag);
	}
}
