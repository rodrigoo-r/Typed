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

#[macro_export]
macro_rules! execute_or_return {
    ($expr:expr) => {{
        let res = $expr;

        if res != crate::adt::runtime::Object::Void {
            return Ok(res);
        }
    }}
}