#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "functions.h"

// Tokens
#define NUMBER  "NUMBER"
#define CMD     "CMD"
#define PLUS    "PLUS"
#define MINUS   "MINUS"
#define MUL     "MUL"
#define DIV     "DIV"
#define MOD     "MOD"
#define EXP     "EXP"
#define LPAREN  "("
#define RPAREN  ")"
#define EOFILE  "EOFILE"



/*  Begin Tokens  */
typedef struct
{
    char *type;
    double value;
} Tokens;

// Initialize variables
void
token_init(Tokens *self_token, char *type_arg, double value_arg)
{
    self_token->type = type_arg;
    self_token->value = value_arg;

    // printf("Token('%s', '%lf')\n", self_token->type, self_token->value);
}
/*  End Tokens  */


/*  Begin Lexer  */
typedef struct
{
    char *text;
    unsigned int pos;
    char current_char;
} Lexer;

// void
// lexer_print(Lexer *self_lexer)
// {
//     printf("Lexer:\n  text = \"%s\"\n  pos = %u\n  current_char = '%c'\n\n", self_lexer->text, self_lexer->pos, self_lexer->current_char);
// }

// Initialize variables
void
lexer_init(Lexer *self_lexer, char *text_arg)
{
    // printf(">>> Lexer_init offset - %i\n", self_lexer);
    self_lexer->text = text_arg;
    self_lexer->pos = 0;
    self_lexer->current_char = self_lexer->text[self_lexer->pos];

    // lexer_print(self_lexer);
    // printf("<<< Lexer_init\n");
}

void
lexer_error(void)
{
    printf("Invalid character");
    exit(1);
}

void
lexer_advance(Lexer *self_lexer)
{
    // printf(">>> Lexer_advance offset - %i\n", self_lexer);
    self_lexer->pos += 1;
    if (self_lexer->pos > strlen(self_lexer->text) - 1)
        self_lexer->current_char = NULL;
    else
        self_lexer->current_char = self_lexer->text[self_lexer->pos];
    // printf("<<< Lexer_advance\n");
}

void
lexer_skip_whitespace(Lexer *self_lexer)
{
    // printf(">>> Lexer_whitespace offset - %i\n", self_lexer);
    while (self_lexer->current_char != NULL && isspace(self_lexer->current_char))
        lexer_advance(self_lexer);
    // printf("<<< Lexer_whitspace\n");
}

double
lexer_number(Lexer *self_lexer)
{
    // printf(">>> Lexer_integer offset - %i\n", self_lexer);
    unsigned int cont = 0;
    char result[30];
    memset((char *)result, 0, 30);

    while (self_lexer->current_char != NULL && (isdigit(self_lexer->current_char) || self_lexer->current_char == '.'))
    {
        result[cont] = self_lexer->current_char;
        lexer_advance(self_lexer);
        cont++;
        if (cont == 30)
            break;
    }
    // printf("  result = %s", result);
    // printf("<<< Lexer_integer\n");
    return atof(result);
}

double
lexer_command(Lexer *self_lexer)
{
    // printf(">>> Lexer_command offset - %i\n", self_lexer);
    unsigned int cont = 0;
    char cmd[8];
    memset((char *)cmd, 0, 8);

    while (self_lexer->current_char != NULL && (isalpha(self_lexer->current_char)))
    {
        cmd[cont] = self_lexer->current_char;
        lexer_advance(self_lexer);
        cont++;
        if (cont == 8 )
            break;
    }

    if (compstr(cmd, "quit") == 0)      // exit
        exit(0);

    else if (compstr(cmd, "sqrt") == 0) // square root
        return 1;

    else if (compstr(cmd, "cbrt") == 0) // cube root
        return 2;

    else if (compstr(cmd, "fact") == 0) // factorial
        return 3;

    else if (compstr(cmd, "dfact") == 0) // factorial
        return 4;

    else
        lexer_error();
}

Tokens
lexer_get_next_token(Lexer *self_lexer)
{
    // printf(">>> Lexer_get_next_token offset - %i\n", self_lexer);

    Tokens token;
    while (self_lexer->current_char != NULL)
    {
        if (isspace(self_lexer->current_char))
        {
            lexer_skip_whitespace(self_lexer);
            continue;
        }
        
        if (isdigit(self_lexer->current_char))
        {
            token_init(&token, NUMBER, lexer_number(self_lexer));
            return token;
        }

        if (isalpha(self_lexer->current_char))
        {
            token_init(&token, CMD, lexer_command(self_lexer));
            return token;
        }
        
        if (self_lexer->current_char == '+')
        {
            lexer_advance(self_lexer);
            token_init(&token, PLUS, '+');
            return token;
        }

        if (self_lexer->current_char == '-')
        {
            lexer_advance(self_lexer);
            token_init(&token, MINUS, '-');
            return token;
        }

        
        if (self_lexer->current_char == '*')
        {
            lexer_advance(self_lexer);
            token_init(&token, MUL, '*');
            return token;
        }
        
        if (self_lexer->current_char == '/')
        {
            lexer_advance(self_lexer);
            token_init(&token, DIV, '/');
            return token;
        }
        
        if (self_lexer->current_char == '%')
        {
            lexer_advance(self_lexer);
            token_init(&token, MOD, '%');
            return token;
        }
        
        if (self_lexer->current_char == '^')
        {
            lexer_advance(self_lexer);
            token_init(&token, EXP, '^');
            return token;
        }
        
        if (self_lexer->current_char == '(')
        {
            lexer_advance(self_lexer);
            token_init(&token, LPAREN, '(');
            return token;
        }

        
        if (self_lexer->current_char == ')')
        {
            lexer_advance(self_lexer);
            token_init(&token, RPAREN, ')');
            return token;
        }

        lexer_error();
    }

    // printf("<<< Lexer_get_next_token\n");
    token_init(&token, EOFILE, 0);
    return token;
}
/*  End Lexer  */


/*  Begin Interpreter  */
typedef struct
{
    Lexer *lexer;
    Tokens current_token;
} Interpreter;

void interpreter_init(Interpreter *self_interpreter, Lexer *lexer_arg);
void interpreter_error(void);
void interpreter_eat(Interpreter *self_interpreter, const char *token_type);
double interpreter_factor(Interpreter *self_interpreter);
double interpreter_expoint(Interpreter *self_interpreter);
double interpreter_term(Interpreter *self_interpreter);
double interpreter_expr(Interpreter *self_interpreter);

void
interpreter_init(Interpreter *self_interpreter, Lexer *lexer_arg)
{
    // printf(">>> Interpreter_init offset - %i\n", self_interpreter);
    self_interpreter->lexer = lexer_arg;
    self_interpreter->current_token = lexer_get_next_token(self_interpreter->lexer);

    // printf("<<< Interpreter_init\n");
}

void
interpreter_error(void)
{
    printf("Invalid syntax");
    exit(1);
}

void
interpreter_eat(Interpreter *self_interpreter, const char *token_type)
{
    // printf(">>> Interpreter_eat offset - %i\n", self_interpreter);
    if (strcmp(self_interpreter->current_token.type, token_type) == 0)
        self_interpreter->current_token = lexer_get_next_token(self_interpreter->lexer);
    else
        interpreter_error();
    // printf("<<< Interpreter_eat\n");
}

double
interpreter_factor(Interpreter *self_interpreter)
{
    // printf(">>> Interpreter_factor offset - %i\n", self_interpreter);
    Tokens token = self_interpreter->current_token;
    if (strcmp(self_interpreter->current_token.type, NUMBER) == 0)
    {
        interpreter_eat(self_interpreter, NUMBER);
        // printf("<<< Interpreter_factor\n");
        return token.value;
    }
    else if (strcmp(self_interpreter->current_token.type, LPAREN) == 0)
    {
        interpreter_eat(self_interpreter, LPAREN);
        double result = interpreter_expr(self_interpreter);
        interpreter_eat(self_interpreter, RPAREN);
        // printf("<<< Interpreter_factor\n");
        return result;
    }
    else if (strcmp(self_interpreter->current_token.type, CMD) == 0)
    {
        char cmd = self_interpreter->current_token.value;
        interpreter_eat(self_interpreter, CMD);
        interpreter_eat(self_interpreter, LPAREN);
        double result = interpreter_expr(self_interpreter);
        interpreter_eat(self_interpreter, RPAREN);

        switch (cmd)
        {
        case 1: // square root
            result = sqrt(result);
            break;
        
        case 2: // cube root
            result = cbrt(result);
            break;

        case 3: // factorial
            result = fact(result);
            break;

        case 4: // double factorial
            result = dfact(result);
            break;

        default:
            break;
        }
        
        // printf("<<< Interpreter_factor\n");
        return result;
    }
    
}

double
interpreter_expoint(Interpreter *self_interpreter)
{
    // printf(">>> Interpreter_expoint offset - %i\n", self_interpreter);
    double result = interpreter_factor(self_interpreter);

    while (strcmp(self_interpreter->current_token.type, EXP) == 0)
    {
        Tokens token = self_interpreter->current_token;
        if (strcmp(token.type, EXP) == 0)
        {
            interpreter_eat(self_interpreter, EXP);
            result = pow(result, interpreter_factor(self_interpreter));
        }
    }
    // printf("<<< Interpreter_expoint\n");
    return result;
}

double
interpreter_term(Interpreter *self_interpreter)
{
    // printf(">>> Interpreter_term offset - %i\n", self_interpreter);
    double result = interpreter_expoint(self_interpreter);

    while (strcmp(self_interpreter->current_token.type, MUL) == 0 || strcmp(self_interpreter->current_token.type, DIV) == 0 || strcmp(self_interpreter->current_token.type, MOD) == 0)
    {
        Tokens token = self_interpreter->current_token;
        if (strcmp(token.type, MUL) == 0)
        {
            interpreter_eat(self_interpreter, MUL);
            result *= interpreter_expoint(self_interpreter);
        }
        else if (strcmp(token.type, DIV) == 0)
        {
            interpreter_eat(self_interpreter, DIV);
            result /= interpreter_expoint(self_interpreter);
        }
        else if (strcmp(token.type, MOD) == 0)
        {
            interpreter_eat(self_interpreter, MOD);
            result = fmod(result, interpreter_expoint(self_interpreter));
        }
    }
    // printf("<<< Interpreter_term\n");
    return result;
}

double
interpreter_expr(Interpreter *self_interpreter)
{
    // printf(">>> Interpreter_expr offset - %i\n", self_interpreter);
    double result = interpreter_term(self_interpreter);

    while (strcmp(self_interpreter->current_token.type, PLUS) == 0 || strcmp(self_interpreter->current_token.type, MINUS) == 0)
    {
        Tokens token = self_interpreter->current_token;
        if (strcmp(token.type, PLUS) == 0)
        {
            interpreter_eat(self_interpreter, PLUS);
            result += interpreter_term(self_interpreter);
        }
        else if (strcmp(token.type, MINUS) == 0)
        {
            interpreter_eat(self_interpreter, MINUS);
            result -= interpreter_term(self_interpreter);
        }
    }
    // printf("<<< Interpreter_expr\n");
    return result;
}
/*  End Interpreter  */


int
main(void)
{
    char buffer[100];

    while (1)
    {
        printf("calc> ");
        fgets(buffer, 100, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        Lexer lexer;
        Interpreter interpreter;
        // printf("Lexer offset - %i\n", &lexer);
        // printf("Interpreter offset - %i\n", &interpreter);

        lexer_init(&lexer, buffer);
        interpreter_init(&interpreter, &lexer);
        double result = interpreter_expr(&interpreter);

        printf("\n  %s = %lf\n\n", buffer, result);
    }
    
    return 0;
}
