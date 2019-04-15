#include <iostream>
#include <chrono>
#include <future>
#include <string>
#include <fstream>

std::string GetLineFromCin() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
		std::cout << "Project Name: " <<  &argv[0][2] << std::endl;
	auto future = std::async(std::launch::async, GetLineFromCin);
    std::string line;
    std::ifstream fin;
    fin.open("../res/input.txt");
    while (fin)
    {
        getline(fin, line);
        std::cout << line << std::endl;
    }
    fin.close();
    while (true) {
        if (future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
			auto line = future.get();
			transform(line.begin(), line.end(), line.begin(), static_cast<int (*)(int)>(&std::toupper));
			if (line.find("Q") != std::string::npos) break;
            // Execute code here after input for Saving and Restoration
            future = std::async(std::launch::async, GetLineFromCin);
            std::cout << "you wrote " << line << std::endl;
        }
        // Default execution
        // std::cout << "waiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
	return 0;
}
