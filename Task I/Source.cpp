#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>


int topInfix = -1;
int topPostfix = -1;

char stackInfix[50];
int stackPostfix[50];

char postfix[200];

void pushInfix(char);
void pushPostfix(int);
char popInfix();
int popPostfix();

int precedence(char symbol){

	char ch;
	ch = symbol;
	if (ch == '^')
		return 3;
	else if (ch == '/' || ch == '*')
		return 2;
	else if (ch == '+' || ch == '-')
		return 1;
	else
		return 0;

}

int power(int base, int index){

	int res = 1;
	int i = 0;

	for (i = 0; i < index; i++)
		res *= base;

	return res;


}
int PostfixEval(char* postfix){

	char ch;
	int op2, op1;
	int i = 0;
	int multiplier = 1;

	if (postfix[i] == '-')
	{
		multiplier = -1;
		i++;
	}
	while (postfix[i] != '\0'){


		ch = postfix[i];

		if (ch == ' '&&postfix[i + 1] == '-')
		{
			multiplier = -1;
			i++;
		}

		if (ch == ' '){

			i++;
			continue;
		}

		if (isdigit(ch)){

			int number = ch - '0';
			i++;
			while (isdigit(postfix[i]) && postfix[i] != ' '){

				ch = postfix[i];
				number = number * 10 + (ch - '0');
				i++;
			}

			number = number*multiplier;
			multiplier = 1;
			pushPostfix(number);
			continue;
		}

		else{

			op1 = popPostfix();
			op2 = popPostfix();

			switch (ch){

			case '+':
				pushPostfix(op2 + op1);
				break;
			case '-':

				pushPostfix(op2 - op1);
				break;
			case '*':
				pushPostfix(op2*op1);
				break;
			case '/':
				pushPostfix(op2 / op1);
				break;
			case '^':
				printf("\n%d  %d\n", op1, op2);

				pushPostfix((int)pow(op2*1.0, op1));
				break;
			default:
				printf("\nWhat the operator?");
			}

		}
		i++;
	}
	printf("result is    %d", stackPostfix[topPostfix]);
	return stackPostfix[topPostfix];
}


int infixToPostfix(char* infix){

	char symbol;
	int finalResult = 0;
	int i = 0;
	int j = 0;
	bool flag = false;

	if (infix[i] == '-')
	{
		postfix[j++] = infix[i];
		i++;
	}
	while (infix[i] != '\0'){

		char temp;

		symbol = infix[i];
		char nextsymbol = infix[i + 1];
		char presymbol = infix[i - 1];

		if (symbol == '-'&&i - 1 >= 0 && (presymbol == '+' || presymbol == '-' || presymbol == '*' || presymbol == '/'))
		{

			postfix[j] = symbol;
			j++;
			i += 1;
		}
		else
		{

			switch (symbol){

			case '+':

				if (flag == true){
					postfix[j] = ' ';
					j++;
				}

				flag = false;
				while (topInfix != -1 && precedence(symbol) <= precedence(stackInfix[topInfix])){

					temp = popInfix();
					postfix[j] = temp;
					j++;
				}
				pushInfix(symbol);
				break;

			case '/':

				if (flag == true){
					postfix[j] = ' ';
					j++;
				}

				flag = false;
				while (topInfix != -1 && precedence(symbol) <= precedence(stackInfix[topInfix])){

					temp = popInfix();
					postfix[j] = temp;
					j++;
				}
				pushInfix(symbol);
				break;

			case '-':

				if (flag == true){
					postfix[j] = ' ';
					j++;
				}

				flag = false;
				while (topInfix != -1 && precedence(symbol) <= precedence(stackInfix[topInfix])){

					temp = popInfix();
					postfix[j] = temp;
					j++;
				}
				pushInfix(symbol);
				break;
			case '*':

				if (flag == true){
					postfix[j] = ' ';
					j++;
				}
				flag = false;

				if (nextsymbol != '*'){

					while (topInfix != -1 && precedence(symbol) <= precedence(stackInfix[topInfix])){

						temp = popInfix();
						postfix[j] = temp;
						j++;
					}
					pushInfix(symbol);

				}
				if (nextsymbol == '*'){

					symbol = '^';

					while (topInfix != -1 && precedence(symbol) <= precedence(stackInfix[topInfix])){

						temp = popInfix();
						postfix[j] = temp;
						j++;
					}
					pushInfix(symbol);
					i++;

				}
				break;

			default:
				flag = true;
				postfix[j] = symbol;
				j++;

			}
			i++;
		}
	}

	if (topInfix >= 0){

		while (topInfix >= 0){

			postfix[j] = popInfix();
			j++;
		}

	}
	postfix[j] = '\0';
	printf("\n\n%s\n\n", postfix);

	finalResult = PostfixEval(postfix);

	return finalResult;

}

void pushInfix(char symbol){

	stackInfix[++topInfix] = symbol;
}

char popInfix(){

	char ch;
	ch = stackInfix[topInfix];
	topInfix--;
	return ch;
}

void infixWrapper(char* expr){


	char* ans = (char*)malloc(10 * sizeof(char));
	int result = 0;

	FILE *file = fopen("myfile.txt", "a");

	fprintf(file, "%s", expr);
	fprintf(file, "%s", "=");
	fclose(file);

	result = infixToPostfix(expr);
	printf("%d \n", result);
	//char* temp = getIntToString(result);


	itoa(result, ans, 10);
	printf("\n%s\n", ans);

	file = fopen("myfile.txt", "a");

	fprintf(file, "%s", ans);
	fprintf(file, "%s", "\n");
	fclose(file);

}

void lineExtracterUtil(char* filename){


	char character;

	char* line = (char*)malloc(200 * sizeof(char));
	int i = 0;


	FILE *file = fopen(filename, "r");

	if (file != NULL){

		character = fgetc(file);

		while (character != EOF){

			while (character != '\n' && character != EOF){
				line[i++] = character;
				character = fgetc(file);
			}
			line[i] = '\0';

			infixWrapper(line);
			i = 0;
			character = fgetc(file);
		}
		fclose(file);
	}

	else{

		printf("Error in Openeing the File \n");
		return;

	}
}


void pushPostfix(int symbol){

	stackPostfix[++topPostfix] = symbol;
}

int popPostfix(){

	int ch;
	ch = stackPostfix[topPostfix];
	topPostfix--;
	return ch;
}


void swapFile(char* file){

	remove(file);
	rename("myfile.txt", file);
}
int main(void){

	char* fileName= "SampleFile_ExpressionEvaluator.txt";

	lineExtracterUtil(fileName);
	swapFile(fileName);

	return 0;
}