#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef int element;
typedef struct {
    element* data;
    int capacity;
    int top;
}StackType;   //data�� �����ͷ�

void init_stack(StackType* sp)
{
    sp->top = -1;
    sp->capacity = 1;
    sp->data = (element*)malloc(sp->capacity * sizeof(element));
}

int is_empty(StackType* sp)
{
    return (sp->top == -1);
}
int is_full(StackType* sp)
{
    return (sp->top == (MAX_SIZE - 1));
}

void push(StackType* sp, element item)
{
    if (is_full(sp))
    {
        sp->capacity = sp->capacity * 2;
        sp->data = (element*)realloc(sp->data, sp->capacity * sizeof(element));
    }
    sp->data[++(sp->top)] = item;
}

element pop(StackType* sp)
{
    if (is_empty(sp))
    {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else
    {
        return sp->data[(sp->top)--];
    }
}

element peek(StackType* sp)
{
    if (is_empty(sp))
    {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else return sp->data[sp->top];
}


int check(char string[])
{
    StackType sp;
    int i = 0;
    init_stack(&sp);

    while (string[i] != NULL)
    {
        if ('a' <= string[i] && string[i] <= 'z')
        {
            push(&sp, string[i]);
        }
        else if ('A' <= string[i] && string[i] <= 'Z')
        {
            char c = string[i] + ('a' - 'A');   //�빮��->�ҹ���
            push(&sp, c);
        }
        i++;
    }
    i = 0;
    int j = 0;   //���ĺ��� �ƴ� �� ī��Ʈ 
    while (string[i + j] != NULL)
    {
        if (isalpha(string[i + j]) != 0)
        {
            if ('a' <= string[i + j] && string[i + j] <= 'z')
            {
                if (pop(&sp) != string[i + j])
                    return 0;
            }
            else if ('A' < string[i + j] && string[i + j] <= 'Z')
            {
                char a = string[i] + ('a' - 'A');
                if (pop(&sp) != a)
                    return 0;
            }
            i++;
        }
        else j++;   //���ĺ��� �ƴ� �� ī��Ʈ
    }
    return 1;
}

void string_remove(char* string)
{
    int i, j;
    for (i = 0, j = 0; string[i]; i++)
    {
        if (!isspace(string[i]) && !ispunct(string[i])) // ����� ������ ��� ����
        {
            string[j++] = tolower(string[i]);
        }
    }
    string[j] = '\0';
}


int main()
{
    char string[MAX_SIZE] = { NULL };
    char re[MAX_SIZE];

    while (1)
    {
        printf("���ڿ��� �Է��Ͻÿ�: ");
        gets_s(string, sizeof(string));
        string_remove(string);
        if (check(string) == 1)
        {
            printf("ȸ���Դϴ�.\n\n");
        }
        else
        {
            printf("ȸ���� �ƴմϴ�.\n\n");
        }
        printf("��� �Է��Ͻðڽ��ϱ�?(Yes/No): ");
        fgets(re, sizeof(re), stdin) != NULL;
        if (strcmp(re, "Yes\n") == 0)
            continue;
        else if (strcmp(re, "No\n") == 0)
            break;
        else
            break;
    }
}