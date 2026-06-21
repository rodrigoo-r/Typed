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
use std::cell::RefCell;
use std::fs;
use crate::adt::error::RuntimeError;
use crate::adt::lang::{ASTValue, RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, List, NonHashableObject, Object, RuntimeList};
use crate::support::runtime::object::get_string;

pub fn scan_directory<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let path = args.get(0).unwrap();
    let path = get_string(path, trace)?;

    let res = fs::read_dir(path);
    if res.is_err() {
        return Err(
            RuntimeError::could_not_read(trace)
        );
    }
    
    let res = res.unwrap();
    let mut result = List::new();

    for item in res {
        if item.is_err() {
            return Err(
                RuntimeError::could_not_read(trace)
            )
        }

        let item = item.unwrap();

        let path = item.path();
        let path = path.to_str().unwrap();

        result.push(
            Object::Hashable(
                HashableObject::String(
                    ASTValue::Owned(
                        path.to_string()
                    )
                )
            )
        );
    }

    Ok(
        Object::NonHashable(
            NonHashableObject::List(
                RuntimeList::new(
                    RefCell::new(result)
                )
            )
        )
    )
}