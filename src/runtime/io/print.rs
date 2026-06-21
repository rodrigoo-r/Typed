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
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::Object;
use crate::runtime::strings::format;
use crate::support::runtime::object::{*};

pub fn print<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let res = format::format(args, trace)?;
    let str = get_string(&res, trace)?;
    print!("{}", str);

    Ok(Object::Void)
}