#include <stdio.h>
#include <stdlib.h>

enum States
{
    NORMAL_STATE,
    START_A_COMMENT_STATE,
    INSIDE_COMMENT_STATE,
    END_A_COMMENT_STATE,
    STRING_STATE,
    CHAR_STATE,
    C99
};
FILE *destFile;

/**
 * If the character is a double quote, then we're in a string. If the character is a single quote, then
 * we're in a character. If the character is a forward slash, then we're starting a comment. Otherwise,
 * we're in the normal state
 *
 * @param ch The character that was read from the source file.
 * @param state The current state of the state machine.
 */
void handleNormalState(char ch, enum States *state)
{

    if (ch == '"')
    {
        *state = STRING_STATE;
        fputc(ch, destFile);
    }
    else if (ch == '\'')
    {
        *state = CHAR_STATE;
        fputc(ch, destFile);
    }
    else if (ch == '/')
    {
        *state = START_A_COMMENT_STATE;
    }
    else
    {
        fputc(ch, destFile);
    }
}
/**
 * If the next character is a `*`, then we're inside a comment. If the next character is a `/`, then
 * we're starting a comment. Otherwise, we're not in a comment
 *
 * @param ch the current character
 * @param state the current state of the state machine
 * @param commentStartLine the line number where the comment started
 * @param line the current line number
 */
void handleStartCommentState(char ch, enum States *state, int *commentStartLine, int *line)
{
    if (ch == '*')
    {
        *state = INSIDE_COMMENT_STATE;
        *commentStartLine = *line;
        // fputc(' ', destFile);
    }
    else if (ch == '/')
    {
        // *state = START_A_COMMENT_STATE;
        *state = C99;
        // fputc("", destFile);
    }
    else
    {
        *state = NORMAL_STATE;
        fputc('/', destFile);
        fputc(ch, destFile);
    }
}
void handleC99(char ch, enum States *state)
{
    if (ch == '\n')
    {
        *state = NORMAL_STATE;
    fputc('\n', destFile);

    }
    fputc(' ', destFile);
}
/**
 * If the character is a star, then we're at the end of a comment. If the character is a newline, then
 * we're still inside a comment, so we print the newline to the output file
 *
 * @param ch the current character being read from the source file
 * @param state the current state of the state machine
 * @param line the line number of the source file
 */
void handleInsideCommentState(char ch, enum States *state, int *line)
{
    if (ch == '*')
    {
        *state = END_A_COMMENT_STATE;
    }
    else if (ch == '\n')
    {
        fputc(ch, destFile);
    }
}
/**
 * If the character is a double quote, then we're done with the string, so we go back to the normal
 * state. Otherwise, we just write the character to the output file
 *
 * @param ch The character that is being read from the source file.
 * @param state The current state of the state machine.
 */
void handleInStringState(char ch, enum States *state)
{
    if (ch == '\"')
    {
        *state = NORMAL_STATE;
        fputc(ch, destFile);
    }
    else
    {
        fputc(ch, destFile);
    }
}

/**
 * If the character is a single quote, then we're done with the character constant, so we go back to
 * the normal state. If the character is a newline, then we're still in the character constant, so we
 * stay in the character constant state. In either case, we write the character to the output file
 *
 * @param ch The character that was read from the source file.
 * @param state The current state of the program.
 */
void handleInCharState(char ch, enum States *state)
{
    if (ch == '\'')
    {
        *state = NORMAL_STATE;
    }
    else if (ch == '\n')
    {
        *state = CHAR_STATE;
        fputc(ch, destFile);
    }
    fputc(ch, destFile);
}

/**
 * If the character is a slash, then we're back to the normal state. If the character is an asterisk,
 * then we're still in the end-a-comment state. Otherwise, we're in the inside-comment state
 *
 * @param ch the current character being read
 * @param state The current state of the state machine.
 */
void handleToEndACommentState(char ch, enum States *state)
{
    if (ch == '/')
    {
        *state = NORMAL_STATE;
    }
    else if (ch == '*')
    {
        *state = END_A_COMMENT_STATE;
    }
    else
    {
        *state = INSIDE_COMMENT_STATE;
    }
}

int main(int argc, char *argv[])
{
    FILE *file;

    enum States state;
    state = NORMAL_STATE;
    int line = 1;
    int commentStartLine = 1;
    char ch;
    destFile = fopen("outPutFileWithouptComments.c", "w");
    file = fopen("inputFile.c", "r");

    if (file == NULL || destFile == NULL)
    {
        fprintf(stderr, "Cannot open the file\n");
        exit(-1);
    }

    int i = 0;

    for (;;)
    {
        ch = getc(file);
        if (ch == '\n')
        {
            line += 1;
        }
        if (ch == EOF)
        {

            if (state == INSIDE_COMMENT_STATE || state == END_A_COMMENT_STATE)
            {
                fprintf(stderr, "Error: Comment started on line  %d  is unterminated comment.\n", commentStartLine);
                break;
            }
            break;
        }
        if (state == NORMAL_STATE)
        {
            handleNormalState(ch, &state);
        }
        else if (state == START_A_COMMENT_STATE)
        {
            handleStartCommentState(ch, &state, &commentStartLine, &line);
        }
        else if (state == INSIDE_COMMENT_STATE)
        {
            handleInsideCommentState(ch, &state, &line);
        }
        else if (state == END_A_COMMENT_STATE)
        {
            handleToEndACommentState(ch, &state);
        }
        else if (state == STRING_STATE)
        {
            handleInStringState(ch, &state);
        }

        else if (state == CHAR_STATE)
        {
            handleInCharState(ch, &state);
        }
        else if (state == C99)
        {
            handleC99(ch, &state);
        }
    }

    fclose(file);
    fclose(destFile);
}
