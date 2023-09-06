#include "FinalProject-041044400.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <random>
#include <cmath>
using namespace std;

template <class T>
//create normal test sample number
void NormalTest<T>::createSamples() {
	random_device rd{};
	mt19937 gen{ rd() };
	normal_distribution<T> d{ 0, 10 };
	//clear any existing numbers in the vector before adding new ones
	this->numbers.clear();

	//add the numbers into the vector numbers
	for (int i = 0; i < this->sampleNumber; i++) {
		this->numbers.push_back(static_cast<T>(round(d(gen))));
	}
	//sort the numbers in ascend order
	sort(this->numbers.begin(), this->numbers.end());
}

template <class T>
T NormalTest<T>::getMin() {
	//return the first element in numbers
	return this->numbers[0];
}

template <class T>
T NormalTest<T>::getMax() {
	//return the last element in numbers
	return this->numbers[this->sampleNumber - 1];
}

template <class T>
//according to the sampleNumber is even or odd, use different method to calculate mean value
T NormalTest<T>::getMean() {
	int sum = 0;
	for (int i = 0; i < this->sampleNumber; i++) {
		sum = sum + numbers[i];
	}
	return sum / this->sampleNumber;
}

template <class T>
T NormalTest<T>::getMedian() {
	if (static_cast<int>(this->sampleNumber) % 2 == 1)
		return this->numbers[sampleNumber / 2];
	else
		return (this->numbers[sampleNumber / 2 - 1] + this->numbers[sampleNumber / 2]) / 2;
}

template <class T>
vector<T> NormalTest<T>::getHistogram() {
	vector<T> histogram(20, 0);
	T minValue = this->getMin();	
	T maxValue = this->getMax();	
	T startPoint;// the starting point used in map key value
	T bucketSize = (maxValue - minValue) / 20;

	for (int i = 0; i < 20; i++) {		
		vector <T> temp;	
		for (int j = 0; j < sampleNumber; j++) {		
			if (i<19) {
				startPoint = minValue + i * bucketSize;
				if (minValue + i * bucketSize <= this->numbers[j] && this->numbers[j] < minValue + (i + 1) * bucketSize) {					
					temp.push_back(numbers[j]);
				}
			}
			else if(i == 19) {
				startPoint = minValue + i * bucketSize;
				if (this->numbers[j] >= minValue + i * bucketSize) {					
					temp.push_back(numbers[j]);
				}
			}
		}
		//histogram.push_back(temp.size());
		histogram[i] = temp.size();
		this->myMap[startPoint] = histogram[i];
	}

	return histogram;
}


template <class T>
void UniformTest<T>::createSamples() {
	random_device rd{};
	mt19937 gen{ rd() };
	uniform_int_distribution<T> d{ -100, 100 };
	//add the numbers into the vector numbers
	for (int i = 0; i < this->sampleNumber; i++) {
		this->numbers.push_back(static_cast<T>(round(d(gen))));
	}
	sort(this->numbers.begin(), this->numbers.end());
}


template <class T>
T UniformTest<T>::getMin() {
	//return the first element in numbers
	return this->numbers[0];
}

template <class T>
T UniformTest<T>::getMax() {
	//return the last element in numbers
	return this->numbers[this->sampleNumber - 1];
}

template <class T>
T UniformTest<T>::getMean() {
	int sum = 0;
	for (int i = 0; i < this->sampleNumber; i++) {
		sum = sum + numbers[i];
	}
	return sum / this->sampleNumber;
}

template <class T>
T UniformTest<T>::getMedian() {
	if (this->sampleNumber % 2 == 1)
		return this->numbers[sampleNumber / 2];
	else
		return (this->numbers[sampleNumber / 2 - 1] + this->numbers[sampleNumber / 2]) / 2;
}

template <class T>
vector<T> UniformTest<T>::getHistogram() {

	vector<T> histogram(20, 0);
	T minValue = this->getMin();
	T maxValue = this->getMax();
	T startPoint;
	T bucketSize = (maxValue - minValue) / 20;
	for (int i = 0; i < 20; i++) {
		vector <T> temp;
		for (int j = 0; j < sampleNumber; j++) {
			if (i < 19) {
				startPoint = minValue + i * bucketSize;
				if (minValue + i * bucketSize <= this->numbers[j] && this->numbers[j] < minValue + (i + 1) * bucketSize) {
					temp.push_back(numbers[j]);
				}
			}
			else if (i == 19) {
				startPoint = minValue + i * bucketSize;
				if (this->numbers[j] >= minValue + i * bucketSize) {
					temp.push_back(numbers[j]);
				}
			}
		}
		histogram[i] = temp.size();
		this->myMap[startPoint] = histogram[i];
	}

	return histogram;
}

template <class T>
void runTest(Test<T>* pTest) {

	pTest->createSamples();

	cout << "Min: " << pTest->getMin() << endl;
	cout << "Max: " << pTest->getMax() << endl;
	cout << "Mean: " << pTest->getMean() << endl;
	cout << "Median: " << pTest->getMedian() << endl;
	vector<T> histogram = pTest->getHistogram();
	cout << "Histogram:" << endl;

	for (const auto& entry : pTest->myMap) {
		cout << "[" << entry.first << "] - Count: " << entry.second << endl;
	}
}

int main(int argc, const char* argv[]) {
	sf::RenderWindow window{ {800, 600},"TGUI window with sfml" };
	tgui::Gui gui{ window };
	gui.loadWidgetsFromFile("form.txt");


	auto topButton = gui.get<tgui::Button>("topButton");

	auto bottomButton = gui.get<tgui::Button>("bottomButton");

	topButton-> onClick([]() {
		using T = int;
		T num;
		cout << "You click on the RUN UNIFORM button" << endl;
		cout << "Please enter the number of sample to generate Uniform Distribution Test: " << endl;

		while (!(cin >> num) || num <= 0) {
			cout << "Sorry, invalid input. Please enter a positive integer: ";
			cin.clear();
			cin.ignore(256, '\n');
		}
		UniformTest<T> test(num);

		runTest(&test);
		});

	bottomButton->onClick([]() {
		using T = double;
		T num;
		cout << "You click on the RUN NORMAL button" << endl;
		cout << "Please enter the number of sample to generate Normal Distribution Test: " << endl;
		
		while (!(cin >> num) || num <= 0) {
			cout << "Sorry, invalid input. Please enter a positive integer: ";
			cin.clear();
			cin.ignore(256, '\n');
		}

		NormalTest<T> test(num);

		runTest(&test);
		});

	gui.mainLoop();
	return 0;
}

