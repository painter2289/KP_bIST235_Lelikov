
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
		puts("\n* ����� ���������� � ����������� �������� *");
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
			if (s_bricks == 0) printf("������� �������� ������!\n");
			if (s_walls == 0) printf("������� ������� ������� ����!\n");
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
			
			if (s_bricks == 0) printf("������� �������� ������!\n");
			if (s_walls == 0) printf("������� ������� ������� ����!\n");
			if (s_bricks == 0 || s_walls == 0) {
				system("pause");
				break;
			}
			if (s_cal == 0) {
				printf("������� �������������� ��������\n");
				system("pause");
				break;
			}
			puts("���������� ��������� � ��������...");
			writefile(fname_output, bricks, walls, openings, n, cal);
			system("pause");
			break;
			
		}
		case 6:
			puts("\n �� ��������!");
			break;

		default: puts("��������, ����� ����� �� 1 �� 6 - �� �����������");
		}
	}
	while (variant != 6);
	return 0;
}

text()
{
	puts("\n\n***********************************************************");
	puts("\n�������� �������� ");
	puts("1. ������� ��� ������� (����� ������ ������)");
	puts("2. ������ �������� � ������ ����");
	puts("3. ������ ���������� ������� � �� ������");
	puts("4. ��������� ����������");
	puts("5. ��������� � ��������");
	puts(" \n����� ����� �� ��������� ������� 6");
	puts("\n***********************************************************");
	printf("� ������: ");
}


wall select_wall() {
	int yes;
	wall tes;
	do {
		printf("������� ������ ����� (�): ");
		scanf("%d", &tes.H);
		printf("������� �������� ����� (�): ");
		scanf("%d", &tes.P);
		puts("���������� ���������? \n 1.�� \n 2.���");
		yes = get_variant(2);
	} while (yes != 2);
	return tes;
}


opening* select_opening() {
	int n;
	int yes;
	opening* tes;
	do {
		
		printf("������� ���������� �������: ");
		scanf("%d", &n);

		tes = (opening*)malloc(n * sizeof(opening));
		tes->n = n;
		for (int i = 0; i < n; i++) {
			printf("������� ������� %d-�� ������ (�): ", i + 1);
			scanf("%d %d", &tes[i].L1, &tes[i].L2);
		}
		puts("���������� ���������? \n 1.�� \n 2.���");
		yes = get_variant(2);
	} while (yes != 2);
	return tes;
}


int get_variant(int count) {
	int variant;
	char s[200]; // ������ ��� ���������� �������� ������
	scanf("%s", s); // ��������� ������

	// ���� ���� �����������, �������� �� ���� � ������ ��������� ���
	while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) 
	{
		printf("������ �������� �� ����������, ���������� ��� ���: "); // ������� ��������� �� ������
		scanf("%s", s); // ��������� ������ ��������
	}

	return variant;
}


int status(brick status_brick, wall status_wall, opening* status_opening, int n) {
	puts("\n��� �������� ���������� � ����������� ��� ������� � � ������ ��� ���� � �������");
	printf("\n ������ ������: ");
	if (status_brick.x == NULL) printf("�� ������");
	else printf("%s (%d x %d x %d ��)", status_brick.name, status_brick.x, status_brick.y, status_brick.z);

	printf("\n\n �������� �����: ");
	if (status_wall.P <= 0) printf("�� ������");
	else printf("%d �", status_wall.P);
	printf("\n\n ������ �����: ");
	if (status_wall.H <= 0) printf("�� ������");
	else printf("%d �", status_wall.H);

	puts("");

	if (n == 0) printf("\n ������ �� ������");

	for (int i = 0; i < n; i++) {
		printf("\n ������� ������� %d: ����� = %d �, ������ = %d �", (i + 1), status_opening[i].L1, status_opening[i].L2);
	}
}


int writefile(char *fname, brick status_brick, wall status_wall, opening* status_opening, int n, calculates cal) {
	FILE* out;
	if ((out = fopen(fname, "wt")) == NULL) {
		printf("������ �������� ����� ��� ������");
		return 0;

	}



	fprintf(out, " ������ ������: %s (%d*%d*%d) \n �������� �����: %d \n ������ �����: %d", status_brick.name, status_brick.x, status_brick.y, status_brick.z, status_wall.P, status_wall.H);
	for (int i = 0; i < n; i++) {
		
		fprintf(out, "\n ������� ������� %d: ����� = %d, ������ = %d", (i + 1), status_opening[i].L1, status_opening[i].L2);

	}
	
	fprintf(out, "\n ���������� �������� � �������� - %.4f \n ������� ������� ���� - %.4f \n ����� ���������� ������� � ������ ������� - %.1f\n",
cal.N, cal.S_wall, cal.N_fin);

	fclose(out);
	
}


calculates calculate(brick bricks, wall walls, opening* openings, int n) {
	calculates cal;
	
	
	// �������� �� ������������� �������� �������� ���� � �������
	if (walls.H <= 0 || walls.P <= 0 || bricks.x <= 0 || bricks.y <= 0 || bricks.z <= 0) {
		printf("������: ������������� ��� ������� �������� �������� ���� ��� �������. ����������, �������� ����.\n");
		return cal; // ���������� ������ ���������
	}

	cal.S_wall = walls.H * walls.P; // ������� ���� � ���������� ������
	cal.N = (1000.0 / bricks.x) * (1000.0 / bricks.z); // ���������� �������� �� ��. ����

	cal.N_sum = cal.S_wall * cal.N; // ����� ���������� �������� ��� ����� �������

	cal.S_open = 0;
	for (int i = 0; i < n; i++) {
		if (openings[i].L1 <= 0 || openings[i].L2 <= 0) {
			printf("������: ������������� ��� ������� �������� �������� ������. ����������, �������� ����.\n");
			return cal; // ���������� ������ ���������
		}
		cal.S_open += openings[i].L1 * openings[i].L2; // ������� ������� � ���������� ������
	}

	cal.N_open = cal.N * cal.S_open; // ���������� �������� ��� �������
	cal.N_fin = cal.N_sum - cal.N_open; // �������� ���������� �������� � ������ �������

	// �������� �� ������������� �������� ���������� ��������
	if (cal.N_fin < 0) {
		printf("������: �������� ���������� �������� �� ����� ���� �������������. ����������, �������� ����.\n");
		return cal; // ���������� ������ ���������
	}

	// ����� �����������
	printf("\n ���������� �������� � �������� - %.2f \n ������� ������� ���� - %.2f � \n ����� ���������� ������� � ������ ������� - %.1f\n",
		cal.N, cal.S_wall, cal.N_fin);

	return cal;
}



brick select_brick(char* fname_brick) {
	
	brick* bricks = NULL;
	int count = readBricksFromFile(fname_brick, &bricks);
	if (count == 0) {
		printf("������ ������ ����� ��� ���� ����.\n");
		return (brick) { 0 };
	} 

	// ���������� �������� "���� �������"
	bricks = realloc(bricks, (count + 1) * sizeof(brick));
	strcpy(bricks[count].name, "���� �������");
	bricks[count].x = bricks[count].y = bricks[count].z = 0;
	count++;

	int choice;
	brick selected;
	int yes;
	// ���������� ������ ������������ � ����������� �����
	do {
		
		for (int i = 0; i < count; i++) {
			printf("%d. %s (%d x %d x %d)\n", i + 1, bricks[i].name, bricks[i].x, bricks[i].y, bricks[i].z);
		}
		printf("�������� �������: ");
		choice = get_variant(count) - 1;
		
		if (choice < count - 1) {
			selected = bricks[choice];
		}
		else{
			printf("������� ������� (����� ������ ������) ��� ������ ��������: ");
			scanf("%d %d %d", &selected.x, &selected.y, &selected.z);
			strcpy(selected.name, "���� �������");
		}
		
		puts("���������� ���������? \n 1.�� \n 2.���");
		yes = get_variant(2);
	} while (yes != 2);
	
	free(bricks);
	return selected;
}

int readBricksFromFile(const char* filename, brick** bricks) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("������ �������� �����");
		return 0;
	}

	char line[100];
	int count = 0;
	brick* temp = NULL;

	while (fgets(line, sizeof(line), file)) {
		temp = realloc(*bricks, (count + 1) * sizeof(brick));
		if (!temp) {
			perror("������ ��������� ������");
			free(*bricks);
			*bricks = NULL;
			fclose(file);
			return 0;
		}
		*bricks = temp;

		if (sscanf(line, "%49[^()] (%dx%dx%d)", (*bricks)[count].name, &(*bricks)[count].x, &(*bricks)[count].y, &(*bricks)[count].z) != 4) {
			printf("������������ ������, ����������...\n");
			continue;
		}
		count++;
	}

	fclose(file);
	return count;
}