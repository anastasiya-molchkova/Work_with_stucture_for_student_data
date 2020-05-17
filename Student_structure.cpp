/* Описать структуру с именем STUDENT, содержащую поля:
   Name — фамилия и инициалы;
   Year — курс;
   Rating — успеваемость (массив из пяти элементов).
Написать программу, выполняющую:
   ввод с клавиатуры данных в массив STUD, состоящий из 10 структур типа STUDENT, записи должны быть упорядочены по алфавиту;
   вывод на экран записей, упорядоченного списка студентов, средний бал которых превышает общий средний бал;
   если таких студентов нет — выдать соответствующее сообщение. */

#include "Students_array.h"
#include <sstream> // для работы со строковым потоком, чтобы превращать данные из строки в нужные данные разного типа

// функция возвращает истину, если строка соответствует ожидаемому формату "Ф И.О. год оценки рэйтинга" и ложь, если не соответствует
bool line_is_ok(const string& line_from_file)
{
	if (line_from_file.length() < 18) return false; //т.к. строка должна иметь вид "Ф И.О. курс ц1 ц1 ц3 ц4 ц5" - как минимум 18 символов
	unsigned short spaces_counter = 0; // счётчик пробелов
	unsigned short index = 0;          // индекс символов строки

	while ((index < line_from_file.size()) && (spaces_counter < 8))
		// 1ый пробел - окончание фамилии, 2ой- окончание имени, 3ий - года, потом через пробел идут пять оценок
	{
		if (isspace(line_from_file[index]))
			spaces_counter++;
		else
		{
			if ((spaces_counter == 0) && (!isalpha(line_from_file[index]))) return false;
			if ((spaces_counter == 1) && (!(isalpha(line_from_file[index]) || (line_from_file[index] == '.')))) return false;
			if ((spaces_counter >= 2) && (!isdigit(line_from_file[index]))) return false;
		}
		index++;
	}
	if (index < line_from_file.size()) return false; // если пробелов до конца строки было больше запланированного
	else return true;
}

// функция превращает строку в правильном формате в указатель на структуру данных о студенте
Student* convert_string_to_data(const string& correct_string)
{
	std::stringstream future_data;
	future_data << correct_string;

	string surname, second_part_of_name;
	future_data >> surname;
	surname += " ";
	future_data >> second_part_of_name;

	unsigned year{ 0 };
	future_data >> year;

	array<Student::marks, Student::number_of_marks_in_rating> rating;
	for (unsigned short i = 0; i < Student::number_of_marks_in_rating; i++)
	{
		unsigned short mark;
		future_data >> mark;
		rating[i] = static_cast<Student::marks>(mark);
	}

	return new Student(surname.append(second_part_of_name), year, rating);
}

// заполняем передаваемый массив данных о студентах данными из файла
void get_students_data(The_list_of_students& Students)
{
	unsigned short lines_index = 0; // счётчик строк
	cout << "Вводите данные о студентах в формате Surname Name курс оценка оценка оценка оценка оценка:\n";
	while (lines_index < The_list_of_students::number_of_students)  // нам нужно получить заданное количество правильных строк
	{
		string possible_data;
		cout << "Введите данные студента №" << lines_index + 1 << ": ";
		getline(cin, possible_data);
		if (line_is_ok(possible_data))
		{
			Student* student_ptr = convert_string_to_data(possible_data);
			Students.add_student(lines_index, student_ptr);
			lines_index++;
		}
		else cout << "Вы ввели строку в неправильном формате, придётся переписать ещё раз!" << '\n';
	}
}

int main()
{
	setlocale(LC_CTYPE, "rus");

	The_list_of_students Students;
	get_students_data(Students);
	Students.sort_by_name();
	cout << "\nУпорядоченные по алфавиту данные студентов, которые учатся лучше среднего:";
	Students.print_best_students();

	return 0;
}