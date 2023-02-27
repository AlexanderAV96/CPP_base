// Read files and prints top k word by frequency

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
#include <thread>
#include <mutex>
#include <future>
#include <cstdio>

std::mutex mtx, mtx2;//!!!!!!!

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string& str);

void count_words(std::istream& stream, Counter&);

void print_topk(std::ostream& stream, const Counter&, const size_t k);


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;
    std::vector< std::ifstream*> book;
    std::vector<std::thread> ggggg;
    std::vector <std::unique_ptr<std::ifstream>> ptr;
                                                                    // std::vector<std::unique_ptr<std::vector<std::ifstream *>>> ptr;

    for (int i = 1; i < argc; ++i) {



        std::ifstream input{ argv[i] };
        


        if (!input.is_open()) {
            std::cerr << "Failed to open file " << argv[i] << '\n';
            return EXIT_FAILURE;
        }

        

                                                            // std::cout << input.rdbuf();// proveryem schitivanie
       book.emplace_back(std::move(input));
        std::istream* ptr2 = book.back();
        ptr.push_back(std::make_unique<std::ifstream>(ptr2));
        
                                                        //    std::ifstream* ptr = &input;
                                                         //   book.emplace_back((ptr));
                                                          // ptr.emplace_back((book.back()));


                                                        // ggggg.push_back(std::async(count_words, ref(input), ref(freq_dict)));// ne podhodit metod void
                                                        // ggggg.push_back(std::thread(std::move(count_words),ref(input), ref(freq_dict)));

                                                        // book[i].join();

                                                       // book.emplace_back(std::async(std::launch::async, count_words, ref(input), ref(freq_dict)));
                                                        /*if (i == 1){ std::thread pro1(count_words, ref(input), ref(freq_dict)); pro1.join();
                                                    }
                                                        if (i == 2) { std::thread pro2(count_words, ref(input), ref(freq_dict)); pro2.join(); }
                                                        if (i == 3) { std::thread pro3(count_words, ref(input), ref(freq_dict));pro3.join(); }*/
                                                        //book.push_back(std::async(count_words, ref(input),ref(freq_dict)));
                                                       // else
                                                       //name.clear();

        


        
       
                                                       //book.back().seekg(0, std::ios_base::beg);
                                                       //std::cout << book.back().rdbuf();//schitivaem iz vectora
                                                       // if(i<1) std::cout << book[place-1].rdbuf();
        ggggg.push_back(std::thread(std::move(count_words), ptr.back().release(), ref(freq_dict)));
                                                         //ggggg.push_back(std::thread(std::move(count_words), std::move(ref(input)), ref(freq_dict)));
                                                       // ggggg[i-1].join();
                                                     //count_words(input, freq_dict);
    }
   
    for (int i=0; i<ggggg.size()-1;i++) ggggg[i ].join();



    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::this_thread::get_id() << "end"<<'\n';
    
                                                        /*{
                                                            std::lock_guard<std::mutex> guard2(mtx2);
                                                            for (int i = 0;i < ggggg.size();++i) ggggg[i].join();
                                                        }*/

    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string& str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
        std::back_inserter(lower_str),
        [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter) {
   // std::cout << stream.rdbuf();

    std::cout << std::this_thread::get_id() << '\n';

        std::for_each(std::istream_iterator<std::string>(stream),
        std::istream_iterator<std::string>(),
            [&counter](const std::string& s) { std::mutex mtx; std::lock_guard guard(mtx); ++counter[tolower(s)]; });
        
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