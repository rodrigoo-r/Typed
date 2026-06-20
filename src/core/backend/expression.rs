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
use crate::core::frontend::parser;
use crate::adt::lang::{File, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::adt::variable::ScopedStack;
use crate::core::backend::{boolean_literal, call, float_literal, identifier, integer_literal};
use crate::core::backend::string_literal;

pub fn evaluate<'a, 'stack>(
    file: &'a File<'a>,
    expr: &AST<'a>,
    stack: &'stack ScopedStack<'a, 'stack>
) -> ExecutionResult<'a> {
    let children = expr.children.borrow();
    let child = children.get(0).unwrap();
    let child = child.borrow();

    match child.rule {
        parser::Rule::Expression => {
            return evaluate(file, &child, stack);
        }

        parser::Rule::Identifier => {
            return identifier::evaluate(&child, stack);
        }

        parser::Rule::Call => {
            return call::evaluate(file, &child, stack);
        }

        parser::Rule::Add => {
            
        }

        parser::Rule::Subtract => {

        }

        parser::Rule::Multiply => {

        }

        parser::Rule::Divide => {

        }
        
        // Literals
        parser::Rule::String_Literal => {
            return string_literal::evaluate(&child);
        }

        parser::Rule::Float_Literal => {
            return float_literal::evaluate(&child);
        }

        parser::Rule::Integer_Literal => {
            return integer_literal::evaluate(&child);
        }

        parser::Rule::True_Literal |
        parser::Rule::False_Literal
        => {
            return boolean_literal::evaluate(&child);
        }

        _ => {}
    }

    Ok(Object::Void)
}