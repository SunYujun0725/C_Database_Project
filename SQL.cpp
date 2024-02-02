#include<iostream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;

int m, n;
map<pair<int, string>, int> tA_i;
map<pair<int, string>, string> tA_s;
string cmd; //整行命令
stringstream cmd_ss;
string cmd_tok; //命令分段
vector<string> pf;//要輸出的種類
stringstream ss;
string column_name;
string optr;
string value_s;
int value;
string cmp_key;
string cmp_pri;
string conj;
set<int> fin_ans;
set<int> tmp_ans;
vector<int> change_ans;
set<int>::iterator it;
vector<int> ans;
bool del[310];

string trash;

void CIN_tA();
void CMD();
void CMD_init(); //pf ans
void SELECT();
void DELETE();
void PF_DEAL(string);
void SEL_WHERE();
void DEL_WHERE();
void CHOOSE();
void LIKE(int);
void AND();
void OR();
void ORDER();
int cmp(int, int);
void ANS_PRINT();

int main(){
    while(cin >> n >> m){
        tA_i.clear();
        tA_s.clear();
        CIN_tA();
        getline(cin, trash);
        CMD();
    }
    return 0;
}

void CIN_tA(){
    for(int i = 0; i < n; i++){
        cin >> tA_i[{i, "ID"}] >> tA_s[{i, "Name"}] >> tA_i[{i, "StudentID"}] >> tA_s[{i, "Class"}] >> tA_s[{i, "Email"}] >> tA_i[{i, "Phone"}];
    }
}

void CMD(){
    for(int i = 0; i < m; i++){
        CMD_init();
        getline(cin, cmd);
        cmd_ss.str("");
        cmd_ss.clear();
        cmd_ss << cmd;
        cmd_ss >> cmd_tok;
        if(cmd_tok == "SELECT"){
            SELECT();
        }
        if(cmd_tok == "DELETE"){
            DELETE();
        }
    }
}

void CMD_init(){
    ans.clear();
    pf.clear();
    fin_ans.clear();
    tmp_ans.clear();
    conj = "";
}

void SELECT(){
    while(cmd_ss >> cmd_tok && cmd_tok != "FROM"){ //輸出格式處理
        PF_DEAL(cmd_tok);
    }
    cmd_ss >> cmd_tok; //table選擇
    if(cmd_tok[cmd_tok.length()-1] == ';'){ //NO WHERE
        for(int i = 0; i < n; i++){
            if(del[i] == false){
                ans.push_back(i);
            }
        }
    }
    else{
        cmd_ss >> cmd_tok; //WHERE
        if(cmd_tok == "WHERE"){
            SEL_WHERE();
        }
        else{
            for(int i = 0; i < n; i++){
                if(del[i] == false){
                    ans.push_back(i);
                }
            }
            ORDER();
        }
    }
    ANS_PRINT();
}

void DELETE(){
    cmd_ss >> cmd_tok; //FROM
    cmd_ss >> cmd_tok; //table
    if(cmd_tok[cmd_tok.length()-1] == ';'){
        for(int i = 0; i < n; i++){
            del[i] = true;
        }
    }
    else{
        cmd_ss >> cmd_tok; //WHERE
        DEL_WHERE();
    }
}

void PF_DEAL(string s){
    if(s == "*"){
        pf.push_back("ID");
        pf.push_back("Name");
        pf.push_back("StudentID");
        pf.push_back("Class");
        pf.push_back("Email");
        pf.push_back("Phone");
    }
    if(s[s.length()-1] == ','){
        s.erase(s.length()-1,1);
    }
    pf.push_back(s);
}

void SEL_WHERE(){
    int order = 0;
    while(cmd_ss >> column_name){
        if(column_name == "ORDER"){
            ORDER();
            return;
        }
        else{
            cmd_ss >> optr;
            cmd_ss >> value_s;
            tmp_ans.clear();
            //cout << column_name << " " << optr << " " << value_s << endl;
            CHOOSE();
            if(conj == "AND"){
                AND();
            }
            else{
                OR();
            }
            if(cmd_ss >> conj){
                if(conj == "ORDER"){
                    order = 1;
                    break;
                }
            }
            else{
                break;
            }
        }
    }
    for(it = fin_ans.begin(); it != fin_ans.end(); it++){
        ans.push_back(*it);
    }
    if(order){
        ORDER();
    }
}

void DEL_WHERE(){
    while(cmd_ss >> column_name && cmd_ss >> optr && cmd_ss >> value_s){
        tmp_ans.clear();
        CHOOSE();
        if(conj == "AND"){
            AND();
        }
        else{
            OR();
        }
        if(cmd_ss >> conj){}
        else{
            break;
        }
    }
    for(it = fin_ans.begin(); it != fin_ans.end(); it++){
        ans.push_back(*it);
    }
    for(int i = 0; i < ans.size(); i++){
        del[ans[i]] = true;
    }
}

void CHOOSE(){
    if(optr == "LIKE"){
        if(value_s[value_s.length()-1] == ';'){
            value_s.erase(value_s.length()-1,1);
        }
        if(value_s[1] == '%' && value_s[value_s.length()-2] == '%'){
            LIKE(2);
        }
        else if(value_s[1] == '%'){
            LIKE(1);
        }
        else if(value_s[value_s.length()-2] == '%'){
            LIKE(3);
        }
        else{
            LIKE(0);
        }
    }
    else{
        ss.str("");
        ss.clear();
        ss << value_s;
        ss >> value;
        for(int i = 0; i < n; i++){
            if(del[i] == false){
                if(optr == ">"){
                    if(tA_i[{i,column_name}] > value){
                        tmp_ans.insert(i);
                    }
                }
                if(optr == ">="){
                    if(tA_i[{i,column_name}] >= value){
                        tmp_ans.insert(i);
                    }
                }
                if(optr == "="){
                    if(tA_i[{i,column_name}] == value){
                        tmp_ans.insert(i);
                    }
                }
                if(optr == "<"){
                    if(tA_i[{i,column_name}] < value){
                        tmp_ans.insert(i);
                    }
                }
                if(optr == "<="){
                    if(tA_i[{i,column_name}] <= value){
                        tmp_ans.insert(i);
                    }
                }
                if(optr == "!="){
                    if(tA_i[{i,column_name}] != value){
                        tmp_ans.insert(i);
                    }
                }
            }
        }
    }
    return;
}

void LIKE(int x){
    value_s.erase(value_s.length()-1,1);
    value_s.erase(0,1);
    if(x == 0){
        for(int i = 0; i < n; i++){
            if(del[i] == false){
                if(tA_s[{i,column_name}] == value_s){
                    tmp_ans.insert(i);
                }
            }
        }
    }
    if(x == 1){
        value_s.erase(0,1);
        for(int i = 0; i < n; i++){
            if(del[i] == false){
                if(tA_s[{i,column_name}].find(value_s) == tA_s[{i,column_name}].length() - value_s.length()){
                    tmp_ans.insert(i);
                }
            }
        }
    }
    if(x == 2){
        value_s.erase(value_s.length()-1,1);
        value_s.erase(0,1);
        for(int i = 0; i < n; i++){
            if(del[i] == false){
                if(tA_s[{i,column_name}].find(value_s) != -1){
                    tmp_ans.insert(i);
                }
            }
        }
    }
    if(x == 3){
        value_s.erase(value_s.length()-1,1);
        for(int i = 0; i < n; i++){
            if(del[i] == false){
                if(tA_s[{i,column_name}].find(value_s) == 0){
                    tmp_ans.insert(i);
                }
            }
        }
    }
}

void AND(){
    change_ans.clear();
    for(it = fin_ans.begin(); it != fin_ans.end(); it++){
        if(fin_ans.count(*it) != tmp_ans.count(*it)){
            change_ans.push_back(*it);
        }
    }
    for(int i = 0; i < change_ans.size(); i++){
        fin_ans.erase(change_ans[i]);
    }
}

void OR(){
    for(it = tmp_ans.begin(); it != tmp_ans.end(); it++){
        fin_ans.insert(*it);
    }
}

void ORDER(){
    cmd_ss >> cmd_tok; //BY
    cmd_ss >> cmp_key;
    cmd_ss >> cmp_pri;
    sort(ans.begin(), ans.end(), cmp);
}

int cmp(int a, int b){
    if(cmp_key == "Name" || cmp_key == "Class" || cmp_key == "Email"){
        if(cmp_pri == "DESC;"){ // big to small
            return tA_s[{a,cmp_key}] > tA_s[{b,cmp_key}];
        }
        else{
            return tA_s[{a,cmp_key}] < tA_s[{b,cmp_key}];
        }
    }
    else{
        if(cmp_pri == "DESC;"){ // big to small
            return tA_i[{a,cmp_key}] > tA_i[{b,cmp_key}];
        }
        else{
            return tA_i[{a,cmp_key}] < tA_i[{b,cmp_key}];
        }
    }
}

void ANS_PRINT(){
    for(int i = 0; i < ans.size(); i++){
        for(int j = 0; j < pf.size(); j++){
            if(tA_i.find({ans[i],pf[j]}) != tA_i.end()){
                cout << tA_i[{ans[i],pf[j]}] << ' ';
            }
            else{
                cout << tA_s[{ans[i],pf[j]}] << ' ';
            }
        }
        cout << endl;
    }
}
