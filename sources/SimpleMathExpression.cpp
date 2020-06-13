#include "SimpleMathExpression.hpp"

SimpleMathExpression::SimpleMathExpression( std::string expression )
{
    this->original = expression;
}

SimpleMathExpression::~SimpleMathExpression()
{

}

std::string SimpleMathExpression::ConvertExpression()
{
    BuildTokensInExpression(  );
    ProcessTokens();

    return std::string();
}

void SimpleMathExpression::ShowTokens()
{
    auto it_token = tokens.begin();

    for( ; it_token != tokens.end() ; it_token++ )
    {
        if(it_token->number) std::cout << "number: " << it_token->f << std::endl;
        else std::cout << "sign: " << it_token->c << "\tPriority -> " << it_token->priority << std::endl;
    }

    std::cout << "\n\n" << std::endl;

    auto it_tok_express = token_expression.begin();
    for( ; it_tok_express != token_expression.end() ; it_tok_express++ )
    {
        if(it_tok_express->number) std::cout << "number: " << it_tok_express->f << std::endl;
        else std::cout << "sign: " << it_tok_express->c << "\tPriority -> " << it_tok_express->priority << std::endl;
    }
}


void SimpleMathExpression::BuildTokensInExpression()
{
    boost::erase_all( original, " " );

    std::stringstream parser( original );
    parser.precision( 10 );
    parser.flags(std::ios_base::fmtflags(std::ios_base::scientific));
    while( parser )
    {
       token t;
       if( isalnum( parser.peek( ) ) )
          parser >> t.f;        // It is an operand
       else
          parser >> t.c;        // It is an operator
       t.number = ( t.c==0 );
       SetPriority( t );
       tokens.push_back( t );
    }
    tokens.pop_back();
}

void SimpleMathExpression::SetPriority(token &tok)
{
    switch ( tok.c ) {
    case '(' :
        tok.priority = 0;
        break;
    case ')' :
        tok.priority = 0;
        break;
    case '^' :
        tok.priority = 3;
        break;
    case '*' :
        tok.priority = 2;
        break;
    case '/' :
        tok.priority = 2;
        break;
    case '+' :
        tok.priority = 1;
        break;
    case '-' :
        tok.priority = 1;
        break;
    default:
        tok.priority = -1;
        break;

    }
}

void SimpleMathExpression::ProcessTokens()
{
    auto it_token = tokens.begin();
    for( ; it_token != tokens.end() ; it_token++ )
    {
        if( it_token->number ) token_expression.push_back(  *it_token );
        else ProcessOperator( it_token );
    }
    EmptyStack();
}

void SimpleMathExpression::ProcessOperator(Token_Iterator it_token )
{

    // If the operator was ')', we empty stack until next operator ')'
    if( it_token->c == ')' ){
        while( operators_stack.top().c != '(' ){
            token_expression.push_back( operators_stack.top() );
            operators_stack.pop();
        }
        operators_stack.pop();   // Remove from stack the operator ')'
        return;
    }

    if( operators_stack.empty() ) { operators_stack.push( *it_token ); return; }
    if( it_token->c == '(' ) { operators_stack.push( *it_token ); return; }
    if( it_token->priority <= operators_stack.top().priority )
    {
        token_expression.push_back( operators_stack.top() );
        operators_stack.pop();
        operators_stack.push( *it_token );

    } else operators_stack.push( *it_token );

}

void SimpleMathExpression::EmptyStack()
{
     while( !operators_stack.empty() ){
            token_expression.push_back( operators_stack.top() );
            operators_stack.pop();
     }
}

float SimpleMathExpression::Calculate_Result()
{
    Vector_Tokens Temp_Tokens( token_expression );
    while( Temp_Tokens.size() != 1 ) Search_Next_Operation( Temp_Tokens );
    return Temp_Tokens[0].f;
}

void SimpleMathExpression::Search_Next_Operation( Vector_Tokens& vec )
{
    token new_token;
    auto it_search = vec.begin();
    for( ; it_search != vec.end() ; it_search++ ){
        if( !it_search->number ) {

            auto it_init = it_search - 2;
            auto it_last = it_search;
            auto it_insert = it_init;
            new_token = Make_SimpleOperation( Vector_Tokens( it_init, it_last + 1 ) );
            if( vec.size() > 3 ){
               vec.erase( it_init, it_last + 1 );
               vec.insert( it_insert, new_token );
            } else {
                vec.clear();
                vec.push_back( new_token );
            }
            break;
        }
    }

}

token SimpleMathExpression::Make_SimpleOperation(Vector_Tokens op)
{
    float op_result;
    switch ( op[2].c ) {

        case '+' :
            op_result = op[0].f + op[1].f;
            break;
        case '-' :
            op_result = op[0].f - op[1].f;
            break;
        case '*' :
            op_result = op[0].f * op[1].f;
            break;
        case '/' :
            op_result = op[0].f / op[1].f;
            break;
        case '^' :
            op_result = std::pow( op[0].f,  op[1].f);
            break;

    }
    token t; t.f = op_result; t.number = true;
    return t;
}

