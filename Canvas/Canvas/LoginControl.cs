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
    public partial class LoginControl : UserControl
    {
        public LoginControl()
        {
            InitializeComponent();
        }

        private void LoginSequence()
        {
            if (!Controller.TryLogin(txtUserID.Text))
            {
                lblResult.Text = "Failed to login";
                txtUserID.Focus();
                txtUserID.SelectAll();
                txtPassword.Text = null;
            }
        }

        private void txtUserID_KeyDown(object sender, KeyEventArgs e)
        {
            if (btnLogin.Enabled)
            {
                if (e.KeyCode == Keys.Enter)
                {
                    LoginSequence();
                }
                else
                {
                    lblResult.Text = null;
                }
            }
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            LoginSequence();
        }

        private void txtPassword_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                LoginSequence();
            }
            else
            {
                lblResult.Text = null;
            }
        }
        public void StartLoading()
        {
            btnLogin.Enabled = false;
            lblResult.Text = "Loading database...";        
        }
        public void StopLoading()
        {
            Invoke(new MethodInvoker(delegate
            {
                btnLogin.Enabled = true;
                lblResult.Text = null;
            }));
        }
    }
}
