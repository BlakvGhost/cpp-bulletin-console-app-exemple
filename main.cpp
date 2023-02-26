#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5

using namespace std;

struct Student
{
    string last_name;
    string first_name;
    float grades[MAX_SUBJECTS][2];
    float average() const
    {
        float total = 0;
        for (int i = 0; i < MAX_SUBJECTS; i++)
        {
            total += grades[i][0] + grades[i][1];
        }
        return total / (MAX_SUBJECTS * 2);
    };
    string mention() const
    {
        const float av = average();

        string m = "";
        if (av > 16)
        {
            m = "Tres bien";
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

void say_hello(int colorCode)
{
    system("cls");
    printf("\x1b[1;%dm\n  _  _     _ _         ___ _         _  __     _    _     \n"
           " | || |___| | |___    |_ _( )_ __   | |/ /__ _| |__(_)_ _ \n"
           " | __ / -_) | / _ \\_   | ||/| '  \\  | ' </ _` | '_ \\ | '_|\n"
           " |_||_\\___|_|_\\___( ) |___| |_|_|_| |_|\\_\\__,_|_.__/_|_|  \n"
           "                  |/\x1b[0m\n",
           colorCode);
}

string intToString(float number)
{
    ostringstream ss;
    ss << number;
    return ss.str();
}

string *get_subjects()
{
    static string subjects[MAX_SUBJECTS] = {"Mathematiques", "Francais     ", "Algorithmique", "Physique     ", "Musique      "};
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

void class_statistic(
    Student student[],
    int nb_students,
    float &class_average,
    float &max_average,
    float &min_average)
{
    min_average = student[0].average();

    for (int c = 0; c < nb_students; c++)
    {
        if (max_average < student[c].average())
        {
            max_average = student[c].average();
        }

        if (min_average > student[c].average())
        {
            min_average = student[c].average();
        }
        class_average += student[c].average();
    }
    class_average /= nb_students;
}

bool compare_students(Student s1, Student s2)
{
    // Comparaison des noms de famille
    if (s1.last_name != s2.last_name)
    {
        return s1.last_name < s2.last_name;
    }
    // Si les noms de famille sont les mêmes, comparer les prénoms
    return s1.first_name < s2.first_name;
}

void write_data_in_file(Student student[], int nb_students, float class_average, float max_average, float min_average)
{
    sort(student, student + nb_students, compare_students);

    ofstream file("students.txt");

    for (int i = 0; i < nb_students; i++)
    {
        file << i + 1 << " - " << student[i].last_name << " " << student[i].first_name << endl;

        for (int j = 0; j < MAX_SUBJECTS; j++)
        {
            file << get_subjects()[j] << " " << student[i].grades[j][0] << " " << student[i].grades[j][1] << endl;
        }
        int rank = 1;
        for (int j = 0; j < nb_students; j++)
        {
            if (student[j].average() > student[i].average())
            {
                rank++;
            }
        }
        file << "Moyenne: " << student[i].average() << endl
             << "Mention: " << student[i].mention() << endl
             << "Rang: " << rank << endl;
        file << "************************************************************************\n";
    }

    file << "Statistiques de la classe:" << endl;
    file << "Nombre total d'etudiant: " << nb_students << endl;
    file << "la moyenne de la classe est: " << class_average << endl;
    file << "la moyenne la plus faible de la classe est: " << min_average << endl;
    file << "la moyenne la plus forte de la classe est: " << max_average << endl;

    file.close();

    cout << "Les donnees ont ete ecrites dans le fichier students.txt" << endl;
}

string print_student_bulletin(const Student &student, int rank)
{
    string result = "\x1b[1;32m";
    string separator = "*********************************************\n";
    result += separator;
    result += "\t\t BULLETIN DE NOTES\n";
    result += separator;
    result += "Nom:    " + student.last_name + "\nPrenom: " + student.first_name + "\n";
    result += separator;
    result += "Matiere\t\tNote1\tNote2\tMoyenne\n";
    result += separator;
    string *subjects = get_subjects();
    for (int i = 0; i < MAX_SUBJECTS; i++)
    {
        result += subjects[i] + "\t" + intToString(student.grades[i][0]) + "\t" + intToString(student.grades[i][1]) + "\t" + intToString((student.grades[i][0] + student.grades[i][1]) / 2) + "\n";
    }
    result += separator;
    result += "Moyenne:\t\t" + intToString(student.average()) + "\n";
    result += "Mention:\t\t" + student.mention() + "\n";
    result += "Rang   :\t\t" + intToString(rank) + "\n";
    result += separator + "\x1b[0m";
    return result;
}

void search_student(Student student[], int nb_students)
{
    string last_name, first_name;
    cout << "Entrer le nom suivi du prenom de l'etudiants a rechercher: ";
    cin >> last_name >> first_name;

    for (int i = 0; i < nb_students; i++)
    {
        if (last_name == student[i].last_name && first_name == student[i].first_name)
        {
            int rank = 1;
            for (int j = 0; j < nb_students; j++)
            {
                if (student[j].average() > student[i].average())
                {
                    rank++;
                }
            }
            cout << print_student_bulletin(student[i], rank);
            return;
        }
    }
    cout << "\x1b[1;32m\nAucun etudiant ne s'appelle " << last_name << " " << first_name << " dans cette base de donnees\x1b[0m" << endl;
}

void print_menu()
{
    cout << "\x1b[1;34m\nSelectionner une action a effectuer par son numero" << endl;
    cout << "1 - Entrer les informations des etudiants" << endl;
    cout << "2 - Afficher la statistique de la classe" << endl;
    cout << "3 - Rechercher un etudiant puis afficher ses informations" << endl;
    cout << "4 - Quitter..." << endl;
    cout << ">:\x1b[0m ";
}

int main()
{
    Student students[MAX_STUDENTS];
    int num_student = 0, choix = 0;
    float class_average = 0, max_average = 0, min_average = 20;

    say_hello(36);
    do
    {
        print_menu();
        cin >> choix;

        switch (choix)
        {
        case 1:
            say_hello(33);
            cout << "Entrer le nombre total d'etudiant: ";
            cin >> num_student;
            if (num_student > 0 && num_student <= MAX_STUDENTS)
            {
                get_student_data(students, num_student);
                class_statistic(students, num_student, class_average, max_average, min_average);
                write_data_in_file(students, num_student, class_average, max_average, min_average);
                break;
            }
            cout << "Nombre d'etudiant incorrect: doit etre [1, " << MAX_STUDENTS << "]" << endl;
            break;
        case 2:
            say_hello(31);
            cout << "Nombre total d'etudiant: " << num_student << endl;
            cout << "la moyenne de la classe est: " << class_average << endl;
            cout << "la moyenne la plus faible de la classe est: " << min_average << endl;
            cout << "la moyenne la plus forte de la classe est: " << max_average << endl;
            break;
        case 3:
            say_hello(32);
            search_student(students, num_student);
            break;
        case 4:
            cout << "Exiting program...";
            break;
        default:
            say_hello(34);
            cout << "Bad choice, try egain!" << endl;
            break;
        }
    } while (choix != 4);

    return 0;
}