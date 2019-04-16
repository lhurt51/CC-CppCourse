#include <iostream>
#include <chrono>
#include <future>
#include <string>
#include <fstream>
#include "FileHandler.class.hpp"

std::string GetLineFromCin() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int main(int argc, char* argv[])
{
    FileHandler FH = FileHandler();

	if (argc == 1)
		std::cout << "Project Name: " <<  &argv[0][2] << std::endl << "Type Q to Quit, S to Save progress, or R to Restore the save(Use return to exec): " << std::endl;

	auto future = std::async(std::launch::async, GetLineFromCin);
    while (true) {
        if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			auto line = future.get();
			transform(line.begin(), line.end(), line.begin(), static_cast<int (*)(int)>(&std::toupper));
			if (line.find("Q") != std::string::npos) break;
            // Execute code here after input for Saving and Restoration
            future = std::async(std::launch::async, GetLineFromCin);
            std::cout << "you wrote " << line << std::endl;
        }
        // Default execution
        // std::cout << "waiting..." << std::endl;
        std::cout << FH.ReadOneByte() << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
	return 0;
}
