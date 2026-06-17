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
#include "Parser.h"
#include "Support/Equality/TokenType.h"
#include "Support/Stream/Extract.h"
#include "Support/Stream/SafeNext.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

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

void Machine::Expression(
    TreePtr body,
    TokenStreamView &input
)
{
    ExprQueue queue;
    queue.emplace_back(input, body);

    while (!queue.empty())
    {
        auto [expr, parent] = queue.back();
        queue.pop_back();

        if (expr.empty()) continue;

        // Create the expression AST
        auto ast = AllocateBase(
            Support::Stream::SafePeek(expr),
            ADT::Lang::ASTType::Expression
        );
        parent->children.push_back(ast);

        // Get the candidate to determine the expression type
        auto &candidate = Support::Stream::SafeNext(expr);
        TreePtr result = nullptr;

        switch (candidate.type)
        {
            case ADT::Lang::TokenType::Call:
            {
                result = Call(expr, queue);
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

            case ADT::Lang::TokenType::Identifier:
            {
                result = AllocateBase(candidate, ADT::Lang::ASTType::Identifier);
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

        // Parse boolean expression if any
        if (
            expr.HasNext() &&
            (
                expr.Peek().type == ADT::Lang::TokenType::Less ||
                expr.Peek().type == ADT::Lang::TokenType::Greater ||
                expr.Peek().type == ADT::Lang::TokenType::LessEqual ||
                expr.Peek().type == ADT::Lang::TokenType::GreaterEqual ||
                expr.Peek().type == ADT::Lang::TokenType::Equal
            )
        )
        {
            result = BooleanOperation(expr, result, queue);
        }

        // Parse boolean delimiters
        if (
            expr.HasNext() &&
            (
                expr.Peek().type == ADT::Lang::TokenType::And ||
                expr.Peek().type == ADT::Lang::TokenType::Or
            )
        )
        {
            result = BooleanOperator(expr, result, queue);
        }

        // Make sure there's no remaining tokens
        if (expr.HasNext())
        {
            throw ADT::Exception::UnexpectedToken(
                expr.Peek().line,
                expr.Peek().column
            );
        }

        ast->children.push_back(result);
    }
}