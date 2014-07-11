/******************************************************************************
    Account
******************************************************************************/

DROP TABLE IF EXISTS Account CASCADE;
CREATE TABLE  Account (
    Username VARCHAR(32) PRIMARY KEY,
    Password BYTEA NOT NULL,
    eMail TEXT UNIQUE NOT NULL,
    LastLogin TIMESTAMP,
    Path VARCHAR(260),
    Forename VARCHAR(64),
    Surname VARCHAR(64),
    Token CHAR(64) UNIQUE,
    PublicKey BYTEA UNIQUE,
    PrivateKey BYTEA UNIQUE,
    RegisterDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE IF EXISTS UserList CASCADE;
CREATE TABLE UserList (
    Id BIGSERIAL PRIMARY KEY,
    Account_Username_1 VARCHAR(32) REFERENCES Account (Username),
    Account_Username_2 VARCHAR(32) REFERENCES Account (Username),
    DateSent DATE DEFAULT CURRENT_DATE,
    DateAccepted DATE,
    Blocked BOOLEAN DEFAULT FALSE
);

DROP TABLE IF EXISTS Mail CASCADE;
CREATE TABLE Mail (
    Id BIGSERIAL PRIMARY KEY,
    Subject VARCHAR(128),
    Content VARCHAR(65536)
);

DROP TABLE IF EXISTS Account_has_Mail CASCADE;
CREATE TABLE Account_has_Mail (
    Account_Username VARCHAR(32) REFERENCES Account (Username),
    Mail_Id BIGINT REFERENCES Mail (Id)
);

/*
    SELECT
        CASE WHEN Account_Username_1='foo' THEN Account_Username_2 ELSE Account_Username_1 END
    FROM
        UserList
    WHERE
        Account_Username_1='foo' OR Account_Username_2='foo';
*/

/******************************************************************************
    Media
******************************************************************************/
DROP TABLE IF EXISTS MIME CASCADE;
CREATE TABLE MIME (
    Template TEXT PRIMARY KEY
);

DROP TABLE IF EXISTS Media CASCADE;
CREATE TABLE Media (
    Id BIGSERIAL PRIMARY KEY,
    Account_Username VARCHAR(32) REFERENCES Account (Username),
    MIME_Template TEXT REFERENCES MIME (Template) NOT NULL,
    FileName VARCHAR(32) NOT NULL,
    Size INT NOT NULL,
    Visible BOOLEAN DEFAULT TRUE,
    Uploaded TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE IF EXISTS Comment CASCADE;
CREATE TABLE Comment (
    Id BIGSERIAL PRIMARY KEY,
    Media_Id BIGINT REFERENCES Media (Id),
    Content VARCHAR(8192)
);

DROP TABLE IF EXISTS Property CASCADE;
CREATE TABLE Property (
    Id BIGSERIAL PRIMARY KEY,
    Key VARCHAR(32) UNIQUE NOT NULL,
    Value VARCHAR(1024)
);

DROP TABLE IF EXISTS Media_has_Property CASCADE;
CREATE TABLE Media_has_Property (
    Media_Id BIGINT REFERENCES Media (Id),
    Property_Id BIGINT REFERENCES Property (Id)
);
