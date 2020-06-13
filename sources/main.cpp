#include "SimpleMathExpression.hpp"
#include <iostream>     // std::cin, std::cout
#include <string>       // std::string
#include <cctype>       // std::isdigit


int main(int argc, char *argv[])
{

//    std::string prueba = { "5 + 3 * (7.7 / 9.8 ^ 1 )" };
//    std::string prueba2 = { "3 + 2 + 4 - 3.2 * ( 7/9^2  )" };
//    std::string prueba3 = { " 3 + 1" };

    std::string Math_Expression;

    std::cout << "Introduce Math Expression" << std::endl;
    std::cin >> Math_Expression;

    SimpleMathExpression exp( Math_Expression );

    exp.ConvertExpression();
    exp.ShowTokens();

    std::cout << "\n" << Math_Expression << " = "  << exp.Calculate_Result() << std::endl;

}
