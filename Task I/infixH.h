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