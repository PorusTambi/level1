#include "porus.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <stdlib.h>
#include<avr/interrupt.h>
int y=1; int x=1; char a[3]; int i,j;
int main()
{ initialize_lcd1();
	goto_location1(3,1);
	send_a_string1("g@me starts in");
	
	goto_location1(10,2);
	send_a_string1("3");
	_delay_ms(1000);
	goto_location1(10,2);
	send_a_string1(" ");
	
	goto_location1(10,2);
	send_a_string1("2");
	_delay_ms(1000);
	goto_location1(10,2);
	send_a_string1(" ");
	
	goto_location1(10,2);
	send_a_string1("1");
	_delay_ms(1000);
	goto_location1(10,2);
	send_a_string1(" ");
	
	goto_location1(3,1);           //to clear whole screen
	send_a_string1("                  ");
	 goto_location1(1,1);
	 send_a_string1("p");
	 
	 DDRD&=~(1<<PIND3);
	 PORTD|=(1<<PIND3);
		MCUCR|=1<<ISC11||1<<ISC10;                 //setting two external interrupts
		GICR|=1<<INT0;                             //purpose of using interruppts is that
		                                           //1)bit_is_set is not sense to fast thrg switch
												   //2)if some statements are above bit_is_set in prgrm and btton is pressed before then nothing
												   //3)now in interrupt advantage is that when interrupt devlops normal execution of prgrm at current position stops and go to ISR code block
		DDRD&=~(1<<PIND2);
		PORTD|=(1<<PIND2);
		MCUCR|=1<<ISC01||1<<ISC00;
		GICR|=1<<INT1;
	sei(); 
	
	
	 j=1;  i=16;
	while(1)
	{ if(i==x&&j==y)
		{  goto_location1(x,y);
			send_a_string1(" ");
			goto_location1(i,j);
			send_a_string1(" ");
			goto_location1(3,1);
			send_a_string1("game over");
			_delay_ms(2000);
			break;
			
		}
	else{
		  	
		   goto_location1(i,j);
		    send_a_string1("#");
		   _delay_ms(1000);
		    goto_location1(i,j);
		    send_a_string1(" ");
		   switch(j)                        //zig zag pattern of hash going from cordinate changing like (16,1) then 15,2 then 14,1 so on
		   {
			case 1:
			j=2; 
			break;
			case 2:
			j=1;
			break;
			
		   }
		i=i-1;
		 if(i==0)
		{
			i=16;
		}
	}
	if(x==16)
	{
		goto_location1(x,y);
		send_a_string1(" ");
		goto_location1(i,j);
		send_a_string1(" ");
		goto_location1(3,1);
		send_a_string1("you win");
		_delay_ms(2000);
		break;
	}
}
	
	/*for(x=61;x<=128;x++)
	{    send_a_command(0x80+x);
		send_a_string("x");
		_delay_ms(200);                                 //CHECK POSITIONS CODE
		send_a_command(0x80+x);
		send_a_string(" ");
		itoa(x,a,10);
		send_a_command(0x80+11);
		send_a_string(a);
		_delay_ms(100);
		send_a_string(" ");
	}*/
	

}
ISR(INT1_vect)
{  if(i==x&&j==y)
	{  goto_location1(x,y);
		send_a_string1(" ");
		goto_location1(i,j);
		send_a_string1(" ");
		goto_location1(3,1);
		send_a_string1("game over");
		_delay_ms(2000);
		
		
	}
	else
	{    
		
	        if(y==1)
	       {  goto_location1(x,y);
		      send_a_string1(" ");
		      goto_location1(x,++y);             //interrupt int1 for up down
	          send_a_string1("p");
		
           }
         else if(y==2)
        { 
         goto_location1(x,y);
         send_a_string1(" ");
         goto_location1(x,--y);
         send_a_string1("p");
         }
	}
	if(x==16)
	{
		goto_location1(x,y);
		send_a_string1(" ");
		goto_location1(i,j);
		send_a_string1(" ");
		goto_location1(3,1);
		send_a_string1("you win");
		_delay_ms(2000);
		
	}
}


ISR(INT0_vect)
{   if(i==x&&j==y)
	{  goto_location1(x,y);
		send_a_string1(" ");
		goto_location1(i,j);
		send_a_string1(" ");
		goto_location1(3,1);
		send_a_string1("game over");
		_delay_ms(2000);
		
		
	}    
	else
		{    
			
			goto_location1(x,y);
		    send_a_string1(" ");
		    goto_location1(x+1,y);     //for moving to right another interrupt
		     send_a_string1("p");
		     x=x+1;
	    }
	if(x==16)
	{
		goto_location1(x,y);
		send_a_string1(" ");
		goto_location1(i,j);
		send_a_string1(" ");
		goto_location1(3,1);
		send_a_string1("you win");
		_delay_ms(2000);
	
	}	
		
		
		
	
}