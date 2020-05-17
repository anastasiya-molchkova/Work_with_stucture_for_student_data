#ifndef STUDENTS_ARRAY
#define STUDENTS_ARRAY

#include <algorithm> // для использования алгоритмов сортировки
#include "Student_data.h"

using std::cout; using std::cin; using std::endl;

// класс-контейнер для обработки данных о студентах
class The_list_of_students
{
public:
	static const unsigned number_of_students = 10;
private:
	array<Student*, number_of_students> students; // массив указателей на данные о студентах
public:
	// конструктор по умолчанию
	The_list_of_students()
	{}

	// добавление данных о ещё одном студенте
	void add_student(const unsigned i,  Student* student)
	{
		students.at(i) = student;
	}

	// сортировка элементов вектора по имени
	void sort_by_name()
	{
		for (unsigned startIndex = 0; startIndex < (number_of_students - 1); ++startIndex)
		{
			int minimumIndex = startIndex;
			for (unsigned currentIndex = startIndex + 1; currentIndex < number_of_students; ++currentIndex)
			{
				if (students.at(currentIndex)->Name < students.at(minimumIndex)->Name)
					minimumIndex = currentIndex;
			}
			std::swap(students[startIndex], students[minimumIndex]);
		}
	}

	// печать студентов со средним баллом выше среднего
	void print_best_students()
	{
		cout << '\n';
		if (students.size() == 0) cout << "Список студентов пуст!" << '\n';
		else
		{
			double summ_of_average{ 0 };
			for (const auto student : students)
				summ_of_average += student->Average_score;
			double total_average_score = summ_of_average / number_of_students;
			bool best_students_exist{ false };
			for (const auto student : students)
				if (student->Average_score > total_average_score)
				{
					cout << *student;
					best_students_exist = true;
				}
			if (best_students_exist == false)
				cout << "Не найдено студентов со средним баллом, превышающим общий средний балл!\n";
		}
	}

	// деструктор
	~The_list_of_students()
	{
		for (auto student_ptr : students)
		delete student_ptr;
	}
};

#endif