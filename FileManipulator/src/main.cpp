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

std::string StrToUpper(std::string str)
{
    transform(str.begin(), str.end(), str.begin(), static_cast<int (*)(int)>(&std::toupper));
    return str;
}

int main(void)
{
    FileHandler FH = FileHandler();
    auto future = std::async(std::launch::async, GetLineFromCin);

	std::cout << "Type Q to Quit, S to Save progress, or R to Restore the save(Use return to exec): " << std::endl;
    while (true) {
        if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			auto line = future.get();
			line = StrToUpper(line);
			if (line.find("Q") != std::string::npos) break;
            else if (line.find("S") != std::string::npos)
                FH.SaveRead();
            else if (line.find("R") != std::string::npos)
                FH = FileHandler(FileHandler::RESTORE);
            // Execute code here after input for Saving and Restoration
            future = std::async(std::launch::async, GetLineFromCin);
        }
        // Default execution
        FH.ReadOneByte();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
	return 0;
}
