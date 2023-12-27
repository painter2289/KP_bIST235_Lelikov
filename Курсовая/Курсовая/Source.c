
#include<stdio.h>
#include<locale.h>
#include<stdlib.h>


typedef struct {
	float S_wall, N, N_sum, S_open, N_open, N_fin;
} calculates;

typedef struct {
	char name[50];
	int x;
	int y;
	int z;
}brick;

typedef struct {
	int P;
	int H;

}wall;

typedef struct {
	int n;
	int L1;
	int L2;
}opening;

brick select_brick(char *fname_brick);
wall select_wall();
opening* select_opening();
int readBricksFromFile(const char* filename, brick** bricks);
int status(brick status_brick, wall status_wall, opening* status_opening, int n);
int writefile(char* fname, brick status_brick, wall status_wall, opening* status_opening, int n, calculates cal);
calculates calculate(brick bricks, wall walls, opening* openings, int n);

main()
{
	int variant;
	setlocale(LC_CTYPE, "RUS");

	char fname_brick[20] = "bricks.txt";
	char fname_output[20] = "data.txt";
	calculates cal;
	brick bricks = {NULL};
	wall walls = {NULL};
	opening *openings;
	int n = 0;
	int s_bricks = 0;
	int s_walls = 0;
	int s_cal = 0;

	openings = (opening*)malloc(n * sizeof(opening));

	do
	{
		system("cls");
		puts("\n* Добро пожаловать в калькулятор кирпичей *");
		status(bricks, walls, openings, n);
		text();
		
		variant = get_variant(7);
		
		switch (variant)
		{
		case 1: 
			
			bricks = select_brick(fname_brick);
			s_bricks = 1;
			break;
		case 2:
		{
			walls = select_wall();
			s_walls = 1;
			break;
		}

		case 3:
			free(openings);
			openings = select_opening();
			n = openings->n;
			break;
			
		case 4:;
		{
			if (s_bricks == 0) printf("Сначала выберите кирпич!\n");
			if (s_walls == 0) printf("Сначала введите размеры стен!\n");
			if (s_bricks == 0 || s_walls == 0) {
				system("pause");
				break;
			}
			cal = calculate(bricks, walls, openings, n);
			s_cal = 1;
			system("pause");
			break;
		}
		case 5: 
		{
			
			if (s_bricks == 0) printf("Сначала выберите кирпич!\n");
			if (s_walls == 0) printf("Сначала введите размеры стен!\n");
			if (s_bricks == 0 || s_walls == 0) {
				system("pause");
				break;
			}
			if (s_cal == 0) {
				printf("Сначала воспользуетесь расчетом\n");
				system("pause");
				break;
			}
			puts("Записываем параметры в документ...");
			writefile(fname_output, bricks, walls, openings, n, cal);
			system("pause");
			break;
			
		}
		case 6:
			puts("\n До свидания!");
			break;

		default: puts("Значения, кроме чисел от 1 до 6 - не принимаются");
		}
	}
	while (variant != 6);
	return 0;
}

text()
{
	puts("\n\n***********************************************************");
	puts("\nВыберите действие ");
	puts("1. Выбрать вид кирпича (Длина Ширина Высота)");
	puts("2. Задать периметр и высоту стен");
	puts("3. Задать количество проемов и их размер");
	puts("4. Результат вычисления");
	puts("5. Сохранить в документ");
	puts(" \nЧтобы выйти из программы нажмите 6");
	puts("\n***********************************************************");
	printf("Я выберу: ");
}


wall select_wall() {
	int yes;
	wall tes;
	do {
		printf("Введите высоту стены (м): ");
		scanf("%d", &tes.H);
		printf("Введите периметр стены (м): ");
		scanf("%d", &tes.P);
		puts("Продолжить изменения? \n 1.Да \n 2.Нет");
		yes = get_variant(2);
	} while (yes != 2);
	return tes;
}


opening* select_opening() {
	int n;
	int yes;
	opening* tes;
	do {
		
		printf("Введите количество проемов: ");
		scanf("%d", &n);

		tes = (opening*)malloc(n * sizeof(opening));
		tes->n = n;
		for (int i = 0; i < n; i++) {
			printf("Введите размеры %d-го проема (м): ", i + 1);
			scanf("%d %d", &tes[i].L1, &tes[i].L2);
		}
		puts("Продолжить изменения? \n 1.Да \n 2.Нет");
		yes = get_variant(2);
	} while (yes != 2);
	return tes;
}


int get_variant(int count) {
	int variant;
	char s[200]; // строка для считывания введённых данных
	scanf("%s", s); // считываем строку

	// пока ввод некорректен, сообщаем об этом и просим повторить его
	while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) 
	{
		printf("Такого варианта не существует, попробуйте еще раз: "); // выводим сообщение об ошибке
		scanf("%s", s); // считываем строку повторно
	}

	return variant;
}


int status(brick status_brick, wall status_wall, opening* status_opening, int n) {
	puts("\nВсе значения измеряются в миллиметрах для кирпича и в метрах для стен и проемов");
	printf("\n Выбран кирпич: ");
	if (status_brick.x == NULL) printf("Не указан");
	else printf("%s (%d x %d x %d мм)", status_brick.name, status_brick.x, status_brick.y, status_brick.z);

	printf("\n\n Периметр стены: ");
	if (status_wall.P <= 0) printf("Не указан");
	else printf("%d м", status_wall.P);
	printf("\n\n Высота стены: ");
	if (status_wall.H <= 0) printf("Не указан");
	else printf("%d м", status_wall.H);

	puts("");

	if (n == 0) printf("\n Проемы не заданы");

	for (int i = 0; i < n; i++) {
		printf("\n Размеры проемов %d: Длина = %d м, Ширина = %d м", (i + 1), status_opening[i].L1, status_opening[i].L2);
	}
}


int writefile(char *fname, brick status_brick, wall status_wall, opening* status_opening, int n, calculates cal) {
	FILE* out;
	if ((out = fopen(fname, "wt")) == NULL) {
		printf("Ошибка открытия файла для записи");
		return 0;

	}



	fprintf(out, " Выбран кирпич: %s (%d*%d*%d) \n Периметр стены: %d \n Высота стены: %d", status_brick.name, status_brick.x, status_brick.y, status_brick.z, status_wall.P, status_wall.H);
	for (int i = 0; i < n; i++) {
		
		fprintf(out, "\n Размеры проемов %d: Длина = %d, Ширина = %d", (i + 1), status_opening[i].L1, status_opening[i].L2);

	}
	
	fprintf(out, "\n Количество кирпичей в квадрате - %.4f \n Площадь внешних стен - %.4f \n Итого количества кирпича с учетом проемов - %.1f\n",
cal.N, cal.S_wall, cal.N_fin);

	fclose(out);
	
}


calculates calculate(brick bricks, wall walls, opening* openings, int n) {
	calculates cal;
	
	
	// Проверка на отрицательные значения размеров стен и кирпича
	if (walls.H <= 0 || walls.P <= 0 || bricks.x <= 0 || bricks.y <= 0 || bricks.z <= 0) {
		printf("Ошибка: Отрицательные или нулевые значения размеров стен или кирпича. Пожалуйста, измените ввод.\n");
		return cal; // Возвращаем пустую структуру
	}

	cal.S_wall = walls.H * walls.P; // Площадь стен в квадратных метрах
	cal.N = (1000.0 / bricks.x) * (1000.0 / bricks.z); // Количество кирпичей на кв. метр

	cal.N_sum = cal.S_wall * cal.N; // Общее количество кирпичей без учета проемов

	cal.S_open = 0;
	for (int i = 0; i < n; i++) {
		if (openings[i].L1 <= 0 || openings[i].L2 <= 0) {
			printf("Ошибка: Отрицательные или нулевые значения размеров проема. Пожалуйста, измените ввод.\n");
			return cal; // Возвращаем пустую структуру
		}
		cal.S_open += openings[i].L1 * openings[i].L2; // Площадь проемов в квадратных метрах
	}

	cal.N_open = cal.N * cal.S_open; // Количество кирпичей для проемов
	cal.N_fin = cal.N_sum - cal.N_open; // Итоговое количество кирпичей с учетом проемов

	// Проверка на отрицательное итоговое количество кирпичей
	if (cal.N_fin < 0) {
		printf("Ошибка: Итоговое количество кирпичей не может быть отрицательным. Пожалуйста, измените ввод.\n");
		return cal; // Возвращаем пустую структуру
	}

	// Вывод результатов
	printf("\n Количество кирпичей в квадрате - %.2f \n Площадь внешних стен - %.2f м \n Итого количества кирпича с учетом проемов - %.1f\n",
		cal.N, cal.S_wall, cal.N_fin);

	return cal;
}



brick select_brick(char* fname_brick) {
	
	brick* bricks = NULL;
	int count = readBricksFromFile(fname_brick, &bricks);
	if (count == 0) {
		printf("Ошибка чтения файла или файл пуст.\n");
		return (brick) { 0 };
	} 

	// Добавление варианта "Свой вариант"
	bricks = realloc(bricks, (count + 1) * sizeof(brick));
	strcpy(bricks[count].name, "Свой вариант");
	bricks[count].x = bricks[count].y = bricks[count].z = 0;
	count++;

	int choice;
	brick selected;
	int yes;
	// Показываем список пользователю и запрашиваем выбор
	do {
		
		for (int i = 0; i < count; i++) {
			printf("%d. %s (%d x %d x %d)\n", i + 1, bricks[i].name, bricks[i].x, bricks[i].y, bricks[i].z);
		}
		printf("Выберите вариант: ");
		choice = get_variant(count) - 1;
		
		if (choice < count - 1) {
			selected = bricks[choice];
		}
		else{
			printf("Введите размеры (длина ширина высота) для своего варианта: ");
			scanf("%d %d %d", &selected.x, &selected.y, &selected.z);
			strcpy(selected.name, "Свой вариант");
		}
		
		puts("Продолжить изменения? \n 1.Да \n 2.Нет");
		yes = get_variant(2);
	} while (yes != 2);
	
	free(bricks);
	return selected;
}

int readBricksFromFile(const char* filename, brick** bricks) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Ошибка открытия файла");
		return 0;
	}

	char line[100];
	int count = 0;
	brick* temp = NULL;

	while (fgets(line, sizeof(line), file)) {
		temp = realloc(*bricks, (count + 1) * sizeof(brick));
		if (!temp) {
			perror("Ошибка выделения памяти");
			free(*bricks);
			*bricks = NULL;
			fclose(file);
			return 0;
		}
		*bricks = temp;

		if (sscanf(line, "%49[^()] (%dx%dx%d)", (*bricks)[count].name, &(*bricks)[count].x, &(*bricks)[count].y, &(*bricks)[count].z) != 4) {
			printf("Некорректная строка, пропускаем...\n");
			continue;
		}
		count++;
	}

	fclose(file);
	return count;
}