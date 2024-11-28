#pragma once

#include <aws/gamelift/server/GameLiftServerAPI.h>
#include <string>
#include <iostream>

class GameLiftServer {
public:
    GameLiftServer();
    ~GameLiftServer();

    void OnStartGameSession(Aws::GameLift::Server::Model::GameSession);
    void OnProcessTerminate();
    bool OnHealthCheck();
    void OnUpdateGameSession(Aws::GameLift::Server::Model::UpdateGameSession);
    void SetupSDK(
        std::string webSocketUrl,
        std::string authToken,
        std::string fleetId,
        std::string hostId,
        std::string processId
        );
    void DestorySDK();
};