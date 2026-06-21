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
pub mod access;
pub mod add;
pub mod size;
pub mod pop;
pub mod set;
pub mod join;

use crate::adt::lang::{ASTValue, Argument, Kind, Procedure};
use crate::adt::runtime::PackageDictionary;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();

    dict.insert(
        "List_Access",
        Procedure{
            variadic: false,
            arguments: vec![
                Argument{
                    kind: Kind::List,
                    name: ASTValue::Borrowed("list")
                }
            ],
            ret: Some(Kind::Any),
            body: None,
            native: Some(access::access)
        }
    );

    dict.insert(
        "List_Add",
        Procedure{
            variadic: false,
            arguments: vec![
                Argument{
                    kind: Kind::List,
                    name: ASTValue::Borrowed("list")
                },
                Argument{
                    kind: Kind::Any,
                    name: ASTValue::Borrowed("el")
                }
            ],
            ret: None,
            body: None,
            native: Some(add::add)
        }
    );

    dict.insert(
        "List_Pop",
        Procedure{
            variadic: false,
            arguments: vec![
                Argument{
                    kind: Kind::List,
                    name: ASTValue::Borrowed("list")
                }
            ],
            ret: None,
            body: None,
            native: Some(pop::pop)
        }
    );

    dict.insert(
        "List_Size",
        Procedure{
            variadic: false,
            arguments: vec![
                Argument{
                    kind: Kind::List,
                    name: ASTValue::Borrowed("list")
                }
            ],
            ret: Some(Kind::Integer),
            body: None,
            native: Some(size::size)
        }
    );

    dict.insert(
        "List_Set",
        Procedure{
            variadic: false,
            arguments: vec![
                Argument{
                    kind: Kind::List,
                    name: ASTValue::Borrowed("list")
                },
                Argument{
                    kind: Kind::Integer,
                    name: ASTValue::Borrowed("idx")
                },
                Argument{
                    kind: Kind::Any,
                    name: ASTValue::Borrowed("el")
                }
            ],
            ret: None,
            body: None,
            native: Some(set::set)
        }
    );
    
    dict.insert(
        "List_Join",
        Procedure{
            variadic: false,
            arguments: vec![
                Argument{
                    kind: Kind::List,
                    name: ASTValue::Borrowed("list")
                },
                Argument{
                    kind: Kind::String,
                    name: ASTValue::Borrowed("delim")
                }
            ],
            ret: Some(Kind::String),
            body: None,
            native: Some(join::join)
        }
    );

    dict
}