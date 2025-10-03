#pragma once
#include <string>
#include <vector>
#include <random>

using namespace std;

class Questions {
private:
	vector<string> questions = {
		"1 + 1 = ?",
		"2 * 2 = ?",
		"3 - 1 = ?",
		"4 / 2 = ?",
		"5 + 3 = ?",
		"6 * 2 = ?",
		"8 - 4 = ?",
		"9 / 3 = ?",
		"7 + 2 = ?",
		"10 - 5 = ?"
	};
	vector<string> answers = {
		"2",
		"4",
		"2",
		"2",
		"8",
		"12",
		"4",
		"3",
		"9",
		"5"
	};

public:
	string GetRandomQustion() 
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> question_index(0, questions.size() - 1);

		return questions[question_index(gen)];
	}

	bool CheckAnswer(const string& question, const string& answer)
	{
		for (size_t i = 0; i < questions.size(); i++) {
			if (questions[i] == question) {
				return answers[i] == answer;
			}
		}
		return false;
	}
};