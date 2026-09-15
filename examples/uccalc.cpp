#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
using namespace std;

class ExpressionParser {
    const char *current;
    const char *error_message;

    void skip_spaces()
    {
        while (isspace(*current)) current++;
    }

    double parse_sum();

    double parse_primary()
    {
        skip_spaces();
        if (*current == '(') {
            current++;
            double value = parse_sum();
            skip_spaces();
            if (*current != ')') {
                error_message = "expected ')'";
                return 0.0;
            }
            current++;
            return value;
        }

        char *end;
        double value = strtod(current, &end);
        if (end == current) {
            error_message = "expected a number or '('";
            return 0.0;
        }
        current = end;
        return value;
    }

    double parse_unary()
    {
        skip_spaces();
        if (*current == '+') { current++; return parse_unary(); }
        if (*current == '-') { current++; return -parse_unary(); }
        return parse_primary();
    }

    double parse_power()
    {
        double left = parse_unary();
        skip_spaces();
        if (*current == '^') {
            current++;
            return pow(left, parse_power());
        }
        return left;
    }

    double parse_product()
    {
        double value = parse_power();
        while (!error_message) {
            skip_spaces();
            char op = *current;
            if (op != '*' && op != '/') break;
            current++;
            double right = parse_power();
            if (op == '*') value *= right;
            else if (right == 0.0) {
                error_message = "division by zero";
                return 0.0;
            } else value /= right;
        }
        return value;
    }

public:
    ExpressionParser(const char *expression)
      : current(expression), error_message(0) { }

    bool calculate(double& result)
    {
        result = parse_sum();
        skip_spaces();
        if (!error_message && *current != '\0')
            error_message = "unexpected character";
        return error_message == 0;
    }

    const char *error() const { return error_message; }
};

double ExpressionParser::parse_sum()
{
    double value = parse_product();
    while (!error_message) {
        skip_spaces();
        char op = *current;
        if (op != '+' && op != '-') break;
        current++;
        double right = parse_product();
        if (op == '+') value += right;
        else value -= right;
    }
    return value;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ucc uccalc.cpp \"EXPRESSION\"\n");
        return 2;
    }

    ExpressionParser parser(argv[1]);
    double result;
    if (!parser.calculate(result)) {
        fprintf(stderr, "Cannot calculate '%s': %s\n", argv[1], parser.error());
        return 1;
    }
    cout << result;
    cout << "\n";
    return 0;
}
