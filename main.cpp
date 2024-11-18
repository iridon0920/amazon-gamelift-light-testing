#define GAMELIFT_USE_STD 1
#include <iostream>
#include <aws/gamelift/server/GameLiftServerAPI.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << Aws::GameLift::Server::GetSdkVersion().GetResult() << std::endl;

    return 0;
}
