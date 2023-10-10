#include <iostream>
#include <omp.h>
#include <locale.h>
#include <vector>

void task1() {
	double a, b;
	const int ITERATIONS = 10000000;
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
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

void task4() {
	#pragma omp parallel num_threads(3)
	{
		std::cout << "������, ����� ����: " << omp_get_thread_num() << std::endl;
		#pragma omp master
		{
			std::cout << "������� �����, ����� ����: " << omp_get_thread_num() << std::endl;
		}
		std::cout << "��������, ����� ����: " << omp_get_thread_num() << std::endl;
		#pragma omp master
		{
			std::cout << "������� �����, ����� ����: " << omp_get_thread_num() << std::endl;
		}
		std::cout << "�����, ����� ����: " << omp_get_thread_num() << std::endl;
		#pragma omp master
		{
			std::cout << "������� �����, ����� ����: " << omp_get_thread_num() << std::endl;
		}
	}
}

void task5() {
	int n = 10;
	std::cout << "��������������� �������, n = " << n << ", ����� ������: " << omp_get_thread_num() << std::endl;
	#pragma omp parallel num_threads(3) private(n)
	{
		std::cout << "������������ �������, n = " << n << ", ����� ������: " << omp_get_thread_num() << std::endl;
		n = omp_get_thread_num();
		std::cout << "������������ �������, n* = " << n << ", ����� ������: " << omp_get_thread_num() << std::endl;
	}
	std::cout << "���������������� �������, n = " << n << ", ����� ������: " << omp_get_thread_num() << std::endl;
}

void task6() {
	int size = 5;
	std::vector <int> m(size, 0);
	std::cout << "�������� ������: ";
	for (int i = 0; i < size; ++i) std::cout << m[i] << " ";
	#pragma omp parallel num_threads(2) shared(m)
	{
		for (int i = 0; i < m.size(); ++i) 
			if (i == omp_get_thread_num())
				m[i] = 1;
	}
	std::cout << "\n��������� ������: ";
	for (int i = 0; i < size; ++i) std::cout << m[i] << " ";
}

void task7() {
	int sum = 0;
	#pragma omp parallel reduction(+: sum)
	{
		sum = 1;
		std::cout << "������� �������� sum: " << sum << ", ����� ������: " << omp_get_thread_num() << std::endl;
	}
	std::cout << "�������� �������� ���������� sum: " << sum;
}

void task8() {
	int sum = 0;
	#pragma omp parallel reduction(+: sum) num_threads(4)
	{
		sum = omp_get_thread_num();
		std::cout << "�������� ���������� sum: " << sum << ", ����� ������: " << omp_get_thread_num() << std::endl;
	}
	std::cout << "�������� �������� ���������� sum: " << sum;
}

#ifdef _OPENMP
int main() {
	setlocale(LC_ALL, "");
	//task1();
	//task2();
	//task3();
	//task4(); 
	//task5();
	//task6();
	//task7();
	//task8();
	return 1;
}
#endif