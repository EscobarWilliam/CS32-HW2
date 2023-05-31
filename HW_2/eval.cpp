//
//  eval.cpp
//  HW_2
//
//  Created by William  Escobar on 4/29/23.
//

#include <iostream>
#include <stack>
#include <string>
#include <cassert>


//function prototype
int evaluate(std::string infix, std::string& postfix, bool& result);//evaluates the infix expression
bool setup(std::string &infix);//removes all whitespace from infix

int main()
{
        std::string pf;
        bool answer;
        assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
        assert(evaluate("T^", pf, answer) == 1);
        assert(evaluate("F F", pf, answer) == 1);
        assert(evaluate("TF", pf, answer) == 1);
        assert(evaluate("()", pf, answer) == 1);
        assert(evaluate("()T", pf, answer) == 1);
        assert(evaluate("T(F^T)", pf, answer) == 1);
        assert(evaluate("T(&T)", pf, answer) == 1);
        assert(evaluate("(T&(F^F)", pf, answer) == 1);
        assert(evaluate("T|F", pf, answer) == 1);
        assert(evaluate("", pf, answer) == 1);
        assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
                               &&  pf == "FF!TF&&^"  &&  !answer);
        assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
        assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    
        assert(evaluate("T", pf, answer) == 0  &&  pf == "T"  &&  answer);
        assert(evaluate("(F)", pf, answer) == 0  &&  pf == "F"  &&  !answer);
        assert(evaluate("T&(F)", pf, answer) == 0  &&  pf == "TF&"  &&  !answer);
        assert(evaluate("T & !F", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
        assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
        assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
        assert(evaluate("(T & !F)", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
        assert(evaluate("F&T&F", pf, answer) == 0 && pf == "FT&F&"  && !answer);

        //check invalid cases
        assert(evaluate("F F", pf, answer) == 1);
        assert(evaluate("TF", pf, answer) == 1);
        assert(evaluate("()", pf, answer) == 1);
        assert(evaluate("(  )", pf, answer) == 1);
        assert(evaluate("(  T&F)T", pf, answer) == 1);
        assert(evaluate("T(&T)", pf, answer) == 1);
        assert(evaluate("", pf, answer) == 1);
        assert(evaluate("  ", pf, answer) == 1);
        assert(evaluate("T!", pf, answer) == 1);
        assert(evaluate("T(", pf, answer) == 1);
        assert(evaluate("(TT", pf, answer) == 1);
        assert(evaluate("&TF", pf, answer) == 1);
        assert(evaluate(")(", pf, answer) == 1);
        assert(evaluate("#2", pf, answer) == 1);
        assert(evaluate("F&&", pf, answer) == 1);
        assert(evaluate("F!!", pf, answer) == 1);
        assert(evaluate("F!!T", pf, answer) == 1);
        
        //check valid cases
        assert(evaluate("T", pf, answer) == 0  &&  pf == "T"  &&  answer);
        assert(evaluate("T&T", pf, answer) == 0  &&  pf == "TT&"  &&  answer);
        assert(evaluate("T & !F", pf, answer) == 0  &&  pf == "TF!&"  &&  answer);
        assert(evaluate("F&(&T)", pf, answer) == 1);
        assert(evaluate("T!T", pf, answer) == 1);
        assert(evaluate("(F", pf, answer) == 1);
        assert(evaluate("F)", pf, answer) == 1);
        assert(evaluate("TF", pf, answer) == 1);
        assert(evaluate("F T&T", pf, answer) == 1);
    std::cout << "Passed all tests" << std::endl;
}

bool setup(std::string &infix)
{
    //remove all whitespace---------------------------------------------------
    std::string temp;
    std::stack<char> stringStack1;
    
    for(int i=0; i<infix.size(); i++)
    {
        if(infix[i] == ' ')
            continue;
        temp += infix[i];
    }
    infix = temp;//overwrite infix but now with no whitespace
    
    //check if parentheses come in pairs--------------------------------------
    int i = (infix.size() - 1.0);
    while(i >= 0)
    {
        if(infix[i] != '(')
        {
            stringStack1.push(infix[i]);
            i--;
        }
        else
        {
            while(!stringStack1.empty() && stringStack1.top() != ')')
                stringStack1.pop();
            
            if(stringStack1.empty())
                return 1; //meaning that we never found a matching closing bracket to pop from the list
            
            stringStack1.pop();//otherwise pop off paired bracket
            i--;
        }
    }
    //now, pop all  remaining values. If we encounter a '(' or ')' it won't have a pair
    while(!stringStack1.empty() && (stringStack1.top() != '(') && (stringStack1.top() != ')') )
        stringStack1.pop();
    
    //at this point, our stack should be empty if valid otherwise its not
    if(!stringStack1.empty())
        return false;
    
    return true;
}

bool validate(const std::string &infix, int i)//ignores whitespace and returns the position of next character or -1 if
{
    //validate if syntactically valid.  Can't have 'FF', 'TF', 'TT', 'FT', ')F', ')T'
    //We want to allow whitepsace between characters and no matter the amount of spaces
    //the expression can still be true
    if(i > 0)//then there are characters/operators before infix[i]
    {
        if( (infix[i] == '!' || infix[i] == 'T' || infix[i] == 'F' || infix[i] == '(' ) && ( infix[i-1] == 'T' || infix[i-1] == 'F' || infix[i-1] == ')') )
            return false; //if the current nonblank chars isn't legal, return -1
        else if((i-1 > 0) && (infix[i] == '&' || infix[i] == '^' ) && ((infix[i-1] == '!') || (infix[i-1] == '&')|| (infix[i-1] == '^') || (infix[i-1] == '(')))
                return false; //if the current nonblank chars isn't legal, return -1
    }
    else if(i == 0 ) //certain operators must have a preceding operand
    {
         if(infix[i] == '&' || infix[i] == '^' || infix[i] == ')')
             return false;
    }
    
    return true;
}

//*******************************************************************************
//      int evaluate(std::string infix, std::string& postfix, bool& result)
//
// EVALUATES A BOOLEAN EXPRESSION:
//  i. If infix is a syntactically valid infix boolean expression,
//     then set postfix to the postfix form of that expression, set
//     result to the value of the expression, and return zero.
//
// ii. If infix is not a syntactically valid expression, return 1;
//     in that case, postfix may or may not be changed, but result must
//     be unchanged.
//*******************************************************************************
int evaluate(std::string infix, std::string& postfix, bool& result)
{
    //before anything else, lets do our setup and preliminary checks
    //if setup returns false, then our string wasn't valid
    if(!setup(infix))
        return 1;
    
    postfix = ""; //initialize to empty
    std::stack<char> operatorStack;//create an empty character stack to hold the operands
    
    for(int i = 0; i<infix.size(); i++)//go through each character of the strig and don't exceed string size
    {
        switch(infix[i])
        {
            case 'T'://------------------------------------------------------------------------------------------------
            case 'F':
            {
                if(!validate(infix, i))
                    return 1;
                
                postfix += infix[i];
                break;
            }
            case '('://------------------------------------------------------------------------------------------------
            {
                
                if(!validate(infix, i))
                    return 1;
                
                operatorStack.push(infix[i]);
                break;
            }
            case ')'://------------------------------------------------------------------------------------------------
            {
                if(!validate(infix, i))
                    return 1;
                
                while(operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop(); //pops off the opening bracket
                break;
            }
            case '!'://------------------------------------------------------------------------------------------------
            {
                //validate if syntactically valid. Can't have 'T!', "F!", ')' because whatever the not operator
                //works on becomes either T or F and can't have 'FF' or 'TF' etc...
                if(!validate(infix, i))
                    return 1;
                
                operatorStack.push(infix[i]); //we can just push right away since '!'
                                            //has higher presedence than all other operators
                break;
            }
            case '&'://------------------------------------------------------------------------------------------------
            {
                //validate if syntactically valid. Can't have '(&', '!&', '&&', '^&'
                if(!validate(infix, i))
                    return 1;
                
                while(!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() != '^')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(infix[i]);
                break;
            }
            case '^'://------------------------------------------------------------------------------------------------
            {
                //validate if syntactically valid. Can't have '(&', '!&', '&&', '^&'
                if(!validate(infix, i))
                    return 1;
                
                while(!operatorStack.empty() && operatorStack.top() != '(' )
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(infix[i]);
                break;
            }
        
        }
    }
    
    while(!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    
    //std::cerr<<postfix<<std::endl;
    
    //insert code to evaluate the postfix expression
    std::stack<char> operandStack;
    for(int i=0; i<postfix.size(); i++)
    {
        if(postfix[i] == 'T' || postfix[i] == 'F')
            operandStack.push(postfix[i]);
        
        else if (postfix[i] == '!')
        {
            char operand1 = operandStack.top();
            operandStack.pop();
            //apply the not operator and push value onto the stack
            switch(operand1)
            {
                case 'T': operandStack.push('F');
                    break;
                case 'F': operandStack.push('T');
                    break;
            }
        }
        
        else if(postfix[i] == '&')
        {
            char operand2;
            if(!operandStack.empty())//check if the program can pop the stack
            {
                operand2 = operandStack.top();
                operandStack.pop();
            }
            else
                return 1;
            
            char operand1;
            if(!operandStack.empty())//check if the program can pop the stack
            {
                operand1 = operandStack.top();
                operandStack.pop();
            }
            else return 1;
            
            //evaluate the boolean expression
            if(operand1 == 'T' && operand2 == 'T')
                operandStack.push('T');
            else
                operandStack.push('F');
        }
        else//the operator is '^'
        {
            char operand2;
            if(!operandStack.empty())//check if the program can pop the stack
            {
                operand2 = operandStack.top();
                operandStack.pop();
            }
            else
                return 1;//if the stack is empty then '^' doesn't have a pair of operands to work on
                        
            char operand1;
            if(!operandStack.empty())//check if the program can pop the stack
            {
                operand1 = operandStack.top();
                operandStack.pop();
            }
            else
                return 1;
                        
           //evaluate the boolean expression
            if(operand1 == operand2)
                operandStack.push('F');
            else
                operandStack.push('T');
        }
    }
    
    if(operandStack.size() != 1)
            return 1; //if stack doesn't have exactly one item, return 1
        
    if(operandStack.top() == 'T')
        result = true;
    else
        result = false;
        
    return 0;
}
