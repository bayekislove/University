#include<iostream>
#include<queue>
#include<string>
#include<stack>
#include<map>

using namespace std;

///[priority, left-sided, right-sided]                  
queue<char> convert(string inp, map<char, array<int, 3>> op_pr)
{
    queue<char> returned;
    stack<char> operators;
    for(unsigned int i = 0; i < inp.length(); i++)// warning
    {
        if(inp[i] >= '0' && inp[i] <= '9')
        {
            returned.push(inp[i]);
        }

        else if(op_pr.count(inp[i]) > 0)
        {
            while(!operators.empty())
            {
                if((op_pr[inp[i]][1] && op_pr[inp[i]][0] <= op_pr[operators.top()][0]) ||
                   (op_pr[inp[i]][2] && op_pr[inp[i]][0] < op_pr[operators.top()][0]))
                {
                    returned.push(operators.top());
                    operators.pop();
                }
                else
                    break;
            }
            operators.push(inp[i]);
        }

        else if(inp[i] == '(')
            operators.push(inp[i]);

        else if(inp[i] == ')')
        {
            while(!operators.empty())
            {
                if(operators.top() == '(')
                {
                    operators.pop();
                    break;
                }
                returned.push(operators.top());
                operators.pop();
            }
        }
    }

    while(!operators.empty())
    {
        returned.push(operators.top());
        operators.pop();
    }

    return returned;
}

void writeRPN(queue<char> rpn)
{
    while(!rpn.empty())
    {
        cout << rpn.front() << ' ';
        rpn.pop();
    }
    cout << endl;
}

int main()
{
    ///{sign : [priority, left-sided, right-sided]}
    map<char, array<int, 3>> asd;
    asd.insert(make_pair('(', array<int, 3>{0, 0, 0}));
    asd.insert(make_pair('+', array<int, 3>{1, 1, 1}));
    asd.insert(make_pair('-', array<int, 3>{1, 1, 0}));
    asd.insert(make_pair('*', array<int, 3>{2, 1, 1}));
    asd.insert(make_pair('/', array<int, 3>{2, 1, 0}));
    asd.insert(make_pair('^', array<int, 3>{3, 0, 1}));

    writeRPN(convert("(2+3)*5", asd));
    writeRPN(convert("3+4*2/(1-5)^2", asd));
}