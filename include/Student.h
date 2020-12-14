#ifndef S22612_STUDENT_H
#define S22612_STUDENT_H

#include <string>
namespace s22612 {
struct Student {
    std::string const imie;
    std::string const nazwisko;
    int indeks;
    int aktualny_semestr;
    double srednia_ocen;


    Student(std::string, std::string, int, int, double);
    auto to_string() const -> std::string;
};
}  // namespace s22612

#endif
