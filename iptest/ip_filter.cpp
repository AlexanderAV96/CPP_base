
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>

int main( int argc , char* argv[] )
{
	if ( argc > 2 )
	{
		std::cerr << "Parametres problem\n";
		return EXIT_FAILURE;
	}



	std::string tmpData , add;
	if ( argc == 2 )
	{
		std::ifstream inputD( argv [ 1 ] );

		if ( inputD.is_open( ) );

		else
		{

			std::cout << "file for input does not exist";

			exit( 0 );
		}

		while ( 1 )
		{

			if ( inputD.eof( ) ) break;


			std::getline( inputD , add );
			tmpData += add;
			tmpData += '\n';

		}
	}

	else
	{
		int count = 0;

		std::cout << "Enter number of adresses \n";
		std::cin >> count;
		std::cout << "Enter adress \n";
		for ( int i = 0; i < count; i++ )
		{
			std::cin.ignore( std::numeric_limits<std::streamsize>::max( ) , '\n' );
			std::getline( std::cin , add );
			//std::cin >> add;
			tmpData += add;
			tmpData += '\n';
		//	std::cin.clear( );
			//std::cin.sync( );
		}


	}



	std::vector <std::tuple<int , int , int , int , int , int , int> > iplist;
	std::tuple<int , int , int , int , int , int , int> tmptuple;
	std::string tmpstr;
	std::size_t place = 0;


	for ( int i = 0; i < tmpData.size( ); i++ )
	{

		if ( tmpData [ i ] == '.' )
		{

			if ( place == 0 ) { std::get <0>( tmptuple ) = atof( tmpstr.c_str( ) ); }
			if ( place == 1 ) { std::get <1>( tmptuple ) = atof( tmpstr.c_str( ) ); }
			if ( place == 2 ) { std::get <2>( tmptuple ) = atof( tmpstr.c_str( ) ); }
			place++;
			tmpstr.clear( );
			continue;
		}

		if ( tmpData [ i ] == '\t' )
		{

			if ( place == 3 ) { std::get <3>( tmptuple ) = atof( tmpstr.c_str( ) ); place++; }

			tmpstr.clear( );
		}




		if ( place == 4 )
		{



			if ( iplist.size( ) == 0 )
			{

				std::get <4>( tmptuple ) = 0;
				std::get <5>( tmptuple ) = 0;
				std::get <6>( tmptuple ) = 0;

				if ( std::get <0>( tmptuple ) == 1 ) std::get <3>( tmptuple ) = 1;
				if ( std::get <0>( tmptuple ) == 46 && std::get <1>( tmptuple ) == 70 ) std::get <4>( tmptuple ) = 1;
				if ( std::get <0>( tmptuple ) == 46 || std::get <1>( tmptuple ) == 46 || std::get <2>( tmptuple ) == 46 || std::get <3>( tmptuple ) == 46 ) std::get <6>( tmptuple ) = 1;

				iplist.emplace_back( tmptuple );


			}


			else
			{


				if ( std::get <0>( tmptuple ) == 1 ) std::get <4>( tmptuple ) = 1;
				if ( std::get <0>( tmptuple ) == 46 && std::get <1>( tmptuple ) == 70 ) std::get <5>( tmptuple ) = 1;
				if ( std::get <0>( tmptuple ) == 46 || std::get <1>( tmptuple ) == 46 || std::get <2>( tmptuple ) == 46 || std::get <3>( tmptuple ) == 46 ) std::get <6>( tmptuple ) = 1;

				auto iter = iplist.begin( );

				for ( ; iter < iplist.end( ); iter++ )
				{

					if ( std::get <0>( *iter ) > std::get <0>( tmptuple ) )
					{

						if ( iter == ( --iplist.end( ) ) ) { iplist.push_back( tmptuple ); break; }

						continue;

					}

					else if ( std::get <0>( *iter ) == std::get <0>( tmptuple ) )
					{

						if ( std::get <1>( *iter ) > std::get <1>( tmptuple ) )
						{

							if ( iter == ( --iplist.end( ) ) ) { iplist.push_back( tmptuple ); break; }
							continue;

						}

						else if ( std::get <1>( *iter ) == std::get <1>( tmptuple ) )
						{
							if ( std::get <2>( *iter ) > std::get <2>( tmptuple ) )
							{
								if ( iter == ( --iplist.end( ) ) ) { iplist.push_back( tmptuple ); break; }
								continue;

							}

							else if ( std::get <2>( *iter ) == std::get <2>( tmptuple ) )
							{

								if ( std::get <3>( *iter ) > std::get <3>( tmptuple ) )
								{
									if ( iter == ( --iplist.end( ) ) ) { iplist.push_back( tmptuple ); break; }
									continue;

								}
								else if ( std::get <3>( *iter ) == std::get <3>( tmptuple ) )
								{

									if ( std::get <4>( *iter ) > std::get <4>( tmptuple ) )
									{
										if ( iter == ( --iplist.end( ) ) ) { iplist.push_back( tmptuple ); break; }
										continue;

									}

									else if ( std::get <3>( *iter ) == std::get <3>( tmptuple ) )
									{

										iplist.insert( iter , tmptuple );

										break;

									}
								}
							}
						}
					}



					else
					{

						iplist.insert( iter , tmptuple );
						break;

					}
				}
			}

			place = 0;

		}



		if ( tmpData [ i ] == '\n' )
		{
			tmptuple = { 0,0,0,0,0,0,0 };
			tmpstr.clear( );
		}

		if ( tmpData [ i ] != '\t' )
		{
			if ( tmpData [ i ] == '\n' )  tmpData [ i ] = ' ';

			else tmpstr += tmpData [ i ];
		}


	}
	for ( auto i : iplist )
	{

		std::cout << std::get <0>( i ) << '.' << std::get <1>( i ) << '.' << std::get <2>( i ) << '.' << std::get <3>( i ) << '\n';
	}

	for ( auto i : iplist )
	{
		if ( std::get <4>( i ) == 1 )
		{
			std::cout << std::get <0>( i ) << '.' << std::get <1>( i ) << '.' << std::get <2>( i ) << '.' << std::get <3>( i ) << '\n';
		}
	}

	for ( auto i : iplist )
	{
		if ( std::get <5>( i ) == 1 )
		{
			std::cout << std::get <0>( i ) << '.' << std::get <1>( i ) << '.' << std::get <2>( i ) << '.' << std::get <3>( i ) << '\n';
		}
	}

	for ( auto i : iplist )
	{
		if ( std::get <6>( i ) == 1 )
		{
			std::cout << std::get <0>( i ) << '.' << std::get <1>( i ) << '.' << std::get <2>( i ) << '.' << std::get <3>( i ) << '\n';
		}
	}


}
