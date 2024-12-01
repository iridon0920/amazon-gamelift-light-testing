#define GAMELIFT_USE_STD 1
#include "GameLiftServer.h"

GameLiftServer::GameLiftServer() {
}

GameLiftServer::~GameLiftServer() {
}

void GameLiftServer::OnStartGameSession(Aws::GameLift::Server::Model::GameSession gameSession) {
    std::cout << "[GameLift]Callback: OnStartGameSession" << std::endl;
    Aws::GameLift::GenericOutcome outcome = 
        Aws::GameLift::Server::ActivateGameSession();
}

void GameLiftServer::OnProcessTerminate() {
    std::cout << "[GameLift]Callback: OnProcessTerminate" << std::endl;
    Aws::GameLift::GenericOutcome outcome = 
        Aws::GameLift::Server::ProcessEnding();

    Aws::GameLift::Server::Destroy();
}

bool GameLiftServer::OnHealthCheck() {
    std::cout << "[GameLift]Callback: OnHealthCheck" << std::endl;
    return true;
}

void GameLiftServer::OnUpdateGameSession(Aws::GameLift::Server::Model::UpdateGameSession gameSession) {
    std::cout << "[GameLift]Callback: OnUpdateGameSession" << std::endl;

}

void GameLiftServer::SetupSDK(
    std::string webSocketUrl,
    std::string authToken,
    std::string fleetId,
    std::string hostId,
    std::string processId,
    std::uint16_t port
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

    Aws::GameLift::Server::LogParameters logParams({"game.log"});
    Aws::GameLift::Server::ProcessParameters processParameters =
        Aws::GameLift::Server::ProcessParameters(
            std::bind(&GameLiftServer::OnStartGameSession, this, std::placeholders::_1),
            std::bind(&GameLiftServer::OnUpdateGameSession, this, std::placeholders::_1),
            std::bind(&GameLiftServer::OnProcessTerminate, this),
            std::bind(&GameLiftServer::OnHealthCheck, this),
            port,
            logParams
        );

    Aws::GameLift::GenericOutcome outcome = Aws::GameLift::Server::ProcessReady(processParameters);

}

void GameLiftServer::DestorySDK() {
    Aws::GameLift::GenericOutcome processEndingOutcome = Aws::GameLift::Server::ProcessEnding();
    Aws::GameLift::Server::Destroy();

    if (processEndingOutcome.IsSuccess()) {
        exit(0);
    } else {
        std::cout << "ProcessEnding() failed. Error: " << processEndingOutcome.GetError().GetErrorMessage();
        exit(-1);
    }
}