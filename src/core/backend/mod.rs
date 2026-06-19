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
mod procedure;

use crate::adt::lang::File;

pub fn execute(file: File) {
    // Get the main procedure
    let main = file.procedures.get("Main").unwrap();

    procedure::execute(main, Vec::new());
}