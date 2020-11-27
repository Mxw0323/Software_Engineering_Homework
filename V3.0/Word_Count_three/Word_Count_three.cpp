// Word_Count_two.c : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Count(char* file); // 计数文件内统计量多少
void Disp_help();   // 打印帮助信息

int file_chars = 0;     // 初始字母数为0
int file_words = 0;     // 初始单词数为0
int file_sentences = 0;     // 初始句子数为0
int file_lines = 0;     // 初始行数为0
int file_blanklines = 0;     // 初始空行数为0 
int file_explainlines = 0;   // 初始注释行为0
int n;
char new_char[4];            // 临时存储变量

int main(int argc, char* argv[])
{
    FILE* fp;
    /*对输出参数的粗略判断*/
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        Disp_help();
        return 0;
    }
    else if (argc == 3)
    {
        /*判断是否为txt文件*/
        n = strlen(argv[2]);
        new_char[0] = argv[2][n - 4];
        new_char[1] = argv[2][n - 3];
        new_char[2] = argv[2][n - 2];
        new_char[3] = argv[2][n - 1];
        if (strcmp(new_char, ".txt") == 0)                   // 如果不是txt文件，报错
        {
            printf("该文件不是 .txt 文件，本程序只对 .txt 文件生效\n");
            printf("请重新输入命令选择 .txt 文件以执行");
        }
        else
        {
            /*判断文件是否能正常打开*/
            if ((fp = fopen(argv[2], "r")) == NULL)
            {
                printf("该文件不存在/拒绝访问\n");
                return 0;
            }

            Count(argv[2]);                      // 计数.txt 文件中各统计量的数量

            if (strcmp(argv[1], "-c") == 0)                   // -c 统计文件字符数
                printf("文件 %s 字符数为:%d\n", argv[2], file_chars);
            else if (strcmp(argv[1], "-w") == 0)                   // -w 统计文件单词数
                printf("文件 %s 单词数为:%d\n", argv[2], file_words);
            else if (strcmp(argv[1], "-s") == 0)                  // -s 统计文件句子数
                printf("文件 %s 句子数为%d\n", argv[2], file_sentences);
            else if (strcmp(argv[1], "-l") == 0)                  // -l 统计文件行数
                printf("文件 %s 行数为%d\n", argv[2], file_lines);
            else if (strcmp(argv[1], "-b") == 0)                  // -b 统计文件空行数
                printf("文件 %s 空行数为%d\n", argv[2], file_blanklines);
            else if (strcmp(argv[1], "-e") == 0)                  // -h 统计文件注释行数
                printf("文件 %s 注释行数为%d\n", argv[2], file_explainlines);
            else                                                  // 打印“没有该命令”，可使用"-h"获取帮助
                printf("该指令不存在\n可使用 Word_Count_three.exe -h 获取帮助文档\n");
            return 0;
        }
    }
    else
    {
        printf("该指令不存在\n可使用 Word_Count_three.exe -h 获取帮助文档\n");
    }
    return 0;
}

/*打印帮助指南*/
void Disp_help()
{
    printf("统计纯英文 .txt 文件中的字符、单词、句子数等");
    printf("\n");
    printf("Word_Count_three.exe [-h]\n");
    printf("Word_Count_three.exe [-c] [-w] [-s] [-l] [-b] [-e] [[file_name].txt]\n");
    printf("\tfile_name   指当前目录下的 .txt 文件名\n");
    printf("\t-h\t显示当前程序的帮助文档\n");
    printf("\t-c\t显示 .txt 文件内的字符数\n");
    printf("\t-w\t显示 .txt 文件内的单词数\n");
    printf("\t-s\t显示 .txt 文件内的句子数\n");
    printf("\t-l\t显示 .txt 文件内的初始行数\n");
    printf("\t-b\t显示 .txt 文件内的空行数\n");
    printf("\t-e\t显示 .txt 文件内的注释行数\n");
}

/*统计文件内部各统计量多少*/
void Count(char* file)
{
    FILE* fp;
    char a, b = 'a';
    if ((fp = fopen(file, "r")) == NULL)
    {
        printf("读文件失败！\n");
        exit(-1);
    }
    while (!feof(fp))
    {
        a = fgetc(fp);
        file_chars++;

        if (a == '/')
        {
            if (b == '/')
            {
                file_explainlines++;
            }
        }

        if (a == ' ' || a == '\n' || a == '\t' || a == ',' || a == '.' || a == '!' || a == ';' || a == '\0' || a == '/' || a == '?')
        {
            if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
            {
                file_words++;
            }
            if (a == '.' || a == '!' || a == '?')
            {
                file_sentences++;
                b = a;
            }
            else if (a == '\n')
            {
                file_lines++;
                if (b == '\n')
                {
                    file_blanklines++;
                    b = a;
                }
                else
                    b = a;
            }
            else
                b = a;
        }
        else
            b = a;
    }
    if (b != ' ' && b != '\n' && b != '\t' && b != ',' && b != '.' && b != '!' && b != ';')
    {
        file_words++;
    }			//最后一行只有单词时，单词数不会加 
    if (b == '\n')
    {
        file_blanklines++;
    }	      	//最后一行为空行循环不会记入 
    file_chars -= 2;          //文件最后字符数'\0'会加一
    file_lines++;
    fclose(fp);
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
