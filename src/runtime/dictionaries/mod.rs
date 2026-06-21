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
pub mod set;
pub mod remove;

use crate::adt::lang::{ASTValue, Argument, Kind, Procedure};
use crate::adt::runtime::PackageDictionary;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();

    dict.insert(
        "Dictionary_Access",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut vec = vec![];

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("dict"),
                        kind: Kind::Dictionary,
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
            native: Some(access::access),
            ret: None
        }
    );

    dict.insert(
        "Dictionary_Set",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut vec = vec![];

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("dict"),
                        kind: Kind::Dictionary,
                    }
                );

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("key"),
                        kind: Kind::Any,
                    }
                );

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("value"),
                        kind: Kind::Any,
                    }
                );

                vec
            },
            native: Some(set::set),
            ret: None
        }
    );

    dict.insert(
        "Dictionary_Remove",
        Procedure{
            variadic: false,
            body: None,
            arguments: {
                let mut vec = vec![];

                vec.push(
                    Argument{
                        name: ASTValue::Borrowed("dict"),
                        kind: Kind::Dictionary,
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
    
    dict
}