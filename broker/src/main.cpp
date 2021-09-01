#include <broker.hpp>
#include <iostream>
#include <App.h>

int main(int argc, char **argv)
{
    std::cout << "hello world\n";

    uWS::SSLApp()
        .get("/*", [](auto *res, auto * /*req*/)
             { res->end("Hello world!"); })
        .listen(15000, [](auto *listen_socket)
                {
                    if (listen_socket)
                    {
                        std::cout << "Listening on port " << 15000 << std::endl;
                    }
                })
        .run();

    std::cout << "Failed to listen on port 15000" << std::endl;
}