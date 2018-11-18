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
        enum ControlType { ManageUsers, NewCourse, ManageCourse };

        public AdminControl()
        {
            InitializeComponent();
        }

        private void SetControl(ControlType type)
        {              
            Action<UserControl, Button> set = 
                (userControl, button) => 
                {
                    btnManageUsers.Enabled = true;
                    btnNewCourse.Enabled = true;
                    btnManageCourses.Enabled = true;
                    button.Enabled = false;
                    panelAdmin.Controls.Clear();
                    panelAdmin.Controls.Add(userControl);
                    panelAdmin.Focus();
                };
            switch (type)
            {
                case ControlType.ManageUsers:
                    set(new ManageUserControl(), btnManageUsers);
                    break;

                case ControlType.NewCourse:
                    set(new NewCourseControl(), btnNewCourse);
                    break;

                case ControlType.ManageCourse:
                    set(new ManageCourseControl(), btnManageCourses);
                    break;
            }           
        }

        private void btnManageUsers_Click(object sender, EventArgs e)
        {
            SetControl(ControlType.ManageUsers);
        }

        private void btnManageCourses_Click(object sender, EventArgs e)
        {
            SetControl(ControlType.ManageCourse);
        }

        private void btnNewCourse_Click(object sender, EventArgs e)
        {
            SetControl(ControlType.NewCourse);
        }
    }
}
