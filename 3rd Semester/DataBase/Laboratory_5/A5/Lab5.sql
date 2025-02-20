USE EPL_Management
GO 

-- Create the tables
CREATE TABLE Team (
    team_id INT PRIMARY KEY, -- aid
	team_name VARCHAR(100),
	founded_year INT UNIQUE -- a2
);

CREATE TABLE Player (
    player_id INT PRIMARY KEY,
    player_name VARCHAR(100),
    age INT UNIQUE, -- b2 
);



CREATE TABLE Match (
    match_id INT PRIMARY KEY, -- cid
    team_id INT, --aid
    player_id INT,-- bid
    FOREIGN KEY (team_id) REFERENCES Team(team_id),
    FOREIGN KEY (player_id) REFERENCES Player(player_id)
);


-- Populate the tables with data
INSERT INTO Team (team_id, team_name, founded_year) 
VALUES 
    (1, 'Manchester United', 1878),
    (2, 'Arsenal', 1886),
    (3, 'Chelsea', 1905);

INSERT INTO Player (player_id, player_name, age) 
VALUES 
    (1, 'Marcus Rashford', 25),
    (2, 'Bukayo Saka', 21),
    (3, 'Mason Mount', 24);

INSERT INTO Match (match_id, team_id, player_id) 
VALUES 
    (1, 1, 1),
    (2, 2, 2),
    (3, 3, 3);

-- a. Queries on Team (Table Ta) to produce the required execution plans

-- Clustered index scan
-- This query scans the entire table using the clustered index on the primary key (team_id).
SELECT team_id, team_name
FROM Team;

-- Clustered index seek
-- This query retrieves specific rows using a range search on the clustered index.
SELECT *
FROM Team
WHERE team_id BETWEEN 1 AND 2;

-- Nonclustered index scan
-- Create a nonclustered index on 'founded_year' for better performance when retrieving this column.
CREATE NONCLUSTERED INDEX IX_Team_Founded_Year ON Team(founded_year);

-- This query scans the nonclustered index to retrieve all values of 'founded_year'.
SELECT founded_year
FROM Team;

-- Nonclustered index seek
-- This query performs a seek operation on the nonclustered index to retrieve a specific range of years.
SELECT founded_year
FROM Team
WHERE founded_year BETWEEN 1880 AND 1900;

-- Key lookup
-- This query combines an index seek with a key lookup to retrieve additional columns based on a nonclustered index.
SELECT *
FROM Team
WHERE founded_year = 1886;

-- b. Query on Player (Table Tb) with WHERE clause

-- Query the Player table with a WHERE clause before creating an index.
SELECT age
FROM Player
WHERE age = 24;

-- Create a nonclustered index on the 'age' column to optimize queries with conditions on 'age'.
CREATE NONCLUSTERED INDEX IX_Player_Age ON Player(age);

-- Query the Player table again to observe the performance improvement with the index.
SELECT age
FROM Player
WHERE age = 24;

-- Drop the index after observing the execution plan to showcase performance differences.
DROP INDEX IX_Player_Age ON Player;

-- c. Create a view and reassess indexes

-- Create a view to join the Match, Team, and Player tables for meaningful queries.
CREATE VIEW Match_View AS
SELECT 
    m.match_id, 
    t.team_name AS team_name, 
    p.player_name AS player_name
FROM Match m
INNER JOIN Team t ON m.team_id = t.team_id
INNER JOIN Player p ON m.player_id = p.player_id;

-- Query the view to find matches where 'Manchester United' is associated with a player.
SELECT *
FROM Match_View
WHERE team_name = 'Manchester United';

-- Index optimization
-- Create a nonclustered index on 'team_name' to optimize searches for specific team names.
CREATE NONCLUSTERED INDEX IX_Team_Name ON Team(team_name);

-- Reassess the query on the view to observe performance improvements.
SELECT *
FROM Match_View
WHERE team_name = 'Manchester United';

-- Drop the index after performance evaluation to demonstrate differences in execution plans.
DROP INDEX IX_Team_Name ON Team;