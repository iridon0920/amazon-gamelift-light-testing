#pragma once

#include <aws/gamelift/server/GameLiftServerAPI.h>
#include <string>
#include <iostream>

class GameLiftServer {
public:
    GameLiftServer();
    ~GameLiftServer();

    void onStartGameSession(Aws::GameLift::Server::Model::GameSession);
    void onProcessTerminate();
    bool OnHealthCheck();
    void OnUpdateGameSession();
    void SetupSDK(
        std::string webSocketUrl,
        std::string authToken,
        std::string fleetId,
        std::string hostId,
        std::string processId
        );
};