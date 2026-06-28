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
use std::cmp::max;
use std::fmt::Write;
use crate::adt::error::RuntimeError;
use crate::adt::lang::{ASTValue, Kind, RuntimeArguments, AST};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{HashableObject, Object};
use crate::runtime::strings::format::format_obj;
use crate::support::runtime::execution::continue_execution;
use crate::support::runtime::object::{get_list, get_string};

pub fn join<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let list = args.get(0).unwrap();
    let delim = args.get(1).unwrap();

    let delim = get_string(delim, trace)?;
    let list = get_list(list, trace)?;
    let list = list.borrow();
    let size = max(list.len(), 1) - 1;
    
    let mut result = String::new();
    
    for (i, item) in list.iter().enumerate() {
        format_obj(
            item,
            Kind::Any,
            trace,
            &mut result
        )?;
        
        if i != size {
            let res = result.write_str(delim);
            
            if res.is_err() {
                return Err(
                    RuntimeError::could_not_write(trace)
                )
            }
        }
    }

    continue_execution(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(result)
            )
        )
    )
}