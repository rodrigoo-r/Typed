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
use std::cell::RefMut;
use crate::core::frontend::parser;
use crate::adt::lang::{File, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::adt::variable::ScopedStack;
use crate::core::backend::{declare, expression, for_loop};
use crate::execute_or_return;

pub fn evaluate<'a>(
    file: &'a File<'a>,
    body: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionResult<'a> {
    let children = body.children.borrow();

    for statement in children.iter() {
        let statement = statement.borrow();

        match statement.rule {
            parser::Rule::Expression => {
                expression::evaluate(file, &statement, stack)?;
            }

            parser::Rule::For => {
                execute_or_return!(for_loop::evaluate(file, &statement, stack));
            }

            parser::Rule::While => {

            }

            parser::Rule::Declare => {
                declare::evaluate(file, &statement, stack)?;
            }

            parser::Rule::Condition_Group => {

            }

            _ => {}
        }
    }

    Ok(Object::Void)
}