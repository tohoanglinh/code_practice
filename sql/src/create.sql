/* create table */

CREATE TABLE flights (
    id SERIAL PRIMARY KEY,
    origin VARCHAR(255) NOT NULL,
    destination VARCHAR(255) NOT NULL,
    duration INTEGER NOT NULL
);

