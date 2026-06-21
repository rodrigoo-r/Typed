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
use crate::adt::variable::ScopedStack;
use crate::core::backend::body;

pub fn execute<'a>(
    file: &'a File<'a>,
    trace: &AST<'a>,
    procedure: &Procedure<'a>,
    given_args: RuntimeArguments<'a>
) -> ExecutionResult<'a> {
    // Call native procedures if needed
    if procedure.native.is_some() {
        return procedure.native.as_ref().unwrap()(given_args, trace);
    }

    let stack = ScopedStack::new(None);
    let deref_stack = stack.deref();
    let mut deref_stack = deref_stack.borrow_mut();

    // Add all arguments
    for i in 0..procedure.arguments.len() {
        let name = &procedure.arguments[i].name;
        let arg = given_args.get(i).unwrap();
        deref_stack.push(name.clone(), arg);
    }

    let body = procedure.body.as_ref();
    let body = body.unwrap().borrow();

    body::evaluate(file, procedure, &body, &mut deref_stack)
}