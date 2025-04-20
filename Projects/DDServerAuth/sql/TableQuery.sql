
-- AccountDB Setup Query
--

CREATE TABLE tbl_AccountInfo (
    account_uid     BIGINT IDENTITY(1, 1) PRIMARY KEY,      -- 고유 아이디
    created_at      DATETIME DEFAULT GETDATE(),             -- 계정 생성 시간
    display_name    NVARCHAR(32) NULL,                      -- 사용자 표시 이름
);

CREATE TABLE tbl_GoogleAccount (
    account_uid     BIGINT UNIQUE NOT NULL,                 -- 고유 아이디
    google_id       VARCHAR(50) UNIQUE NOT NULL,            -- Google에서 제공하는 고유 사용자 ID
    email           VARCHAR(255) UNIQUE NOT NULL,           -- 사용자 이메일 (Google 계정)
);

CREATE TABLE tbl_AccountGMInfo (
    account_uid     BIGINT UNIQUE NOT NULL,                 -- 고유 아이디
    access_level    TINYINT UNIQUE NOT NULL,                -- 접근 권한 레벨
);

CREATE TABLE tbl_LastLoginInfo (
    account_uid     BIGINT UNIQUE NOT NULL,                 -- 고유 아이디
    login_time      DATETIME DEFAULT GETDATE() NOT NULL,    -- 마지막 로그인 시간
    provider_name   VARCHAR(20) UNIQUE NOT NULL,            -- google, apple, facebook, email
    ip_address      VARCHAR(45) NULL,                       -- 마지막 접속한 IP 주소 (IPv4/IPv6 지원)
    mac_address     VARCHAR(17) NULL,                       -- 마지막 접속한 MAC 주소 (XX:XX:XX:XX:XX:XX)
    device_info     VARCHAR(255) NULL,                      -- 마지막 접속한 기기 정보
);
