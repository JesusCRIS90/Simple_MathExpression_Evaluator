#include <string>
#include <stack>



class SimpleMathExpression
{
    private:
        std::string original;
        std::string expression = std::string();
        std::stack<char> operators_stack;
    public:

        SimpleMathExpression( );
        SimpleMathExpression( std::string );
        ~SimpleMathExpression( );


        bool IsValidExpression( );
        std::string ConvertExpression();





    protected:

        bool CheckExpression();


        void Execute( );
};