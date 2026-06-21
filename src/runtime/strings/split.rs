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
use crate::adt::lang::{RuntimeArguments, AST};
use crate::adt::result::ExecutionResult;
use crate::adt::runtime::{HashableObject, NonHashableObject, Object, RuntimeList, StringKind};
use crate::support::runtime::object::get_string;

pub fn split<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let origin = args.get(0).unwrap();
    let delim = args.get(1).unwrap();

    let origin = get_string(origin, trace)?;
    let delim = get_string(delim, trace)?;

    let mut result: RuntimeList = RuntimeList::new(RefCell::new(vec![]));
    let mut current = String::new();
    let mut idx: usize = 0;

    while idx < origin.len() {
        let mut is_match = false;

        if idx + delim.len() <= origin.len() {
            for i in 0..delim.len() {
                if origin.as_bytes()[idx + i] != delim.as_bytes()[i] {
                    is_match = false;
                    break;
                }

                is_match = true;
            }
        } else {
            is_match = false;
        }

        if is_match {
            let mut result = result.borrow_mut();

            result.push(
                Object::Hashable(
                    HashableObject::String(
                        StringKind::Dynamic(
                            current.clone()
                        )
                    )
                )
            );
            current.clear();
            idx += delim.len();
        }
    }

    Ok(
        Object::NonHashable(
            NonHashableObject::List(
                result
            )
        )
    )
}