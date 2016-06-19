#include <stdio.h>

char* a = " this is /* a test of \" junk // embedded in a '\' string";
char* b = "it should be left alone//";

// comment /* that should ***////  be converted.
/* leave this alone*/// but fix this one

// and "leave these \' \" quotes in a comment alone*
/****  and these '\' too //
*/

enum states {
    state_normal,
    state_string,
    state_string_escape,
    state_single_slash,
    state_c99_comment,
    state_asterix,
    state_c89_comment
};

enum states current_state = state_normal;

void handle_char( char ch)
{

    switch (current_state)
    {
        case state_normal:

            switch(ch)
            {
                case '/':
                    current_state = state_single_slash;
                    break;

                case '\"':
                    current_state = state_string;
                    break;

                default:
                    break;
            }

            putchar(ch);
            return;

        case state_string:

            switch(ch)
            {
                case '\"':
                    current_state = state_normal;
                    break;

                case '\\':
                    current_state = state_string_escape;
                    break;

                default:
                    break;
            }

            putchar(ch);
            return;


        case state_string_escape:

            current_state = state_string;
            putchar(ch);
            return;

        case state_single_slash:

            switch(ch)
            {
                case '/':
                    current_state = state_c99_comment;
                    putchar('*');
                    return;

                case '*':
                    current_state = state_c89_comment;
                    break;

                default:
                    break;
            }

            putchar(ch);
            return;

        case state_c99_comment:

            switch(ch)
            {
                case '\n':
                case '\r':
                    current_state = state_normal;
                    putchar('*');
                    putchar('/');
                    putchar(ch);
                    return;

                default:
                    break;
            }

            putchar(ch);
            return;

            case state_c89_comment:

                switch(ch)
                {
                    case '*':
                        current_state = state_asterix;
                        break;

                    default:
                        break;
                }

                putchar(ch);
                return;

            case state_asterix:

                switch(ch)
                {
                    case '/':
                        current_state = state_normal;
                        break;

                    default:
                        current_state = state_c89_comment;
                }

                putchar(ch);
                return;

    }

}

int main(void)
{
    int c;

    while ((c = getchar()) != EOF) {
        handle_char( c);
    }

    return 0;
}
