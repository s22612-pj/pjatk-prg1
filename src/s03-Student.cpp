#include <Student.h>

#include <iostream>
#include <sstream>


s22612::Student::Student(std::string imie,
                         std::string nazwisko,
                         int indeks,
                         int aktualny_semestr,
                         double srednia_ocen)
        : imie{imie}
        , nazwisko{nazwisko}
        , indeks{indeks}
        , aktualny_semestr{aktualny_semestr}
        , srednia_ocen{srednia_ocen}
{}

auto s22612::Student::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << "Imie: " << imie << "\nNazwisko: " << nazwisko
        << "\nIndeks:" << indeks << "\nAktualny semestr: " << aktualny_semestr
        << "\nŚrednia ocen: " << srednia_ocen;
    return out.str();
}

auto main() -> int
{
    auto student = s22612::Student{"Kamil", "Paczynski", 22612, 1, 4.0};
    std::cout << student.to_string() << "\n";
    return 0;
}
