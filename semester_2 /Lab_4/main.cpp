#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



class StateMachine {
private:
    std::vector<std::vector<int>> transition_table;
    std::vector<std::vector<int>> out_table;

    std::vector<char> alphabet = {'a', 'b', 'c', 'd'};
public:
    StateMachine(std::vector<std::vector<int>>, std::vector<std::vector<int>>);
    bool checker(std::string word);

};


int main() {
    std::vector<std::vector<int>> transition_table ={
        {1,2,7,4,5,7,3,7,8},
        {1,2,3,4,5,6,3,7,8},
        {1,2,3,4,5,6,3,7,8},
        {1,2,3,4,5,6,3,7,8},
        {0,0,0,1,1,1,1,0,1}
    };
    std::vector<std::vector<int>> output_table ={
       {0,0,0,1,1,0,1,0,1},
       {0,0,1,1,1,1,1,0,1},
       {0,0,1,1,1,1,1,0,1},
       {0,0,1,1,1,1,1,0,1},
       {0,0,0,1,1,1,1,0,1}
    };
    

    StateMachine* machine = new StateMachine(transition_table, output_table);

    std::string word = "abaabcaba";

    bool isRecognized = machine->checker(word);

    std::cout << "A word to recognize: "<< word << std::endl;

    std::cout << "The result: " << isRecognized << std::endl;

    return 0;
}

StateMachine::StateMachine(std::vector<std::vector<int>> tt, std::vector<std::vector<int>> ot) {
    this->transition_table = tt;
    this->out_table = ot;
    
}

bool StateMachine::checker(std::string word) {
    auto al = this->alphabet;
    al.push_back(' '); // marker of string's ending
    
    int state = 0; // beginning state is 0 

    bool isRecognized = false;

    int idx = 0;

    word = word+' '; 

    while (idx < word.length()) {
        char c = word[idx];

        if (std::find(al.begin(), al.end(), c) == al.end()) {
            std::cout << "Unexpected character" << std::endl;
            return false;
        }
        auto it = std::find(al.begin(), al.end(), c);
        int c_idx =  it - al.begin();

        isRecognized = (bool) out_table[c_idx][state];

        state = transition_table[c_idx][state]; 

        idx++;
    }
    return isRecognized;
}


