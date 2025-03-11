USE EPL_Management2;
GO


-- Insert sample stadiums
INSERT INTO Stadiums (stadium_name, location, capacity) 
VALUES
('Emirates Stadium', 'London', 60260),
('Villa Park', 'Birmingham', 42785),
('Vitality Stadium', 'Bournemouth', 11329),
('Brentford Community Stadium', 'London', 17250),
('Amex Stadium', 'Brighton', 30750),
('Turf Moor', 'Burnley', 21401),
('Stamford Bridge', 'London', 41837),
('Selhurst Park', 'London', 25456),
('Goodison Park', 'Liverpool', 39414),
('Craven Cottage', 'London', 25700),
('Anfield', 'Liverpool', 54074),
('Etihad Stadium', 'Manchester', 53400),
('Old Trafford', 'Manchester', 74879),
('St James Park', 'Newcastle', 52305),
('City Ground', 'Nottingham', 30446),
('Bramall Lane', 'Sheffield', 32702),
('Tottenham Hotspur Stadium', 'London', 62850),
('London Stadium', 'London', 62500),
('Molineux Stadium', 'Wolverhampton', 32050),
('Kenilworth Road', 'Luton', 12000); 

SELECT * FROM Stadiums; 



-- Insert sample teams
INSERT INTO Teams (team_name, stadium_id,  founding_year) 
VALUES
('Arsenal', 1,  1886),
('Aston Villa', 2,  1874),
('Bournemouth', 3,  1899),
('Brentford', 4,  1889),
('Brighton', 5,  1901),
('Burnley', 6,  1882),
('Chelsea', 7,  1905),
('Crystal Palace', 8,  1905),
('Everton', 9,  1878),
('Fulham', 10, 1879),
('Liverpool', 11,  1892),
('Manchester City', 12,  1880),
('Manchester United', 13,  1878),
('Newcastle United', 14,  1892),
('Nottingham Forest', 15,  1865),
('Sheffield United', 16, 1889),
('Tottenham Hotspur', 17,  1882),
('West Ham United', 18,1895),
('Wolves', 19,1877),
('Luton Town', 20, 1885);

SELECT * FROM Teams; 




INSERT INTO Managers (name, nationality, contract_start_date) VALUES 
('Mikel Arteta', 'Spanish',  '2019-12-20'),
('David Moyes', 'Scottish',  '2020-12-29'),
('Roberto De Zerbi', 'Italian',  '2022-09-16'),
('Mauricio Pochettino', 'Argentinian',  '2023-07-01'),
('Eddie Howe', 'English',  '2020-08-30'),
('Jürgen Klopp', 'German', '2015-10-08'),
('Pep Guardiola', 'Spanish', '2016-07-01'),
('Unai Emery', 'Spanish',  '2023-10-31'),
('Brendan Rodgers', 'Northern Irish',  '2019-02-27'),
('Marco Silva', 'Portuguese',  '2021-06-30'),
('Gary O’Neil', 'English',  '2022-08-12'),
('Andoni Iraola', 'Spanish', '2023-06-01'),
('Vincent Kompany', 'Belgian', '2022-06-01'),
('Jesse Marsch', 'American', '2022-02-28'),
('Thomas Frank', 'Danish', '2018-10-16'),
('Scott Parker', 'English', '2022-06-28'),
('Sean Dyche', 'English',  '2023-02-01'),
('Nuno Espírito Santo', 'Portuguese', '2021-06-30'),
('Antonio Conte', 'Italian', '2021-11-02'),
('Ruben Amorim', 'Portuguese', '2023-06-01');

SELECT * FROM Managers; 


-- Insert top 20 EPL players into Players table
INSERT INTO Players (name, position, nationality, team_id, date_of_birth) VALUES 
('Erling Haaland', 'Forward', 'Norwegian', 12, '2000-07-21'),
('Harry Kane', 'Forward', 'English', 17, '1993-07-28'),
('Kevin De Bruyne', 'Midfielder', 'Belgian', 12, '1991-06-28'),
('Mohamed Salah', 'Forward', 'Egyptian', 11, '1992-06-15'),
('Bruno Fernandes', 'Midfielder', 'Portuguese', 13, '1994-09-08'),
('Bukayo Saka', 'Forward', 'English', 1, '2001-09-05'),
('Martin Ødegaard', 'Midfielder', 'Norwegian', 1, '1998-12-17'),
('Son Heung-min', 'Forward', 'South Korean', 17, '1992-07-08'),
( 'Declan Rice', 'Midfielder', 'English', 1, '1999-01-14'),
('Virgil van Dijk', 'Defender', 'Dutch', 11, '1991-07-08'),
('Marcus Rashford', 'Forward', 'English', 13, '1997-10-31'),
('Raúl Jiménez', 'forward', 'Mexican', 10, '1991-05-05'),
('James Maddison', 'Midfielder', 'English', 17, '1996-11-23'),
('Alisson Becker', 'Goalkeeper', 'Brazilian', 11, '1992-10-02'),
('Casemiro', 'Midfielder', 'Brazilian', 13, '1992-02-23'),
('Kai Havertz', 'Forward', 'German', 1, '1999-06-11'),
('Kieran Trippier', 'Defender', 'English', 17, '1990-09-19'),
('Rodri', 'Midfielder', 'Spanish', 12, '1996-06-22'),
('Nick Pope', 'Goalkeeper', 'English',14, '1992-04-19'),
('Emiliano Martínez', 'Goalkeeper', 'Argentine', 2, '1992-09-02'), 
('Reece James', 'Defender', 'English', 7, '1999-12-08'),
('Raheem Sterling', 'Forward', 'English', 7, '1994-12-08'),
('Enzo Fernandez', 'Midfielder', 'Argentine', 7, '2001-01-17'),
('Thiago Silva', 'Defender', 'Brazilian', 7, '1984-09-22');

SELECT * FROM players ;



-- Insert sample matches into Matches table
INSERT INTO Matches (home_team_id, away_team_id, match_date, match_stadium) VALUES 
( 1, 7, '2024-11-03', 1),   -- Arsenal vs Chelsea
( 3, 2, '2024-11-04', 3),   -- Bournemouth vs Aston Villa
( 4, 5, '2024-11-05', 4),   -- Brentford vs Brighton
( 6, 11, '2024-11-06', 6),  -- Burnley vs Liverpool
( 8, 9, '2024-11-07', 8),   -- Crystal Palace vs Everton
( 10, 1, '2024-11-08', 10), -- Fulham vs Arsenal
( 12, 13, '2024-11-09', 12), -- Man City vs Man United
( 7, 14, '2024-11-10', 7),  -- Chelsea vs Newcastle
( 5, 15, '2024-11-11', 5),  -- Brighton vs Nottingham Forest
( 18, 3, '2024-11-12', 18);  -- West Ham vs Bournemouth

SELECT * FROM Matches; 




-- Create the Match_Results 
INSERT INTO Match_Results (match_id, home_team_goals, away_team_goals, match_winner) VALUES
( 1, 2, 1, 1),    -- Arsenal 2 - 1 Chelsea (Arsenal wins)
( 2, 1, 3, 2),    -- Bournemouth 1 - 3 Aston Villa (Aston Villa wins)
( 3, 1, 1, NULL), -- Brentford 1 - 1 Brighton (Draw)
( 4, 2, 2, NULL), -- Burnley 2 - 2 Liverpool (Draw)
( 5, 1, 0, 8),    -- Crystal Palace 1 - 0 Everton (Crystal Palace wins)
( 6, 0, 2, 1),    -- Fulham 0 - 2 Arsenal (Arsenal wins)
( 7, 1, 2, 13),   -- Man City 1 - 2 Man United (Man United wins)
( 8, 2, 1, 7),    -- Chelsea 2 - 1 Newcastle (Chelsea wins)
( 9, 3, 0, 5),    -- Brighton 3 - 0 Nottingham Forest (Brighton wins)
( 10, 1, 1, NULL); -- West Ham 1 - 1 Bournemouth (Draw)

USE EPL_Management2; 
GO
SELECT * FROM Match_Results;



-- Insert sample goal data into the Goals table
INSERT INTO Goals (match_id, player_id, minute, type_of_goal) VALUES
(1, 10, 15, 'Header'),    -- Arsenal vs Chelsea, player_id 10 scored at 15th minute with a header
(1, 11, 30, 'Penalty'),    -- Arsenal vs Chelsea, player_id 11 scored at 30th minute with a penalty
( 2, 22, 5, 'Open Play'),   -- Bournemouth vs Aston Villa, player_id 22 scored at 5th minute from open play
( 3, 15, 80, 'Long Range'),  -- Brentford vs Brighton, player_id 15 scored at 80th minute with a long-range shot
( 4, 16, 43, 'Header'),     -- Burnley vs Liverpool, player_id 16 scored at 43rd minute with a header
( 5, 6, 27, 'Open Play'),    -- Crystal Palace vs Everton, player_id 6 scored at 27th minute from open play
( 6, 3, 12, 'Free Kick'),   -- Fulham vs Arsenal, player_id 3 scored at 12th minute from a free kick
( 7, 12, 22, 'Counter Attack'),  -- Man City vs Man United, player_id 12 scored at 22nd minute from a counter attack
( 8, 14, 90, 'Header'),     -- Chelsea vs Newcastle, player_id 14 scored at 90th minute with a header
( 9, 18, 68, 'Open Play');   -- Brighton vs Nottingham Forest, player_id 18 scored at 68th minute from open play

SELECT * FROM Goals; 



-- Insert sample booking data into the Bookings table
INSERT INTO Bookings (match_id , player_id, minute, card_type) VALUES
( 1, 10, 45, 'Yellow'),   -- Arsenal vs Chelsea, player_id 10 booked at 45th minute
( 1, 11, 89, 'Red'),      -- Arsenal vs Chelsea, player_id 11 sent off at 89th minute
( 2, 22, 30, 'Yellow'),   -- Bournemouth vs Aston Villa, player_id 22 booked at 30th minute
( 3, 15, 68, 'Yellow'),   -- Brentford vs Brighton, player_id 15 booked at 68th minute
( 4, 16, 78, 'Yellow'),   -- Burnley vs Liverpool, player_id 16 booked at 78th minute
( 5, 6, 12, 'Yellow'),    -- Crystal Palace vs Everton, player_id 6 booked at 12th minute
( 6, 3, 55, 'Red'),       -- Fulham vs Arsenal, player_id 3 sent off at 55th minute
( 7, 12, 83, 'Yellow'),   -- Man City vs Man United, player_id 12 booked at 83rd minute
( 8, 14, 42, 'Yellow'),    -- Chelsea vs Newcastle, player_id 14 booked at 42nd minute
( 9, 18, 90, 'Yellow');    -- Brighton vs Nottingham Forest, player_id 18 booked at 90th minute

SELECT * FROM Bookings; 



-- Insert sample tournaments into the Tournaments table
INSERT INTO Tournaments (name,  season_start, season_end) VALUES
('Premier League', 2023, 2024),
('FA Cup', 2023, 2024),
('EFL Cup', 2023, 2024),
('UEFA Champions League', 2023, 2024),
('UEFA Europa League', 2023, 2024),
('FA Community Shield', 2023, 2023),
( 'FIFA Club World Cup', 2023, 2023),
( 'International Champions Cup', 2023, 2023);

SELECT * FROM Tournaments; 



-- Insert sample data into the Transfers table with only EPL teams
INSERT INTO Transfers (player_id, from_team_id, to_team_id, transfer_fee, transfer_date) VALUES
( 9, 18, 1, 57500000.00, '2023-07-01'),    -- Declan Rice from West Ham United (18) to Arsenal (1)
( 16, 7, 1, 30000000.00, '2023-07-10'),   -- Kai Havertz from Chelsea (7) to Arsenal (1)
( 13, 15, 17, 40000000.00, '2023-08-01'),  -- James Maddison from Leicester City (15) to Tottenham Hotspur (17)
( 22, 11, 7, 45000000.00, '2023-08-10'),   -- Raheem Sterling from Liverpool (11) to Chelsea (7)
( 6, 7, 1, 20000000.00, '2023-08-18');     -- Bukayo Saka from Chelsea (7) to Arsenal (1)

SELECT * FROM Transfers; 



-- Insert sample data into the Team_Tournament table
INSERT INTO Team_Tournament (team_id, tournament_id) VALUES
(1, 1),  -- Arsenal in Premier League 2023/24
(1, 2),  -- Arsenal in FA Cup 2023/24
(1, 4),  -- Arsenal in UEFA Champions League 2023/24
(2, 1),  -- Aston Villa in Premier League 2023/24
(2, 2),  -- Aston Villa in FA Cup 2023/24
(2, 3),  -- Aston Villa in EFL Cup 2023/24
(3, 1),  -- Bournemouth in Premier League 2023/24
(3, 2),  -- Bournemouth in FA Cup 2023/24
(4, 1),  -- Brentford in Premier League 2023/24
(4, 3),  -- Brentford in EFL Cup 2023/24
(5, 1),  -- Brighton in Premier League 2023/24
(5, 4),  -- Brighton in UEFA Champions League 2023/24
(6, 1),  -- Burnley in Premier League 2023/24
(6, 2),  -- Burnley in FA Cup 2023/24
(7, 1),  -- Chelsea in Premier League 2023/24
(7, 4),  -- Chelsea in UEFA Champions League 2023/24
(8, 1),  -- Crystal Palace in Premier League 2023/24
(8, 2),  -- Crystal Palace in FA Cup 2023/24
(9, 1),  -- Everton in Premier League 2023/24
(9, 2),  -- Everton in FA Cup 2023/24
(10, 1), -- Fulham in Premier League 2023/24
(10, 3), -- Fulham in EFL Cup 2023/24
(11, 1), -- Liverpool in Premier League 2023/24
(11, 4), -- Liverpool in UEFA Champions League 2023/24
(12, 1), -- Manchester City in Premier League 2023/24
(12, 6), -- Manchester City in FA Community Shield 2023/24
(13, 1), -- Manchester United in Premier League 2023/24
(13, 4), -- Manchester United in UEFA Champions League 2023/24
(14, 1), -- Newcastle United in Premier League 2023/24
(14, 5), -- Newcastle United in UEFA Europa League 2023/24
(15, 1), -- Nottingham Forest in Premier League 2023/24
(16, 1), -- Sheffield United in Premier League 2023/24
(17, 1), -- Tottenham Hotspur in Premier League 2023/24
(17, 2), -- Tottenham Hotspur in FA Cup 2023/24
(18, 1), -- West Ham United in Premier League 2023/24
(18, 5), -- West Ham United in UEFA Europa League 2023/24
(19, 1), -- Wolves in Premier League 2023/24
(20, 1); -- Luton Town in Premier League 2023/24

SELECT * FROM Team_Tournament; 