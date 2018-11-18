using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Canvas
{
    public partial class AdminControl : UserControl
    {
        public AdminControl()
        {
            InitializeComponent();
        }

        private void btnManageUsers_Click(object sender, EventArgs e)
        {
            btnManageUsers.Enabled = false;
            panelAdmin.Controls.Clear();
            panelAdmin.Controls.Add(new ManageUserControl());
            panelAdmin.Focus();
        }
    }
}
