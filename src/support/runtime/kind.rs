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
use crate::adt::error::RuntimeError;
use crate::adt::lang::{ASTValue, Kind, AST};
use crate::adt::result::RuntimeResult;
use crate::adt::runtime::{HashableObject, NonHashableObject, Object};

pub fn check_kinds(
    expected: Kind,
    actual: Kind,
    trace: &AST
) -> RuntimeResult<()> {
    if expected != actual {
        return Err(RuntimeError::mismatched_types(trace));
    }

    Ok(())
}

pub fn check_kind<'a>(
    expected: Kind,
    actual: &Object<'a>,
    trace: &AST
) -> RuntimeResult<()> {
    match actual {
        Object::Hashable(HashableObject::Integer(_)) => {
            check_kinds(expected, Kind::Integer, trace)
        }

        Object::Hashable(HashableObject::Float(_)) => {
            check_kinds(expected, Kind::Float, trace)
        }

        Object::Hashable(HashableObject::Boolean(_)) => {
            check_kinds(expected, Kind::Boolean, trace)
        }

        Object::Hashable(HashableObject::String(_)) => {
            check_kinds(expected, Kind::String, trace)
        }

        Object::NonHashable(NonHashableObject::List(_)) => {
            check_kinds(expected, Kind::List, trace)
        }

        Object::NonHashable(NonHashableObject::Dictionary(_)) => {
            check_kinds(expected, Kind::Dictionary, trace)
        }

        Object::Void => {
            Err(RuntimeError::mismatched_types(trace))
        }

        Object::Any(_) => {
            Ok(())
        }
    }
}

pub fn check_obj_kind<'a>(
    expected: &Object<'a>,
    actual: &Object<'a>,
    trace: &AST
) -> RuntimeResult<()> {
    match expected {
        Object::Hashable(HashableObject::Integer(_)) => {
            check_kind(Kind::Integer, actual, trace)
        }

        Object::Hashable(HashableObject::Float(_)) => {
            check_kind(Kind::Float, actual, trace)
        }

        Object::Hashable(HashableObject::Boolean(_)) => {
            check_kind(Kind::Boolean, actual, trace)
        }

        Object::Hashable(HashableObject::String(_)) => {
            check_kind(Kind::String, actual, trace)
        }

        Object::NonHashable(NonHashableObject::List(_)) => {
            check_kind(Kind::List, actual, trace)
        }

        Object::NonHashable(NonHashableObject::Dictionary(_)) => {
            check_kind(Kind::Dictionary, actual, trace)
        }

        Object::Void => {
            Err(RuntimeError::mismatched_types(trace))
        }

        Object::Any(_) => {
            Ok(())
        }
    }
}

pub fn convert_kind<'a>(decl: &AST<'a>)
    -> (ASTValue<'a>, Kind)
{
    let children = decl.children.borrow();
    let name = children.get(0).unwrap().borrow();
    let name = name.value.as_ref().unwrap();

    let kind = children.get(1).unwrap().borrow();
    let kind = kind.children.borrow();
    let kind = kind.get(0).unwrap().borrow();

    (
        name.clone(),
        match kind.rule {
            crate::core::frontend::parser::Rule::Integer =>
                Kind::Integer,
            crate::core::frontend::parser::Rule::Float =>
                Kind::Float,
            crate::core::frontend::parser::Rule::String =>
                Kind::String,
            crate::core::frontend::parser::Rule::Boolean =>
                Kind::Boolean,
            crate::core::frontend::parser::Rule::Dictionary =>
                Kind::Dictionary,
            crate::core::frontend::parser::Rule::List =>
                Kind::List,

            _ => unreachable!(),
        }
    )
}