#include <iostream>
#include <omp.h>
#include <locale.h>

void task1() {
	double a = 2.5, b = 3.5;
	const int ITERATIONS = 10000000;
	auto timer1 = omp_get_wtime();
	for (int i = 0; i < ITERATIONS; ++i)
		a * b;
	auto timer2 = omp_get_wtime();
	std::cout << "����� ���������� � �������������� ������ ������: " << timer2 - timer1 << std::endl;
	timer1 = omp_get_wtime();
	#pragma omp parallel num_threads(2)
	{
	#pragma omp for
		for (int i = 0; i < ITERATIONS; ++i)
			a * b;
	}
	timer2 = omp_get_wtime();
	std::cout << "����� ���������� � �������������� ���� �������: " << timer2 - timer1;
}

void task2() {
	auto timer1 = omp_get_wtime();
	#pragma omp parallel
	{

	}
	auto timer2 = omp_get_wtime();
	std::cout << "����� ����������� ��� �������� �� ����������� ������������ �������: " << timer2 - timer1;
}

void task3() {
	std::cout << "��� ��������� nowait\n\n";
	#pragma omp parallel num_threads(3)
	{
		#pragma omp single
		{
			std::cout << "������, ����� ����: " << omp_get_thread_num() << std::endl;
		}
		#pragma omp single
		{
			std::cout << "���� ����, ����� ����: " << omp_get_thread_num() << std::endl;
		}
		#pragma omp single
		{
			std::cout << "���������, ����� ����: " << omp_get_thread_num() << std::endl;
		}
	}
	std::cout << "\n\n� ���������� nowait\n\n";
	#pragma omp parallel num_threads(3)
	{
		#pragma omp single nowait
		{
			std::cout << "������, ����� ����: " << omp_get_thread_num() << std::endl;
		}
		#pragma omp single nowait
		{
			std::cout << "���� ����, ����� ����: " << omp_get_thread_num() << std::endl;
		}
		#pragma omp single nowait
		{
			std::cout << "���������, ����� ����: " << omp_get_thread_num() << std::endl;
		}
	}
}

#ifdef _OPENMP
int main() {
	setlocale(LC_ALL, "");
	//task1();
	//task2();
	task3();
	return 1;
}
#endif