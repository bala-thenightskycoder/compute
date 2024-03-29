#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

// Main function
int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cout << "Usage: compute <threshold> <limit>" << std::endl;
        exit(1);
    }
    double threshold = atof(argv[1]);
    double limit = atof(argv[2]);

    // Input values range check
    if(!(threshold >= 0.0) || !(threshold <= 1000000000.0))  {
        std::cout << "ERR: Threshold parameter is not between 0.0 and 1000000000.0(inclusive)" << std::endl; 
        exit(1);
    }

    if(!(limit >= 0.0) || !(limit <= 1000000000.0)) {
        std::cout << "ERR: Limit parameter is not between 0.0 and 1000000000.0" << std::endl;
        exit(1);    
    }

    double inputValues;
    int numOfLines = 0;
    std::vector <double> inputStorage;

    while (std::cin >> inputValues) {
        if(inputValues >= 0.0 && inputValues <= 1000000000.0) {
            inputStorage.push_back(inputValues);
            numOfLines = numOfLines + 1;
        } else {
            std::cout << "ERR: Input value not in the given range in the line number: " << numOfLines << std::endl;
            exit(1);
        }
    }

    if(!(numOfLines >= 0) || !(numOfLines <= 100)) {
        std::cout << "ERR: Number of lines in the file exceeds 100." << std::endl;
        exit(1);
    }

    std::vector <double> outputVec;
    double cumulative_sum = 0;
    bool check_limit_attained = false;
    for(auto it = inputStorage.begin(); it != inputStorage.end(); ++it) {
        if(*it < threshold || check_limit_attained) {
            outputVec.push_back(0);
        } else {
            cumulative_sum = cumulative_sum + *it;
            if(cumulative_sum > limit) {
                outputVec.push_back(*it - (cumulative_sum - limit));
                cumulative_sum = cumulative_sum - (cumulative_sum - limit);
                check_limit_attained = true;
            } else {
                 outputVec.push_back(*it - threshold);
                 cumulative_sum = cumulative_sum - threshold;
            }
        }
    }
    int precision = std::numeric_limits<double>::max_digits10;
    for(auto it = outputVec.begin(); it != outputVec.end(); ++it) {
        std::cout << std::setprecision(precision) << *it << std::endl;
    }
    std::cout << std::setprecision(precision) << cumulative_sum << std::endl;

    return 0;
}
