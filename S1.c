#Program 1:Write a program for a distance vector algorithm to find a suitable path for transmission.
#include<stdio.h>
struct node
{
	unsigned int dist[20], nexthop[20];
} route[10];

void init(int n);
void dist_vector(int n);

int i, j;

void main()
{
	int n;
	printf("Enter the number of routers: ");
	scanf("%d", &n);
    
	init(n);
    
	printf("Enter the cost matrix (999 for no link):\n");
	for (i=0; i<n; i++)
    	for (j=0; j<n; j++)
        	scanf("%d", &route[i].dist[j]);
    
	dist_vector(n);
    
	printf("----------------------\n");
	printf("Updated Distance Vector Table\n");
	printf("----------------------\n");
	for (i=0; i<n; i++)
	{
    		for (j=0; j<n; j++)
    		{
        			printf("%d\t", route[i].dist[j]);
    		}
    		printf("\n");
	}
    
	printf("\nRouting Tables:\n");
	for (i=0; i<n; i++)
	{
    		printf("\nRouting table for node %c\n", 65 + i);
    		printf("---------------------\n");
    		printf("Dest\tCost\tNext Hop\n");
    		printf("---------------------\n");
    		for (j=0; j<n; j++)
    		{
        			if (i != j)
        			{
            			printf("%c\t%d\t%c\n", 65 + j, route[i].dist[j], 65 + route[i].nexthop[j]);
        			}
    		}
	}
}

// Initialization
void init(int n)
{
	int i, j;
	for (i=0; i<n; i++)
	{
    	for (j=0; j<n; j++)
    	{
        			if (i!=j)
        			{
            			route[i].dist[j] = 999;
            			route[i].nexthop[j] = -1;
        			}
    		}
    		route[i].dist[i] = 0;
	}
}

// Distance Vector Algorithm
void dist_vector(int n)
{
	int count, k;
	do
	{
    		count=0;
    		for (i=0; i<n; i++)
    		{
        			for (j=0; j<n; j++)
        			{
            			for (k=0; k<n; k++)
            			{
                				if (route[i].dist[j] > route[i].dist[k] + route[k].dist[j])
                				{
                    					route[i].dist[j] = route[i].dist[k] + route[k].dist[j];
                    					route[i].nexthop[j] = k;
                    					count = 1;
                				}
            			}
        			}
    		}
	} while (count);
}
