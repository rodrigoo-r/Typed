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
#include "Support/Stream/SafeNext.h"
#include "Support/Stream/SafePeek.h"

using namespace Typed;
using namespace Typed::Core;
using namespace Typed::Core::Frontend;
using namespace Typed::Core::Frontend::Parser;

void Machine::Procedure()
{
    // Expect the procedure's name
    auto &proc_token = tokens.Curr();
    auto &identifier = Support::Stream::SafePeek(tokens);
    Expect(ADT::Lang::TokenType::Identifier);

    auto node = AllocateBase(identifier, ADT::Lang::ASTType::Procedure);
    root->children.PushBack(node);

    // Case: The procedure has arguments
    auto peek = Support::Stream::SafePeek(tokens);
    if (peek.type == ADT::Lang::TokenType::With)
    {
        auto args = Allocate(ADT::Lang::ASTType::Arguments);
        node->children.PushBack(args);

        Expect(ADT::Lang::TokenType::Arguments);
        peek = Support::Stream::SafePeek(tokens);

        // Parse arguments
        while (peek.type != ADT::Lang::TokenType::Begin)
        {
            // Expect the argument's structure: <Identifier> As <Type>
            peek = Support::Stream::SafePeek(tokens);
            Expect(ADT::Lang::TokenType::Identifier);
            Expect(ADT::Lang::TokenType::As);

            // Parse the type
            auto type = Type();

            // Build the AST
            auto arg = AllocateBase(peek, ADT::Lang::ASTType::Argument);
            arg->children.PushBack(AllocateBase(peek, ADT::Lang::ASTType::Identifier));
            arg->children.PushBack(type);

            args->children.PushBack(arg);
            peek = Support::Stream::SafePeek(tokens);

            // Make sure there is a comma if there's more arguments
            if (peek.type == ADT::Lang::TokenType::Comma)
            {
                Expect(ADT::Lang::TokenType::Comma);
                peek = Support::Stream::SafePeek(tokens);
            }
        }
    }

    // Parse return types if necessary
    peek = Support::Stream::SafePeek(tokens);
    if (peek.type == ADT::Lang::TokenType::Returns)
    {
        auto type = Allocate(ADT::Lang::ASTType::ReturnType);
        node->children.PushBack(type);
        type->children.PushBack(type);
    }

    Expect(ADT::Lang::TokenType::Begin);
    peek = Support::Stream::SafePeek(tokens);

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
        peek = Support::Stream::SafePeek(tokens);
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

            case ADT::Lang::TokenType::For:
            {
                For(last_el.body, body_queue);
                break;
            }

            case ADT::Lang::TokenType::EndWhile:
            case ADT::Lang::TokenType::EndIf:
            case ADT::Lang::TokenType::EndFor:
            {
                End(peek.type, body_queue);
                break;
            }

            case ADT::Lang::TokenType::While:
            {
                While(last_el.body, body_queue);
                break;
            }

            default:
            {
                Expression(last_el.body);
                break;
            }
        }

        // Update the peek for the next iteration
        peek = Support::Stream::SafePeek(tokens);
    }

    // Consume the end procedure token
    Support::Stream::SafeNext(tokens);
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
