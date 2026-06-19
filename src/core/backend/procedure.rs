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
use crate::adt::lang::Procedure;
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::adt::variable::ScopedStack;

pub fn execute<'a>(
    procedure: &Procedure<'a>,
    given_args: Vec<(&'a str, Object<'a>)>
) -> ExecutionResult<'a> {
    let mut stack = ScopedStack::new(None);

    // Add all arguments
    for (name, arg) in given_args.iter() {
        stack.push(name, arg);
    }

    let body = procedure.body.borrow();
    let children = body.children.borrow();

    for statement in children.iter() {
        let statement = statement.borrow();

        match statement.rule {

            _ => {}
        }
    }
    
    Ok(Object::Void)
}