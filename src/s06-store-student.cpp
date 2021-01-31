#include <Student.h>
#include <fcntl.h>
#include <unistd.h>

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
    auto const IMIE             = std::string{"Kamil"};
    auto const NAZWISKO         = std::string{"Paczynski"};
    auto const INDEKS           = int{22612};
    auto const AKTUALNY_SEMESTR = int{1};
    auto const SREDNIA_OCEN     = double{4.0};

    auto student =
        s22612::Student{IMIE, NAZWISKO, INDEKS, AKTUALNY_SEMESTR, SREDNIA_OCEN};
    std::cout << student.to_string() << "\n";
    auto file = std::string{"./student.txt"};

    std::cout << "Saved to file: " << file << "\n";
    auto student_file = open(file.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);


    auto n = write(
        student_file, student.to_string().data(), student.to_string().size());

    if (n == -1) {
        perror("write(2)");
    }

    close(student_file);

    return 0;
}
