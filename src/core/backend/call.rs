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
use crate::adt::error::{ErrorKind, ExecutionError};
use crate::adt::lang::{File, RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::variable::NestedStack;
use crate::core::backend::{expression, procedure};

pub fn evaluate<'a>(
    file: &'a File<'a>,
    child: &AST<'a>,
    stack: &NestedStack<'a>
) -> ExecutionResult<'a> {
    let children = child.children.borrow();
    let name = children.get(0).unwrap();
    let name = name.borrow().value.unwrap();

    // Find the procedure
    let procedure = file.procedures.get(name);

    if procedure.is_none() {
        return Err(
            ExecutionError{
                kind: ErrorKind::UndefinedFindProcedure,
                column: child.column,
                line: child.line,
                message: "Could not find procedure"
            }
        );
    }

    let procedure = procedure.unwrap();
    let mut args: RuntimeArguments = RuntimeArguments::new();

    // Add arguments if needed
    if children.len() > 1 {
        let ast_args = children.get(1).unwrap();
        let ast_args = ast_args.borrow();

        for arg in ast_args.children.borrow().iter() {
            let arg = arg.borrow();
            args.push(
                expression::evaluate(file, &arg, stack)?
            );
        }
    }

    // Execute the procedure
    procedure::execute(file, child, procedure, args)
}