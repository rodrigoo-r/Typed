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
use crate::adt::lang::{ChildAST, Procedure, ProcedureArguments};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::adt::variable::ScopedStack;
use crate::core::frontend;

pub fn execute<'a>(
    trace: &'a ChildAST<'a>,
    procedure: &Procedure<'a>,
    given_args: ProcedureArguments<'a>
) -> ExecutionResult<'a> {
    let mut stack = ScopedStack::new(None);

    // Add all arguments
    for (name, arg) in given_args.iter() {
        stack.push(name, arg);
    }

    // Call native procedures if needed
    if procedure.native.is_some() {
        return procedure.native.as_ref().unwrap()(&given_args, trace);
    }

    let body = procedure.body.as_ref();
    let body = body.unwrap().borrow();
    let children = body.children.borrow();

    for statement in children.iter() {
        let statement = statement.borrow();

        match statement.rule {
            frontend::parser::Rule::Expression => {

            }

            frontend::parser::Rule::For => {

            }

            frontend::parser::Rule::While => {

            }

            frontend::parser::Rule::Declare => {

            }

            frontend::parser::Rule::Condition_Group => {

            }

            _ => {}
        }
    }

    Ok(Object::Void)
}