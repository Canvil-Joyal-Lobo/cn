//PRG 3:-Write a program for Hamming code generation for error detection and correction.

#include <stdio.h>
#include <math.h>
void calculate_parity_bits(int data[], int hamming_code[]) {
    hamming_code[0] = data[0] ^ data[1] ^ data[3];
    hamming_code[1] = data[0] ^ data[2] ^ data[3];
    hamming_code[3] = data[1] ^ data[2] ^ data[3];
}
void generate_hamming_code(int data[]) {
    int hamming_code[7] = {0}; 
    hamming_code[2] = data[0]; 
    hamming_code[4] = data[1]; 
    hamming_code[5] = data[2]; 
    hamming_code[6] = data[3]; 
    calculate_parity_bits(data, hamming_code);
    printf("Generated Hamming Code : ");
    for (int i = 0; i < 7; i++) {
        printf("%d", hamming_code[i]);
    }
    printf("\n");
}
void check_and_correct_hamming_code(int received[]) {
    int parity_check[3] = {0}; 
    parity_check[0] = received[0] ^ received[2] ^ received[4] ^ received[6]; // P1 check
    parity_check[1] = received[1] ^ received[2] ^ received[5] ^ received[6]; // P2 check
    parity_check[2] = received[3] ^ received[4] ^ received[5] ^ received[6]; // P3 check
    int error_position = parity_check[0] * 1 + parity_check[1] * 2 + parity_check[2] * 4;
    if (error_position == 0) {
        printf("No error detected.\n");
    } else {
        printf("Error detected at position: %d\n", error_position);
        printf("Corrected Hamming Code: ");
        received[error_position - 1] = !received[error_position - 1]; // Flip the incorrect bit
        for (int i = 0; i < 7; i++) {
            printf("%d", received[i]);
        }
        printf("\n");
    }
}
int main() {
    int data[4]; 
    // Input 4 data bits
    printf("Enter 4 data bits : ");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &data[i]);
    }
    generate_hamming_code(data);
    int received[7];
    printf("Enter the received 7-bit Hamming code : ");
    for (int i = 0; i < 7; i++) {
        scanf("%d", &received[i]);
    }
    check_and_correct_hamming_code(received);
    return 0;
}


///////////////////////////////////////////

//3. Write a program for Hamming code generation for error detection and correction.

#include<stdio.h>
#include<math.h>
int input[5];int messege[20];
int ham_calc(int,int);
void main()
{
	int n,i,par_bits=0;
	printf("Enter the length of messege");
	scanf("%d",&n);
	printf("Enter the Message in bits");
	for(i=0;i<n;i++)
	{
		scanf("%d",&input[i]);
	}
//redundant bits to add
i=1;
while(pow(2,i)<=n+i+1)
{
	i++;
	par_bits++;
}
int tot_bits=par_bits+n;
printf("\n total number of bits:%d\n",tot_bits);
//positioning parity
int j=0,k=0;
for(i=0;i<tot_bits;i++)
{
	if(i==((int)pow(2,k)-1))
	{
		messege[i]=0;
		k++;
	}
	else
	{
		messege[i]=input[j];
		j++;
	}
}

for(i=0;i<tot_bits;i++)
{
	printf("Initialized value%d\t",messege[i]);
}
//updating the parity value
for(i=0;i<par_bits;i++)
{
	int position = (int)pow(2,i);
	int value = ham_calc(position,tot_bits);
	messege[position-1]=value;
}
printf("\nThe calculated Code Word is: ");
for(i=0;i<tot_bits;i++)
	printf("%d",messege[i]);
	printf("\n");
	printf("Please enter the received Code Word:\n");
for(i=0;i<tot_bits;i++)
	scanf("%d",&messege[i]);
int error_pos = 0;
for(i=0;i<par_bits;i++)
{
	int position = (int)pow(2,i);
	int value = ham_calc(position,tot_bits);
	if(value != 0)
		error_pos+=position;
}
if(error_pos == 1)
	printf("The received Code Word is correct.\n");
else
	printf("Error at bit position: %d\n",error_pos);
}
int ham_calc(int position,int tot_bits)
{
	int count=0,i,j;
	i=position-1;
	while(i<tot_bits)
	{
		for(j=i;j<i+position;j++)
		{
			if(messege[j] == 1)
			count++;
		}
		i=i+2*position;
	}
	if(count%2 == 0)
		return 0;
	else
		return 1;
}


