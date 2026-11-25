//Створити динамічний масив структур студентів з оцінками з фізики, математики та інформатики.
//Вивести прізвища відмінників і визначити відсоток студентів із середнім балом понад 4,5.

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// Specialties in alphabetical order by their English names.
enum Specialty { CS, INF, ME, PI, TE };

struct Student
{
    string surname;
    int course;
    Specialty spec;
    int physics, math;
    int informatics;
};

string SpecName(Specialty spec)
{
    switch (spec)
    {
    case CS: return "Computer Science";
    case INF: return "Informatics";
    case ME: return "Math and Economics";
    case PI: return "Physics and Informatics";
    case TE: return "Technology Education";
    }
    return "Unknown";
}

int ReadInt(const string& prompt, int low, int high)
{
    int x;
    while (true)
    {
        cout << prompt;
        if (cin >> x && x >= low && x <= high)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid value. Try again.\n";
    }
}

Specialty ReadSpec()
{
    cout << "0-CS, 1-INF, 2-ME, 3-PI, 4-TE\n";
    return (Specialty)ReadInt("Specialty: ", 0, 4);
}

void Create(Student* s, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Student " << i + 1 << ":\n";
        cout << "Surname: ";
        getline(cin >> ws, s[i].surname);
        s[i].course = ReadInt("Course: ", 1, 6);
        s[i].spec = ReadSpec();
        s[i].physics = ReadInt("Physics: ", 2, 5);
        s[i].math = ReadInt("Mathematics: ", 2, 5);
        s[i].informatics = ReadInt("Informatics: ", 2, 5);
    }
}

void Print(const Student* s, int n, const int* index = nullptr)
{
    cout << "\nStudents\n";
    cout << left << setw(4) << "No" << setw(16) << "Surname"
        << setw(8) << "Course" << setw(25) << "Specialty"
        << setw(6) << "Phys" << setw(6) << "Math"
        << "Info\n";
    for (int i = 0; i < n; i++)
    {
        int j = index == nullptr ? i : index[i];
        cout << left << setw(4) << i + 1
            << setw(16) << s[j].surname << setw(8) << s[j].course
            << setw(25) << SpecName(s[j].spec)
            << setw(6) << s[j].physics << setw(6) << s[j].math;
        cout << s[j].informatics << '\n';
    }
}

double Average(const Student& s)
{
    return (s.physics + s.math + s.informatics) / 3.0;
}

void PrintExcellent(const Student* s, int n)
{
    cout << "\nExcellent students:\n";
    bool found = false;
    for (int i = 0; i < n; i++)
        if (Average(s[i]) == 5.0)
        {
            cout << s[i].surname << '\n';
            found = true;
        }
    if (!found) cout << "None\n";
}

double PercentAbove(const Student* s, int n)
{
    if (n == 0) return 0;
    int k = 0;
    for (int i = 0; i < n; i++)
        if (Average(s[i]) > 4.5) k++;
    return 100.0 * k / n;
}

#ifndef UNIT_TEST
int main()
{
    int n = ReadInt("Number of students: ", 1, 1000);
    Student* s = new Student[n];
    Create(s, n);
    Print(s, n);
    PrintExcellent(s, n);
    cout << fixed << setprecision(2)
        << "Average > 4.5: " << PercentAbove(s, n) << "%\n";
    delete[] s;
    return 0;
}
#endif
