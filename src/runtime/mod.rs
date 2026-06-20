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
use crate::adt::runtime::GlobalPackageDictionary;

pub mod io;

pub fn get_global_package<'a>() -> GlobalPackageDictionary<'a> {
    let mut result = GlobalPackageDictionary::new();
    result.insert("IO", io::get_package());
    
    result
}
