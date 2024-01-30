#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//Richard Auch
//code lab challenge 30 Jan 2024

/*
* Given an interger array of numbers, find the contiguous subarray (containing at least one number) that has the largest sum and returns both its sum and the starting and ending indicies of this subarray
* 
* Ex: nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 } -> sum = 6, indices [3, 6]
*               0  1  2  [3   4  5  6]  7  8
* 
* Challenge constraints: 
*	array size: can contain up to 10^6 integers
*	number range: -2147 to 2147
*
*/

void findSubArray(vector<int>);
void inchWorm(vector<int>);

void findPositiveSubArrays(vector<int>);
int getVectorSumWithIndicies(vector<int>);
int getVectorSum(vector<int>);
void groupSubArraysByValue(vector<int>);

int main() {
	vector<int> testData = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	findSubArray(testData); 
}

void runAll() {

	vector<vector<int>> testData;
	testData.push_back({ -2, 1, -3, 4, -1, 2, 1, -5, 4 });						//answer [3,6]:6
	testData.push_back({ 5, -12, 3, 2, 9, -10, 4 });							//answer [2,4]:14
	testData.push_back({ 120, -10, -3, -4, -32, -1, -46, -2, -1, -5, 120 });	//answer [0,10]:136
	testData.push_back({ -21, 1, -3, 4, -1, 2, 1, 5, -46 });					//answer [3,7]:11
	testData.push_back({ 7, 10, -3, 4, -32, 1, -46, 2, 1, 5, -4 });				//answer[0,3]:18

	for (int i = 0; i < testData.size(); i++)
	{
		findSubArray(testData[i]); // this can handle the first 4 examples but not the others
	}

}


void groupSubArraysByValue(vector<int> inputVector) {

	vector<vector<int>> vectorGroups;
	int left = 0;
	int right = 0;

	for (int i = 0; i < inputVector.size() - 1; i++) {
		vector<int> temp;
		if (!temp.empty()) {
			if (temp[0] >= 0) {
				if (inputVector[i] >= 0) {
					temp.push_back(inputVector[i]);
					right = i;
				}
				else {
					temp.push_back(left);
					temp.push_back(right);
					vectorGroups.push_back(temp);
					temp.clear();
				}
			}
			else {
				if (inputVector[i] < 0) {
					temp.push_back(inputVector[i]);
					right = i;
				}
				else {
					temp.push_back(left);
					temp.push_back(right);
					vectorGroups.push_back(temp);
					temp.clear();
				}
			}
		}
	}

}

//this doesn't handle cases like the first sample where the -5 negates
void findPositiveSubArrays(vector<int> inputVector) {

	//vector<int> sample = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };	//answer [3,6]

	vector<vector<int>> arrays;
	int left = 0;
	int right = 0;
	int sum = 0;

	//search moving left to right
	for (int i = 0; i < inputVector.size(); i++) {
		sum += inputVector[i];
		if (sum <= 0) {
			vector<int> temp;
			for (int j = left; j <= right; j++) {
				temp.push_back(inputVector[j]);
			}
			temp.push_back(left);
			temp.push_back(right);
			arrays.push_back(temp);
			temp.clear();
			sum = 0;
			left = i + 1;
			right = i + 1;
		}
		else {
			right = i;
		}
	}

	
	right = inputVector.size() - 1;
	left = right;

	//search moving right to left
	for (int i = inputVector.size() - 1; i >= 0; i--) {
		sum += inputVector[i];
		if (sum <= 0) {
			vector<int> temp;
			for (int j = left; j <= right; j++) {
				temp.push_back(inputVector[j]);
			}
			temp.push_back(left);
			temp.push_back(right);
			arrays.push_back(temp);
			sum = 0;
			left = i - 1;
			right = i - 1;
		}
		else {
			left = i;
		}
	}

	int highestValueIndex = 0;
	int highestValue = 0;
	int smallestSize = arrays[0].size();
	int arrayValue = 0;
	int arraySize = arrays[0].size();

	for (int i = 0; i < arrays.size(); i++) {
		arrayValue = getVectorSumWithIndicies(arrays[i]);
		if(arrayValue >= highestValue){
			if (arrayValue == highestValue && arrays[i].size() < smallestSize) {
				smallestSize = arrays[i].size();
			}
			else if (arrayValue == highestValue){
				continue;
			}
			
			highestValueIndex = i;
			highestValue = arrayValue;
		}
	}
	
	right = arrays[highestValueIndex][smallestSize - 1];
	left = arrays[highestValueIndex][smallestSize - 2];

	stringstream value;
	value << "[" << left << ", " << right << "] - { ";

	for (int i = left; i <= right; i++) {		
		value << inputVector[i];
		if(i < right)
			value << ", ";
	}

	value << "} - Sum: " << highestValue;

	cout << value.str() << endl << endl;
}

int getVectorSumWithIndicies(vector<int> inputVector) {
	int sum = 0;
	for (int i = 0; i < inputVector.size() - 2; i++) {
		sum += inputVector[i];
	}
	return sum;
}

int getVectorSum(vector<int> inputVector) {
	int sum = 0;
	for (int i = 0; i < inputVector.size(); i++) {
		sum += inputVector[i];
	}
	return sum;
}

void findSubArray(vector<int> inputVector) {

	//find left index
	int left = 0;
	int right = inputVector.size() - 1;
	int distance = right - left;
	int sum = 0;
	
	//step through the values from the left and see if there
	//is a negative value that negates all of the values 
	//added together up to that index - roll value if a negative of
	//sufficient value is found

	//look through each value but the last -> leave for right side
	for (int i = 0; i < inputVector.size() - 2; i++) {
		if (left == -1)
			left = i;

		sum += inputVector[i];
		if (sum <= 0) {
			sum = 0;
			left = -1;
		}
		
		//cout << "Value at index " << i << ": <" << (inputArray[i]) << "> -sum: <" << sum << ">" << endl;
	}

	sum = 0;
	//cout << "Left index: " << left << endl;

	//find right index
	for (int i = inputVector.size() - 1; i > left; i--) {
		if (right == -1)
			right = i;

		sum += inputVector[i];
		if (sum < 0) {
			sum = 0;
			right = -1;
		}

		//cout << "Value at index " << i << ": <" << (inputArray[i]) << "> -sum: <" << sum << ">" << endl;
	}

	//cout << "Right index: " << right << endl;

	int subarraySum = 0;

	stringstream value;
	value << "[" << left << ", " << right << "] - { ";

	for (int i = left; i <= right; i++) {
		subarraySum += inputVector[i];
		value << inputVector[i];
		if(i < right)
			value << ", ";
	}

	value << "} - Sum: " << subarraySum;

	cout << value.str() << endl << endl;
}

void inchWorm(vector<int> inputVector) {

	//find left index
	int sum = 0;
	vector<vector<int>> subarrays;
	
	int left = 0;
	int right = inputVector.size() - 1;
	for (int i = 0; i < inputVector.size(); i++) {
		if (left == -1)
			left = i;

		sum += inputVector[i];
		if (sum <= 0) {
			sum = 0;
			left = -1;
		}
		else { //store every possible subarray and their indicies
			vector<int> temp;
			for (int j = left; j < i; j++)
			{
				temp.push_back(inputVector[j]);
			}
			temp.push_back(left);
			temp.push_back(i);
			subarrays.push_back(temp);
		}

		//cout << "Value at index " << i << ": <" << (inputArray[i]) << "> -sum: <" << sum << ">" << endl;
	}

	sum = 0;
	//cout << "Left index: " << left << endl;

	//find right index
	for (int i = inputVector.size() - 1; i > left; i--) {
		if (right == -1)
			right = i;

		sum += inputVector[i];
		if (sum < 0) {
			sum = 0;
			right = -1;
		}

		//cout << "Value at index " << i << ": <" << (inputArray[i]) << "> -sum: <" << sum << ">" << endl;
	}

	//cout << "Right index: " << right << endl;

	int subarraySum = 0;

	stringstream value;
	value << "[" << left << ", " << right << "] - { ";

	for (int i = left; i <= right; i++) {
		subarraySum += inputVector[i];
		value << inputVector[i];
		if (i < right)
			value << ", ";
	}

	value << "} - Sum: " << subarraySum;

	cout << value.str() << endl << endl;
}