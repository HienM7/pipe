#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define SIZE 1024 * 10
#define MAX 4000
#define STRING 1000

// char ERROR[] = "Error. Invalid math expression.";
// Stack_Char
typedef struct stack_char {
	char elements[MAX];
	int top;
} Stack_Char;


int isEmpty(Stack_Char *S) {
	return S->top == -1;
}

int isFull(Stack_Char *S) {
	return S->top == MAX - 1;
}

void createStack(Stack_Char *S) {
	S->top = -1;
}

void push(Stack_Char *S, char a) {
	if(!isFull(S)) {
		S->elements[++S->top] = a;
	}
  return 0;
}

char pop(Stack_Char *S) {
	if(!isEmpty(S)) {
		return S->elements[S->top--];
	}
  return 0;
}

char peek(Stack_Char *S) {
	if(!isEmpty(S)) {
		return S->elements[S->top];
	}
  return 0;
}

void print(Stack_Char S) {
	int i;
	for(i=0;i<=S.top;i++){
		printf("%c ",S.elements[i]);
	}
}

//Stack float
typedef struct stack_float {
	float elements[MAX];
	int top;
} Stack_Float;


int isEmptyFloat(Stack_Float *S) {
	return S->top == -1;
}

int isFullFloat(Stack_Float *S) {
	return S->top == MAX - 1;
}

void createStackFloat(Stack_Float *S) {
	S->top = -1;
}

void pushFloat(Stack_Float *S, float a) {
	if(!isFull(S)) {
		S->elements[++S->top] = a;
	}
  return 0;
}

float popFloat(Stack_Float *S) {
	if(!isEmpty(S)) {
		return S->elements[S->top--];
	}
  return 0;
}

float peekFloat(Stack_Float *S) {
	if(!isEmpty(S)) {
		return S->elements[S->top];
	}
  return 0;
}

void printFloat(Stack_Float S) {
	int i;
	for(i=0;i<=S.top;i++){
		printf("%f ",S.elements[i]);
	}
  printf("\n");
}
// END Stack_Float

// Thu tu uu tien cac toan tu

int ktUuTien(char a) {
  switch(a) {
    case '-': return 0;
    case '+': return 0;
    case '*': return 1;
    case '/': return 1;
  }
}

int ktToanHang(char a) {
	if ((a >= '0' && a <= '9') || a == '.')
		return 1;
	return 0;
}

int ktToanTu(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 1;
	return 0;
}

int ktBieuThuc(char bt[]) {
	int open = 0;
	int close = 0;
	for (int i = 0; i < strlen(bt); i++) {
		if (ktToanTu(bt[i]) && ktToanTu(bt[i + 1]))           ///kiem tra du lieu dau vao`
			return 0;
		if ((bt[i] >= 97 && bt[i] <= 122) || (bt[i] >= 65 && bt[i] <= 90))
			return 0;
    if ( !ktToanTu(bt[i]) && !ktToanHang(bt[i]) && bt[i] != ')'&& bt[i] != '(') 
      return 0;
		if (bt[i] == ')') open += 1;
		if (bt[i] == '(') close += 1;
	}
	if (open != close) return 0;
	return 1;
}


/*********************ham` chuyen tu 1 bieu thuc trung to--->hau to *************/


int conver(char infix[], char postfix[]) {
	Stack_Char myStack;
	createStack(&myStack);
	int count = 0;

	// for (int i = 0; i < strlen(infix); i++) {
	// 	if (ktToanTu(infix[i]) && ktToanTu(infix[i + 1]))           ///kiem tra du lieu dau vao`
	// 		return 0;
	// 	if ((infix[i] >= 97 && infix[i] <= 122) || (infix[i] >= 65 && infix[i] <= 90))
	// 		return 0;
  //   // if ( !ktToanTu(infix[i])|| !ktToanHang(infix[i])) 
  //   //   return 0;
	// }

	for (int i = 0; i < strlen(infix); i++) {
		char ch = infix[i];
		if (ktToanHang(ch)) {
			postfix[count++] = ch;
			if (ktToanTu(infix[i + 1]))
				postfix[count++] = ' '; //dau cach dung de phan biet giua cac so co nhieu chu so voi nhau
		}
		if (ch == '(')
			push(&myStack,ch);
		if (ktToanTu(ch)) {
			if (!isEmpty(&myStack)) {
        while (1) {
          if (ktToanTu(peek(&myStack)) && ktUuTien(ch) <= ktUuTien(peek(&myStack))) {
            char m;
            m = pop(&myStack);
            postfix[count++] = m;
          }
          else {
            push(&myStack,ch);
            break;
          }
        }
			}
			else
				push(&myStack,ch);
		}
		if (ch == ')') {   // neu Phat hien dau ) thi ta pop cho toi khi gap dau '(" thi` dung`
			char d;
			while (1) {
				d=pop(&myStack);
				if (d == '(')
					break;
				postfix[count++] = d;
			}
		}
	}

	// lay toan tu con lai trong Stack_Char...
	while (!isEmpty(&myStack)) {
		char m;
		// char n;
		m = pop(&myStack);
		postfix[count++] = m;
	}

	postfix[count] = '\0';
}

// Tinh toan bieu thuc hau to
float calculate(char infix[SIZE])
{
  Stack_Float S;
  createStackFloat(&S);
  char postfix[MAX];
	char *p;
	float op1, op2, result;
  conver(infix, postfix);
  // for (int i = 0; i < strlen(postfix); i++) {
  //   printf("%c", postfix[i]);
  // }
	p = &postfix[0];
  
	// while (*p != '\0')
   while(*p != '\0')
	{
    if (*p == ' ')
      p++;
		if (ktToanHang(*p))
		{
			char stringNumber[STRING];
      int index = 0;
			while (ktToanHang(*p))
			{ 
        stringNumber[index++] = *p;
				p++;
			}
      stringNumber[index] = '\0';
      float num = atof(stringNumber);

			pushFloat(&S, num);
      // printFloat(S);

		}
		if (ktToanTu(*p))
		{ 
			op1 = popFloat(&S);
			op2 = popFloat(&S);
      // printf("(%f %c %f)", op1, *p, op2);
      // printf("%f ***", op2);

			switch (*p)
			{
			case '+':
				result = op2 + op1;
				break;
			case '-':
				result = op2 - op1;
				break;
			case '/':
				result = op2 / op1;
				break;
			case '*':
				result = op2 * op1;
				break;
			default:
				printf("\nInvalid Operator");
				return 0;
			}
      // printf("\n~~~~%f~~~~~\n", result);
			pushFloat(&S, result);
      // printFloat(S);
		}
		p++;
	}
	result = popFloat(&S);
	return result;
}

void reader(FILE* stream)
{
  char buffer[SIZE];
  if(!feof(stream) && !ferror(stream) && fgets(buffer,sizeof(buffer),stream) != NULL) {
    fputs(buffer,stdout);
  } else {
    fputs("Something went wrong (Invalid expression...)\n",stdout);
  }
}


int main()
{

	char inputString[SIZE];
	printf("---------- Start -----------\n");

	while(1) {
		printf("Enter expression : ");
		fflush(stdin);
		gets(inputString);
		if (ktBieuThuc(inputString)) {
			break;
		}
		printf("Invalid expression. Please try again\n");
	}
  


	////////
  int fds_1[2]; //pipe 1 (result)
  int fds_2[2]; //pipe 2 (inputString)

  pid_t pid;
  pipe(fds_1);
  pipe(fds_2);

  pid = fork();
  if(pid == (pid_t) 0)
  {
    /* Child */
    sleep(1);
    FILE* stream;
    close(fds_2[1]);
    stream = fdopen(fds_2[0], "r");

    char buffer[SIZE];
    fgets(buffer,sizeof(buffer),stream);
    if(sizeof(buffer)>0){
        printf("\n%s\n", "---------- Start B -----------");
    }
    char strReceive[SIZE];
    char result[SIZE] = "Result: ";
    char tmpStr[SIZE];

    // Read inputString from parent
    sscanf(buffer, "%s", &strReceive);
    printf("Process B receive expression is %s\n", strReceive);
    close(fds_2[0]);
    printf("%s\n", "Do calculating ...");

    sprintf(tmpStr, "%3.3f", calculate(strReceive));     //tmpStr = calculate(strReceive)
		if (strcmp(result) )
    strcat(result, tmpStr);                          //result += tmpStr

    printf("%s\n", "Done calculate");
    printf("%s\n", "Process B send back result to process A");
    // Write back data (result) to parent.
    close(fds_1[0]);
    stream = fdopen(fds_1[1], "w");
    fprintf(stream, "%s\n", result);
    fflush(stream);
    printf("%s\n", "---------- End B -----------");
    close(fds_1[1]);
  }
  else
  {
    /* Parent */
    FILE* stream;
    close(fds_2[0]);
    stream = fdopen(fds_2[1], "w");

    // The string (inputString) write to child process for calculate.
    printf("\n%s\n", "---------- Start A -----------");
    // char inputString[SIZE];
    // printf("Enter expression : ");
  	// fflush(stdin);
  	// gets(inputString);
    printf("Writing expression str = %s to child process for calculate.\n", inputString);
    fprintf(stream, "%s\n", inputString);
    fflush(stream);
    close(fds_2[1]);
    sleep(1);

    // Get back data (result) send from child.
    close(fds_1[1]);
    stream = fdopen(fds_1[0], "r");
    printf("\n%s\n", "Process A wait for get data send back from B.");
    reader(stream);
    printf("%s\n", "---------- End A -----------");
    close(fds_1[0]);
  }
  return 0;
}
