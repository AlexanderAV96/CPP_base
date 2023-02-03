﻿#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <execution>
#include <sstream>



const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string& str);

void count_words(std::string& stream, Counter&);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

std::mutex m;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    size_t nthreads = std::thread::hardware_concurrency();//!!!!
    if (!nthreads) { nthreads = 1; }//!!!!


   /* std::transform(std::execution::par, workVec.begin(), workVec.end(),
        workVec.begin(),
        [](double arg) { return std::tan(arg); });*/




    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;
    for (int i = 1; i < argc; ++i) {
        std::ifstream input{ argv[i] };
        if (!input.is_open()) {
            std::cerr << "Failed to open file " << argv[i] << '\n';
            return EXIT_FAILURE;
        }
        
        std::stringstream ss;
        while (input) {
            ss.put(input.get());
                      }
        std::string str;
        ss.str(str);

        count_words(str, freq_dict);//!!!
        //count_words(input, freq_dict);
    }

    


    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " ms\n";
}

std::string tolower(const std::string& str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
        std::back_inserter(lower_str),
        [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::string& str, Counter& counter)  {
  
   
    /// !!!!!!!!!!! popitka sdelat forward dlya string, kak opredilit i ispolzovat ne izvestno
    //// std::string::iterator ::iterator_category::bidirectional_iterator_tag bi ;
    
   
    
    


    /// !!!! 3333333 oshibka c2664
    std::for_each( str.begin(), str.end(),
        
        [&counter](const std::string& s) mutable { ++counter[tolower(s)]; });



    ///// 222222 oshibka forward iterator
    //   std::for_each(std::execution::par, std::istream_iterator<std::string>(stream),
    //    std::istream_iterator<std::string>(),
    //    [&counter](const std::string& s) {std::lock_guard<std::mutex> guard(m); ++counter[tolower(s)]; });
    //
   

    /// nachalnii variant
   /* std::for_each(std::istream_iterator<std::string>(stream),
        std::istream_iterator<std::string>(),
        [&counter](const std::string& s) { ++counter[tolower(s)]; });*/
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort( std::execution::par,
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto& rhs) { std::lock_guard<std::mutex> guard(m); return lhs->second > rhs->second; });

    std::for_each( 
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator& pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                << '\n';
        });
}