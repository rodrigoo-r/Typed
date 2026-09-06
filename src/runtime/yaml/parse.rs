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
use std::collections::HashMap;
use crate::adt::error::RuntimeError;
use crate::adt::lang::{RuntimeArguments, AST, ASTValue};
use crate::adt::result::ExecutionTupleResult;
use crate::adt::runtime::{Dictionary, Float, HashableObject, List, NonHashableObject, Object, RuntimeDictionary, RuntimeList};
use crate::support::runtime::execution::{continue_execution};
use crate::support::runtime::object::{get_string};

fn create_object<'a>(value: noyalib::Value) -> Option<Object<'a>> {
    match value {
        noyalib::Value::String(s) => Some(Object::Hashable(
            HashableObject::String(
                ASTValue::Owned(s)
            )
        )),

        noyalib::Value::Number(i) => Some(Object::Hashable(
            if i.is_i64() {
                HashableObject::Integer(i.as_i64().unwrap() as isize)
            } else if i.is_u64() {
                HashableObject::Integer(i.as_u64().unwrap() as isize)
            } else {
                HashableObject::Float(Float::from(i.as_f64() as f32))
            }
        )),

        noyalib::Value::Bool(b) => Some(Object::Hashable(
            HashableObject::Boolean(b)
        )),

        noyalib::Value::Sequence(l) => {
            let mut list = List::new();

            for item in l {
                if let Some(item_obj) = create_object(item) {
                    list.push(item_obj);
                }
            }

            Some(Object::NonHashable(
                NonHashableObject::List(
                    RuntimeList::new(
                        RefCell::new(list)
                    )
                )
            ))
        },

        noyalib::Value::Mapping(m) => {
            let mut dict = Dictionary::new();

            for (key, value) in m {
                if let Some(value_obj) = create_object(value) {
                    dict.insert(
                        HashableObject::String(
                            ASTValue::Owned(key)
                        ),
                        value_obj
                    );
                }
            }

            Some(Object::NonHashable(
                NonHashableObject::Dictionary(
                    RuntimeDictionary::new(
                        RefCell::new(dict)
                    )
                )
            ))
        },

        _ => None
    }
}

fn create_dict<'a>(input: HashMap<String, noyalib::Value>) -> Dictionary<'a> {
    let mut res = Dictionary::new();

    for (key, value) in input {
        let obj = create_object(value).unwrap_or(
            Object::Hashable(
                HashableObject::String(
                    ASTValue::Owned(String::from("null"))
                )
            )
        );
        
        res.insert(
            HashableObject::String(
                ASTValue::Owned(key)
            ),
            obj
        );
    }

    res
}

pub fn parse<'a>(
    args: RuntimeArguments<'a>,
    trace: &AST<'a>
)
    -> ExecutionTupleResult<'a>
{
    let str_obj = args.get(0).unwrap();

    let str = get_string(str_obj, trace)?;
    let result = noyalib::from_str(&str);

    if result.is_err() {
        return Err(
            RuntimeError::unparsable_file(trace)
        );
    }

    let result: HashMap<String, noyalib::Value> = result.unwrap();
    let dict = create_dict(result);

    continue_execution(
        Object::NonHashable(
            NonHashableObject::Dictionary(
                RuntimeDictionary::new(
                    RefCell::new(dict)
                )
            )
        )
    )
}