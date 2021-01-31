#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>
#include <vector>


auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        std::cout << "Podaj jako argument nazwę pliku"
                  << "\n";
        return 1;
    }

    auto const file_name = std::string{argv[1]};

    auto fd = open(file_name.c_str(), O_RDONLY, S_IRUSR);

    if (fd == -1) {
        std::cout << "Taki plik nie istnieje"
                  << "\n";
        return 1;
    }

    struct stat info;
    memset(&info, 0, sizeof(info));
    auto const r = fstat(fd, &info);

    if (r == -1) {
        perror("stat(2)");
        return 1;
    }

    std::array<char, 4096> buf{0};
    auto const n = read(fd, buf.data(), buf.size());
    close(fd);

    if (n == -1) {
        perror("Something went wrong");
        return 1;
    }

    std::cout << std::string{buf.data(), static_cast<size_t>(n)} << "\n";

    return 0;
}
