#define _CRT_SECURE_NO_WARNINGS
/*
 * 10以内加减法练习系统
 * C语言程序设计结课大作业
 * 交互式答题版本
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 /*
  * 函数声明
  */
void makeEx(char e[], int* correctAnswer);  // 生成一道题目并返回正确答案
int addEx(char e[], char es[30][15], int answers[30], int num, int ans);  // 比对并添加题目
void startQuiz(char es[30][15], int answers[30]);  // 开始交互式答题

/*
 * 主函数
 */
int main() {
    char e[15];                  // 存储一道新生成的题目
    char es[30][15];             // 存储全部30道不重复的题目
    int answers[30];             // 存储每道题的正确答案
    int n = 0;                   // 已生成的题目数

    printf("========================================\n");
    printf("      10以内加减法练习系统\n");
    printf("========================================\n\n");

    // 设置随机数种子，产生真随机数
    srand(time(NULL));

    printf("正在生成题目...\n\n");

    // 生成30道不重复的题目
    while (n < 30) {
        int ans;
        makeEx(e, &ans);                          // 生成一道题目和正确答案
        n = addEx(e, es, answers, n, ans);        // 比对并添加
    }

    // 开始交互式答题
    startQuiz(es, answers);

    return 0;
}

/*
 * 试题生成模块 makeEx
 * 功能：随机生成一道10以内的加减法题目
 * 参数：e[15] - 用于存储生成的题目字符串
 *       correctAnswer - 用于返回题目的正确答案
 */
void makeEx(char e[], int* correctAnswer) {
    int type;       // 题目类型：0-加法，1-减法
    int bracketPos; // 括号位置：0-左侧，1-中间，2-右侧
    int a, b, c;    // 运算数和结果

    // 随机产生题目类型：加法或减法
    type = rand() % 2;

    if (type == 0) {
        // 加法：加数与和均不超过10
        a = rand() % 11;           // 第一个加数 0-10
        b = rand() % (11 - a);     // 第二个加数 0-(10-a)
        c = a + b;
    }
    else {
        // 减法：被减数、减数不超过10，差≥0
        a = rand() % 11;           // 被减数 0-10
        b = rand() % (a + 1);      // 减数 0-a
        c = a - b;
    }

    // 随机产生括号位置
    bracketPos = rand() % 3;

    // 根据括号位置确定正确答案并生成题目字符串
    if (type == 0) {
        // 加法题目
        switch (bracketPos) {
        case 0:  // 括号在左侧：( ) + b = c，答案是a
            sprintf(e, "(  ) + %d = %d", b, c);
            *correctAnswer = a;
            break;
        case 1:  // 括号在中间：a + ( ) = c，答案是b
            sprintf(e, "%d + (  ) = %d", a, c);
            *correctAnswer = b;
            break;
        case 2:  // 括号在右侧：a + b = ( )，答案是c
            sprintf(e, "%d + %d = (  )", a, b);
            *correctAnswer = c;
            break;
        }
    }
    else {
        // 减法题目
        switch (bracketPos) {
        case 0:  // 括号在左侧：( ) - b = c，答案是a
            sprintf(e, "(  ) - %d = %d", b, c);
            *correctAnswer = a;
            break;
        case 1:  // 括号在中间：a - ( ) = c，答案是b
            sprintf(e, "%d - (  ) = %d", a, c);
            *correctAnswer = b;
            break;
        case 2:  // 括号在右侧：a - b = ( )，答案是c
            sprintf(e, "%d - %d = (  )", a, b);
            *correctAnswer = c;
            break;
        }
    }
}

/*
 * 比对添加模块 addEx
 * 功能：检查新生成的题目是否重复，不重复则添加
 * 参数：e - 新生成的题目
 *       es - 已有的题目数组
 *       answers - 正确答案数组
 *       num - 已有题目数量
 *       ans - 新题目的正确答案
 * 返回：更新后的题目数量
 */
int addEx(char e[], char es[30][15], int answers[30], int num, int ans) {
    int i;

    // 检查是否重复
    for (i = 0; i < num; i++) {
        if (strcmp(e, es[i]) == 0) {
            // 题目重复，不添加
            return num;
        }
    }

    // 题目不重复，添加到数组中
    strcpy(es[num], e);
    answers[num] = ans;
    return num + 1;
}

/*
 * 交互式答题模块 startQuiz
 * 功能：逐题显示，接收用户输入，判题，统计成绩
 * 参数：es - 存储所有题目的数组
 *       answers - 存储所有题目的正确答案
 */
void startQuiz(char es[30][15], int answers[30]) {
    int i;
    int userAnswer;
    int correctCount = 0;     // 答对题数
    int wrongCount = 0;       // 答错题数
    int score;                // 最终得分（百分制）
    float accuracy;           // 正确率

    printf("题目生成完成！共30道题，准备好了吗？\n");
    printf("请在每道题后输入括号中应填的数字，按回车确认\n\n");
    printf("按回车键开始答题...");
    getchar();  // 等待用户按回车
    printf("\n");

    // 逐题答题
    for (i = 0; i < 30; i++) {
        printf("【第 %2d/30 题】 %s  请输入答案：", i + 1, es[i]);
        scanf("%d", &userAnswer);

        // 判题
        if (userAnswer == answers[i]) {
            printf("         回答正确！\n\n");
            correctCount++;
        }
        else {
            printf("         回答错误！正确答案是：%d\n\n", answers[i]);
            wrongCount++;
        }
    }

    // 计算成绩
    score = (int)((float)correctCount / 30 * 100 + 0.5);  // 百分制，四舍五入
    accuracy = (float)correctCount / 30 * 100;

    // 输出成绩报告
    printf("========================================\n");
    printf("            答题完成！\n");
    printf("========================================\n\n");
    printf(" 成绩报告\n");
    printf("----------------------------------------\n");
    printf("  总题数：    30 道\n");
    printf("  答对题数：  %d 道\n", correctCount);
    printf("  答错题数：  %d 道\n", wrongCount);
    printf("  最终得分：  %d 分（百分制）\n", score);
    printf("  正确率：    %.1f%%\n", accuracy);
    printf("----------------------------------------\n");

    // 成绩评价
    if (score >= 90) {
        printf("\n 优秀！继续保持！\n");
    }
    else if (score >= 80) {
        printf("\n 良好！再接再厉！\n");
    }
    else if (score >= 60) {
        printf("\n 及格！还需多加练习！\n");
    }
    else {
        printf("\n 加油！多多练习一定会进步的！\n");
    }

    printf("\n========================================\n");
    printf("         感谢使用本练习系统\n");
    printf("========================================\n");
}
