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
    public partial class ManageUserControl : UserControl
    {
        public ManageUserControl()
        {
            InitializeComponent();
            new Task(() => UpdateUserList(Database.GetUsers())).Start();
        }

        private void txtSearch_TextChanged(object sender, EventArgs e)
        {
            new Task(() => UpdateUserList(Database.GetUsers(txtSearch.Text))).Start();
        }

        private void ClearSelectedUser()
        {
            txtUserID.Text = string.Empty;
            txtFirstName.Text = string.Empty;
            txtLastName.Text = string.Empty;
            btnDeleteUser.Enabled = false;
            btnUpdateUser.Enabled = false;
        }

        private void UpdateUserList(List<User> users, bool selectLast = false)
        {
            Invoke(new MethodInvoker(delegate
            {
                ClearSelectedUser();
                listUser.Items.Clear();                
                listUser.Items.AddRange(users.ToArray());
                if (selectLast)
                {
                    listUser.SelectedIndex = listUser.Items.Count - 1;
                }
            }));
        }

        private void listUser_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listUser.SelectedItem is User)
            {
                var user = listUser.SelectedItem as User;
                txtUserID.Text = user.userID;
                txtFirstName.Text = user.firstName;
                txtLastName.Text = user.lastName;
                btnDeleteUser.Enabled = true;
                btnUpdateUser.Enabled = true;
            }
            else
            {
                ClearSelectedUser();   
            }
        }

        private void btnUpdateUser_Click(object sender, EventArgs e)
        {
            var updatedUser = new User()
            {
                firstName = txtFirstName.Text,
                lastName = txtLastName.Text,
                userID = txtUserID.Text
            };
            int idx = listUser.SelectedIndex;
            listUser.Items[idx] = updatedUser;
            btnUpdateUser.Focus();
            new Task(() => 
            {
                Database.UpdateUser(updatedUser);
            }).Start();
            
        }

        private void btnDeleteUser_Click(object sender, EventArgs e)
        {
            ClearSelectedUser();
            var user = listUser.SelectedItem as User;
            listUser.Items.Remove(user);
            new Task(() =>
            {
                Database.DeleteUser(user);
            }).Start();
            
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            ClearSelectedUser();
            txtSearch.Text = string.Empty;
        }

        private void btnCreateUser_Click(object sender, EventArgs e)
        {
            if (Database.CreateUser(txtNewFirstName.Text.Trim(), txtNewLastName.Text.Trim()))
            {
                txtNewFirstName.Text = "";
                txtNewLastName.Text = "";
                lblStatus.ForeColor = Color.Green;
                ClearSelectedUser();
                new Task(() =>
                {
                    UpdateUserList(Database.GetUsers(), true);                   
                }).Start();

            }
            else
            {
                lblStatus.ForeColor = Color.Red;
                lblStatus.Text = "Invalid user information";
            }
        }

        private void txtNewLastName_TextChanged(object sender, EventArgs e)
        {
            lblStatus.Text = "";
        }

        private void txtNewFirstName_TextChanged(object sender, EventArgs e)
        {
            lblStatus.Text = "";
        }
    }
}
