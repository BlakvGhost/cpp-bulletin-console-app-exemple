#include <iostream>
#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5

using namespace std;

struct Student {
    string last_name;
    string first_name;
    float grades[MAX_SUBJECTS][2];
    float average;
    char mention[15];
};

void get_student_data(float student[][2], int nb_student = 0)
{
    for (int i = 0; i < nb_student; i++)
    {
        cout << "Entrer les deux notes de l'etudiant " << i + 1 << " separees par un espace: ";
        cin >> student[i][0] >> student[i][1];
    }
}

int main()
{
    float students[MAX_STUDENTS][2];
    int num_student;
    cout << "Entrer le nombre total d'etudiant: ";
    cin >> num_student;
    get_student_data(students, num_student);

    for (int i = 0; i < num_student; i++)
    {
        cout << "La note 1: " << students[i][0] << " puis la note 2: " << students[i][1] << endl;
    }
    return 0;
}