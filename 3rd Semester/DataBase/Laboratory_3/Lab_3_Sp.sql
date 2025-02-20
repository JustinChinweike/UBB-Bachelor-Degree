USE EPL_Management; 

GO  
   

            -- 2. General Stored Procedure


         -- Modify Column Type
CREATE PROCEDURE spModifyColumnType
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128),
    @NewType NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' ALTER COLUMN ' + QUOTENAME(@ColumnName) + N' ' + @NewType;
        EXEC sp_executesql @sql;
        PRINT 'Column type modified successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error modifying column type: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;



---Reverse Modify Column Type
CREATE PROCEDURE spReverseModifyColumnType
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128),
    @OriginalType NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' ALTER COLUMN ' + QUOTENAME(@ColumnName) + N' ' + @OriginalType;
        EXEC sp_executesql @sql;
        PRINT 'Column type reverted successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error reverting column type: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;





       --   Add or Remove Column 
CREATE PROCEDURE spAddColumn
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128),
    @DataType NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' ADD ' + QUOTENAME(@ColumnName) + N' ' + @DataType;
        EXEC sp_executesql @sql;
        PRINT 'Column added successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error adding column: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;



-- Remove Column
CREATE PROCEDURE spRemoveColumn
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' DROP COLUMN ' + QUOTENAME(@ColumnName);
        EXEC sp_executesql @sql;
        PRINT 'Column removed successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error removing column: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;


           -- Add or Remove Default Constraint 
-- Add Default Constraint
CREATE PROCEDURE spAddDefaultConstraint
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128),
    @DefaultValue NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' ADD CONSTRAINT DF_' + @ColumnName +
                   N' DEFAULT ' + @DefaultValue + N' FOR ' + QUOTENAME(@ColumnName);
        EXEC sp_executesql @sql;
        PRINT 'Default constraint added successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error adding default constraint: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;




 --Remove Default Constraint
CREATE PROCEDURE spRemoveDefaultConstraint
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' DROP CONSTRAINT DF_' + @ColumnName;
        EXEC sp_executesql @sql;
        PRINT 'Default constraint removed successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error removing default constraint: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;


              -- Add or Remove Keys
			    -- Primay Key: 

-- Add Primary Key
CREATE PROCEDURE spAddPrimaryKey
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' ADD CONSTRAINT PK_' + @TableName +
                   N' PRIMARY KEY (' + QUOTENAME(@ColumnName) + N')';
        EXEC sp_executesql @sql;
        PRINT 'Primary key added successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error adding primary key: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;


-- Remove Primary Key
CREATE PROCEDURE spRemovePrimaryKey
    @TableName NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' DROP CONSTRAINT PK_' + @TableName;
        EXEC sp_executesql @sql;
        PRINT 'Primary key removed successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error removing primary key: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;




              --Canditate Key (Unique Constraint): 
--Add Candidate Key (Unique Constraint)
CREATE PROCEDURE spAddUniqueConstraint
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' ADD CONSTRAINT UQ_' + @TableName + '_' + @ColumnName +
                   N' UNIQUE (' + QUOTENAME(@ColumnName) + N')';
        EXEC sp_executesql @sql;
        PRINT 'Unique constraint added successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error adding unique constraint: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;



--Remove Candidate Key (Unique Constraint)
-- Remove Unique Constraint Dynamically
CREATE PROCEDURE spRemoveUniqueConstraint
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @ConstraintName NVARCHAR(128);
        DECLARE @sql NVARCHAR(MAX);

        SELECT @ConstraintName = tc.CONSTRAINT_NAME
        FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS AS tc
        INNER JOIN INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE AS ccu
            ON tc.CONSTRAINT_NAME = ccu.CONSTRAINT_NAME
        WHERE tc.TABLE_NAME = @TableName
          AND tc.CONSTRAINT_TYPE = 'UNIQUE'
          AND ccu.COLUMN_NAME = @ColumnName;

        IF @ConstraintName IS NOT NULL
        BEGIN
            SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) + 
                       N' DROP CONSTRAINT ' + QUOTENAME(@ConstraintName);
            EXEC sp_executesql @sql;
            PRINT 'Unique constraint removed successfully.';
        END
        ELSE
            PRINT 'No unique constraint found for the specified column.';
    END TRY
    BEGIN CATCH
        PRINT 'Error removing unique constraint: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;



DROP PROCEDURE spAddForeignKey

        --   Add or Remove Foreign Key
-- Add Foreign Key
CREATE PROCEDURE spAddForeignKey
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128),
    @ReferencedTable NVARCHAR(128),
    @ReferencedColumn NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) +
                   N' ADD CONSTRAINT FK_' + @TableName + '_' + @ColumnName +
                   N' FOREIGN KEY (' + QUOTENAME(@ColumnName) + N') REFERENCES ' +
                   QUOTENAME(@ReferencedTable) + '(' + QUOTENAME(@ReferencedColumn) + N')';
        EXEC sp_executesql @sql;
        PRINT 'Foreign key added successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error adding foreign key: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;



-- Remove Foreign Key Dynamically
CREATE PROCEDURE spRemoveForeignKey
    @TableName NVARCHAR(128),
    @ColumnName NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @ConstraintName NVARCHAR(128);
        DECLARE @sql NVARCHAR(MAX);

        SELECT @ConstraintName = fk.name
        FROM sys.foreign_keys AS fk
        INNER JOIN sys.foreign_key_columns AS fkc
            ON fk.object_id = fkc.constraint_object_id
        WHERE fkc.parent_object_id = OBJECT_ID(@TableName)
          AND COL_NAME(fkc.parent_object_id, fkc.parent_column_id) = @ColumnName;

        IF @ConstraintName IS NOT NULL
        BEGIN
            SET @sql = N'ALTER TABLE ' + QUOTENAME(@TableName) + 
                       N' DROP CONSTRAINT ' + QUOTENAME(@ConstraintName);
            EXEC sp_executesql @sql;
            PRINT 'Foreign key removed successfully.';
        END
        ELSE
            PRINT 'No foreign key constraint found for the specified column.';
    END TRY
    BEGIN CATCH
        PRINT 'Error removing foreign key: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;


               -- Create or Drop Table
--Create Table
CREATE PROCEDURE spCreateTable
    @TableName NVARCHAR(128),
    @Columns NVARCHAR(MAX)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'CREATE TABLE ' + QUOTENAME(@TableName) + N' (' + @Columns + N')';
        EXEC sp_executesql @sql;
        PRINT 'Table created successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error creating table: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;


--Drop Table
CREATE PROCEDURE spDropTable
    @TableName NVARCHAR(128)
AS
BEGIN
    BEGIN TRY
        DECLARE @sql NVARCHAR(MAX);
        SET @sql = N'DROP TABLE ' + QUOTENAME(@TableName);
        EXEC sp_executesql @sql;
        PRINT 'Table dropped successfully.';
    END TRY
    BEGIN CATCH
        PRINT 'Error dropping table: ' + ERROR_MESSAGE();
        THROW;
    END CATCH
END;



-- #######################################
-- # COMPLETE ADD/REMOVE OPERATIONS PROVIDED #
-- #######################################


           