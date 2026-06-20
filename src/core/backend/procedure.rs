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
use std::ops::Deref;
use crate::adt::lang::{File, Procedure, RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::adt::variable::ScopedStack;
use crate::core::backend::expression;
use crate::core::backend::declare;
use crate::core::frontend;

pub fn execute<'a>(
    file: &'a File<'a>,
    trace: &AST<'a>,
    procedure: &Procedure<'a>,
    given_args: RuntimeArguments<'a>
) -> ExecutionResult<'a> {
    let stack = ScopedStack::new(None);
    let deref_stack = stack.deref();
    let mut deref_stack = deref_stack.borrow_mut();

    // Add all arguments
    for i in 0..procedure.arguments.len() {
        let name = procedure.arguments[i].name;
        let arg = given_args.get(i).unwrap();
        deref_stack.push(name, arg);
    }

    // Call native procedures if needed
    if procedure.native.is_some() {
        return procedure.native.as_ref().unwrap()(given_args, trace);
    }

    let body = procedure.body.as_ref();
    let body = body.unwrap().borrow();
    let children = body.children.borrow();

    for statement in children.iter() {
        let statement = statement.borrow();

        match statement.rule {
            frontend::parser::Rule::Expression => {
                expression::evaluate(file, &statement, &stack)?;
            }

            frontend::parser::Rule::For => {

            }

            frontend::parser::Rule::While => {

            }

            frontend::parser::Rule::Declare => {
                declare::evaluate(file, &statement, &stack)?;
            }

            frontend::parser::Rule::Condition_Group => {

            }

            _ => {}
        }
    }

    Ok(Object::Void)
}