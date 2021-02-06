#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>
#include <vector>


auto file_server(std::string const& file_path) -> std::string
{
    auto fd = open(file_path.c_str(), O_RDONLY, S_IRUSR);

    if (fd == -1) {
        return ":-(";
    }

    struct stat info;
    memset(&info, 0, sizeof(info));
    auto const r = fstat(fd, &info);

    if (r == -1) {
        return ("stat(2)");
    }

    std::vector<char> buf(info.st_size, 0);
    auto const n = read(fd, buf.data(), buf.size());
    close(fd);

    if (n == -1) {
        return ("Something went wrong");
    }

    auto const file_server = std::string{
        file_path + "\n" + std::string{buf.data(), static_cast<size_t>(n)}};

    return file_server;
}


auto main_loop(int const server_sock) -> void
{
    std::string const data;
    auto clients = std::vector<int>{};
    while (true) {
        {
            auto client_sock =
                accept4(server_sock, nullptr, nullptr, SOCK_NONBLOCK);
            if (client_sock == -1) {
            } else {
                std::cout << "Nowy klient!\n";
                clients.push_back(client_sock);
            }
        }


        for (auto const each : clients) {
            auto buf = std::string{};
            buf.resize(4096);


            auto const n = read(each, buf.data(), buf.size());
            if (n == -1) {
            } else if (n == 0) {
                std::cout << "Rozłączono klienta numer: " << each << "\n";
                shutdown(each, SHUT_RDWR);
                close(each);
            } else {
                auto const file_server_data = file_server(data);

                write(each, file_server_data.data(), file_server_data.size());
            }
        }
    }
}


auto main() -> int
{
    auto const ip   = std::string{"127.0.0.1"};
    auto const port = uint16_t{8080};
    std::cout << "Nasłuchuję na ip: " << ip << "\n"
              << "Port: " << port << "\n";

    auto server_sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    {
        auto const enable = int{1};
        setsockopt(
            server_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);

    bind(server_sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    listen(server_sock, SOMAXCONN);

    main_loop(server_sock);


    shutdown(server_sock, SHUT_RDWR);
    close(server_sock);

    return 0;
}
