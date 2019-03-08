
DROP TABLE if exists Film;


Create Table Film
(ID_Film Serial Primary Key,
 FI_TITRE Varchar (50),
 FI_DATE_SORTIE int,
 FI_GENRE Varchar (20) ,
 FI_DUREE int,
 FI_LANGUE Varchar (50)
);
