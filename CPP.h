#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;
// TODO: Reference additional headers your program requires her

template <class T>
class Test {
protected:
	T sampleNumber;
	vector <T> numbers;

public:
	map <T, T> myMap;
	Test(T sampleNumber) : sampleNumber(sampleNumber) {}
	virtual void createSamples() = 0;
	virtual T getMin() = 0;
	virtual T getMax() = 0;
	virtual T getMean() = 0;
	virtual T getMedian() = 0;
	virtual vector<T> getHistogram() = 0;
	virtual ~Test() {}
};

template <class T>
class NormalTest : public Test<T> {
public:
	using Test<T>::sampleNumber;
	using Test<T>::numbers;
	NormalTest(T sampleNumber) :Test<T>(sampleNumber) {}
	virtual ~NormalTest() {};

	void createSamples() override;
	T getMin() override;
	T getMax() override;
	T getMean() override;
	T getMedian() override;
	vector<T> getHistogram() override;
};

template <class T>
class UniformTest : public Test<T> {
public:
	using Test<T>::sampleNumber;
	using Test<T>::numbers;
	using Test<T>::myMap;
	UniformTest(T sampleNumber) :Test<T>(sampleNumber) {}
	virtual ~UniformTest() {};
	void createSamples() override;
	T getMin() override;
	T getMax() override;
	T getMean() override;
	T getMedian() override;
	vector<T> getHistogram() override;
};

template <class T>
void runTests(Test<T>* pTest);

