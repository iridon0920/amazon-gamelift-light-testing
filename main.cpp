#define GAMELIFT_USE_STD 1
#include <iostream>
#include <aws/gamelift/server/GameLiftServerAPI.h>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    std::cout << Aws::GameLift::Server::GetSdkVersion().GetResult() << std::endl;

    // コマンドライン引数の数をチェック
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
        return 1;
    }

    std::cout << "GameLift SDK initialized successfully." << std::endl;

    return 0;
}