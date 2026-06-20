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
use crate::adt::error::ExecutionError;
use crate::adt::lang::{File, RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::variable::ScopedStack;
use crate::core::backend::{expression, procedure};
use crate::support::runtime::kind::check_kind;

pub fn evaluate<'a>(
    file: &'a File<'a>,
    child: &AST<'a>,
    stack: &mut RefMut<ScopedStack<'a>>
) -> ExecutionResult<'a> {
    let children = child.children.borrow();
    let name = children.get(0).unwrap();
    let name = name.borrow().value.unwrap();

    // Find the procedure
    let procedure = file.procedures.get(name);

    if procedure.is_none() {
        return Err(ExecutionError::undefined_procedure(child));
    }

    let procedure = procedure.unwrap();
    let mut args: RuntimeArguments = RuntimeArguments::new();

    // Add arguments if needed
    if children.len() > 1 {
        let ast_args = children.get(1).unwrap();
        let ast_args = ast_args.borrow();
        let children = ast_args.children.borrow();

        // Handle mismatched arguments
        if
            (
                procedure.arguments.len() != children.len() &&
                !procedure.variadic
            ) ||
            (
                procedure.variadic &&
                procedure.arguments.len() > children.len()
            )
        {
            return Err(ExecutionError::mismatched_argument_count(child));
        }

        for i in 0..procedure.arguments.len() {
            let arg = children.get(i).unwrap();
            let arg = arg.borrow();
            let expected = &procedure.arguments[i];
            let kind = expected.kind.clone();
            let arg = expression::evaluate(file, &arg, stack)?;

            check_kind(kind, &arg, child)?;

            args.push(arg);
        }

        // Handle variadic arguments
        if procedure.variadic {
            for i in procedure.arguments.len()..children.len() {
                let arg = children.get(i).unwrap();
                let arg = arg.borrow();
                let arg = expression::evaluate(file, &arg, stack)?;

                args.push(arg);
            }
        }
    }

    // Execute the procedure
    procedure::execute(file, child, procedure, args)
}