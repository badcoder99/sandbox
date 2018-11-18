using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Canvas
{
    public partial class MainPage : Form
    {
        public MainPage()
        {
            InitializeComponent();
        }

        public void SetPanel(UserControl userControl)
        {
            mainPanel.Controls.Clear();
            mainPanel.Controls.Add(userControl);
            mainPanel.Focus();
        }

        public void SetUserName(string userName)
        {
            lblUserName.Text = userName;
        }

        public void UserPanelVisible(bool visible)
        {
            foreach (Control child in panelUser.Controls)
            {
                if (child.Text != "Exit")
                {
                    child.Visible = visible;
                }
            }
        }

        private void MainPage_FormClosed(object sender, FormClosedEventArgs e)
        {
            Controller.Exit();
        }

        private void btnLogout_Click(object sender, EventArgs e)
        {
            Controller.Logout();
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Controller.Exit();
        }
    }
}
