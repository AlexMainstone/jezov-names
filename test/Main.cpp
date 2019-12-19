#include<iostream>
#include "../include/Markov.hpp"
#include<fstream>
#include<streambuf>

int main() {
    std::ifstream t("../res/names.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    Markov markov(2, str);
    for(int i = 0; i < 100; i++)
        std::cout << markov.generate() << std::endl;;

}