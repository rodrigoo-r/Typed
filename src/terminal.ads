with Ansi;

package Terminal is

   procedure Write (Text : String);
   procedure Write_Line (Text : String);
   procedure Write_Colored (Prefix : Ansi.Ansi_Color; Text : String);
   procedure Write_Line_Colored (Prefix : Ansi.Ansi_Color; Text : String);

end Terminal;