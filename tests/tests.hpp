#pragma once
#include "../include/verse.hpp"
#include "../prototypes/procedures.hpp"
#include <exception>
#include <iostream>
#include <functional>
#include <vector>

struct TestFailure { };

inline std::vector<std::string> failed_tests;
inline std::vector<std::string> succeded_tests;
inline std::vector<std::string> performed_tests;

inline void expect(bool condition){
    if (not condition) throw TestFailure { };
}

inline void perform_test(std::string test_name, std::function<void(void)> test_procedure){
    performed_tests.push_back(test_name);
    try { test_procedure(); } catch(...) { 
        std::cout << bold_red("FAILURE: ") << yellow(test_name) << std::endl; 
        failed_tests.push_back(test_name);
        return;
    }
    std::cout << bold_green("SUCCESS: ") << purple(test_name) << std::endl; 
    succeded_tests.push_back(test_name);
}

inline void show_test_recap(){
    std::cout << "success: " << succeded_tests.size() << " / " << performed_tests.size() << std::endl;
    std::cout << "failure: " << failed_tests.size() << " / " << performed_tests.size() << std::endl;
    if (performed_tests.size() > 30 and failed_tests.size() > 0) {
        std::cout << std::endl << "failed tests are: " << std::endl;
        for (const std::string& failed : failed_tests){
            std::cout << red(failed) << "\n";
        }
    }
}
