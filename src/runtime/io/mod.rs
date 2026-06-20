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
use crate::adt::lang::{ASTChildren, ChildAST, NativeProcedure, Procedure};
use crate::adt::runtime::PackageDictionary;

pub mod print;

pub fn get_package<'a>() -> PackageDictionary<'a> {
    let mut dict = PackageDictionary::new();
    dict.insert(
        "Print_Line",
        Procedure{
            variadic: true,
            body: None,
            arguments: Vec::new(),
            native: Some(print::println)
        }
    );

    dict
}