#include <Student.h>
#include <fcntl.h>
#include <unistd.h>

#include <array>
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
    out << imie << "\n"
        << nazwisko << "\n"
        << indeks << "\n"
        << aktualny_semestr << "\n"
        << srednia_ocen;
    return out.str();
}

auto main() -> int
{
    auto const file   = std::string{"./student.txt"};
    auto file_student = open(file.c_str(), O_RDONLY, S_IRUSR);
    std::array<char, 4096> buf{0};
    auto const n = read(file_student, buf.data(), buf.size());
    close(file_student);

    if (n == -1) {
        perror("stat(2)");
        return 1;
    }

    auto student = s22612::Student{"Kamil", "Paczynski", 22612, 1, 4.0};
    std::cout << student.to_string() << "\n";
    return 0;
}
