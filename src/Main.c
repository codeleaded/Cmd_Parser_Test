#include "/home/codeleaded/System/Static/Library/AlxParser.h"

#define TOKEN_CUSTOM_HELLO      TOKEN_START+0
#define TOKEN_CUSTOM_WORLD      TOKEN_START+1

#define TOKEN_CUSTOM_ASS        TOKEN_START+2
#define TOKEN_CUSTOM_ADD        TOKEN_START+3
#define TOKEN_CUSTOM_SUB        TOKEN_START+4
#define TOKEN_CUSTOM_NEG        TOKEN_START+5
#define TOKEN_CUSTOM_DEC        TOKEN_START+6

int main(){

    KeywordMap kwm = KeywordMap_Make((KeywordRP[]){
        KeywordRP_New("Hello",TOKEN_CUSTOM_HELLO),
        KeywordRP_New("World",TOKEN_CUSTOM_WORLD),
        KeywordRP_End()
    });
    OperatorMap om = OperatorMap_Make((OperatorRP[]){
        OperatorRP_Make((TT_Type[]){ TOKEN_EQUAL_SIGN,TOKEN_END },                  TOKEN_CUSTOM_ASS,1),
        OperatorRP_Make((TT_Type[]){ TOKEN_PLUS_SIGN,TOKEN_END },                   TOKEN_CUSTOM_ADD,1),
        OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_END },                  TOKEN_CUSTOM_SUB,1),
        OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_END },                  TOKEN_CUSTOM_NEG,0),
        OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_MINUS_SIGN,TOKEN_END }, TOKEN_CUSTOM_DEC,0),
        OperatorRP_End()
    });
    ReseterMap rsm = ReseterMap_Make((Reseter[]){ 
        // operators who might have two versions: 1 arg vs. 2 args are not listed: -
        { TOKEN_NONE,RESETER_NONE },
        { TOKEN_NUMBER,RESETER_ADD1 },
        { TOKEN_FLOAT,RESETER_ADD1 },
        { TOKEN_STRING,RESETER_ADD1 },
        
        { TOKEN_SPACE,RESETER_NONE },
        { TOKEN_NEWLINE,RESETER_NONE },
        { TOKEN_CARTURN,RESETER_NONE },
        { TOKEN_HTAB,RESETER_NONE },
        { TOKEN_VTAB,RESETER_NONE },
        
        { TOKEN_PARENTHESES_R,RESETER_NONE },
        { TOKEN_SQUARE_BRACKETS_R,RESETER_NONE },
        { TOKEN_CURLY_BRACES_R,RESETER_NONE },
        //{ TOKEN_ANGLE_BRACKETS_R,RESETER_NONE }, //also < and > operator
        { TOKEN_DOUBLE_ANGLE_BRACKETS_R,RESETER_NONE },
        { TOKEN_WHITE_SQUARE_BRACKETS_R,RESETER_NONE },
        
        { TOKEN_PARENTHESES_L,RESETER_RST },
        { TOKEN_SQUARE_BRACKETS_L,RESETER_RST },
        { TOKEN_CURLY_BRACES_L,RESETER_RST },
        //{ TOKEN_ANGLE_BRACKETS_L,RESETER_RST }, //also < and > operator
        { TOKEN_DOUBLE_ANGLE_BRACKETS_L,RESETER_RST },
        { TOKEN_WHITE_SQUARE_BRACKETS_L,RESETER_RST },
        { TOKEN_SEMICOLON,RESETER_RST },
        { TOKEN_COLON,RESETER_RST },
        { TOKEN_EXCLAMATION_MARK,RESETER_RST },
        { TOKEN_QUESTION_MARK,RESETER_RST },
        { TOKEN_ELLIPSIS,RESETER_RST },
        { TOKEN_PLUS_SIGN,RESETER_RST },
        { TOKEN_MULTIPLICATION_SIGN,RESETER_RST },
        { TOKEN_DIVISION_SIGN,RESETER_RST },
        { TOKEN_EQUAL_SIGN,RESETER_RST },
        { TOKEN_NOT_EQUAL_SIGN,RESETER_RST },
        { TOKEN_LESS_THAN,RESETER_RST },
        { TOKEN_GREATER_THAN,RESETER_RST },
        { TOKEN_LESS_THAN_OR_EQUAL_TO,RESETER_RST },
        { TOKEN_GREATER_THAN_OR_EQUAL_TO,RESETER_RST },
        { TOKEN_APPROXIMATION_SIGN,RESETER_RST },
        { TOKEN_PLUS_MINUS_SIGN,RESETER_RST },
        { TOKEN_AMPERSAND,RESETER_RST },
        { TOKEN_AT_SIGN,RESETER_RST },
        { TOKEN_ASTERISK,RESETER_RST },
        { TOKEN_CARET,RESETER_RST },
        { TOKEN_TILDE,RESETER_RST },
        { TOKEN_SLASH,RESETER_RST },
        { TOKEN_BACKSLASH,RESETER_RST },
        { TOKEN_UNDERSCORE,RESETER_RST },
        { TOKEN_PIPE,RESETER_RST },
        { TOKEN_PERCENT,RESETER_RST },
        { TOKEN_HASH_POUND_SIGN,RESETER_RST },
        { TOKEN_SINGLE_QUOTE,RESETER_RST },
        { TOKEN_DOUBLE_QUOTE,RESETER_RST },
        { TOKEN_BACKTICK,RESETER_RST },
        { TOKEN_PRIME,RESETER_RST },
        { TOKEN_DOUBLE_PRIME,RESETER_RST },
        { TOKEN_SECTION_SYMBOL,RESETER_RST },
        { TOKEN_DEGREE_SYMBOL,RESETER_RST },
        { TOKEN_FRACTION_SLASH,RESETER_RST },
        { TOKEN_INTERROBANG,RESETER_RST },
        { TOKEN_BULLET_POINT,RESETER_RST },
        { TOKEN_END,RESETER_RST } 
    });
    
    Parser p = Parser_New();

    Parser_Parse_cstr(&p,"a = --a - 1 + (-1) - (--a);");
    Parser_Print(&p);
    Parser_TF_Std(&p);
    Parser_TF_KW(&p,&kwm);
    Parser_Print(&p);
    Parser_TF_OPS(&p,&om,&rsm);
    Parser_Print(&p);
    Parser_Free(&p);

    ReseterMap_Free(&rsm);
    OperatorMap_Free(&kwm);
    KeywordMap_Free(&kwm);

    return 0;
}