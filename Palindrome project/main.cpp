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
}StackType;   //data는 포인터로

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
        fprintf(stderr, "스택 공백 에러\n");
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
        fprintf(stderr, "스택 공백 에러\n");
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
            char c = string[i] + ('a' - 'A');   //대문자->소문자
            push(&sp, c);
        }
        i++;
    }
    i = 0;
    int j = 0;   //알파벳이 아닌 것 카운트 
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
        else j++;   //알파벳이 아닌 것 카운트
    }
    return 1;
}

void string_remove(char* string)
{
    int i, j;
    for (i = 0, j = 0; string[i]; i++)
    {
        if (!isspace(string[i]) && !ispunct(string[i])) // 공백과 구두점 모두 제거
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
        printf("문자열을 입력하시오: ");
        gets_s(string, sizeof(string));
        string_remove(string);
        if (check(string) == 1)
        {
            printf("회문입니다.\n\n");
        }
        else
        {
            printf("회문이 아닙니다.\n\n");
        }
        printf("계속 입력하시겠습니까?(Yes/No): ");
        fgets(re, sizeof(re), stdin) != NULL;
        if (strcmp(re, "Yes\n") == 0)
            continue;
        else if (strcmp(re, "No\n") == 0)
            break;
        else
            break;
    }
}