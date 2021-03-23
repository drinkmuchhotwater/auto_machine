#include<stdio.h>
#include<math.h>
#include<stdlib.h>
struct OPND{
	double number;
	struct OPND * next;
};
struct OPTR{
	char operate;
	struct OPTR * next;
};
struct OPND * init_num(void);//初始化 
struct OPTR * init_ope(void);
void push_num(struct OPND*,double);//存储操作数 
void push_ope(struct OPTR*,char);//存储操作符 
double pop_num(struct OPND*);//弹出数字栈顶元素 
char pop_ope(struct OPTR*);//弹出操作符栈顶元素（不负责计算） 
void read(struct OPND *,struct OPTR *);
double operate(double,double,char);//前两个为数据，第三个为操作数
int compare(char,char);
int main(void)
{
	double result=0;
	struct OPND	* num=init_num();
	struct OPTR * ope=init_ope();
	read(num,ope);
	result=pop_num(num);
	printf("%lf",result);
	return 0; 
}
void read(struct OPND* NUM,struct OPTR * OPE)
{
	int loc=0,decide=0,i=0;
	double temp,data_1,data_2,num_ex;
	char equal[100];
	char input,input_prev,ope_top,ptr_prev;
	char *ptr,*orign;
	scanf("%s",&equal);
	orign=&equal[0];
	for(ptr=&equal[0];!loc;ptr++)
	{
		if(*ptr>='0'&&*ptr<='9') //如果是数字 
		{
			ptr_prev=*ptr;
			ptr++;
			if(*ptr>'9'||*ptr<'0'&&*ptr!='.')
			{
				num_ex=(double)(ptr_prev-'0');
				temp=num_ex;
			}
			else 
			{
				for(num_ex=ptr_prev-'0';1;ptr++)
				{
					if(*ptr=='.')
					{
						ptr++;
						for(i=1;1;i++)
						{
							if(*ptr<'0'||*ptr>'9')
								break;
							temp=(double)(*ptr-'0');
							num_ex=num_ex+temp*pow(0.1,i);
							ptr++;
						}
						break;
					}
					else if(*ptr<='9'&&*ptr>='0')
					{
						num_ex=num_ex*10+*ptr-'0';
					}
					else
					{ 
						break;
					}
				}
				temp=num_ex;
			}
			push_num(NUM,temp);
			ptr--;
		}
		else//如果是运算符
		{
			if(*ptr=='s')
			{
				ptr+=2;
				*ptr='S';
			}
			else if(*ptr=='c')
			{
				ptr+=2;
				*ptr='C';
			}
			else if(*ptr=='l')
			{
				ptr++;
				if(*ptr=='o')
				{
					ptr++;
					*ptr='L';
				}
				else
				{
					ptr++;
					*ptr='N';
				}
			}
			while(1)//做死循环一直比较直到优先级大于 
			{
				decide=compare(OPE->operate,*ptr);
				if(decide<=0||*ptr=='=')
				{
					ope_top=pop_ope(OPE);
					if(ope_top=='=')
					{
						if(*ptr=='=')
						{
							loc=1;
							break;
						}
						else
						{
							push_ope(OPE,'=');
							push_ope(OPE,*ptr);
							break;
						}
					}
					else if(ope_top=='+'||ope_top=='-'||ope_top=='*'||ope_top=='/'||ope_top=='^')//如果是双目运算符 
					{
						data_2=pop_num(NUM);
						data_1=pop_num(NUM);
						temp=operate(data_1,data_2,ope_top);
						push_num(NUM,temp);
					}
					else//如果是单目运算符 
					{
						data_1=pop_num(NUM);
						temp=operate(data_1,0,ope_top);
						push_num(NUM,temp);
					}
				}
				else
				{
					push_ope(OPE,*ptr);
					break;
				}
			}
		}
	}
}
struct OPND * init_num(void)
{
	struct OPND * head=NULL;
	head=(struct OPND *)malloc(sizeof(struct OPND));
	head->number=-1;
	head->next=NULL;
	return head;
}
struct OPTR * init_ope(void)
{
	struct OPTR * head=NULL,*curr;
	head=(struct OPTR *)malloc(sizeof(struct OPTR));
	curr=(struct OPTR *)malloc(sizeof(struct OPTR));
	head->operate='0';
	head->next=curr;
	curr->operate='=';//将=填充如操作符栈中 
	curr->next=NULL;
	return head;
}
void push_num(struct OPND *num,double temp)
{
	struct OPND* curr_num,*prev_num;
	for(prev_num=num;prev_num->next!=NULL;prev_num=prev_num->next)
		;
	curr_num=(struct OPND*)malloc(sizeof(struct OPND));
	prev_num->next=curr_num;
	curr_num->number=temp;
	curr_num->next=NULL;
}
void push_ope(struct OPTR*ope,char ptr)
{
	struct OPTR* curr_ope,*prev_ope;
	for(prev_ope=ope;prev_ope->next!=NULL;prev_ope=prev_ope->next)
		;
	curr_ope=(struct OPTR*)malloc(sizeof(struct OPTR));
	prev_ope->next=curr_ope;
	curr_ope->operate=ptr;
	curr_ope->next=NULL;
}
double pop_num(struct OPND * head_num)
{
	double temp_pop_num;
	struct OPND* curr,*prev;
	for(prev=head_num;prev->next->next!=NULL;prev=prev->next)有 
		;
	curr=prev->next;
	temp_pop_num=curr->number;
	prev->next=NULL;
	free(curr);
	return temp_pop_num;
}
char pop_ope(struct OPTR* head_ope)
{
	char temp_pop_ope;
	struct OPTR* curr,* prev;
	for(prev=head_ope;prev->next->next!=NULL;prev=prev->next)
		;
	curr=prev->next;
	temp_pop_ope=curr->operate;
	prev->next=NULL;
	free(curr);
	return temp_pop_ope;
}
double operate(double data_1,double data_2,char operate)
{
	int data_A,data_B,result_op=1;
	data_A=(int)data_1;
	data_B=(int)data_2;
	switch(operate)
	{
		case '+':
			return data_1+data_2;break;
		case '-':
			return data_1-data_2;break;
		case '*':
			return data_1*data_2;break;
		case '/':
			return data_1/data_2;break;
		case '^':
			return pow(data_A,data_B);break;
		case 'S':
			return sin(data_1*3.1415926535/180);break;
		case 'C':
			return cos(data_1*3.1415926535/180);break;
		case 'G':
			return log(data_1)/log(10);	break;
		case 'N':
			return log(data_1);	break;
		case '!':
			{
				for(;data_A!=1;data_A--)
					result_op*=data_A;
				return result_op;	
			}
			break;
	}
}
int compare(char top,char read)
{
	char temp_char;
	int i,prio_top,prio_read,temp_int;
	for(i=1;i>=0;i--)
	{
		if(i==1)
			temp_char=top;
		else
			temp_char=read;
		switch(temp_char)
		{
			case ')':
				temp_int=0;	break;
			case '=':
				temp_int=0;	break;
			case '+':
				temp_int=1;	break;
			case '-':
				temp_int=1;	break;
			case '*':
				temp_int=2;	break;
			case '/':
				temp_int=2;	break;
			case '^':
				temp_int=3;	break;
			case 'S':
				temp_int=4;	break;
			case 'C':
				temp_int=4;	break;
			case 'G':
				temp_int=4;	break;
			case 'N':
				temp_int=4;	break;
			case '!':
				temp_int=5;	break;
			case '(':
				{
					if(i==1)
						temp_int=0;
					else
						temp_int=6;
				}
				break;
		}
		if(i==1)
			prio_top=temp_int;
		else
			prio_read=temp_int;
	}
	if(prio_top<prio_read)
		return 1;
	else if(prio_top==prio_read)
		return 0;
	else
		return -1;
}
