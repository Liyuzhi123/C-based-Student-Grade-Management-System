#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000
#define ID_LENGTH 50
#define NAME_LENGTH 50
#define GENDER_LENGTH 10
#define FILE_PATH "学生成绩.txt"

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
            printf("程序已退出\n");
            return 0;
        default:
            printf("无效的选项，请重新输入\n");
        }
    }

    return 0;
}

void menu() {
    system("cls");
    printf("*********************\n");
    printf("**学生成绩管理系统**\n");
    printf("**  作者：李俣志  **\n");
    printf("**1. 添加学生信息**\n");
    printf("**2. 删除指定学生**\n");
    printf("**3. 修改学生信息**\n");
    printf("**4. 查找单个学生**\n");
    printf("**5. 显示学生信息**\n");
    printf("**6. 学生成绩统计**\n");
    printf("**7. 学生信息排序**\n");
    printf("**0.     退出    **\n");
    printf("**  请输入选择:  **\n");
    printf("*********************\n");
}

void add_student() {
    char continue_input = 'y';
    while (continue_input == 'y' || continue_input == 'Y') {
        if (student_count >= MAX_STUDENTS) {
            printf("学生储存数量已超过上限，无法继续添加\n");
            return;
        }

        Student new_student;
        printf("请输入学生学号: ");
        scanf("%s", new_student.id);
        getchar();

        printf("请输入学生姓名: ");
        scanf("%s", new_student.name);
        getchar();

        printf("请输入学生性别: ");
        scanf("%s", new_student.gender);
        getchar();

        printf("请输入学生成绩: ");
        scanf("%f", &new_student.score);
        getchar();

        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].name, new_student.name) == 0 || strcmp(students[i].id, new_student.id) == 0) {
                printf("存在相同的姓名或学号，无法添加\n");
                return;
            }
        }

        students[student_count++] = new_student;
        printf("添加成功\n");

        printf("是否继续输入下一个学生？(Y/N): ");
        scanf(" %c", &continue_input);
        getchar();
    }
    system("pause");
}

void display_students() {
    printf("学号\t姓名\t性别\t成绩\n");
    for (int i = 0; i < student_count; i++) {
        printf("%s\t%s\t%s\t%.1f\n", students[i].id, students[i].name, students[i].gender, students[i].score);
    }
    system("pause");
}

void delete_student() {
    char id[ID_LENGTH];
    printf("请输入要删除的学生的学号: ");
    scanf("%s", id);
    getchar();

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("删除成功\n");
            system("pause");
            return;
        }
    }

    printf("未找到指定学号的学生\n");
    system("pause");
}

void modify_student() {
    char id[ID_LENGTH];
    printf("请输入要修改的学生的学号: ");
    scanf("%s", id);
    getchar();

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("请输入新的学生姓名: ");
            scanf("%s", students[i].name);
            getchar();

            printf("请输入新的学生性别: ");
            scanf("%s", students[i].gender);
            getchar();

            printf("请输入新的学生成绩: ");
            scanf("%f", &students[i].score);
            getchar();
            printf("修改成功\n");
            system("pause");
            return;
        }
    }

    printf("未找到指定学号的学生\n");
    system("pause");
}

void find_student() {
    char name[NAME_LENGTH];
    printf("请输入要查找的学生的姓名: ");
    scanf("%s", name);
    getchar();

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("学号: %s\n", students[i].id);
            printf("姓名: %s\n", students[i].name);
            printf("性别: %s\n", students[i].gender);
            printf("成绩: %.1f\n", students[i].score);
            system("pause");
            return;
        }
    }

    printf("未找到指定姓名的学生\n");
    system("pause");
}

void sort_student() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - 1 - i; j++) {
            if (students[j].score < students[j + 1].score) {
                // 交换位置
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("学生信息已按成绩排序\n");
    printf("****************************\n");
    display_students();
}

void calculate_statistics() {
    // 初始化统计变量
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

    printf("学生数量: %d\n", count);
    printf("最低成绩: %.1f\n", min_score);
    printf("最高成绩: %.1f\n", max_score);
    printf("平均成绩: %.1f\n", average_score);
    system("pause");
}

void read_students_from_file() {
    FILE* file = fopen(FILE_PATH, "r");
    if (!file) {
        printf("无法打开文件\n");
        return;
    }

    Student student;
    while (fscanf(file, "%s %s %s %f", student.id, student.name, student.gender, &student.score) == 4) {
        students[student_count++] = student;
    }
    printf("读取成功\n");
    fclose(file);
}

void write_students_to_file() {
    FILE* file = fopen(FILE_PATH, "w");
    if (!file) {
        printf("无法打开文件\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s %s %s %.1f\n", students[i].id, students[i].name, students[i].gender, students[i].score);
    }
    printf("写入成功\n");
    fclose(file);
}