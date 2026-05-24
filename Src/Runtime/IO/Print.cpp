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
// Created by Rodrigo on 5/20/26.
//

#include "Print.h"

#include "ADT/Exception/MismatchedArgCount.h"
#include "Support/Printer/ASTPrinter.h"
#include "Support/Runtime/GetObjValue.h"
#include "Support/Runtime/TypeChecker.h"

using namespace Typed;
using namespace Typed::Runtime;
using namespace Typed::Runtime::IO;

ADT::Runtime::Object &GetArg(
    ADT::List::Object &args,
    Celery::Trait::VeryLarge &idx,
    Celery::Trait::VeryLarge &line,
    Celery::Trait::VeryLarge &col
)
{
    // Make sure there are enough arguments
    if (args.Size() <= idx)
    {
        throw ADT::Exception::MismatchedArgCount(line, col);
    }

    auto &obj = args[idx];
    idx++;
    return obj;
}

void PrintString(ADT::Runtime::Object &obj)
{
    // Special case: Owned strings
    if (obj.type == ADT::Runtime::ObjectType::OwnedString)
    {
        auto &val = Support::Runtime::GetOwnedStrObj(obj);
        Celery::Io::Print(val);
        return;
    }

    auto &val = Support::Runtime::GetStrObj(obj);
    Celery::Io::Print(val);
}

void PrintFloat(ADT::Runtime::Object &obj)
{
    auto &val = Support::Runtime::GetFloatObj(obj);
    Celery::Io::Print(val);
}

void PrintInt(ADT::Runtime::Object &obj)
{
    auto &val = Support::Runtime::GetIntObj(obj);
    Celery::Io::Print(val);
}

void PrintBool(ADT::Runtime::Object &obj)
{
    auto &val = Support::Runtime::GetBoolObj(obj);
    Celery::Io::Print(val);
}

void PrintList(ADT::Runtime::Object &obj);
void PrintDictionary(ADT::Runtime::Object &obj);
void PrintObject(ADT::Runtime::Object &obj);

void PrintDictionary(ADT::Runtime::Object &obj)
{
    auto &val = Support::Runtime::GetDictionaryObj(obj);

    Celery::Io::Print("Dictionary(");

    auto last = val->size() - 1;
    Celery::Trait::VeryLarge i = 0;

    for (auto &pair : *val)
    {
        PrintObject(pair.first);
        Celery::Io::Print(" : ");
        PrintObject(pair.second);

        if (i != last)
        {
            Celery::Io::Print(", ");
        }

        i++;
    }

    Celery::Io::Print(')');
}

void PrintList(ADT::Runtime::Object &obj)
{
    Celery::Io::Print("List(");
    auto &val = Support::Runtime::GetListObj(obj);
    if (val->Empty())
    {
        Celery::Io::Print(')');
        return;
    }

    auto last = val->Size() - 1;
    for (auto i = 0; i < val->Size(); i++)
    {
        auto &el = (*val)[i];
        PrintObject(el);

        if (i != last)
            Celery::Io::Print(", ");
    }

    Celery::Io::Print(')');
}

void PrintObject(ADT::Runtime::Object &obj)
{
    switch (obj.type)
    {
        case ADT::Runtime::ObjectType::String:
        {
            PrintString(obj);
            break;
        }

        case ADT::Runtime::ObjectType::Float:
        {
            PrintFloat(obj);
            break;
        }

        case ADT::Runtime::ObjectType::Integer:
        {
            PrintInt(obj);
            break;
        }

        case ADT::Runtime::ObjectType::Boolean:
        {
            PrintBool(obj);
            break;
        }

        case ADT::Runtime::ObjectType::List:
        {
            PrintList(obj);
            break;
        }

        case ADT::Runtime::ObjectType::Dictionary:
        {
            PrintDictionary(obj);
            break;
        }

        default: break;
    }
}

ADT::Runtime::Object IO::Print(
    ADT::List::Object &args,
    ADT::Lang::AST *trace
)
{
    auto &fmt = Support::Runtime::GetStrObj(args[0]);
    auto line = trace->line;
    auto col = trace->column;
    Celery::Trait::VeryLarge pos = 1;

    // Print the string character by character
    for (auto i = 0; i < fmt.Size(); i++)
    {
        auto c = fmt[i];

        // Match formats
        if (c == '$' && fmt.Size() > i + 1)
        {
            auto f = fmt[i + 1];
            auto can_continue = true;

            switch (f)
            {
                case 'S':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Support::Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::String,
                        arg.type,
                        line,
                        col
                    );

                    can_continue = false;
                    PrintString(arg);
                    break;
                }

                case 'F':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Support::Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::Float,
                        arg.type,
                        line,
                        col
                    );

                    can_continue = false;
                    PrintFloat(arg);
                    break;
                }

                case 'I':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Support::Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::Integer,
                        arg.type,
                        line,
                        col
                    );

                    can_continue = false;
                    PrintInt(arg);
                    break;
                }

                case 'B':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Support::Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::Boolean,
                        arg.type,
                        line,
                        col
                    );

                    can_continue = false;
                    PrintBool(arg);
                    break;
                }

                case 'L':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Support::Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::List,
                        arg.type,
                        line,
                        col
                    );

                    can_continue = false;
                    PrintList(arg);
                    break;
                }

                case 'D':
                {
                    auto &arg = GetArg(args, pos, line, col);
                    Support::Runtime::TypeCheck(
                        ADT::Runtime::ObjectType::Dictionary,
                        arg.type,
                        line,
                        col
                    );

                    can_continue = false;
                    PrintDictionary(arg);
                    break;
                }

                default: break;
            }

            // Skip the next character if we found a format
            if (!can_continue)
            {
                i++;
                continue;
            }
        }

        Celery::Io::Print(c);
    }

    return {};
}
