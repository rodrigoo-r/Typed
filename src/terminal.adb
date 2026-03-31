with Ada.Text_IO;
with Ansi; use Ansi;

package body Terminal is

   procedure Set_Color (Color : Ansi.Ansi_Color) is
      use Ada.Text_IO;
   begin
      Put (String (Color));
   end Set_Color;

   procedure Write (Text : String) is
      use Ada.Text_IO;
   begin
      Put (Text);
   end Write;

   procedure Write_Line (Text : String) is
      use Ada.Text_IO;
   begin
      Put_Line (Text);
   end Write_Line;

   procedure Write_Colored (Prefix : Ansi.Ansi_Color; Text : String) is
      use Ada.Text_IO;
   begin
      Set_Color (Prefix);
      Put (Text & String (Ansi.Reset)); -- Reset to default after writing
   end Write_Colored;

   procedure Write_Line_Colored (Prefix : Ansi.Ansi_Color; Text : String) is
      use Ada.Text_IO;
   begin
      Set_Color (Prefix);
      Put_Line (Text & String (Ansi.Reset)); -- Reset to default after writing
   end Write_Line_Colored;

end Terminal;