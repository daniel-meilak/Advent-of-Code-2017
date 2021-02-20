#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// Forward function declaration
bool compare_letters(std::string word1, std::string word2);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);
    

    // number of valid passwords
    int count1 = 0;
    int count2 = 0;

    // check each password
    for (std::vector<std::string> line : input){

        bool valid1 = true;
        bool valid2 = true;

        // check each password
        size_t size = line.size();
        for (size_t i=0; i<size; i++){
            for (size_t j=i+1; j<size; j++){

                std::string pass1 = line[i];
                std::string pass2 = line[j];

                // only check if same size
                if (pass1.size() == pass2.size()){
                    
                    if (pass1 == pass2){
                        valid1 = false;
                        valid2 = false;
                        break;
                    }

                    // check anagrams for part 2
                    if (compare_letters(pass1, pass2) || !valid2){
                        valid2 = false;
                        break;
                    }
                }
            }

            // if two passwords are the same, dont check others
            if (!valid1){ break; }
        }

        if (valid1){ count1++; }
        if (valid2){ count2++; }
    }

    std::cout << "Answer (part 1): " << count1 << std::endl;
    std::cout << "Answer (part 2): " << count2 << std::endl;

    return 0;
}

// checks if characters and their freq in two strings are the same (anagrams)
bool compare_letters(std::string word1, std::string word2){
        
        // vector of pair for each letter and its frequency
        std::vector<std::pair<char,int>> freq1(26), freq2(26);

        // initialize freq, uses char ascii codes
        for (int i=0; i<26; i++){
            freq1[i] = {i+97,0};
            freq2[i] = {i+97,0};
        }

        // fill freq1 using word1
        for (const char & letter : word1){
            if (letter == '-'){ continue; }
            freq1[letter-97].second++;
        }

        // fill freq2 using word2
        for (const char & letter : word2){
            if (letter == '-'){ continue; }
            freq2[letter-97].second++;
        }

        return (freq1 == freq2);
}