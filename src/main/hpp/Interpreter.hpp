/** @file Interpreter.hpp
 *  @brief Declarações das funções e atributos do Interpretador para interpretar o que foi lido do .class.
 *  @bug No known bugs.
 */
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ClassLoader.hpp"
#include "Frame.hpp"
#include "Instance.hpp"
#include <cstring>
#include <map>
#include <string>

using namespace std;

class Interpreter {

  public:
    std::string current_path_folder;
    std::stack<Frame*> frame_stack;
    
    void execute(ClassLoader*);
    void loadVariables(Instance*);
    ClassLoader * getClassInfo(std::string);
    MethodInfo  * mainFinder(ClassLoader*);
    Instance    * loadInMemo(ClassLoader*);
    Operand     * createType(std::string);
};

#endif