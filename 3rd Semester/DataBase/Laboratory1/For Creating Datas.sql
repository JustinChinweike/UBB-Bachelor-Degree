USE EPL_Management;
GO
-- Insert sample teams
INSERT INTO Teams (team_id, team_name, stadium_id, manager_id, founding_year) 
VALUES
(1,'Arsenal', 1, 1, 1886),
(2,'Aston Villa', 2, 2, 1874),
(3,'Bournemouth', 3, 3, 1899),
(4,'Brentford', 4, 4, 1889),
(5,'Brighton', 5, 5, 1901),
(6,'Burnley', 6, 6, 1882),
(7,'Chelsea', 7, 7, 1905),
(8,'Crystal Palace', 8, 8, 1905),
(9,'Everton', 9, 9, 1878),
(10,'Fulham', 10, 10, 1879),
(11,'Liverpool', 11, 11, 1892),
(12,'Manchester City', 12, 12, 1880),
(13,'Manchester United', 13, 13, 1878),
(14,'Newcastle United', 14, 14, 1892),
(15,'Nottingham Forest', 15, 15, 1865),
(16,'Sheffield United', 16, 16, 1889),
(17,'Tottenham Hotspur', 17, 17, 1882),
(18,'West Ham United', 18, 18, 1895),
(19,'Wolves', 19, 19, 1877),
(20, 'Luton Town', 20, 20, 1885);

SELECT * FROM Teams; 




INSERT INTO Managers (manager_id, name, nationality, contract_start_date) VALUES 
(1, 'Mikel Arteta', 'Spanish',  '2019-12-20'),
(2, 'David Moyes', 'Scottish',  '2020-12-29'),
(3, 'Roberto De Zerbi', 'Italian',  '2022-09-16'),
(4, 'Mauricio Pochettino', 'Argentinian',  '2023-07-01'),
(5, 'Eddie Howe', 'English',  '2020-08-30'),
(6, 'Jürgen Klopp', 'German', '2015-10-08'),
(7, 'Pep Guardiola', 'Spanish', '2016-07-01'),
(8, 'Unai Emery', 'Spanish',  '2023-10-31'),
(9, 'Brendan Rodgers', 'Northern Irish',  '2019-02-27'),
(10, 'Marco Silva', 'Portuguese',  '2021-06-30'),
(11, 'Gary O’Neil', 'English',  '2022-08-12'),
(12, 'Andoni Iraola', 'Spanish', '2023-06-01'),
(13, 'Vincent Kompany', 'Belgian', '2022-06-01'),
(14, 'Jesse Marsch', 'American', '2022-02-28'),
(15, 'Thomas Frank', 'Danish', '2018-10-16'),
(16, 'Scott Parker', 'English', '2022-06-28'),
(17, 'Sean Dyche', 'English',  '2023-02-01'),
(18, 'Nuno Espírito Santo', 'Portuguese', '2021-06-30'),
(19, 'Antonio Conte', 'Italian', '2021-11-02'),
(20, 'Ruben Amorim', 'Portuguese', '2023-06-01');

SELECT * FROM Managers; 


-- Insert top 20 EPL players into Players table
INSERT INTO Players (player_id, name, position, nationality, team_id, date_of_birth) VALUES 
(1,'Erling Haaland', 'Forward', 'Norwegian', 12, '2000-07-21'),
(2,'Harry Kane', 'Forward', 'English', 17, '1993-07-28'),
(3, 'Kevin De Bruyne', 'Midfielder', 'Belgian', 12, '1991-06-28'),
(4, 'Mohamed Salah', 'Forward', 'Egyptian', 11, '1992-06-15'),
(5, 'Bruno Fernandes', 'Midfielder', 'Portuguese', 13, '1994-09-08'),
(6, 'Bukayo Saka', 'Forward', 'English', 1, '2001-09-05'),
(7, 'Martin Ødegaard', 'Midfielder', 'Norwegian', 1, '1998-12-17'),
(8, 'Son Heung-min', 'Forward', 'South Korean', 17, '1992-07-08'),
(9, 'Declan Rice', 'Midfielder', 'English', 1, '1999-01-14'),
(10, 'Virgil van Dijk', 'Defender', 'Dutch', 11, '1991-07-08'),
(11, 'Marcus Rashford', 'Forward', 'English', 13, '1997-10-31'),
(12, 'Raúl Jiménez', 'forward', 'Mexican', 10, '1991-05-05'),
(13, 'James Maddison', 'Midfielder', 'English', 17, '1996-11-23'),
(14, 'Alisson Becker', 'Goalkeeper', 'Brazilian', 11, '1992-10-02'),
(15, 'Casemiro', 'Midfielder', 'Brazilian', 13, '1992-02-23'),
(16, 'Kai Havertz', 'Forward', 'German', 1, '1999-06-11'),
(17, 'Kieran Trippier', 'Defender', 'English', 17, '1990-09-19'),
(18, 'Rodri', 'Midfielder', 'Spanish', 12, '1996-06-22'),
(19, 'Nick Pope', 'Goalkeeper', 'English',14, '1992-04-19'),
(20, 'Emiliano Martínez', 'Goalkeeper', 'Argentine', 2, '1992-09-02'), 
(21, 'Reece James', 'Defender', 'English', 7, '1999-12-08'),
(22, 'Raheem Sterling', 'Forward', 'English', 7, '1994-12-08'),
(23, 'Enzo Fernandez', 'Midfielder', 'Argentine', 7, '2001-01-17'),
(24, 'Thiago Silva', 'Defender', 'Brazilian', 7, '1984-09-22');

SELECT * FROM Players;



-- Insert sample stadiums
INSERT INTO Stadiums (stadium_id, stadium_name, location, capacity) 
VALUES
(1,'Emirates Stadium', 'London', 60260),
(2,'Villa Park', 'Birmingham', 42785),
(3,'Vitality Stadium', 'Bournemouth', 11329),
(4,'Brentford Community Stadium', 'London', 17250),
(5,'Amex Stadium', 'Brighton', 30750),
(6,'Turf Moor', 'Burnley', 21401),
(7,'Stamford Bridge', 'London', 41837),
(8,'Selhurst Park', 'London', 25456),
(9,'Goodison Park', 'Liverpool', 39414),
(10,'Craven Cottage', 'London', 25700),
(11,'Anfield', 'Liverpool', 54074),
(12,'Etihad Stadium', 'Manchester', 53400),
(13,'Old Trafford', 'Manchester', 74879),
(14,'St James Park', 'Newcastle', 52305),
(15,'City Ground', 'Nottingham', 30446),
(16,'Bramall Lane', 'Sheffield', 32702),
(17,'Tottenham Hotspur Stadium', 'London', 62850),
(18,'London Stadium', 'London', 62500),
(19,'Molineux Stadium', 'Wolverhampton', 32050),
(20,'Kenilworth Road', 'Luton', 12000); 

SELECT * FROM Stadiums; 



-- Insert sample matches into Matches table
INSERT INTO Matches (match_id, home_team_id, away_team_id, match_date, match_stadium) VALUES 
(1, 1, 7, '2024-11-03', 1),   -- Arsenal vs Chelsea
(2, 3, 2, '2024-11-04', 3),   -- Bournemouth vs Aston Villa
(3, 4, 5, '2024-11-05', 4),   -- Brentford vs Brighton
(4, 6, 11, '2024-11-06', 6),  -- Burnley vs Liverpool
(5, 8, 9, '2024-11-07', 8),   -- Crystal Palace vs Everton
(6, 10, 1, '2024-11-08', 10), -- Fulham vs Arsenal
(7, 12, 13, '2024-11-09', 12), -- Man City vs Man United
(8, 7, 14, '2024-11-10', 7),  -- Chelsea vs Newcastle
(9, 5, 15, '2024-11-11', 5),  -- Brighton vs Nottingham Forest
(10, 18, 3, '2024-11-12', 18), -- West Ham vs Bournemouth
(11, 19, 16, '2024-11-13', 19), -- Wolves vs Sheffield United
(12, 20, 17, '2024-11-14', 20), -- Luton Town vs Tottenham
(13, 9, 6, '2024-11-15', 9),   -- Everton vs Burnley
(14, 14, 4, '2024-11-16', 14), -- Newcastle vs Brentford
(15, 17, 10, '2024-11-17', 17), -- Tottenham vs Fulham
(16, 15, 8, '2024-11-18', 15), -- Nottingham Forest vs Crystal Palace
(17, 13, 20, '2024-11-19', 13), -- Man United vs Luton Town
(18, 2, 12, '2024-11-20', 2),  -- Aston Villa vs Man City
(19, 16, 7, '2024-11-21', 16), -- Sheffield United vs Chelsea
(20, 11, 19, '2024-11-22', 11); -- Liverpool vs Wolves

SELECT * FROM Matches; 


-- Create the Match_Results 
INSERT INTO Match_Results (result_id, match_id, home_team_goals, away_team_goals, match_winner) VALUES
(1, 1, 2, 1, 1),    -- Arsenal 2 - 1 Chelsea (Arsenal wins)
(2, 2, 1, 3, 2),    -- Bournemouth 1 - 3 Aston Villa (Aston Villa wins)
(3, 3, 1, 1, NULL), -- Brentford 1 - 1 Brighton (Draw)
(4, 4, 2, 2, NULL), -- Burnley 2 - 2 Liverpool (Draw)
(5, 5, 1, 0, 8),    -- Crystal Palace 1 - 0 Everton (Crystal Palace wins)
(6, 6, 0, 2, 1),    -- Fulham 0 - 2 Arsenal (Arsenal wins)
(7, 7, 1, 2, 13),   -- Man City 1 - 2 Man United (Man United wins)
(8, 8, 2, 1, 7),    -- Chelsea 2 - 1 Newcastle (Chelsea wins)
(9, 9, 3, 0, 5),    -- Brighton 3 - 0 Nottingham Forest (Brighton wins)
(10, 10, 1, 1, NULL),-- West Ham 1 - 1 Bournemouth (Draw)
(11, 11, 2, 3, 16),  -- Wolves 2 - 3 Sheffield United (Sheffield United wins)
(12, 12, 0, 1, 17),  -- Luton Town 0 - 1 Tottenham (Tottenham wins)
(13, 13, 1, 2, 6),   -- Everton 1 - 2 Burnley (Burnley wins)
(14, 14, 2, 0, 14),  -- Newcastle 2 - 0 Brentford (Newcastle wins)
(15, 15, 1, 2, 10),  -- Tottenham 1 - 2 Fulham (Fulham wins)
(16, 16, 0, 0, NULL),-- Nottingham Forest 0 - 0 Crystal Palace (Draw)
(17, 17, 3, 1, 13),  -- Man United 3 - 1 Luton Town (Man United wins)
(18, 18, 2, 2, NULL),-- Aston Villa 2 - 2 Man City (Draw)
(19, 19, 1, 1, NULL),-- Sheffield United 1 - 1 Chelsea (Draw)
(20, 20, 2, 0, 11);  -- Liverpool 2 - 0 Wolves (Liverpool wins)

SELECT * FROM Match_Results;



-- Insert sample goal data into the Goals table
INSERT INTO Goals (goal_id, match_id, player_id, minute, type_of_goal) VALUES
(1, 1, 10, 15, 'Header'),    -- Arsenal vs Chelsea, player_id 10 scored at 15th minute with a header
(2, 1, 11, 30, 'Penalty'),    -- Arsenal vs Chelsea, player_id 11 scored at 30th minute with a penalty
(3, 2, 22, 5, 'Open Play'),   -- Bournemouth vs Aston Villa, player_id 22 scored at 5th minute from open play
(4, 3, 15, 80, 'Long Range'),  -- Brentford vs Brighton, player_id 15 scored at 80th minute with a long-range shot
(5, 4, 16, 43, 'Header'),     -- Burnley vs Liverpool, player_id 16 scored at 43rd minute with a header
(6, 5, 6, 27, 'Open Play'),    -- Crystal Palace vs Everton, player_id 6 scored at 27th minute from open play
(7, 6, 3, 12, 'Free Kick'),   -- Fulham vs Arsenal, player_id 3 scored at 12th minute from a free kick
(8, 7, 12, 22, 'Counter Attack'),  -- Man City vs Man United, player_id 12 scored at 22nd minute from a counter attack
(9, 8, 14, 90, 'Header'),     -- Chelsea vs Newcastle, player_id 14 scored at 90th minute with a header
(10, 9, 18, 68, 'Open Play'),    -- Brighton vs Nottingham Forest, player_id 18 scored at 68th minute from open play
(11, 10, 19, 33, 'Penalty'),     -- West Ham vs Bournemouth, player_id 19 scored at 33rd minute with a penalty
(12, 11, 17, 50, 'Open Play'),  -- Wolves vs Sheffield United, player_id 17 scored at 50th minute from open play
(13, 12, 21, 75, 'Long Range'),  -- Luton Town vs Tottenham, player_id 21 scored at 75th minute with a long-range shot
(14, 13, 20, 10, 'Open Play'),   -- Everton vs Burnley, player_id 20 scored at 10th minute from open play
(15, 14, 24, 59, 'Header'),     -- Newcastle vs Brentford, player_id 24 scored at 59th minute with a header
(16, 15, 23, 35, 'Open Play'),  -- Tottenham vs Fulham, player_id 23 scored at 35th minute from open play
(17, 16, 5, 25, 'Own Goal'),    -- Nottingham Forest vs Crystal Palace, player_id 5 scored an own goal at 25th minute
(18, 17, 8, 88, 'Counter Attack'),  -- Man United vs Luton Town, player_id 8 scored at 88th minute from a counter attack
(19, 18, 13, 76, 'Header'),     -- Aston Villa vs Man City, player_id 13 scored at 76th minute with a header
(20, 19, 9, 47, 'Open Play'),   -- Sheffield United vs Chelsea, player_id 9 scored at 47th minute from open play
(21, 20, 7, 14, 'Penalty');     -- Liverpool vs Wolves, player_id 7 scored at 14th minute with a penalty

SELECT * FROM Goals; 


-- Insert sample booking data into the Bookings table
INSERT INTO Bookings (booking_id,match_id , player_id, minute, card_type) VALUES
(1, 1, 10, 45, 'Yellow'),   -- Arsenal vs Chelsea, player_id 10 booked at 45th minute
(2, 1, 11, 89, 'Red'),      -- Arsenal vs Chelsea, player_id 11 sent off at 89th minute
(3, 2, 22, 30, 'Yellow'),   -- Bournemouth vs Aston Villa, player_id 22 booked at 30th minute
(4, 3, 15, 68, 'Yellow'),   -- Brentford vs Brighton, player_id 15 booked at 68th minute
(5, 4, 16, 78, 'Yellow'),   -- Burnley vs Liverpool, player_id 16 booked at 78th minute
(6, 5, 6, 12, 'Yellow'),    -- Crystal Palace vs Everton, player_id 6 booked at 12th minute
(7, 6, 3, 55, 'Red'),       -- Fulham vs Arsenal, player_id 3 sent off at 55th minute
(8, 7, 12, 83, 'Yellow'),   -- Man City vs Man United, player_id 12 booked at 83rd minute
(9, 8, 14, 42, 'Yellow'),    -- Chelsea vs Newcastle, player_id 14 booked at 42nd minute
(10, 9, 18, 90, 'Yellow');    -- Brighton vs Nottingham Forest, player_id 18 booked at 90th minute

SELECT * FROM Bookings; 


-- Insert sample tournaments into the Tournaments table
INSERT INTO Tournaments (tournament_id, name,  season_start, season_end) VALUES
(1, 'Premier League', 2023, 2024),
(2, 'FA Cup', 2023, 2024),
(3, 'EFL Cup', 2023, 2024),
(4, 'UEFA Champions League', 2023, 2024),
(5, 'UEFA Europa League', 2023, 2024),
(6, 'FA Community Shield', 2023, 2023),
(7, 'FIFA Club World Cup', 2023, 2023),
(8, 'International Champions Cup', 2023, 2023);

SELECT * FROM Tournaments; 


-- Insert sample data into the Transfers table with only EPL teams
INSERT INTO Transfers (transfer_id, player_id, from_team_id, to_team_id, transfer_fee, transfer_date) VALUES
(1, 9, 18, 1, 57500000.00, '2023-07-01'),    -- Declan Rice from West Ham United (18) to Arsenal (1)
(2, 16, 7, 1, 30000000.00, '2023-07-10'),   -- Kai Havertz from Chelsea (7) to Arsenal (1)
(3, 13, 15, 17, 40000000.00, '2023-08-01'),  -- James Maddison from Leicester City (15) to Tottenham Hotspur (17)
(4, 22, 11, 7, 45000000.00, '2023-08-10'),   -- Raheem Sterling from Liverpool (11) to Chelsea (7)
(5, 6, 7, 1, 20000000.00, '2023-08-18');     -- Bukayo Saka from Chelsea (7) to Arsenal (1)

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