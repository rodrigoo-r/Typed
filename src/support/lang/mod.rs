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
use crate::adt::lang::AST;

#[warn(dead_code)]
pub fn print_ast<'a>(
    ast: AST<'a>,
    depth: usize
) {
    let children = ast.children.borrow().clone();
    for child in children.into_iter() {
        for _ in 0..depth {
            print!("  ");
        }
        
        let child = child.borrow();
        print!("{:?}", child.rule);
        
        if child.value.is_some() {
            print!(": {:?}", child.value);
        }
        
        println!();
        print_ast(child.clone(), depth + 1);
    }
}