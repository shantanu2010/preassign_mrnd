typedef struct Student{


	char name[50];
	int* marks;
	int total;
	int min;
	int max;
	float avg;
	int count;
	int incomplete;

}Student;

void computeStudentDetails(Student* student){

	int min = INT_MAX;
	int max = INT_MIN;
	int total=0;
	for (int i = 0; i <student->count; i++){

		if (student->marks[i] < min)
			min = student->marks[i];
		
		if (student->marks[i] > max)
			max = student->marks[i];

		total += student->marks[i];

	}

	student->total = total;
	(student->avg) = ((0.1)*total)/(student->count);
	student->min = min;
	student->max = max;
}


