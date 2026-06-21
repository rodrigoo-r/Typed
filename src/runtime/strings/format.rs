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
use memchr::memchr;
use crate::adt::error::RuntimeError;
use crate::adt::lang::{ASTValue, Kind, RuntimeArguments, AST};
use crate::adt::result::{ExecutionResult, RuntimeResult};
use crate::adt::runtime::{HashableObject, NonHashableObject, Object};
use crate::support::runtime::kind::{check_kind, check_kinds};
use crate::support::runtime::object::get_string;

fn format_hashable_object(
    obj: &HashableObject,
    expected: Kind,
    trace: &AST,
    result: &mut String
) -> RuntimeResult<()> {
    match obj {
        HashableObject::String(
            ASTValue::Borrowed(s)
        ) => {
            check_kinds(expected, Kind::String, trace)?;
            result.push_str(s);
        }

        HashableObject::String(
            ASTValue::Owned(s)
        ) => {
            check_kinds(expected, Kind::String, trace)?;
            result.push_str(s);
        }

        HashableObject::Float(f) => {
            check_kinds(expected, Kind::Float, trace)?;
            let f = f.to_string();
            result.push_str(&f);
        }

        HashableObject::Integer(i) => {
            check_kinds(expected, Kind::Integer, trace)?;
            let i = i.to_string();
            result.push_str(&i);
        }

        HashableObject::Boolean(b) => {
            check_kinds(expected, Kind::Boolean, trace)?;
            let b = b.to_string();
            result.push_str(&b);
        }
    }

    Ok(())
}

pub fn format_obj<'a>(
    obj: &Object,
    expected: Kind,
    trace: &AST,
    result: &mut String
) -> RuntimeResult<()> {
    check_kind(expected.clone(), obj, trace)?;

    match obj {
        Object::Hashable(hashable) => {
            format_hashable_object(
                hashable,
                expected.clone(),
                trace,
                result
            )?;
        }

        Object::NonHashable(
            NonHashableObject::List(list)
        ) => {
            result.push_str("List(");

            let list = list.borrow();
            for (idx, item) in list.iter().enumerate() {
                if idx != 0 {
                    result.push_str(", ");
                }

                format_obj(item, expected.clone(), trace, result)?;
            }

            result.push_str(")");
        }

        Object::NonHashable(
            NonHashableObject::Dictionary(dict)
        ) => {
            result.push_str("Dictionary(");
            let mut idx: usize = 1;
            let dict = dict.borrow();
            let size = dict.len();

            for (key, value) in dict.iter() {
                if idx != size {
                    result.push_str(", ");
                }

                format_hashable_object(key, expected.clone(), trace, result)?;
                result.push_str(": ");
                format_obj(value, expected.clone(), trace, result)?;

                idx += 1;
            }

            result.push_str(")");
        }

        Object::Void => {
            result.push_str("Void");
        }
    }

    Ok(())
}

pub fn format<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionResult<'a>
{
    let fmt = args.get(0);
    let fmt = fmt.unwrap();
    let mut fmt = get_string(&fmt, trace)?;
    let mut result = String::new();

    // Format the string
    let mut last_arg_idx: usize = 1;
    while let Some(pos) = memchr(b'$', fmt.as_bytes()) {
        // Get the slice of the string before the $
        let slice = &fmt[0..pos];
        let fmt_type = &fmt[pos + 1 .. pos + 2];
        let fmt_type = fmt_type.as_bytes();
        let fmt_type = fmt_type.first().unwrap();
        fmt = &fmt[(pos + 2)..];

        // Write the slice to the result
        result.push_str(slice);

        // Get the argument
        let arg = args.get(last_arg_idx);
        last_arg_idx += 1;

        if arg.is_none() {
            return Err(RuntimeError::mismatched_argument_count(trace));
        }

        let arg = arg.unwrap();
        match *fmt_type {
            b'S' => {
                format_obj(&arg, Kind::String, trace, &mut result)?;
            },

            b'I' => {
                format_obj(&arg, Kind::Integer, trace, &mut result)?;
            },

            b'B' => {
                format_obj(&arg, Kind::Boolean, trace, &mut result)?;
            },

            b'F' => {
                format_obj(&arg, Kind::Float, trace, &mut result)?;
            },

            _ => {
                // Just add the character
                result.push(*fmt_type as char);
            }
        }
    }

    // Add the last slice
    result.push_str(&fmt);

    Ok(
        Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(result)
            )
        )
    )
}