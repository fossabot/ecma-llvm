#ifndef ECMA_AST_STMT_CTRL_CASE_H_
#define ECMA_AST_STMT_CTRL_CASE_H_

#include "ecma/utils/element.h"
#include <memory>
#include <vector>
#include "ecma/ast/tools/visitor.h"

namespace ecma
{
    namespace ast
    {
        namespace stmt
        {
            namespace ctrl
            {
                class Case: public utils::Element
                {
                    public:
                        inline Case(CaseKey *key)
                            : utils::Element()
                            , m_key(key)
                        {
                        }
                        virtual inline ~Case()
                        {
                        }

                        inline const CaseKey *key() const
                        {
                            return m_key.get();
                        }
                        inline Case &key(CaseKey *key)
                        {
                            m_key.reset(key);
                            return *this;
                        }
                        inline CaseKey *take_key()
                        {
                            return m_key.release();
                        }

                        inline const std::vector<std::unique_ptr<Statement>> &actions() const
                        {
                            return m_actions;
                        }
                        inline std::vector<std::unique_ptr<Statement>> &actions()
                        {
                            return m_actions;
                        }

                        virtual inline void accept(tools::Visitor &visitor) const
                        {
                            visitor.visit(*this);
                        }

                    private:
                        std::unique_ptr<CaseKey> m_key;
                        std::vector<std::unique_ptr<Statement>> m_actions;
                };
            }
        }
    }
}

#endif /* ECMA_AST_STMT_CTRL_CASE_H_ */