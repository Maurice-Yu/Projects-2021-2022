#include "thermo.h"
//~ int thermo_update()
//~ {
	//~ temp_t x;
	//~ x.temp_mode = 0;
	//~ x.tenths_degrees=0;
	//~ int a = set_temp_from_ports(&x);
	//~ int b = set_display_from_temp(x,&THERMO_DISPLAY_PORT);
	//~ if(a==0 && b==0)
	//~ {	
		//~ return 0;
	//~ }	
	//~ return 1;
	//sets the temps then sets the display if both are free from errors then it will return zero
//~ }
//~ int set_temp_from_ports(temp_t *temp)
//~ {
	//~ //checks the sensors and sets the correct temp mode
	//~ if(THERMO_SENSOR_PORT<0||THERMO_SENSOR_PORT>28800)
	//~ {
		//~ temp->temp_mode = 3;
		//~ temp->tenths_degrees = 0;
		//~ return 1;
	//~ }
	//~ if((THERMO_STATUS_PORT & 0b100000)==0b100000)
	//~ {
		//~ temp->temp_mode = 2;
	//~ }
	//~ else
	//~ {	
		//~ temp->temp_mode = 1;	
	//~ }

	//~ if((THERMO_STATUS_PORT & 0b100)==0b100)
	//~ {
		//~ temp->temp_mode = 3;
		//~ temp->tenths_degrees=0;
		//~ return 1;
	//~ }
	// depending on the temp mode it will set the correct degrees
	//~ if(temp->temp_mode==1)
	//~ {
		//~ int x=THERMO_SENSOR_PORT&0b11111;
		//~ temp->tenths_degrees = ((THERMO_SENSOR_PORT>>5)-450);
		//~ if(x>=16)
		//~ {
		//~ temp->tenths_degrees +=1;
		//~ }	
	//~ }
	//~ if(temp->temp_mode == 2)
	//~ {
		//~ int x=THERMO_SENSOR_PORT&0b11111;
		//~ if(x>=16)
		//~ {
		//~ temp->tenths_degrees=(((((THERMO_SENSOR_PORT>>5)-450+1)*9)/5)+320);
		//~ }
		//~ else
		//~ {
		//~ temp->tenths_degrees=(((((THERMO_SENSOR_PORT>>5)-450)*9)/5)+320);
	//~ }
	//~ }
	//~ return 0;
//~ }
//~ int set_display_from_temp(temp_t temp, int *display)
//~ {
	//~ int zero = 0b1111011;
	//~ int one = 0b1001000;
	//~ int two = 0b0111101;
	//~ int three = 0b1101101;
	//~ int four = 0b1001110;
	//~ int five = 0b1100111;
	//~ int six = 0b1110111;
	//~ int seven = 0b1001001;
	//~ int eight = 0b1111111;
	//~ int nine = 0b1101111;
	//~ int e = 0b0110111;
	//~ int r = 0b1011111;
	//~ int blank = 0b0000000;
	//~ int negitive = 0b0000100;
	//~ int lst[] = {zero,one,two,three,four,five,six,seven,eight,nine,e,r,blank,negitive};
	//~ int mask= 0;
	//~ int sign= sign ^ sign;
	//~ int holder = 4;
	//~ short tempshort=temp.tenths_degrees;
	//~ *display=(*display ^ *display);
	//~ //checks if it is set to 1 or 2 just in case 
	//~ if(temp.temp_mode!=1&&temp.temp_mode!=2)
	//~ {
	//~ mask=mask^mask;//clears the mask
	//~ mask=mask | (lst[10]<<(7*3));
	//~ mask=mask | (lst[11]<<(7*2));
	//~ mask=mask | (lst[11]<<7);
	//~ *display=mask;
	//~ //sets the mask if its an error
	//~ return 1;
	//~ }
	
	//~ if(temp.temp_mode ==1)
	//~ {
	//~ if(tempshort<-450||tempshort>450)
	//~ {
		//~ mask=mask^mask;
	//~ mask=mask | (lst[10]<<(7*3));
	//~ mask=mask | (lst[11]<<(7*2));
	//~ mask=mask | (lst[11]<<7);
	//~ *display=mask;
	//~ //sets the mask if its an error
	//~ return 1;
	//~ }
	
	//~ }
	//~ if(temp.temp_mode ==2)
	//~ {
	//~ if(tempshort<-490||tempshort>1130)
	//~ {
		//~ mask=mask^mask;
	//~ mask=mask | (lst[10]<<(7*3));
	//~ mask=mask | (lst[11]<<(7*2));
	//~ mask=mask | (lst[11]<<7);
	//~ *display=mask;
	//~ //sets the mask if its an error
	//~ return 1;
	//~ }
	//~ }
	
	//~ if(tempshort<0)
	//~ {
		//~ sign=0b11111111;
		//~ tempshort=tempshort*-1;
	//~ }	//checks if its negitive
	//~ int units[] = {0,0,0,0};	
	//~ for(int i=0;i<4;i++)
	//~ {
	//~ //puts the numbers into an array
		//~ units[i]=tempshort%10;
		//~ tempshort=tempshort/10;
		//~ if(tempshort==0)
		//~ {
			//~ holder = i;
			//~ break;
		//~ }		
	//~ }

	//~ for(int i=0;i<4;i++)
	//~ {
		//~ mask = mask | (lst[units[i]]<<(7*i));	
	//~ }
	//~ //setss the bytes
	//~ for(int i=3;i>holder;i--)
	//~ {
		//~ mask = mask & ~((~lst[12])<<(7*i));	
	//~ }
	
	//~ if(sign)
	//~ {
		//~ mask=mask | (lst[13]<<(7*(holder+1)));
	//~ }
	//~ if(temp.temp_mode==1)
	//~ {
	//~ mask=mask | (0b0001<<28);
	//~ }
	//~ if(temp.temp_mode==2)
	//~ {
	//~ mask=mask | (0b0010<<28);
	//~ }
	
	//~ *display=mask;
	
	//~ return 0;
	//~ }
		
	
	
	
		
	
	
	

