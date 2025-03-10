 //PRG 1:-write a c program distance vector algorithm to find suitable path for transmission//

#include <stdio.h>
#include <limits.h>

struct Node {
    int cost[10];
    int nextHop[10];
};

void dist(int n, struct Node nodes[]) {
    int updated;
    
    do {
        updated = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    for (int k = 0; k < n; k++) {
                        if (k != i && nodes[i].cost[k] != INT_MAX && nodes[k].cost[j] != INT_MAX) {
                            int newCost = nodes[i].cost[k] + nodes[k].cost[j];
                            if (newCost < nodes[i].cost[j]) {
                                nodes[i].cost[j] = newCost;
                                nodes[i].nextHop[j] = k;
                                updated = 1;
                            }
                        }
                    }
                }
            }
        }
    } while (updated);
}

int main() {
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    struct Node nodes[n];

    printf("Enter the cost matrix for each node:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &nodes[i].cost[j]);
            if (i != j && nodes[i].cost[j] == 0) {
                nodes[i].cost[j] = INT_MAX;
            }
            nodes[i].nextHop[j] = j;
        }
    }

    dist(n, nodes);

    for (int i = 0; i < n; i++) {
        printf("\nRouting table for node %c:\n", i + 65);
        printf("-----------------------------------------\n");
        printf("Dest\tCost\tNext Hop\n");
        printf("-----------------------------------------\n");
        for (int j = 0; j < n; j++) {
            if (i != j) {
                printf("%c\t", j + 65);
                if (nodes[i].cost[j] == INT_MAX) {
                    printf("INF\t");
                } else {
                    printf("%d\t", nodes[i].cost[j]);
                }
                printf("%c\n", nodes[i].nextHop[j] + 65);
            }
        }
    }

    return 0;
}




///////////////////////////////////////

//MAM :- 1.Write a program for a distance vector algorithm to find a suitable path for transmission.

#include<stdio.h>
void dist_vector(int n);
void init(int n);

//creating structure node
struct node
{
	unsigned int dist[20],nexthop[20];
}route[10];

int i,j;
//main function
void main()
{
	int n,i,j;
	printf("Enter the number of router");
	scanf("%d",&n);
	init(n);
	
	printf("Enter the cost matrix(999 no link)\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&route[i].dist[j]);
	dist_vector(n);
	printf("\n------------------------------------");
	printf("\nupdated distance vector table\n");
	printf("--------------------------------------\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",route[i].dist[j]);
			
		}	
	printf("\n");
	}	
	printf("\n----------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("\nRouting table for node %c table\n",65+i);
		printf("-------------------------\n");
		printf("desti\t Cost\t Next hop\n");
		printf("--------------------------\n");
		for(int j=0;j<n;j++)
		if(i!=j)
			printf("%c\t%d\t%c\n",65+j,route[i].dist[j],65+route[i].nexthop[j]);
	}
}

//initialization
void init(int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{ for(j=0;j<n;j++)
	
	 { if(i!=j)
		{
		route[i].dist[j]=999;
		route[i].nexthop[j]=-20;
		}
	route[i].dist[i]=0;
	route[i].nexthop[j]=-20;
	 }
	}
}

void dist_vector(int n)
{
int count;
do {
count = 0;
for (int i = 0; i < n; i++)
{
for (int j = 0; j < n; j++)
{
for (int k = 0; k < n; k++)
{
if ((route[i].dist[j]) > (route[i].dist[k] + route[k].dist[j]))
{
route[i].dist[j] = route[i].dist[k] + route[k].dist[j];
route[i].nexthop[j] = k;
count = 1;
}
}
}
}
} while (flag);
}


////////////////////////

//correct

#include<stdio.h>

void dist_vector(int n);
void init(int n);

struct node {
    unsigned int dist[20], nexthop[20];
} route[10];

int i, j;

void main() {
    int n;
    printf("Enter the number of routers: ");
    scanf("%d", &n);
    init(n);

    printf("Enter the cost matrix (999 represents no link):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &route[i].dist[j]);
        }
    }

    dist_vector(n);

    printf("\n------------------------------------\n");
    printf("Updated distance vector table\n");
    printf("--------------------------------------\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d\t", route[i].dist[j]);
        }
        printf("\n");
    }

    printf("\n----------------------------\n");
    for (i = 0; i < n; i++) {
        printf("\nRouting table for node %c\n", 65 + i);
        printf("-------------------------\n");
        printf("Destination\tCost\tNext hop\n");
        printf("--------------------------\n");
        for (int j = 0; j < n; j++) {
            if (i != j) {
                printf("%c\t\t%d\t%c\n", 65 + j, route[i].dist[j], 65 + route[i].nexthop[j]);
            }
        }
    }
}

void init(int n) {
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                route[i].dist[j] = 999;
                route[i].nexthop[j] = -1;
            }
        }
        route[i].dist[i] = 0;
        route[i].nexthop[i] = i;
    }
}

void dist_vector(int n) {
    int count;
    do {
        count = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if ((route[i].dist[j]) > (route[i].dist[k] + route[k].dist[j])) {
                        route[i].dist[j] = route[i].dist[k] + route[k].dist[j];
                        route[i].nexthop[j] = k;
                        count = 1;
                    }
                }
            }
        }
    } while (count);
}
