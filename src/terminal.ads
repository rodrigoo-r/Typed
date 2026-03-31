with Ansi;

package Terminal is

   type Style_Collection is array (Natural range <>) of Ansi_Style;

   procedure Clear;
   procedure Write (Text : String);
   procedure Write_Line (Text : String);
   procedure Write_Colored (Text : String; Color : Ansi.Ansi_Color; Styles : Style_Collection := (others => Ansi.Reset));
   procedure Write_Line_Colored (Text : String; Color : Ansi.Ansi_Color; Styles : Style_Collection := (others => Ansi.Reset));

end Terminal;