#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#pragma once

class Data
{
	std::string numbers;

	virtual void pasrNumb( const std::string& tmp )
	{

		std::cout << "smthing goes wrong";

	};

	virtual void outputFile( )
	{

		std::cout << "smthing goes wrong 2";

	};

public:
	int menu( );

	std::string getNumb( ) { return numbers; };

	void setNumb( std::string Num ) { numbers = Num; };

	void fileInpNumb( );
	void fileInpNumb( char* tmp );


	~Data( ) = default;


};


class PVData :public Data
{

	std::vector<double> data;
	double rate = 0;
	double time = 0;
	double payPerMonth = 0;
	double pvAm = 0;

public:

	virtual void outputFile( )override;

	virtual void pasrNumb( const std::string& tmp ) override;
	
	void fincalculation( );

	friend std::ostream& operator << ( std::ostream& os , PVData& obj );
};


class FVData :public Data
{

	double rate = 0;
	double realamount = 0;
	double time = 0;
	double fvamount = 0;






public:

	virtual void outputFile( ) override;

	virtual void pasrNumb( const std::string& tmp ) override;
	
	void fincalculation( );
	
	friend std::ostream& operator << ( std::ostream& os , FVData& obj );

};


class FSData :public Data
{


	double finstate [ 51 ][ 3 ] = {
		//fs
		 { 1110,0,0 }, { 1120,0,0 }, { 1130,0,0 },{ 1140,0,0 }, { 1150,0,0 }, { 1160,0,0 }, { 1170,0,0 }, { 1180,0,0 }, { 1190,0,0 }, { 1100,0,0 }, //total nca 10
		 { 1210,0,0 }, { 1220,0,0 }, { 1230,0,0 }, { 1240,0,0 },{ 1250,0,0 }, { 1260,0,0 },{ 1200,0,0 },//cur assets 7
		 { 1600,0,0 },//assets total 1
		 { 1310,0,0 }, { 1320,0,0 },{ 1340,0,0 },{ 1350,0,0 }, { 1360,0,0 },{ 1370,0,0 },{ 1300,0,0 },//equity 7
		 { 1410,0,0 }, { 1420,0,0 },{ 1430,0,0 },{ 1450,0,0 },{ 1400,0,0 },//ncl 5

		 { 1510,0,0 }, { 1520,0,0 },{ 1530,0,0 },{ 1540,0,0 },{ 1550,0,0 },{ 1500,0,0 },//cur liab 6
		 { 1700,0,0 },//lian total 1
		 //oci
		  { 2110,0,0 },{ 2120,0,0 }, { 2100,0,0 },//gross profit
		  { 2210,0,0 },{ 2220,0,0 },{ 2000,0,0 },
		  { 2310,0,0 },{ 2320,0,0 },{ 2330,0,0 }, { 2340,0,0 }, { 2350,0,0 },{ 2300,0,0 }, // other
		  { 2410,0,0 },
		  { 2400,0,0 },//net profit

	};

	//fin ratios

	double currRat = 0;
	double acidRat = 0;
	double cashRat = 0;
	double debtToEquRat = 0;
	double interCoverRat = 0;
	double assetTurnRat = 0;
	double recievTurnRat = 0;
	double grossMargRat = 0;
	double returAssetsRat = 0;
	double returEquitRat = 0;
	bool netassets = false;


public:

	size_t sizeLine = 3;
	size_t sizeColumn = 51;

	virtual void outputFile( ) override;

	const double* operator[]( size_t i ) const { return finstate [ i ]; }

	double* operator[]( size_t i ) { return finstate [ i ]; }

	double* getfinstate( ) { return &finstate [ 0 ][ 0 ]; }

	const double* getfinstate( ) const { return &finstate [ 0 ][ 0 ]; }

	friend std::ostream& operator << ( std::ostream& os , FSData& obj );

	void checkFSforError( );

	void fincalculation( );

	virtual void pasrNumb( const std::string& tmp ) override;
	



};


int Data::menu( )
{

	int choose;

	std::cout << "1.Calculate Net Present Value (import data from file) \n";
	std::cout << "2.Calculate Future Value (import data from file)\n";
	std::cout << "3.Calculate key financial reporting ratios (import data from file)\n";



	std::cout << "Please enter the number of the action to continue, to exit, click 0\n";
	std::cin >> choose;// ubrat na vremya realiz
	//choose = 3;
	if ( choose < 0 || choose >3 ) { std::cout << "You enter wrong number, please try again, ïîâòîðèòå ïîïûòêó \n"; menu( ); }
	if ( choose == 0 ) return 0;


	return choose;
}

void FSData::pasrNumb( const std::string& tmp ){
	
	int count = 0;
	std::string inner;
	int countLineStr = 0;



	for ( int i = 0 , n = 0; i < tmp.size( ); ++i , ++n )
	{

		if ( tmp [ i ] == ' ' || tmp [ i ] == '(' || tmp [ i ] == ')' ) ++i;

		char test = tmp [ i ];

		/// obrabotka oshibki ne vernogo vvoda
		if ( std::isalpha( ( unsigned char ) test ) )
		{
			if ( test == ',' || test == ';' || test == '\n' ) break;
			else
			{
				std::cout << "wrong data, try again \n";
				menu( );
			}
		}


		if ( tmp [ i ] == ';' || i == ( tmp.size( ) - 1 ) || tmp [ i ] == '\n' )
		{

			if ( count == 0 )
			{

				finstate [ countLineStr ][ 0 ] = atof( inner.c_str( ) );

			}


			if ( count == 1 )
			{

				finstate [ countLineStr ][ 1 ] = atof( inner.c_str( ) );

			}


			if ( count == 2 )
			{


				finstate [ countLineStr ][ 2 ] = atof( inner.c_str( ) );

			}

			count++;
			inner.clear( );

		}

		if ( tmp [ i ] == ',' ) inner += '.';

		else if ( tmp [ i ] >= '0' && tmp [ i ] <= '9' || tmp [ i ] == '-' ) inner += tmp [ i ];

		if ( tmp [ i ] == '\n' )
		{
			++countLineStr;
			count = 0;
		}


	}

	checkFSforError( );
	fincalculation( );



}

void PVData::pasrNumb( const std::string& tmp ) 
{



	int count = 0;
	std::string inner;

	for ( int i = 0 , n = 0; i < tmp.size( ); ++i , ++n )
	{

		char test = tmp [ i ];

		/// obrabotka oshibki ne vernogo vvoda
		if ( std::isalpha( ( unsigned char ) test ) )
		{
			if ( test == ',' || test == ';' || test == '\n' ) break;
			else
			{
				std::cout << "wrong data, try again \n";
				exit( 0 );
			}
		}


		if ( tmp [ i ] == ';' || i == ( tmp.size( ) - 1 ) )
		{

			if ( count == 0 )
			{

				rate = atof( inner.c_str( ) );

			}


			if ( count == 1 )
			{

				time = atof( inner.c_str( ) );
			}


			if ( count == 2 )
			{

				inner += tmp [ i ];
				payPerMonth = atof( inner.c_str( ) );
			}

			count++;
			inner.clear( );

		}

		if ( tmp [ i ] == ',' ) inner += '.';

		else if ( tmp [ i ] >= '0' && tmp [ i ] <= '9' ) inner += tmp [ i ];

	}

	fincalculation( );
}

void FVData::pasrNumb( const std::string& tmp )
{

	int count = 0;
	std::string inner;

	for ( int i = 0 , n = 0; i < tmp.size( ); ++i , ++n )
	{

		char test = tmp [ i ];

		/// obrabotka oshibki ne vernogo vvoda
		if ( std::isalpha( ( unsigned char ) test ) )
		{
			if ( test == ',' || test == ';' || test == '\n' ) break;
			else
			{
				std::cout << "wrong data, try again \n";
				menu( );
			}
		}


		if ( tmp [ i ] == ';' || i == ( tmp.size( ) - 1 ) )
		{

			if ( count == 0 )
			{

				rate = atof( inner.c_str( ) );

			}


			if ( count == 1 )
			{

				time = atof( inner.c_str( ) );
			}


			if ( count == 2 )
			{

				inner += tmp [ i ];
				realamount = atof( inner.c_str( ) );
			}

			count++;
			inner.clear( );

		}

		if ( tmp [ i ] == ',' ) inner += '.';

		else if ( tmp [ i ] >= '0' && tmp [ i ] <= '9' ) inner += tmp [ i ];

	}

	fincalculation( );
};

void FSData::checkFSforError( )
{

	//correction
	//total nca
	finstate [ 9 ][ 1 ] = finstate [ 1 ][ 1 ] + finstate [ 2 ][ 1 ] + finstate [ 3 ][ 1 ] + finstate [ 4 ][ 1 ] + finstate [ 5 ][ 1 ] + finstate [ 6 ][ 1 ] + finstate [ 7 ][ 1 ] + finstate [ 8 ][ 1 ] + finstate [ 0 ][ 1 ];
	finstate [ 9 ][ 2 ] = finstate [ 1 ][ 2 ] + finstate [ 2 ][ 2 ] + finstate [ 3 ][ 2 ] + finstate [ 4 ][ 2 ] + finstate [ 5 ][ 2 ] + finstate [ 6 ][ 2 ] + finstate [ 7 ][ 2 ] + finstate [ 8 ][ 2 ] + finstate [ 0 ][ 2 ];
	//total ca
	finstate [ 16 ][ 1 ] = finstate [ 11 ][ 1 ] + finstate [ 12 ][ 1 ] + finstate [ 13 ][ 1 ] + finstate [ 14 ][ 1 ] + finstate [ 15 ][ 1 ] + finstate [ 10 ][ 1 ];
	finstate [ 16 ][ 2 ] = finstate [ 11 ][ 2 ] + finstate [ 12 ][ 2 ] + finstate [ 13 ][ 2 ] + finstate [ 14 ][ 2 ] + finstate [ 15 ][ 2 ] + finstate [ 10 ][ 2 ];
	//total assets
	finstate [ 17 ][ 1 ] = finstate [ 9 ][ 1 ] + finstate [ 16 ][ 1 ];
	finstate [ 17 ][ 2 ] = finstate [ 9 ][ 2 ] + finstate [ 16 ][ 2 ];
	//total equity
	finstate [ 24 ][ 1 ] = finstate [ 19 ][ 1 ] + finstate [ 20 ][ 1 ] + finstate [ 21 ][ 1 ] + finstate [ 22 ][ 1 ] + finstate [ 23 ][ 1 ] + finstate [ 18 ][ 1 ];
	finstate [ 24 ][ 2 ] = finstate [ 19 ][ 2 ] + finstate [ 20 ][ 2 ] + finstate [ 21 ][ 2 ] + finstate [ 22 ][ 2 ] + finstate [ 23 ][ 2 ] + finstate [ 18 ][ 2 ];
	//total ncl
	finstate [ 29 ][ 1 ] = finstate [ 26 ][ 1 ] + finstate [ 27 ][ 1 ] + finstate [ 28 ][ 1 ] + finstate [ 25 ][ 1 ];
	finstate [ 29 ][ 2 ] = finstate [ 26 ][ 2 ] + finstate [ 27 ][ 2 ] + finstate [ 28 ][ 2 ] + finstate [ 25 ][ 2 ];
	//total cl
	finstate [ 35 ][ 1 ] = finstate [ 31 ][ 1 ] + finstate [ 32 ][ 1 ] + finstate [ 33 ][ 1 ] + finstate [ 34 ][ 1 ] + finstate [ 30 ][ 1 ];
	finstate [ 35 ][ 2 ] = finstate [ 31 ][ 2 ] + finstate [ 32 ][ 2 ] + finstate [ 33 ][ 2 ] + finstate [ 34 ][ 2 ] + finstate [ 30 ][ 2 ];
	//total eq and liab
	finstate [ 36 ][ 1 ] = finstate [ 35 ][ 1 ] + finstate [ 29 ][ 1 ] + finstate [ 24 ][ 1 ];
	finstate [ 36 ][ 2 ] = finstate [ 35 ][ 2 ] + finstate [ 29 ][ 2 ] + finstate [ 24 ][ 2 ];
	//oci gross profit
	finstate [ 39 ][ 1 ] = finstate [ 37 ][ 1 ] + finstate [ 38 ][ 1 ];
	finstate [ 39 ][ 2 ] = finstate [ 37 ][ 2 ] + finstate [ 38 ][ 2 ];
	//oci net profit
	finstate [ 50 ][ 1 ] = finstate [ 39 ][ 1 ] + finstate [ 41 ][ 1 ] + finstate [ 43 ][ 1 ] + finstate [ 44 ][ 1 ]
		+ finstate [ 45 ][ 1 ] + finstate [ 46 ][ 1 ] + finstate [ 47 ][ 1 ] + finstate [ 49 ][ 1 ] + finstate [ 40 ][ 1 ];
	finstate [ 50 ][ 2 ] = finstate [ 39 ][ 2 ] + finstate [ 41 ][ 2 ] + finstate [ 43 ][ 2 ] + finstate [ 44 ][ 2 ]
		+ finstate [ 45 ][ 2 ] + finstate [ 46 ][ 2 ] + finstate [ 47 ][ 2 ] + finstate [ 49 ][ 2 ] + finstate [ 40 ][ 2 ];
	//profit before tax
	finstate [ 48 ][ 1 ] = finstate [ 50 ][ 1 ] - finstate [ 49 ][ 1 ];
	finstate [ 48 ][ 2 ] = finstate [ 50 ][ 2 ] - finstate [ 49 ][ 2 ];

	//check
	if ( finstate [ 17 ][ 1 ] != finstate [ 36 ][ 1 ] || finstate [ 17 ][ 2 ] != finstate [ 36 ][ 2 ] ) { std::cout << "wrong balance \n"; exit( 0 ); }




};

void FSData::fincalculation( )
{

	//liquidity
	//Current ratio = Current assets / Current liabilities

	if ( finstate [ 29 ][ 1 ] == 0 ) currRat = 0;
	else currRat = finstate [ 16 ][ 1 ] / finstate [ 29 ][ 1 ];

	//Acid-test ratio = Current assets – Inventories / Current liabilities

	if ( finstate [ 29 ][ 1 ] == 0 ) acidRat = 0;
	else acidRat = ( finstate [ 16 ][ 1 ] - finstate [ 10 ][ 1 ] ) / finstate [ 29 ][ 1 ];

	//Cash ratio = Cash and Cash equivalents / Current Liabilities

	if ( finstate [ 29 ][ 1 ] == 0 ) cashRat = 0;
	else cashRat = finstate [ 14 ][ 1 ] / finstate [ 29 ][ 1 ];

	//leverage
	//Debt to equity ratio = Total liabilities / Shareholder’s equity

	if ( finstate [ 24 ][ 1 ] == 0 )debtToEquRat = 0;
	else debtToEquRat = ( finstate [ 29 ][ 1 ] + finstate [ 35 ][ 1 ] ) / finstate [ 24 ][ 1 ];


	//Interest coverage ratio = Operating income / Interest expenses

	if ( finstate [ 45 ][ 1 ] == 0 )interCoverRat = 0;
	else interCoverRat = ( finstate [ 39 ][ 1 ] + finstate [ 40 ][ 1 ] + finstate [ 41 ][ 1 ] ) / finstate [ 45 ][ 1 ];

	//efficiency
	//Asset turnover ratio = Net sales / Average total assets


	assetTurnRat = finstate [ 37 ][ 1 ] / ( ( finstate [ 18 ][ 1 ] + finstate [ 18 ][ 2 ] ) / 2 );

	//Receivables turnover ratio = Net credit sales / Average accounts receivable

	recievTurnRat = finstate [ 37 ][ 1 ] / ( ( finstate [ 12 ][ 1 ] + finstate [ 12 ][ 2 ] ) / 2 );

	//profitability
	//Gross margin ratio = Gross profit / Net sales

	if ( finstate [ 37 ][ 1 ] == 0 )grossMargRat = 0;
	else grossMargRat = finstate [ 39 ][ 1 ] / finstate [ 37 ][ 1 ];

	//Return on assets ratio = Net income / Total assets

	returAssetsRat = finstate [ 50 ][ 1 ] / finstate [ 18 ][ 1 ];

	//Return on equity ratio = Net income / Shareholder’s equity

	if ( finstate [ 24 ][ 1 ] == 0 )returEquitRat = 0;
	else returEquitRat = finstate [ 50 ][ 1 ] / finstate [ 24 ][ 1 ];

	// net assets
	if ( finstate [ 24 ][ 1 ] > 0 ) netassets = true;


};

void FVData::fincalculation( )
{

	//PV=paypermonth*time*((1+rate)^(time/12)

	double tmprate = 1 + rate;

	fvamount = ( realamount ) *pow( ( 1 + rate ) , ( time / 12 ) );


}

void PVData::fincalculation( )
{

	//PV=paypermonth*time*((1+rate)^(time/12)

	double tmprate = 1 + rate;

	pvAm = ( payPerMonth * time ) / pow( ( 1 + rate ) , ( time / 12 ) );

}


void Data::fileInpNumb( )
{

	std::string tmpData , add;

	std::ifstream inputD( "data.csv" );

	if ( inputD.is_open( ) );

	else
	{

		std::cout << "file fo input does not exist";

		exit( 0 );
	}

	while ( 1 )
	{

		if ( inputD.eof( ) ) break;

		//inputD >> tmpData;

		std::getline( inputD , add );
		tmpData += add;
		tmpData += '\n';

	}

	this->setNumb( tmpData );



}

void Data::fileInpNumb( char* tmp )
{

	std::string tmpData , add;

	std::ifstream inputD( tmp );

	if ( inputD.is_open( ) );

	else
	{

		std::cout << "file for input does not exist";

		exit( 0 );
	}

	while ( 1 )
	{

		if ( inputD.eof( ) ) break;

		//inputD >> tmpData;

		std::getline( inputD , add );
		tmpData += add;
		tmpData += '\n';

	}

	this->setNumb( tmpData );



}

void PVData::outputFile( )
{

	std::ofstream outputD( "result.csv" , std::ios::out | std::ios::trunc );
	if ( !outputD )
	{



		std::cout << "file for output does not exist";

		exit( 0 );
	}


	outputD << "Input data: \n";
	outputD << "Rate:  ;" << std::setprecision( 2 ) << std::fixed << rate * 100 << "% \n";
	outputD << "Time in month:  ;" << std::setprecision( 0 ) << std::fixed << time << "; monthes\n";
	outputD << "Payment:  ;" << std::setprecision( 2 ) << std::fixed << payPerMonth << "; pay/month \n";
	outputD << "Output data : \n";

	outputD << "Present Value : ;" << std::setprecision( 2 ) << std::fixed << pvAm << '\n';

	outputD.close( );



};

void FVData::outputFile( )
{

	std::ofstream outputD( "result.csv" , std::ios::out | std::ios::trunc );
	if ( !outputD )
	{


		std::cout << "file for output does not exist";

		exit( 0 );
	}


	outputD << "Input data: \n";
	outputD << "Rate:  ;" << std::setprecision( 2 ) << std::fixed << rate * 100 << "% \n";
	outputD << "Time in month:  ;" << std::setprecision( 0 ) << std::fixed << time << "; monthes\n";
	outputD << "Total Payment:  ;" << std::setprecision( 2 ) << std::fixed << realamount << " \n";
	outputD << "Output data : \n";
	outputD << "Future Value : ;" << std::setprecision( 2 ) << std::fixed << fvamount << '\n';

	outputD.close( );


};

void FSData::outputFile( )
{

	std::ofstream outputD( "result.csv" , std::ios::out | std::ios::trunc );
	/*if ( !outputD )
	{


		std::cout << "file for output does not exist";

		exit( 0 );
	}*/

	outputD << "Input data: \n";
	outputD << "Number of line ;" << "Reporting year ;" << "Previous year \n";

	for ( int i = 0; i < 51; i++ )
	{

		outputD << std::setprecision( 0 ) << std::fixed << finstate [ i ][ 0 ] << ';';
		outputD << std::setprecision( 2 ) << std::fixed << finstate [ i ][ 1 ] << ";" << finstate [ i ][ 2 ] << '\n';

	}

	outputD << "Output data : \n";
	outputD << "Liquidity ratios : \n";
	outputD << "Current ratio:  ;" << std::setprecision( 4 ) << std::fixed << currRat << " \n";
	outputD << "Acid-test ratio:  ;" << std::setprecision( 4 ) << std::fixed << acidRat << " \n";
	outputD << "Cash ratio:  ;" << std::setprecision( 3 ) << std::fixed << cashRat << " \n";
	outputD << "Leverage ratios : \n";
	outputD << "Debt to equity ratio:  ;" << std::setprecision( 3 ) << std::fixed << debtToEquRat << " \n";
	outputD << "Interests coverage ratio:  ;" << std::setprecision( 3 ) << std::fixed << interCoverRat << " \n";
	outputD << "Efficiency ratios : \n";
	outputD << "Assets turnover ratio:  ;" << std::setprecision( 3 ) << std::fixed << assetTurnRat << " \n";
	outputD << "Recievable turnover ratio:  ;" << std::setprecision( 3 ) << std::fixed << recievTurnRat << " \n";
	outputD << "Profitability ratios : \n";
	outputD << "Gross margin ratio:  ;" << std::setprecision( 3 ) << std::fixed << grossMargRat << " \n";
	outputD << "Return on assets ratio:  ;" << std::setprecision( 3 ) << std::fixed << returAssetsRat << " \n";
	outputD << "Return on equity ratio:  ;" << std::setprecision( 3 ) << std::fixed << returEquitRat << "\n";
	if ( netassets ) outputD << "Net assets are positive";
	else outputD << "Net assets are negative!!!!!!!!";

	outputD.close( );



}

std::ostream& operator << ( std::ostream& os , PVData& obj )
{
	os << "Input data: \n";
	os << "Rate:  " << std::setprecision( 2 ) << std::fixed << obj.rate * 100 << "% \n";
	os << "Time in month:  " << std::setprecision( 0 ) << std::fixed << obj.time << " monthes\n";
	os << "Payment:  " << std::setprecision( 2 ) << std::fixed << obj.payPerMonth << " pay/month \n";
	os << "Output data : \n";

	os << "Present Value : " << std::setprecision( 2 ) << std::fixed << obj.pvAm << '\n';

	return os;
}

std::ostream& operator << ( std::ostream& os , FVData& obj )
{

	os << "Input data: \n";
	os << "Rate:  " << std::setprecision( 2 ) << std::fixed << obj.rate * 100 << "% \n";
	os << "Time in month:  " << std::setprecision( 0 ) << std::fixed << obj.time << " monthes\n";
	os << "Total Payment:  " << std::setprecision( 2 ) << std::fixed << obj.realamount << " \n";
	os << "Output data : \n";
	os << "Future Value : " << std::setprecision( 2 ) << std::fixed << obj.fvamount << '\n';


	return os;
}

std::ostream& operator << ( std::ostream& os , FSData& obj )
{

	os << "Number of line \t" << "Reporting year \t" << "Previous year \n";

	for ( int i = 0; i < 51; i++ )
	{

		os << std::setprecision( 0 ) << std::fixed << obj.finstate [ i ][ 0 ] << '\t' << '\t';
		os << std::setprecision( 2 ) << std::fixed << obj.finstate [ i ][ 1 ] << "       " << obj.finstate [ i ][ 2 ] << '\n';

	}

	os << "Output data : \n";
	os << "Liquidity ratios : \n";
	os << "Current ratio:  " << std::setprecision( 4 ) << std::fixed << obj.currRat << " \n";
	os << "Acid-test ratio: " << std::setprecision( 4 ) << std::fixed << obj.acidRat << " \n";
	os << "Cash ratio: " << std::setprecision( 2 ) << std::fixed << obj.cashRat << " \n";
	os << "Leverage ratios : \n";
	os << "Debt to equity ratio:  " << std::setprecision( 2 ) << std::fixed << obj.debtToEquRat << " \n";
	os << "Interests coverage ratio:  " << std::setprecision( 2 ) << std::fixed << obj.interCoverRat << " \n";
	os << "Efficiency ratios : \n";
	os << "Assets turnover ratio:  " << std::setprecision( 2 ) << std::fixed << obj.assetTurnRat << " \n";
	os << "Recievable turnover ratio:  " << std::setprecision( 2 ) << std::fixed << obj.recievTurnRat << " \n";
	os << "Profitability ratios : \n";
	os << "Gross margin ratio:  " << std::setprecision( 2 ) << std::fixed << obj.grossMargRat << " \n";
	os << "Return on assets ratio:  " << std::setprecision( 2 ) << std::fixed << obj.returAssetsRat << " \n";
	os << "Return on equity ratio:  " << std::setprecision( 2 ) << std::fixed << obj.returEquitRat << "\n";
	if ( obj.netassets ) os << "Net assets are positive";
	else os << "Net assets are negative!!!!!!!!";

	return os;
}