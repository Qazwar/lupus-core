DROP TABLE IF EXISTS Account CASCADE;
CREATE TABLE  Account (
    Username VARCHAR(32) PRIMARY KEY,
    Password TEXT NOT NULL,
    eMail TEXT UNIQUE NOT NULL,
    RegisterDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    LastLogin TIMESTAMP,
    Path VARCHAR(260),
    Forename VARCHAR(64), -- Für Personen
    Surname VARCHAR(64), -- Für Personen
    Name VARCHAR(64) UNIQUE -- Für Firmen
);

DROP TABLE IF EXISTS Tag CASCADE;
CREATE TABLE Tag (
    Name VARCHAR(32) PRIMARY KEY
);

DROP TABLE IF EXISTS Genre CASCADE;
CREATE TABLE Genre (
    Name VARCHAR(32) PRIMARY KEY
);

DROP TABLE IF EXISTS Entity CASCADE;
CREATE TABLE Entity (
    Name VARCHAR(32) PRIMARY KEY
);

DROP TABLE IF EXISTS Copyright CASCADE;
CREATE TABLE Copyright (
    Id BIGSERIAL PRIMARY KEY,
    Holder VARCHAR(64),
    Year INT
);

DROP TABLE IF EXISTS Album CASCADE;
CREATE TABLE Album (
    Id BIGSERIAL PRIMARY KEY,
    Title VARCHAR(64),
    Year INT,
    Price INT
);

DROP TABLE IF EXISTS FriendOrBlocked CASCADE;
CREATE TABLE FriendOrBlocked (
    Id BIGSERIAL PRIMARY KEY,
    Account_Username_1 VARCHAR(32) REFERENCES Account (Username),
    Account_Username_2 VARCHAR(32) REFERENCES Account (Username),
    DateSent DATE DEFAULT CURRENT_DATE,
    DateAccepted DATE,
    Blocked BOOLEAN DEFAULT FALSE
);

/*
SELECT CASE WHEN Account_Username_1='foo' THEN Account_Username_2 ELSE Account_Username_1 END
FROM FriendOrBlocked
WHERE Account_Username_1='foo' OR Account_Username_2='foo';
*/

DROP TYPE IF EXISTS VISIBILITY CASCADE;
CREATE TYPE VISIBILITY AS ENUM ('Public', 'Private', 'None');

DROP TABLE IF EXISTS ContentData CASCADE;
CREATE TABLE ContentData (
    Id BIGSERIAL PRIMARY KEY,
    Account_Username VARCHAR(32) REFERENCES Account (Username),
    Visibility VISIBILITY,
    Artist VARCHAR(64),
    Title VARCHAR(64),
    FileName VARCHAR(32),
    MIME VARCHAR(32),
    Size BIGINT,
    Price INT,
    Uploaded TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE IF EXISTS Image CASCADE;
CREATE TABLE Image (
    Id BIGSERIAL PRIMARY KEY,
    ContentData_Id BIGINT REFERENCES ContentData (Id),
    Width INT,
    Height INT,
    BitDepth INT,
    DateTaken DATE
);

DROP TABLE IF EXISTS Audio CASCADE;
CREATE TABLE Audio (
    Id BIGSERIAL PRIMARY KEY,
    ContentData_Id BIGINT REFERENCES ContentData (Id),
    Subtitle VARCHAR(64),
    Comments VARCHAR(256),
    Length INT,
    BitRate INT,
    Year INT
);

DROP TABLE IF EXISTS Video CASCADE;
CREATE TABLE Video (
    Id BIGSERIAL PRIMARY KEY,
    ContentData_Id BIGINT REFERENCES ContentData (Id),
    Subtitle VARCHAR(64),
    Comments VARCHAR(256),
    Length INT,
    BitRate INT,
    FrameWidth INT,
    FrameHeight INT,
    DataRate INT,
    FrameRate INT,
    AudioBitRate INT,
    AudioChannels INT,
    AudioSampleRate INT,
    Year INT
);

DROP TABLE IF EXISTS ContentData_has_Copyright CASCADE;
CREATE TABLE ContentData_has_Copyright (
    Copyright_Id BIGINT REFERENCES Copyright (Id),
    ContentData_Id BIGINT REFERENCES ContentData (Id)
);

DROP TABLE IF EXISTS ContentData_has_Album CASCADE;
CREATE TABLE ContentData_has_Album (
    Album_Id BIGINT REFERENCES Album (Id),
    ContentData_Id BIGINT REFERENCES ContentData (Id)
);

DROP TABLE IF EXISTS Image_has_Tag CASCADE;
CREATE TABLE Image_has_Tag (
    Image_Id BIGINT REFERENCES Image (Id),
    Tag_Name VARCHAR(32) REFERENCES Tag (Name)
);

DROP TABLE IF EXISTS Audio_has_Tag CASCADE;
CREATE TABLE Audio_has_Tag (
    Audio_Id BIGINT REFERENCES Audio (Id),
    Tag_Name VARCHAR(32) REFERENCES Tag (Name)
);

DROP TABLE IF EXISTS Video_has_Tag CASCADE;
CREATE TABLE Video_has_Tag (
    Video_Id BIGINT REFERENCES Video (Id),
    Tag_Name VARCHAR(32) REFERENCES Tag (Name)
);

DROP TABLE IF EXISTS Audio_has_Genre CASCADE;
CREATE TABLE Audio_has_Genre (
    Audio_Id BIGINT REFERENCES Audio (Id),
    Genre_Name VARCHAR(32) REFERENCES Genre (Name)
);

DROP TABLE IF EXISTS Video_has_Genre CASCADE;
CREATE TABLE Video_has_Genre (
    Video_Id BIGINT REFERENCES Video (Id),
    Genre_Name VARCHAR(32) REFERENCES Genre (Name)
);

DROP TABLE IF EXISTS Audio_has_ContributingArtist CASCADE;
CREATE TABLE Audio_has_ContributingArtist (
    Audio_Id BIGINT REFERENCES Audio (Id),
    Entity_Name VARCHAR(32) REFERENCES Entity (Name)
);

DROP TABLE IF EXISTS Video_has_ContributingArtist CASCADE;
CREATE TABLE Video_has_ContributingArtist (
    Video_Id BIGINT REFERENCES Video (Id),
    Entity_Name VARCHAR(32) REFERENCES Entity (Name)
);

DROP TABLE IF EXISTS Comment CASCADE;
CREATE TABLE Comment (
    Id BIGSERIAL PRIMARY KEY,
    Text VARCHAR(1000),
    Account_Username VARCHAR(32) REFERENCES Account (Username),
    Image_Id BIGINT REFERENCES Image (Id),
    Audio_Id BIGINT REFERENCES Audio (Id),
    Video_Id BIGINT REFERENCES Video (Id)
);
