#include "global.h"
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
void title_to_date();
void flash();
extern int increase_carry;
void increase(int which);

// timer_go() ---call---> timer()
//     timer_go: the CLK divider
//     timer:    actually modify the model

// title_to_time(), title_to_date(): push model to view

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

void title_to_time()
{
	digit4 = minute % 10;
	digit3 = minute / 10;
	digit2 = hour % 10;
	digit1 = hour / 10;
}

void title_to_date()
{
	digit4 = day % 10;
	digit3 = day / 10;
	digit2 = month % 10;
	digit1 = month / 10;
	if (digit3 == 0)
		digit3 = ' ';
	if (digit1 == 0)
		digit1 = ' ';
}

void timer_go()
{
	if (++divider == 20) {
		divider = 0;
		second++;
		timer();
	}
}

int flash_hidden = 0;

void flash()
{
	if (divider % 5 == 0) {
		flash_hidden = !flash_hidden;
	}
	if(flash_hidden) {
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

void timer_int()
{
	static int key_b_time = 0;
	if (key_b == 1)
		key_b_time++;

	else
		key_b_time = 0;
	if (key_b_time >= 40 && flag != 0) {
		increase(flag);
	}

	timer_go();
	if (flag == 0) {
		if(key_b == 1) {
			title_to_date();
			colon = 0;
		}
		else {
			title_to_time();
			if (divider % 10 == 0)
				colon = !colon;
		}
	}
	else {
		if(flag == 1 || flag == 2) {
			colon = 1;
			title_to_time();
		}
		else {
			colon = 0;
			title_to_date();
		}
		flash();
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
