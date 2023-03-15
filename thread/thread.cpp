
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <mutex>
#include <future>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string& str);

void count_words(std::istream *stream, Counter&);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

std::mutex mtx;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    std::vector<std::thread> thr;
    std::vector<std::ifstream> str;
    std::vector <std::unique_ptr<std::ifstream>> ptr;
    std::vector<std::future <void>> thr2;
    std::vector<Counter> counvec;
    std::vector <std::unique_ptr<std::ifstream>> counptr;

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;

    counvec.reserve( argc -1);
    

    for (int i = 1; i < argc; ++i) {
      
        
         
        ptr.emplace_back(std::make_unique<std::ifstream>((argv[i])));

       
        if (!ptr.back().get()->is_open()) {
            std::cerr << "Failed to open file " << argv[i] << '\n';
            return EXIT_FAILURE;
        }
                                           
        counvec.emplace_back((freq_dict));
        thr2.emplace_back( std::async( std::launch::async , count_words , ( ptr.back( ).get( ) ) , ref ( counvec .back() )) );
        
    }
   

    for ( auto& i : thr2 ) i.get( );
   
    if ( counvec.size( ) > 1 )
    {
        for ( int i = 1; i < counvec.size();i++ ) // prohod vektorov
        {
 
            for ( auto it1 = counvec[i].begin( ); it1 != counvec[i].end( ); ++it1 ) // prohod map
            {

                auto it = counvec [ 0 ].find( it1->first );

                if ( it != counvec [ 0 ].end( ) )
                {
                    
                    it->second = it->second + it1->second;

                }
                else
                {
                    counvec [ 0 ].insert( make_pair ( it1->first , it1->second) );
                }
            }
        }
    }
        
    
    print_topk( std::cout , counvec[0] , TOPK );
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string& str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
        std::back_inserter(lower_str),
        [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream* stream, Counter& counter) {
   
    
    std::for_each(std::istream_iterator<std::string>(*stream),
        std::istream_iterator<std::string>(),
        [&counter](const std::string& s) { ++counter[tolower(s)]; });
    
}


void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto& rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator& pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                << '\n';
        });
}