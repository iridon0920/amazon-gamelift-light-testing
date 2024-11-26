#include "GameLiftServer.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " <webSocketUrl> <processId> <fleetId> <hostId> <authToken>" << std::endl;
        return 1;
    }

    // コマンドライン引数から値を取得
    std::string webSocketUrl = argv[1];
    std::string processId = argv[2];
    std::string fleetId = argv[3];
    std::string hostId = argv[4];
    std::string authToken = argv[5];

    GameLiftServer gameliftServer;
    gameliftServer.SetupSDK(
        webSocketUrl,
        authToken,
        fleetId,
        hostId,
        processId
        );

    return 0;
}