#ifndef STUDENT_DATA
#define STUDENT_DATA

#include <iostream>
#include <string>
#include <array>

using std::string; using std::array;

// ��������� ������ � �������� - ���, ���� � ������������
struct Student
{
	// ������������ ��������� ������
	enum marks { one = 1, bad, satisfactorily, good, excellent };
	static const unsigned short number_of_marks_in_rating = 5;

	// ������ ��� ������ ����������:
	string Name;
	unsigned Year;
	array<marks, number_of_marks_in_rating> Rating{marks::one, marks::one, marks::one, marks::one, marks::one};
	double Average_score;

	// ����������� �� ��������� ����� ��� �������� "�������" �������
	Student() : Name(), Year(0), Average_score(marks::one)
	{
	}
	// ����������� � �����������
	Student(const string& name, const unsigned year, const array<marks, number_of_marks_in_rating>& rating):
		Name(name), Year(year), Rating(rating)
	{
		double summ{0};
		for (const auto& mark_from_rating : Rating)
			summ += mark_from_rating;
		Average_score = summ / number_of_marks_in_rating;
	}
	// ���������� ��������� ������ ������ ��������
	friend std::ostream& operator<<(std::ostream& out, const Student& student)
	{
		out << student.Name << " " << student.Year << " ";
		for (const auto& mark_from_rating : student.Rating)
			out << mark_from_rating << " ";
		out << '\n';
		return out;
	}
};

#endif