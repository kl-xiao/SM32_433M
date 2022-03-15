#include "main.h"

uint8_t rf_data[4];
extern uint8_t decode_ok;    //解码成功标志位

int main()
{
    uart_init(115200);
    SM1642_Init();
    RF433M_Init();
    ZERO_Init();

    printf("start\r\n");
    while (1)
    {  
        if(decode_ok == 1)   //解码成功
		{
			switch(rf_data[2])
			{
				case ALL_ON:

					break;
				case ALL_OFF:

					break;
				case LIGHT:

					break;
				case DARK:

					break;
				case WARM:

					break;
				case COLD:

					break;
				case SW1_ON:

					break;
				case SW1_OFF:

					break;	
				case SW2_ON:

					break;
				case SW2_OFF:

					break;				
				case SW3_ON:

					break;
				case SW3_OFF:

					break;
				case SW4_ON:

					break;
				case SW4_OFF:

					break;
				default:
					break;
			}

			decode_ok = 0;
#if PRINT
			printf("rf_data[0] = %x\r\n", rf_data[0]);
			printf("rf_data[1] = %x\r\n", rf_data[1]);
			printf("rf_data[2] = %x\r\n", rf_data[2]);
			printf("\r\n");
#endif
		}
        SM1642_Shownum(2333);
    }
}
