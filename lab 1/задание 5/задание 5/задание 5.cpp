#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

int   main(void)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	int i;
	struct student
	{
		char famil[20];
		char name[20], grup[20];
		int Nomzach;
	} stud[3];
	
	for (i = 0; i < 3; i++)
	{
		printf("Введите фамилию студента\n"); scanf("%20s", stud[i].famil);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите имя студента %s\n", stud[i].famil); scanf("%20s", stud[i].name);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите название группы студента %s %s\n", stud[i].famil, stud[i].name); scanf("%20s", stud[i].grup);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите номер зачётной книжки студента %s %s\n", stud[i].famil, stud[i].name); scanf("%d", &stud[i].Nomzach);
	}

	for (i = 0; i < 3; i++)
	{
		printf("Cтудент %s %s обучается в группе %s, номер зачётной книжки %d \n", stud[i].famil, stud[i].name,
			stud[i].grup, stud[i].Nomzach);
	}
	char famil[20], name[20];
	printf("Введите Фамилию учащегося: ");
	scanf("%20s", famil);
	printf("Введите Имя учащегося: ");
	scanf("%20s", name);
	int g = 0;
	for (i = 0; i < 3; i++) {
		if (!strcmp(stud[i].famil, famil) and !strcmp(stud[i].name, name) )
			g = 1;
	}
	if (g)
		printf("Найден учащийся ");
	else
		printf("Не найден :( ");
}
