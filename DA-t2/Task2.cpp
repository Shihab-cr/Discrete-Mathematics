#include <iostream>
#include <vectOR>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;

//****************************************************Operators part ****************************
enum class OperatOR : char{
    NOT = '~',
    AND = '^',
    OR = 'v',
    open_paren = '(',
    closed_paren = ')'
};
int gateOutput(int input1, int input2, char logicGate){
    bool result;
    switch(logicGate){
    case (char)OperatOR::OR:
        result = input1 || input2;
        break;
    case (char)OperatOR::AND:
        result = input1 && input2;
        break;
    case (char)OperatOR::NOT:
        if(!input1){
            result = true;
        }
        else
            result = false;
    }
    if(result)
        return 1;
    else
        return 0;
}

bool isOperatOR(char token){
return
token == (char)OperatOR::NOT ||
token == (char)OperatOR::AND ||
token == (char)OperatOR::OR ||
token == (char)OperatOR::open_paren ||
token == (char)OperatOR::closed_paren;

}

int getPrecedance(char token){
if(token == (char)OperatOR::NOT)
    return 3;
else if(token == (char)OperatOR::AND)
    return 2;
else if(token == (char)OperatOR::OR)
    return 1;
else
    return 0;
}

//************************************************************************************************
//***************************************************Helper classes ******************************
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

class VectorStack{
    vector<vector<int>> mylist;

public:
    VectorStack(){}

    void Push(vector<int> o){
        mylist.push_back(o);
    }
    void Pop(){
        if(!mylist.empty())
            mylist.pop_back();
    }
    vector<int> top(){
        if(!mylist.empty())
            return mylist.back();
        else
            return {};
    }
    bool isEmpty(){
        return mylist.empty();
    }
};

//************************************************************************************************
//***************************************************Table generation*****************************
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

struct tableStatus{
    bool isTautalogy;
    bool isSatisfiability;
    bool isContracdition;
};

tableStatus checkTableStatus(vector<int> arr){
    bool hasOne = false;
    bool hasZero = true;
    for(int i : arr){
        if(i){
            hasOne = true;
        }
        else{
            hasZero = true;
        }
    }
    return {!hasZero && hasOne, hasOne,!hasOne && hasZero};
}

vector<char> logicalCircuit_HANDler(string userInput){
    userInput.erase(remove(userInput.begin(),userInput.end(),' '), userInput.end());
    vector<char> result;
    Stack* stk = new Stack;

    for(int i=0; i<userInput.length();i++){
            if(!isOperatOR(userInput[i])){
                //then its a gate so place it directly in result
                result.push_back(userInput[i]);
            }
            else{
                //then its an operatOR

                if(userInput[i]== (char)OperatOR::closed_paren){
                    char temp;
                    do{
                        temp = stk->top();
                        stk->popFromStack();
                        if(temp != (char)OperatOR::open_paren)
                            result.push_back(temp);
                    }while(temp != (char)OperatOR::open_paren);

                continue;
                }
                    int currPriORity;
                    int topPriORity;
                do{
                        if(userInput[i]==(char)OperatOR::open_paren || stk->isEmpty()){
                            break;
                           }
                    currPriORity = getPrecedance(userInput[i]);
                    if(stk->top()==(char)OperatOR::open_paren){
                        break;
                       }
                    topPriORity = getPrecedance(stk->top());
                    if(topPriORity>= currPriORity){
                        char c = stk->top();
                        stk->popFromStack();
                        result.push_back(c);
                    }
                }while(topPriORity>currPriORity);
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

struct truthTable{
    vector<vector<int>> grid;
    int rowsNum =0;
    int columnsNum=0;
    vector<pair<char,int>> gates;

};

void printSatisfiableInputs(vector<int> results, truthTable table){
    bool isFound = false;
    for(int i=0; i<static_cast<int>(results.size());i++){
        if(results[i]==1){
            isFound=true;
            cout<<"result is satisfiable "<<endl;
            for(int j=0;j<table.columnsNum;j++){
                cout<<table.gates[j].first<<"="<<table.grid[i][j]<<" ";
            }
            cout<<endl;
            cout<<endl;
        }
    }
    if(!isFound) cout<<" result is a contradiction"<<endl;
}

truthTable tableGenerator(vector<char> logicCircuit){
    int circuitSize = static_cast<int>(logicCircuit.size());
    truthTable data;
    vector<char> uniqueInputs;
    for(int i=0; i<circuitSize; i++){
        if(!isOperatOR(logicCircuit[i])){
                bool alreadyListed = false;

                for(char v : uniqueInputs){
                    if(logicCircuit[i] == v){
                        alreadyListed = true;
                    }
                }
                if(!alreadyListed){
                        uniqueInputs.push_back(logicCircuit[i]);
                }
        }
    }
    sort(uniqueInputs.begin(), uniqueInputs.end());
    for(size_t i=0; i<uniqueInputs.size();i++){
        data.gates.push_back({uniqueInputs[i],i});
        data.columnsNum++;
    }
    int gateNum = static_cast<int>(data.gates.size());
    int rowsNum = pow(2,gateNum);
    data.rowsNum = rowsNum;
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

int getGateIndex(truthTable data, char input){
    for(pair<char,int> v : data.gates){
        if(v.first == input){
            return v.second;
        }
    }
    return -1;

}

vector<int> evalutor(vector<int>& in1, vector<int>& in2, char gate){
    vector<int> result;
    int temp;
    for(int i=0; i<static_cast<int>(in1.size()); i++){
            temp = gateOutput(in1[i],in2[i],gate);
            result.push_back(temp);
    }
    return result;

}

vector<int> generateResult(truthTable data, vector<char> postfix_Circuit){

    VectorStack *stk = new VectorStack;
    stack<string> nameStk;

    for(int i=0; i<static_cast<int>(postfix_Circuit.size());i++){
        if(!isOperatOR(postfix_Circuit[i])){
            int inputIndex = getGateIndex(data, postfix_Circuit[i]);
            vector<int> temp;
            for(int l=0;l<data.rowsNum;l++){
                temp.push_back(data.grid[l][inputIndex]);
            }
            stk->Push(temp);
            string s(1,postfix_Circuit[i]);
            nameStk.push(s);
        }
        else{
            vector<int> in1;
            vector<int> in2;
            if(postfix_Circuit[i] == (char)OperatOR::NOT){
                in1 = stk->top();
                in2 = in1;
                stk->Pop();
                string newName = (char)OperatOR::NOT + nameStk.top();
                nameStk.pop();
                cout<<"evaluating "<<newName<<endl;
                nameStk.push(newName);
            }
            else{
                in1 = stk->top();
                stk->Pop();

                in2= stk->top();
                stk->Pop();

                string rightOp = nameStk.top();
                nameStk.pop();
                string leftOp = nameStk.top();
                nameStk.pop();

                string newName = (char)OperatOR::open_paren + leftOp + postfix_Circuit[i] + rightOp + (char)OperatOR::closed_paren;
                cout<<"evaluating "<<newName<<endl;
                nameStk.push(newName);
            }
            vector<int> temp = evalutor(in1,in2,postfix_Circuit[i]);

            for(size_t op=0;op<temp.size();op++){
                cout<<temp[op]<<endl;
            }
            stk->Push(temp);
        }
    }
    vector<int> res = stk->top();
    stk->Pop();
    return res;
}



void repairLogic(vector<char> PostfixCircuit, truthTable data){
    for(int i=0; i<PostfixCircuit.size();i++){
        char originalToken = PostfixCircuit[i];
        if(isOperatOR(originalToken)){
            char newToken = '\0';
            if(originalToken == (char)OperatOR::AND)
                newToken = (char)OperatOR::OR;
            else if(originalToken == (char)OperatOR::OR)
                newToken = (char)OperatOR::AND;

            if(newToken != '\0'){
                vector<char> newCircuit = PostfixCircuit;
                newCircuit[i] = newToken;

                truthTable newTable = tableGenerator(newCircuit);
                vector<int> newResults = generateResult(newTable, newCircuit);
                tableStatus status = checkTableStatus(newResults);

                if(!status.isContracdition && !status.isTautalogy && status.isSatisfiability){
                    cout<<"has correctly fixed the table "<<endl;
                    cout<<"Success! at changing gate at index"<< i << " from " << originalToken << " to " << newToken << endl;
                    printSatisfiableInputs(newResults,newTable);
                    return;
                }

            }
        }
    }
    cout << "Could not auto-repair the circuit by swapping one gate." << endl;
}



bool Comparator(vector<int> mainLogic, vector<int> simplifiedLogic, int tableSize){

    bool isEqual = true;
    for(int i=0;i<tableSize;i++){
        if(mainLogic[i] != simplifiedLogic[i])
            isEqual = false;
    }
    return isEqual;
}

void ProgramHandler(string circuit, string s){
    vector<char> PostFixCircuit = logicalCircuit_HANDler(circuit);
    truthTable table = tableGenerator(PostFixCircuit);
    cout<<"Main Circuit: "<< endl;
    for(int i=0;i<table.columnsNum;i++)
            cout<<table.gates[i].first<<" ";
    cout<<endl;
    for(int i=0;i<table.rowsNum;i++){
        for(int j=0;j<table.columnsNum;j++){
            cout<<table.grid[i][j]<<" ";
        }
        cout<<endl;
    }
    vector<int> MC_result = generateResult(table, PostFixCircuit);
    tableStatus MC_status = checkTableStatus(MC_result);
    if(MC_status.isSatisfiability){
        printSatisfiableInputs(MC_result, table);
    }
    else if(MC_status.isContracdition){
        cout<<"Circuit is always false (CONTRAICTORY)"<<endl;
    }
    else if(MC_status.isTautalogy){
        cout<<"Circuit is always true"<<endl;
    }

    if(MC_status.isContracdition || MC_status.isTautalogy){
        string startRepair;
        cout<<"Attempt auto repair of circuit?"<<endl;
        cout<<"type [y] to accept "<< " type [n] to reject"<<endl;
        cin>>startRepair;
        if(startRepair=="y"){
            repairLogic(PostFixCircuit, table);
        }
    }



    vector<char> simplified = logicalCircuit_HANDler(s);
    truthTable simpleTable = tableGenerator(simplified);
    cout<<"Simplified Circuit: "<< endl;
    for(int i=0;i<simpleTable.columnsNum;i++)
            cout<<simpleTable.gates[i].first<<" ";
    cout<<endl;
    for(int i=0;i<simpleTable.rowsNum;i++){
        for(int j=0;j<simpleTable.columnsNum;j++){
            cout<<simpleTable.grid[i][j]<<" ";
        }
        cout<<endl;
    }
    vector<int> SC_result = generateResult(simpleTable, simplified);

    if(Comparator(MC_result, SC_result, static_cast<int>(MC_result.size()))){
        cout<<"both generate the same result"<< endl;
    }
    else{
        cout<<"don't match"<<endl;
    }
}




int main(){
    string mainLogicInput;
    string simplified;
    cout<<"Please follow the following instructions"
    <<endl<<"use the following symbols to represent the desired gates"
    <<endl<<"OR -> v"
    <<endl<<"AND -> ^"
    <<endl<<"NOT -> ~"
    <<endl <<"Enter up to 3 gates"
    <<endl<<"if you want to apply negation to mORe than 1 gate use ()"
    <<endl<<"example ~(AvB)^C"
    <<endl<<"Type exit to terminate"
    <<endl<<"---------------------";
    do{
    cin>>mainLogicInput;
    cin>>simplified;

    ProgramHandler(mainLogicInput, simplified);

    }while(mainLogicInput != "exit" || simplified != "exit");
}

