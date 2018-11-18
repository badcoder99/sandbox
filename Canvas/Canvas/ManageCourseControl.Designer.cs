namespace Canvas
{
    partial class ManageCourseControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.listCourse = new System.Windows.Forms.ListBox();
            this.listTeacher = new System.Windows.Forms.ListBox();
            this.listStudent = new System.Windows.Forms.ListBox();
            this.lblCourses = new System.Windows.Forms.Label();
            this.lblTeachers = new System.Windows.Forms.Label();
            this.lblStudents = new System.Windows.Forms.Label();
            this.txtCourse = new System.Windows.Forms.TextBox();
            this.txtStudent = new System.Windows.Forms.TextBox();
            this.listEnrolled = new System.Windows.Forms.ListBox();
            this.txtTeacher = new System.Windows.Forms.TextBox();
            this.lblEnrolled = new System.Windows.Forms.Label();
            this.txtEnrolled = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // listCourse
            // 
            this.listCourse.FormattingEnabled = true;
            this.listCourse.ItemHeight = 16;
            this.listCourse.Location = new System.Drawing.Point(3, 31);
            this.listCourse.Name = "listCourse";
            this.listCourse.Size = new System.Drawing.Size(297, 132);
            this.listCourse.TabIndex = 0;
            // 
            // listTeacher
            // 
            this.listTeacher.FormattingEnabled = true;
            this.listTeacher.ItemHeight = 16;
            this.listTeacher.Location = new System.Drawing.Point(325, 31);
            this.listTeacher.Name = "listTeacher";
            this.listTeacher.Size = new System.Drawing.Size(300, 132);
            this.listTeacher.TabIndex = 1;
            // 
            // listStudent
            // 
            this.listStudent.FormattingEnabled = true;
            this.listStudent.ItemHeight = 16;
            this.listStudent.Location = new System.Drawing.Point(3, 202);
            this.listStudent.Name = "listStudent";
            this.listStudent.Size = new System.Drawing.Size(297, 260);
            this.listStudent.TabIndex = 2;
            // 
            // lblCourses
            // 
            this.lblCourses.AutoSize = true;
            this.lblCourses.Location = new System.Drawing.Point(34, 6);
            this.lblCourses.Name = "lblCourses";
            this.lblCourses.Size = new System.Drawing.Size(60, 17);
            this.lblCourses.TabIndex = 3;
            this.lblCourses.Text = "Courses";
            // 
            // lblTeachers
            // 
            this.lblTeachers.AutoSize = true;
            this.lblTeachers.Location = new System.Drawing.Point(351, 6);
            this.lblTeachers.Name = "lblTeachers";
            this.lblTeachers.Size = new System.Drawing.Size(68, 17);
            this.lblTeachers.TabIndex = 4;
            this.lblTeachers.Text = "Teachers";
            // 
            // lblStudents
            // 
            this.lblStudents.AutoSize = true;
            this.lblStudents.Location = new System.Drawing.Point(30, 177);
            this.lblStudents.Name = "lblStudents";
            this.lblStudents.Size = new System.Drawing.Size(64, 17);
            this.lblStudents.TabIndex = 5;
            this.lblStudents.Text = "Students";
            // 
            // txtCourse
            // 
            this.txtCourse.Location = new System.Drawing.Point(100, 3);
            this.txtCourse.Name = "txtCourse";
            this.txtCourse.Size = new System.Drawing.Size(200, 22);
            this.txtCourse.TabIndex = 6;
            // 
            // txtStudent
            // 
            this.txtStudent.Location = new System.Drawing.Point(100, 174);
            this.txtStudent.Name = "txtStudent";
            this.txtStudent.Size = new System.Drawing.Size(200, 22);
            this.txtStudent.TabIndex = 8;
            // 
            // listEnrolled
            // 
            this.listEnrolled.FormattingEnabled = true;
            this.listEnrolled.ItemHeight = 16;
            this.listEnrolled.Location = new System.Drawing.Point(325, 202);
            this.listEnrolled.Name = "listEnrolled";
            this.listEnrolled.Size = new System.Drawing.Size(300, 260);
            this.listEnrolled.TabIndex = 9;
            // 
            // txtTeacher
            // 
            this.txtTeacher.Location = new System.Drawing.Point(425, 3);
            this.txtTeacher.Name = "txtTeacher";
            this.txtTeacher.Size = new System.Drawing.Size(200, 22);
            this.txtTeacher.TabIndex = 10;
            // 
            // lblEnrolled
            // 
            this.lblEnrolled.AutoSize = true;
            this.lblEnrolled.Location = new System.Drawing.Point(359, 177);
            this.lblEnrolled.Name = "lblEnrolled";
            this.lblEnrolled.Size = new System.Drawing.Size(60, 17);
            this.lblEnrolled.TabIndex = 11;
            this.lblEnrolled.Text = "Enrolled";
            // 
            // txtEnrolled
            // 
            this.txtEnrolled.Location = new System.Drawing.Point(425, 174);
            this.txtEnrolled.Name = "txtEnrolled";
            this.txtEnrolled.Size = new System.Drawing.Size(200, 22);
            this.txtEnrolled.TabIndex = 12;
            // 
            // ManageCourseControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.txtEnrolled);
            this.Controls.Add(this.lblEnrolled);
            this.Controls.Add(this.txtTeacher);
            this.Controls.Add(this.listEnrolled);
            this.Controls.Add(this.txtStudent);
            this.Controls.Add(this.txtCourse);
            this.Controls.Add(this.lblStudents);
            this.Controls.Add(this.lblTeachers);
            this.Controls.Add(this.lblCourses);
            this.Controls.Add(this.listStudent);
            this.Controls.Add(this.listTeacher);
            this.Controls.Add(this.listCourse);
            this.Name = "ManageCourseControl";
            this.Size = new System.Drawing.Size(751, 482);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listCourse;
        private System.Windows.Forms.ListBox listTeacher;
        private System.Windows.Forms.ListBox listStudent;
        private System.Windows.Forms.Label lblCourses;
        private System.Windows.Forms.Label lblTeachers;
        private System.Windows.Forms.Label lblStudents;
        private System.Windows.Forms.TextBox txtCourse;
        private System.Windows.Forms.TextBox txtStudent;
        private System.Windows.Forms.ListBox listEnrolled;
        private System.Windows.Forms.TextBox txtTeacher;
        private System.Windows.Forms.Label lblEnrolled;
        private System.Windows.Forms.TextBox txtEnrolled;
    }
}
