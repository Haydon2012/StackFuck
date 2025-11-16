#include <bits/stdc++.h>
#include <fstream>

/***
*           ____    _                    _      _____                  _            
*          / ___|  | |_    __ _    ___  | | __ |  ___|  _   _    ___  | | __        
*   _____  \___ \  | __|  / _` |  / __| | |/ / | |_    | | | |  / __| | |/ /  _____ 
*  |_____|  ___) | | |_  | (_| | | (__  |   <  |  _|   | |_| | | (__  |   <  |_____|
*          |____/   \__|  \__,_|  \___| |_|\_\ |_|      \__,_|  \___| |_|\_\        
*                                                                                   
*  -version null- 
*/

class StackfuckVm {
private:
    std::stack<int> st1, st2;
    int reg[4];
    std::unordered_map<std::string, size_t> lmap;
    std::string src;
    size_t pc;
    void skip() {
        while (pc < src.length() && (src[pc] == ' ' || src[pc] == '\n' || src[pc] == '\t' || src[pc] == EOF)) {
            pc++;
        }
    }
    std::string readParameter(bool isLabel = false) {
        skip();
        if (pc >= src.length()) return "";
        std::string param;
        if (isLabel) {
            while (pc < src.length() && !isspace(src[pc]) && 
                   src[pc] != '#' && src[pc] != ';') {
                if (src[pc] == '\'' || src[pc] == '+' || src[pc] == '-' ||
                    src[pc] == '*' || src[pc] == '/' || src[pc] == '%' ||
                    src[pc] == '&' || src[pc] == '^' || src[pc] == '|' ||
                    src[pc] == '.' || src[pc] == ',' || src[pc] == '~' ||
                    src[pc] == '$' || src[pc] == '?' || src[pc] == ']' ||
                    src[pc] == '[' || src[pc] == ':' || src[pc] == '@' ||
                    src[pc] == ';' || src[pc] == '#' || src[pc] == '=' ||
                    src[pc] == '<' || src[pc] == '>') {
                    break;
                }
                param += src[pc++];
            }
        } else if (src[pc] == 'n') param = "000", pc += 3;
		 else {
            for (int i = 0; i < 3 && pc < src.length(); i++) {
                if (isspace(src[pc])) break;
                param += src[pc++];
            }
        }
        return param;
    }
    void skipComment() {
        while (pc < src.length() && src[pc] != '#') {
            pc++;
        }
        if (pc < src.length()) pc++; 
    }
    int parseNumber(const std::string& param) {
        if (param.length() != 3) return 0;
        return (param[0]-'0')*100 + (param[1]-'0')*10 + (param[2]-'0');
    }
public:
	StackfuckVm(const std::string& code) : src(code), pc(0) {
        for (int i = 0; i < 4; i++) reg[i] = 0;
        size_t pos = 0;
        while (pos < src.length()) {
            if (src[pos] == ' ' || src[pos] == '\n') {
                pos++;
                continue;
            }
            if (src[pos] == '#') { 
                while (pos < src.length() && src[pos] != '#') {
                    pos++;
                }
                if (pos < src.length()) pos++;
                continue;
            }
            
            char op = src[pos++];
            
            if (op == ':') { 
                std::string lb;
                while (pos < src.length() && !isspace(src[pos]) && 
                       src[pos] != '#' && src[pos] != ';') {
                    if (src[pos] == '\'' || src[pos] == '+' || src[pos] == '-' ||
                        src[pos] == '*' || src[pos] == '/' || src[pos] == '%' ||
                        src[pos] == '&' || src[pos] == '^' || src[pos] == '|' ||
                        src[pos] == '.' || src[pos] == ',' || src[pos] == '~' ||
                        src[pos] == '$' || src[pos] == '?' || src[pos] == ']' ||
                        src[pos] == '[' || src[pos] == ':' || src[pos] == '@' ||
                        src[pos] == ';' || src[pos] == '#' || src[pos] == '=' ||
                        src[pos] == '<' || src[pos] == '>') {
                        break;
                    }
                    lb += src[pos++];
                }
                lmap[lb] = pos;
            } else {
                std::string param;
                if (op == '?' || op == ']' || op == '[' || op == '@') {
                    while (pos < src.length() && !isspace(src[pos]) && 
                           src[pos] != '#' && src[pos] != ';') {
                        if (src[pos] == '\'' || src[pos] == '+' || src[pos] == '-' ||
                            src[pos] == '*' || src[pos] == '/' || src[pos] == '%' ||
                            src[pos] == '&' || src[pos] == '^' || src[pos] == '|' ||
                            src[pos] == '.' || src[pos] == ',' || src[pos] == '~' ||
                            src[pos] == '$' || src[pos] == '?' || src[pos] == ']' ||
                            src[pos] == '[' || src[pos] == ':' || src[pos] == '@' ||
                            src[pos] == ';' || src[pos] == '#' || src[pos] == '=' ||
                            src[pos] == '<' || src[pos] == '>') {
                            break;
                        }
                        param += src[pos++];
                    }
                } else {
                    for (int i = 0; i < 3 && pos < src.length(); i++) {
                        if (isspace(src[pos])) break;
                        param += src[pos++];
                    }
                }
            }
        }
    }
    
    void run() {
        pc = 0;
        while (pc < src.length()) {
            skip();
            if (pc >= src.length()) break;
            
            char op = src[pc++];
            
            if (op == '#') {
                skipComment();
                continue;
            }
            
            if (op == ';') {
                break;
            }
            
            std::string param;
            bool isLabelParam = false;
            if (op == '?' || op == ']' || op == '[' || op == '@') {
                param = readParameter(true);
                isLabelParam = true;
            } else if (op == ':') {
                std::string lb;
                while (pc < src.length() && !isspace(src[pc]) && 
                       src[pc] != '#' && src[pc] != ';') {
                    if (src[pc] == '\'' || src[pc] == '+' || src[pc] == '-' ||
                        src[pc] == '*' || src[pc] == '/' || src[pc] == '%' ||
                        src[pc] == '&' || src[pc] == '^' || src[pc] == '|' ||
                        src[pc] == '.' || src[pc] == ',' || src[pc] == '~' ||
                        src[pc] == '$' || src[pc] == '?' || src[pc] == ']' ||
                        src[pc] == '[' || src[pc] == ':' || src[pc] == '@' ||
                        src[pc] == ';' || src[pc] == '#' || src[pc] == '=' ||
                        src[pc] == '<' || src[pc] == '>') {
                        break;
                    }
                    lb += src[pc++];
                }
                continue;
            } else {
                param = readParameter(false);
            }
            
            switch (op) {
                case '\'': {
                    int num = parseNumber(param);
                    st1.push(num);
                    break;
                }
                
                case '+': {
                    if (st1.size() < 2) {
                        std::cerr << "Error: Stack underflow for +" << std::endl;
                        return;
                    }
                    int b = st1.top(); st1.pop();
                    int a = st1.top(); st1.pop();
                    st1.push(a + b);
                    break;
                }
                
                case '-': {
                    if (st1.size() < 2) {
                        std::cerr << "Error: Stack underflow for -" << std::endl;
                        return;
                    }
                    int b = st1.top(); st1.pop();
                    int a = st1.top(); st1.pop();
                    st1.push(a - b);
                    break;
                }
                
                case '*': {
                    if (st1.size() < 2) {
                        std::cerr << "Error: Stack underflow for *" << std::endl;
                        return;
                    }
                    int b = st1.top(); st1.pop();
                    int a = st1.top(); st1.pop();
                    st1.push(a * b);
                    break;
                }
                
                case '/': {
                    if (st1.size() < 2) {
                        std::cerr << "Error: Stack underflow for /" << std::endl;
                        return;
                    }
                    int b = st1.top(); st1.pop();
                    int a = st1.top(); st1.pop();
                    if (b == 0) {
                        std::cerr << "Error: Division by zero" << std::endl;
                        return;
                    }
                    st1.push(a / b);
                    break;
                }
                
                case '%': {
                    if (st1.size() < 2) {
                        std::cerr << "Error: Stack underflow for %" << std::endl;
                        return;
                    }
                    int b = st1.top(); st1.pop();
                    int a = st1.top(); st1.pop();
                    if (b == 0) {
                        std::cerr << "Error: Division by zero" << std::endl;
                        return;
                    }
                    st1.push(a % b);
                    break;
                }
                
                case '&': {
                    if (st1.size() < 2) {
                        std::cerr << "Error: Stack underflow for &" << std::endl;
                        return;
                    }
                    int b = st1.top(); st1.pop();
                    int a = st1.top(); st1.pop();
                    st1.push(a & b);
                    break;
                }
                
                case '|': {
                    if (st1.size() < 2) {
                        std::cerr << "Error: Stack underflow for |" << std::endl;
                        return;
                    }
                    int b = st1.top(); st1.pop();
                    int a = st1.top(); st1.pop();
                    st1.push(a | b);
                    break;
                }
                
                case '^': {
                    if (st1.size() < 2) {
                        std::cerr << "Error: Stack underflow for ^" << std::endl;
                        return;
                    }
                    int b = st1.top(); st1.pop();
                    int a = st1.top(); st1.pop();
                    st1.push(a ^ b);
                    break;
                }
                
                case '<': { 
                    if (st1.empty()) {
                        std::cerr << "Error: Stack empty for <" << std::endl;
                        return;
                    }
                    int bits = parseNumber(param);
                    int value = st1.top(); st1.pop();
                    st1.push(value << bits);
                    break;
                }
                
                case '>': { 
                    if (st1.empty()) {
                        std::cerr << "Error: Stack empty for >" << std::endl;
                        return;
                    }
                    int bits = parseNumber(param);
                    int value = st1.top(); st1.pop();
                    st1.push(value >> bits);
                    break;
                }
                
                case '.': { //out
                    if (st1.empty()) {
                        std::cerr << "Error: Stack empty for ." << std::endl;
                        return;
                    }
                    int out = st1.top();
                    if (param == "001") {
                        std::cout << out;
                    } else { 
                        std::cout << static_cast<char>(out);
                    }
                    break;
                }
                
                case ',': { // in
                    if (param == "001") {
                        int num;
                        std::cin >> num;
                        st1.push(num);
                    } else {
                        char input;
                        std::cin.get(input);
                        st1.push(static_cast<int>(input));
                    }
                    break;
                }
                
                case '~': { // ->reg
                    if (st1.empty()) {
                        std::cerr << "Error: Stack empty for ~" << std::endl;
                        return;
                    }
                    int regIndex = parseNumber(param);
                    if (regIndex < 0 || regIndex >= 4) {
                        std::cerr << "Error: Invalid register index" << std::endl;
                        return;
                    }
                    reg[regIndex] = st1.top();
                    st1.pop();
                    break;
                }
                
                case '$': { // <-reg
                    int regIndex = parseNumber(param);
                    if (regIndex < 0 || regIndex >= 4) {
                        std::cerr << "Error: Invalid register index" << std::endl;
                        return;
                    }
                    st1.push(reg[regIndex]);
                    break;
                }
                
                case '?': { // =0
                    if (st1.empty()) {
                        std::cerr << "Error: Stack empty for ?" << std::endl;
                        return;
                    }
                    if (st1.top() == 0) {
                        if (lmap.find(param) != lmap.end()) {
                            pc = lmap[param];
                        } else {
                        	std::cerr << "Error: No such label named that" << std::endl;
						}
                    }
                    st1.pop();
                    break;
                }
                
                case '[': { // >0
                    if (st1.empty()) {
                        std::cerr << "Error: Stack empty for [" << std::endl;
                        return;
                    }
                    if (st1.top() > 0) {
                        if (lmap.find(param) != lmap.end()) {
                            pc = lmap[param];
                        } else {
                        	std::cerr << "Error: No such label named that" << std::endl;
						}
                    }
                    st1.pop();
                    break;
                }
                
                case ']': { // <0
                    if (st1.empty()) {
                        std::cerr << "Error: Stack empty for ]" << std::endl;
                        return;
                    }
                    if (st1.top() < 0) {
                        if (lmap.find(param) != lmap.end()) {
                            pc = lmap[param];
                        } else {
                        	std::cerr << "Error: No such label" << std::endl;
						}
                    }
                    st1.pop();
                    break;
                }
                
                case '@': { // alw
                    if (lmap.find(param) != lmap.end()) {
                        pc = lmap[param];
                    } else {
                        std::cerr << "Error: No such label named that" << std::endl;
					}
                    break;
                }
                
                case '=': { // pop
                    int stackNum = parseNumber(param);
                    if (stackNum == 1 && !st1.empty()) {
                        st1.pop();
                    } else if (stackNum == 2 && !st2.empty()) {
                        st2.pop();
                    }
                    break;
                }
                
                case '{': { // debug
                	std::cout << "\n========DEBUG=========\n";
                    for(int i = 0; i < 8; i++)	std::cout << reg[i] <<" ";
                    if(st1.empty())	std::cout << "Empty ";
                    else	std::cout << st1.top() << " ";
                    if(st2.empty())	std::cout << "Empty ";
                    else	std::cout << st2.top() << " ";
                    std::cout << "\n======================\n";
                    break;
                }
                
                default:
                    std::cerr << "Error: Unknown operator '" << op << "' at " << pc << std::endl;
                    return;
            }
        }
    }
};
int main() {
//'100'010*nul~003'000~000'001~001:loop$000$003-nul]continue;nul:continue$000.001'032.000$000$001+nul~002$001~000$002~001@loop
	int md = 0;
	std::cout << "          ____    _                    _      _____                  _            \n";
	std::cout << "         / ___|  | |_    __ _    ___  | | __ |  ___|  _   _    ___  | | __        \n";
	std::cout << "  _____  \\___ \\  | __|  / _` |  / __| | |/ / | |_    | | | |  / __| | |/ /  _____ \n";
	std::cout << " |_____|  ___) | | |_  | (_| | | (__  |   <  |  _|   | |_| | | (__  |   <  |_____|\n";
	std::cout << "         |____/   \\__|  \\__,_|  \\___| |_|\\_\\ |_|      \\__,_|  \\___| |_|\\_\\        \n\n";
	std::cout << "(Console version null)\n";
	std::cout << "and actually it's a completely mess though\n\n\n";
    std::string prog;
    std::fstream file;
    while(1) {
    	std::string prom;
    	std::cout << ">>> ";
    	getline(std::cin, prom);
    	if ((prom[0] == '\'' || prom[0] == '+' || prom[0] == '-' ||
            prom[0] == '*' || prom[0] == '/' || prom[0] == '%' ||
            prom[0] == '&' || prom[0] == '^' || prom[0] == '|' ||
            prom[0] == '.' || prom[0] == ',' || prom[0] == '~' ||
            prom[0] == '$' || prom[0] == '?' || prom[0] == ']' ||
            prom[0] == '[' || prom[0] == ':' || prom[0] == '@' ||
            prom[0] == ';' || prom[0] == '#' || prom[0] == '=' ||
            prom[0] == '<' || prom[0] == '>')) {
            prog += prom;
        } else if (prom.substr(0, 6) == "_save ") {
        	file.open(prom.substr(6, prom.size() - 6) + ".sf", std::ios::out);
        	file << prog;
        	file.close();
		} else if (prom.substr(0, 6) == "_open ") {
        	file.open(prom.substr(6, prom.size() - 6) + ".sf", std::ios::in);
        	if (!file) {
		        std::cerr << "Error : No such file" << std::endl;
		    } else {
		    	file >> prog;
        		std::cout << "\n" << prog << "\n\n";
			} 
        	file.close();
		} else if (prom.substr(0, 4) == "_clr") {
        	prog = "";
		} else if (prom.substr(0, 4) == "_run") {
        	std::cout << "Initializing...\n";
        	StackfuckVm vm(prog);
        	std::cout << "Running...\n\n-Execution Results-\n";
        	vm.run();
        	std::cout << "\n====================\n";
		} else {
			std::cerr << "Error : Unexpected operator\n";
		}
	}
    return 0;
}
