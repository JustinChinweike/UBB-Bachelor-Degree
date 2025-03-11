namespace EPL_Management_App
{
    partial class Form1
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.dataGridViewPlayers = new System.Windows.Forms.DataGridView();
            this.dataGridViewTeams = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.Teams = new System.Windows.Forms.Label();
            this.btnUpdatePlayer = new System.Windows.Forms.Button();
            this.btnDeletePlayer = new System.Windows.Forms.Button();
            this.btnAddPlayer = new System.Windows.Forms.Button();
            this.txtName = new System.Windows.Forms.TextBox();
            this.txtNationality = new System.Windows.Forms.TextBox();
            this.Label_Name = new System.Windows.Forms.Label();
            this.Position = new System.Windows.Forms.Label();
            this.Nationality = new System.Windows.Forms.Label();
            this.DateOfBirth = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.txtPosition = new System.Windows.Forms.TextBox();
            this.dtpDateOfBirth = new System.Windows.Forms.DateTimePicker();
            this.comboTeam = new System.Windows.Forms.ComboBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewPlayers)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTeams)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewPlayers
            // 
            this.dataGridViewPlayers.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewPlayers.Location = new System.Drawing.Point(344, 42);
            this.dataGridViewPlayers.Name = "dataGridViewPlayers";
            this.dataGridViewPlayers.Size = new System.Drawing.Size(267, 340);
            this.dataGridViewPlayers.TabIndex = 0;
            this.dataGridViewPlayers.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.players_CellClick);
            this.dataGridViewPlayers.SelectionChanged += new System.EventHandler(this.dataGridViewPlayers_SelectionChanged);
            // 
            // dataGridViewTeams
            // 
            this.dataGridViewTeams.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTeams.Location = new System.Drawing.Point(-1, 42);
            this.dataGridViewTeams.Name = "dataGridViewTeams";
            this.dataGridViewTeams.Size = new System.Drawing.Size(308, 340);
            this.dataGridViewTeams.TabIndex = 1;
            this.dataGridViewTeams.SelectionChanged += new System.EventHandler(this.dataGridViewTeams_SelectionChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.SystemColors.MenuHighlight;
            this.label1.Location = new System.Drawing.Point(445, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Players";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(511, 219);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 13);
            this.label2.TabIndex = 4;
            // 
            // Teams
            // 
            this.Teams.AutoSize = true;
            this.Teams.BackColor = System.Drawing.SystemColors.MenuHighlight;
            this.Teams.Location = new System.Drawing.Point(45, 19);
            this.Teams.Name = "Teams";
            this.Teams.Size = new System.Drawing.Size(39, 13);
            this.Teams.TabIndex = 5;
            this.Teams.Text = "Teams";
            // 
            // btnUpdatePlayer
            // 
            this.btnUpdatePlayer.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.btnUpdatePlayer.Location = new System.Drawing.Point(899, 369);
            this.btnUpdatePlayer.Name = "btnUpdatePlayer";
            this.btnUpdatePlayer.Size = new System.Drawing.Size(85, 35);
            this.btnUpdatePlayer.TabIndex = 6;
            this.btnUpdatePlayer.Text = "Update Player";
            this.btnUpdatePlayer.UseVisualStyleBackColor = false;
            this.btnUpdatePlayer.Click += new System.EventHandler(this.btnUpdatePlayer_Click);
            // 
            // btnDeletePlayer
            // 
            this.btnDeletePlayer.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.btnDeletePlayer.Location = new System.Drawing.Point(777, 369);
            this.btnDeletePlayer.Name = "btnDeletePlayer";
            this.btnDeletePlayer.Size = new System.Drawing.Size(85, 35);
            this.btnDeletePlayer.TabIndex = 7;
            this.btnDeletePlayer.Text = "Delete Player";
            this.btnDeletePlayer.UseVisualStyleBackColor = false;
            this.btnDeletePlayer.Click += new System.EventHandler(this.DeletePlayers_Click);
            // 
            // btnAddPlayer
            // 
            this.btnAddPlayer.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.btnAddPlayer.Location = new System.Drawing.Point(646, 369);
            this.btnAddPlayer.Name = "btnAddPlayer";
            this.btnAddPlayer.Size = new System.Drawing.Size(85, 35);
            this.btnAddPlayer.TabIndex = 8;
            this.btnAddPlayer.Text = "Add Player";
            this.btnAddPlayer.UseVisualStyleBackColor = false;
            this.btnAddPlayer.Click += new System.EventHandler(this.btnAddPlayer_Click);
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(758, 19);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(152, 20);
            this.txtName.TabIndex = 12;
            this.txtName.TextChanged += new System.EventHandler(this.txtName_TextChanged);
            // 
            // txtNationality
            // 
            this.txtNationality.Location = new System.Drawing.Point(758, 114);
            this.txtNationality.Name = "txtNationality";
            this.txtNationality.Size = new System.Drawing.Size(152, 20);
            this.txtNationality.TabIndex = 13;
            // 
            // Label_Name
            // 
            this.Label_Name.AutoSize = true;
            this.Label_Name.BackColor = System.Drawing.SystemColors.Info;
            this.Label_Name.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Label_Name.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label_Name.Location = new System.Drawing.Point(707, 22);
            this.Label_Name.Name = "Label_Name";
            this.Label_Name.Size = new System.Drawing.Size(41, 15);
            this.Label_Name.TabIndex = 14;
            this.Label_Name.Text = "Name";
            // 
            // Position
            // 
            this.Position.AutoSize = true;
            this.Position.BackColor = System.Drawing.SystemColors.Info;
            this.Position.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.Position.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Position.Location = new System.Drawing.Point(690, 70);
            this.Position.Name = "Position";
            this.Position.Size = new System.Drawing.Size(54, 15);
            this.Position.TabIndex = 15;
            this.Position.Text = "Position";
            // 
            // Nationality
            // 
            this.Nationality.AutoSize = true;
            this.Nationality.BackColor = System.Drawing.SystemColors.Info;
            this.Nationality.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Nationality.Location = new System.Drawing.Point(677, 121);
            this.Nationality.Name = "Nationality";
            this.Nationality.Size = new System.Drawing.Size(71, 13);
            this.Nationality.TabIndex = 16;
            this.Nationality.Text = "Nationality ";
            // 
            // DateOfBirth
            // 
            this.DateOfBirth.AutoSize = true;
            this.DateOfBirth.BackColor = System.Drawing.SystemColors.Info;
            this.DateOfBirth.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.DateOfBirth.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DateOfBirth.Location = new System.Drawing.Point(661, 167);
            this.DateOfBirth.Name = "DateOfBirth";
            this.DateOfBirth.Size = new System.Drawing.Size(87, 15);
            this.DateOfBirth.TabIndex = 17;
            this.DateOfBirth.Text = "Date Of Birth ";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.BackColor = System.Drawing.SystemColors.Info;
            this.label7.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(704, 219);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 15);
            this.label7.TabIndex = 18;
            this.label7.Text = "Team ";
            // 
            // txtPosition
            // 
            this.txtPosition.Location = new System.Drawing.Point(758, 65);
            this.txtPosition.Name = "txtPosition";
            this.txtPosition.Size = new System.Drawing.Size(152, 20);
            this.txtPosition.TabIndex = 19;
            // 
            // dtpDateOfBirth
            // 
            this.dtpDateOfBirth.Location = new System.Drawing.Point(758, 162);
            this.dtpDateOfBirth.Name = "dtpDateOfBirth";
            this.dtpDateOfBirth.Size = new System.Drawing.Size(200, 20);
            this.dtpDateOfBirth.TabIndex = 20;
            // 
            // comboTeam
            // 
            this.comboTeam.FormattingEnabled = true;
            this.comboTeam.Location = new System.Drawing.Point(758, 213);
            this.comboTeam.Name = "comboTeam";
            this.comboTeam.Size = new System.Drawing.Size(121, 21);
            this.comboTeam.TabIndex = 21;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.DimGray;
            this.ClientSize = new System.Drawing.Size(1023, 450);
            this.Controls.Add(this.comboTeam);
            this.Controls.Add(this.dtpDateOfBirth);
            this.Controls.Add(this.txtPosition);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.DateOfBirth);
            this.Controls.Add(this.Nationality);
            this.Controls.Add(this.Position);
            this.Controls.Add(this.Label_Name);
            this.Controls.Add(this.txtNationality);
            this.Controls.Add(this.txtName);
            this.Controls.Add(this.btnAddPlayer);
            this.Controls.Add(this.btnDeletePlayer);
            this.Controls.Add(this.btnUpdatePlayer);
            this.Controls.Add(this.Teams);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridViewTeams);
            this.Controls.Add(this.dataGridViewPlayers);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewPlayers)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTeams)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewPlayers;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label Teams;
        private System.Windows.Forms.Button btnDeletePlayer;
        private System.Windows.Forms.Button btnAddPlayer;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.TextBox txtNationality;
        private System.Windows.Forms.Label Label_Name;
        private System.Windows.Forms.Label Position;
        private System.Windows.Forms.Label Nationality;
        private System.Windows.Forms.Label DateOfBirth;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtPosition;
        private System.Windows.Forms.DateTimePicker dtpDateOfBirth;
        private System.Windows.Forms.ComboBox comboTeam;
        private System.Windows.Forms.DataGridView dataGridViewTeams;
        private System.Windows.Forms.Button btnUpdatePlayer;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
    }
}

