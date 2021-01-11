#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Course {
    char ID[10];
    int score;
};

struct Student {
    char name[255];
    double GPA;
    Course c;
};

Student *createStudent(const char *name, double gpa, const char *ID, int score){
    Student *newStudent = (Student*) malloc(sizeof(Student));
    strcpy(newStudent->name, name);
    newStudent->GPA = gpa;
    strcpy(newStudent->c.ID, ID);
    newStudent->c.score = score;

    return newStudent;
}

void removeStudent(Student *s){
    free(s);
    s = NULL;
}

void printStudent(Student *s){
    printf("Name : %s\n", s->name);
    printf("GPA : %.2lf\n", s->GPA);
    printf("Course ID : %s\n", s->c.ID);
    printf("Course Score : %d\n", s->c.score);
}

int main(){
    Student *s1 = createStudent("Adi", 3.80, "CMP6363", 90);

    printStudent(s1);
    removeStudent(s1);

    return 0;
}