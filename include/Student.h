//#ifndef S22612_STUDENT_H
//#define S22612_STUDENT_H
#include <sstream>
#include <string>


struct Student {
    std::string imie, nazwisko;
    int indeks, aktualny_semestr;
    double srednia_ocen;

    Student(std::string i, std::string n, int in, int akt_s, double sr_o)
    {
        imie             = i;
        nazwisko         = n;
        indeks           = in;
        aktualny_semestr = akt_s;
        srednia_ocen     = sr_o;
    }

    auto to_string() const -> std::string;
};

//#endif
