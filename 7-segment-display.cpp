//Lab 5 - assessed lab - Peter Morrow - 40204698
//This programme controls a 7-segment display
// With 2 push buttons / OR reading from putty
//2 Mode hardware - start up mode - serial mode
// star up mode = displays letters 'HELLO' in order 
// Letters A - G in Hex

#include "mbed.h"

//Global Variable 
BusOut LED_Disp(p7, p11, p9, p8, p5, p6, p10, p12);

DigitalIn Slider_1(p17);
DigitalIn Slider_2(p18);
DigitalOut led1(LED1); // Debugging LED
InterruptIn button_1(p14); // Allocate interrupt input on pin 14

DigitalOut Key_4(p26); //Pin 4 of keypad
DigitalOut Key_2(p28); //Pin 2 of keypad
DigitalOut Key_6(p24); //Pin 6 of keypad

DigitalIn Key_3(p27); //Pin 3 of keypad
DigitalIn Key_8(p22); //Pin 8 of keypad
DigitalIn Key_7(p23); //Pin 7 of keypad
DigitalIn Key_5(p25); //Pin 5 of keypad

unsigned char counter = 0; //Make Global Variable 
unsigned int Mode = 0; //Make Global Variable - 0 = Start up mode 

//Function Prototype 
void DisplayNum(int);

void Flash_char();

char check_keypad(void);

void Serial_isr();



Serial pc(USBTX, USBRX); // Declare serial comms object

int Num_0 = ~0x3F;
int Num_1 = ~0x06;
int Num_2 = ~0x5B;
int Num_3 = ~0x4F;
int Num_4 = ~0x66;
int Num_5 = ~0x6D;
int Num_6 = ~0x7D;
int Num_7 = ~0x07;
int Num_8 = ~0x7F;
int Num_9 = ~0x6F;

int Letter_A = ~0x77; // ~1110111
int Letter_B = ~0x7F; // ~1111111
int Letter_C = ~0x39; // ~0111001
int Letter_D = ~0x3F; // ~0111111
int Letter_E = ~0x79; // ~1111001
int Letter_F = ~0x71; // ~1110001
int Letter_G = ~0x7D; // ~1111101
int Letter_H = ~0x76;
int Letter_L = ~0x38;
int Letter_S = ~0x6D;
int Letter_O = ~0x3F; // ~0111111

int Seg_Off = ~0000000;

//***********************************************************************
// ISR1 - Function to swicth operating modes 
void Serial_isr(){
    
    if (Mode == 0){ //The mode is changed to 1, if in state 0
        
        Mode = 1; //Serial Comms mode
        }   
    else if (Mode == 1){ //The mode is changed to 0, if in state 1
        
        Mode = 0; //Start up Mode
        }
    }

//***********************************************************************


int main() {
    
    button_1.rise(&Serial_isr);
    
    int counter2; // Declare counter 2 variable as int
    int Prev_counter; // Declare previous counter variable as int
    int Prev_counter2; // Declare previous counter 2 variable as int
    int Prev_counter3; // Declare previous counter 3 variable as int
    
    while(1) {
        
        if (Mode == 0){ //If in start up mode (no button press)
        
        Flash_char();
        
        wait(0.6);
        
     
        }  
        
        if (Mode == 1){ //If in Serial Comms mode (no button press)
            
            DisplayNum(5); //Call function to display correct Character - S
            
            counter = check_keypad();
                    

            if (counter == 'Z'){
                wait(0.5);
                }
                
            else if (counter == 'S'){
                
                
                Prev_counter2 = Prev_counter - 48; //to show dec number
                
                pc.printf("ASCII code for char %d, = %d Dec ", Prev_counter2, Prev_counter);

                
                wait(0.5);
                }
 
            else if (counter == 'H'){
                
                Prev_counter2 = Prev_counter - 48; //to show dec number
                
                Prev_counter3 = Prev_counter - 30;
                
                pc.printf(" ASCII code for char %d, = %d Hex ", Prev_counter2, Prev_counter3);
                
                wait(0.5);
                }
 
 
            else {
                
                Prev_counter = counter;
                
                counter2 = counter - 48; //converts to decimal 
                
                pc.printf("%d\n\r", counter2);
                
                wait(0.5); //debounce timer 
                
                }
        
     
        } 
        


        
    }

}

//****************Functions***************************************************


//Displays Characters 'HELLO' in order 
void Flash_char(){
    
    DisplayNum(0); //Call function to display correct Character - H
    
    wait(0.6); //Display character for 0.6 secs
    
    DisplayNum(6); //Call function to display correct Character - Seg Off
    
    wait(0.1);
    
    DisplayNum(1); //Call function to display correct Character - E
    
    wait(0.6); //Display character for 0.6 secs
    
    DisplayNum(6); //Call function to display correct Character - Seg Off
    
    wait(0.1);
    
    DisplayNum(2); //Call function to display correct Character - L
    
    wait(0.6); //Display character for 0.6 secs
    
    DisplayNum(6); //Call function to display correct Character - Seg Off
    
    wait(0.1);
    
    DisplayNum(3); //Call function to display correct Character - L
    
    wait(0.6); //Display character for 0.6 secs
    
    DisplayNum(6); //Call function to display correct Character - Seg Off
    
    wait(0.1);
    
    DisplayNum(4); //Call function to display correct Character - O
    
    wait(0.6); //Display character for 0.6 secs
    
    DisplayNum(6); //Call function to display correct Character - Seg Off
    
    wait(0.1);
    
  
  }
  
  
char check_keypad(void){
    
    Key_4 = 1; //pulling collumn one high 
    Key_2 = 0;
    Key_6 = 0;
        if (Key_3 == 1) // Check if Pin 3 is pressed
        {
            return('1'); 
            }
            else if (Key_8 == 1) // Check if Pin 3 is pressed
        {
            return('4'); 
            }
            else if (Key_7 == 1) // Check if Pin 3 is pressed
        {
            return('7'); 
            }
            else if (Key_5 == 1) // Check if Pin 3 is pressed
        {
            return('S'); 
            }
            
            
    Key_4 = 0; //pulling collumn two high 
    Key_2 = 1;
    Key_6 = 0;
        if (Key_3 == 1) // Check if Pin 3 is pressed
        {
            return('2'); 
            }
            else if (Key_8 == 1) // Check if Pin 3 is pressed
        {
            return('5'); 
            }
            else if (Key_7 == 1) // Check if Pin 3 is pressed
        {
            return('8'); 
            }
            else if (Key_5 == 1) // Check if Pin 3 is pressed
        {
            return('0'); 
            }
    
    
    Key_4 = 0; //pulling collumn three high 
    Key_2 = 0;
    Key_6 = 1;
        if (Key_3 == 1) // Check if Pin 3 is pressed
        {
            return('3'); 
            }
            else if (Key_8 == 1) // Check if Pin 3 is pressed
        {
            return('6'); 
            }
            else if (Key_7 == 1) // Check if Pin 3 is pressed
        {
            return('9'); 
            }
            else if (Key_5 == 1) // Check if Pin 3 is pressed
        {
            return('H'); 
            }
            
            
            
            
        else{
            return('Z');
            }
    
    }
    
    
    
 void DisplayNum(int num){   
    switch(num)
    {
        
        case 0:
        LED_Disp = Letter_H;
        break;
        
        case 1:
        LED_Disp = Letter_E;
        break;
        
        case 2:
        LED_Disp = Letter_L;
        break;
        
        case 3:
        LED_Disp = Letter_L;
        break;
        
        case 4:
        LED_Disp = Letter_O;
        break;
        
        case 5:
        LED_Disp = Letter_S;
        break; 
        
        case 6:
        LED_Disp = Seg_Off;
        break; 
        
        }
    
    }