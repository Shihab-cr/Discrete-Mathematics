#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<char> intToBinary(int n, int numOfBits){
    vector<char> temp;
    for(int i=numOfBits-1; i>=0; i--){
        int k = (n>>i)&1;
        if(k==1)
            temp.push_back('1');
        else{
            temp.push_back('0');
        }
    }
    return temp;
}

class Node{
private:
    char token;
    Node* next;
public:
    Node(char c){
        this->token = c;
        next = nullptr;
    }
    void setNext(Node* newNext){
        this->next = newNext;
    }
    Node* getNext(){
        return next;
    }
    char getToken(){
        return token;
    }

//    friend List;
};

class List{
private:
    Node * head;
    int length;
public:
    List(){
        head = nullptr;
        length = 0;
    }
    bool isEmpty(){
        return head == nullptr;
    }
    void addFront(Node* pointer){
        if(head == nullptr){
            head = pointer;
            length++;
        }
        else{
            pointer->setNext(head);
            head = pointer;
            length++;
        }
    }
    int getLength(){
        return this->length;
    }
    void popFront(){
        //char topChar;
        if(isEmpty())
            return;
            // '\0';
        else{
            Node* currNode = head;
            head = currNode->getNext();
            //topChar = currNode->getToken();
            length--;
            delete currNode;
            //return topChar;
        }
    }
    char getTop(){
        char topChar;
        if(isEmpty())
            return '\0';
        else{
            Node* currNode = head;
            topChar = currNode->getToken();
            return topChar;
        }
    }

};

class Stack{
    List* stck;
public:
    Stack(){
        stck = new List();
    }
    char top(){
        if(stck->isEmpty()){
            cout<<"stack is empty"<<endl;
            return '\0';
        }
        else{
            return stck->getTop();
        }
    }
    void pushIntoStack(Node* e){
        stck->addFront(e);
    }
    void popFromStack(){
        stck->popFront();
    }
    bool isEmpty(){
        return stck->isEmpty();
    }
};


vector<char> logicalCircuit_Handler(string userInput){
    vector<char> result;
    Stack* stk = new Stack;

    for(int i=0; i<userInput.length();i++){
            if(userInput[i] != '~' && userInput[i] != 'v' && userInput[i] != '^' && userInput[i] !='(' && userInput[i] != ')'){
                //then its a gate so place it directly in result
                result.push_back(userInput[i]);
            }
            else{
                //then its an operator

                if(userInput[i]==')'){
                    char temp;
                    do{
                        temp = stk->top();
                        result.push_back(temp);
                        stk->popFromStack();
                    }while(temp != '(');
                if(stk->top() == '(')
                    stk->popFromStack();
                continue;
                }
                    int currPriority;
                    int topPriority;
                do{
                        if(userInput[i]=='(' || stk->isEmpty()){
                            break;
                           }
                    switch(userInput[i]){
                        case '~':
                            currPriority = 3;
                            break;
                        case '^':
                            currPriority = 2;
                            break;
                        case 'v':
                            currPriority = 1;
                            break;
                    }
                    if(stk->top()=='('){
                        break;
                       }
                    switch(stk->top()){
                        case '~':
                            topPriority = 3;
                            break;
                        case '^':
                            topPriority = 2;
                            break;
                        case 'v':
                            topPriority = 1;
                            break;
                    }
                    if(topPriority>= currPriority){
                        char c = stk->top();
                        stk->popFromStack();
                        result.push_back(c);
                    }
                }while(topPriority>currPriority);
                Node* c = new Node(userInput[i]);
                stk->pushIntoStack(c);
            }
    }
    while(!stk->isEmpty()){
            char temp = stk->top();
            stk->popFromStack();
            result.push_back(temp);
    }
    return result;
}

int gateOutput(int input1, int input2, char logicGate){
    bool result;
    switch(logicGate){
    case 'v':
        result = input1 || input2;
        break;
    case '^':
        result = input1 && input2;
        break;
    }
    if(result)
        return 1;
    else
        return 0;
}

struct truthTable{
    vector<vector<int>> grid;
    vector<char> gates;
};

truthTable tableGenerator(vector<char> logicCircuit){
    int circuitSize = static_cast<int>(logicCircuit.size());
    truthTable data;
    for(int i=0; i<circuitSize; i++){
        if(logicCircuit[i] != '~' && logicCircuit[i] != 'v' && logicCircuit[i] != '^' && logicCircuit[i] != '(' && logicCircuit[i] != ')'){
                bool alreadyListed = false;

                for(char v : data.gates){
                    if(logicCircuit[i] == v){
                        alreadyListed = true;
                    }
                }
                if(!alreadyListed)
                    data.gates.push_back(logicCircuit[i]);
        }
    }
    int gateNum = static_cast<int>(data.gates.size());
    int rowsNum = pow(2,gateNum);
    data.grid.resize(rowsNum, vector<int>(gateNum));

    int counter =0;

    for(int i=0;i<rowsNum;i++){
        vector<char> temp = intToBinary(i, gateNum);

        for(int j=0; j<gateNum; j++){
            if(temp[j]=='1')
                data.grid[i][j] =  1;
            else
                data.grid[i][j] =  0;
        }

    }

    return data;
}

vector<int> evalutor(truthTable data, vector<char> PostFix_circuit){

    //work in progress
    int gateNum = static_cast<int>(data.gates.size());
    int circSize = static_cast<int>(PostFix_circuit.size());
    Stack* stk = new Stack;

    for(int i=0; i<circSize;i++){
            if(PostFix_circuit[i] != '~' && PostFix_circuit[i] != 'v' && PostFix_circuit[i] != '^' && PostFix_circuit[i] != '(' && PostFix_circuit[i] != ')'){
                Node* gate = new Node(PostFix_circuit[i]);
                stk.pushIntoStack(gate);
            }else{
                if(PostFix_circuit[i] != '~'){

                }
            }
    }

}

bool Comparator(vector<int> mainLogic, vector<int> simplifiedLogic, int tableSize){

    bool isEqual = true;
    for(int i=0;i<tableSize;i++){
        if(mainLogic[i] != simplifiedLogic[i])
            isEqual = false;
    }
    return isEqual;
}


int main(){
    string mainLogicInput;
    cout<<"Please follow the following instructions"
    <<endl<<"use the following symbols to represent the desired gates"
    <<endl<<"OR -> v"
    <<endl<<"AND -> ^"
    <<endl<<"NOT -> ~"
    <<endl <<"Enter up to 3 gates"
    <<endl<<"if you want to apply negation to more than 1 gate use ()"
    <<endl<<"example ~(AvB)^C"
    <<endl<<"---------------------";

    cin>>mainLogicInput;
    vector<char> LogicCircuit = logicalCircuit_Handler(mainLogicInput);
    int sizeCircuit = static_cast<int>(LogicCircuit.size());
    for(int i=0; i<sizeCircuit; i++){
        cout<<endl<<LogicCircuit[i];
    }
}

