with Ada.Containers.Hashed_Maps;

package Lang.Map is

   procedure Initialize;

private

   package Map_Type is new Ada.Containers.Hashed_Maps
      (
         Key_Type => String, 
         Element_Type => Integer,
         Hash => Ada.Strings.Hash,
         Equivalent_Keys => Ada.Strings.Equal_Case_Insensitive
      );

   Token_Map : Map_Type.Map;

end Lang.Map;