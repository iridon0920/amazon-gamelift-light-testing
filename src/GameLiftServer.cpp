#define GAMELIFT_USE_STD 1
#include "GameLiftServer.h"

GameLiftServer::GameLiftServer() {
}

GameLiftServer::~GameLiftServer() {
}

void GameLiftServer::onStartGameSession(Aws::GameLift::Server::Model::GameSession myGameSession) {
    Aws::GameLift::GenericOutcome outcome = 
        Aws::GameLift::Server::ActivateGameSession();
}

void GameLiftServer::onProcessTerminate() {
    Aws::GameLift::GenericOutcome outcome = 
        Aws::GameLift::Server::ProcessEnding();
}

bool GameLiftServer::OnHealthCheck() {
    return true;
}

void GameLiftServer::OnUpdateGameSession() {
}

void GameLiftServer::SetupSDK(
    std::string webSocketUrl,
    std::string authToken,
    std::string fleetId,
    std::string hostId,
    std::string processId
    ) {

    Aws::GameLift::Server::Model::ServerParameters serverParameters =
        Aws::GameLift::Server::Model::ServerParameters(
            webSocketUrl,
            authToken,
            fleetId,
            hostId,
            processId
        );

    Aws::GameLift::Server::InitSDKOutcome initSdkOutcome = Aws::GameLift::Server::InitSDK(serverParameters);

    // InitSDKの結果を確認
    if (!initSdkOutcome.IsSuccess()) {
        std::cerr << "GameLift SDK initialization failed: " << initSdkOutcome.GetError().GetErrorMessage() << std::endl;

    }

    std::cout << "GameLift SDK initialized successfully." << std::endl;

}
