#include <bits/stdc++.h>
using namespace std;

#define CHECK_SPLIT(n) \
    vec.clear(); \
    Check(line); \
    StringSplit(line,',',vec); \
    for(int i = 0; i < vec.size(); i++){ n }
#define HIT_BAD_AT(reason) \
    { cerr<<"syntax error"<<reason<<endl; \
    exit(3); }

#define HIT_BAD_TRAP \
    { cerr<<"syntax error"<<endl; \
    exit(3); }

#define VB(n) if(verbose){ n }
#define DIGIT(n) to_string(abs(n)).length()

void StringSplit(const string& str, const char split, vector<string>& res)
{
	if (str == "")	return;
	string strs = str + split;
	size_t pos = strs.find(split);
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}
template<typename T>
int vFind(vector<T>& vec, T val){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == val) return i;
    }
    return -1;
}

class QuMachine{
  public:
    fstream f;
    string content;
    map<string, int> states;
    vector<char> input_symbols;
    vector<char> type_symbols;
    vector<string> finish_states;
    string StartState;
    int type_num;

    struct rule{
        string old_symbols;
        string new_symbols;
        string directions;
        string new_state;
    };
    vector<rule> *state_rules;

    struct paper{
        int index;
        bool positive;
        string content;
    };
    vector<paper> types;

    void Check(string& line){
        if(line.length() >= 7 && line.substr(2, 4) == " = {" && line.back() == '}'){
            line.erase(line.begin(),line.begin() + 6);
            line.pop_back();
        }
        else HIT_BAD_TRAP
    }
    QuMachine(){}
    QuMachine(string filename){
        ifstream fs(filename);
        if(!fs){
            cerr<<"no such file!"<<endl;
            exit(0);
        }
        int linenum = 0;
        for(string line; getline(fs, line); linenum++){
            if(line.find(';') != line.npos) line.erase(line.find(';'));
            while(!line.empty()&&isspace(line.back())) line.pop_back();
            if(line.empty()) continue;            

            if(line[0] == '#'){
                vector<string> vec;
                switch(line[1]){
                    case 'Q':
                        CHECK_SPLIT(states.insert(make_pair(vec[i], i));)
                        state_rules = new vector<rule>[vec.size()];
                        break;
                    case 'S':
                        CHECK_SPLIT(
                            if(vec[i].length() != 1) HIT_BAD_TRAP
                            else input_symbols.push_back(vec[i][0]);)
                        break;
                    case 'G':
                        CHECK_SPLIT(
                            if(vec[i].length() != 1) HIT_BAD_TRAP
                            else type_symbols.push_back(vec[i][0]);)
                        break;
                    case 'F':
                        CHECK_SPLIT(
                            if(states.find(vec[i]) == states.end()) HIT_BAD_TRAP
                            else finish_states.push_back(vec[i]);)
                        break;
                    case 'B':
                        if(line!="#B = _") HIT_BAD_AT("B")
                        break;
                    case 'q':
                        if(line.find("#q0 = ") != line.npos){
                            line.erase(line.begin(),line.begin()+6);
                            if(states.find(line) != states.end()) StartState = line;
                            else HIT_BAD_AT("q0")
                        }else HIT_BAD_AT("q0")
                        break;
                    case 'N':
                        if(sscanf(line.data(),"#N = %d",&type_num) != 1) HIT_BAD_AT(" fail in type number") 
                        for(int i = 0; i < type_num; i++){
                            paper tmp1,tmp2;
                            tmp1.index = tmp2.index = i;
                            tmp1.positive = true;
                            tmp2.positive = false;
                            if(i != 0){
                                tmp1.content = "_";
                            }
                            types.push_back(tmp1);
                            types.push_back(tmp2);
                        }
                        break;                        
                    default:
                        HIT_BAD_TRAP
                        break;                  
                }
            }
            else{
                vector<string> vec;
                StringSplit(line, ' ', vec);
                if(states.find(vec[0])==states.end() || states.find(vec[4])==states.end()) 
                    HIT_BAD_AT(line + ": cannot find state")
                if(vec.size() != 5 || vec[1].size()!=type_num || vec[2].size()!=type_num)
                    HIT_BAD_AT(line + ": size of rules error")
                bool flag = true;
                vector<char> dir;
                dir.push_back('l');
                dir.push_back('r');
                dir.push_back('*');
                rule tmp;
                tmp.new_state = states[vec[4]];
                for(int i = 0; i < type_num; i++){
                    if(vFind(type_symbols,vec[1][i]) == -1 && vec[1][i]!= '*') HIT_BAD_AT(line+" unknown symbols")
                    if(vFind(type_symbols,vec[2][i]) == -1 && vec[2][i]!= '*') HIT_BAD_AT(line+" unknown symbols")
                }
                tmp.old_symbols = vec[1];
                tmp.new_symbols = vec[2];
                tmp.directions = vec[3];
                tmp.new_state = vec[4];
                state_rules[states[vec[0]]].push_back(tmp);
            }
        }
    }
    void PrintRule(){
        for(auto it = states.begin();it != states.end(); it++){
            cout<<"state: "<<it->first<<endl;
            for(auto rule : state_rules[it->second]){
                cout<<rule.old_symbols<<" "<<rule.new_symbols<<" "<<rule.directions<<" "<<rule.new_state<<endl;
            }
        }
    }
    //st:状态名  curr:当前纸带上的符号  返回值：对应规则数组的下标 -1表示没有匹配
    int match(string& st, string& curr){
        if(state_rules[states[st]].empty()) return -1;
        int res = 0;
        string tmp;
        tmp.append(curr);
        for(auto rule : state_rules[states[st]]){
            bool flag = true;
            for(int i = 0; i < curr.length(); i++){
                if(rule.old_symbols[i] == '*' && curr[i] != '_') continue;
                else{
                    if(rule.old_symbols[i] == curr[i]) continue;
                    else{
                        flag = false;
                        break;
                    }
                }
            }
            if(flag) return res;
            res++;
        }
        return -1; 
    }
    void PrintIndex(int i, int* pin){
        cout<< "Index" << left << setw(1 + DIGIT(type_num)) << i << ": ";
        int max_pos, min_pos;
        int tmp1 = types[2*i].content.length() - 1;
        int tmp2 = types[2*i+1].content.length() - 1;
        if(pin[i] >= 0){
            while(tmp1 > 0 && tmp1 > pin[i] && types[2*i].content[tmp1] == '_') tmp1--;
            max_pos = tmp1;
            while(tmp2 > -1 && types[2*i+1].content[tmp2] == '_') tmp2--;
            if(tmp2 != -1) min_pos = -tmp2 - 1;
            else{
                int tt = 0;
                while(tt < tmp1 && types[2*i].content[tt] == '_') tt++;
                min_pos = tt;
            }
            for(int x = min_pos; x <= max_pos; x++) cout<<abs(x)<<" ";
        }else{
            while(tmp2 > 0 && tmp2 > -pin[i] - 1 && types[2*i+1].content[tmp2] == '_') tmp2--;
            min_pos = -tmp2 - 1;
            while(tmp1 > -1 && types[2*i].content[tmp1] == '_') tmp1--;
            if(tmp1 != -1) max_pos = tmp1;
            else{
                int tt = 0;
                while(tt < tmp2 && types[2*i+1].content[tt] == '_' && tt < -pin[i]-1) tt++;
                max_pos = -tt - 1;
            }
            for(int x = min_pos; x <= max_pos; x++) cout<<abs(x)<<" ";
        }
        
        cout<< endl <<"Tape" << left << setw(2 + DIGIT(type_num)) << i << ": ";
        for(int x = min_pos; x <= max_pos; x++){
            if(x < 0){
                if(x<=-10)cout<<types[2*i+1].content[-x-1]<<"  ";
                else cout<<types[2*i+1].content[-x-1]<<" ";                
            } 
            else{
                if(x>=10) cout<<types[2*i].content[x]<<"  ";
                else  cout<<types[2*i].content[x]<<" ";
            }
        }
        cout<< endl << "Head" << left << setw(2 + DIGIT(type_num)) << i << ": ";
        int space_num = pin[i] - min_pos;
        string total = "";
        for(int j = min_pos; j < pin[i]; j++){
            if(j <= -10 ||j >= 10) total += "   ";
            else total += "  ";
        }
        total += "^";
        cout<<total<<endl;
    }
   
   
    void PrintQu(int step, string& state, int* pin, string acc){
        cout << left << setw(6 + DIGIT(type_num)) << "Step" << ": " << step << endl;
        cout << left << setw(6 + DIGIT(type_num)) << "State" << ": " << state << endl;
        cout << left << setw(6 + DIGIT(type_num)) << "Acc" << ": " << acc << endl;
        for(int i = 0; i < type_num; i++){
            PrintIndex(i, pin);
        }
        cout << "---------------------------------------------" << endl;
    }
    
    void GetResult(){
        string ans = "";
        int tmp1 = types[0].content.length() - 1;
        int tmp2 = types[1].content.length() - 1;
        while(tmp1 > -1 && types[0].content[tmp1] == '_') tmp1--;
        while(tmp2 > -1 && types[1].content[tmp2] == '_') tmp2--;
        if(tmp1 == -1 && tmp2 == -1) cout<<endl;
        else if(tmp1 == -1){
            int tt = 0;
            while(tt < tmp2 && types[1].content[tt] == '_') tt++;
            for(int i = tmp2; i >= tt; i--) cout<<types[1].content[i];
        }
        else if(tmp2 == -1){
            int tt = 0;
            while(tt < tmp1 && types[0].content[tt] == '_') tt++;
            for(int i = tt; i <= tmp1; i++) cout<<types[0].content[i];
        }
        else{
            for(int i = tmp2; i >= 0; i--) cout<<types[1].content[i];
            for(int i = 0; i <= tmp1; i++) cout<<types[0].content[i];
        }
        cout<<endl;
    }
    
    bool turing(bool verbose){
        bool result = false;
        int *pin = new int[type_num];
        for(int i = 0; i < type_num; i++) pin[i] = 0;

        string curr_state = StartState;
        int step = 0;

        VB(PrintQu(0, StartState, pin, "No");)

        while(1){
            string curr_type = "";
            for(int i = 0; i < type_num; i++){
                if(pin[i] >= 0){
                    curr_type += types[i*2].content[pin[i]];
                }else{
                    int tmp = pin[i] * (-1) - 1;
                    curr_type += types[i*2+1].content[tmp];
                }   
            }

            int index = match(curr_state, curr_type);
            if(index == -1) break;
            rule curr_rule = state_rules[states[curr_state]][index];
            for(int i = 0; i < type_num; i++){
                if(curr_rule.new_symbols[i] != '*'){
                    if(pin[i] < 0){
                        int tmp = pin[i] * (-1) - 1;
                        types[i*2+1].content[tmp] = curr_rule.new_symbols[i];
                    }else{
                        types[i*2].content[pin[i]] = curr_rule.new_symbols[i];
                    } 
                }
                if(curr_rule.directions[i] != '*'){
                    if(curr_rule.directions[i] == 'l') pin[i]--;
                    else pin[i]++;
                }           
            }
            curr_state = curr_rule.new_state;
            if(vFind(finish_states, curr_state) != -1) result = true;
            
            for(int i = 0; i < type_num; i++){
                if(pin[i] >= 0){
                    if(types[i*2].content.length() == pin[i]) types[i*2].content.append("_");
                }else{
                    int tmp = pin[i] * (-1) - 1;
                    if(types[i*2+1].content.length() == tmp) types[i*2+1].content.append("_");
                }   
            }
            step++;
            string acc = "No";
            if(result) acc = "Yes"; 
            VB(PrintQu(step, curr_state, pin, acc);)
        }
        return result;
    }

    void DoTuring(string input, bool verbose){
        if(input.empty()) types[0].content.append("_");
        for(int i = 0; i < input.length(); i++)
            if(vFind(input_symbols, input[i]) == -1){
                if(verbose){
                    cout<<"Input: "<<input<<endl<<"==================== ERR ===================="<<endl;
                    cout<<"error: Symbol \""<< input[i] <<"\" in input is not defined in the set of input symbols"<<endl;
                    cout<<"Input: "<<input<<endl;
                    string heno = "       ";
                    for(int j = 0; j < i; j++) heno.append(" ");
                    cout<<heno<<"^"<<endl;
                    cout<<"==================== END ===================="<<endl;
                    exit(3);
                }else{
                    cerr<<"illegal input string"<<endl;
                    exit(3);
                }
            }
        types[0].content.append(input);

        VB(cout<<"Input: "<<input<<endl<<"==================== RUN ===================="<<endl;)

        bool res = turing(verbose);

        if(!verbose){
            if(res) cout<<"(ACCEPTED)";
            else cout<<"(UNACCEPTED)";
            GetResult();
        }else{
            if(res) cout<<"ACCEPTED"<<endl;
            else cout<<"UNACCEPTED"<<endl;
            cout<<"Result: ";
            GetResult();
            cout<<"==================== END ===================="<<endl;
        }       
    }
};
int main(int argc, char *argv[])
{
    if(argc < 3 || argc > 4){
      cerr<<"bad command"<<endl;
      exit(3);
    }
    else if(argc == 3){
        QuMachine Qu = QuMachine(argv[1]);
        string input = argv[2];
        Qu.DoTuring(input, false);
    }
    else if(argc == 4){
        if(argv[1] != "-v"s && argv[1] != "--verbose"s){
            cout<<argv[1]<<endl;
            cerr<<"bad command"<<endl;
            exit(3);
        }
        else{
            QuMachine Qu = QuMachine(argv[2]);
            Qu.DoTuring(argv[3], true);
        }
    }
    return 0;
}