#include "global.h"
#include "controller.h"
#include "model.h"
#include "view.h"
#include <stdio.h>

int key_a = 0;
int key_b = 0;

int divider=0;

static int flag=0;

void timer_to_title();
int A();
int B();
void timer();
void digit_time();
void digit_date();
void title_to_time();
void title_to_date();
void flash();

void timer_to_title()
{
  switch(flag)
    {
    case 2:
      if(digit4!=' ')
	minute=digit4 + digit3 * 10;
      break;
    case 3:
      if(digit2!=' ')
        hour=digit2 + digit1 *10;
      break;
    case 4:
      if(digit4!=' ')
	{
	  if(digit3 == ' ')
	    day=digit4;
	  else
	    day=digit4 +digit3 *10;
	}
      break;
    case 0:
      if(digit2!=' ')
	{
	  if(digit1 == ' ')
	    month=digit2;
	  else
	    month= digit2 + digit1 *10;
	}
      break;
    case 1:
      break;
    }
}


int A()
{
  static int prev_key_a=0;
  int temp=0;
  if(prev_key_a ==0 && key_a ==1)
    {
      temp=1;
    }
  prev_key_a=key_a;
  return temp;
}

int B()
{
   static int prev_key_b = 0;
   int temp=0;
    if(prev_key_b == 0 && key_b == 1)
    {
      temp=1;
    }
    prev_key_b = key_b;
    return temp;
}

void timer()
{
  if(second>=60)
    {
      second=0;
      minute++;
    }
  if(minute>=60)
    {
      minute=0;
      hour++;
    }
  if(hour>=24)
    {
      hour=0;
      day++;
    }
  if(day>month_num_days[month-1])
    {
      day=1;
      month++;
    }
  if(month>12)
    month=1;
}

void title_to_time()
{
  digit4 =minute%10;
  digit3 =minute/10;
  digit2 =hour%10;
  digit1 =hour/10;
}

void title_to_date()
{
  digit4 =day%10;
  digit3 =day/10;
  digit2 =month%10;
  digit1 =month/10;
  if(digit3 ==0)
    digit3= ' ';
  if(digit1 ==0)
    digit1= ' ';
}

void timer_go()
{
  if(++divider==20)
    {
      divider=0;
      second++;
      timer();
    }
}

void flash()
{
  colon=1;
  if(divider%5==0)
    {
      switch(flag)
	{
	case 1:
	  if(digit4!=' ')
	      digit4=digit3=' ';
	  else
	    title_to_time();
	  break;
	case 2:
	  if(digit2!=' ')
	      digit1=digit2=' ';
	  else
	    title_to_time();
	  break;
	case 3:
	  if(digit2!=' ')
	      digit2=digit1=' ';
	  else
	    title_to_date();
	  break;
	case 4:
	  if(digit4!=' ')
	    digit4=digit3=' ';
	  else
	    title_to_date();
	  break;
	default:
	  break;
	}
    }
}

void timer_int()
{
  static int key_b_time=0;
  if(key_b==1)
    key_b_time++;
  else
    key_b_time=0;
  if(key_b_time>=40 && flag!=0)
    {
      switch(flag)
	{
	  case 1:
	    minute++;
	    if(minute>59)
	      minute=0;
	    title_to_time();
	    break;
	  case 2:
	    hour++;
	    if(hour>23)
	      hour=0;
	    title_to_time();
	    break;
	  case 3:
	    month++;
	    if(month>12)
	      month=1;
	    title_to_date();
	    break;
	  case 4:
	    day++;
	    if(day>month_num_days[month-1])
	      day=1;
	    title_to_date();
	    break;
	  default:
	    break;      
	  }
    }
    
  timer_go();
  
  if(flag == 0 && key_b==1)
    {
      title_to_date();
      colon=0;
    }
  else if(flag ==0)
    {
      title_to_time();
      if(divider%10 ==0)
	colon=!colon;
    }

  if(flag !=0)
    flash();

  if(flag ==3||flag==4)
    colon=0;
  
  if(A())
    {
      flag++;
      if(flag>4)
	flag=0;
	timer_to_title();
    }
  
  if(B())
    {
       switch(flag)
	{
	  case 0:
	    break;
	  case 1:
	    minute++;
	    if(minute>59)
	      minute=0;
	    title_to_time();
	    break;
	  case 2:
	    hour++;
	    if(hour>23)
	      hour=0;
	    title_to_time();
	    break;
	  case 3:
	    month++;
	    if(month>12)
	      month=1;
	    title_to_date();
	    break;
	  case 4:
	    day++;
	    if(day>month_num_days[month-1])
	      day=1;
	    title_to_date();
	    break;
	  default:
	    break;      
	  }
    }

}



