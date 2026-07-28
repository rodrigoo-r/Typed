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
use crate::cli::RunCommand;
use crate::core::middle_end;
use crate::core::backend::execute;
use crate::runtime::get_global_package;
use crate::support::failable::{catch, catch_non_traceable};
use crate::support::file;

pub fn handle(cmd: &RunCommand) {
    let contents = file::read(cmd.file.as_str());
    let contents = catch_non_traceable(&contents);
    
    let ast = file::parse(&contents, &cmd.syntax);

    let global_package = get_global_package();

    let file = middle_end::pre_walker::convert(ast, &global_package);
    let file = catch(&file);

    catch(&execute(file));
}