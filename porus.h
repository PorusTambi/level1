#ifndef porus
#define porus
#include<avr/io.h>    //cursor appears after latest written character this 0x80+x we do for accesing rectangles/pixels
#include<util/delay.h>
#include<stdlib.h>   //for itoa conversion
#define mrlcd_data       PORTB
#define mrlcd_control    PORTE
#define read_write         1 //enable at pd5 r/w off write mode read means microcontroller read data from lcd
#define light_switch       2
#define what_we_send       0
void send_a_command1(unsigned char vamp );
void send_a_character1(unsigned char temp); //unsigned because we want only +
void check_busy1(void);
void_send_a_string1(unsigned char *p);
void on_off1(void);
int lcd1firstcolumnposition[2]={64,0}; //a,b,c,d are known numbers
void goto_location1(unsigned int x,unsigned int y);
void initialize_lcd1(void);


void check_busy1()
{ DDRB=0b00000000; //since first we want to know from lcd to give info abt he is bsy or not portb is for i/p
  mrlcd_control|=(1<<read_write); //sets for reading
  mrlcd_control&=~(1<<what_we_send); //sice lcd sends commmand
 while(mrlcd_data>=0X80) // if pb7 is 1 lcd busy else not portb=10000000; binary to hex is 0x80 0x is symbol for hexadecimal
{ on_off1();  //switching on off lights to read data 
}
DDRB=0xFF; //makes portb for o/p again as it has to be to transmit data
}
void on_off1()
{ mrlcd_control|=(1<<light_switch);
   asm volatile("nop");          //since lcd requires some time to see data to fully get it what we have told it to do
   asm volatile("nop");          // assembly command for delay
 mrlcd_control&=~(1<<light_switch);
   _delay_ms(100); // off lights to process data
                           //$$$ we not include delay here but it require some time to process data we will include delay in main
}
void send_a_command1(unsigned char vamp)
{ check_busy1();
  mrlcd_control&=~(1<<read_write);    //sets for writing lcd
  mrlcd_control&=~(1<<what_we_send);  //ensure we are sending command
  mrlcd_data=vamp;                    //giving data to lcd as portb connect to data pins
  on_off1();                           //setting lights on/off so that he can read data and process it
  mrlcd_data=0;                       //again make it 0 so nothing gets sent
}
void send_a_character1(unsigned char temp)
{ check_busy1();
  mrlcd_control&=~(1<<read_write);    
  mrlcd_control|=(1<<what_we_send);  //ensure we are sending command rest all same as sending command function
  mrlcd_data=temp;                    
  on_off1();                           
  mrlcd_data=0;
}                       
void send_a_string1(unsigned char *p)
{  while(*p!='\0')
  { send_a_character1(*p++); //post increment first send p then by array increment of addres it points to a[1] then a[2] so on
                            //when null character we stop 
  }
}
void goto_location1(unsigned int x,unsigned int y)
{ send_a_command1(0x80+(x-1)+lcd1firstcolumnposition[y-1]);

}
void initialize_lcd1(void)
{DDRE=0b11111111;
  _delay_ms(100);  //since lcd requires some time to get on 
send_a_command1(0x31); //command for clearing screen
 _delay_ms(60);  //$$$ since we not include delay there to processs we include here as command needs some time to process ^^^data not needs^^^
  send_a_command1(0x38); //command used to tell we are using all data pins 8 bit data not 4 bit data
  _delay_us(60);    //***these time are given in datasheet with commands
  send_a_command1(0b00001100); //starting from left first 1 to make command on,second for making display on,third for displaying cursor, fourth is whether we want blinking or still cursor
_delay_ms(60);
}
#endif