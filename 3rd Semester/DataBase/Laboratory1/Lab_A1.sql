USE EPL_Management;
GO


-- Table: Teams
CREATE TABLE Teams (
    team_id INT,
    team_name VARCHAR(50),
    stadium_id INT,  -- Foreign key for Stadiums, will be added later
    manager_id INT,  -- Foreign key for Managers, will be added later
    founding_year INT
	PRIMARY KEY (team_id)
);
SELECT * FROM TEAMS; 


-- Table: Managers
CREATE TABLE Managers (
    manager_id INT NOT NULL,  
    name VARCHAR(50),
    nationality VARCHAR(50),
    contract_start_date DATE,
    PRIMARY KEY (manager_id)
-- team_id INT FOREIGN KEY REFERENCES Teams(team_id), 

);
SELECT * FROM MANAGERS; 




-- Table: Players
CREATE TABLE Players (
    player_id INT , 
    name VARCHAR(50),
    position VARCHAR(30),
    nationality VARCHAR(50),
    date_of_birth DATE,
    team_id INT FOREIGN KEY REFERENCES Teams(team_id),
	PRIMARY KEY (player_id) , 
);
SELECT * FROM Players; 




-- Table: Stadiums
CREATE TABLE Stadiums (
    stadium_id INT ,
    stadium_name VARCHAR(50),
    location VARCHAR(100),
    capacity INT,
	PRIMARY KEY (stadium_id)
);
SELECT * FROM STADIUMS; 


-- Table: Matches
CREATE TABLE Matches (
    match_id INT,
    home_team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    away_team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    match_date DATE,
	PRIMARY KEY(match_id), 
    match_stadium INT FOREIGN KEY REFERENCES Stadiums(stadium_id)

);

-- Create the Match_Results 
CREATE TABLE Match_Results (
    result_id INT,
    match_id INT FOREIGN KEY REFERENCES Matches(match_id),
    home_team_goals INT,
    away_team_goals INT,
    match_winner INT FOREIGN KEY REFERENCES Teams(team_id), 
	PRIMARY KEY (result_id)
);



-- Table: Goals
CREATE TABLE Goals (
    goal_id INT,
    match_id INT FOREIGN KEY REFERENCES Matches(match_id),
    player_id INT FOREIGN KEY REFERENCES Players(player_id),
    minute INT,
    type_of_goal VARCHAR(50)  -- (e.g., header, penalty, etc.)
	PRIMARY KEY (goal_id)
);



-- Table: Bookings
CREATE TABLE Bookings (
    booking_id INT ,
    match_id INT FOREIGN KEY REFERENCES Matches(match_id),
    player_id INT FOREIGN KEY REFERENCES Players(player_id),
    minute INT,
    card_type VARCHAR(50),  -- (e.g., Yellow, Red)
	PRIMARY KEY (booking_id)
);


-- Table: Tournaments
CREATE TABLE Tournaments (
    tournament_id INT,
    name VARCHAR(50),
    season_start INT,
    season_end INT, 
	PRIMARY KEY (tournament_id)
);


-- Table: Transfers
CREATE TABLE Transfers (
    transfer_id INT,
    player_id INT FOREIGN KEY REFERENCES Players(player_id),
    from_team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    to_team_id INT FOREIGN KEY REFERENCES Teams(team_id),
    transfer_fee DECIMAL(10, 2),
    transfer_date DATE, 
	PRIMARY KEY (transfer_id) 
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










SELECT 
    fk.name AS ForeignKeyName,
    tp.name AS ParentTable,
    cp.name AS ParentColumn,
    tr.name AS ReferencedTable,
    cr.name AS ReferencedColumn
FROM 
    sys.foreign_keys AS fk
INNER JOIN 
    sys.foreign_key_columns AS fkc ON fk.object_id = fkc.constraint_object_id
INNER JOIN 
    sys.tables AS tp ON fkc.parent_object_id = tp.object_id
INNER JOIN 
    sys.columns AS cp ON fkc.parent_object_id = cp.object_id AND fkc.parent_column_id = cp.column_id
INNER JOIN 
    sys.tables AS tr ON fkc.referenced_object_id = tr.object_id
INNER JOIN 
    sys.columns AS cr ON fkc.referenced_object_id = cr.object_id AND fkc.referenced_column_id = cr.column_id
ORDER BY 
    tp.name, fk.name;









-- Drop tables
DROP TABLE IF EXISTS Players;
DROP TABLE IF EXISTS Teams;
DROP TABLE IF EXISTS Matches;
DROP TABLE IF EXISTS Bookings;
DROP TABLE IF EXISTS Goals;
DROP TABLE IF EXISTS Managers;
DROP TABLE IF EXISTS Match_Results;
DROP TABLE IF EXISTS Player_Match;
DROP TABLE IF EXISTS Stadiums;
DROP TABLE IF EXISTS Team_Tournament;
DROP TABLE IF EXISTS Transfers;
