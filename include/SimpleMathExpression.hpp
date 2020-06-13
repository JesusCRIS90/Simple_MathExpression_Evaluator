#include <string>
#include <stack>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <math.h>


struct token{

    char c;
    float f;
    bool number;
    int priority;

    token():c(0), number(false), priority( -1 ){};
};

typedef std::vector<token> Vector_Tokens;
typedef std::vector<token>::iterator Token_Iterator;
typedef std::stack<token> Token_Stack;

class SimpleMathExpression
{
    private:
        std::string original;
        std::string expression = std::string();
        Token_Stack operators_stack;

        Vector_Tokens tokens;               // Tokens in "Infija"
        Vector_Tokens token_expression;     // Tokens in "Polaca"

    public:

        SimpleMathExpression( std::string );
        ~SimpleMathExpression( );
         float Calculate_Result();

        std::string ConvertExpression();
        void ShowTokens();

    protected:

        void BuildTokensInExpression();
        void SetPriority( token& tok);
        void ProcessTokens();
        void ProcessOperator( Token_Iterator );
        void EmptyStack();

        void Search_Next_Operation( Vector_Tokens& );
        token Make_SimpleOperation( Vector_Tokens );

        void Execute( );
};
