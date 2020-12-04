#include <Student.h>

#include <iostream>

auto Student::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << "Imie: "
        << imie
        << "\nNazwisko: "
        << nazwisko
        << "\nIndeks:"
        << indeks
        << "\nAktualny semestr: "
        << aktualny_semestr
        << "\nŚrednia ocen: "
        << srednia_ocen;
    return out.str();
}

auto main() -> int {


    auto student = Student{"Kamil", "Paczynski", 22612, 1, 4.0};
    std::cout << student.to_string() << "\n";
    return 0;
}
