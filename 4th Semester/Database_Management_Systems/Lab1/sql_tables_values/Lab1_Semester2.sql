USE EPL_Management2;
GO


-- Stadiums
CREATE TABLE Stadiums (
    stadium_id INT IDENTITY (1,1) PRIMARY KEY,
    stadium_name VARCHAR(50),
    location VARCHAR(100),
    capacity INT
);

SELECT * FROM STADIUMS; 



-- Teams 
CREATE TABLE Teams (
    team_id INT IDENTITY (1,1) PRIMARY KEY,
    team_name VARCHAR(50),
    stadium_id INT FOREIGN KEY REFERENCES Stadiums(stadium_id),
    founding_year INT
);

SELECT * FROM TEAMS; 



-- Managers referencing Teams
CREATE TABLE Managers (
    manager_id INT IDENTITY (1,1) PRIMARY KEY,
    name VARCHAR(50),
    nationality VARCHAR(50),
    contract_start_date DATE,
    team_id INT FOREIGN KEY REFERENCES Teams(team_id)
);
SELECT * FROM MANAGERS; 



-- Players table
CREATE TABLE Players (
    player_id INT IDENTITY (1,1) PRIMARY KEY,
    name VARCHAR(50),
    position VARCHAR(30),
    nationality VARCHAR(50),
    date_of_birth DATE,
    team_id INT FOREIGN KEY REFERENCES Teams(team_id)
);
SELECT * FROM Players; 



-- Table: Matches
CREATE TABLE Matches (
    match_id INT IDENTITY (1,1) PRIMARY KEY,
    home_team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    away_team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    match_date DATE, 
    match_stadium INT FOREIGN KEY REFERENCES Stadiums(stadium_id)

);


-- Create the Match_Results 
CREATE TABLE Match_Results (
    result_id INT IDENTITY (1,1) PRIMARY KEY,
    match_id INT FOREIGN KEY REFERENCES Matches(match_id),
    home_team_goals INT,
    away_team_goals INT,
    match_winner INT FOREIGN KEY REFERENCES Teams(team_id), 
	
);


-- Table: Goals
CREATE TABLE Goals (
    goal_id INT IDENTITY (1,1) PRIMARY KEY,
    match_id INT FOREIGN KEY REFERENCES Matches(match_id),
    player_id INT FOREIGN KEY REFERENCES Players(player_id),
    minute INT,
    type_of_goal VARCHAR(50)  -- (e.g., header, penalty, etc.)

);


-- Table: Bookings
CREATE TABLE Bookings (
    booking_id INT IDENTITY (1,1) PRIMARY KEY ,
    match_id INT FOREIGN KEY REFERENCES Matches(match_id),
    player_id INT FOREIGN KEY REFERENCES Players(player_id),
    minute INT,
    card_type VARCHAR(50),  -- (e.g., Yellow, Red)

);


-- Table: Tournaments
CREATE TABLE Tournaments (
    tournament_id INT IDENTITY (1,1) PRIMARY KEY,
    name VARCHAR(50),
    season_start INT,
    season_end INT, 
	
);


-- Table: Transfers
CREATE TABLE Transfers (
    transfer_id INT IDENTITY (1,1) PRIMARY KEY,
    player_id INT FOREIGN KEY REFERENCES Players(player_id),
    from_team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    to_team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    transfer_fee DECIMAL(10, 2),
    transfer_date DATE, 
	
);

--- Many-to-Many Relationships:
-- Intermediate Table: Team_Tournament (To track which teams are part of
-- which tournaments):


-- Table: Team_Tournament (Intermediate table for Many-to-Many relationship)
CREATE TABLE Team_Tournament (
    team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    tournament_id INT FOREIGN KEY REFERENCES Tournaments(tournament_id),
    PRIMARY KEY (team_id, tournament_id)
);


SELECT * FROM Team_Tournament; 













