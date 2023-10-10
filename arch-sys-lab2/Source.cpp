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
	std::cout << "Время выполнения с использованием одного потока: " << timer2 - timer1 << std::endl;
	timer1 = omp_get_wtime();
	#pragma omp parallel num_threads(2)
	{
	#pragma omp for
		for (int i = 0; i < ITERATIONS; ++i)
			a * b;
	}
	timer2 = omp_get_wtime();
	std::cout << "Время выполнения с использованием двух потоков: " << timer2 - timer1;
}

void task2() {
	auto timer1 = omp_get_wtime();
	#pragma omp parallel
	{

	}
	auto timer2 = omp_get_wtime();
	std::cout << "Время необходимое для операций по организации параллельной области: " << timer2 - timer1;
}

void task3() {
	std::cout << "Без параметра nowait\n\n";
	#pragma omp parallel num_threads(3)
	{
		#pragma omp single
		{
			std::cout << "Начало, номер нити: " << omp_get_thread_num() << std::endl;
		}
		#pragma omp single
		{
			std::cout << "Одна нить, номер нити: " << omp_get_thread_num() << std::endl;
		}
		#pragma omp single
		{
			std::cout << "Окончание, номер нити: " << omp_get_thread_num() << std::endl;
		}
	}
	std::cout << "\n\nС параметром nowait\n\n";
	#pragma omp parallel num_threads(3)
	{
		#pragma omp single nowait
		{
			std::cout << "Начало, номер нити: " << omp_get_thread_num() << std::endl;
		}
		#pragma omp single nowait
		{
			std::cout << "Одна нить, номер нити: " << omp_get_thread_num() << std::endl;
		}
		#pragma omp single nowait
		{
			std::cout << "Окончание, номер нити: " << omp_get_thread_num() << std::endl;
		}
	}
}

void task4() {
	#pragma omp parallel num_threads(3)
	{
		std::cout << "Начало, номер нити: " << omp_get_thread_num() << std::endl;
		#pragma omp master
		{
			std::cout << "Главный поток, номер нити: " << omp_get_thread_num() << std::endl;
		}
		std::cout << "Середина, номер нити: " << omp_get_thread_num() << std::endl;
		#pragma omp master
		{
			std::cout << "Главный поток, номер нити: " << omp_get_thread_num() << std::endl;
		}
		std::cout << "Конец, номер нити: " << omp_get_thread_num() << std::endl;
		#pragma omp master
		{
			std::cout << "Главный поток, номер нити: " << omp_get_thread_num() << std::endl;
		}
	}
}

void task5() {
	int n = 10;
	std::cout << "Последовательня область, n = " << n << ", номер потока: " << omp_get_thread_num() << std::endl;
	#pragma omp parallel num_threads(3) private(n)
	{
		std::cout << "Параллельная область, n = " << n << ", номер потока: " << omp_get_thread_num() << std::endl;
		n = omp_get_thread_num();
		std::cout << "Параллельная область, n* = " << n << ", номер потока: " << omp_get_thread_num() << std::endl;
	}
	std::cout << "Последовательная область, n = " << n << ", номер потока: " << omp_get_thread_num() << std::endl;
}

void task6() {
	int size = 5;
	std::vector <int> m(size, 0);
	std::cout << "Исходный массив: ";
	for (int i = 0; i < size; ++i) std::cout << m[i] << " ";
	#pragma omp parallel num_threads(2) shared(m)
	{
		for (int i = 0; i < m.size(); ++i) 
			if (i == omp_get_thread_num())
				m[i] = 1;
	}
	std::cout << "\nИзменённый массив: ";
	for (int i = 0; i < size; ++i) std::cout << m[i] << " ";
}

void task7() {
	int sum = 0;
	#pragma omp parallel reduction(+: sum)
	{
		sum = 1;
		std::cout << "Текущее значение sum: " << sum << ", номер потока: " << omp_get_thread_num() << std::endl;
	}
	std::cout << "Итоговое значение переменной sum: " << sum;
}

void task8() {
	int sum = 0;
	#pragma omp parallel reduction(+: sum) num_threads(4)
	{
		sum = omp_get_thread_num();
		std::cout << "Значение переменной sum: " << sum << ", номер потока: " << omp_get_thread_num() << std::endl;
	}
	std::cout << "Итоговое значение переменной sum: " << sum;
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