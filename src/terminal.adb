with Ada.Text_IO;
with Ansi; use Ansi;

package body Terminal is

   procedure Set_Color (Color : Ansi.Ansi_Color) is
      use Ada.Text_IO;
   begin
      Put (Color);
   end Set_Color;

   procedure Set_Styles (Styles : Style_Collection) is
      use Ada.Text_IO;
   begin
      for Style of Styles loop
         Put (Style);
      end loop;
   end Set_Styles;

   procedure Clear is
      use Ada.Text_IO;
   begin
      Clear_Screen;
   end Clear;

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

   procedure Write_Colored (Text : String; Color : Ansi.Ansi_Color; Styles : Style_Collection) is
      use Ada.Text_IO;
   begin
      Set_Color (Color);
      Set_Styles (Styles);
      Put (Text);
      Put (Reset); -- Reset to default after writing
   end Write_Colored;

   procedure Write_Line_Colored (Text : String; Color : Ansi.Ansi_Color; Styles : Style_Collection) is
      use Ada.Text_IO;
   begin
      Set_Color (Color);
      Set_Styles (Styles);
      Put_Line (Text);
      Put (Reset); -- Reset to default after writing
   end Write_Line_Colored;

end Terminal;