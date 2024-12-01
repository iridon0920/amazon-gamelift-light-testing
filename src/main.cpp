#include "GameLiftServer.h"
#include "httplib.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " <webSocketUrl> <processId> <fleetId> <hostId> <authToken> <port>" << std::endl;
        return 1;
    }

    // コマンドライン引数から値を取得
    std::string webSocketUrl = argv[1];
    std::string processId = argv[2];
    std::string fleetId = argv[3];
    std::string hostId = argv[4];
    std::string authToken = argv[5];
    std::uint16_t port = std::stoi(argv[6]);

    GameLiftServer gameliftServer;
    gameliftServer.SetupSDK(
        webSocketUrl,
        authToken,
        fleetId,
        hostId,
        processId,
        port
        );

    httplib::Server svr;
    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
      res.set_content("Hello World!", "text/plain");
    });

    svr.listen("0.0.0.0", port);

    gameliftServer.DestorySDK();
}
