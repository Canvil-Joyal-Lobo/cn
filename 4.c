//4. Write a program for congestion control using leaky bucket algorithm.

#include<stdio.h>
void main()
{
int i, n,buck_size=0,packets[10],rate=0,remai_pack=0,recv=0,sent;
printf("Enter the number of packets");
scanf("%d",&n);
printf("enter the value of packets");
for(i=0;i<n;i++)
{
	
	scanf("%d",&packets[i]);
	
}
printf("Enter the bucket_size");
scanf("%d",&buck_size);
printf("Enter the rate of transmission");
scanf("%d",&rate);
printf("\n----------------------------------------------------------------------------------------------\n");
printf("index\t packet size \t\t accept \tsent\tremaining\n");
printf("\n----------------------------------------------------------------------------------------------\n");
for(i=0;i<n;i++)
{
	if(packets[i]==0)
	{
	recv=-1;
	sent=0;
	}else{
		if(remai_pack+packets[i]>buck_size)
		recv=-1;
		else
		{
		recv=packets[i];
		remai_pack+=packets[i];
		}
		if(remai_pack!=0)
		{
			if(remai_pack<rate)
			{
				sent=remai_pack;
				remai_pack=0;
			}
			else
			{
				sent=rate;
				remai_pack=remai_pack-rate;
			}
		}
		else
		sent=0;
		}
		if(recv==-1)
		
			printf("\n%d\t\t%d\t\t%s\t\t%d\t\t%d",i,packets[i],"dropped",sent,remai_pack);
		else
			printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,packets[i],recv,sent,remai_pack);
}
}


/////////////////////////////////////////////////////



#include<stdio.h>
void main()
{
int i, n,buck_size=0,packets[10],rate=0,remai_pack=0,recv=0,sent;
printf("Enter the number of packets");
scanf("%d",&n);
printf("enter the value of packets");
for(i=0;i<n;i++)
{
	
	scanf("%d",&packets[i]);
	
}
printf("Enter the bucket_size");
scanf("%d",&buck_size);
printf("Enter the rate of transmission");
scanf("%d",&rate);
printf("\n----------------------------------------------------------------------------------------------\n");
printf("index\t packet size \t\t accept \tsent\tremaining\n");
printf("\n----------------------------------------------------------------------------------------------\n");
for(i=0;i<n;i++)
{
	if(packets[i]==0)
	{
	recv=-1;
	sent=0;
	}else{
		if(remai_pack+packets[i]>buck_size)
		recv=-1;
		else
		{
		recv=packets[i];
		remai_pack+=packets[i];
		}
		if(remai_pack!=0)
		{
			if(remai_pack<rate)
			{
				sent=remai_pack;
				remai_pack=0;
			}
			else
			{
				sent=rate;
				remai_pack=remai_pack-rate;
			}
		}
		else
		sent=0;
		}
		if(recv==-1)
		
			printf("\n%d\t\t%d\t\t%s\t\t%d\t\t%d",i,packets[i],"dropped",sent,remai_pack);
		else
			printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,packets[i],recv,sent,remai_pack);
}
}
