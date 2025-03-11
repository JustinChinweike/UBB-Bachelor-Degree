using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace EPL_Management_App
{
    public class DatabaseHelper
    {
        private string connectionString = "Data Source=JUSTIN; Initial Catalog=EPL_Management2;Integrated Security=True;";
        private SqlDataAdapter teamsAdapter;
        private SqlDataAdapter playersAdapter;
        private DataSet dataSet;

        public DatabaseHelper()
        {
            dataSet = new DataSet();
        }

        //  Get Teams (Parent Table)
        public DataTable GetTeams()
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM Teams";
                teamsAdapter = new SqlDataAdapter(query, conn);
                if (dataSet.Tables.Contains("Teams"))
                {
                    dataSet.Tables["Teams"].Clear(); // Clear old data
                }
                teamsAdapter.Fill(dataSet, "Teams");
                return dataSet.Tables["Teams"];
            }
        }

        // Get Players for Selected Team (Child Table)
        public DataTable GetPlayersByTeam(int teamId)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                string query = "SELECT * FROM Players WHERE team_id = @team_id";
                playersAdapter = new SqlDataAdapter(query, conn);
                playersAdapter.SelectCommand.Parameters.AddWithValue("@team_id", teamId);

                if (dataSet.Tables.Contains("Players"))
                {
                    dataSet.Tables["Players"].Clear(); // Clear previous data
                }
                playersAdapter.Fill(dataSet, "Players");
                return dataSet.Tables["Players"];
            }
        }

        // Add Player
        public void AddPlayer(string name, string position, string nationality, DateTime dateOfBirth, int teamId)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                string query = "INSERT INTO Players (name, position, nationality, date_of_birth, team_id) VALUES (@name, @position, @nationality, @date_of_birth, @team_id)";
                using (SqlCommand cmd = new SqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@name", name);
                    cmd.Parameters.AddWithValue("@position", position);
                    cmd.Parameters.AddWithValue("@nationality", nationality);
                    cmd.Parameters.AddWithValue("@date_of_birth", dateOfBirth);
                    cmd.Parameters.AddWithValue("@team_id", teamId);
                    cmd.ExecuteNonQuery();
                }
            }
        }

        // Update Player
        
        public void UpdatePlayer(int playerId, string name, string position, string nationality, DateTime dateOfBirth, int teamId)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                string query = @"UPDATE Players 
                         SET name = @name, 
                             position = @position, 
                             nationality = @nationality, 
                             date_of_birth = @date_of_birth, 
                             team_id = @team_id
                         WHERE player_id = @player_id";

                using (SqlCommand cmd = new SqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@name", name);
                    cmd.Parameters.AddWithValue("@position", position);
                    cmd.Parameters.AddWithValue("@nationality", nationality);
                    cmd.Parameters.AddWithValue("@date_of_birth", dateOfBirth);
                    cmd.Parameters.AddWithValue("@team_id", teamId); // new team
                    cmd.Parameters.AddWithValue("@player_id", playerId);

                    cmd.ExecuteNonQuery();
                }
            }
        }


        // Delete Player
        public void DeletePlayer(int playerId)
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                string query = "DELETE FROM Players WHERE player_id = @player_id";
                using (SqlCommand cmd = new SqlCommand(query, conn))
                {
                    cmd.Parameters.AddWithValue("@player_id", playerId);
                    cmd.ExecuteNonQuery();
                }
            }
        }
    }
}
