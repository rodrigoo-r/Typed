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
use crate::adt::lang::{ASTValue, Argument, Kind, Procedure};
use crate::adt::runtime::PackageDictionary;

pub mod contains;
pub mod values;
pub mod remove;
pub mod size;
pub mod add;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();

    dict.insert(
        "Set_Values",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut vec = vec![];

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("set"),
                        kind: Kind::Set,
                    }
                );

                vec
            },
            native: Some(values::values),
            ret: None
        }
    );

    dict.insert(
        "Set_Add",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut vec = vec![];

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("set"),
                        kind: Kind::Set,
                    }
                );

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("key"),
                        kind: Kind::Any,
                    }
                );

                vec
            },
            native: Some(add::add),
            ret: None
        }
    );

    dict.insert(
        "Set_Contains",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut vec = vec![];

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("set"),
                        kind: Kind::Set,
                    }
                );

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("key"),
                        kind: Kind::Any,
                    }
                );

                vec
            },
            native: Some(contains::contains),
            ret: None
        }
    );

    dict.insert(
        "Set_Remove",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut vec = vec![];

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("set"),
                        kind: Kind::Set,
                    }
                );

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("key"),
                        kind: Kind::Any,
                    }
                );

                vec
            },
            native: Some(remove::remove),
            ret: None
        }
    );

    dict.insert(
        "Set_Size",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut vec = vec![];

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("set"),
                        kind: Kind::Set,
                    }
                );

                vec
            },
            native: Some(size::size),
            ret: None
        }
    );

    dict
}