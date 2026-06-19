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

use crate::adt::lang::{File, ProcedureArguments, RuntimeArguments};
use crate::adt::result::ExecutionResult;

pub fn execute<'a>(
    file: &'a File<'a>,
    empty_args: ProcedureArguments<'a>
) -> ExecutionResult<'a> {
    // Get the main procedure
    let main = file.procedures.get("Main").unwrap();

    procedure::execute(
        main.body.as_ref().unwrap(),
        main,
        &empty_args
    )
}