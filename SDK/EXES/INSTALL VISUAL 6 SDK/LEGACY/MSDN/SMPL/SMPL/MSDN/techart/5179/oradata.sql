/*************************************************************************
	Oracle 7 Database - Sample Application Data Loading Script
	
	The following script loads sample application data into the tables
	required for the sample Oracle program.
*************************************************************************/

/*************************************************************************
	Log on as STUDENT_ADMIN
*************************************************************************/
CONNECT STUDENT_ADMIN/STUDENT_ADMIN@WILBUR

/*************************************************************************
	Delete data from STUDENT and GRADE tables in order for DEPT and
	CLASS tables to be loaded (primary key - foreign key relationship
*************************************************************************/
DELETE FROM STUDENT_ADMIN.GRADE
/

DELETE FROM STUDENT_ADMIN.STUDENT
/

COMMIT
/

/*************************************************************************
	Log on as DEPT_ADMIN
*************************************************************************/
CONNECT DEPT_ADMIN/DEPT_ADMIN@WILBUR

/*************************************************************************
	Delete and load DEPT and CLASS tables
*************************************************************************/
DELETE FROM DEPT_ADMIN.CLASS
/

DELETE FROM DEPT_ADMIN.DEPT
/

COMMIT
/
/*************************************************************************
	Insert into DEPT table
*************************************************************************/
insert into DEPT_ADMIN.DEPT values ('Zoo','Zoology')
/
insert into DEPT_ADMIN.DEPT values ('Bus','Business and Economics')
/
insert into DEPT_ADMIN.DEPT values ('Posc','Political Science')
/
insert into DEPT_ADMIN.DEPT values ('Farm','Farming and Agriculture')
/
insert into DEPT_ADMIN.DEPT values ('Mus','Music')
/
insert into DEPT_ADMIN.DEPT values ('Aero','Aeronautics and Astronautics')
/
insert into DEPT_ADMIN.DEPT values ('Hist','History')
/
insert into DEPT_ADMIN.DEPT values ('Undc','Undeclared')
/

/*************************************************************************
	Insert into CLASS table
*************************************************************************/
insert into DEPT_ADMIN.CLASS values
('6456','Advanced Dirt',                 'Farm','221-B', '4545')
/
insert into DEPT_ADMIN.CLASS values
('5555','Screams, Yells and Shrieks',    'Mus', '321-A', NULL)
/
insert into DEPT_ADMIN.CLASS values
('6666','Flying High',                   'Aero','41-A',  NULL)
/
insert into DEPT_ADMIN.CLASS values
('6767','Theory of Air',                 'Aero','104-A', '6666')
/
insert into DEPT_ADMIN.CLASS values
('9789','Historical Relics',             'Hist','10-C',  '7777')
/
insert into DEPT_ADMIN.CLASS values
('5656','Theory of Sound',               'Mus', '21-A',  '5555')
/
insert into DEPT_ADMIN.CLASS values
('7567','Sound of our Times',            'Mus', '40-B',  '5656')
/
insert into DEPT_ADMIN.CLASS values
('7777','History of the World',          'Hist','302-A', NULL)
/
insert into DEPT_ADMIN.CLASS values
('7878','History of the Cosmos',         'Hist','301-D', '7777')
/
insert into DEPT_ADMIN.CLASS values
('8678','Advanced Altitude Training',    'Aero','101-D', '6767')
/
insert into DEPT_ADMIN.CLASS values
('1111','Basic Species Identification',  'Zoo', '100-B', NULL)
/
insert into DEPT_ADMIN.CLASS values
('1212','Reptiles in Cold Blood',        'Zoo', '103-A', '1111')
/
insert into DEPT_ADMIN.CLASS values
('3123','Flora and Fauna of the Artic',    'Zoo', '29-C',  '1212')
/
insert into DEPT_ADMIN.CLASS values
('2222','Basic Business Principles',     'Bus', '201-A', NULL)
/
insert into DEPT_ADMIN.CLASS values
('2323','Having Fun With Finances',      'Bus', '1001-A','2222')
/
insert into DEPT_ADMIN.CLASS values
('4234','The MARKET',                    'Bus', '1234-B','2323')
/
insert into DEPT_ADMIN.CLASS values
('3333','Making Promises I',             'Posc','23-C',  NULL)
/
insert into DEPT_ADMIN.CLASS values
('3444','Making Promises II',            'Posc','123-A', '3333')
/
insert into DEPT_ADMIN.CLASS values
('3434','High Diplomacy',                'Posc','1000-A','3444')
/
insert into DEPT_ADMIN.CLASS values
('4444','Growing Things of All Sorts',   'Farm','101-C', '4545')
/
insert into DEPT_ADMIN.CLASS values
('4545','Dirt, Dirt and more Dirt',      'Farm','212-B', NULL)
/
insert into DEPT_ADMIN.CLASS values
('4387','Pigs: Grunts, Squeals Snorts','Farm','220-A', '4444')
/

COMMIT
/

/*************************************************************************
	Log on as STUDENT_ADMIN
*************************************************************************/
CONNECT STUDENT_ADMIN/STUDENT_ADMIN@WILBUR

/*************************************************************************
	Load data into STUDENT table
*************************************************************************/
INSERT INTO STUDENT_ADMIN.STUDENT VALUES
('343434343','Susie',    'Hall',            'F','Posc','11-JUL-61',
800, 2500,'01-SEP-86','06-JUN-90',5000,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('222222222','Arthur',  'Hollingshead III','M','Bus', '12-SEP-61',
NULL,3000,'01-SEP-85','06-JUN-88',1250,'M')
/
insert into STUDENT_ADMIN.STUDENT values
('333333333','Crystal','Waters',          'F','Bus', '31-MAR-59',
2000,3000,'01-JAN-86','09-SEP-90',NULL,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('444444444','Alfred',  'Bear',            'M','Zoo', '10-JAN-51',
539, 1500,'01-SEP-84','06-JUN-92',7000,'P')
/
insert into STUDENT_ADMIN.STUDENT values
('555555555','George','Flintrock',      'M','Hist','11-FEB-01',
1000,1750,'01-SEP-85','06-JUN-89',1500,'P')
/
insert into STUDENT_ADMIN.STUDENT values
('666666666','Sally',   'Smith',            'F','Aero','28-OCT-53',
1550,2500,'01-JAN-87','09-SEP-91',1000,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('777777777','Anita',   'Bailey',          'F','Mus', '01-DEC-31',
NULL,1500,'01-JAN-88','09-SEP-92',NULL,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('888888888','Frank',   'Carter',          'M','Farm','15-APR-30',
2000,2000,'01-SEP-87','06-JUN-91',NULL,'M')
/
insert into STUDENT_ADMIN.STUDENT values
('999999999','Elizabeth',  'Jackson',         'F','Posc','28-MAY-41',
1200,2500,'01-SEP-87','06-JUN-89',2000,'P')
/
insert into STUDENT_ADMIN.STUDENT values
('121212121','Johnny',  'Rich',            'M','Bus', '23-JUL-57',
3000,3000,'01-SEP-85','06-JUN-89',NULL,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('232323232','Henry',    'Wells',          'M','Hist','29-JAN-64',
NULL,1750,'01-SEP-87','06-JUN-90',2000,'P')
/
insert into STUDENT_ADMIN.STUDENT values
('454545454','Nancy',  'Carpenter',        'F','Zoo', '01-APR-59',
1500,1500,'01-JAN-88','09-SEP-92',NULL,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('565656565','Elliott', 'Flyer',       'M','Aero','24-SEP-60',
1600,2500,'01-SEP-86','06-JUN-88',1350,'M')
/
insert into STUDENT_ADMIN.STUDENT values
('676767676','Barbara',    'White',           'F','Hist','11-JAN-31',
1750,1750,'01-JAN-85','09-SEP-89',NULL,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('787878787','Jane',    'Simpson',         'F','Farm','21-AUG-63',
NULL,2000,'01-SEP-85','06-JUN-88',1250,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('111111111','Sandy',   'Smith',          'F','Mus', '12-FEB-59',
900, 1500,'01-SEP-87','09-JUN-89',NULL,'M')
/
insert into STUDENT_ADMIN.STUDENT values
('987654321','Barney',    'Domino',          'M','Undc',  '10-MAR-48',
1200,2500,'01-SEP-82','06-JUN-89',4000,'D')
/
insert into STUDENT_ADMIN.STUDENT values
('987987987','Homer',     'Sampson',            'M','Undc',  '01-JAN-37',
2000,3000,'01-SEP-86','06-JUN-90',NULL,'U')
/
insert into STUDENT_ADMIN.STUDENT values
('945763281','Theodore','Gremmling',       'M','Farm','15-SEP-53',
NULL,2500,'01-SEP-87','06-JUN-94',5000,'P')
/
insert into STUDENT_ADMIN.STUDENT values
('756433842','Susie',   'Flanders',        'F','Bus', '27-FEB-68',
1200,2500,'01-JAN-88','01-SEP-92',NULL,'D')
/

/*************************************************************************
	Insert into GRADE table
*************************************************************************/
insert into STUDENT_ADMIN.GRADE values ('454545454','1111','A-')
/
insert into STUDENT_ADMIN.GRADE values ('454545454','3123','C+')
/
insert into STUDENT_ADMIN.GRADE values ('454545454','7777','A')
/
insert into STUDENT_ADMIN.GRADE values ('565656565','6666','B-')
/
insert into STUDENT_ADMIN.GRADE values ('565656565','8678','C+')
/
insert into STUDENT_ADMIN.GRADE values ('676767676','7878','B')
/
insert into STUDENT_ADMIN.GRADE values ('787878787','4444','A')
/
insert into STUDENT_ADMIN.GRADE values ('787878787','4545','B+')
/
insert into STUDENT_ADMIN.GRADE values ('787878787','6456','A-')
/
insert into STUDENT_ADMIN.GRADE values ('111111111','5656','B')
/
insert into STUDENT_ADMIN.GRADE values ('111111111','7567','B+')
/
insert into STUDENT_ADMIN.GRADE values ('222222222','3434','B+')
/
insert into STUDENT_ADMIN.GRADE values ('222222222','3333','A+')
/
insert into STUDENT_ADMIN.GRADE values ('343434343','3333','A+')
/
insert into STUDENT_ADMIN.GRADE values ('222222222','2222','A')
/
insert into STUDENT_ADMIN.GRADE values ('222222222','2323','B+')
/
insert into STUDENT_ADMIN.GRADE values ('222222222','4234','C+')
/
insert into STUDENT_ADMIN.GRADE values ('222222222','7777','B-')
/
insert into STUDENT_ADMIN.GRADE values ('333333333','2222','B-')
/
insert into STUDENT_ADMIN.GRADE values ('333333333','2323','C+')
/
insert into STUDENT_ADMIN.GRADE values ('333333333','1111','A')
/
insert into STUDENT_ADMIN.GRADE values ('444444444','1111','B+')
/
insert into STUDENT_ADMIN.GRADE values ('444444444','7777','D')
/
insert into STUDENT_ADMIN.GRADE values ('555555555','7777','A-')
/
insert into STUDENT_ADMIN.GRADE values ('555555555','7878','B+')
/
insert into STUDENT_ADMIN.GRADE values ('555555555','9789','A')
/
insert into STUDENT_ADMIN.GRADE values ('555555555','3333','B')
/
insert into STUDENT_ADMIN.GRADE values ('666666666','6666','B')
/
insert into STUDENT_ADMIN.GRADE values ('666666666','6767','C+')
/
insert into STUDENT_ADMIN.GRADE values ('777777777','5555','B-')
/
insert into STUDENT_ADMIN.GRADE values ('888888888','4444','B-')
/
insert into STUDENT_ADMIN.GRADE values ('888888888','4545','A+')
/
insert into STUDENT_ADMIN.GRADE values ('888888888','6456','A')
/
insert into STUDENT_ADMIN.GRADE values ('888888888','1111','B+')
/
insert into STUDENT_ADMIN.GRADE values ('999999999','3333','C+')
/
insert into STUDENT_ADMIN.GRADE values ('999999999','3444','B+')
/
insert into STUDENT_ADMIN.GRADE values ('999999999','3434','A-')
/
insert into STUDENT_ADMIN.GRADE values ('999999999','5555','C+')
/
insert into STUDENT_ADMIN.GRADE values ('121212121','2222','B+')
/
insert into STUDENT_ADMIN.GRADE values ('121212121','4234','B-')
/
insert into STUDENT_ADMIN.GRADE values ('232323232','7777','C+')
/
insert into STUDENT_ADMIN.GRADE values ('232323232','9789','A-')
/
insert into STUDENT_ADMIN.GRADE values ('343434343','3434','B-')
/
insert into STUDENT_ADMIN.GRADE values ('987654321','2222','C-')
/
insert into STUDENT_ADMIN.GRADE values ('343434343','1111','F')
/
insert into STUDENT_ADMIN.GRADE values ('987987987','1111','F')
/
insert into STUDENT_ADMIN.GRADE values ('343434343','3444','A-')
/
insert into STUDENT_ADMIN.GRADE values ('945763281','4444','A+')
/
insert into STUDENT_ADMIN.GRADE values ('945763281','4545','A-')
/
insert into STUDENT_ADMIN.GRADE values ('945763281','6456','B+')
/
insert into STUDENT_ADMIN.GRADE values ('945763281','5555','B+')
/
insert into STUDENT_ADMIN.GRADE values ('945763281','1111','C-')
/
insert into STUDENT_ADMIN.GRADE values ('333333333','5555','A+')
/
insert into STUDENT_ADMIN.GRADE values ('444444444','1212','A')
/
insert into STUDENT_ADMIN.GRADE values ('444444444','3123','B-')
/
insert into STUDENT_ADMIN.GRADE values ('555555555','1111','D-')
/
insert into STUDENT_ADMIN.GRADE values ('555555555','1212','C+')
/
insert into STUDENT_ADMIN.GRADE values ('555555555','2323','B')
/
insert into STUDENT_ADMIN.GRADE values ('888888888','3333','A+')
/
insert into STUDENT_ADMIN.GRADE values ('888888888','3444','C+')
/
insert into STUDENT_ADMIN.GRADE values ('987654321','5555','B+')
/

COMMIT
/