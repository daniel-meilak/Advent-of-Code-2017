#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<cstdlib>
#include"../../Utils/utils.h"

// forward function declarations
std::vector<std::vector<std::vector<std::string>>> split_pic(const std::vector<std::string> &picture, const int &n);
std::vector<std::string> combine_pic(std::vector<std::vector<std::vector<std::string>>> &split_pic);
void find_apply_rule(std::vector<std::string> &picture,const std::unordered_map<std::string, std::vector<std::string>> &rules);
std::string to_key(const std::vector<std::string> &pic);
std::vector<std::string> rotate(const std::vector<std::string> &matrix, const char &c);
std::vector<std::string> flip(std::vector<std::string> matrix);
int enhance(std::vector<std::string> picture, const std::unordered_map<std::string, std::vector<std::string>> &rules, const int &iter);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", "=>"};
    std::vector<std::vector<std::string>> input = read_input_2D("input_21", delimiters);

    // map of rules
    std::unordered_map<std::string, std::vector<std::string>> rules;

    // fill map
    for (const std::vector<std::string> &line : input){

        // create picture piece value
        std::vector<std::string> pic = split(line[1], "/");

        rules[line[0]] = pic;
    }

    // starting picture
    std::vector<std::string> picture = {".#.","..#","###"};

    std::cout << "Answer (part 1): " << enhance(picture,rules,5)  << std::endl;
    std::cout << "Answer (part 2): " << enhance(picture,rules,18) << std::endl;

    return 0;
}

// takes a starting picture and 'enhances' it by divinding into pieces and increasing the size of each piece
// for iter iterations, by using the conversions provided in the map rules.
int enhance(std::vector<std::string> picture, const std::unordered_map<std::string, std::vector<std::string>> &rules, const int &iter){

    for (int i=0; i<iter; i++){
        int size = picture.size();

        // split image
        std::vector<std::vector<std::vector<std::string>>> split_picture;

        // check which rule to apply and split picture
        if      (size % 2 == 0){ split_picture = split_pic(picture,2); }
        else if (size % 3 == 0){ split_picture = split_pic(picture,3); }

        // apply rules
        size_t pieces = split_picture.size();
        for (size_t i=0; i<pieces; i++){
            for (size_t j=0; j<pieces; j++){
                find_apply_rule(split_picture[i][j], rules);
            }
        }

        // recombine picture
        picture = combine_pic(split_picture);
    }

    // count on pixels after iterations
    size_t size = picture.size();
    int count = 0;
    for (size_t i=0; i<size; i++){
        for (size_t j=0; j<size; j++){
            if (picture[i][j]=='#'){ count++; }
        }
    }

    return count;
}

// split a picture into evenly sized sub-pictures (2*2 or 3*3)
std::vector<std::vector<std::vector<std::string>>> split_pic(const std::vector<std::string> &picture, const int &n){

    size_t max = picture.size()/n;
    // 4D vector, 2D grid of 2D grids
    std::vector<std::vector<std::vector<std::string>>> split_picture(max,std::vector<std::vector<std::string>>(max, std::vector<std::string>(n, std::string(n,' '))));

    // Overall x and y
    for (size_t i=0; i<max; i++){
        for (size_t j=0; j<max; j++){
            
            // Sub picture x and y
            size_t max_k = (n*i)+(n-1);
            for (size_t k=n*i; k<=max_k; k++){
                
                size_t max_l = (n*j)+(n-1);
                for (size_t l=n*j; l<=max_l; l++){ 

                    split_picture[i][j][k%n][l%n] = picture[k][l];
                }
            }
        }
    }

    return split_picture;
}

// combine split picture into whole
std::vector<std::string> combine_pic(std::vector<std::vector<std::vector<std::string>>> &split_pic){

    size_t max     = split_pic.size();
    size_t sub_max = split_pic[0][0].size();
    std::vector<std::string> comb_pic(max*sub_max);

    // Overall x and y
    for (size_t i=0; i<max; i++){
        for (size_t j=0; j<max; j++){

            // Sub picture y
            for (size_t k=0; k<sub_max; k++){
                comb_pic[(sub_max*i)+k] += split_pic[i][j][k];
            }
        }
    }

    return comb_pic;
}

// find rule in rules that applies to pic and apply
void find_apply_rule(std::vector<std::string> &picture,const std::unordered_map<std::string, std::vector<std::string>> &rules){

    // rotate and check each way
    for (int i=0; i<4; i++){

        // first rotate
        picture = rotate(picture, 'r');

        // search for rule and apply if found
        auto it = rules.find(to_key(picture));

        // found, replace pic with rule result
        if (it!=rules.end()){
            picture = (*it).second;
            return;
        }
    }

    // if all rotations fail, flip and rotate again
    picture = flip(picture);

    // rotate and check each way
    for (int i=0; i<4; i++){

        // first rotate
        picture = rotate(picture, 'r');

        // search for rule and apply if found
        auto it = rules.find(to_key(picture));

        // found, replace pic with rule result
        if (it!=rules.end()){
            picture = (*it).second;
            return;
        }
    }

    // if no rule is found output error
    std::cout << "No rule found for picture" << std::endl;
    std::exit(EXIT_FAILURE);
}

// turn picture piece into key for map
std::string to_key(const std::vector<std::string> &pic){

    std::string key;

    for (const std::string &line : pic){
        key += line + "/";
    }

    key.pop_back();
    return key;
}

// rotate matrix 90 deg clockwise (r) or anticlockwise (l)
std::vector<std::string> rotate(const std::vector<std::string> &matrix, const char &c){

    size_t n = matrix.size();
    std::vector<std::string> rotated(n, std::string(n,' '));

    for (size_t i=0; i<n; i++){
        for (size_t j=0; j<n; j++){

            if (c=='r'){ rotated[i][j] = matrix[n-j-1][i]; }
            else if (c=='l'){ rotated[i][j] = matrix[j][n-i-1]; }
        }
    }

    return rotated;
}

// flip matrix horizontally
std::vector<std::string> flip(std::vector<std::string> matrix){

    for (std::string &line : matrix){
        std::reverse(line.begin(), line.end());
    }

    return matrix;
}