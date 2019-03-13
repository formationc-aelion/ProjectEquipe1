Insert into Film           (FI_TITRE,
                            FI_DATE_SORTIE,
                            FI_GENRE,
                            FI_DUREE,
                            FI_LANGUE,
                            FI_PHOTO,
                            FI_RESUME,
                            ID_REAL)
Values                      ('Django',
                             2012,
                             'Western',
                             164,
                             'Anglais',
                             pg_read_binary_file('C:/Users/Dell/Documents/ProjectEquipe1/image_projet/django.jpg')::bytea,
                            'Dans le sud des États-Unis, deux ans avant la guerre de Sécession, le Dr King Schultz, un chasseur de primes allemand, 
                            fait l’acquisition de Django, un esclave qui peut l’aider à traquer les frères Brittle, les meurtriers qu’il recherche. 
                            Schultz promet à Django de lui rendre sa liberté lorsqu’il aura capturé les Brittle – morts ou vifs.
                            Alors que les deux hommes pistent les dangereux criminels, Django n’oublie pas que son seul but est de retrouver Broomhilda, 
                            sa femme, dont il fut séparé à cause du commerce des esclaves…',
                            1);
Insert into Film           (FI_TITRE,
                            FI_DATE_SORTIE,
                            FI_GENRE,
                            FI_DUREE,
                            FI_LANGUE,
                            FI_PHOTO,
                            FI_RESUME,
                            ID_REAL)
Values                      ('Orange Mecanique',
                             1972,
                             'Science Fiction',
                             136,
                             'Anglais',
                             pg_read_binary_file('C:/Users/Dell/Documents/ProjectEquipe1/image_projet/orangemeca.jpg')::bytea,
                            'Au XXIème siècle, où règnent la violence et le sexe, Alex, jeune chef de bande, exerce avec sadisme une terreur aveugle. 
                            Après son emprisonnement, des psychanalystes l emploient comme cobaye dans des expériences destinées à juguler la criminalité...',
                            2);

Insert into Film           (FI_TITRE,
                            FI_DATE_SORTIE,
                            FI_GENRE,
                            FI_DUREE,
                            FI_LANGUE,
                            FI_PHOTO,
                            FI_RESUME,
                            ID_REAL)
Values                      ('Psychose',
                             1960,
                             'Thriller',
                             109,
                             'Anglais',
                              pg_read_binary_file('C:/Users/Dell/Documents/ProjectEquipe1/image_projet/psychose.jpg')::bytea,
                             'Marion Crane en a assez de ne pouvoir mener sa vie comme elle l entend. Son travail ne la passionne plus, son amant ne peut 
                             l épouser car il doit verser une énorme pension alimentaire le laissant sans le sou... Mais un beau jour, son patron lui demande 
                             de déposer 40 000 dollars à la banque. La tentation est trop grande, et Marion s enfuit avec l argent.
                             Très vite la panique commence à se faire sentir. Partagée entre l angoisse de se faire prendre et l excitation de mener une 
                             nouvelle vie, Marion roule vers une destination qu elle n atteindra jamais. La pluie est battante, la jeune femme s arrête près 
                             d un motel, tenu par un sympathique gérant nommé Norman Bates, mais qui doit supporter le caractère possessif de sa mère.',
                             3);