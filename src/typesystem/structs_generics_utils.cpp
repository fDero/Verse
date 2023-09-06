#include "../include/verse.hpp"
#include "../include/procedures.hpp"

TemplateGenerics get_template_generics(const StructDefinition& struct_definition){
    TemplateGenerics template_generics { struct_definition.generics };
    if (struct_definition.parent_scope != nullptr) {
        template_generics.splice(template_generics.end(), get_template_generics(*struct_definition.parent_scope));
    }
    return template_generics;
}

InstanciatedGenerics get_instanciated_generics(const TypeSignature& type){
    if (std::holds_alternative<BaseType>(type)){
        InstanciatedGenerics instanciated_generics { std::get<BaseType>(type).generics };
        return instanciated_generics;
    }
    else if (std::holds_alternative<NestedType>(type)){
        InstanciatedGenerics instanciated_generics = get_instanciated_generics(*std::get<NestedType>(type).right);
        const TypeSignature& lx = *std::get<NestedType>(type).left;
        instanciated_generics.push_back(std::get<BaseType>(lx).generics);
        return instanciated_generics;
    }
    throw InternalCompilerError {
        "attempt to get instanciated generics from a typesignature wich is neither a base-type nor a nested-type"
    };
}

GenericsLookupTable get_generics_lookup_table(const TemplateGenerics& template_generics, const InstanciatedGenerics& instanciated_generics){
    GenericsLookupTable generics_lookup_table;
    auto template_generics_iterator = template_generics.begin();
    auto instanciated_generics_iterator = instanciated_generics.begin();
    if (template_generics.size() != instanciated_generics.size()) throw InternalCompilerError { 
        "different number of template-generics and instanciated-generics" 
    };
    for (int t = 0; t < template_generics.size(); t++){
        for (int i = 0; i < template_generics_iterator->size(); i++){
            if (template_generics_iterator->size() != instanciated_generics_iterator->size()) {
                throw InternalCompilerError { "different number of template-generics and instanciated-generics" };
            }
            std::string template_generic_name = type_to_string((*template_generics_iterator)[i]);
            generics_lookup_table[template_generic_name] = (*instanciated_generics_iterator)[i];
        }
        ++template_generics_iterator;
        ++instanciated_generics_iterator;
    }
    return generics_lookup_table;
}