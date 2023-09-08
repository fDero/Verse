#include "../include/verse.hpp"
#include "../include/procedures.hpp"

inline const std::set<std::string> prefixes{"!","-","+","#"};
inline const std::set<std::string> infixies{".","+","-","*","/","%","^","<",">","<=",">=","==","&&","||","^^","!="};

bool parse_prefix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& target){
    if (it == tokens.end() or prefixes.find(it->sourcetext) == prefixes.end()) return false;
    std::vector<std::string> encountered_prefixes;
    std::shared_ptr<Instruction> operand;
    while (it != tokens.end() and prefixes.find(it->sourcetext) != prefixes.end()) { 
        encountered_prefixes.push_back(it->sourcetext);
        std::advance(it,1);
    }
    acquire_terminal(it,tokens,operand); 
    UnaryOperator op {encountered_prefixes.back(), operand};
    encountered_prefixes.pop_back();
    auto reverse_prefixes_iterator = encountered_prefixes.rbegin();
    while (reverse_prefixes_iterator != encountered_prefixes.rend()){
        op = UnaryOperator{*reverse_prefixes_iterator, std::make_shared<Instruction>(op)};
        std::advance(reverse_prefixes_iterator,1);
    }
    target = op;
    return true;
}

int get_precedence(const Instruction& expr){
    if (std::holds_alternative<BinaryOperator>(expr)){
        std::string optext = std::get<BinaryOperator>(expr).text;
        if (optext == "&&" or optext == "||" or optext == "^^") return 1;
        if (optext == "<" or optext == ">" or optext == "==" or optext == "!=" or optext == ">=" or optext == "<=") return 2;
        if (optext == "+" or optext == "-")  return 3;
        if (optext == "*" or optext == "/" or optext == "%")  return 4;
        if (optext == "^")  return 7;
        if (optext == ".")  return 8;
    }
    return (std::holds_alternative<UnaryOperator>(expr))? 6 : 9;
}

void fix_binary_operators_precedence(Instruction& expr){
    if (not std::holds_alternative<BinaryOperator>(expr)) return;
    if (not std::holds_alternative<BinaryOperator>(*(std::get<BinaryOperator>(expr).lx))) return;
    BinaryOperator root = std::get<BinaryOperator>(expr);
    BinaryOperator root_lx = std::get<BinaryOperator>(*(std::get<BinaryOperator>(expr).lx));
    if (get_precedence(root) <= get_precedence(root_lx) or root_lx.wrapped_in_parenthesys) return;
    BinaryOperator new_root_rx {root.text, root_lx.rx, root.rx};
    BinaryOperator new_root {root_lx.text, root_lx.lx, std::make_shared<Instruction>(new_root_rx)};
    fix_expression(*(new_root.rx));
    expr = new_root;
}

void fix_unary_operators_precedence(Instruction& expr){
    if (not std::holds_alternative<BinaryOperator>(expr)) return;
    if (not std::holds_alternative<UnaryOperator>(*(std::get<BinaryOperator>(expr).lx))) return;
    BinaryOperator root = std::get<BinaryOperator>(expr);
    UnaryOperator root_lx = std::get<UnaryOperator>(*(std::get<BinaryOperator>(expr).lx));
    if (get_precedence(root) <= get_precedence(root_lx) or root_lx.wrapped_in_parenthesys) return;
    BinaryOperator new_operand {root.text, root_lx.operand, root.rx};
    UnaryOperator new_root {root_lx.text, std::make_shared<Instruction>(new_operand)};  
    fix_expression(*(new_root.operand));
    expr = new_root;
}

void fix_expression(Instruction& expr){
    fix_binary_operators_precedence(expr);
    fix_unary_operators_precedence(expr);
}

bool parse_infix_operator(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& expr){
    if (it == tokens.end() or infixies.find(it->sourcetext) == infixies.end()) return false;
    std::shared_ptr<Instruction> lx = std::make_shared<Instruction>(expr);
    std::string infix_operator_text = it->sourcetext;
    std::advance(it,1);
    std::shared_ptr<Instruction> rx;
    if (parse_prefix_operator(it,tokens,expr)) rx = std::make_shared<Instruction>(expr);
    else acquire_terminal(it,tokens,rx);
    expr = BinaryOperator{infix_operator_text, lx, rx};
    fix_expression(expr);
    return true;
}

bool parse_assignment(std::vector<Token>::iterator& it, const std::vector<Token>& tokens, Instruction& expr){
    if (it == tokens.end() or it->sourcetext != "=") return false;
    std::shared_ptr<Instruction> lx = std::make_shared<Instruction>(expr);
    std::string infix_operator_text = it->sourcetext;
    std::advance(it,1);
    std::shared_ptr<Instruction> rx;
    acquire_expression(it,tokens,rx);
    expr = Assignment{lx,rx};
    return true;
}

void operator_precedence_lockout(Instruction& expr){
    if (std::holds_alternative<UnaryOperator>(expr)){
        UnaryOperator& op = std::get<UnaryOperator>(expr);
        op.wrapped_in_parenthesys = true;
    }
    if (std::holds_alternative<BinaryOperator>(expr)){
        BinaryOperator& op = std::get<BinaryOperator>(expr);
        op.wrapped_in_parenthesys = true;
    }
}