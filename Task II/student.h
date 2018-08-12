typedef struct Student{

	
	char name[50];
	int* marks;
	int total;
	int min;
	int max;
	float avg;
	int count;

}Student;

float computeAvg(int n1, int n2, int n3, int n4){

	return (float)((n1 + n2 + n3 + n4) / 4.0);
}


int getGrade(int num){


	if (num > 90 && num <= 100)
		return 10;

	else if (num > 80 && num <= 90)
		return 9;

	else if (num > 70 && num <= 80)
		return 8;

	else if (num > 60 && num <= 70)
		return 7;

	else if (num > 50 && num <= 60)
		return 6;

	else if (num > 40 && num <= 50)
		return 5;

	else if (num > 30 && num <= 40)
		return 4;

	else if (num > 30 && num <= 40)
		return 3;

	else if (num > 20 && num <= 30)
		return 2;

	else if (num > 10 && num <= 20)
		return 1;

	else return 0;

}

float computeCgpa(int n1, int n2, int n3, int n4){

	int g1 = getGrade(n1);
	int g2 = getGrade(n2);
	int g3 = getGrade(n3);
	int g4 = getGrade(n4);


	return (float)((g1 + g2 + g3 + g4) / 4.0);
}

