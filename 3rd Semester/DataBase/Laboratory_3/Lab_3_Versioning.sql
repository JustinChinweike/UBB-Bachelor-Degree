USE EPL_Management; 

GO 


   --- Current State and Version Management

-- Table: current_state
CREATE TABLE current_state (
    current_version INT NOT NULL
);
-- Initialize current version to 0
INSERT INTO current_state (current_version) VALUES (0);

-- Table: switch_state
CREATE TABLE switch_state (
    procedure_used NVARCHAR(50),
    from_version INT,
    to_version INT,
    short_description NVARCHAR(255),
    parameters NVARCHAR(MAX)
);

SELECT * FROM switch_state; 


        
		-- 3. Version Transition Stored Procedure

-- spSwitchVersion
--Handles schema transitions based on the current_state and switch_state tables

CREATE PROCEDURE spSwitchVersion
    @TargetVersion INT
AS
BEGIN
    BEGIN TRY
        -- Declare variables
        DECLARE @CurrentVersion INT;
        DECLARE @Procedure NVARCHAR(50);
        DECLARE @Parameters NVARCHAR(MAX);
        DECLARE @SQL NVARCHAR(MAX);

        -- Fetch the current version
        SELECT @CurrentVersion = current_version FROM current_state;

        -- Validate target version
        IF NOT EXISTS (
            SELECT 1 FROM switch_state
            WHERE from_version = @CurrentVersion OR to_version = @TargetVersion
        )
        BEGIN
            RAISERROR('Invalid target version.', 16, 1);
            RETURN;
        END

        -- Loop until the current version equals the target version
        WHILE @CurrentVersion <> @TargetVersion
        BEGIN
            IF @TargetVersion > @CurrentVersion
            BEGIN
                -- Forward transition
                SELECT @Procedure = procedure_used, @Parameters = parameters
                FROM switch_state
                WHERE from_version = @CurrentVersion AND to_version = @CurrentVersion + 1;

                SET @SQL = 'EXEC ' + @Procedure + ' ' + @Parameters;
                EXEC sp_executesql @SQL;

                UPDATE current_state SET current_version = current_version + 1;
            END
            ELSE
            BEGIN
                -- Reverse transition
                SELECT @Procedure = procedure_used, @Parameters = parameters
                FROM switch_state
                WHERE from_version = @CurrentVersion AND to_version = @CurrentVersion - 1;

                SET @SQL = 'EXEC ' + @Procedure + ' ' + @Parameters;
                EXEC sp_executesql @SQL;

                UPDATE current_state SET current_version = current_version - 1;
            END;

            SELECT @CurrentVersion = current_version FROM current_state;
        END;
    END TRY
    BEGIN CATCH
        PRINT 'Error during version transition: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;





CREATE TABLE Dummy_Stadiums (
    dummy_stadium_id INT not null ,  
    stadium_name VARCHAR(50),
    location VARCHAR(100)
);

-- Create Dummy_Teams Table (For Unique Constraint Example)
CREATE TABLE Dummy_Teams (
   dummy_team_id INT,
    team_name VARCHAR(50), 
    foundation_year INT
); 










-- Drop tables if they exist
DROP TABLE IF EXISTS Players;
DROP TABLE IF EXISTS Teams;
DROP TABLE IF EXISTS Matches;
DROP TABLE IF EXISTS Bookings;
DROP TABLE IF EXISTS Goals;
DROP TABLE IF EXISTS Managers;
DROP TABLE IF EXISTS Match_Results;
DROP TABLE IF EXISTS Stadiums;
DROP TABLE IF EXISTS Team_Tournament;
DROP TABLE IF EXISTS Transfers;
DROP TABLE IF EXISTS Tournaments;

-- Drop version management tables
DROP TABLE IF EXISTS switch_state;
DROP TABLE IF EXISTS current_state;


-- Drop stored procedures
DROP PROCEDURE IF EXISTS spModifyColumnType;
DROP PROCEDURE IF EXISTS spReverseModifyColumnType;
DROP PROCEDURE IF EXISTS spAddColumn;
DROP PROCEDURE IF EXISTS spRemoveColumn;
DROP PROCEDURE IF EXISTS spAddDefaultConstraint;
DROP PROCEDURE IF EXISTS spRemoveDefaultConstraint;
DROP PROCEDURE IF EXISTS spAddPrimaryKey;
DROP PROCEDURE IF EXISTS spRemovePrimaryKey;
DROP PROCEDURE IF EXISTS spAddCandidateKey;
DROP PROCEDURE IF EXISTS spRemoveCandidateKey;
DROP PROCEDURE IF EXISTS spAddForeignKey;
DROP PROCEDURE IF EXISTS spRemoveForeignKey;
DROP PROCEDURE IF EXISTS spCreateTable;
DROP PROCEDURE IF EXISTS spDropTable;
DROP PROCEDURE IF EXISTS spSwitchVersion;
