#Program 3: Write a program for Hamming code generation for error detection and correction.

#include <stdio.h>
#include <math.h>

int input[32]; // global declaration
int code[32];

int ham_calc(int, int); // function to calculate the hamming code

void main() {
	int n, i, p_n = 0, c_l, j, k;

	printf("Please enter the length of the Data Word: ");
	scanf("%d", &n);

	printf("Please enter the Data word:\n");
	for (i = 0; i < n; i++) {
    	scanf("%d", &input[i]);
	}

	i = 0;
	while (n > (int)pow(2, i) - (i + 1)) { // used to calculate how many parity bits are required
    	p_n++;
    	i++;
	}

	c_l = p_n + n;
	j = k = 0;
	for (i = 0; i < c_l; i++) {
    	if (i == ((int)pow(2, k) - 1)) {
        	code[i] = 0;
        	k++;
    	} else {
        	code[i] = input[j];
        	J++;
    	}
	}

	for (i = 0; i < p_n; i++) {
    	int position = (int)pow(2, i);
    	int value = ham_calc(position, c_l);
    	code[position - 1] = value;
	}

	printf("\nThe calculated Code word is: ");
	for (i = 0; i < c_l; i++) {
    	printf("%d", code[i]);
	}

	printf("\nPlease enter the received Codeword:\n");
	for (i = 0; i < c_l; i++) {
    	scanf("%d", &code[i]);
	}

	int error_pos = 0;
	for (i = 0; i < p_n; i++) {
    	int position = (int)pow(2, i);
    	int value = ham_calc(position, c_l);
    	if (value != 0)
        	error_pos += position;
	}

	if (error_pos == 0)
    		printf("The received Code Word is correct.\n");
	else
    		printf("Error at bit position: %d\n", error_pos);
}

int ham_calc(int position, int c_l) {
	int count = 0, i, j;
	i = position - 1;
	while (i < c_l) {
    	for (j = i; j < i + position; j++) {
        	if (code[j] == 1)
            	count++;
    	}
    		i = i + 2 * position;
	}

	if (count % 2 == 0)
    		return 0;
	else
    		return 1;
}
