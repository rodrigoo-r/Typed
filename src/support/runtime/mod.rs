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
use crate::adt::lang::{ChildAST, AST};
use crate::adt::result::RuntimeResult;
use crate::adt::runtime::{Dictionary, Float, HashableObject, List, NonHashableObject, Object, StringKind};
use crate::adt::runtime::Object::NonHashable;

macro_rules! unwrap_obj {
    ($obj:expr, $pattern:pat => $result:expr, $trace:expr) => {{
        if let $pattern = $obj {
            Ok($result)
        } else {
            let err = ExecutionError{
                kind: ErrorKind::MismatchedTypes,
                message: "mismatched types",
                line: $trace.line,
                column: $trace.column,
            };

            Err(err)
        }
    }}
}

pub fn get_string<'obj, 'data>(
    obj: &'obj Object<'data>,
    trace: &AST<'data>,
) -> RuntimeResult<'data, &'obj str>
{
    let kind = unwrap_obj!(
        obj,
        Object::Hashable(HashableObject::String(s)) => s,
        trace
    )?;

    match kind {
        StringKind::Static(s) => Ok(s),
        StringKind::Dynamic(s) => Ok(s.as_str()),
    }
}

pub fn get_integer<'source>(
    obj: &'source Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<'source, &'source isize>
{
    unwrap_obj!(
        obj,
        Object::Hashable(HashableObject::Integer(s)) => s,
        trace
    )
}

pub fn get_float<'source>(
    obj: &'source Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<'source, &'source Float>
{
    unwrap_obj!(
        obj,
        Object::Hashable(HashableObject::Float(s)) => s,
        trace
    )
}

pub fn get_boolean<'source>(
    obj: &'source Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<'source, &'source bool>
{
    unwrap_obj!(
        obj,
        Object::Hashable(HashableObject::Boolean(s)) => s,
        trace
    )
}

pub fn get_list<'source>(
    obj: Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<'source, List<'source>>
{
    unwrap_obj!(
        obj,
        NonHashable(NonHashableObject::List(s)) => s,
        trace
    )
}

pub fn get_dictionary<'source>(
    obj: &'source Object<'source>,
    trace: &AST<'source>
) -> RuntimeResult<'source, &'source Dictionary<'source>>
{
    unwrap_obj!(
        obj,
        NonHashable(NonHashableObject::Dictionary(s)) => s,
        trace
    )
}