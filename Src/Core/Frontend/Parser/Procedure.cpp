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

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Procedure()
{
    // Expect the procedure's name
    auto &proc_token = tokens.Curr();
    auto &identifier = tokens.Peek();
    Expect(ADT::Lang::TokenType::Identifier);

    auto node = AllocateBase(identifier, ADT::Lang::ASTType::Procedure);
    root->children.PushBack(node);

    // Case: The procedure has arguments
    auto &peek = tokens.Peek();
    if (peek.type == ADT::Lang::TokenType::With)
    {
        auto args = Allocate(ADT::Lang::ASTType::Arguments);
        node->children.PushBack(args);

        Expect(ADT::Lang::TokenType::Arguments);
        peek = tokens.Peek();

        // Parse arguments
        while (peek.type != ADT::Lang::TokenType::Begin)
        {
            // Expect the argument's structure: <Identifier> As <Type>
            peek = tokens.Peek();
            Expect(ADT::Lang::TokenType::Identifier);
            Expect(ADT::Lang::TokenType::As);

            // Parse the type
            auto type = Type();

            // Build the AST
            auto arg = AllocateBase(peek, ADT::Lang::ASTType::Argument);
            arg->children.PushBack(AllocateBase(peek, ADT::Lang::ASTType::Identifier));
            arg->children.PushBack(type);

            args->children.PushBack(arg);
            peek = tokens.Peek();

            // Make sure there is a comma if there's more arguments
            if (peek.type == ADT::Lang::TokenType::Comma)
            {
                Expect(ADT::Lang::TokenType::Comma);
                peek = tokens.Peek();
            }
        }
    }

    // Parse return types if necessary
    peek = tokens.Peek();
    if (peek.type == ADT::Lang::TokenType::Returns)
    {
        auto type = Allocate(ADT::Lang::ASTType::ReturnType);
        node->children.PushBack(type);
        type->children.PushBack(type);

        peek = tokens.Peek();
    }

    if (peek.type != ADT::Lang::TokenType::Begin)
    {
        throw ADT::Exception::UnexpectedToken(
            peek.line,
            peek.column
        );
    }

    // Consume the Begin token
    tokens.Next();
    peek = tokens.Peek();

    // Now parse the body
    auto body = AllocateBase(peek, ADT::Lang::ASTType::Body);
    node->children.PushBack(body);

    BodyQueue body_queue = {
        {
            body,
            proc_token
        }
    };

    while (peek.type != ADT::Lang::TokenType::EndProcedure)
    {
        peek = tokens.Peek();
        auto &last_el = body_queue.front();

        switch (peek.type)
        {
            case ADT::Lang::TokenType::Declare:
            {
                Declare(last_el.body);
                break;
            }

            case ADT::Lang::TokenType::Return:
            {
                Return(last_el.body);
                break;
            }

            case ADT::Lang::TokenType::If:
            {
                If(last_el.body, body_queue);
                break;
            }

            case ADT::Lang::TokenType::ElseIf:
            {
                ElseIf(last_el.body, body_queue);
                break;
            }

            case ADT::Lang::TokenType::Else:
            {
                Else(last_el.body, body_queue);
                break;
            }

            case ADT::Lang::TokenType::EndIf:
            {
                EndIf(body_queue);
                break;
            }

            case ADT::Lang::TokenType::For:
            {
                For(last_el.body, body_queue);
                break;
            }

            case ADT::Lang::TokenType::EndFor:
            {
                EndFor(body_queue);
                break;
            }

            case ADT::Lang::TokenType::While:
            {
                While(last_el.body, body_queue);
                break;
            }

            case ADT::Lang::TokenType::EndWhile:
            {
                EndWhile(body_queue);
                break;
            }

            default:
            {
                Expression(last_el.body);
                break;
            }
        }

        // Update the peek for the next iteration
        if (tokens.HasNext())
            peek = tokens.Peek();
    }

    // Consume the end procedure token
    tokens.Next();
    body_queue.pop_front();

    // Make sure the body queue is empty at the end
    if (!body_queue.empty())
    {
        auto &trace = body_queue.front();

        throw ADT::Exception::UnexpectedToken(
            trace.match.line,
            trace.match.column
        );
    }
}
