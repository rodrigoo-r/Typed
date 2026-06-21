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
                        name: ASTValue::Borrowed("dict"),
                        kind: Kind::Any,
                    }
                );
                
                vec
            },
            native: Some(access::access),
            ret: None
        }
    );
    
    dict
}