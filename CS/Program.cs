using System;
using System.Drawing;
using System.Windows.Forms;

public class Program : Form {
   [STAThread]
   public static void Main() {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      Application.Run(new Program());
   }
   private Button btn1 = new Button() {
      Top = 5, Left = 5, Text = "Exit", FlatStyle = FlatStyle.Flat,
      Height = 490, Width = 490, Font = new Font("Arial", 64) 
   };
   public Program() {
      this.ClientSize = new Size(500, 500);
      this.Text = "Program";
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.ShowIcon = false;
      this.BackColor = Color.FromName("WhiteSmoke");
      btn1.Click += (s, e) => this.Close();
      this.Controls.Add(btn1);
      this.Show();
      this.DesktopLocation = new Point(25, 25);
   }
}


