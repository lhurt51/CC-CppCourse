#include <iostream>
#include <chrono>
#include <future>
#include <string>

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

    while (true) {
        if (future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
			auto line = future.get();
			transform(line.begin(), line.end(), line.begin(), static_cast<int (*)(int)>(&std::toupper));
			if (line.find("Q") != std::string::npos) break;
            // Set a new line. Subtle race condition between the previous line
            // and this. Some lines could be missed. To alleviate, you need an
            // io-only thread. I'll give an example of that as well.
            future = std::async(std::launch::async, GetLineFromCin);
            std::cout << "you wrote " << line << std::endl;
        }

        // std::cout << "waiting..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
	return 0;
}
