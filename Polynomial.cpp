#include <bits/stdc++.h>
#include <vector>
#include <math.h>
#include <string.h>

using namespace std;

class Polynomial{
    class term{
        public:
            int value;
            int pow=0;
    };

    vector<term*> poly_list;

    public:
        Polynomial(string pol);
        Polynomial(){};
        string print();
        Polynomial operator+(const Polynomial &obj);
        Polynomial operator-(const Polynomial &obj);
        Polynomial operator*(const Polynomial &obj);
        bool operator==(const Polynomial &obj);
        void operator=(const Polynomial &obj);


    private:
        void insert(string x);
        int to_int(string num);
        void push_back(int value , int pow);
        void clear();
};

Polynomial::Polynomial(string pol){
    int start = 0;
    for (int i = 0; i < pol.length(); i++) {
        if (pol[i] == '+' || pol[i] == '-' || i == pol.length() - 1) {
            string term = pol.substr(start, i - start + 1);
            if (term[0] != '+' && term[0] != '-') {
                term = "+" + term;
            }
            else if(term[0] == '-'){
                term = "-" + term;
            }
            if(term[term.length() - 1] == '+' || term[term.length() - 1] == '-'){
                term[term.length() - 1] = '\0';
            }
            this->insert(term);
            start = i;
        }
    }
}

void Polynomial::insert(string x){
    term *new_t = new term();
    string *value = new string();
    string *pow = new string();
    *value = x.substr(0 , x.find("x"));
    if(x.find('^')!=-1){
        *pow = x.substr(x.find('^')+1);
    }
    else if(x.find("x") != -1 && x.find('^')==-1){
        *pow = '1';
    }
    else if(x.find("x") == -1 && x.find('^')==-1){
        *pow = '0';
    }


    new_t->value = this->to_int(*value);
    new_t->pow = this->to_int(*pow);

    this->poly_list.push_back(new_t);

}

int Polynomial::to_int(string num){
    int number=0 , i=0 , sign = 1;
    if(num[0] == '-'){
        i=1;
        sign = -1;
    }
    else if(num[0] == '+'){
        i=1;
    }
    for(; i<num.length() ; i++){
        if(int(num[i]) <= int('9') && int(num[i]) >= int('0'))
        number = (number*10) + (int(num[i]) - int('0'));
    }
    return number*sign;
}

void Polynomial::push_back(int value , int pow){
    term *newX = new term();
    newX->value = value;
    newX->pow = pow;
    this->poly_list.push_back(newX);
}

string Polynomial :: print(){
    string pol = "";    
    for(int i=0 ; i<this->poly_list.size() ; ++i){
        if(this->poly_list[i]->pow!=0){
            pol += to_string(this->poly_list[i]->value)+"x^"+to_string(this->poly_list[i]->pow);
        }
        else{
            pol += to_string(this->poly_list[i]->value);
        }
        if(i == this->poly_list.size()-1){
            break;
        }
        if(this->poly_list[i+1]->value > 0){
            pol+='+';
        }
    }
    return pol;
}

Polynomial Polynomial :: operator+(const Polynomial &obj){
    Polynomial result;
    for(int i=0 ; i<this->poly_list.size() ; ++i){
        bool flag = false;
        for(int j=0 ; j<obj.poly_list.size() ; ++j){
            if(this->poly_list[i]->pow == obj.poly_list[j]->pow){
                result.push_back(this->poly_list[i]->value + obj.poly_list[j]->value , obj.poly_list[j]->pow);
                flag = true;
            }
        }
        if(!flag){
            result.push_back(this->poly_list[i]->value , this->poly_list[i]->pow);
        }
    }
    for(int i=0 ; i<obj.poly_list.size() ; ++i){
        bool flag = false ;
        for(int j=0 ; j<result.poly_list.size() ; ++j){
            if(result.poly_list[j]->pow == obj.poly_list[i]->pow){flag = true;}
        }
        if(!flag){
            result.push_back(obj.poly_list[i]->value , obj.poly_list[i]->pow);
        }
    }
    return result;
}

void Polynomial::clear(){
    for(int i=0 ; i<this->poly_list.size() ; ++i){
        this->poly_list.pop_back();
    }
}

void Polynomial::operator=(const Polynomial &obj){
    this->clear();
    for(int i=0 ; i<obj.poly_list.size() ; ++i){
        this->poly_list.push_back(obj.poly_list[i]);
    }
}

Polynomial Polynomial::operator*(const Polynomial &obj){
    Polynomial result;
    for(int i=0 ; i<this->poly_list.size() ; ++i){
        for(int j=0 ; j<obj.poly_list.size() ; ++j){
            result.push_back(this->poly_list[i]->value*obj.poly_list[j]->value , this->poly_list[i]->pow+obj.poly_list[j]->pow);
        }
    }
    return result;
}

bool Polynomial::operator==(const Polynomial &obj){
    for(int i=0 ; i<this->poly_list.size() ; ++i){
        for(int j=0 ; j<obj.poly_list.size(); ++j){
            if(this->poly_list[i]->pow == obj.poly_list[j]->pow && this->poly_list[i]->value != obj.poly_list[j]->value){
                return false;
            }
        }
    }
    return true;
}