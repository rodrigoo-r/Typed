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
mod procedure;
mod expression;
mod identifier;
mod string_literal;
mod float_literal;
mod integer_literal;
mod boolean_literal;
mod call;
mod arithmetic;
mod declare;
mod for_loop;
mod body;
mod while_loop;
mod return_smt;
mod condition_group;
mod boolean;

use std::ops::Deref;
use crate::adt::lang::File;
use crate::adt::result::ExecutionTupleResult;
use crate::adt::error::RuntimeError;

pub fn execute<'a>(
    file: &'a File<'a>
) -> ExecutionTupleResult<'a> {
    // Get the main procedure
    let main = file.procedures.get("Main");
    if main.is_none() {
        return Err(
            RuntimeError{
                message: "Could not find procedure 'Main'",
                line: 0,
                column: 0
            }
        );
    }
    
    let main = main.unwrap();
    let trace = main.body.as_ref().unwrap();
    let trace = trace.borrow();

    procedure::execute(
        file,
        trace.deref(),
        main,
        Vec::new()
    )
}