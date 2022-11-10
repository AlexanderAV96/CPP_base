#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(const std::vector <double>& next) = 0;
	virtual double eval() const = 0;
	virtual const char* name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{ std::numeric_limits<double>::max() } {
	}

	void update(const std::vector <double> &next) override {
		for (int i = 0; i < next.size(); ++i){
			if (next[i] < m_min) {
				m_min = next[i];
			}
		}

		
	}

	double eval() const override {
		return m_min;
	}

	const char* name() const override {
		return "min";
	}

private:
	double m_min;
};

class big : public IStatistics {
public:
	big() : m_big{ std::numeric_limits<double>::min() } {
	}

	void update(const std::vector <double>& next) override {
		for (int i = 0; i < next.size(); ++i) {
			if (next[i] > m_big) {
				m_big = next[i];
			}
		}
	}

	double eval() const override {
		return m_big;
	}

	const char* name() const override {
		return "max";
	}

private:
	double m_big;
};

class Mean : public IStatistics {
private:
	double average;
public:
	double eval() const override {
		return average;
	}

	const char* name() const override {
		return "mean";
	}
	
	
	Mean() { average = 0; }

	void update(const std::vector <double>& next) override {
		for (int i = 0; i < next.size(); ++i) {
			average += next[i];
			}
		average /= next.size();
		}
	
	


};

class PCT : public IStatistics {
private:
	double pct90;
public:
	double eval() const override {
		return pct90;
	}
		const char* name() const override {
		return "PCT90";
	}


	PCT() { pct90 = 0; }

	void update(const std::vector <double>& next) override {
		
				
		int placeOfPCT = next.size() * 90/100;
		pct90 = next[placeOfPCT-1];
	}
};


class STD : public IStatistics {
private:
	double std;
public:
	double eval() const override {
		return std;
	}

	const char* name() const override {
		return "STD";
	}


	STD() { std = 0; }

	void update(const std::vector <double>& next) override {
		double avg=0, transit = 0;
		for (int i = 0; i < next.size(); ++i) {
			avg += next[i];
		}
		avg /= next.size();
		for (int i = 0; i < next.size(); ++i) {
			transit = (next[i]-avg)* (next[i] - avg);
			std += transit;
		
		}
		std /= next.size();
		std = sqrt(std);
	}




};



int main() {

	std::vector <double> arrayST;

	double val = 0;
	
	while (std::cin >> val) {

		arrayST.push_back(val);

	}

	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}



	for (int n = 0; n < arrayST.size(); n++) {
		std::cout << arrayST[n] << '\n';
	}
	//obyavlenie obiejtov klassov
	Min MN;
	big MX;
	Mean XX;
	STD YY;
	PCT GG;
	
	//sortirovka
	for (int i = 0; i < (arrayST.size() - 1); i++)
	{
		for (int j = (arrayST.size() - 1); j > i; j--)
		{
			if (arrayST[j - 1] > arrayST[j])
			{
				std::swap(arrayST[j - 1], arrayST[j]);
			}

		}
	}



	MN.update(arrayST);
	
	std::cout << MN.name() << " = " << MN.eval() << std::endl;
	
	MX.update(arrayST);

	std::cout << MX.name() << " = " << MX.eval() << std::endl;

	XX.update(arrayST);

	std::cout << XX.name() << " = " << XX.eval() << std::endl;

	YY.update(arrayST);

	std::cout << YY.name() << " = " << YY.eval() << std::endl;

	GG.update(arrayST);

	std::cout << GG.name() << " = " << GG.eval() << std::endl;


	return 0;
}