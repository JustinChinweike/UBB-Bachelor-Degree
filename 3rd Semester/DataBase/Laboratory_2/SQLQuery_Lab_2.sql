USE EPL_Management; 

GO 


-- Insert into Bookings, intentionally violating referential integrity by using non-existent match_id
INSERT INTO Bookings (booking_id, match_id, player_id, minute, card_type)
VALUES (12, 999, 3, 45, 'Yellow');

INSERT INTO Bookings (booking_id, match_id, player_id, minute, card_type)
VALUES (11, 1, 3, 45, 'Yellow');  -- Adding booking with ID 11

SELECT * FROM Bookings; 

-- Update player position using AND condition
UPDATE Players 
SET position = 'Midfielder' 
WHERE name = 'Raheem Sterling' AND nationality = 'English' ;

SELECT * FROM Players; 

-- Update team founding year with NOT and comparison
UPDATE Teams 
SET founding_year = 1879
WHERE team_name = 'Manchester United F.C ' AND founding_year IS NOT NULL ;

SELECT * FROM Teams; 


-- Update match stadium using OR condition
UPDATE Matches
SET match_stadium = 2
WHERE home_team_id = 1 OR away_team_id = 1;

SELECT * FROM Matches;

--- Delete records in two tables with conditions involving IS NULL, IN, BETWEEN, or LIKE.

-- Delete bookings where player has a specific name pattern
DELETE FROM Bookings
WHERE player_id IN (SELECT player_id FROM Players WHERE name LIKE 'Erling%' ) ; 

SELECT * FROM Bookings; 

-- Delete matches between certain dates

DELETE FROM Matches 
WHERE match_date BETWEEN '2024-11-21' AND '2024-11-22' ; 

SELECT * FROM Matches; 


-- Part 2: SELECT Queries

-- Combine lists of players from two teams
SELECT name FROM Players WHERE team_id = 10
UNION
SELECT name FROM Players WHERE team_id = 12;


-- Combine lists of players, including duplicates with UNION ALL
SELECT name FROM Players WHERE team_id = 13
UNION ALL
SELECT name FROM Players WHERE team_id = 17;


-- Players who played in both matches 1 and 2 using Bookings
SELECT player_id FROM Bookings WHERE match_id = 1
INTERSECT
SELECT player_id FROM Bookings WHERE match_id = 2;


-- Players in multiple matches using Bookings table
SELECT player_id FROM Bookings
WHERE match_id IN (1, 2)
GROUP BY player_id
HAVING COUNT(DISTINCT match_id) = 2;

SELECT * FROM Players;


-- INTERSECT: Players who play for both team 1 and team 2 (hypothetical example, assuming loan players)
SELECT player_id FROM Players WHERE team_id = 1
INTERSECT
SELECT player_id FROM Players WHERE team_id = 2;

-- IN: Matches with at least one player booked in it
SELECT match_id FROM Matches
WHERE match_id IN (SELECT match_id FROM Bookings);

--C 
-- EXCEPT: Players in team 13 but not in team 17
SELECT player_id FROM Players WHERE team_id = 13
EXCEPT
SELECT player_id FROM Players WHERE team_id = 17;


-- NOT IN: Matches without any goals scored
SELECT match_id FROM Matches
WHERE match_id NOT IN (SELECT match_id FROM Goals);


--D
-- Inner join to get players with team details
SELECT Players.name, Teams.team_name
FROM Players
INNER JOIN Teams ON Players.team_id = Teams.team_id;

-- Left join to find all teams and their stadiums, even if no stadium assigned
SELECT Teams.team_name, Stadiums.stadium_name
FROM Teams
LEFT JOIN Stadiums ON Teams.stadium_id = Stadiums.stadium_id;

-- Right join to get all managers and their associated teams (if any)
SELECT Managers.name AS manager_name, Teams.team_name
FROM Managers
RIGHT JOIN Teams ON Managers.manager_id = Teams.manager_id;


-- Full join across Teams and Matches to find teams that have played home or away
SELECT Teams.team_name, Matches.match_date
FROM Teams
FULL JOIN Matches ON Teams.team_id = Matches.home_team_id OR Teams.team_id = Matches.away_team_id;

--Joining Multiple Tables and Many-to-Many:

-- Join Teams, Matches, and Stadiums for match location details
SELECT Teams.team_name AS home_team, Matches.match_date, Stadiums.stadium_name
FROM Teams
INNER JOIN Matches ON Teams.team_id = Matches.home_team_id
INNER JOIN Stadiums ON Matches.match_stadium = Stadiums.stadium_id;


-- Join Teams with Team_Tournament and Tournaments for participation details
SELECT Teams.team_name, Tournaments.name AS tournament
FROM Teams
INNER JOIN Team_Tournament ON Teams.team_id = Team_Tournament.team_id
INNER JOIN Tournaments ON Team_Tournament.tournament_id = Tournaments.tournament_id;


--Problem e: Queries with INTERSECT and IN

--Query 1: Teams Participating in Both the Premier League and the FA Cup
 --It finds teams that are participating in both Premier League 
--(tournament_id = 1) and FA Cup (tournament_id = 2).

--Explanation:
--The query uses two subqueries, each checking for participation in 
--either the Premier League or the FA Cup.
--Teams must appear in both subqueries to satisfy both
--conditions in the WHERE clause, which ensures they’re 
--participating in both tournaments.

SELECT team_id, team_name 
FROM Teams
WHERE team_id IN (
    SELECT team_id 
    FROM Team_Tournament 
    WHERE tournament_id = 1
)
AND team_id IN (
    SELECT team_id 
    FROM Team_Tournament 
    WHERE tournament_id = 2
);





--Query 2: Teams with Players in Both Midfield and Forward Positions
--This query finds teams that have players in both Midfield and Forward positions. 
---It uses an IN operator with a nested subquery

--Explanation:
--The outer query selects team_id and team_name from the Teams table.
--The first subquery (SELECT team_id FROM Players WHERE position = 'Midfielder') 
--finds teams with at least one midfielder.
--The nested subquery (SELECT team_id FROM Players WHERE position = 'Forward')
--ensures that the team also has at least one player in the forward position.


SELECT team_id, team_name 
FROM Teams
WHERE team_id IN (
    SELECT team_id
    FROM Players
    WHERE position = 'Midfielder'
      AND team_id IN (
          SELECT team_id
          FROM Players
          WHERE position = 'Forward'
      )
);


-- Problem f: Two Queries Using the EXISTS Operator in the WHERE Clause

--Query 1: Find Teams with Managers from Specific Countries
--This query finds all teams whose managers are from England.

--Explanation:
--The outer query retrieves team_name from the Teams table.
--The EXISTS clause checks if there’s a Manager for each team who is English.
--The inner subquery uses the Teams.manager_id = Managers.manager_id condition
--to match teams with their managers  and filters for managers with English nationality.

SELECT team_name 
FROM Teams 
WHERE EXISTS (
    SELECT 1 
    FROM Managers 
    WHERE Managers.manager_id = Teams.manager_id 
      AND Managers.nationality = 'English'
);


--Query 2: Find Matches Where a Forward Scored a Goal
--This query finds matches where at least one goal was 
--scored by a player in the Forward position.
SELECT match_id, match_date
FROM Matches
WHERE EXISTS (
    SELECT 1
    FROM Goals
    INNER JOIN Players ON Goals.player_id = Players.player_id
    WHERE Goals.match_id = Matches.match_id
      AND Players.position = 'Forward'
);







---Problem g: Two Queries with a Subquery in the FROM Clause

-- Query 1 - Average Goals Scored by Each Team

--Explanation and Analysis:
--The team_goals subquery in the FROM clause calculates total goals 
--scored by each team, whether they were the home or away team.
--By UNION ALL on home_team_goals and away_team_goals, 
--this subquery aggregates goals scored in all matches for each team.
--The main query then calculates the average goals scored by each team.

SELECT Teams.team_name, AVG(team_goals.total_goals) AS avg_goals
FROM Teams
JOIN (
    SELECT Matches.home_team_id AS team_id, Match_Results.home_team_goals AS total_goals
    FROM Match_Results
    JOIN Matches ON Matches.match_id = Match_Results.match_id
    UNION ALL
    SELECT Matches.away_team_id AS team_id, Match_Results.away_team_goals AS total_goals
    FROM Match_Results
    JOIN Matches ON Matches.match_id = Match_Results.match_id
) AS team_goals ON Teams.team_id = team_goals.team_id
GROUP BY Teams.team_name;



--Query 2 - List Players Who Played in Multiple Matches

--Explanation and Analysis:

--This query finds players who scored goals in multiple matches by counting the 
--number of goals each player scored.
--The subquery player_goal_counts aggregates goal_id by each
--player's name and provides a count.
--The main query filters out players who scored only once 
--(by retaining only those with a goal_count > 1).

SELECT player_name, goal_count
FROM (
    SELECT Players.name AS player_name, COUNT(Goals.goal_id) AS goal_count
    FROM Players
    JOIN Goals ON Players.player_id = Goals.player_id
    GROUP BY Players.name
) AS player_goal_counts
WHERE goal_count > 1;




--Problem h: Four Queries Using GROUP BY, Including HAVING with Subqueries

-- Query 1 - Counts how many teams are in each tournament.

--Explanation:
--This query groups by each tournament and counts how many teams are associated with each.
--It uses the GROUP BY clause with COUNT.

SELECT Tournaments.name AS tournament_name, COUNT(Team_Tournament.team_id) AS team_count
FROM Tournaments
JOIN Team_Tournament ON Tournaments.tournament_id = Team_Tournament.tournament_id
GROUP BY Tournaments.name;


--Query 2: Average Transfer Fee for Teams with High Transfer Fees
--(using GROUP BY and HAVING)

--This query finds teams with an average transfer fee greater than $40 Million.
Explanation:

--This query calculates the average transfer fee for each team and filters 
--out teams with an average transfer fee below $40 million.
--It uses GROUP BY with AVG and HAVING to filter based on the aggregated average.

SELECT Teams.team_name, AVG(Transfers.transfer_fee) AS avg_transfer_fee
FROM Teams
JOIN Transfers ON Teams.team_id = Transfers.to_team_id
GROUP BY Teams.team_name
HAVING AVG(Transfers.transfer_fee) > 40000000;



--Query 3: Teams with the Most Wins (using GROUP BY, HAVING, and a Subquery in HAVING)

--Explanation:
--This query finds the team with the most wins.
--The subquery in the HAVING clause finds the maximum number of wins.
--Only teams with a win count equal to the maximum are displayed.

SELECT Teams.team_name, COUNT(*) AS win_count
FROM Match_Results
JOIN Teams ON Match_Results.match_winner = Teams.team_id
GROUP BY Teams.team_name
HAVING COUNT(*) = (
    SELECT MAX(win_counts)
    FROM (
        SELECT match_winner, COUNT(*) AS win_counts
        FROM Match_Results
        GROUP BY match_winner
    ) AS team_win_counts
);



--Query 4: Players with Goals Above the Team Average (using GROUP BY, HAVING, 
--and a Subquery in HAVING)

SELECT Players.name, COUNT(Goals.goal_id) AS player_goals
FROM Players
JOIN Goals ON Players.player_id = Goals.player_id
GROUP BY Players.name
HAVING COUNT(Goals.goal_id) > (
    SELECT AVG(team_goals)
    FROM (
        SELECT team_id, COUNT(goal_id) AS team_goals
        FROM Goals
        JOIN Players ON Goals.player_id = Players.player_id
        GROUP BY team_id
    ) AS team_goal_stats
);


--Problem i: Queries Using ANY and ALL

-- Query 1: Teams with Transfers Higher Than Arsenal's Transfers (Using ANY)

--Explanation:
--We calculate the adjusted average transfer fee (AVG(transfer_fee) * 1.1)
--as an arithmetic expression in the SELECT clause.
--The WHERE clause uses ANY to filter teams with a transfer 
--fee higher than any fee of Arsenal (assumed team_id = 1),
--excluding Arsenal itself with AND team_id != 1.
--The query includes DISTINCT and ORDER BY.

SELECT DISTINCT team_name, AVG(transfer_fee) * 1.1 AS adjusted_avg_fee
FROM Teams
JOIN Transfers ON Teams.team_id = Transfers.to_team_id
WHERE transfer_fee > ANY (
    SELECT transfer_fee
    FROM Transfers
    WHERE to_team_id = 1
)
AND team_id != 1
ORDER BY adjusted_avg_fee DESC;



--Query 2: Managers with Contract Start Dates Earlier Than All English Managers (Using ALL)

SELECT name AS manager_name, nationality, contract_start_date
FROM Managers
WHERE contract_start_date < ALL (
    SELECT contract_start_date
    FROM Managers
    WHERE nationality = 'English'
);


-- Query 2: Managers with Contract Start Dates Earlier Than All English Managers

--Explanation:
--YEAR(CURRENT_DATE) - YEAR(contract_start_date) calculates the 
--number of years since the contract start date for each non-English manager.
--The subquery in the WHERE clause filters managers whose
--contract start date is earlier than any English manager’s start date.
--The ORDER BY years_since_contract DESC sorts the result
--by years since the contract start in descending order.

SELECT DISTINCT name AS manager_name, nationality,
       YEAR(CURRENT_DATE) - YEAR(contract_start_date) AS years_since_contract
FROM Managers
WHERE contract_start_date < ALL (
    SELECT contract_start_date
    FROM Managers
    WHERE nationality = 'English'
)
AND nationality != 'English'
ORDER BY years_since_contract DESC;


--Query 3: Players with Goals in Matches Where All Goals Exceed Team Average 
--(Using ANY and Aggregation)

--Explanation:

--The ANY operator is used in the subquery to identify goals by players on
--teams with more than one goal in matches.
--The arithmetic expression COUNT(Goals.goal_id) * 1.5 scales the goal count.
--WHERE includes conditions with AND and OR using parentheses.

SELECT DISTINCT Players.name, (COUNT(Goals.goal_id) * 1.5) AS weighted_goal_count
FROM Players
JOIN Goals ON Players.player_id = Goals.player_id
WHERE Goals.goal_id > ANY (
    SELECT goal_id
    FROM Goals AS sub_goals
    JOIN Players AS sub_players ON sub_goals.player_id = sub_players.player_id
    WHERE sub_players.team_id = Players.team_id
    AND sub_goals.goal_id > 1
)
GROUP BY Players.name
HAVING COUNT(Goals.goal_id) > 1;


-- Query 4: Matches Without Certain Teams 

--Explanation:

--This query retrieves matches where neither the home team nor the away 
--team has a name starting with "A" or was founded before 1900.
--The SELECT clause includes an arithmetic expression 
--(home_team_id + away_team_id) as total_team_ids to sum the team IDs.
--It uses NOT IN subqueries to exclude specific teams, 
--and TOP with ORDER BY to limit and sort the results by total_team_ids.

SELECT TOP 5 Matches.match_id, Matches.match_date, 
       (Matches.home_team_id + Matches.away_team_id) AS total_team_ids
FROM Matches
WHERE home_team_id NOT IN (
    SELECT team_id
    FROM Teams
    WHERE team_name LIKE 'A%' OR founding_year < 1900
)
AND away_team_id NOT IN (
    SELECT team_id
    FROM Teams
    WHERE team_name LIKE 'A%' OR founding_year < 1900
)
ORDER BY total_team_ids DESC;

