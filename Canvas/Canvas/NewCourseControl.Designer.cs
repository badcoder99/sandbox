namespace Canvas
{
    partial class NewCourseControl
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
            this.txtTeacher = new System.Windows.Forms.TextBox();
            this.lblTeacher = new System.Windows.Forms.Label();
            this.listTeacher = new System.Windows.Forms.ListBox();
            this.btnSearch = new System.Windows.Forms.Button();
            this.txtCourseName = new System.Windows.Forms.TextBox();
            this.lblCourseName = new System.Windows.Forms.Label();
            this.txtSearch = new System.Windows.Forms.TextBox();
            this.btnCreateCourse = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txtTeacher
            // 
            this.txtTeacher.Location = new System.Drawing.Point(100, 144);
            this.txtTeacher.Name = "txtTeacher";
            this.txtTeacher.ReadOnly = true;
            this.txtTeacher.Size = new System.Drawing.Size(200, 22);
            this.txtTeacher.TabIndex = 0;
            // 
            // lblTeacher
            // 
            this.lblTeacher.AutoSize = true;
            this.lblTeacher.Location = new System.Drawing.Point(33, 147);
            this.lblTeacher.Name = "lblTeacher";
            this.lblTeacher.Size = new System.Drawing.Size(61, 17);
            this.lblTeacher.TabIndex = 1;
            this.lblTeacher.Text = "Teacher";
            // 
            // listTeacher
            // 
            this.listTeacher.FormattingEnabled = true;
            this.listTeacher.ItemHeight = 16;
            this.listTeacher.Location = new System.Drawing.Point(306, 3);
            this.listTeacher.Name = "listTeacher";
            this.listTeacher.Size = new System.Drawing.Size(442, 468);
            this.listTeacher.TabIndex = 3;
            // 
            // btnSearch
            // 
            this.btnSearch.Location = new System.Drawing.Point(100, 31);
            this.btnSearch.Name = "btnSearch";
            this.btnSearch.Size = new System.Drawing.Size(200, 33);
            this.btnSearch.TabIndex = 15;
            this.btnSearch.Text = "Search";
            this.btnSearch.UseVisualStyleBackColor = true;
            // 
            // txtCourseName
            // 
            this.txtCourseName.Location = new System.Drawing.Point(100, 172);
            this.txtCourseName.Name = "txtCourseName";
            this.txtCourseName.Size = new System.Drawing.Size(200, 22);
            this.txtCourseName.TabIndex = 16;
            // 
            // lblCourseName
            // 
            this.lblCourseName.AutoSize = true;
            this.lblCourseName.Location = new System.Drawing.Point(0, 175);
            this.lblCourseName.Name = "lblCourseName";
            this.lblCourseName.Size = new System.Drawing.Size(94, 17);
            this.lblCourseName.TabIndex = 17;
            this.lblCourseName.Text = "Course Name";
            // 
            // txtSearch
            // 
            this.txtSearch.Location = new System.Drawing.Point(100, 3);
            this.txtSearch.Name = "txtSearch";
            this.txtSearch.Size = new System.Drawing.Size(200, 22);
            this.txtSearch.TabIndex = 18;
            // 
            // btnCreateCourse
            // 
            this.btnCreateCourse.Location = new System.Drawing.Point(100, 200);
            this.btnCreateCourse.Name = "btnCreateCourse";
            this.btnCreateCourse.Size = new System.Drawing.Size(200, 33);
            this.btnCreateCourse.TabIndex = 19;
            this.btnCreateCourse.Text = "Create Course";
            this.btnCreateCourse.UseVisualStyleBackColor = true;
            // 
            // NewCourseControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnCreateCourse);
            this.Controls.Add(this.txtSearch);
            this.Controls.Add(this.lblCourseName);
            this.Controls.Add(this.txtCourseName);
            this.Controls.Add(this.btnSearch);
            this.Controls.Add(this.listTeacher);
            this.Controls.Add(this.lblTeacher);
            this.Controls.Add(this.txtTeacher);
            this.Name = "NewCourseControl";
            this.Size = new System.Drawing.Size(751, 482);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtTeacher;
        private System.Windows.Forms.Label lblTeacher;
        private System.Windows.Forms.ListBox listTeacher;
        private System.Windows.Forms.Button btnSearch;
        private System.Windows.Forms.TextBox txtCourseName;
        private System.Windows.Forms.Label lblCourseName;
        private System.Windows.Forms.TextBox txtSearch;
        private System.Windows.Forms.Button btnCreateCourse;
    }
}
