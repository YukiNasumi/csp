#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct stack {
    char* base;
    char* top;
    int stacksize;
} SqStack;

int InitStack(SqStack* s) {
	s->base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	if (!s->base) exit(0);
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return 1;
}

int StackEmpty(SqStack* s) {
	return s->top == s->base;
}

int DestroyStack(SqStack* s) {
	if (s->base) {
		free(s->base);
		s->base = NULL;
		s->top = NULL;
		s->stacksize = 0;
		return 1;
	}
	return 0;
}

int Push(SqStack* s, char e) {
	if (s->top - s->base >= s->stacksize) {
		s->base = (char*)realloc(s->base, (s->stacksize + STACKINCREMENT) * sizeof(char));
		if (!s->base) exit(0);
		s->top = s->base + s->stacksize;
		s->stacksize += STACKINCREMENT;
	}
	*s->top++ = e;
	return 1;
}

int Pop(SqStack* s, char* e) {
	if (s->base == s->top) return 0;
	else {
		*e = *--s->top;
	}
	return 1;
}

//ºÏ≤È¿®∫≈ «∑Ò∆•≈‰
int CheckParenthesesMatching(char* expr) {
	SqStack s;
	char e;

	InitStack(&s);
	for (int i = 0; i < strlen(expr); i++) {
		char c = expr[i];
		if (c == '(' || c == '[' || c == '{') {
			Push(&s, c);
		}
		else if (c == ')' || c == ']' || c == '}') {
			if (StackEmpty(&s)) {
				DestroyStack(&s);
				return 0;
			}
			Pop(&s, &e);
			if ((c == ')' && e != '(') ||
				(c == ']' && e != '[') ||
				(c == '}' && e != '{')) {
				DestroyStack(&s);
				return 0;
			}
		}
	}
	int flag = StackEmpty(&s);
	if (flag) DestroyStack(&s);
	return flag;
}

int main() {
	char expr[100];
	printf("«Î ‰»Î“ª∏ˆ±Ì¥Ô Ω: ");
	scanf("%s", expr);

	if (CheckParenthesesMatching(expr)) {
		printf("¿®∫≈∆•≈‰’˝»∑£°\n");
	}
	else {
		printf("¿®∫≈∆•≈‰¥ÌŒÛ£°\n");
	}
	return 0;
}