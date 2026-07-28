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
pub mod old;
pub mod standard;
pub mod cobol_parody;

use crate::adt::lang::AST;

pub fn format(
    ast: &AST, 
    output_fmt: &str
) -> String {
    let mut result = String::new();
    
    if output_fmt == "standard" {
        standard::format(ast, &mut result);
    } else if output_fmt == "old" {
        old::format(ast, &mut result);
    } else if output_fmt == "cobol_parody" {
        cobol_parody::format(ast, &mut result);
    } else {
        panic!("Unknown output format: {}", output_fmt);
    }
    
    result
}