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
use crate::adt::lang::{File, Procedure, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::Object;
use crate::adt::variable::ScopedStack;
use crate::core::backend::{condition_group, declare, expression, for_loop, return_smt, while_loop};
use crate::execute_or_return;
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::execution::stop_execution;

pub fn evaluate<'a>(
    file: &'a File<'a>,
    procedure: &Procedure<'a>,
    body: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionTupleResult<'a> {
    let children = body.children.borrow();

    for statement in children.iter() {
        let statement = statement.borrow();

        match statement.rule {
            parser::Rule::Expression => {
                expression::evaluate(file, &statement, stack)?;
            }

            parser::Rule::For => {
                execute_or_return!(for_loop::evaluate(file, procedure, &statement, stack));
            }

            parser::Rule::While => {
                execute_or_return!(while_loop::evaluate(file, procedure, &statement, stack));
            }

            parser::Rule::Declare => {
                declare::evaluate(file, &statement, stack)?;
            }

            parser::Rule::Return => {
                return return_smt::evaluate(file, procedure, &statement, stack);
            }

            parser::Rule::Condition_Group => {
                execute_or_return!(condition_group::evaluate(file, procedure, &statement, stack));
            }

            _ => {}
        }
    }

    continue_execution(Object::Void)
}