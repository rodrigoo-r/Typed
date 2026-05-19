/*
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #                           Typed                     # *
 * #                   A text formatting DSL             # *
 * #                                                     # *
 * #-----------------------------------------------------# *
 * #                                                     # *
 * #         Created by Rodrigo R. & Contributors        # *
 * #         Released under the Apache License 2.0       # *
 * #            Check LICENSE.MD for more info           # *
 * #                                                     # *
 * #-----------------------------------------------------# *
*/

//
// Created by Rodrigo on 5/18/26.
//

#include "ADT/Exception/UnexpectedToken.h"
#include "ADT/Stream/External.h"
#include "Parser.h"
#include "Support/Equality/TokenType.h"
#include "Support/Stream/Extract.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

struct ExpressionQueueElement
{
    Machine::TokenStreamView tokens;
    Machine::TreePtr parent;
};

using Queue =
    Celery::Array::Vector<ExpressionQueueElement>;

void Machine::Expression(TreePtr parent)
{
    auto expr = Support::Stream::Extract<
        ADT::Lang::Token,
        Support::Equality::TokenType
    >(
        tokens,
        ADT::Lang::TokenType::Semicolon
    );

    Expression(parent, expr);
}

void Machine::Expression(TreePtr body, const TokenStreamView& input)
{
    Queue queue;
    queue.EmplaceBack(input, body);

    while (!queue.Empty())
    {
        auto [expr, parent] = queue.Back();
        queue.PopBack();

        // Create the expression AST
        auto ast = AllocateBase(expr.Peek(), ADT::Lang::ASTType::Expression);
        parent->children.PushBack(ast);

        // Get the candidate to determine the expression type
        auto &candidate = expr.Next();
        TreePtr result = nullptr;

        switch (candidate.type)
        {
            case ADT::Lang::TokenType::Call:
            {
                result = Call(expr);
                break;
            }

            case ADT::Lang::TokenType::CallMethod:
            {
                result = CallMethod(expr);
                break;
            }

            case ADT::Lang::TokenType::Add:
            {
                result = Add(expr);
                break;
            }

            case ADT::Lang::TokenType::Sub:
            {
                result = Sub(expr);
                break;
            }

            case ADT::Lang::TokenType::Mul:
            {
                result = Mul(expr);
                break;
            }

            case ADT::Lang::TokenType::Div:
            {
                result = Div(expr);
                break;
            }

            case ADT::Lang::TokenType::StringLiteral:
            {
                result = AllocateBase(candidate, ADT::Lang::ASTType::StringLiteral);
                break;
            }

            case ADT::Lang::TokenType::NumberLiteral:
            {
                result = AllocateBase(candidate, ADT::Lang::ASTType::NumberLiteral);
                break;
            }

            case ADT::Lang::TokenType::FloatLiteral:
            {
                result = AllocateBase(candidate, ADT::Lang::ASTType::FloatLiteral);
                break;
            }

            case ADT::Lang::TokenType::FalseLiteral:
            {
                result = AllocateBase(candidate, ADT::Lang::ASTType::FalseLiteral);
                break;
            }

            case ADT::Lang::TokenType::TrueLiteral:
            {
                result = AllocateBase(candidate, ADT::Lang::ASTType::TrueLiteral);
                break;
            }

            default:
            {
                throw ADT::Exception::UnexpectedToken(
                    candidate.line,
                    candidate.column
                );
            }
        }
    }
}