USE EPL_Management; 

GO


         -----1. Modify Column Type
--Scenario
--Modify the capacity column in the Stadiums table from INT to BIGINT.
--Revert the capacity column back to INT.

--switch_state Entries
-- Modify column to BIGINT
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spModifyColumnType', 0, 1, 'Modify capacity to BIGINT', 
'@TableName=''Stadiums'', @ColumnName=''capacity'', @NewType=''BIGINT''');


-- Revert column back to INT
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spReverseModifyColumnType', 1, 0, 'Revert capacity to INT', 
'@TableName=''Stadiums'', @ColumnName=''capacity'', @OriginalType=''INT''');


--1. Forward Transition:
EXEC spSwitchVersion @TargetVersion = 1;
--This will change the capacity column in the Stadiums table to BIGINT.


--2. Backward Transition:
EXEC spSwitchVersion @TargetVersion = 0;
-- This will revert the capacity column back to INT.

--Check Column Type in Stadiums:
EXEC sp_help 'Stadiums';

--Check Current Version. 
SELECT * FROM current_state;



      --- 2. Add/Remove a Column
--Scenario
--Add a seating_zone column to the Stadiums table (VARCHAR(50)).
--Remove the seating_zone column.

--switch_state Entries
-- Add column
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spAddColumn', 1, 2, 'Add seating_zone column to Stadiums', 
'@TableName=''Stadiums'', @ColumnName=''seating_zone'', @DataType=''VARCHAR(50)''');

-- Remove column
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spRemoveColumn', 2, 1, 'Remove seating_zone column from Stadiums', 
'@TableName=''Stadiums'', @ColumnName=''seating_zone''');

--Forward Transition:
EXEC spSwitchVersion @TargetVersion = 2;
-- This will add a seating_zone column to the Stadiums table.

--Backward Transition:
EXEC spSwitchVersion @TargetVersion = 1;
--This will remove the seating_zone column.

--Check Column in Stadiums:
EXEC sp_help 'Stadiums';


--Check Current Version. 
SELECT * FROM current_state;



        ----3. Add/Remove Default Constraint
--Scenario
--Add a default value (10000) for the capacity column in the Stadiums table.
--Remove the default constraint.


--switch_state Entries
-- Add default constraint
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spAddDefaultConstraint', 2, 3, 'Add default capacity for Stadiums', 
'@TableName=''Stadiums'', @ColumnName=''capacity'', @DefaultValue=''10000''');


-- Remove default constraint
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description,parameters)
VALUES ('spRemoveDefaultConstraint', 3, 2, 'Remove default capacity from Stadiums', 
'@TableName=''Stadiums'', @ColumnName=''capacity''');


EXEC spRemoveDefaultConstraint @TableName = 'Stadiums' ,@ColumnName = 'capacity';

--Forward Transition:
EXEC spSwitchVersion @TargetVersion = 1;
--Adds a default constraint for the capacity column.

--Backward Transition:
EXEC spSwitchVersion @TargetVersion = 2;
--Removes the deafult constraint

--Verify Changes
--Check Default Constraint:
SELECT COLUMN_DEFAULT 
FROM INFORMATION_SCHEMA.COLUMNS 
WHERE TABLE_NAME = 'Stadiums' AND COLUMN_NAME = 'capacity';

--Chekc current version
SELECT * FROM current_state;




-- Add primary key
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spAddPrimaryKey' , 3, 4, 'Add primary key to Dummy_Stadiums',    
'@TableName=''Dummy_Stadiums'', @ColumnName=''dummy_stadium_id'''
  
);


-- Remove primary key
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spRemovePrimaryKey', 4, 3, 'Remove primary key from Dummy_Stadiums',
'@TableName=''Dummy_Stadiums'''  
);


select * from switch_state; 

--Forward Transition:
EXEC spSwitchVersion @TargetVersion = 1;
--Adds a primary key to the specified column.

--Backward Transition:
EXEC spSwitchVersion @TargetVersion = 3;
--Removes the primary key.


--Verify Changes
--Check Primary Key:
SELECT * 
FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS 
WHERE TABLE_NAME = 'Dummy_Stadiums' AND CONSTRAINT_TYPE = 'PRIMARY KEY';




--Check current version
SELECT * FROM current_state;



       ----5. Add/Remove Candidate Key (Unique Constraint)
--Scenario
--Add a unique constraint to the team_name column in the Teams table.
--Remove the unique constraint.


 ----5. Add/Remove Candidate Key (Unique Constraint)
--Scenario
--Add a unique constraint to the team_name column in the Teams table.
--Remove the unique constraint.



--switch_state Entries
-- Add unique constraint
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spAddCandidateKey', 4, 5, 'Add unique constraint for team_name in Teams',
'@TableName=''Teams'', @Columns=''team_name''');


-- Remove unique constraint
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spRemoveCandidateKey', 5, 4, 'Remove unique constraint for team_name in Teams',
'@TableName=''Teams'', @ConstraintName=''UQ_Teams''');


--Forward Transition:
EXEC spSwitchVersion @TargetVersion = 5;
--Adds a unique constraint to the team_name column.

--Backward Transition:
EXEC spSwitchVersion @TargetVersion = 4;
--Removes the unique constraint.



--Verify Changes
--Check Unique Constraint:
SELECT * 
FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS 
WHERE TABLE_NAME = 'Teams' AND CONSTRAINT_TYPE = 'UNIQUE';


--Check current version
SELECT * FROM current_state;

select * from switch_state; 




        ---6. Add/Remove Foreign Key
--Scenario
--Add a foreign key to the home_team_id column in the Matches 
--table referencing team_id in the Teams table.
--Remove the foreign key.


--switch_state Entries
-- Add foreign key
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spAddForeignKey', 5, 6, 'Add foreign key from Matches to Teams', 
'@TableName=''Matches'', @ColumnName=''home_team_id'',
@ReferencedTable=''Teams'', @ReferencedColumn=''team_id''');


-- Remove foreign key
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spRemoveForeignKey', 6, 5, 'Remove foreign key from Matches to Teams',
'@TableName=''Matches'', @ConstraintName=''FK_Matches_home_team_id''');

--Forward Transition:
EXEC spSwitchVersion @TargetVersion = 6;


--Backward Transition:
EXEC spSwitchVersion @TargetVersion = 5;


--Verify Changes
--Check Foreign Key:
SELECT * 
FROM INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS 
WHERE CONSTRAINT_NAME = 'FK_Matches_home_team_id';

--Check current version
SELECT * FROM current_state;




         ---7. Create/Drop Table
--Scenario
--Create a Referees table.
--Drop the Referees table.


--switch_state Entries
-- Create table
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spCreateTable', 6, 7, 'Create Referees table', '@TableName=''Referees'', 
@Columns=''referee_id INT PRIMARY KEY, name NVARCHAR(50), experience_years INT''');

-- Drop table
INSERT INTO switch_state (procedure_used, from_version, to_version, short_description, parameters)
VALUES ('spDropTable', 7, 6, 'Drop Referees table', '@TableName=''Referees''');

--Forward Transition:
EXEC spSwitchVersion @TargetVersion = 7;


-- Backward Transition:
EXEC spSwitchVersion @TargetVersion = 6;


--Verify Changes
--Check the Table:
SELECT * 
FROM INFORMATION_SCHEMA.TABLES 
WHERE TABLE_NAME = 'Referees';


--Check current version
SELECT * FROM current_state;

