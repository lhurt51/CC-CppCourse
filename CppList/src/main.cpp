#include <iostream>
#include <string>
#include "LinkedList.class.hpp"

int main(void)
{
    List<int> linkList = List<int>();

    linkList.Push(1);
    linkList.Push(2);
    linkList.Push(3);
    linkList.Push(4);
    linkList.Push(5);
    std::cout << "Is Empty: " << ((linkList.Empty()) ? "true" : "false") << std::endl;
    std::cout << linkList << std::endl;
    linkList.Remove(4);
    linkList.Insert(2, 8);
    linkList.Push(26);
    linkList.Pop();
    std::cout << "Is Empty: " << ((linkList.Empty()) ? "true" : "false") << std::endl;
    std::cout << linkList << std::endl;
    linkList.Clear();
    std::cout << "Is Empty: " << ((linkList.Empty()) ? "true" : "false") << std::endl;
    std::cout << linkList << std::endl;

    List<float> linkListf = List<float>();

    linkListf.Push(1.0f);
    linkListf.Push(2.0f);
    linkListf.Push(3.0f);
    linkListf.Push(4.0f);
    linkListf.Push(5.0f);
    std::cout << "Is Empty: " << ((linkListf.Empty()) ? "true" : "false") << std::endl;
    std::cout << linkListf << std::endl;
    linkListf.Remove(4);
    linkListf.Insert(2, 8.34f);
    linkListf.Push(26.7823f);
    linkListf.Pop();
    std::cout << "Is Empty: " << ((linkListf.Empty()) ? "true" : "false") << std::endl;
    std::cout << linkListf << std::endl;
    linkListf.Clear();
    std::cout << "Is Empty: " << ((linkListf.Empty()) ? "true" : "false") << std::endl;
    std::cout << linkListf << std::endl;
	return 0;
}
