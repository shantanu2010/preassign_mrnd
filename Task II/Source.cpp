#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>
#include "students.h"
#include "util.h"


Student** studentArray = (Student**)malloc(5 * sizeof(Student*));
char** subjectNames = (char**)malloc(10 * sizeof(char*));

int currIndex = 0;
int size = 5;
int subjectSize = 10;

void allocateSubjectNames(char* str,int count){

	char** temp;
	if (count >= 10){

		temp = subjectNames;
		subjectNames= (char**)malloc((count + 1)*sizeof(char*));
		free(temp);
	}

	int i = 0;
	int j = 0;
	int k = 0;

	char* s = (char*)malloc(10 * sizeof(char));

	while (i < count){

		while (str[j] != '\n' && str[j] != ','){
			s[k] = str[j];
			k++;
			j++;
		}
		s[k] = '\0';
		k = 0;
		j++;

		subjectNames[i] = (char*)malloc(10 * sizeof(char));

		strcpy(subjectNames[i], s);

		i++;
	}

}

void reallocateStudent(){

	Student ** temp = (Student**)malloc((size * 2) * sizeof(Student*));
	size = size * 2;
	int i = 0;
	for (i = 0; i < currIndex; i++)
		temp[i] = studentArray[i];

	free(studentArray);
	studentArray = temp;

}
bool allocateStudent(char* str){

	Student* student = (Student*)malloc(sizeof(Student));
	
	strcpy(student->name, str);

	if (currIndex == size - 1)
		reallocateStudent();
	
	studentArray[currIndex] = student;

	return true;
}



int convertIntoNumber(char* str){

	if (str == NULL)
		return -1;
	else
		return atoi(str);

}


void lower_string(char* s) {
	
	int c = 0;

	while (s[c] != '\0') {
		if (s[c] >= 'A' && s[c] <= 'Z') {
			s[c] = s[c] + 32;
		}
		c++;
	}
}

bool allocateMarks(char* str,int index){


	char s[5];
	int i = 0;
	int j = 0;
	int k = 0;
	int seperatorCount=0;
	int partialCount = 0;
	int tempNumber;
	int temp;
	
	int* array = (int*)malloc(subjectSize*sizeof(int));

	while (str[i] != '\0'){


		if (str[i] == ','){

			seperatorCount++;
			s[j] = '\0';
			
			if (j == 0){

				array[k++] = -1;
				partialCount++;

			}
			else{

				temp = atoi(s);
				array[k++] = temp;
			}
			j = 0;
			s[j] = '\0';
		}

		else{

			s[j++] = str[i];

		}

		i++;

	}

	s[j] = '\0';
	if (s[0] == '\0'){

		partialCount++;
		array[k] = -1;
	}
	else{
		array[k] = atoi(s);
	}

	if (k>0 && k<subjectSize){
		studentArray[index]->marks = array;
		studentArray[index]->count = k + 1;
		studentArray[index]->incomplete = partialCount;
		computeStudentDetails(studentArray[index]);

		return true;
	}

	return false;

}

void lineExtractor(char* filename){


	char character;

	char buf[256];
	

	char* line = (char*)malloc(200 * sizeof(char));
	int i = 0;
	int count = 0;
	int loopCount;
	int temp;

	FILE *file = fopen(filename, "r");
	bool flag1 = false;
	bool flag2 = false;
	if (file != NULL){

		fgets(buf, 256, file);
		buf[strlen(buf) - 1] = '\0';
		
		temp = atoi(buf);
		subjectSize = temp;

		fgets(buf, 256, file);
		
		lower_string(buf);
		allocateSubjectNames(buf, temp);

		while (fgets(buf, 256, file) != NULL){

			if (isalpha(buf[0])){

				buf[strlen(buf) - 1] = '\0';
				lower_string(buf);
				flag1 = allocateStudent(buf);
				

			}

			else if (isdigit(buf[0]) && flag1){

				buf[strlen(buf) - 1] = '\0';
				lower_string(buf);
				flag2 = allocateMarks(buf,currIndex);
			}

			if (flag1 && flag2){


				currIndex++;
				flag1 = false;
				flag2 = false;
			}

		}
			
	}

	else{

		printf("Error in Openeing the File \n");
		return;

	}
	fclose(file);

}

void printParticularStudent(){

	int i = 0;
	int j = 0;
	char str[50];
	
	printf("\nEnter Student Name : ");
	scanf(" %s", str);
	lower_string(str);

	
	for (i = 0; i < currIndex; i++){

		if (strcmp(studentArray[i]->name,str) == 0){

			printf("\nDetails of %s are \n", str);

			for (j = 0; j < studentArray[i]->count; j++)
				printf("%s - %d\n", subjectNames[j], studentArray[i]->marks[j]);
		}

	}

}

void printData(){

	int i = 0;
	int j = 0;

	
	printf("\n\nDetails Are : \n");
	for (i = 0; i < subjectSize; i++){

		printf("%s|", subjectNames[i]);
	}
	printf("Name|");
	printf("\n");
	for (i = 0; i < currIndex; i++){
		
		
		for (j = 0; j < studentArray[i]->count; j++)
			printf("%d\t", studentArray[i]->marks[j]);

		printf("%s\t", studentArray[i]->name);

		printf("\n");

	}

}

int getIndex(char* str){

	for (int i = 0; i<subjectSize; i++){

		if (strcmp(subjectNames[i], str) == 0)
			return i;
	}
	return -1;
}
void printParticularMarksStudent(){

	char buf1[20];
	char buf2[20];
	
	printf("\nEnter Name : ");
	scanf(" %s", buf1);
	lower_string(buf1);

	printf("\nEnter Subject : ");
	scanf(" %[^\n]", buf2);

	lower_string(buf2);
	int index = getIndex(buf2);


	if (index == -1)
		printf("\nNo Such Subject Exists");

	else{

		int i = 0;
		
		for (i = 0; i < currIndex; i++){
			if (strcmp(buf1, studentArray[i]->name) == 0){
				printf("%s ", studentArray[i]->name);
				printf(" %d\n", studentArray[i]->marks[index]);
			}
		}
	}

}

void maximumMarksStudent(){

	for (int i = 0; i < currIndex; i++){

		printf("%d\n", studentArray[i]->max);
	}

}

void average(){

	for (int i = 0; i < currIndex; i++){

		printf("%f\n", studentArray[i]->avg);
	}
}

void fetchMarksStudent(){

	char buf[20];
	
	
	printf("\nEnter Subject : ");
	scanf(" %[^\n]", buf);
	lower_string(buf);

	int index = getIndex(buf);


	if (index == -1)
		printf("\nNo Such Subject Exists");

	else{

		int i = 0;

		for (i = 0; i < currIndex; i++){
			
				printf("%s ", studentArray[i]->name);
				printf(" %d\n", studentArray[i]->marks[index]);
			
		}
	}

}

void addnewData(){

	bool flag1 = false;
	bool flag2 = false;

	char buf1[50];
	char buf2[50];

	printf("\nEnter Name : ");
	scanf(" %s", buf1);
	lower_string(buf1);

	printf("\nEnter Subject : ");
	scanf(" %s", buf2);
	lower_string(buf2);

	if (isalpha(buf1[0]))
		flag1 = allocateStudent(buf1);

	if (flag1 && isdigit(buf2[0]))

		flag2 = allocateMarks(buf2,currIndex);

	if (flag1 && flag2){

		printf("\nData Successfully Added");
		currIndex++;
		return;
	}
	else{

		printf("\nData couldnt be loaded");
	}

}

void changeName(){


	char buf1[50];
	char buf2[50];

	printf("\nEnter the Name to be Changed : ");
	scanf(" %[^\n]", buf1);
	lower_string(buf1);

	printf("\nEnter the new name : ");
	scanf(" %[^\n]", buf2);
	lower_string(buf2);

	bool flag = false;

	for (int i = 0; i < currIndex && !flag; i++){

		if (strcmp(studentArray[i]->name, buf1) == 0){

			flag = true;
			printf("\nName changesd from %s to %s", studentArray[i]->name, buf2);
			strcpy(studentArray[i]->name, buf2);

		}
	}

	if (!flag){

		printf("\nNo Such Student");
	}


}

void changeMarks(){



	char buf1[30];
	char buf2[30];
	char buf3[30];

	printf("\nEnter Name of the Student : ");
	scanf(" %[^\n]", buf1);
	lower_string(buf1);

	printf("\nEnter the subject Name or total if you want to change all marks : ");
	scanf(" %[^\n]", buf2);
	lower_string(buf2);
	
	printf("\nEnter Marks : ");
	scanf(" %[^\n]", buf3);
	lower_string(buf3);
	
	int index = -1;

	for (int i = 0; i < currIndex; i++){

		if (strcmp(studentArray[i]->name, buf1) == 0){

			index = i;
			break;
		}
	}

	if (index != -1){

		bool flag = false;

		if (strcmp(buf2, "total") == 0){

			flag = allocateMarks(buf3,index);
			
			if (flag)
				printf("\nTotal Marks succesfully Updated");
			else
				printf("\nMarks coudnt be updated");

		}
		else {

			int temp = getIndex(buf2);
			
			if (temp != -1){

				studentArray[index]->marks[temp] = atoi(buf3);
			}
			else{

				printf("\nSubject not Found...");
			}
		}

	}

}

void deleteStudent(){


	char buf[30];

	printf("\nEnter Name of the Student : ");
	scanf(" %[^\n]", buf);
	lower_string(buf);

	int index = -1;
	for (int i = 0; i < currIndex; i++){

		if (strcmp(studentArray[i]->name, buf) == 0){
			index = i;
			break;
		}
	}

	if (index != -1){

		Student* temp = studentArray[index];
		free(temp);

		if (index == currIndex - 1)
			currIndex--;

		else{

			
			for (int j = index; j < currIndex - 1; j++)
				studentArray[j] = studentArray[j + 1];

			currIndex--;
		}

	}

}

int getStudentIndex(char* name){


	for (int i = 0; i < currIndex; i++){

		if (strcmp(studentArray[i]->name, name) == 0)
			return i;
	}
	return -1;
}

void displayMissing(){

	for (int i = 0; i < currIndex; i++){


		if (studentArray[i]->incomplete > 0)
			printf(" %s\n", studentArray[i]->name);

	}
	char buf[20];
	printf("\nDo you want To Update Marks (yes/no): ");
	scanf(" %s", buf);
	lower_string(buf);


	if (buf[0] == 'y'){

		printf("\nEnter The Name: ");
		scanf(" %s", buf);
		lower_string(buf);

		int index = getStudentIndex(buf);
		
		printf("\nEnter Marks : ");
		scanf(" %s", buf);
		lower_string(buf);
		bool flag = false;

		if (index != -1){

			flag = allocateMarks(buf, index);

		}

		if (flag)
			printf("\nMarks Updated");
		else
			printf("\nCouldnt update marks as student Mismatch");
		

	}
}

int comparator(const void* a, const void* b){

	int l = (*(Student**)a)->total;
	int r = (*(Student**)b)->total;

	if (l > r)
		return -1;
	else if (l < r)
		return 1;

	return 0;
}

void leaderBoard(){

	qsort(studentArray, currIndex, sizeof(Student*), &comparator);
	printData();
}

int* lessThan(int subject, int mark, int* index){

	int*  tempArray = (int*)malloc(size*sizeof(int));
	
	for (int i = 0; i < currIndex; i++){

		if (studentArray[i]->marks[subject] < mark)
			tempArray[(*index)++] = i;
	}
	return tempArray;
}

int* lessThanEqualTo(int subject, int mark, int* index){

	int*  tempArray = (int*)malloc(size*sizeof(int));

	for (int i = 0; i < currIndex; i++){

		if (studentArray[i]->marks[subject] <= mark)
			tempArray[(*index)++] = i;
	}
	return tempArray;
}

int* greaterThan(int subject, int mark, int* index){

	int*  tempArray = (int*)malloc(size*sizeof(int));

	for (int i = 0; i < currIndex; i++){

		if (studentArray[i]->marks[subject] > mark)
			tempArray[(*index)++] = i;
	}
	return tempArray;
}

int* greaterThanEqualTo(int subject, int mark, int* index){

	int*  tempArray = (int*)malloc(size*sizeof(int));

	for (int i = 0; i < currIndex; i++){

		if (studentArray[i]->marks[subject] >= mark)
			tempArray[(*index)++] = i;
	}
	return tempArray;
}

int* equal(int subject, int mark, int* index){

	int*  tempArray = (int*)malloc(size*sizeof(int));

	for (int i = 0; i < currIndex; i++){

		if (studentArray[i]->marks[subject] == mark){
			tempArray[(*index)] = i;
			*index = *index + 1;
		}
	}

	return tempArray;
}


void printCustom(int* array, int index){


	printf("\nName\n");
	for (int i = 0; i < index; i++){

		printf("%s\n", studentArray[array[i]]->name);
	}
}


int* processSimpleQuery(char* variable, char* compare, char* value,int* resultIndex){

	qsort(studentArray, currIndex, sizeof(Student*), &comparator);
	int subjectIndex = getIndex(variable);
	int mark = atoi(value);
	int* resultIndices = NULL;
	
	if (subjectIndex != -1){

		if (strcmp(compare, "<") == 0)
			resultIndices = lessThan(subjectIndex, mark, resultIndex);

		else if (strcmp(compare, "<=") == 0)
			resultIndices = lessThanEqualTo(subjectIndex, mark, resultIndex);

		else if (strcmp(compare, ">") == 0)
			resultIndices = greaterThan(subjectIndex, mark, resultIndex);

		else if (strcmp(compare, ">=") == 0)
			resultIndices = greaterThanEqualTo(subjectIndex, mark, resultIndex);

		else if (strcmp(compare, "=") == 0)
			resultIndices = equal(subjectIndex, mark, resultIndex);

		else
			printf("\nInvalid operator");

		return resultIndices;
	}
	else{

		printf("\nInvalid Name");
	}

	return NULL;
	//if (resultIndices != NULL){
		//printCustom(resultIndices, resultIndex);
		//free(resultIndices);
	//}

}

void printUnion(int arr1[], int arr2[], int m, int n){

	int i = 0, j = 0;
	while (i < m && j < n){

		if (arr1[i] < arr2[j]){

			printf("\n%s", studentArray[arr1[i]]);
			i++;
		}
		else if (arr2[j] < arr1[i]){

			printf("\n%s", studentArray[arr1[j]]);
			j++;
		}
		
		else{
			printf("\n%s", studentArray[arr1[j]]);
			j++;
			i++;
		}
	}

	while (i < m){

		printf("\n%s", studentArray[arr1[i]]);
		i++;

	}
	
	while (j < n){

		printf("\n%s", studentArray[arr1[j]]);
		j++;
	}
		
}


void printIntersection(int arr1[], int arr2[], int m, int n){

	int i = 0, j = 0;
	while (i < m && j < n){

		if (arr1[i] < arr2[j])
			i++;
		else if (arr2[j] < arr1[i])
			j++;
		else {
			printf("\n%s", studentArray[arr1[j]]);
			j++;
			i++;
		}
	}
}
void leaderBoardQuery(){

	char buf[100];
	printf("\nEnter Query : ");
	//scanf(" %[^\n]", buf);

	char* variableIdentifer = (char*)malloc(30 * sizeof(char));
	char* comparatorIdentifer = (char*)malloc(30 * sizeof(char));
	char* valueIdentifer = (char*)malloc(30 * sizeof(char));
	char* operation = (char*)malloc(5 * sizeof(char));
	int resultIndex1 = 0;

	scanf(" %s %s %s", variableIdentifer, comparatorIdentifer, valueIdentifer);
	lower_string(variableIdentifer);
	lower_string(comparatorIdentifer);
	lower_string(valueIdentifer);

	if (strcmp(variableIdentifer, "name") == 0){


		int studentIndex = getStudentIndex(valueIdentifer);

		if (studentIndex != -1){

			printf("\nName : %s", valueIdentifer);
			printf("\nMarks are : ");

			for (int i = 0; i < studentArray[studentIndex]->count; i++){

				printf("\n%s : %d", subjectNames[i], studentArray[studentIndex]->marks[i]);
			}

		}
		else{

			printf("\nInvalid Name");
		}
		return;

	}
	else{

		int* res1 = processSimpleQuery(variableIdentifer, comparatorIdentifer, valueIdentifer, &resultIndex1);

		printf("Do You want to Perform And/Or (Yes/No) : ");
		scanf(" %s", buf);

		lower_string(buf);
		if (strcmp(buf, "yes") == 0){


			printf("\nEnter option (And/Or) : ");
			scanf(" %s", buf);
			lower_string(buf);
			printf("\nEnter Query : ");
			scanf(" %s %s %s", variableIdentifer, comparatorIdentifer, valueIdentifer);
			lower_string(variableIdentifer);
			lower_string(comparatorIdentifer);
			lower_string(valueIdentifer);
			int resultIndex2 = 0;
			int* res2 = processSimpleQuery(variableIdentifer, comparatorIdentifer, valueIdentifer, &resultIndex2);

			printf("\nNames");
			if (strcmp(buf, "and") == 0){

				printIntersection(res1, res2, resultIndex1, resultIndex2);

			}

			else{

				printUnion(res1, res2, resultIndex1, resultIndex2);
			}

			free(res1);
			free(res2);
		}

		else{

			printCustom(res1, resultIndex1);
			free(res1);
		}
	}


}
int main(void){


	char* fileName = "SampleFile_StudentsMarksSystem.txt";
	lineExtractor(fileName);

	int i = 0;
	
	int choice;

	do{
				
		printOptions();
		scanf(" %d", &choice);

		switch (choice){

			case 1:

				printData();
				break;
			case 2:
				printParticularStudent();
				break;
			case 3:
				printParticularMarksStudent();
				break;
			case 4:
				maximumMarksStudent();
				break;
			case 5:
				average();
				break;
			
			case 6:
				fetchMarksStudent();
				break;
			case 7:
				addnewData();
				break;
			
			case 8:
				changeName();
				break;

			case 9:
				changeMarks();
				break;
			case 10:
				deleteStudent();
				break;
			case 11:
				displayMissing();
				break;
			case 12:
				leaderBoard();
				break;

			case 13:
				leaderBoardQuery();
				break;

			case 14:
				break;
				
		}

	} while (choice != 14);
	
	printf("value of current %d\n", currIndex);
	
	
	getchar();

}



