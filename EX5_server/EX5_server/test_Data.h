#pragma once
#include <iostream>
#include <string>


struct test_Data {
	std::string questions[10]{}; // << 있어야하나?
	std::string answers[10]{};
	int score{};
	bool quiz_flag{};

	friend std::ostream& operator<<(std::ostream& os, const test_Data& data) {
		if (data.quiz_flag) {
			for (int i{}; i < 10; i++) {
				os << "Q" << (i + 1) << ": " << data.questions[i] << ", A" << (i + 1) << ": " << data.answers[i] << std::endl;
			}
		}
		else {
			os << "Message: " << data.answers[0] << std::endl;
		}
		os << "Score: " << data.score << std::endl;
		os << "Quiz Flag: " << (data.quiz_flag ? "true" : "false") << std::endl;

		return os;
	}
};