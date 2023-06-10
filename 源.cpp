#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000
#define ID_LENGTH 50
#define NAME_LENGTH 50
#define GENDER_LENGTH 10
#define FILE_PATH "ѧ���ɼ�.txt"

typedef struct {
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    char gender[GENDER_LENGTH];
    float score;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void menu();
void add_student();
void display_students();
void delete_student();
void modify_student();
void find_student();
void sort_student();
void calculate_statistics();
void read_students_from_file();
void write_students_to_file();

int main() {
    read_students_from_file();
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            add_student();
            break;
        case 2:
            delete_student();
            break;
        case 3:
            modify_student();
            break;
        case 4:
            find_student();
            break;
        case 5:
            display_students();
            break;
        case 6:
            calculate_statistics();
            break;
        case 7:
            sort_student();
            break;
        case 0:
            write_students_to_file();
            printf("�������˳�\n");
            return 0;
        default:
            printf("��Ч��ѡ�����������\n");
        }
    }

    return 0;
}

void menu() {
    system("cls");
    printf("*********************\n");
    printf("**ѧ���ɼ�����ϵͳ**\n");
    printf("**  ���ߣ���ٶ־  **\n");
    printf("**1. ���ѧ����Ϣ**\n");
    printf("**2. ɾ��ָ��ѧ��**\n");
    printf("**3. �޸�ѧ����Ϣ**\n");
    printf("**4. ���ҵ���ѧ��**\n");
    printf("**5. ��ʾѧ����Ϣ**\n");
    printf("**6. ѧ���ɼ�ͳ��**\n");
    printf("**7. ѧ����Ϣ����**\n");
    printf("**0.     �˳�    **\n");
    printf("**  ������ѡ��:  **\n");
    printf("*********************\n");
}

void add_student() {
    char continue_input = 'y';
    while (continue_input == 'y' || continue_input == 'Y') {
        if (student_count >= MAX_STUDENTS) {
            printf("ѧ�����������ѳ������ޣ��޷��������\n");
            return;
        }

        Student new_student;
        printf("������ѧ��ѧ��: ");
        scanf("%s", new_student.id);
        getchar();

        printf("������ѧ������: ");
        scanf("%s", new_student.name);
        getchar();

        printf("������ѧ���Ա�: ");
        scanf("%s", new_student.gender);
        getchar();

        printf("������ѧ���ɼ�: ");
        scanf("%f", &new_student.score);
        getchar();

        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].name, new_student.name) == 0 || strcmp(students[i].id, new_student.id) == 0) {
                printf("������ͬ��������ѧ�ţ��޷����\n");
                return;
            }
        }

        students[student_count++] = new_student;
        printf("��ӳɹ�\n");

        printf("�Ƿ����������һ��ѧ����(Y/N): ");
        scanf(" %c", &continue_input);
        getchar();
    }
    system("pause");
}

void display_students() {
    printf("ѧ��\t����\t�Ա�\t�ɼ�\n");
    for (int i = 0; i < student_count; i++) {
        printf("%s\t%s\t%s\t%.1f\n", students[i].id, students[i].name, students[i].gender, students[i].score);
    }
    system("pause");
}

void delete_student() {
    char id[ID_LENGTH];
    printf("������Ҫɾ����ѧ����ѧ��: ");
    scanf("%s", id);
    getchar();

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("ɾ���ɹ�\n");
            system("pause");
            return;
        }
    }

    printf("δ�ҵ�ָ��ѧ�ŵ�ѧ��\n");
    system("pause");
}

void modify_student() {
    char id[ID_LENGTH];
    printf("������Ҫ�޸ĵ�ѧ����ѧ��: ");
    scanf("%s", id);
    getchar();

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("�������µ�ѧ������: ");
            scanf("%s", students[i].name);
            getchar();

            printf("�������µ�ѧ���Ա�: ");
            scanf("%s", students[i].gender);
            getchar();

            printf("�������µ�ѧ���ɼ�: ");
            scanf("%f", &students[i].score);
            getchar();
            printf("�޸ĳɹ�\n");
            system("pause");
            return;
        }
    }

    printf("δ�ҵ�ָ��ѧ�ŵ�ѧ��\n");
    system("pause");
}

void find_student() {
    char name[NAME_LENGTH];
    printf("������Ҫ���ҵ�ѧ��������: ");
    scanf("%s", name);
    getchar();

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("ѧ��: %s\n", students[i].id);
            printf("����: %s\n", students[i].name);
            printf("�Ա�: %s\n", students[i].gender);
            printf("�ɼ�: %.1f\n", students[i].score);
            system("pause");
            return;
        }
    }

    printf("δ�ҵ�ָ��������ѧ��\n");
    system("pause");
}

void sort_student() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - 1 - i; j++) {
            if (students[j].score < students[j + 1].score) {
                // ����λ��
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("ѧ����Ϣ�Ѱ��ɼ�����\n");
    printf("****************************\n");
    display_students();
}

void calculate_statistics() {
    // ��ʼ��ͳ�Ʊ���
    int count = 0;
    float min_score = 100.0;
    float max_score = 0.0;
    float total_score = 0.0;

    for (int i = 0; i < student_count; i++) {
        float score = students[i].score;
        total_score += score;
        count++;

        if (score < min_score) {
            min_score = score;
        }
        if (score > max_score) {
            max_score = score;
        }
    }

    float average_score = total_score / count;

    printf("ѧ������: %d\n", count);
    printf("��ͳɼ�: %.1f\n", min_score);
    printf("��߳ɼ�: %.1f\n", max_score);
    printf("ƽ���ɼ�: %.1f\n", average_score);
    system("pause");
}

void read_students_from_file() {
    FILE* file = fopen(FILE_PATH, "r");
    if (!file) {
        printf("�޷����ļ�\n");
        return;
    }

    Student student;
    while (fscanf(file, "%s %s %s %f", student.id, student.name, student.gender, &student.score) == 4) {
        students[student_count++] = student;
    }
    printf("��ȡ�ɹ�\n");
    fclose(file);
}

void write_students_to_file() {
    FILE* file = fopen(FILE_PATH, "w");
    if (!file) {
        printf("�޷����ļ�\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s %s %s %.1f\n", students[i].id, students[i].name, students[i].gender, students[i].score);
    }
    printf("д��ɹ�\n");
    fclose(file);
}