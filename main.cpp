#include <iostream>
#include <vector>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5

using namespace std;

struct Student
{
    string last_name;
    string first_name;
    float grades[MAX_SUBJECTS][2];
    float average()
    {
        float total = 0;
        for (int i = 0; i < MAX_SUBJECTS; i++)
        {
            total += grades[i][0] + grades[i][1];
        }
        return total / (MAX_SUBJECTS * 2);
    };
    string mention()
    {
        float av = average();
        string m = "";
        if (av > 16)
        {
            m = "Très bien";
        }
        else if (av > 14)
        {
            m = "Bien";
        }
        else if (av > 12)
        {
            m = "Assez bien";
        }
        else if (av > 10)
        {
            m = "Passable";
        }
        else
        {
            m = "Insuffisant";
        }
        return m;
    };
};

string *get_subjects()
{
    static string subjects[MAX_SUBJECTS] = {"Math", "Francais", "Algorithmique", "Physique", "Musique"};
    return subjects;
}

void get_student_data(Student student[], int nb_student = 0)
{
    for (int i = 0; i < nb_student; i++)
    {
        cout << "Pour l'etudiant " << i + 1 << endl;
        cout << "Entrer le nom suivi du prenom: ";
        cin >> student[i].last_name >> student[i].first_name;

        for (int j = 0; j < MAX_SUBJECTS; j++)
        {
            cout << "Entrer les deux notes de la matiere " << get_subjects()[j] << " (sur 20): ";
            cin >> student[i].grades[j][0] >> student[i].grades[j][1];
        }
    }
}

void print_menu()
{
    cout << "Selectionner une action a effectuer par son numero" << endl;
    cout << "1 - Entrer les informations des etudiants" << endl;
    cout << "2 - Afficher la statistique de la classe" << endl;
    cout << "3 - Rechercher un etudiant puis afficher ses informations" << endl;
    cout << "4 - Quitter..." << endl;
    cout << ">: ";
}

int main()
{
    Student students[MAX_STUDENTS];
    int num_student = 0, choix;

    do
    {
        print_menu();
        cin >> choix;

        switch (choix)
        {
        case 1:
            cout << "Entrer le nombre total d'etudiant: ";
            cin >> num_student;
            get_student_data(students, num_student);
            break;
        case 4:
            break;
        default:
            cout << "Exiting program...";
        }
    } while (choix != 4);

    return 0;
}