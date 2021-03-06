//
// Created by Marcus on 3/31/2015.
//

#include "SyntaxAnalyzer.hpp"


#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include "SemanticsTree.h"




using namespace std;
string tempType;
string tempID;
node *currentNode;
node *globalNode;
SemanticsTree semTable;
int tempIndex;
priority_queue<string> eval;



string expressionID;

SyntaxAnalyzer::SyntaxAnalyzer(vector<string> input) {
    exitString  = "Incorrect Syntax Exiting Program Current Token: ";
    tokenArray = input;
    index = 0;
    exitString = "Incorrect Syntax Exiting Program CURRENT TOKEN: " + currentToken;
    semTable = SemanticsTree();


    /*for (int i = 0; i < tokenArray.size(); ++i) {
        cout << tokenArray[i] << endl;
    }*/

}

SyntaxAnalyzer::~SyntaxAnalyzer() {
}

void SyntaxAnalyzer::setNewInput(string in) {


}

void SyntaxAnalyzer::syntax() {
    Splitter();
    program();

    if(currentToken =="$"){

        cout << "ACCEPT" <<endl;
    }else {
        cout << "REJECT" << currentToken << endl;
    }

}

void SyntaxAnalyzer::program(){
    //cout << "inside program call"<< endl;
    declarationList();

}

void SyntaxAnalyzer::declarationList(){
    // cout << "inside declarationList call"<< endl;
    declaration();
    if (currentClass == EMPTY) {
        FailExit();

    }
    declarationListPrime();
    if (currentClass == EMPTY){
        ;
    }
    //cout <<"LEAVING DECLARATIONLIST CALL"<<endl;
    //TokenStmt();
}

void SyntaxAnalyzer::declaration(){
    // cout<<"inside declaration call"<<endl;
    // cout <<"tokens: " << currentToken << " " << currentClass<< endl;

    typeSpecific();
    if (currentClass != EMPTY) {

        if(currentClass == ID) {
            // cout<< "inside declaratoin ID check"<<endl;
            tempID = currentToken;
            Splitter();
            // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            declarationPrime();
        }else {
            //cout<<"inside declartion fail ID check"<<endl;
            FailExit();
        }
    }
    // cout<<"LEAVING DECLARATION CALL"<<endl;
    //TokenStmt();
}

void SyntaxAnalyzer::declarationListPrime(){
    // cout<<"inside declarationListPrime call"<<endl;
    tempToken = currentToken;
    tempClass = currentClass;

    declaration();
    if (currentClass == EMPTY) {
        currentClass = tempClass;
        currentToken = tempToken;

    }else {
        declarationListPrime();
    }

}

void SyntaxAnalyzer::declarationPrime() {

    declarationPrimeFactor();
    if (currentClass == EMPTY) {
        currentClass = tempClass;
        currentToken = tempToken;

        semTable.insert(tempID, tempType);
        currentNode = semTable.search(tempID);
        if (currentToken == "(") {
            currentNode->numberOfParams = 0;
            Splitter();
            params();
            if (currentToken == ")") {
                Splitter();
                compoundStmt();
            }
        }else {
            FailExit();
        }
    }
    // cout<<"LEAVING DECLARATIONPRIME CALL"<<endl;

}

void SyntaxAnalyzer::declarationPrimeFactor() {
    /*cout<< "inside declarationPrimeFactor"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/

    if (currentToken == ";") {
        // Check to see if a var is of the void type
        if(tempType == "void"){
            SemReject();
        }
        if(!semTable.isCreated()) {
            semTable.insert("global");
            currentNode = semTable.search("global");
            globalNode = semTable.search("global");
        }
        for (vector<varList>::iterator it = currentNode->variables.begin(); it != currentNode->variables.end(); ++it) {
            if (it->varID.compare(tempID) == 0) {
                SemReject();
            }
        }
        if(!semTable.isCreated()) {
            semTable.varInsert("global", tempID, tempType);
        }else {
            for (vector<varList>::iterator it = globalNode->variables.begin(); it != globalNode->variables.end(); ++it) {
                if (it->varID.compare(tempID) == 0) {
                    SemReject();
                }
            }

            semTable.varInsert(currentNode->key, tempID, tempType);
        }


        //semTable.insert(tempID, tempType);
        Splitter();
    }else{
        //cout <<"inside declarationPrimeFactor else statement"<< endl;
        if(currentToken == "[") {
            if(tempType == "void"){
                SemReject();
            }
            if(!semTable.isCreated()) {
                semTable.insert("global");
                currentNode = semTable.search("global");
                globalNode = semTable.search("global");
            }
            for (vector<varList>::iterator it = currentNode->variables.begin(); it != currentNode->variables.end(); ++it) {
                if (it->varID.compare(tempID) == 0) {
                    SemReject();
                }
            }
            for (vector<varList>::iterator it = globalNode->variables.begin(); it != globalNode->variables.end(); ++it) {
                if (it->varID.compare(tempID) == 0) {
                    SemReject();
                }
            }


            Splitter();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            if (currentClass == INT) {

                // convert array index form string into a number
                stringstream convert(currentToken);
                convert >> tempIndex;


                for (int i = 0; i < tempIndex; ++i) {
                    semTable.varInsert(currentNode->key, tempID, tempType);
                }


                //cout << "inside declarationPrimeFactor NUM check"<<endl;
                Splitter();
                if (currentToken == "]") {
                    //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                    Splitter();
                    if (currentToken == ";") {
                        // insert array into varList

                        Splitter();

                    }else {
                        FailExit();
                    }
                } else {
                    FailExit();
                }
            } else {
                SemReject();
            }
        } else {
            tempToken = currentToken;
            tempClass = currentClass;
            currentClass = EMPTY;
        }
    }
    //cout <<"LEAVING DECLARATOINPRIMEFACTOR CALL"<<endl;
    // TokenStmt();

}

void SyntaxAnalyzer::typeSpecific(){


     tempType = currentToken;

    if(currentToken == "int"){
        // cout<< "inside typeSpecific  int if statement"<<endl;
        Splitter();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
    }else {
        if(currentToken == "float") {
            // cout<< "inside typeSpecific float if statement"<<endl;
            Splitter();
            // cout <<"tokens: " << currentToken << " " <<currentClass<< endl;
        } else {
            if(currentToken == "void") {
                // cout<< "inside typeSpecific void if statement"<<endl;
                Splitter();
                // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            }else {
                // Set Empty variable
                // cout<<"inside typeSpecific fail else statement"<<endl;
                // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                isEmpty();
            }
        }

    }
    //cout<<"leaving TYPESPECIFIC CALL"<<endl;

}

void SyntaxAnalyzer::params() {
    /*cout <<"inside params call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    tempType = currentToken;
    if (currentToken == "int") {

        Splitter();
        if (currentClass == ID) {
            tempID = currentToken;
            semTable.varInsert(currentNode->key, tempID, tempType);
            currentNode->paramVariables = currentNode->variables;
            //currentNode->numberOfParams++;
            Splitter();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            paramPrime();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            paramListPrime();
            if (currentClass == EMPTY) {
                currentClass = tempClass;
                currentToken = tempToken;
            }
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;

        } else {
            FailExit();
        }
    }else {
        if (currentToken=="void") {
            Splitter();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            if (currentToken != ")") {
                SemReject();
            }
            paramsPrime();
            // cout <<"tokens: " << currentToken << " " << currentClass<< endl;

        }else {
            if(currentToken == "float") {
                Splitter();
                if (currentClass == ID) {
                    tempID = currentToken;
                    semTable.varInsert(currentNode->key, tempID, tempType);
                    currentNode->paramVariables = currentNode->variables;
                    currentNode->numberOfParams++;
                    Splitter();
                    //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                    paramPrime();
                    //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                    paramListPrime();
                    if (currentClass == EMPTY) {
                        currentClass = tempClass;
                        currentToken = tempToken;
                    }
                    //cout <<"tokens: " << currentToken << " " << currentClass<< endl;

                } else {
                    FailExit();
                }
            }
        }
    }
}

void SyntaxAnalyzer::paramsPrime(){
    /*cout <<"inside paramsPrime call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/

    if(currentClass == ID) {
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        Splitter();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        paramPrime();
        // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        paramListPrime();
        if (currentClass == EMPTY) {
            currentClass = tempClass;
            currentToken = tempToken;
        }
        // cout <<"tokens: " << currentToken << " " << currentClass<< endl;

    }

}

void SyntaxAnalyzer::paramListPrime(){
    /*cout << "inside paramListPrime call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if (currentToken == ",") {
        Splitter();
        // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        param();
        if (currentClass == EMPTY) {
            FailExit();
        }else {
            paramListPrime();
            if (currentClass == EMPTY) {
                currentClass = tempClass;
                currentToken = tempToken;
            }
        }
    }else{
        tempClass = currentClass;
        tempToken = currentToken;
        currentClass = EMPTY;
    }

}

void SyntaxAnalyzer::param(){
    /*cout <<"inside Param call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    typeSpecific();
    int x =0;
    if (currentClass != EMPTY) {

        if (currentClass == ID) {
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            tempID = currentToken;
            semTable.varInsert(currentNode->key, tempID, tempType);
            currentNode->paramVariables = currentNode->variables;
            //currentNode->numberOfParams++;
            Splitter();
            // cout <<"tokens: " << currentToken << " " << currentClass<< endl;

        }else {
            FailExit();

        }
    }


}

void SyntaxAnalyzer::paramPrime(){
    /*cout << "inside paramPrime call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if(currentToken =="[") {
        Splitter();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        if (currentToken =="]") {
            Splitter();
        } else {
            FailExit();
        }
    }

}

void SyntaxAnalyzer::compoundStmt(){
    /*cout << "inside compoundStmt call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if (currentToken == "{") {
        Splitter();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        localDeclarationsPrime();
        // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        EmptyCheck();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        statementListPrime();
        EmptyCheck();
        // Need to check if empty is ok for statementLIst
        if (currentToken == "}") {

            if(currentNode->semType.compare("int") == 0 || currentNode->semType.compare("float") == 0) {
                if(!currentNode->hasReturn) {
                    SemReject();
                }
            }
            Splitter();
            // TokenStmt();
        }else {
            FailExit();
        }
    }else {
        isEmpty();
    }

}
// May be able to Delete this Method
void SyntaxAnalyzer::localDeclarations(){
    localDeclarationsPrime();

}

void SyntaxAnalyzer::localDeclarationsPrime(){
    //cout<<"inside localDeclarationsPrime call"<<endl;
    tempToken = currentToken;
    typeSpecific();
    if (currentClass != EMPTY) {
        if (currentClass == ID) {
            tempID = currentToken;
            // check to see if variable has already been
            Splitter();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            declarationPrimeFactor();
            if (currentClass == EMPTY) {
                FailExit();
            }
            localDeclarationsPrime();
            EmptyCheck();
        }else {
            FailExit();
        }
    }
    //cout<<"LEAVING LOCALdECLARATIONSpRIME"<<endl;

}
// May be able to Delete this Method
void SyntaxAnalyzer::statementList(){

}

void SyntaxAnalyzer::statementListPrime(){
    /* cout<<"inside statementListPrime call"<<endl;
     cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    statement();
    if (currentClass != EMPTY) {
        statementListPrime();
        EmptyCheck();
    }else {
        EmptyCheck();
    }


    //cout<<"LEAVING STATEMENTLISTPrime"<<endl;
}

void SyntaxAnalyzer::statement(){
    //cout<<"inside statement call"<<endl;
    // TokenStmt();
    expressionStmt();
    if (currentClass == EMPTY) {
        EmptyCheck();
        compoundStmt();
        if (currentClass == EMPTY) {
            EmptyCheck();
            selectionStmt();
            if (currentClass == EMPTY) {
                EmptyCheck();
                iterationStmt();
                if (currentClass == EMPTY) {
                    EmptyCheck();
                    returnStmt();

                }
            }
        }
    }
    //cout<<"LEAVING STATEMENT CALL"<<endl;
}

void SyntaxAnalyzer::expressionStmt(){
    /* cout<<"inside expressionStmt call"<<endl;
     TokenStmt();*/
    expression();
    if (currentClass != EMPTY) {
        if (currentToken == ";") {
            string temp;
            string evalcheck;
            while (!eval.empty()) {

                evalcheck = semTable.hasBeenDeclared(eval.top(), currentNode);
                if (evalcheck.compare("") == 0) {
                    SemReject();
                }

                if(eval.top().compare("int") == 0 || eval.top().compare("float") == 0)  {
                    if(evalcheck.compare(eval.top()) == 0) {
                        evalcheck = eval.top();
                        eval.pop();
                    }else {
                        SemReject();
                    }
                }else {
                    // call hasBeenDeclared since tehre is an id to be check
                    temp = semTable.hasBeenDeclared(eval.top(), currentNode);
                    if (temp.compare("") == 0) {
                        SemReject();
                    }

                    if (evalcheck.compare(temp) == 0) {
                        evalcheck = temp;
                        eval.pop();
                    }else {
                        SemReject();
                    }

                }
            }


            // TokenStmt();
            Splitter();
            // TokenStmt();
        }
    }else {
        EmptyCheck();
        if (currentToken == ";") {
            // TokenStmt();
            Splitter();
            // TokenStmt();
        }else {
            isEmpty();
        }
    }
    // cout<<"LEAVING EXPRESSIONSTMT"<<endl;

}

void SyntaxAnalyzer::selectionStmt(){
    //cout<<"inside selectionStmt call"<<endl;
    // TokenStmt();
    if (currentToken == "if") {
        Splitter();
        // TokenStmt();
        if (currentToken == "(") {
            Splitter();
            //  TokenStmt();
            expression();
            // cout<<"PASSED EXPRESSION IN SELECTIONSTMT"<<endl;
            //TokenStmt();
            if (currentClass != EMPTY) {
                //cout<<"CHECKING FOR  ) "<<endl;
                if (currentToken == ")") {
                    // cout<<"CHECKING FOR )"<<endl;
                    Splitter();
                    // TokenStmt();
                    statement();
                    // cout<<"CHECKING TO SEE IF EMPTY OR ELSE IS HERE"<<endl;
                    // TokenStmt();
                    if (currentClass == EMPTY) {
                        FailExit();
                    }else {
                        selectionStmtPrime();
                        EmptyCheck();
                    }
                }
            }else {
                FailExit();
            }
        }else {
            FailExit();
        }

    }else {
        isEmpty();
    }
    /*cout<<"LEAVING SELECTIONSTMT"<<endl;
    TokenStmt();*/

}

void SyntaxAnalyzer::selectionStmtPrime(){
    /*cout << "inside selectionStmtPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == "else") {
        Splitter();
        // TokenStmt();
        statement();
        if (currentClass == EMPTY) {
            FailExit();
        }
    }else {
        isEmpty();
    }
    /*cout<<"LEAVING SELECTIONSTMTPRIME"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::iterationStmt(){
    /*cout<<"inside iteratoinStmt call"<<endl;
    TokenStmt();*/
    if (currentToken == "while") {
        Splitter();
        // TokenStmt();
        if (currentToken == "(") {
            Splitter();
            // TokenStmt();
            expression();
            if (currentClass != EMPTY) {
                if (currentToken == ")") {
                    Splitter();
                    // TokenStmt();
                    statement();
                    EmptyCheck();
                } else {
                    FailExit();
                }
            }
            else {
                FailExit();
            }

        }
    }else {
        isEmpty();
    }
    // cout<<"LEAVING ITERATIONsTMT"<<endl;
}

void SyntaxAnalyzer::returnStmt(){
    /*cout<<"inside returnStmt call"<<endl;
    TokenStmt();*/
    if (currentToken == "return") {
        currentNode->hasReturn = true;
        Splitter();
        // TokenStmt();
        returnStmtPrime();
        if (currentClass == EMPTY) {
            FailExit();
        }

    }else {
        isEmpty();
    }
    //cout<<"LEAVING RETURNSTMT"<<endl;
    // TokenStmt();
}

void SyntaxAnalyzer::returnStmtPrime(){
    /*cout<<"inside returnStmtPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == ";") {
        if(currentNode->semType.compare("void") != 0) {
            SemReject();
        }
        Splitter();
        // TokenStmt();

    } else {
        tempID = currentToken;
        string returnType = semTable.hasBeenDeclared(tempID, currentNode);
        if(returnType != "") {
            if(currentNode->semType.compare(returnType) != 0) {
                SemReject();
            }
        } else {
            SemReject();
        }

        expression();
        //cout<<"CHECK TO SEE IF RETURNSTMTPRIME CAN MOVE"<<endl;
        //TokenStmt();
        if (currentToken == ";") {

            Splitter();
            //TokenStmt();
        }else {
            FailExit();
        }
    }

    /*cout<<"LEAVING RETURNSTMTPRIME"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::expression() {
    // cout<<"inside expression Call"<<endl;

    if (currentClass == ID) {
        expressionID = currentToken;
        eval.push(expressionID);
        tempID = currentToken;
        /*cout<<"INSIDE EXPRESSION id CHECK"<<endl;
        TokenStmt();*/
        Splitter();
        //TokenStmt();
        expressionFactor();
        //TokenStmt();
        EmptyCheck();

    }else {
        if (currentToken == "(") {
            // TokenStmt();
            Splitter();

            expression();
            if (currentClass == EMPTY) {
                FailExit();
            }else {
                if (currentToken == ")") {
                    Splitter();
                    //TokenStmt();
                    termPrime();
                    EmptyCheck();
                    additiveExpressionPrime();
                    EmptyCheck();
                    simpleExpressionPrime();
                    EmptyCheck();

                }
            }
        }else {
            if (currentClass == INT) {
                eval.push("int");
                Splitter();
                //TokenStmt();
                termPrime();
                EmptyCheck();
                additiveExpressionPrime();
                EmptyCheck();
                simpleExpressionPrime();
                EmptyCheck();

            }else {
                if (currentClass == FLOAT) {
                    eval.push("float");
                    Splitter();
                    //TokenStmt();
                    termPrime();
                    EmptyCheck();
                    additiveExpressionPrime();
                    EmptyCheck();
                    simpleExpressionPrime();
                    EmptyCheck();

                }else {
                    isEmpty();
                }

            }
        }
    }
    /*cout<<"leaving expression"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::expressionFactor(){
    //cout<<"inside expressionFactor call"<< endl;

    expressionPrime();
    EmptyCheck();
    if (currentToken == "=") {

        Splitter();
        // TokenStmt();
        expression();
        if (currentClass == EMPTY) {
            FailExit();
        }

    }else {
        factorPrime();
        EmptyCheck();
        termPrime();
        EmptyCheck();
        additiveExpressionPrime();
        EmptyCheck();
        simpleExpressionPrime();
        EmptyCheck();
    }
    /*cout<<"leaving expressionFactor"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::expressionPrime(){
    /*cout<<"inside expressionPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == "[") {
        Splitter();
        // TokenStmt();
        expression();
        if (currentClass == EMPTY) {
            FailExit();
        }else {
            if (currentToken == "]") {
                Splitter();
                //TokenStmt();
            } else {
                FailExit();
            }
        }
    }else {
        isEmpty();
    }

}

void SyntaxAnalyzer::simpleExpressionPrime(){
    /*cout<<"inside simpleExpressionPrime()"<<endl;
    TokenStmt();*/
    relop();
    if (currentClass != EMPTY) {
        //cout<<"inside simpleExpressionPrime EMPTY"<<endl;
        additiveExpression();
        // cout<<"passed additiveExpression in simpleExpression"<<endl;
        //TokenStmt();
        EmptyCheck();
        //cout<<"checking tokens after additive"<<endl;
        //TokenStmt();
        if (currentClass == EMPTY) {
            //cout<<"inside simpeleExpressionPrime Fail"<<endl;
            FailExit();
        }
    }/*else {
        cout<<"CHECKING<<<<<<<<"<<endl;
       // TokenStmt();
        isEmpty();
       // TokenStmt();
    }*/
    /*cout<<"leaving simpleExpressionPrime"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::relop() {
    /*cout<<"inside relop call"<<endl;
    TokenStmt();*/
    if (currentToken == "<=") {
        Splitter();
        //TokenStmt();

    }else {
        if (currentToken == "<") {
            Splitter();
            //TokenStmt();

        }else {
            if (currentToken == ">") {
                Splitter();
                //TokenStmt();

            }else {
                if (currentToken == ">=") {
                    Splitter();
                    //TokenStmt();

                }else {
                    if (currentToken == "==") {
                        Splitter();
                        //TokenStmt();

                    }else {
                        if (currentToken == "!=") {
                            Splitter();
                            //TokenStmt();

                        }else {
                            isEmpty();
                        }
                    }
                }
            }

        }
    }
    /*cout<<"leaving relop call"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::additiveExpression(){
    /*cout<<"inside additiveExpression Call"<<endl;
    TokenStmt();*/
    term();
    if (currentClass != EMPTY) {
        //cout<<"inside additiveExpression EMPTY check"<<endl;
        additiveExpressionPrime();
        //cout<<"Passed addtiiveExpressionPrime in addtiveExpression"<<endl;
        EmptyCheck();
    }
    /*cout<<"LEAVING ADDITIVEEXPRESSION"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::additiveExpressionPrime(){
    /*cout<<"inside additiveExpressionPrime call"<<endl;
    TokenStmt();*/
    addop();
    if (currentClass != EMPTY) {
        // cout<<"inside additiveExpressionPrime empty check"<<endl;
        term();
        if (currentClass != EMPTY) {
            additiveExpressionPrime();
            // cout<<"inside additiveExpressionPrime term check"<<endl;
            EmptyCheck();
        }else {
            // cout<<"inside additiveExpression Fail check"<<endl;
            //FailExit();
        }
    }
    /*cout<<"leaving additiveExpressionPrime"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::addop(){
    /* cout<<"inside addop call"<<endl;
     TokenStmt();*/
    if (currentToken == "+") {
        Splitter();
        //TokenStmt();
    }else {
        if (currentToken == "-") {
            Splitter();
            //TokenStmt();
        }else {
            /*cout<<"inside empty of addop"<<endl;
            TokenStmt();*/
            isEmpty();
            //  TokenStmt();
        }
    }
    /*cout<<"leaving addop"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::term(){
    /*cout<<"inside term call"<<endl;
    TokenStmt();*/
    factor();
    if (currentClass != EMPTY) {
        termPrime();
        EmptyCheck();
    }else {
        FailExit();
    }
    /*cout<<"leaving term()"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::termPrime(){
    /*cout<<"inside termPrime"<<endl;
    TokenStmt();*/
    mulop();
    if (currentClass != EMPTY) {
        // TokenStmt();
        factor();
        if (currentClass != EMPTY) {
            // TokenStmt();
            termPrime();
            EmptyCheck();
        }else {
            FailExit();
        }
    }
    /* cout<<"leaving termPrime"<<endl;
     TokenStmt();*/
}

void SyntaxAnalyzer::mulop(){
    /*cout<<"inside mulop call"<<endl;
    TokenStmt();*/
    if (currentToken == "*") {
        Splitter();
        // TokenStmt();
    }else {
        if (currentToken == "/") {
            Splitter();
            //TokenStmt();
        } else {
            isEmpty();
        }
    }
    /* cout<<"leaving mulop"<<endl;
     TokenStmt();*/
}

void SyntaxAnalyzer::factor(){
    /*cout<<"inside factor call"<<endl;
    TokenStmt();*/
    if (currentToken == "(") {
        // cout<<"inside factor ( if statement"<<endl;
        Splitter();
        //TokenStmt();
        expression();
        if (currentClass == EMPTY) {
            FailExit();
        }else {
            if (currentToken == ")") {
                //cout<<"inside factor ) if statement"<<endl;
                Splitter();
                //TokenStmt();
            }else {
                FailExit();
            }
        }
    }else {
        if (currentClass == INT) {
            eval.push("int");
            Splitter();
            //TokenStmt();
        }else {
            if (currentClass == FLOAT) {
                eval.push("flaot");
                Splitter();
                //TokenStmt();
            }else {
                if (currentClass == ID) {
                    eval.push(currentToken);
                    Splitter();
                    // TokenStmt();
                    factorPrime();
                    EmptyCheck();
                }else{
                    isEmpty();
                }
            }
        }
    }
    /*cout<<"LEAVING FACTOR"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::factorPrime(){
    /*cout<<"inside factorPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == "(") {
        Splitter();
        //  TokenStmt();
        args();

        if (currentToken == ")") {
            Splitter();
            //  TokenStmt();
        }
    }else {
        expressionPrime();
        EmptyCheck();

    }
    /*cout<<"LEAVING FACTORPRIME"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::args(){
    /*cout<<"inside args call"<<endl;
    TokenStmt();*/
    expression();
    if (currentClass != EMPTY) {
        argsPrime();
        EmptyCheck();
    }
    //cout<<"leaving args call"<<endl;
}

void SyntaxAnalyzer::argsPrime(){
    /*cout<<"inside argsPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == ",") {
        Splitter();
        expression();
        // TokenStmt();
        if (currentClass == EMPTY) {
            FailExit();
        }
        argsPrime();
        EmptyCheck();
    }else {
        isEmpty();
    }
    //cout<<"leaving argsPrime"<<endl;
}

void SyntaxAnalyzer::Splitter() {
    string buf;
    stringstream ss(tokenArray[index]);
    vector<string> splitToken;



    while (ss >> buf) {
        splitToken.push_back(buf);
    }

    if (splitToken.size()> 1) {
        stringstream convert(splitToken[1]);
        currentToken = splitToken[0];
        convert >> currentClass;
        //cout << "Split Tokens: " << currentToken << " " << currentClass <<endl;
    } else {
        currentToken = splitToken[0];

    }
    index++;
}

void SyntaxAnalyzer::FailExit() {
    cout << exitString << currentToken << " indexed: " << index <<endl;
    exit(1);
}

void SyntaxAnalyzer::EmptyCheck() {
    if (currentClass == EMPTY) {
        currentClass = tempClass;
        currentToken = tempToken;
    }
}

void SyntaxAnalyzer::TokenStmt() {
    cout <<"tokens: " << currentToken << " " << currentClass << endl;
}

void SyntaxAnalyzer::isEmpty() {
    tempToken = currentToken;
    tempClass = currentClass;
    currentClass = EMPTY;
}

void SyntaxAnalyzer::SemReject() {
    cout << "REJECT" << endl;
    exit(1);

}
