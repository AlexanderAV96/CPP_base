#include "Raschet.h"





int main( int argc , char* argv[] )
{
	if ( argc > 2 )
	{
		std::cerr << "Too many parametres\n";
		return EXIT_FAILURE;
	}

	int choose;

	Data test;

	choose = test.menu( );


	while ( choose != 0 )
	{
		switch ( choose )
		{

			case 1: {

					if (argc == 2){ test.fileInpNumb( argv[1] ); }
					
					if ( argc < 2 ) { test.fileInpNumb( ); }

					PVData incmData;

					incmData.pasrNumb( test.getNumb( ) );

					std::cout << incmData;

					incmData.outputFile( );

					choose = 0;

					break; }

			case 2: {

					if ( argc == 2 ) { test.fileInpNumb( argv[1] ); }

					if ( argc < 2 ) { test.fileInpNumb( ); }

					FVData incmData;

					incmData.pasrNumb( test.getNumb( ) );

					std::cout << incmData;

					incmData.outputFile( );

					choose = 0;

					break; }

			case 3: {

					if ( argc == 2 ) { test.fileInpNumb( argv [ 1 ] ); }

					if ( argc != 2 ) { test.fileInpNumb( ); }

					FSData incmData;

					incmData.pasrNumb( test.getNumb( ) );
													
					std::cout << incmData;

					incmData.outputFile( );

					choose = 0;

					break; }

			case 4:

				break;

			case 5:

				break;

			case 6:

				break;

		}





	}


}


