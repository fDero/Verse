#include "../include/verse.hpp"
#include "../include/procedures.hpp"

bool convert_while_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<WhileLoop>(instr)) return false;
    WhileLoop loop = std::get<WhileLoop>(instr);
    output << prefix <<  ("<WHILE>\n");
    translate_instructions_into_xml({*(loop.condition)},output,"\t" + prefix);
    output << prefix <<  ("\t<CODE>\n");
    translate_instructions_into_xml(loop.code,output,"\t\t" + prefix);
    output << prefix <<  ("\t<CODE>\n");
    output << prefix <<  ("</WHILE>\n");
    return true;
}

bool convert_until_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<UntilLoop>(instr)) return false;
    UntilLoop loop = std::get<UntilLoop>(instr);
    output << prefix <<  ("<UNTIL>\n");
    translate_instructions_into_xml({*(loop.condition)},output,"\t" + prefix);
    output << prefix <<  ("\t<CODE>\n");
    translate_instructions_into_xml(loop.code,output,"\t\t" + prefix);
    output << prefix <<  ("\t<CODE>\n");
    output << prefix <<  ("</UNTIL>\n");
    return true;
}


bool convert_conditional_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Conditional>(instr)) return false;
    Conditional conditional = std::get<Conditional>(instr);
    output << prefix <<  ("<IF>\n");
    translate_instructions_into_xml({*(conditional.condition)},output,"\t" + prefix);
    output << prefix <<  ("\t<THEN>\n");
    translate_instructions_into_xml(conditional.then,output,"\t\t" + prefix);
    output << prefix <<  ("\t</THEN>\n");
    output << prefix <<  ("\t<ELSE>\n");
    translate_instructions_into_xml(conditional.otherwise,output,"\t\t" + prefix);
    output << prefix <<  ("\t</ELSE>\n");
    output << prefix <<  ("</IF>\n");
    return true;
}

bool convert_continue_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Continue>(instr)) return false;
    output << prefix << ("<CONTINUE/>\n");
    return true;
}


bool convert_break_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Break>(instr)) return false;
    output << prefix << ("<BREAK/>\n");
    return true;
}

bool convert_return_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Return>(instr)) return false;
    Return ret = std::get<Return>(instr);
    output << prefix << ("<RETURN>\n");
    translate_instructions_into_xml({*(ret.value)},output,"\t" + prefix);
    output << prefix << ("</RETURN>\n");
    return true;
}

bool convert_defer_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Defer>(instr)) return false;
    Defer defer = std::get<Defer>(instr);
    output << prefix << ("<DEFER>\n");
    translate_instructions_into_xml({*(defer.operation)},output,"\t" + prefix);
    output << prefix << ("</DEFER>\n");
    return true;
}

bool convert_attempt_into_xml(const Instruction& instr, std::fstream& output, const std::string& prefix){
    if (not std::holds_alternative<Attempt>(instr)) return false;
    Attempt attempt = std::get<Attempt>(instr);
    output << prefix << ("<ATTEMPT>\n");
    for (const std::vector<Instruction>& option : attempt.attempts){
        output << prefix << ("\t<TRY>\n");
        translate_instructions_into_xml(option,output,"\t\t" + prefix);
        output << prefix << ("\t</TRY>\n");
    }
    if (!attempt.otherwise.empty()){
        output << prefix << ("\t<DEFAULT>\n");
        translate_instructions_into_xml(attempt.otherwise,output,"\t\t" + prefix);
        output << prefix << ("\t</DEFAULT>\n");
    }
    output << prefix << ("</ATTEMPT>\n");
    return true;
    
}