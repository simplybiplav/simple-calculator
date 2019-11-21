/*
 Part D
 Part D is an extension of Part C. Create a program that reads a text string with multiple numbers and operators and prints the result. But now it should be possible, among other things, to use () around partial expressions and the program must deal with arbitrary number of parameters. It is also advantageous to add some other operators%, ^ etc.
 
 A natural extension is also to create the program so that the text string can be entered at the start of the program from the command line.
 
 Example (The text at the back of the > is read during execution):
 
 Enter two numbers with an operator between> (2 + 3) * 5
 
 The answer to (2 + 3) * 5 is 25.
 
 
 
 Enter two numbers with an operator between> 4 + 5 + (7 + 4) * 3 + 4 * 4 + 9/3 + 4 * 12 - 3/4
 The answer to 4 + 5 + (7 + 4) * 3 + 4 * 4 + 9/3 + 4 * 12 - 3/4 is 108.25.
 
 */


#if 0
while there are tokens to be read do:
read a token.
if the token is a number, then:
push it to the output queue.
if the token is a function then:
push it onto the operator stack
if the token is an operator, then:
while ((there is a function at the top of the operator stack)
       or (there is an operator at the top of the operator stack with greater precedence)
       or (the operator at the top of the operator stack has equal precedence and is left associative))
and (the operator at the top of the operator stack is not a left parenthesis):
pop operators from the operator stack onto the output queue.
push it onto the operator stack.
if the token is a left paren (i.e. "("), then:
push it onto the operator stack.
if the token is a right paren (i.e. ")"), then:
while the operator at the top of the operator stack is not a left paren:
pop the operator from the operator stack onto the output queue.
/* if the stack runs out without finding a left paren, then there are mismatched parentheses. */
if there is a left paren at the top of the operator stack, then:
pop the operator from the operator stack and discard it
after while loop, if operator stack not null, pop everything to output queue
if there are no more tokens to read then:
while there are still operator tokens on the stack:
/* if the operator token on the top of the stack is a paren, then there are mismatched parentheses. */
pop the operator from the operator stack onto the output queue.
exit.


#endif

#include <iostream>

using namespace std;

int precedence(char op)
{
    if (op == '+' || op == '-' )
        return 1;
    if (op == '/' || op == '*')
        return 2;
    
    if (op == '^' || op == '%')
        return 3;
    
    return 0;
}

int IsBlank( char c)
{
    if ( c == ' ')
        return 1;
    return 0;
}

int topOfOperatorStack(char arr[], int array_size, int position,char& value)
{
    if (position < 0 )
    {
        // stack underflow
        return 0;
    }
    value = arr[position];
    return 1;
}

int popFromNumberStack(int arr[], int array_size, int& position, int &value)
{
    
    if (position < 0 )
    {
        // stack underflow
        return 0;
    }
    value = arr[position];
    position--;
    return 1;
    
}

int popFromOperatorStack(char arr[], int array_size, int& position,char& value)
{
    if (position < 0 )
    {
        // stack underflow
        return 0;
    }
    value = arr[position];
    position--;
    return 1;
}

int pushToNumberStack(int arr[],int array_size, int& position ,const int value )
{
    if (position >= (array_size -1))
    {
        // stack overflow
        return 0;
    }
    position++;
    arr[position] = value;
    return 1;
    
}

int pushToOperatorStack(char arr[],int array_size, int& position, const char value)
{
    
    if (position >= (array_size -1))
    {
        // stack overflow
        return 0;
    }
    position++;
    arr[position] = value;
    return 1;
}


int IsDigit(char c)
{
    int a = c - '0';
    if((a >=0) && (a <10))
    {
        return 1;
    }
    return 0;
}

int IsOperator(char c)
{
    if ( c == '+' || c == '-' || c == '*' ||
        c == '/' || c == '^' || c == '%')
    {
        return 1;
    }
    return 0;
    
}
int InvalidCharacter(char c)
{
    
    if (IsDigit(c)) return 0;
    if (IsOperator(c)) return 0;
    if (c=='(' || c ==')') return 0;
    return 1;
    
}

void InvalidUsage()
{
    
    cout << "Invalid Input"<<endl;
}
int applyOperation( int lvalue, char op, int rvalue, int &result)
{
    
    switch ( op )
    {
        case '+':
            result = lvalue + rvalue;
            break;
        case '-':
            result = lvalue - rvalue;
            break;
        case '*':
            result = lvalue * rvalue;
            break;
        case '/':
            result = lvalue / rvalue;
            break;
        case '^':
            result = lvalue ^ rvalue;
            break;
        case '%':
            result = lvalue % rvalue;
            break;
        default:
            result = 0;
            return 0;
    }
    
    return 1;
}
void UsageStackOverflow(string info)
{
    cout << "Stack Overflow : "<< info << endl;
}

void UsageStackUnderflow( string info)
{
    cout << "Stack Underflow:" << info <<endl;
}

int main(int argc, char** args)
{
#define NUMBER_STACK_SIZE 100
#define OPERATOR_STACK_SIZE 100
#define EXPRESSION_INDEX 1
    
    int numberStackPos = -1; // to keep track of number stack
    int operatorStackPos = -1; // to keep track of operator stack
    string expression;
    int numberStack[NUMBER_STACK_SIZE];
    char operatorStack[OPERATOR_STACK_SIZE];
    
    cout << " Please enter the Expression: > "<<endl;
    getline(cin,expression);
    if (expression.empty())
    {
        InvalidUsage();
        return 1;
    }
    
    for (int expressPos=0; expressPos < expression.size() ; expressPos++)
    {
        //check if it is a number and put into number stack
        if ( IsBlank(expression.at(expressPos)) )
        {
            continue;
        }
        else if ( IsDigit(expression.at(expressPos)))
        {
            int value = int(expression.at(expressPos) - '0');
            expressPos++;
            while( expressPos < expression.size() && IsDigit(expression.at(expressPos)))
            {
                value = 10 * value + int(expression.at(expressPos) - '0');
                expressPos++;
            }
            expressPos--;
            if ( ! pushToNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos,value)) UsageStackOverflow("Number Stack");
        }
        //check if it a operator
        else if ( IsOperator(expression.at(expressPos)))
        {
            char op = 0;
            if( topOfOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,op) &&
               (precedence(op) >=precedence(expression.at(expressPos))  )
               )
            {
                int lvalue,rvalue,result;
                // pop two numbers from number stack
                if ( !popFromNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos, rvalue) || ! popFromNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos, lvalue))
                {
                    UsageStackUnderflow("Number Stack");
                }
                
                // pop operator from operator Stack, already checked for underflow
                popFromOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,op);
                applyOperation(lvalue,op,rvalue,result);
                if ( ! pushToNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos,result)) UsageStackOverflow("Number Stack");
                
            }
            if ( ! pushToOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,expression.at(expressPos)) )
            {
                UsageStackOverflow( "Operator Stack");
            }
        }
        else if ( expression.at(expressPos) == '(' )
        {
            if ( ! pushToOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,expression.at(expressPos) ) )
            {
                UsageStackOverflow( "Operator Stack");
            }
            
        }
        else if ( expression.at(expressPos) == ')' )
        {
            char op = 0;
            while( topOfOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,op) &&
                  (op != '(')
                  )
            {
                int lvalue,rvalue,result;
                // pop two numbers from number stack
                if ( !popFromNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos, rvalue) || !popFromNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos, lvalue))
                {
                    UsageStackUnderflow("Number Stack");
                }
                
                if ( !popFromOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,op) )
                {
                    UsageStackUnderflow("Operator Stack");
                }
                applyOperation(lvalue,rvalue,op,result);
                if ( ! pushToNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos,result)) UsageStackOverflow("Number Stack");
                
            }
            
            if ( !popFromOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,op) || (op!='(') )
            {
                UsageStackUnderflow("Invalid Expression: Operator Stack");
            }
            
        }
    }
    
    char op;
    while( topOfOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,op))
    {
        int lvalue,rvalue,result;
        // pop two numbers from number stack
        if ( !popFromNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos, rvalue) || !popFromNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos, lvalue))
        {
            UsageStackUnderflow("Number Stack");
        }
        
        if ( !popFromOperatorStack(operatorStack, OPERATOR_STACK_SIZE, operatorStackPos,op) )
        {
            UsageStackUnderflow("Operator Stack");
        }
        applyOperation(lvalue,op,rvalue,result);
        if ( ! pushToNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos,result)) UsageStackOverflow("Number Stack");
        
    }
    
    if (numberStackPos != 0)
    {
        cout << "Invalid Expression" <<endl;
    }
    else
    {
        int value;
        popFromNumberStack(numberStack, NUMBER_STACK_SIZE, numberStackPos, value);
        cout << "Result of Expression :\n"<<expression << "\n" << "=" <<value <<endl;
    }
    
    return 0;
}
