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