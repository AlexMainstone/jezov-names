#pragma once

#include<string>
#include<map>
#include<vector>
#include<utility>
#include<sstream>
#include<locale>
#include<iostream>

using namespace std;

class Markov {
    public:
        Markov(int n, std::string input) : n(n) {
            srand(time(0));
            add(input);
        }

        void add(std::string input) {
            // To lower
            std::string intext = "";
            for(int i = 0; i < input.length(); i++) {
                char s = tolower(input.at(i));
                if(s < 97 || s > 122) {
                    continue;
                }
                intext += s;
            }

            std::stringstream test_stream(intext);
            std::string word;
            for(int i = 0; test_stream >> word; i++) {

                // iterate through word
                for(int j = 0; j < word.length() - n; j++) {
                    std::string subs = word.substr(j, n);
                    char next = word.at(j+n);
                    if(markov_map[subs].empty()) {
                        std::pair<char, int> p;
                        p.first = next;
                        p.second = 1;
                        markov_map[subs].push_back(p);
                    } else {
                        bool exist = false;
                        for(auto &a : markov_map[subs]) {
                            if(a.first == next) {
                                exist = true;
                                a.second++;
                            }
                        }
                        if(!exist) {
                            std::pair<char, int> p;
                            p.first = next;
                            p.second = 1;
                            markov_map[subs].push_back(p);
                        }
                    }
                }
            }
        }

        std::string generate(std::string beginning = "", int min = 2, int max = 6) {
            if(beginning == "") {
                beginning = "nn";
                while(!(isvowel(beginning.at(0)) || isvowel(beginning.at(1)))) {
                    auto it = markov_map.begin();
                    std::advance(it, rand() % markov_map.size());
                    beginning = it->first;
                }
            }
            std::string result = beginning;

            for(int i = 0; i < rand() % max + min; i++) {
                auto v = markov_map[result.substr(result.length()-2)];
                if(v.empty()) {
                    if(result.length() <= min) {
                        return generate();
                    }
                    break;
                }

                std::vector<char> dev;
                for(int j = 0; j < v.size(); j++) {
                    for(int c = 0; c < v[j].second; c++) {
                        dev.push_back(v[j].first);
                    }
                }
                result += dev[rand() % dev.size()];
            }
            return result;
        }
    private:
        bool isvowel(char c) { return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'); }
        std::map<std::string, std::vector<std::pair<char, int>>> markov_map;
        const int n;
};