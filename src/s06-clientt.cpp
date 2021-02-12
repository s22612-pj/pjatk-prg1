#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>
#include <vector>

auto main() -> int
{
    auto const ip    = std::string{"127.0.0.1"};
    auto const port  = uint16_t{8080};
    auto server_sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (server_sock == -1) {
        perror("Something went wrong");
        return 1;
    }


    sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);

    auto client =
        connect(server_sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (client == -1) {
        perror("error");
    } else {
        std::cout << "Połączono z IP: " << ip << "\n"
                  << "Port: " << port << "\n";

        while (true) {
            auto data = std::string{};
            std::cout << "wysłano: ";
            std::getline(std::cin, data);

            data.append("\n");

            write(server_sock, data.data(), data.size());

            std::array<char, 4096> buf{0};
            memset(buf.data(), 0, sizeof(buf));
            auto const n = read(server_sock, buf.data(), buf.size());
            std::cout << "pobrano"
                      << " : "
                      << std::string{buf.data(), static_cast<size_t>(n)};
        }

        shutdown(server_sock, SHUT_RDWR);
        close(server_sock);
    }

    return 0;
}
