#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <locale.h>

int data; //отвечает за тип данных
int k; //отвечает за тип операции
int c;//определяет включать тест или нет

struct matrix{
	int n, size;
	void* z;
}first, second, result;
struct complex{
	int x, y;
};
struct matrix* fill(int* n){ // заполнение массивов
	int i, j;
	void* matrix = malloc(*n**n*first.size);
	for (i = 0; i < *n; i++)
		for (j = 0; j < *n; j++){
			if (data == 1){
				if (n == &first.n) printf("a[%d][%d] = ", i, j);
				else printf("b[%d][%d] = ", i, j);
				scanf("%d", ((int*)matrix + i**n + j));
			}
			else if (data == 2){
				if (n == &first.n) printf("a[%d][%d] = ", i, j);
				else printf("b[%d][%d] = ", i, j);
				scanf("%f", ((float*)matrix + i**n + j));
			}
			else if (data == 3){
				if (n == &first.n){
					printf("a[%d][%d].re = ", i, j);
					scanf("%d", &(((struct complex*)matrix + i**n + j)->x));
					printf("a[%d][%d].im = ", i, j);
					scanf("%d", &(((struct complex*)matrix + i**n + j)->y));
				}
				else {
					printf("b[%d][%d].re = ", i, j);
					scanf("%d", &(((struct complex*)matrix + i**n + j)->x));
					printf("b[%d][%d].im = ", i, j);
					scanf("%d", &(((struct complex*)matrix + i**n + j)->y));
				}
			}
		}
	return matrix;
} 
void sumInt(void* a, void* b, int i, int j){ // сумма целых
	*((int*)result.z + i*first.n + j) = *((int*)a) + *((int*)b);
}
void sumFloat(void* a, void* b, int i, int j){ // сумма вещественных
	*((float*)result.z + i*first.n + j) = *((float*)a) + *((float*)b);
}
void sumComplex(void* a, void* b, int i, int j){ // сумма комплексных
		((struct complex*)result.z + i*first.n + j)->x = ((struct complex*)a)->x + ((struct complex*)b)->x;
		((struct complex*)result.z + i*first.n + j)->y = ((struct complex*)a)->y + ((struct complex*)b)->y;
}
void Sum(void* a, void* b, void (*func)(void* a, void* b)){ // универсальная функция суммы 
	int i, j;
	result.z = calloc(first.n*first.n, first.size);
	for (i = 0; i < first.n; i++){
		for (j = 0; j < first.n; j++){
			func((char*)a + (i*first.n + j)*first.size, (char*)b + (i*first.n + j)*first.size, i, j);
		}
	}
}
void multiInt(void* a, void* b, int i, int j){ // умножение
	*((int*)result.z + i*first.n + j) += *((int*)a) * *((int*)b);
}
void multiFloat(void* a, void* b, int i, int j){
	*((float*)result.z + i*first.n + j) += *((float*)a) * *((float*)b);
}
void multiComplex(void* a, void* b, int i, int j){
	((struct complex*)result.z + i*second.n + j)->x += ((struct complex*)a)->x*((struct complex*)b)->x - ((struct complex*)a)->y*((struct complex*)b)->y;
	((struct complex*)result.z + i*second.n + j)->y += ((struct complex*)a)->x*((struct complex*)b)->y + ((struct complex*)a)->y*((struct complex*)b)->x;
}
void Multi(void* a, void* b, void(*func)(void* a, void* b)){
	int i, j, h;
	result.z = calloc(first.n*second.n, first.size);
	for (i = 0; i < first.n; i++){
		for (j = 0; j < first.n; j++){
			for (h = 0; h < first.n; h++){
				func((char*)a + (i*first.n + h)*first.size, (char*)b + (i*first.n + h)*first.size, i, j);
			}
		}
	}
}
void output(void* a) { // вывод массива
	int i, j;
	for (i = 0; i < first.n; i++){
		for (j = 0; j < first.n; j++){
			if (data == 1) printf("%d  ", *((int*)result.z + i*first.n + j));
			else if (data == 2) printf("%f  ", *((float*)result.z + i*first.n + j));
			else if (data == 3) printf("%d + %d*i  ", ((struct complex*)result.z + i*first.n + j)->x, ((struct complex*)result.z + i*first.n + j)->y);
		}
		printf("\n");
	}
}
void test(int data){
	int i, j;

	first.n = 2;
	second.n = 2;
	first.z = malloc(2 * 2 * first.size);
	second.z = malloc(2 * 2 * first.size);
		if (data == 1){
			printf("Сложение:\n");
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					*((int*)first.z + first.n*i + j) = 1;
					*((int*)second.z + first.n*i + j) = 1;
				}
			Sum(first.z, second.z, sumInt);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					if (*((int*)result.z + first.n*i + j) != 2)
						printf("Ошибка сложения\n");
					else printf("Все верно\n");
				}
			printf("Умножение:\n");
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					*((int*)first.z + first.n*i + j) = 3;
				}
			for (i = 0; i < second.n; i++)
				for (j = 0; j < second.n; j++){
					*((int*)second.z + second.n*i + j) = 3;
				}
			Multi(first.z, second.z, multiInt);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					if (*((int*)result.z + first.n*i + j) != 18)
						printf("Ошибка умножения\n");
					else printf("Все верно\n");
				}
		}
		else if (data == 2){
			printf("Сложение:\n");
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					*((float*)first.z + first.n*i + j) = first.n + i;
					*((float*)second.z + first.n*i + j) = first.n + j;
				}
			Sum(first.z, second.z, sumFloat);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					if (*((float*)result.z + first.n*i + j) != 2 * first.n + i + j)
						printf("Ошибка сложения\n");
					else printf("Все верно\n");
				}
			printf("Умножение:\n");
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					*((float*)first.z + first.n*i + j) = 6;
					*((float*)second.z + first.n*i + j) = 3;
				}
			Multi(first.z, second.z, multiFloat);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					if (*((float*)result.z + first.n*i + j) != 36)
						printf("Ошибка умножения\n");
					else printf("Все верно\n");
				}
		}
		else if (data == 3){
			printf("Сложение:\n");
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					((struct complex*)first.z + first.n*i + j)->x = ((struct complex*)first.z + first.n*i + j)->y = first.n + i;
					((struct complex*)second.z + first.n*i + j)->x = ((struct complex*)second.z + first.n*i + j)->y = first.n + j;
				}
			Sum(first.z, second.z, sumComplex);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					if (((struct complex*)result.z + first.n*i + j)->x != 2 * first.n + i + j & ((struct complex*)result.z + first.n*i + j)->y != 2 * first.n + i + j)
						printf("Ошибка сложения\n");
					else printf("Все верно\n");
				}
			printf("Умножение:\n");
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					((struct complex*)first.z + first.n*i + j)->x = ((struct complex*)first.z + first.n*i + j)->y = 2;
					((struct complex*)second.z + first.n*i + j)->x = ((struct complex*)second.z + first.n*i + j)->y = 2;
				}
			Multi(first.z, second.z, multiComplex);
			for (i = 0; i < first.n; i++)
				for (j = 0; j < first.n; j++){
					if (((struct complex*)result.z + first.n*i + j)->x != 0 && ((struct complex*)result.z + first.n*i + j)->y != 16)
						printf("Ошибка умножения\n");
					else printf("Все верно\n");
				}
		}
}

int main() {
	setlocale(LC_ALL, "Rus");
	printf("Введите 1 для целых, 2 для вещественных, 3 для комплексных\n");
	scanf("%d", &data);
	if (data == 1) first.size = sizeof(int);
	else if (data == 2) first.size = sizeof(float);
	else if (data == 3) first.size = sizeof(struct complex);
	printf("Запустить тест (1-Да или 2-Нет)?\n");
	scanf("%d", &c);
	if (c == 1){
		test(data);
	}
	else if (c == 2){
		printf("Введите 1 для сложения, 2 для умножения\n");
		scanf("%d", &k);
		printf("Введите кол-во строк и столбцов первой матрицы\n");
		scanf("%d", &first.n);
		printf("Введите кол-во строк и столбцов второй матрицы\n");
		scanf("%d", &second.n);
		first.z = fill(&first.n);
		second.z = fill(&second.n);
		if (k == 1){
			if (first.n == second.n){
				if (data == 1) Sum(first.z, second.z, sumInt);
				else if (data == 2) Sum(first.z, second.z, sumFloat);
				else if (data == 3) Sum(first.z, second.z, sumComplex);
				output(result.z);
			}
			else printf("Матрицы невозможно сложить\n");
		}
		else if (k == 2){
			if (first.n == second.n){
				if (data == 1) Multi(first.z, second.z, multiInt);
				else if (data == 2) Multi(first.z, second.z, multiFloat);
				else if (data == 3) Multi(first.z, second.z, multiComplex);
				output(result.z);
			}
			else printf("Матрицы невозможно умножить\n");
		}	
	}
	free(first.z);
	free(second.z);
	free(result.z);
	system("PAUSE");
}
