#include "div.h"

int get_bit(int data)
{
    int i,j = 0;
    for(i = 0;i<32;i++)
    {
        if(!data)return j;
        else j++;
        data = data >> 1;
    }
    return 1;
}
unsigned char  get_bit_Value(int data,int cnt)
{
    if(data & (1 << cnt))return 1;
    else return 0;
}
//四舍五入
int my_div(int data,int divnum)
{
    int m ,n,i,res_data = 0,temp = 0;
    m = get_bit(data);
    n = get_bit(divnum);
    if(m<n)return 0;
    temp = data >> (m-n);
    for(i = m-n+1;i >0;i--)
    {
        res_data = res_data << 1;
        if(temp>=divnum)
        {
            res_data += 1;
            temp = temp - divnum;
            temp = temp << 1;
            temp = temp + get_bit_Value(data,i-2);
        }
        else
        {
            temp = temp << 1;
            temp = temp + get_bit_Value(data,i-2);
        }
    }
    if(temp>=divnum)res_data++;
    return res_data;
}
//省去小数
int my_div_f(int data,int divnum)
{
    int m ,n,i,res_data = 0,temp = 0;
    m = get_bit(data);
    n = get_bit(divnum);
    if(m<n)return 0;
    temp = data >> (m-n);
    for(i = m-n+1;i >0;i--)
    {
        res_data = res_data << 1;
        if(temp>=divnum)
        {
            res_data += 1;
            temp = temp - divnum;
            temp = temp << 1;
            temp = temp + get_bit_Value(data,i-2);
        }
        else
        {
            temp = temp << 1;
            temp = temp + get_bit_Value(data,i-2);
        }
    }
    return res_data;
}
//求众数
unsigned short int get_own_pwm(unsigned short int *addr_reg,unsigned int SIZE)
{
    unsigned char i,j,min,re_num  = 1,num_cnt = 1;
    unsigned short int addr1;
    unsigned short int *temp_reg;
    temp_reg = (unsigned short int *)0x10001000;
    for(i = 0;i < SIZE;i++)
    {
        temp_reg[i] = addr_reg[i];
    }
    min = temp_reg[0];
    for(i = 0;i < SIZE;i++)//冒泡排序
    {
        for(j = 0;j < SIZE-1 - i;j++)
        {
            if(temp_reg[j] < temp_reg[j + 1])//小的交换至后端
            {
                min = temp_reg[j];
                temp_reg[j] = temp_reg[j + 1];
                temp_reg[j + 1] = min;
            }
        }
    }
    //my_printf("")
    addr1 = temp_reg[0];
    for(i = 0;i < SIZE; i++)//查找重复最多的地址值
    {
        if(temp_reg[i] == temp_reg[i + 1])
        {
            num_cnt ++ ;
        }
        else
        {
            if(num_cnt > re_num)
            {
                re_num = num_cnt;
                addr1 = temp_reg[i];//重复最多的地址值
            }
            num_cnt = 1;
        }
    return addr1;
    }
    return 0;
}



