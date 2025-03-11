
using System;
using System.Data;
using System.Windows.Forms;


namespace EPL_Management_App
{
    public partial class Form1 : Form
    {
        private DatabaseHelper dbHelper = new DatabaseHelper();

        public Form1()
        {
            InitializeComponent();
            LoadTeams();
        }

        //  Load Teams (Parent Table)
        private void LoadTeams()
        {
            DataTable teams = dbHelper.GetTeams();
            if (teams.Rows.Count > 0)
            {
                dataGridViewTeams.DataSource = teams;
                comboTeam.DataSource = teams;
                comboTeam.DisplayMember = "team_name";
                comboTeam.ValueMember = "team_id";
            }
            else
            {
                MessageBox.Show("No teams found in the database. Please check your database connection!",
                                "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        //// Load Players for Selected Team (Child Table)

        private void dataGridViewTeams_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewTeams.SelectedRows.Count > 0)
            {
                int teamId = Convert.ToInt32(dataGridViewTeams.SelectedRows[0].Cells["team_id"].Value);

                DataTable playersTable = dbHelper.GetPlayersByTeam(teamId);

                if (playersTable != null && playersTable.Rows.Count > 0)
                    dataGridViewPlayers.DataSource = playersTable;
                else
                    dataGridViewPlayers.DataSource = null;  // Clear if no players
            }
        }


        private void dataGridViewPlayers_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridViewPlayers.SelectedRows.Count > 0)
            {
                DataGridViewRow row = dataGridViewPlayers.SelectedRows[0];

                txtName.Text = row.Cells["name"].Value.ToString();
                txtPosition.Text = row.Cells["position"].Value.ToString();
                txtNationality.Text = row.Cells["nationality"].Value.ToString();
                dtpDateOfBirth.Value = Convert.ToDateTime(row.Cells["date_of_birth"].Value);

                // Set the ComboBox to player's current team
                comboTeam.SelectedValue = row.Cells["team_id"].Value;
            }
        }






        private void btnAddPlayer_Click(object sender, EventArgs e)
        {
            if (comboTeam.SelectedValue == null)
            {
                MessageBox.Show("Please select a team first.");
                return;
            }

            int teamId = Convert.ToInt32(comboTeam.SelectedValue);

            dbHelper.AddPlayer(txtName.Text, txtPosition.Text, txtNationality.Text, dtpDateOfBirth.Value, teamId);

            MessageBox.Show("Player added successfully!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);

            dataGridViewPlayers.DataSource = dbHelper.GetPlayersByTeam(teamId);
        }




        private void btnUpdatePlayer_Click(object sender, EventArgs e)
        {
            if (dataGridViewPlayers.SelectedRows.Count == 0)
            {
                MessageBox.Show("Please select a player first.");
                return;
            }

            int playerId = Convert.ToInt32(dataGridViewPlayers.SelectedRows[0].Cells["player_id"].Value);
            int teamId = Convert.ToInt32(comboTeam.SelectedValue); // Get selected team from combo box

            dbHelper.UpdatePlayer(playerId, txtName.Text, txtPosition.Text, txtNationality.Text, dtpDateOfBirth.Value, teamId);

            MessageBox.Show("Player updated successfully!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);

            // Refresh the grid view for both the old and new teams
            dataGridViewPlayers.DataSource = dbHelper.GetPlayersByTeam(teamId);
        }






        private void DeletePlayers_Click(object sender, EventArgs e)
        {
            if (dataGridViewPlayers.SelectedRows.Count == 0)
            {
                MessageBox.Show("Please select a player first.");
                return;
            }

            int playerId = Convert.ToInt32(dataGridViewPlayers.SelectedRows[0].Cells["player_id"].Value);
            dbHelper.DeletePlayer(playerId);

            MessageBox.Show("Player deleted successfully!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            dataGridViewPlayers.DataSource = dbHelper.GetPlayersByTeam(Convert.ToInt32(comboTeam.SelectedValue));
        }



        private void players_CellClick(object sender, DataGridViewCellEventArgs e)
        {


        }

        private void txtName_TextChanged(object sender, EventArgs e)
        {

        }
    }


}






