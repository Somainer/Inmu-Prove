#include "helpers.h"
#include "time_testing_marco.h"

vector<int> getInts(string s){
    string digits(s.length(), ' ');
    copy_if(s.begin(), s.end(), digits.begin(), [](char c){
        return isdigit(c);
    });
    int len = digits.find_last_not_of(' ') + 1;
    vector<int> res(len);
    transform(digits.begin(), digits.begin() + len, res.begin(), [](char c){
        return c^'0';
    });
    return res;
}

int main(int argc, char **argv) {
    vector<int> left = {2,0,1,8},
    right = {1,1,4,5,1,4};
    int limit = NO_LIMIT;
    bool digest = !I_WANT_DIGEST;
    if(argc > 2 && argc < 5){
        left = getInts(argv[1]);
        right = getInts(argv[2]);
        if(argc == 4){
            auto arg = argv[3][0];
            digest = arg == 't' || arg == 'T' || arg == 'b';
            if(!digest){
                stringstream ss(argv[3]);
                ss >> limit;
            }
        }
        cout << "Proving: " << argv[1] << " == " << argv[2] << " limits " << limit << (digest?" brief":"") << endl;
    }
    inmu::startProve(left, right, limit, digest);
    return 0;
}