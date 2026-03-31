with Ansi;

package Wide_Terminal is

   procedure Write (Text : Wide_String);
   procedure Write_Line (Text : Wide_String);
   procedure Write_Colored (Prefix : Ansi.Ansi_Color; Text : Wide_String);
   procedure Write_Line_Colored (Prefix : Ansi.Ansi_Color; Text : Wide_String);

end Wide_Terminal;