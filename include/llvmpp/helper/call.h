#ifndef LLVMPP_COMPILER_HELPER_CALL_H_
#define LLVMPP_COMPILER_HELPER_CALL_H_

#include <stdexcept>
#include <string>
#include <vector>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

namespace llvmpp
{
    namespace helper
    {
        template<typename... T>
        inline llvm::Value *call(llvm::LLVMContext &context, llvm::Module *module, llvm::IRBuilder<> &irBuilder, llvm::Function *function, T... args)
        {
            return irBuilder.CreateCall(function, std::vector<llvm::Value*>({args...}));
        }

        template<typename... T>
        inline llvm::Value *call(llvm::LLVMContext &context, llvm::Module *module, llvm::IRBuilder<> &irBuilder, const std::string &name, T... args)
        {
            llvm::Function *function = module->getFunction(name);
            if (function == nullptr)
            {
                throw std::runtime_error("Function not found: " + name);
            }

            return helper::call(context, module, irBuilder, function, args...);
        }

        #define CREATE_CALLEE(NAME)                                                                                         \
        template<typename... T>                                                                                             \
        inline llvm::Value *NAME(llvm::LLVMContext &context, llvm::Module *module, llvm::IRBuilder<> &irBuilder, T... args) \
        {                                                                                                                   \
            return helper::call(context, module, irBuilder, #NAME, args...);                                     \
        }
    }
}

#endif /* LLVMPP_COMPILER_HELPER_CALL_H_ */
