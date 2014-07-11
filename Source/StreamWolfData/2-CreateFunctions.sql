DROP FUNCTION IF EXISTS sw_get_friends (text);
CREATE FUNCTION sw_get_friends(text)
RETURNS TABLE (Username VARCHAR(32)) AS $$ 
    SELECT 
        CASE WHEN 
            Account_Username_1=$1 
        THEN 
            Account_Username_2 
        ELSE 
            Account_Username_1 
        END 
    FROM 
        UserList 
    WHERE 
        Account_Username_1=$1 OR Account_Username_2=$1;
$$ LANGUAGE SQL;
