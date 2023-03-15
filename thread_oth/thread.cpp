
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

using Counter = std::map<std::string , std::size_t>;

std::string tolower( const std::string& str );


Counter count_wordsnew( std::istream* stream );

void print_topk( std::ostream& stream , const Counter& , const size_t k );

std::mutex mtx;

int main( int argc , char* argv[] )
{
	if ( argc < 2 )
	{
		std::cerr << "Usage: topk_words [FILES...]\n";
		return EXIT_FAILURE;
	}

	std::vector<std::thread> thr;
	std::vector<std::ifstream> str;
	std::vector <std::unique_ptr<std::ifstream>> ptr;
	std::vector<std::future <Counter>> thr2;
	
	std::vector <std::unique_ptr<std::ifstream>> counptr;

	auto start = std::chrono::high_resolution_clock::now( );
	Counter freq_dict;




	for ( int i = 1; i < argc; ++i )
	{



		ptr.emplace_back( std::make_unique<std::ifstream>( ( argv [ i ] ) ) );


		if ( !ptr.back( ).get( )->is_open( ) )
		{
			std::cerr << "Failed to open file " << argv [ i ] << '\n';
			return EXIT_FAILURE;
		}


		thr2.emplace_back( std::async( std::launch::async , count_wordsnew , ( ptr.back( ).get( ) ) ) );

	}



	Counter tmp;
	freq_dict = thr2 [ 0 ].get( );


	for ( int i = 1; i < thr2.size( ); i++ )
	{


		tmp = thr2 [ i ].get( );


		{

			{

				for ( auto it1 = tmp.begin( ); it1 != tmp.end( ); ++it1 ) // prohod map
				{

					auto it = freq_dict.find( it1->first );

					if ( it != freq_dict.end( ) )
					{

						it->second = it->second + it1->second;

					}
					else
					{
						freq_dict.insert( make_pair( it1->first , it1->second ) );
					}
				}
			}
		}
	}

	print_topk( std::cout , freq_dict , TOPK );
	auto end = std::chrono::high_resolution_clock::now( );
	auto elapsed_ms = std::chrono::duration_cast< std::chrono::microseconds >( end - start );
	std::cout << "Elapsed time is " << elapsed_ms.count( ) << " us\n";
}

std::string tolower( const std::string& str )
{
	std::string lower_str;
	std::transform( std::cbegin( str ) , std::cend( str ) ,
					std::back_inserter( lower_str ) ,
					[] ( unsigned char ch ) { return std::tolower( ch ); } );
	return lower_str;
};


Counter count_wordsnew( std::istream* stream )
{
	Counter tmp;

	std::for_each( std::istream_iterator<std::string>( *stream ) ,
				   std::istream_iterator<std::string>( ) ,
				   [&tmp] ( const std::string& s ) { ++tmp [ tolower( s ) ]; } );
	return tmp;
}


void print_topk( std::ostream& stream , const Counter& counter , const size_t k )
{
	std::vector<Counter::const_iterator> words;
	words.reserve( counter.size( ) );
	for ( auto it = std::cbegin( counter ); it != std::cend( counter ); ++it )
	{
		words.push_back( it );
	}

	std::partial_sort(
		std::begin( words ) , std::begin( words ) + k , std::end( words ) ,
		[] ( auto lhs , auto& rhs ) { return lhs->second > rhs->second; } );

	std::for_each(
		std::begin( words ) , std::begin( words ) + k ,
		[&stream] ( const Counter::const_iterator& pair )
		{
			stream << std::setw( 4 ) << pair->second << " " << pair->first
				<< '\n';
		} );
}