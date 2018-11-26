#include "../hpp/Frame.hpp"
#include "../hpp/CpAttributeInterface.hpp"
#include <iostream>

Instance::Instance(ClassLoader * toLoad) {
    
    CpAttributeInterface cpAtAux;
    
    this->name   = cpAtAux.getUTF8(toLoad->getConstPool(),toLoad->getThisClass()-1);
    this->classe = toLoad;   
}

Frame::~Frame() {
    free(this->instructions);
}

Frame::Frame(std::vector<CpInfo*> cp, MethodInfo * methd) {

    CpAttributeInterface cpAtAux;
    
    //std::cout << "Frame::Frame begin" << std::endl;
    this->instructions = (Instruction*)calloc(256,sizeof(Instruction));
    this->instructions->init(this->instructions); // Inicializa as instruções.

    this->pc = 0;
    this->method_reference = methd;
    this->cp_reference = cp;

    for(int i = 0; i < methd->attributes_count; i++) {
        AttributeInfo at = methd->attributes[i];
        if(cpAtAux.getUTF8(cp,at.name_index-1) == "Code") this->method_code = at.code;
    }
    this->local_variables.resize(method_code.max_locals);
    //std::cout << "Frame::Frame end" << std::endl;
}

void Frame::run() {
    //std::cout << "Frame::run begin" << std::endl;

    bool flag = true;

    do {
        uint8_t opCode = this->method_code.code[pc];
        this->instructions[opCode].func(this);
        //std::cout << this->instructions[opCode].name << std::endl;
        if(this->instructions[opCode].name == "return") flag = false;    
    } while(flag);
    

    //std::cout << "Frame::run end" << std::endl;
}

void Frame::cpPrint() {
    CpAttributeInterface aux;
    auto a = this->cp_reference;
    for(int i = 0; i < a.size(); i++) {
        std::cout << i << " : " << aux.getUTF8(a,i) << std::endl;
        getchar();
    }
    getchar();
}